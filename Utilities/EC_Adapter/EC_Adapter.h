//                              -*- Mode: C++ -*-
// EC_Adapter.h ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Oct 18 13:59:39 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Oct 24 11:37:16 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 168
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: EC_Adapter.h,v 1.12 2001/12/02 03:30:27 srivasta Exp $
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


#ifndef EC_ADAPTER_H
# define  EC_ADAPTER_H
/** @file EC_Adapter.h
 *  @ingroup TAOEC
 *  @brief Interface definition for the QMS API
 *
 */

#include <vector>

#include "ace/Synch.h"
#include "ace/Thread.h"


#include "orbsvcs/CosNamingC.h"
#include "orbsvcs/Event_Utilities.h"

//#include "QMS_Debug.h"
#include "Debug.h"
#include "CORBA_Handles.h"
#include "Push_Consumer.h"
#include "Push_Supplier.h"


/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

using namespace std;
namespace STDC
{
  namespace QMS
  {
    /** @class EC_Adapter
     *  @ingroup TAOEC
     *  @brief This is the main entry point for the QMS API for clients
     *
     * This API is general enough to allow for simultaneous instantiations
     * of suppliers and consumers.  This API should handle most of the
     * intricacies of setting up the CORBA connection, error handling, and
     * safe disconnects for the client code.
     *
     *  The files test_desi.cpp and test_remos.cpp provide examples of
     *  usage. The most common usage is to create an EC_Adapter object,
     *  initialize it, passing in the command line argumets to allow
     *  configuration of the ORB at run time, an ID number that identifies
     *  the type of entity that we are (for example, a Desi entity that
     *  generates queries and consumes Remos data, or Remos
     *  instrumentation that consumes queries and creates data
     *  events). This causes the library to initialize and bind to the
     *  ORB, POA, the event channel, and the scheduler; though no
     *  connections to the event channel are established at this point.
     *
     *  Following initialization, one should register a call back function
     *  to call when the consumer instance recieves event data, specifying
     *  any additional arguments to that function as needed.
     *
     *  One is then free to connect the supplier, and the consumer, and
     *  finally start listening for events. Please note that the listen
     *  call does not normally return until we are done.
     *
     *  Disconnecting cleanly from the event channel in case of errors is
     *  of concern, and an attempt has been made to err on the side of
     *  caution here.
     *
     *  There are variants of some calls to be used when more control is
     *  desired than is provided by the common usage.  There are
     *  provisions to have an unlimited number of Push_consumer push
     *  consumers, and/or Push_Supplier push suppliers, with full control
     *  over scheduling and subscription options
     */
    class EC_Adapter
    {
    public:
      /**
       *  @brief default constructor
       */
      Dllexport  EC_Adapter ();
      // copy constructor
      Dllexport  EC_Adapter (EC_Adapter & rhs);
      Dllexport  ~EC_Adapter ();

      /// The = operator
      const EC_Adapter operator=(EC_Adapter & copy);
  
      /**
       *   @brief Register a call back to be called when the data arrives.
       */
      Dllexport  int register_callback (void (*callback)(const string &data,
							 void *arg_p),
					void * arg_p = 0,
					unsigned int which_consumer = 0
					);


      /**
       *   @brief Used by the supplier to send data to the event channel.
       */
      Dllexport  int send (const string &data,
			   unsigned int which_supplier = 0);

      /**
       *   @brief The main initialization and configuration entry point
       *  
       *   This comes n two overloaded forms, one bring the simple
       *   interface, and ther allowing for maximum flexibility
       */
      Dllexport  void init (int argc, char **argv,
			    RtecEventComm::EventSourceID my_id,
			    RtecEventComm::EventType send_event = 0,
			    RtecEventComm::EventType get_event  = 0,
			    char * event_channel_name_p = "QMS_Channel",
			    STDC::QMS::CORBA_Handles *handle_p = 0,
			    CORBA_Environment &ACE_TRY_ENV =
			    TAO_default_environment ()
			    )
	ACE_THROW_SPEC ((CORBA::SystemException));

      Dllexport  void init (int argc, char **argv,
			    CORBA_Environment &ACE_TRY_ENV =
			    TAO_default_environment ())
	ACE_THROW_SPEC ((CORBA::SystemException));

