//                              -*- Mode: C++ -*- 
// CORBA_Handles.h --- 
// Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
// Created On       : Sat Aug 11 18:12:59 2001
// Created On Node  : ember.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Mon Oct 22 13:51:02 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 15
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


/** @file CORBA_Handles.h
 *  @ingroup Utilities
 *  @brief A Convenience class to deal with CORBA handles
 */


#ifndef _CORBA_HANDLES_H_
#define _CORBA_HANDLES_H_

#include <tao/corba.h>
#include <tao/Adapter.h>
#include <tao/PortableServer/PortableServer.h>
#include <orbsvcs/CosNamingC.h>
#include <orbsvcs/Runtime_Scheduler.h>
#include <orbsvcs/CosNamingC.h>
#include <orbsvcs/Event_Utilities.h>

/// Headers required for returning ptr to trading service lookup interface.
#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"
#include "orbsvcs/CosTradingDynamicC.h"
#include "orbsvcs/Event_Utilities.h"


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

      /** A global QMS event type for a disconnect message */
      static const RtecEventComm::EventType QMS_DISCONNECT        = 10000;
      /**  A event type for a supplier disconnect message */
      static const RtecEventComm::EventType SUPPLIER_DISCONNECT   = 20000;

      /** sleep interval in seconds */
      static const long QMS_DEFAULT_retry_sleep_interval = 60; /// in
							 /// seconds
      /** Num ber of retries */
      static const int  QMS_DEFAULT_number_of_retries     = 3;

      /** @class CORBA_Handles
       *  @ingroup Utilities
       *  @brief A convenience class for getting handles for CORBA objects
       *
       *  This class is used as an abstraction for the details of getting
       *  hold of CORBA entities that one needs to set up connections to the
       *  ORB. Any ORB specific idiosyncracies should be dealt with
       *  here. The methods are very conscientous in checking return status,
       *  and handling exceptions
       *
       *  The file QMS_Api.cpp shows example usa for this class. This class has
       *  been split out from that file as a convenience to other code that
       *  may need to set up a CORBA interface independently.
       *
       *  The most common usage is to create an CORBA_Handles object,
       *  initialize it, passing in the command line argumets to allow
       *  configuration of the ORB at run time, and pass in an event channel
       *  name to get a handle for. Subsequently, any of the convenience
       *  functions can be used to get access to the handles stashed away
       *  internally.
       *
       *  Refrences to the following entities are stored:
       *   - The orb itself
       *   - The portable object adapter
       *   - The portable object adapter manager
       *   - The naming service
       *   - The scheduling service
       *   - The event channel itself
       */
      class CORBA_Handles
      {
      public:
	/// default constructor
	Dllexport CORBA_Handles (CORBA::ORB_ptr orb = 0,
				 PortableServer::POA_ptr poa = 0,
				 PortableServer::POAManager_ptr poa_manager
				 = 0);
	/// default destructor
	Dllexport ~CORBA_Handles ();
	
	/// Initialize the ORB/root POA, using the supplied command line
	/// arguments or the default ORB components.  
	Dllexport void init (int argc, char **argv, 
			     const char * orb_name_p  = "QMS_API",
			     CORBA_Environment &ACE_TRY_ENV = 
			     TAO_default_environment ());
	
	/// Creates a child poa under the root poa with PERSISTENT and
	/// USER_ID policies.  Call this if you want a <child_poa> with the
	/// above policies, otherwise call init.  
	Dllexport void init_child_poa (int &argc,
				       char *argv[],
				       const char *poa_name,
				       const char *orb_name  = "QMS_API",
				       CORBA_Environment &ACE_TRY_ENV =
				       TAO_default_environment ());
	
	/// Create a dynamic EC handle
	Dllexport void get_event_channel 
	(const char * event_channel_name_p,
	 RtecEventChannelAdmin::EventChannel_var& event_channel,
	 CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ());
	
	/// Activate the POA manager. Put POA manager into the <Active>
	/// state, so that incoming corba requests are processed.  This
	/// method is useful for clients, which are not going to enter
	/// "orb->run" loop, yet may want to service incoming requests while
	/// waiting for a result of CORBA call on a server.  Returns -1 on
	/// failure. 
	Dllexport void 
	activate_poa_manager(CORBA_Environment &ACE_TRY_ENV =
			     TAO_default_environment ());
	
	/// Activate <servant>, using the POA <activate_object> call.  Users
	/// can call this method multiple times to activate multiple objects.
	/// Returns 0 on failure.
	Dllexport PortableServer::ObjectId_var
	activate (PortableServer::Servant servant, CORBA_Environment
		  &ACE_TRY_ENV = TAO_default_environment ());
	
	/// Deactivate object in RootPOA.
	Dllexport  void deactivate (const char *id,
				    CORBA_Environment &ACE_TRY_ENV =
				    TAO_default_environment ());
	
	
	/// Precondition: init_child_poa has been called.  Activate <servant>
	/// using the POA <activate_object_with_id> created from the string
	/// <object_name>. Users should call this to activate objects under
	/// the child_poa.
	Dllexport char *
	activate_under_child_poa (const char *object_name,
				  PortableServer::Servant servant,
				  CORBA_Environment &ACE_TRY_ENV =
				  TAO_default_environment ());
	
	/// Deactivate object in child POA.
	Dllexport void 
	deactivate_under_child_poa (const char *id,
				    CORBA_Environment &ACE_TRY_ENV =
				    TAO_default_environment ());
	
	
	
	
	/// Start listening
	Dllexport void run(CORBA_Environment &ACE_TRY_ENV = 
			   TAO_default_environment ());
	
	/// Get a handle for the @em ORB
	/// Accessor which returns the ORB pointer.  Following the normal
	/// CORBA memory management rules of return values from functions,
	/// this function duplicates the orb return value before returning
	/// it.
	Dllexport CORBA::ORB_var          get_orb_handle(void) const;
	
	/// Get a handle for the @em portable object adapter
	/// Accessor which returns the root poa. Following the normal CORBA
	/// memory management rules of return values from functions, this
	/// function duplicates the poa return value before returning it.
	Dllexport PortableServer::POA_var get_root_poa_handle(void) const;
	Dllexport PortableServer::POA_var get_poa_handle(void) const;

	/// Get a handle for the @em POA Manager
	Dllexport PortableServer::POAManager_var 
	get_poa_mgr_handle(void) const;

	/// Get a handle for the @em Naming service
	Dllexport CosNaming::NamingContext_var get_naming_handle(void) const;
	
	/// Get a handle for the @em Scheduler
	Dllexport RtecScheduler::Scheduler_var 
	get_scheduler_handle(void) const;

	/// Get a handle for the @em Event Channel
	Dllexport RtecEventChannelAdmin::EventChannel_var 
	get_ec_handle(void) const;

	/// Finished with the handles
	Dllexport void fini(CORBA_Environment &ACE_TRY_ENV = 
			    TAO_default_environment ());
  
	/// Disconnect and recover resources allocated
	Dllexport void disconnect(CORBA_Environment &ACE_TRY_ENV = 
				  TAO_default_environment ());
	
	/// return an pointer to the lookup interface
	Dllexport CosTrading::Lookup_var 
	get_lookup_handle(CORBA_Environment &ACE_TRY_ENV =
			  TAO_default_environment ());
  
	/// DEPRECATED: Initialize the  event channel 
	Dllexport void add_event_channel (const char * event_channel_name_p,
					  CORBA_Environment &ACE_TRY_ENV =
					  TAO_default_environment ());
	/// DEPRECATED:  Delete the event channel handle in this object
	Dllexport void delete_event_channel (void);

      private:
	
	/// Stash the orb, once we get it
	CORBA::ORB_var _orb;
	/// while we are at it, we also stash away the POA reference
	PortableServer::POA_var _root_poa;
	
	/// Child poa under the root POA.
	PortableServer::POA_var _child_poa;
	
	/// As well as the pointer to the manager
	PortableServer::POAManager_var _poa_manager;
	///  Reference to the naming service
	CosNaming::NamingContext_var _naming_context;
	/// The scheduling service
	RtecScheduler::Scheduler_var _scheduler;
	/// And finally the event channel itself
	RtecEventChannelAdmin::EventChannel_var _event_channel;
	
	/// We also provide (optionally) an interface to the trading
	/// service:
	/// Lookup interface
	CosTrading::Lookup_var  _lookup_var;
	
	/// Well, the event channel name
	char *EC_Name;

	/// Have we been initialized?
	bool _initialized;
	/// Has to root poa manager been activated
	bool _poa_activated;
	
      };
    };
};

#endif /* _CORBA_HANDLES_H_ */
