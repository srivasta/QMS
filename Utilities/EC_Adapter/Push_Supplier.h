//                              -*- Mode: C++ -*-
// Push_Supplier.h ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Oct 18 14:44:48 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Oct 24 11:39:21 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 81
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: Push_Supplier.h,v 1.11 2001/12/16 01:51:44 srivasta Exp $
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


#ifndef PUSH_SUPPLIER_H
# define PUSH_SUPPLIER_H
/** @file Push_Supplier.h
 *  @ingroup TAOEC
 *  @brief Interface definition of the QMS Supplier class.
 */

#include <string>
#include <exception>
#include <stdexcept>


#include "ace/Synch.h"
#include "ace/Thread.h"

#include "orbsvcs/RtecEventChannelAdminC.h"
#include "orbsvcs/RtecEventCommS.h"
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
    
    /// The event ID for a QMS widedisconnect event
    const RtecEventComm::EventType DEFAULT_PUSH_SUPPLIER_DISCONNECT = 20000;
    
    /** @class Push_Supplier
     *  @ingroup TAOEC
     *
     * Here we create a supplier object to send events to the event
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
     *  The most common usage is to create an Push_Supplier object,
     *  initialize it, passing in a STDC::QMS::CORBA_Handles object, an ID number
     *  that identifies the type of entity that we are (for example, a
     *  Desi entity that sends Remos queries,  or Remos instrumentation
     *  that sends Remos data), as well as the ID of the data type we
     *  shall send over the event channel. This causes the library to
     *  initialize and bind to the ORB, POA, the event channel, and the
     *  scheduler; though no  connections to the event channel are
     *  established at this point.
     *
     *  One is then free to connect to the event channel, and are now
     *  ready to start sending events.
     */
    class Push_Supplier : public POA_RtecEventComm::PushSupplier
    {

    public:

      /// Constructor
      Dllexport Push_Supplier();
      Dllexport Push_Supplier(Push_Supplier & rhs);
      ///  Destructor
      Dllexport ~Push_Supplier();

      /// The = operator
      const Push_Supplier operator=(const Push_Supplier & copy);
  
      /// Where the real intialization happens
      Dllexport void init (STDC::QMS::CORBA_Handles Handles,
			   RtecEventComm::EventType send_event_type,
			   RtecEventComm::EventSourceID my_id,
			   const char * ec_name_p = "QMS_Channel",
			   CORBA_Environment &ACE_TRY_ENV =
			   TAO_default_environment ()
			   );

      /// This is where the payload is sent across packaged in an event.
      Dllexport int send(const string &data,
			 CORBA_Environment &ACE_TRY_ENV =
			 TAO_default_environment ());

      /// Set up as a supplier
      Dllexport void connect(CORBA::Environment & = TAO_default_environment())
	ACE_THROW_SPEC ((CORBA::SystemException));

      /// A method to have us disconnect, called from a management function
      Dllexport void disconnect (long etype =
				 DEFAULT_PUSH_SUPPLIER_DISCONNECT,
				 CORBA::Environment & = TAO_default_environment())
	ACE_THROW_SPEC ((CORBA::SystemException));
      /// Tell the event channel we are going off the air
      Dllexport void disconnect_push_supplier (CORBA::Environment &)
	ACE_THROW_SPEC ((CORBA::SystemException));

      /// Get scheduling information
      Dllexport RtecScheduler::handle_t& get_schedule(void);
      /// set scheduling information
      Dllexport void set_schedule(RtecScheduler::handle_t& schedule);

      /// Get subscription information
      Dllexport ACE_SupplierQOS_Factory& get_subscription(void);
      /// Set subscription information
      Dllexport void set_subscription(ACE_SupplierQOS_Factory& qos);
      /// Get internal corba handles reference
      Dllexport STDC::QMS::CORBA_Handles * get_handles(void);

    private:
      /// A private method invoked to send a disconnect event
      void send_disconnect_event(CORBA::Environment &ACE_TRY_ENV);

      /// Set the default Schedule for this object
      void default_schedule(CORBA_Environment &ACE_TRY_ENV =
			    TAO_default_environment ());

      /// Set a mutex to guard the data
      ACE_Thread_Mutex asset_guard;
      /// Our copy of the CORBA Handles
      STDC::QMS::CORBA_Handles handles;

      // Supplier specific handles stashed away
      RtecEventChannelAdmin::SupplierAdmin_var _supplier_admin;
      /// Handle to the consumer proxy we are connected to
      RtecEventChannelAdmin::ProxyPushConsumer_var _consumer_proxy;

      /// The scheduling information for the event channel scheduling
      RtecScheduler::handle_t rt_info;
      /// Have we been scheduled yet?
      bool Is_Scheduled;
  
      /// The combination of supplier ID's and eventID's to register with
      /// the event channel
      ACE_SupplierQOS_Factory qos;
      bool Is_Subscribed;

      /// The event channel we connect to
      char * ec_name_p;
      
      /// Event ID of the events sent
      RtecEventComm::EventType _send_event_type;
      ///  Event ID of the disconnect event
      RtecEventComm::EventType _disconnect_event_type;
      /// The supplier ID of this object
      RtecEventComm::EventSourceID _my_id;
      /// The name of the event we supply
      char * EventName;
      /// Are we coneected to our prozy?
      bool connected_to_proxy;
    };
  };
};

#endif  //PUSH_SUPPLIER_H
