//                              -*- Mode: C++ -*-
// Push_Supplier.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Oct 18 16:37:52 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu Dec  6 13:31:44 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 136
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: Push_Supplier.cpp,v 1.18 2002/02/28 21:02:53 srivasta Exp $
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
static const char* version = 
"$Id: Push_Supplier.cpp,v 1.18 2002/02/28 21:02:53 srivasta Exp $";

/** @file Push_Supplier.cpp
 *  @ingroup TAOEC
 *  @brief Implentation of the Push Supplier class
 *
 *  This is the main implementation for the class.
 */

#include "orbsvcs/Time_Utilities.h"
#include "orbsvcs/Event_Utilities.h"

#include "Push_Supplier.h"
#include "Debug.h"

#if defined (_WIN32) /* Only Win32 needs special treatment. */
static const int  QMS_DEFAULT_number_of_retries     = 3;
static const RtecEventComm::EventType SUPPLIER_DISCONNECT   = 20000;
static const long QMS_DEFAULT_retry_sleep_interval = 60;
#endif

/**
 *  @brief  Constructor
 *
 * Sets up internal variables to a sane default state. The object
 * still needs to be initialized to be useful.
 */
STDC::QMS::Push_Supplier::Push_Supplier(void) :
  Is_Scheduled(false), Is_Subscribed(false), ec_name_p(0), 
  _send_event_type(9999),_disconnect_event_type(9999), _my_id(17), 
  EventName(0), connected_to_proxy(false)
{
  QMS_Trace ("STDC::QMS::Push_Supplier::Push_Supplier", __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG: New  Supplier object\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  this->connected_to_proxy = false;
}
/**
 * @overload
 */

STDC::QMS::Push_Supplier::Push_Supplier(Push_Supplier & rhs):
  POA_RtecEventComm::PushSupplier(),
  handles (rhs. handles),
  _supplier_admin (rhs._supplier_admin),
  _consumer_proxy (rhs._consumer_proxy),
  rt_info (rhs. rt_info),
  Is_Scheduled (rhs. Is_Scheduled),
  qos (rhs. qos),
  Is_Subscribed (rhs. Is_Subscribed),
  _send_event_type (rhs._send_event_type),
  _disconnect_event_type (rhs._disconnect_event_type),
  _my_id (rhs._my_id),
  connected_to_proxy (rhs. connected_to_proxy)
{
  QMS_Trace ("STDC::QMS::Push_Supplier::Push_Supplier", __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG: New  Supplier object\n");
  this->EventName              = CORBA::string_dup(rhs.EventName);
}

/**
 * @brief The = operator
 *
 * This avoids self assignements, but does not make anny attempt to
 * disconnect before the copy. It is the callers responsibility to
   ensure that the consumer object is disconnected.
 */
const STDC::QMS::Push_Supplier 
STDC::QMS::Push_Supplier::operator=(const Push_Supplier & copy)
{
  QMS_Trace ("QMS_Consumer::operator =", __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG: copy object\n");
  if(&copy != this)
   {  
     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

     this->handles          	    = copy.handles;
     this->_supplier_admin  	    = copy._supplier_admin;
     this->_consumer_proxy  	    = copy._consumer_proxy;
     this->rt_info          	    = copy.rt_info;
     this->Is_Scheduled     	    = copy.Is_Scheduled;
     this->qos              	    = copy.qos;
     this->Is_Subscribed    	    = copy.Is_Subscribed;
     this->_send_event_type 	    = copy._send_event_type;
     this->_my_id                 = copy._my_id;
     this->EventName              = CORBA::string_dup(copy.EventName);
     this->connected_to_proxy     = copy.connected_to_proxy;
   } /* end of if(&copy != this) */
  return *this;			// enable cascaded assignments
}
/**
 * @brief Destructor
 */

STDC::QMS::Push_Supplier::~Push_Supplier()
{
  CORBA::string_free(this->EventName);
}


/**
 *  @brief Initialization
 *  @param Handles A set of CORBA references and handles required to set up
 *  @param send_event_type The type of event we shall send out
 *  @param  my_id The supplier ID we shall use for that event
 *
 * This is where the real intialization happens. Well, really, most of
 * it has already happened in the caller, we just stash the
 * information locally.
 */
void
STDC::QMS::Push_Supplier::init (STDC::QMS::CORBA_Handles Handles,
				RtecEventComm::EventType send_event_type,
				RtecEventComm::EventSourceID my_id,
				const char * ec_name_p,
				CORBA_Environment &ACE_TRY_ENV
				)
{
  QMS_Trace ("STDC::QMS::Push_Supplier::init", __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG:  Supplier object initializing\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  this->handles          = Handles;
  this->_send_event_type = send_event_type;
  this->_my_id           = my_id;
  this->EventName        = CORBA::string_dup("Send QMS Message");
  this->Is_Scheduled     = false;
  this->Is_Subscribed    = false;
  this->ec_name_p        = CORBA::string_dup (ec_name_p);

  ACE_TRY
    {
      this->rt_info = 
	this->handles.get_scheduler_handle()->create (this->EventName,
						      ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0 (4, "DEBUG: Create a supplier rt info\n"); 
      this->default_schedule();
      this->qos.insert (this->_my_id,	          // source id
			this->_send_event_type, // event type
			this->rt_info,          // handle to the rt info
			1);	// number of calls???
      this->Is_Subscribed    = true;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception supplier::init initializing supplier:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception supplier::init initializing supplier:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}



/**
 *  @brief send event
 *  @param data string to be sent
 *  @return int
 *
 * This is where the payload is sent across packaged in an event. We
 *   - create an event set for one event, initialize event header.
 *   - create the event
 *   - send it across
 */
int
STDC::QMS::Push_Supplier::send(const string &data,
			       CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::Push_Supplier::send", __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG:  Supplier object sending message\n");

  ACE_TRY
    {
      // Create an event set for one event, initialize event header.
      RtecEventComm::EventSet event (1);
      event.length (1);
      event[0].header.type   = this->_send_event_type;
      event[0].header.source = this->_my_id;
      event[0].header.ttl    = 1;
      DEBUG0 (4, "DEBUG create dataset\n");
      DEBUG1 (4, "DEBUG Sending Event: %d\n",
	      this->_send_event_type);

      DEBUG1 (4, "DEBUG With ID: %d\n",
	      this->_my_id);

      // Set up time stamps in event header.  This is for performance
      // measurements, so this step can be omitted at will.
      //   ACE_hrtime_t t = ACE_OS::gethrtime ();
      //   ORBSVCS_Time::hrtime_to_TimeT (event[0].header.creation_time, t);
      //   event[0].header.ec_recv_time = ORBSVCS_Time::zero;
      //   event[0].header.ec_send_time = ORBSVCS_Time::zero;

      // Set up message block for event data.
      ACE_Message_Block mb (data.size() + 1);
      // This takes care of positioning the wr_ptr automatically
      char * temp_p = (char *) data.data();
      temp_p[data.size()] = 0;

      mb.copy(temp_p, data.size());
      DEBUG0 (4, "DEBUG Copy data\n");

      // We use replace to minimize the copies, this should result
      // in just one memory allocation;
      event[0].data.payload.replace(data.size(),&mb);


      {
	ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
	DEBUG0 (4, "DEBUG pushing event\n");
	this->_consumer_proxy->push (event, ACE_TRY_ENV);
      }
      ACE_TRY_CHECK;

      // mb.release();
      DEBUG0 (4, "DEBUG done sending\n");
    }
  ACE_CATCH (CORBA::SystemException, sys_ex)
    {
      ACE_PRINT_EXCEPTION (sys_ex, "SYS_EX during send");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "NON SYS EX during send");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;


  return 0;
}
/**
 * @brief Get scheduling information
 * @return The current scheduling information set
 */
RtecScheduler::handle_t&
STDC::QMS::Push_Supplier::get_schedule(void)
{
  return this->rt_info;
}

/**
 * @brief Set scheduling information
 * @param schedule the scheduling parameters to set for this object
 */
void
STDC::QMS::Push_Supplier::set_schedule(RtecScheduler::handle_t& schedule)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  this->rt_info = schedule;
  this->Is_Scheduled = true;
}

/**
 * @brief Get subscription information
 * @return The current subscription information set
 */
ACE_SupplierQOS_Factory&
STDC::QMS::Push_Supplier::get_subscription(void)
{
  return this->qos;
}

/**
 * @brief Set subscription information
 * @param qos the new subsciption informati0on for this object
 */
void
STDC::QMS::Push_Supplier::set_subscription(ACE_SupplierQOS_Factory& qos)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  this->qos = qos;
  this->Is_Subscribed = true;
}

/**
 * @brief Set up a default scheduling policy for(this object.)
 * 
 *  The execution times are set to reasonable values, but actually
 *  they are changed on the real execution, i.e. we lie to the
 *  scheduler to obtain right priorities; but we don't care if the set
 *  is schedulable. Let us say the execution time for this is 5 milliseconds
 */
void
STDC::QMS::Push_Supplier::default_schedule(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::Push_Supplier::default_schedule", __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG:  Setting a default Schedule\n");

  // No need for a guard element here, since this is a provate
  // function called only by protected members


  ACE_TRY
    {
      ACE_Time_Value tv (0, 5000);
      TimeBase::TimeT time;
      ORBSVCS_Time::Time_Value_to_TimeT (time, tv);
      RtecScheduler::Period_t rate = ACE_U64_TO_U32(time);
      
      DEBUG0 (4, "set the scheduler information\n");
	  DEBUG0 (4, "DEBUG: set the scheduler information\n");
      this->handles.get_scheduler_handle()->set 
	(this->rt_info,
	 RtecScheduler::VERY_HIGH_CRITICALITY,
	 0, 0, 0,
	 rate,
	 RtecScheduler::MEDIUM_IMPORTANCE,
	 0,
	 1,
	 RtecScheduler::OPERATION,
	 ACE_TRY_ENV);
      ACE_TRY_CHECK;
      this->Is_Scheduled = true;
    }
  ACE_CATCH (CORBA::SystemException, sys_ex)
    {
      ACE_PRINT_EXCEPTION (sys_ex, "SYS_EX setting the schedule");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "NON SYS EX setting the schedule");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}


/**
 *  @brief Connect to the event channel as a supplier
 *  @param ACE_TRY_ENV The ACE exception handling var
 *  @exception CORBA::SystemException
 *
 * This is where the bulk of the configuration occurs. This is where
 * the  admin object is created and the event channel connection is
 * set up 
 */
void
STDC::QMS::Push_Supplier::connect(CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace ("STDC::QMS::Push_Supplier::connect", __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG:  Supplier object connecting\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);


  ACE_TRY
    {
      if(this->Is_Scheduled == false)
       {
	 this->default_schedule();
       } /* end of if(this->Is_Scheduled == false) */

      DEBUG2 (4, "DEBUG: My id = %d send event type = %d\n",
	      this->_my_id,  this->_send_event_type);

      if (CORBA::is_nil (this->_supplier_admin.in ()))
       {
	 // We need to get a supplier admin object from the event channel
	 // The canonical protocol to connect to the EC
	 RtecEventChannelAdmin::EventChannel_var event_channel_var;
	 this->handles.get_event_channel(this->ec_name_p, event_channel_var,
					 ACE_TRY_ENV);
	 RtecEventChannelAdmin::EventChannel_ptr event_channel = 
	   event_channel_var.in();
	
	 this->_supplier_admin = event_channel->for_suppliers (ACE_TRY_ENV);
	 ACE_TRY_CHECK;
	 int count = 0;
	 while (CORBA::is_nil (this->_supplier_admin.in ()))
	  {
	    ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
	    ACE_ERROR ((LM_ERROR,"(%P|%t) Unable to get the admin object.\n"));
	    if(count >= 4)
	     {
	       throw std::runtime_error::runtime_error("Unable to get the admin object.");
	     } /* end of if(count >= 4) */
	  
	    ACE_OS::sleep (sleep_time);
	    DEBUG0 (6, "retrying getting the admin object.\n");

	    this->_supplier_admin =
	      this->handles.get_ec_handle()->for_suppliers (ACE_TRY_ENV);
	    ACE_TRY_CHECK;

	    count++;
	  }
	 DEBUG0 (6, "Got the admin object.\n");
       }
      else
       {
	 DEBUG0 (6, "Already had  the admin object.\n");
       }

      // Now we need the consumer proxy that shall recieve the events
      if (CORBA::is_nil (this->_consumer_proxy.in ()))
       {
	 this->_consumer_proxy =
	   this->_supplier_admin->obtain_push_consumer (ACE_TRY_ENV);
	 ACE_TRY_CHECK;
	 int count = 0;
	 while (CORBA::is_nil (this->_consumer_proxy.in ())){

	   ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
	   ACE_ERROR ((LM_ERROR," Unable to get the consumer proxy.\n"));
	   if(count >= 4)
	    {
	      throw std::runtime_error::runtime_error("Unable to get the consumer proxy");
	    } /* end of if(count >= 4) */
	  
	   ACE_OS::sleep (sleep_time);
	   DEBUG0 (6, "retrying getting consumer proxy\n");
	   this->_consumer_proxy =
	     this->_supplier_admin->obtain_push_consumer (ACE_TRY_ENV);
	   ACE_TRY_CHECK;
	  
	   count++;
	 }
	 DEBUG0 (6, "Got the consumer proxy.\n");
       }
      else
       {
	 DEBUG0 (6, "Already had  the consumer proxy.\n");
       }

      if (this->connected_to_proxy == false){
	// set ourselves up as suppliers
	RtecEventComm::PushSupplier_var supplier = this->_this (ACE_TRY_ENV);
	ACE_TRY_CHECK;

	DEBUG0 (6, "connecting supplier\n");
	this->_consumer_proxy->connect_push_supplier
	  (supplier.in (), this->qos.get_SupplierQOS (), ACE_TRY_ENV);
	ACE_TRY_CHECK;
	this->connected_to_proxy = true;
	DEBUG0 (6, "supplier connected\n");
      }
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, 
			   "System Exception while connecting Push Supplier:");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception while connecting Push Supplier:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}



/**
 *  @brief Disconnect from Event Channel
 *  @param ACE_TRY_ENV ACE exceptiona handling variable
 *  @exception CORBA::SystemException
 *
 * A method to have us disconnect. We need to do a number of things to
 * have us die cleanly.
 *   - Check to see if we are still connected
 *   - tell our supplier to stop sending us events
 *   - when the supplier is disabled, we destroy the proxy
 *   - ditto for the admin object we obtained
 */
void
STDC::QMS::Push_Supplier::disconnect (long etype, CORBA::Environment 
				      &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace ("STDC::QMS::Push_Supplier::disconnect", __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG:  Supplier object disconnecting\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);


  if (CORBA::is_nil (this->_consumer_proxy.in ()))
    return;
  this->_disconnect_event_type = etype;

  if (this->connected_to_proxy == true){
    // Tell the event channel we are going off
    this->_consumer_proxy->disconnect_push_consumer (ACE_TRY_ENV);
    ACE_CHECK;
    this->connected_to_proxy = false;
    DEBUG0 (4, "DEBUG:  Supplier disconnected from proxy\n");
  }
  if (! CORBA::is_nil (this->_consumer_proxy.in ())){
    // This is no longet a valid reference
    this->_consumer_proxy =
      RtecEventChannelAdmin::ProxyPushConsumer::_nil ();
  }

  if (! CORBA::is_nil (this->_supplier_admin.in ())){
    this->_supplier_admin =
      RtecEventChannelAdmin::SupplierAdmin::_nil ();
  }

  // Deactivate the servant
  DEBUG0 (4, "DEBUG:  Supplier deactivating the servant\n");
  PortableServer::ObjectId_var id =
    this->handles.get_root_poa_handle()->servant_to_id (this, ACE_TRY_ENV);
  ACE_CHECK;
  this->handles.get_root_poa_handle()->deactivate_object (id.in (), 
							  ACE_TRY_ENV);
  ACE_CHECK;
}


/**
 * @brief Tell the event channel we are going off the air
 * @param ACE_TRY_ENV ACE exceptiona handling variable
 * @exception CORBA::SystemException
 */
void
STDC::QMS::Push_Supplier::disconnect_push_supplier (CORBA::Environment 
						    &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace ("STDC::QMS::Push_Supplier::disconnect_push_supplier",
	     __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG:  Supplier disconnect_push_supplier\n");
  ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  this->send_disconnect_event(ACE_TRY_ENV);
}


/**
 *  @brief Set the disconnect event to the consumer
 */
void
STDC::QMS::Push_Supplier::send_disconnect_event(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::Push_Supplier::send_disconnect_event",
	     __LINE__, __FILE__);
  DEBUG0 (4, "DEBUG:  Supplier sending shutdown\n");
  // Send one event shutdown

  ACE_TRY
    {
      RtecEventComm::EventSet event (1);
      event.length (1);
      event[0].header.source = this->_my_id;
      event[0].header.type = this->_disconnect_event_type;


      {
	ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
      	DEBUG0 (4, "DEBUG:    Supplier pushing disconnect\n");
	DEBUG2 (4, "DEBUG: My ID = %d Disconnect event type = %d\n",
		this->_my_id,  this->_disconnect_event_type);

	this->_consumer_proxy->push(event, ACE_TRY_ENV);
	ACE_TRY_CHECK;
      }
    }
  ACE_CATCH (CORBA::SystemException, sys_ex)
    {
      ACE_PRINT_EXCEPTION (sys_ex, "SYS_EX sending the disconnect event");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "NON SYS EX sending the disconnect event");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return;
}

/**
 * @brief Return a pointer to the internal corba handles
 * @return A pointer to the internal corba handles
 */
STDC::QMS::CORBA_Handles *
STDC::QMS::Push_Supplier::get_handles(void)
{
  return  & this->handles;
}








