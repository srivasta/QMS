//                              -*- Mode: C++ -*-
// test_desi.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Tue Oct 24 01:20:39 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Jan 14 23:28:19 2001
// Last Machine Used: ember
// Update Count     : 114
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: test_desi.cpp,v 1.8 2001/10/21 08:54:10 srivasta Exp $
//

/*
 * Copyright (C) 2001 System/Technology Development Corporation
 * This file is part of QoS Metrics Services (QMS)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA
 *
 * You may contact System/Technology Development Corporation at
 *
 *     System/Technology Development Corporation
 *     Suite 500, Center for Innovative Technology,
 *     2214 Rock Hill Road,
 *     Herndon, VA 20170    
 *     (703) 476-0687
 */


/** @file test_desi.cpp
 *  @ingroup Remos Testing
 *  @brief Implentation of a mock desi module for testing
 *
 *  We implement a mock Desi module here which can generate Remos
 *  queries, either sending a static query, or reading from a file,
 *  and displays the data returned from the respondent at the other
 *  end.
 *
 *  The module also exercizes the XML conversion routines
 */

#include <signal.h>

#include <string>
extern "C" {
#include <string.h>
}

#include <vector>
#include "ace/OS.h"             // For the LM_DEBUG macros
#include "ace/Log_Msg.h"
#include "ace/Thread.h"
#include "ace/Synch.h"
#include "QMS_Remos_Msg.h"
#include "Remos_Datastructs.h"
#include "QMS_Config.h"
#include "QMS_Api.h"
#include "QMS_Debug.h"

#include "orbsvcs/Time_Utilities.h"
#include "orbsvcs/Event_Utilities.h"

/// Where we stash a handle for the QMS API object
QMS_Api qms_api;
/// sequence number of the message being sent, initially 0
int count = 0;
/// A mutex to protect the sequence
ACE_Thread_Mutex TD_asset_guard;
/// RCS version string
static const char* version = "$Id: test_desi.cpp,v 1.8 2001/10/21 08:54:10 srivasta Exp $";
/// A place to stash the pointer to a file name
char *filename_p = 0;



/**
 *  @param sig The signal being handled
 *  @brief The Default signal handler
 *
 * Ensure that we disconnect cleanly from QMS
 */
void
sig_handler (int sig)
{
  QMS_Trace ("sig_handler", __LINE__, __FILE__);
  DEBUG1 (DEBUG_L_ENTER, "caught signal %d\n", sig);
  qms_api.disconnect();
  exit (sig);
}


/** @fn void mock_message(void)
 *  @brief  Generate a test Remos Query randomly
 *
 * Here we generate a mock query statically, incrementing the request
 * ID every time we are invoked. We instantiate a struct Query_struct,
 * populate it, and use a QMS_Remos_Msg object to facilitate
 * conversion to XML
 */
void
mock_message(void)
{
  QMS_Trace ("mock_message", __LINE__, __FILE__);
  Query_struct query;
  ACE_Write_Guard<ACE_Thread_Mutex> guard(TD_asset_guard);
  {
    query.request_id = count++;
  }
  query.request_id = 0;
  query.repeat_count = 5;
  query.refresh_rate = 2.45;
  query.type = Query_struct::link;
  query.host_names = "skywalker_t.stdc.com,kenobee_t.stdc.com,c3po_t.stdc.com";
  DEBUG0 (DEBUG_L_CALL, "DEBUG Created Query\n");
  cout << "============================================================"
       <<endl;
  print_query(&query);
  cout << "============================================================"
       <<endl;

  QMS_Remos_Msg message;
  message.insert(query);
  string data = message.as_string();
  qms_api.send(data);
  DEBUG0 (DEBUG_L_LEAVE, "DEBUG Sending all done\n");
}

/// The maximum number of characters in a path element
#ifndef PATH_MAX
# define PATH_MAX 4095
#endif

/**
 *  @param file_p Name of the file to read the message from
 *  @brief  Generate a test Remos Query from a file
 *
 * Instead of generating a mock query by populating a struct on the
 * fly, we read the query directly from a file. It is assumed that the
 * file is in a format that is being expected by the remote end.
 */
void
file_message(char * file_p)
{
  QMS_Trace ("file_message", __LINE__, __FILE__);
  // We need to read this file
  // We assume that the file has a genuine XML message, since until we
  // have a validating parser, little can be done about error checking
  DEBUG0 (DEBUG_L_ENTER, "DEBUG opening file\n");
  FILE *input_file_p = fopen(file_p, "r");
  if (!input_file_p)
   {
     DEBUG1 (DEBUG_L_ENTER, "Error reading file %s \n", file_p);
     perror("fopen error");
     exit (errno);
   }
  char buffer[PATH_MAX];
  string file;
  DEBUG0 (DEBUG_L_CALL, "DEBUG reading file\n");
  while (fgets (buffer, PATH_MAX, input_file_p))
  {
    file.append(buffer);
  }
  DEBUG0 (DEBUG_L_CALL, "DEBUG sending file\n");
  qms_api.send(file);

#if 0
  string query;

  QMS_Remos_Msg message;
  // OK. Now for parsing the message

  size_t location = 0;
  size_t start = 0;
  size_t stop = 0;
#endif
  DEBUG0 (DEBUG_L_LEAVE, "DEBUG Sending all done\n");
}



/**
 *  This is where we send all the test messages. Depending o the
 *  argument, either we read a static XML evnt from a file (and thus
 *  there is no XML conversion overhead incurred), or we instantiate
 *  and populate a struct Query_struct for every message and convert
 *  it to XML format using a QMS_Remos_Msg object on the fly.
 */
