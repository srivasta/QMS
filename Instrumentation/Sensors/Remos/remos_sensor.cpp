//                              -*- Mode: C++ -*- 
// remos_sensor.cpp --- 
// Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
// Created On       : Wed Jul 25 20:46:23 2001
// Created On Node  : ember.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Dec  8 00:16:10 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 110
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


/** @file remos_sensor.cpp
 *  @ingroup RemosSensor
 *  @brief Driver for the Remos sensor
 *
 * $Id: remos_sensor.cpp,v 1.34 2001/12/09 02:14:18 nath Exp $
 */

#include "ace/Synch.h"
#include "ace/Thread.h"
#include "ace/Containers_T.h"
#include "ace/Get_Opt.h"
#include "ace/Reactor.h"
#include "ace/Event_Handler.h"

#include "orbsvcs/CosNamingC.h"
#include "orbsvcs/Event_Utilities.h"
#include "tao/ORB_Core.h"

#if !defined(_WIN32)
#include <sys/types.h>
#include <sys/wait.h>
#endif

#include "Debug.h"

#include "CORBA_Handles.h"
#include "Push_Consumer.h"
#include "Push_Supplier.h"

#include "Remos_Sensor_Impl.h"

/// RCS version string
static const char* version = 
"$Id: remos_sensor.cpp,v 1.34 2001/12/09 02:14:18 nath Exp $";

/// The servant that instantiates the sensor is a global variable
STDC::QMS::Citizen::Remos_Sensor_Impl *sensor_p = 
   new STDC::QMS::Citizen::Remos_Sensor_Impl();

/**
 * @brief A concrete implementation for handling errors 
 *
 * This class is used to register a signal handler registered with the
 * reactor used by the TAO ORB. We over ride the handle_signal method
 * and use it to act on signals we register handlers for.
 */
class sensor_error_handler : public ACE_Event_Handler
{
public:
  /// The default constructor for the classsensor_error_handler
  sensor_error_handler(STDC::QMS::Citizen::Remos_Sensor_Impl *sensor_p,
		       STDC::QMS::CORBA_Handles *handles_p):
    handles_p_(handles_p), sensor_p_(sensor_p) {};

  /// This method takes action on an   signal event.
  int handle_signal (int signum, siginfo_t *info_p, ucontext_t* context_p);

  
protected:
  
private:
  /// Private destructor so that the signal handler is always created
  /// dynamically and hence the heap doesnt get corrupted.
  /// the destructor
  ~sensor_error_handler(){};
  /// Without this g++ complains about the private destructor
  friend class Shut_Up_G_Plus_Plus;

  /// Stash away a pointer to the the CORBA Handles
  STDC::QMS::CORBA_Handles *handles_p_;
  
  /// Stash away the sensor object so we can exit gracefully
  STDC::QMS::Citizen::Remos_Sensor_Impl *sensor_p_;
  
};	// end of class sensor_error_handler

/**
 * @brief The action to take when a registered signal is  handled. 
 *
 * Essentially, we just shut down the sensor object, which
 * causes the ORB to shutdown.
 */
int
sensor_error_handler::handle_signal (int signum, siginfo_t *info_p, 
				     ucontext_t* context_p)
{
  std::cerr << "Received signal" << signum << std::endl;
  if(signum == SIGCHLD)
   {
     std::cerr << " Handling SIGCHLD" << std::endl;
#if !defined(_WIN32)
     pid_t pid;
     int stat;
     while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
      {
	std::cerr << " Child" << pid << " terminated" << std::endl;
      } /* end of while((pid = waitpid(-1, &stat, WNOHANG)) > 0) */
#endif
     return 0;
   } /* end of if(signum == SIGCHLD) */
  
  this->sensor_p_->cleanup();
  this->handles_p_->get_orb_handle()->shutdown ();
  return 0;
}

