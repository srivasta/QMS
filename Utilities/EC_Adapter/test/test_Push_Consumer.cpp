//                              -*- Mode: C++ -*- 
// test_Push_Consumer.cpp --- 
// Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
// Created On       : Mon Aug 13 12:40:49 2001
// Created On Node  : ember.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Mon Aug 13 12:59:26 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 10
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


/// RCS version string
static const char* version = "$Id: test_Push_Consumer.cpp,v 1.5 2001/12/04 18:19:10 spatil Exp $";

#include <signal.h>

#include <string>
extern "C" {
#include <string.h>
}

#include "Debug.h"
#include "Push_Consumer.h"


/// The Remos data event type
static const RtecEventComm::EventType
QMS_Remos_Data =  ACE_ES_EVENT_UNDEFINED  + 2400;

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
  ACE_DEBUG ((LM_DEBUG, "caught signal %d\n", sig));
  exit (sig);
}


void 
my_callback(const string &data, void *arg_p)
{
  cout << "In call back" << endl;
  if(!arg_p)
   {
     cout << "We have an argument" << endl;
   } /* end of if(!arg_p) */
  cout << data <<endl;
}

int
main(int argc, char *argv[])
{
  QMS_Trace ("main", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: starting\n");
  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);

  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");
  ACE_OS::srand(time(0));

  char * ecname_p = (char *) "QMS_Channel";
  char * filename_p = 0;

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

  STDC::QMS::Push_Consumer consumer;
  STDC::QMS::CORBA_Handles handles;
   

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
	  handles.init(argc, argv, "test_consumer", ACE_TRY_ENV);
	  ACE_TRY_CHECK;

	  handles.add_event_channel(ecname_p, ACE_TRY_ENV);
	  ACE_TRY_CHECK;

      consumer.init(handles, QMS_Remos_Data, ecname_p, ACE_TRY_ENV);
      ACE_TRY_CHECK;
      
      consumer.register_callback(&my_callback, 0);
      
      consumer.connect(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_ConsumerQOS_Factory &qos = consumer.get_subscription();
      ACE_TRY_CHECK;
      
      consumer.set_subscription(qos);
      ACE_TRY_CHECK;

	  handles.activate_poa_manager(ACE_TRY_ENV);
	  ACE_TRY_CHECK;

	  handles.run(ACE_TRY_ENV);
	  ACE_TRY_CHECK;
      //consumer.disconnect();
      //ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY; 

  return 0;
} /* end of main() */
