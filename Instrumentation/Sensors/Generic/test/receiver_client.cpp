//                              -*- Mode: C++ -*- 
// receiver.cpp --- 
// Author           : Manoj Srivastava ( srivasta@ember.green-gryphon.com ) 
// Created On       : Fri Dec 14 11:33:18 2001
// Created On Node  : ember.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Fri Dec 14 11:56:21 2001
// Last Machine Used: ember.green-gryphon.com
// Update Count     : 6
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

/** @file 
 *  @ingroup GenericSensor 
 *  @brief implementation of the client program
 *
 * $Id: receiver_client.cpp,v 1.2 2001/12/15 02:53:03 srivasta Exp $
 */

/// RCS version string
static const char* version = 
"$Id: receiver_client.cpp,v 1.2 2001/12/15 02:53:03 srivasta Exp $";


#include "ace/OS.h"             
#include "ace/Log_Msg.h"
#include "ace/Containers_T.h"
#include "ace/Get_Opt.h"
#include "ace/Thread.h"
#include "ace/Synch.h"
#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include "tao/ORB_Core.h"

#include "CORBA_Handles.h"
#include "Push_Consumer.h"

#include "YP_Offer.h"
#include "Receiver.h"
#include "TraderC.h"
#include "Debug.h"

#include "Parse_XML.h"

#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"

using namespace CosTradingRepos;
using namespace CosTrading;


#include <string>
#include <cstring>
#include <csignal>
#include <cstdio>

#include <exception>

/// using the std name space.
using namespace std;

/// The client is a global variable
Test_Receiver *client_p = new Test_Receiver();

/**
 * @brief A concrete implementation for handling errors 
 *
 * This class is used to register a signal handler registered with the
 * reactor used by the TAO ORB. We over ride the handle_signal method
 * and use it to act on signals we register handlers for.
 */
class client_error_handler : public ACE_Event_Handler
{
public:
  /// The default constructor for the classclient_error_handler
  client_error_handler(Test_Receiver *client_p):  _client_p(client_p){};
  /// This method takes action on an   signal event.
  int handle_signal (int signum, siginfo_t *info_p, ucontext_t* context_p);
  
private:
  /// Private destructor so that the signal handler is always created
  /// dynamically and hence the heap doesnt get corrupted.
  /// the destructor
  ~client_error_handler(){};
  /// Without this g++ complains about the private destructor
  friend class Shut_Up_G_Plus_Plus;
  
  /// Stash away the sensor object so we can exit gracefully
  Test_Receiver *_client_p;  
};	// end of class client_error_handler

/**
 * @brief The action to take when a registered signal is  handled. 
 *
 * Essentially, we just shut down the sensor object, which
 * causes the ORB to shutdown.
 */
int
client_error_handler::handle_signal (int signum, siginfo_t *info_p, 
				     ucontext_t* context_p)
{
  cerr << "Received signal" << signum << std::endl;
  this->_client_p->cleanup();
  return 0;
}

void
add_handler(client_error_handler *signal_handler_p, 
	    STDC::QMS::CORBA_Handles *handles_p, int signal)
{
//       CORBA::ORB_var my_orb = handles_p->get_orb_handle();
//       TAO_ORB_Core *orb_core_p = my_orb->orb_core();
//       ACE_Reactor *reactor_p = orb_core_p->reactor();
//       int ret = reactor_p->register_handler(SIGINT, signal_handler_p);
  DEBUG1 (4, "DEBUG: Adding signal for signal number %d\n",
	  signal);

  if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler(signal, signal_handler_p) == -1)
   {
     std::cerr << "Error:register_handler for " << signal
	       << std::endl;
     if(handles_p)
      {
	delete handles_p;
	handles_p = 0;
      } /* end of if(handles_p) */
     exit (EXIT_FAILURE);
   }
}



/**
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 *
 * Usage:   [CORBA OPTIONS] [OPTIONS]
 *     -  -h             : This help text
 *     -  -v             : Prints out the version
 */
int
main (int argc, char *argv[])
{
  QMS_Trace ("main", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: starting\n");

  DEBUG0 (4, "DEBUG: added signal handling\n");
  ACE_OS::srand(time(0));

  char *qun_category = 0;
  char *limiter_p = const_cast< char * >("qms:payload");
  

  client_error_handler *signal_handler_p = new client_error_handler(client_p);

  STDC::QMS::CORBA_Handles *handles_p = new STDC::QMS::CORBA_Handles();
  if(!handles_p)
   {
       cerr << "Error creating corba handles" <<std::endl;
       exit (EXIT_FAILURE);
   } /* end of if(!handles_p) */

  DEBUG0 (4, "DEBUG: parsing arguments\n");
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
	cerr << argv[0] << version << endl
	     << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
	     << endl
	     << "\t-h                 : This help text"  << endl
	     << "\t-help              : This help text"  << endl
	     << "\t-v                 : Prints out the version"  << endl
 	     << "\t-version           : Prints out the version"  << endl
	     << "\t-q category        : QMS Unique Name Category" << endl
	     << "\t-qun_category category : QMS Unique Name Category" << endl
             << "\t-p delim-tag       : The tag contianing interesting data"
             << "\t-payload delim-tag : The tag contianing interesting data"
	     << endl
             << "                       defaults to [qms:payload]"
	     << endl
	  ;
	exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
	cerr << argv[0] << ": Version "<< version << endl;
	exit (0);
      }

     if (! strcmp((argv[i] + j), "qun_category") || strchr((argv[i] + j), 'q'))
      {
          qun_category = (char *) malloc (strlen(argv[i + 1]) + 1);
          strcpy(qun_category,argv[i + 1]);
          continue;
      }
     if (! strcmp((argv[i] + j), "payload") || strchr((argv[i] + j), 'p'))
      {
	limiter_p = (char *) malloc (strlen(argv[i + 1]) + 1);
	strcpy(limiter_p, argv[i + 1]);
	continue;
      }
     
     cerr << "unknown argument " << argv[i] << std::endl;
   }

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
  
      DEBUG0 (4," Initializing the Corba Handles \n");
      handles_p->init(argc, argv, "Receiver Client", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      DEBUG0 (4,"Activating POA Manager using the handles.\n ");
      handles_p->activate_poa_manager(ACE_TRY_ENV);
      ACE_TRY_CHECK;
 
      add_handler(signal_handler_p, handles_p, SIGINT);
#if !defined(_WIN32)
      add_handler(signal_handler_p, handles_p, SIGHUP);
#endif

      client_p->init(*handles_p, (char *)"QMS Probes receive client", 
		     qun_category,  limiter_p, ACE_TRY_ENV);
      DEBUG0 (4, "DEBUG: Client intialized. Client going to run\n");
      DEBUG0 (4, "DEBUG: Entering Loop\n");
      handles_p->run(ACE_TRY_ENV);	
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      client_p->cleanup();
      exit (1);
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      client_p->cleanup();
      exit (2);
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      client_p->cleanup();
      exit (3);
    }
  ACE_ENDTRY;

  cout << "Client Done" << endl;
  exit(EXIT_SUCCESS);
}

