//                              -*- Mode: C++ -*-
// bench_recv.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Fri Dec  8 15:33:54 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Jan 14 23:27:33 2001
// Last Machine Used: ember
// Update Count     : 24
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
//
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


/** @file bench_recv.cpp
 *  @ingroup Remos Benchmarks
 *  @brief The reciever/reflector part of the QMS benchmark test.
 *
 *  This is a part of a two part test designed to provide round trip
 *  latency metrics of a typical QMS event transaction.
 */


#include <signal.h>

#include <string>
extern "C" {
#include <string.h>
}

#include <vector>
#include "ace/Log_Msg.h"
#include "QMS_Api.h"
#include "QMS_Remos_Msg.h"
#include "QMS_Debug.h"
#include "Remos_Datastructs.h"


/// RCS version string
static const char* version = "$Id: bench_recv.cpp,v 1.7 2001/10/21 08:54:10 srivasta Exp $";

/// Where we stash a handle for the QMS API object
QMS_Api qms_api;
/// sequence number of the message being sent, initially 0
int count = 0;
/// A mutex to protect the sequence
ACE_Thread_Mutex TR_asset_guard;
/// Where the event data that is sent is stashed
string event_data;

/**
 *  @param sig The signal being handled
 *  @brief The default signal handler
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

/**
 *  @param query The query recieved from the event channel
 *  @param arg_p Optional additional argument, unused
 *  @brief Call back when an event is recieved
 *
 *  When we recieve an event, we immediately send a event back on the
 *  event channel. No local processing is done.
 */
void
my_cb_func(const string &query, void * arg_p = 0)
{
  QMS_Trace ("my_cb_func", __LINE__, __FILE__);
  qms_api.send(event_data);
}

/**
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 *  @brief The main entry point
 *
 *  Usage:   [CORBA OPTIONS] [OPTIONS]
 *   -  -h             : This help text
 *   -  -v             : Prints out the version
 *   -  -file Filename : Read XML data from here
 *   -  -f    Filename : Read XML data from here
 *   -  -ecname NAME   : The name of the event channel
 *   -  -e      NAME   : The name of the event channel
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
  DEBUG3(DEBUG_L_CALL, "DEBUG: starting the API With ID = %d "
	 " Send event type = %d Recieve event type = %d\n",  Data_Supplier,
	 QMS_Remos_Data, << QMS_Remos_Query );

  char * ecname_p = (char *) "QMS_Channel";
  char *source_p = (char *) "quite05_t";
  char *destination_p = (char *) "Host_Two";

  Data_struct data;
  ACE_Write_Guard<ACE_Thread_Mutex> guard(TR_asset_guard);
  {
    data.request_id = count++;
    data.data_id = 3 + count;
  }
  data.refresh_rate = 2.45;
  data.latency = 0.135;
  data.available_bandwidth = 50000.0;
  data.maximum_bandwidth  = 100000.0;
  data.type = Data_struct::link;
  data.source = source_p;
  data.destination = destination_p;

  QMS_Remos_Msg message;
  message.insert(data);
  event_data = message.as_string();

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
	cout << argv[0] << ": Version " << version << endl;
	exit (0);
      }

     if (! strcmp((argv[i] + j), "ecname") || strchr((argv[i] + j), 'f'))
      {
	ecname_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
	strcpy(ecname_p,argv[i + 1]);
	continue;
      }
     DEBUG1 (DEBUG_L_ERROR, "unknown argument", argv[i]);

   }


  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {

      qms_api.init(argc, argv,
		   Data_Supplier,   // My ID
		   QMS_Remos_Data,  //  The data I send
		   QMS_Remos_Query, // The data I get
		   ecname_p
		   );
      ACE_TRY_CHECK;
      qms_api.register_callback(my_cb_func, 0);
      ACE_TRY_CHECK;
      qms_api.connect_supplier();
      ACE_TRY_CHECK;
      qms_api.connect_consumer();
      ACE_TRY_CHECK;
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