      /**
       *  @brief Add a new supplier object
       */
      Dllexport  STDC::QMS::Push_Supplier *
      add_supplier  (int &slot_num,
		     char * event_channel_name_p,
		     RtecEventComm::EventSourceID my_id  = 0,
		     RtecEventComm::EventType send_event = 0
		     );
  
      /**
       *  @brief Add a new consumer object
       */
      Dllexport  STDC::QMS::Push_Consumer *
      add_consumer(int &slot_num,
		   char * event_channel_name_p,
		   RtecEventComm::EventType get_event  = 0
		   );

      /**
       *  @brief Add a new supplier object
       */
      Dllexport  STDC::QMS::Push_Supplier * add_supplier  (int &slot_num);
  
      /**
       *  @brief Add a new consumer object
       */
      Dllexport  STDC::QMS::Push_Consumer * add_consumer(int &slot_num);

      /**
       *   @brief  Connect a push supplier to the event channel.
       */
      // Actually sending the event happens by using the send event
      Dllexport  int connect_supplier(unsigned int which_supplier = 0,
				      CORBA_Environment &ACE_TRY_ENV =
				      TAO_default_environment ());

      /**
       *   @brief Connect a push consumer to the event channel..
       */
      Dllexport  int connect_consumer(unsigned int which_consumer = 0,
				      CORBA_Environment &ACE_TRY_ENV =
				      TAO_default_environment ());


      // Safely disconnecting from the event channel is quite important,
      // espescially if the performance and teh response time of the event
      // channel are not to be impacted.

      /**
       *   @brief Disconnects both the consumer and the supplier
       */
      // The consumer goes down first, since it  sends a disconnect event
      Dllexport  void disconnect(void);

      /**
       *   @brief  Disconnect the consumer object. Sends a disconnect event
       */
      Dllexport  int disconnect_consumer(unsigned int which_consumer = 0,
					 CORBA_Environment &ACE_TRY_ENV =
					 TAO_default_environment ());

      /**
       *   @brief Disconnect the Supplier Object
       */
      // Should not be called before the consumer is disconnected
      Dllexport  int disconnect_supplier(unsigned int which_supplier = 0,
					 CORBA_Environment &ACE_TRY_ENV =
					 TAO_default_environment ());

      /**
       *   @brief  Enters into an event loop listening for events.
       */
      // The CORBA spec mentions that access to the main thread needs to
      // be provided; and this generally all other tasks that one needs to
      // do should delegated to threads spawned off
      Dllexport  int listen(void);

      /// Get a pointer to a specific consumer object
      Dllexport  int get_consumer(STDC::QMS::Push_Consumer *&consumer_p, 
				  unsigned int which_consumer = 0);
  
      /// Get a pointer to a specific supplier object
      Dllexport  int get_supplier(STDC::QMS::Push_Supplier *&supplier_p,
				  unsigned int which_supplier = 0);
  
      /// Get a pointer to the list of consumer elements
      Dllexport std::vector<STDC::QMS::Push_Consumer *> *
      get_consumer_list(void);
      /// Get a pointer to the list of supplier elements
      Dllexport std::vector<STDC::QMS::Push_Supplier *> *
      get_supplier_list(void);

      Dllexport STDC::QMS::CORBA_Handles *get_handles(void);
      
    private:
      int argc;
      char **argv;
      bool Simple_mode;
  
      /// Set a mutex to guard the data
      ACE_Thread_Mutex asset_guard;


      /** Stash data here that is used by the consumer and supplier
       * objects
       */

      /// @var EC_Adapter::send_event_type Event type we send
      RtecEventComm::EventType send_event_type;
      /// Event type we get
      RtecEventComm::EventType get_event_type;
      /// Supplier Id for sending
      RtecEventComm::EventSourceID my_id;


      STDC::QMS::CORBA_Handles handles;
      bool i_own_handles;
      
      /// The event channel name
      char *EC_Name;

      /// The object instantiating the supplier interface
      std::vector<STDC::QMS::Push_Consumer *> Consumers;

      /// The object instantiating the consumer interface
      std::vector<STDC::QMS::Push_Supplier *> Suppliers;

      /// useful constants
      const RtecEventComm::EventType DEFAULT_SEND_TYPE;
      const RtecEventComm::EventType DEFAULT_GET_TYPE;
      const RtecEventComm::EventSourceID DEFAULT_ID;
    };
  };
};


#endif //  EC_ADAPTER_H