void
generate_query(void)
{
  QMS_Trace ("generate_query", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG Thread Created\n");
  ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval * ACE_OS::rand()%30, 0);
  DEBUG0 (DEBUG_L_CALL, "DEBUG Thread sleeping\n");
  ACE_Thread::yield();
  ACE_OS::sleep (sleep_time);
  DEBUG0 (DEBUG_L_CALL, "DEBUG Thread awake\n");

  if (filename_p)
   {
     file_message(filename_p);
   }
  else
   {
     mock_message();
   }
  DEBUG0 (DEBUG_L_LEAVE, "DEBUG Thread all done, exiting\n");
}



/**
 *  @param data The data recieved from the event channel
 *  @param arg_p Optional argument
 *  @brief Function called when there is an event to be consumed
 *
 *  Whenever an event is recieved, we convert it from XML into a a
 *  struct Data_struct, printing out both the data structure and the
 *  converted XML
 */
void
my_cb_func(const string &data, void *arg_p = 0)
{
  QMS_Trace ("my_cb_func", __LINE__, __FILE__);
  cout << "============================================================"
       <<endl;

  cout << "Got some data" << endl
       << data << endl;

  if (arg_p)
   {
     cout << "With a non null argument"  << endl;
   }


  QMS_Remos_Msg message;
  message.insert(data);
  struct Data_struct *data_p = message.extract_data();
  cout << "============================================================"
       <<endl;
   print_data(data_p);
  cout << "============================================================"
       <<endl;
 }


/**
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 * Usage:   [CORBA OPTIONS] [OPTIONS]
 *     -  -h             : This help text
 *     -  -v             : Prints out the version
 *     -  -file Filename : Read XML data from here
 *     -  -f    Filename : Read XML data from here
 *     -  -ecname NAME   : The name of the event channel
 *     -  -e      NAME   : The name of the event channel
 */
int
main (int argc, char *argv[])
{
  QMS_Trace ("main", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: starting\n");
  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);

  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");
  ACE_OS::srand(time(0));

  DEBUG3 (DEBUG_L_CALL, "DEBUG: starting the API With ID = %d"
	  " Send event type = %d Recieve event type = %d\n" ,
	  Query_Supplier, QMS_Remos_Query, QMS_Remos_Data);

  char * ecname_p = (char *) "QMS_Channel";

  DEBUG0 (DEBUG_L_CALL, "DEBUG: parsing arguments\n");
  for (int i = 0; i < argc; i++)
   {
     if (!argv[i])           { break; }
     if (argv[i][0] != '-')  { continue; }
     int j = 1;
     if (argv[i][1] == '-')  {
       if (argv[i][2] == 0)  { break; }	// handle -- end of options
       j = 2;			// handle --argument
     }
     if (strstr((argv[i] + j), "ORB"))  { continue; }
     if (! strcmp((argv[i] + j), "help") || strchr((argv[i] + j), 'h'))
      {				// -h or --help
	cout << argv[0] << version << endl
	     << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
	     << endl
	     << "\t-h             : This help text"  << endl
	     << "\t-v             : Prints out the version"  << endl
	     << "\t-file Filename : Read XML data from here"  << endl
	     << "\t-f    Filename : Read XML data from here"  << endl
	     << "\t-ecname NAME   : The name of the event channel"  << endl
	     << "\t-e      NAME   : The name of the event channel"  << endl
	  ;
	exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
	cout << argv[0] << ": Version "<< version << endl;
	exit (0);
      }

     if (! strcmp((argv[i] + j), "file") || strchr((argv[i] + j), 'f'))
      {
	filename_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
	strcpy(filename_p,argv[i + 1]);
	continue;
      }
     if (! strcmp((argv[i] + j), "ecname") || strchr((argv[i] + j), 'f'))
      {
	ecname_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
	strcpy(ecname_p,argv[i + 1]);
	continue;
      }
     DEBUG1 (DEBUG_L_ERROR, "unknown argument %s", argv[i] );
   }


  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {

      qms_api.init(argc, argv,
		   Query_Supplier,  // My ID
		   QMS_Remos_Query, //  The data I send
		   QMS_Remos_Data,  // The data I get
		   ecname_p
		   );
      ACE_TRY_CHECK;


      qms_api.register_callback(my_cb_func, 0);
      ACE_TRY_CHECK;
      qms_api.connect_supplier();
      ACE_TRY_CHECK;
      qms_api.connect_consumer();
      ACE_TRY_CHECK;

      DEBUG0 (DEBUG_L_CALL, "DEBUG: Spawning a thread\n");

      if (ACE_Thread::spawn((ACE_THR_FUNC)generate_query,
			    0,	// arg
			    THR_JOINABLE, // flags
			    0,	// t_id
			    0,	// t_handle
			    ACE_DEFAULT_THREAD_PRIORITY,
			    0,	// stack
			    0,	// stack_size
			    0	// thread_adapter
			    )==-1)
       {
	 DEBUG0 (DEBUG_L_ERROR, "DEBUG: Error in spawning thread\n");
       }
      DEBUG0 (DEBUG_L_CALL, "DEBUG: Entering Loop\n");
      qms_api.listen();
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      qms_api.connect_supplier();
      qms_api.connect_consumer();
	exit (1);
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      qms_api.connect_supplier();
      qms_api.connect_consumer();
      exit (2);
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      qms_api.connect_supplier();
      qms_api.connect_consumer();
      exit (3);
    }
  ACE_ENDTRY;

  exit (0);
}
