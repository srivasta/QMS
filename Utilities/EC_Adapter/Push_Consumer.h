//                              -*- Mode: C++ -*-
// Push_Consumer.h ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Oct 18 14:41:32 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Oct 24 11:38:44 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 92
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: Push_Consumer.h,v 1.12 2002/02/15 17:08:06 srivasta Exp $
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


#ifndef _PUSH_CONSUMER_H
#define _PUSH_CONSUMER_H

/** @file Push_Consumer.h
 *  @ingroup TAOEC
 *  @brief Implentation of the Consumer object class
 *
 */


#include <string>
#include <exception>
#include <stdexcept>

#include "ace/Synch.h"
#include "ace/Thread.h"

#include "orbsvcs/orbsvcs/Runtime_Scheduler.h"
#include "orbsvcs/RtecEventChannelAdminS.h"
#include "orbsvcs/CosNamingC.h"
#include "CORBA_Handles.h"


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
    

    /** @class Push_Consumer
     *  @ingroup TAOEC
     *
     * Here we create a consumer object to recieve events from the event
     * channel. This shall be used on either end of the QMS channel. We
     * use the real time TAO event channel, and ACE exception wrapper
     * macros.
     *
     * The file QMS_Api.cpp should provide an example of usage for this
     * class. For the most part, it is expected that client code shall not
     * instantiate objects of this class directly, but shall create
     * QMS_Api objects that contain an instance of this class. However, in
     * some unusual cases, it may be necesary to create objects of this
     * class directly (for instance, if an application needs more than one
     * consumer or supplier object at a time).
     *
     *  The most common usage is to create an Push_Consumer object,
     *  initialize it, passing in a QMS_CORBA_Handles object,
     *  an ID number that identifies the kind of data we are interested in
     *  consuming. This causes the library to initialize and bind to the
     *  ORB, POA, the event channel, and the scheduler; though no
     *  connections to the event channel are established at this point.
     *
     *  Following initialization, one should register a call back function
     *  to call when the we get event data, specifying any additional
     *  arguments to that function as needed.
     *
     *  One is then free to connect to the event channel, and finally
     *  start listening for events. Please note that the listen
     *  call does not normally return until we are done.
     *
     *  Disconnecting cleanly from the event channel in case of errors is
     *  of concern, and an attempt has been made to err on the side of
     *  caution here.
     */
    class Push_Consumer : public POA_RtecEventComm::PushConsumer
    {

    public:
      /// Constructor
      Dllexport  Push_Consumer();
      /// Copy Constructor
      Dllexport  Push_Consumer(const Push_Consumer & rhs);
      /// Destructor
      Dllexport  ~Push_Consumer();

      /// The = operator
      Dllexport  const Push_Consumer operator=(const Push_Consumer & copy);
  

      /// Where the real intialization happens
      Dllexport  void init (STDC::QMS::CORBA_Handles Handle,
			    RtecEventComm::EventType get_event_type,
			    const char * ec_name_p = "QMS_Channel",
			    CORBA_Environment &ACE_TRY_ENV =
			    TAO_default_environment ()
			    );

      /* This is a required part of the interface. This is the function
       * that the event channel calls when there is an event for us to
       * consumer
       */
      /// Called when an event is available (required part of the interface)
      Dllexport  void push (const RtecEventComm::EventSet &,
			    CORBA::Environment & = TAO_default_environment())
	ACE_THROW_SPEC ((CORBA::SystemException));

      /// Set up as a comsumer
      Dllexport  void connect(CORBA::Environment & = TAO_default_environment())
	ACE_THROW_SPEC ((CORBA::SystemException));
      /// A method to have us disconnect
      Dllexport void disconnect (CORBA::Environment & = 
				 TAO_default_environment())
	ACE_THROW_SPEC ((CORBA::SystemException));
      /// Tell the event channel we are going off the air
      Dllexport void disconnect_push_consumer (CORBA::Environment &)
	ACE_THROW_SPEC ((CORBA::SystemException));

      /// Get scheduling information
      Dllexport RtecScheduler::handle_t& get_schedule(void);
      /// set scheduling information
      Dllexport void set_schedule(RtecScheduler::handle_t& schedule);

      /// Get subscription information
      Dllexport ACE_ConsumerQOS_Factory& get_subscription(void);
      /// Set subscription information
      Dllexport void set_subscription(ACE_ConsumerQOS_Factory& qos);
  


      /// Callback function (all the marshalling happens outside QMS)
      Dllexport void register_callback (void (*callback)(const string &data,
							 void *arg_p),
					void *arg_p = 0);
      /// Get a referece to our internal CORBA Handles stash
      Dllexport  STDC::QMS::CORBA_Handles *get_handles(void);

    private:
      /// Set the default Schedule for this object
      void default_schedule(CORBA_Environment &ACE_TRY_ENV =
			    TAO_default_environment ());

      /// Set a mutex to guard the data
      ACE_Thread_Mutex asset_guard;
      /// Our copy of the CORBA Handles
      STDC::QMS::CORBA_Handles handles;
      /// Are we coneected to our prozy?
      bool connected_to_proxy;

      /// The event channel we connect to
      char * ec_name_p;
      
      /// The event type we subscribe to
      RtecEventComm::EventType _get_event_type;
      /// The name of the event we supply
      char * EventName;

      /// Consumer specific handles stashed away
      RtecEventChannelAdmin::ConsumerAdmin_var _consumer_admin;
      /// handle for the supplier proxy we are connected to
      RtecEventChannelAdmin::ProxyPushSupplier_var _supplier_proxy;

      /// The scheduling information for the event channel scheduling
      RtecScheduler::handle_t rt_info;
      /// Have we been scheduled yet?
      bool Is_Scheduled;
  
      /// The combination of supplier ID's and eventID's to register with
      /// the event channel
      ACE_ConsumerQOS_Factory qos;
      /// Have we subscribed to the event channel?
      bool Is_Subscribed;


      /// Function pointer to the data callback function
      void (*callback)(const string &data, void *arg_p);
      /// optional argument for the callback
      void *arg_p;
    };    
  };
};


#endif  // _PUSH_CONSUMER_H
