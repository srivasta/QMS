//                              -*- Mode: C++ -*- 
// hello_world.cpp --- 
// Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
// Created On       : Wed Jul 25 20:46:23 2001
// Created On Node  : ember.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Jun  8 01:09:18 2002
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 107
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


/** @file hello_world.cpp
 *  @ingroup HelloWorld 
 *  @brief Driver for the hello world sensor
 *
 * $Id: hello_world.cpp,v 1.24 2002/06/08 06:25:26 srivasta Exp $
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

#include "Debug.h"

#include "CORBA_Handles.h"
#include "Push_Consumer.h"
#include "Push_Supplier.h"

#include "Hello_World_Impl.h"

/// RCS version string
static const char* version = 
"$Id: hello_world.cpp,v 1.24 2002/06/08 06:25:26 srivasta Exp $";

/// The servant that instantiates the sensor is a global variable
STDC::QMS::Citizen::Hello_World_Impl *sensor_p = 
   new STDC::QMS::Citizen::Hello_World_Impl();

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
  sensor_error_handler(STDC::QMS::Citizen::Hello_World_Impl *sensor_p,
		       STDC::QMS::CORBA_Handles *handles_p):
    sensor_p_(sensor_p), handles_p_(handles_p){};

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
  
  STDC::QMS::Citizen::Hello_World_Impl *sensor_p_;
  
  /// Stash away a pointer to the the CORBA Handles
  STDC::QMS::CORBA_Handles *handles_p_;
  
  /// Stash away the sensor object so we can exit gracefully
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
  cerr << "Received signal" << signum << std::endl;
  this->sensor_p_->cleanup();
  this->handles_p_->get_orb_handle()->shutdown ();
  return 0;
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
  // Create a Generic Sensor object. Perhaps this should be a static,
  // global variable? 
  string credentials;

  
  char *filename_p = 0;
  STDC::QMS::CORBA_Handles *handles_p = new STDC::QMS::CORBA_Handles();
  if(!handles_p)
   {
       cerr << "Error creating corba handles" <<std::endl;
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
        cout << argv[0] << version << endl
             << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
             << endl
             << "\t-h             : This help text"  << endl
             << "\t-v             : Prints out the version"  << endl
             << "\t-file Filename : Read XML data from here"  << endl
             << "\t-f    Filename : Read XML data from here"  << endl
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
        filename_p = (char *) malloc (strlen(argv[i + 1]) + 1);
        strcpy(filename_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (DEBUG_L_ENTER, "unknown argument %s", argv[i] );
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
      cerr << "DEBUG: initialized corba handles" << std::endl;

//       CORBA::ORB_var my_orb = handles_p->get_orb_handle();
//       TAO_ORB_Core *orb_core_p = my_orb->orb_core();
//       ACE_Reactor *reactor_p = orb_core_p->reactor();
//       int ret = reactor_p->register_handler(SIGINT, signal_handler_p);
      
      if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler(SIGINT, signal_handler_p) == -1)
       {
	 cerr << "Error:register_handler for SIGINT" << std::endl;
	 if(handles_p)
	  {
	    delete handles_p;
	    handles_p = 0;
	  } /* end of if(handles_p) */
	 exit (EXIT_FAILURE);
       }
#if !defined(_WIN32)
      if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler(SIGHUP, signal_handler_p) == -1)
       {
	 cerr << "Error:register_handler for SIGHUP" << std::endl;
	 if(handles_p)
	  {
	    delete handles_p;
	    handles_p = 0;
	  } /* end of if(handles_p) */
	 exit (EXIT_FAILURE);
       }
#endif
      if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler(SIGABRT, signal_handler_p) == -1)
       {
	 cerr << "Error:register_handler for SIGABRT" << std::endl;
	 if(handles_p)
	  {
	    delete handles_p;
	    handles_p = 0;
	  } /* end of if(handles_p) */
	 exit (EXIT_FAILURE);
       }
      if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler(SIGTERM, signal_handler_p) == -1)
       {
	 cerr << "Error:register_handler for SIGTERM" << std::endl;

	 if(handles_p)
	  {
	    delete handles_p;
	    handles_p = 0;
	  } /* end of if(handles_p) */
	 exit (EXIT_FAILURE);
       }
      const char* env_var_p = getenv("SENSOR_CRITICALITY");
      const char* criticality_p = "VERY_HIGH";
      if(env_var_p)
       {
	 if(!strcmp("VERY_HIGH", env_var_p))   	 criticality_p = "VERY_HIGH";
	 else if(!strcmp("HIGH", env_var_p))   	 criticality_p = "HIGH";
	 else if(!strcmp("MEDIUM", env_var_p)) 	 criticality_p = "MEDIUM";
	 else if(!strcmp("LOW", env_var_p))    	 criticality_p = "LOW";
	 else if(!strcmp("VERY_LOW", env_var_p)) criticality_p = "VERY_LOW"; 
         else    	   	   	   	 criticality_p = "VERY_HIGH";
       } 

      env_var_p = getenv("SENSOR_IMPORTANCE");
      const char* importance_p = "MEDIUM";
      if(env_var_p)
       {
	 if(!strcmp("VERY_HIGH", env_var_p))   	 importance_p = "VERY_HIGH";
	 else if(!strcmp("HIGH", env_var_p))   	 importance_p = "HIGH";
	 else if(!strcmp("MEDIUM", env_var_p)) 	 importance_p = "MEDIUM";
	 else if(!strcmp("LOW", env_var_p))    	 importance_p = "LOW";
	 else if(!strcmp("VERY_LOW", env_var_p)) importance_p = "VERY_LOW"; 
         else    	   	   	   	 importance_p = "MEDIUM";
       } 
      
      sensor_p->init(handles_p, credentials, filename_p, 
		     criticality_p, importance_p, ACE_TRY_ENV);
      cerr << "DEBUG: Initialized the sensor" << std::endl;
      cerr << "DEBUG: Starting the loop" << std::endl;
      handles_p->run(ACE_TRY_ENV);	
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,"Caught exception:");
      cout << "Cleaning up" << endl;
      sensor_p->cleanup();
      cout << "Sensor Done" << endl;
      exit(EXIT_FAILURE);
    }
  ACE_ENDTRY;
  cout << "Sensor Done" << endl;
  exit(EXIT_SUCCESS);
} /* end of main() */