void
add_handler(sensor_error_handler *signal_handler_p, 
	    STDC::QMS::CORBA_Handles *handles_p, int signal)
{
//       CORBA::ORB_var my_orb = handles_p->get_orb_handle();
//       TAO_ORB_Core *orb_core_p = my_orb->orb_core();
//       ACE_Reactor *reactor_p = orb_core_p->reactor();
//       int ret = reactor_p->register_handler(SIGINT, signal_handler_p);
  DEBUG1 (4, "DEBUG: Adding signal for signal number %d\n",
	  signal);

  if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler(SIGINT, signal_handler_p) == -1)
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
 * This is the main driver for the generic sensor
 */
int
main(int argc, char *argv[])
{
  std::cerr << "Remos Sensor starting up" <<std::endl;
  // Create a Generic Sensor object. Perhaps this should be a static,
  // global variable? 
  string credentials;

  
  char *filename_p = 0;
  STDC::QMS::CORBA_Handles *handles_p = new STDC::QMS::CORBA_Handles();
  if(!handles_p)
   {
       std::cerr << "Error creating corba handles" <<std::endl;
       exit (EXIT_FAILURE);
   } /* end of if(!handles_p) */
      
  sensor_error_handler *signal_handler_p = new sensor_error_handler(sensor_p,
								    handles_p);

  DEBUG0 (DEBUG_L_CALL, "DEBUG: parsing arguments\n");
  for (int i = 0; i < argc; i++)
   {
     if (!argv[i])           { break; }
     if (argv[i][0] != '-')  { continue; }
     int j = 1;
     if (argv[i][1] == '-')  {
       if (argv[i][2] == 0)  { break; } // handle -- end of options
       j = 2;                   // handle --argument
     }
     if (strstr((argv[i] + j), "ORB"))  { continue; }
     if (! strcmp((argv[i] + j), "help") || strchr((argv[i] + j), 'h'))
      {                         // -h or --help
        std::cout << argv[0] << version << std::endl
		  << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
		  << std::endl
		  << "\t-h             : This help text"  << std::endl
		  << "\t-v             : Prints out the version"  << std::endl
		  << "\t-file Filename : Read XML data from here"  << std::endl
		  << "\t-f    Filename : Read XML data from here"  << std::endl
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        std::cout << argv[0] << ": Version "<< version << std::endl;
        exit (0);
      }

     if (! strcmp((argv[i] + j), "file") || strchr((argv[i] + j), 'f'))
      {
        filename_p = (char *) malloc (strlen(argv[i + 1]) + 1);
        strcpy(filename_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (6, "unknown argument %s", argv[i] );
   }

  if(!filename_p)
   {
     filename_p = const_cast< char * >("sensorConfiguration.xml");
   } /* end of if(!filename_p) */
  
  
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {

      handles_p->init(argc, argv, "QMS_Sensor", ACE_TRY_ENV);
      ACE_TRY_CHECK;
      std::cerr << "DEBUG: initialized corba handles" << std::endl;

      add_handler(signal_handler_p, handles_p, SIGINT);
#if !defined(_WIN32)
      add_handler(signal_handler_p, handles_p, SIGHUP);
#endif
      add_handler(signal_handler_p, handles_p, SIGQUIT);
      add_handler(signal_handler_p, handles_p, SIGABRT);
      add_handler(signal_handler_p, handles_p, SIGUSR1);
      add_handler(signal_handler_p, handles_p, SIGSEGV);
      add_handler(signal_handler_p, handles_p, SIGUSR2);
      add_handler(signal_handler_p, handles_p, SIGPIPE);
      add_handler(signal_handler_p, handles_p, SIGTERM);
      add_handler(signal_handler_p, handles_p, SIGCHLD);
      
      sensor_p->init(handles_p, credentials, filename_p, ACE_TRY_ENV);
      std::cerr << "DEBUG: Initialized the sensor" << std::endl;
      std::cerr << "DEBUG: Starting the loop" << std::endl;
      handles_p->run(ACE_TRY_ENV);	
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,"Caught exception:");
      std::cout << "Cleaning up" << std::endl;
      sensor_p->cleanup();
    }
  ACE_ENDTRY;
  std::cout << "Sensor Done" << std::endl;
  exit(EXIT_SUCCESS);
} /* end of main() */
