//                              -*- Mode: C++ -*-
// Push_Consumer.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Oct 18 16:37:08 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu Dec  6 13:32:24 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 168
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: Push_Consumer.cpp,v 1.20 2002/02/28 21:02:53 srivasta Exp $
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
"$Id: Push_Consumer.cpp,v 1.20 2002/02/28 21:02:53 srivasta Exp $";

/** @ingroup TAOEC
 *
 */


#include "orbsvcs/Time_Utilities.h"
#include "orbsvcs/Event_Utilities.h"

#include "Push_Consumer.h"
#include "Debug.h"
#if defined (_WIN32) /* Only Win32 needs special treatment. */
static const RtecEventComm::EventType QMS_DISCONNECT        = 10000;
static const long QMS_DEFAULT_retry_sleep_interval = 60;
static const int  QMS_DEFAULT_number_of_retries     = 3;
static const RtecEventComm::EventType SUPPLIER_DISCONNECT   = 20000;
#endif


/** @file Push_Consumer.cpp
 *  @ingroup TAOEC
 *  @brief Implentation of the QMS Consumer class
 */

/**
 *  @brief  Constructor
 *
 * Sets up internal variables to a sane default state. The object
 * still needs to be initialized to be useful.
 */
STDC::QMS::Push_Consumer::Push_Consumer() :
  ec_name_p(0), _get_event_type(9999), EventName(0), Is_Scheduled(false),
  Is_Subscribed(false), callback(0), arg_p(0)
{
  QMS_Trace ("STDC::QMS::Push_Consumer::Push_Consumer", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: New QMS  Consumer connecting\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  this->connected_to_proxy = false;
  this->Is_Subscribed      = false;
}


/**
 * @overload
 */

STDC::QMS::Push_Consumer::Push_Consumer(const STDC::QMS::Push_Consumer& rhs):POA_RtecEventComm::PushConsumer(),
  handles (rhs.handles),
  connected_to_proxy (rhs. connected_to_proxy),
  _get_event_type (rhs._get_event_type),
  _consumer_admin (rhs._consumer_admin),
  _supplier_proxy (rhs._supplier_proxy),
  rt_info (rhs. rt_info),
  Is_Scheduled (rhs. Is_Scheduled),
  qos (rhs. qos),
  Is_Subscribed (rhs. Is_Subscribed),
  callback (rhs.callback),
  arg_p (rhs.arg_p)
{
  QMS_Trace ("STDC::QMS::Push_Consumer::Push_Consumer copy", 
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: New  Consumer object\n");
  this->EventName = CORBA::string_dup(rhs. EventName);
}

/**
 * @brief The = operator
 *
 * This avoids self assignements, but does not make anny attempt to
 * disconnect before the copy. It is the callers responsibility to
   ensure that the consumer object is dosconnected.
 */
const STDC::QMS::Push_Consumer
STDC::QMS::Push_Consumer::operator=(const STDC::QMS::Push_Consumer& copy)
{
  QMS_Trace ("STDC::QMS::Push_Consumer::operator =", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: copy object\n");
  if(&copy != this)
   {  
     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

     this->handles 		= copy.handles;
     this->_consumer_admin 	= copy._consumer_admin;
     this->_supplier_proxy 	= copy._supplier_proxy;
     this->rt_info 		= copy.rt_info;
     this->Is_Scheduled 	= copy.Is_Scheduled;
     this->qos 		= copy.qos;
     this->Is_Subscribed 	= copy.Is_Subscribed;
     this->_get_event_type 	= copy._get_event_type;
     this->EventName 		= CORBA::string_dup(copy.EventName);
     this->connected_to_proxy = copy.connected_to_proxy;
     this->callback           = copy.callback;
     this->arg_p              = copy.arg_p;

   } /* end of if(&copy != this) */
  return *this;			// enable cascaded assignments
}


STDC::QMS::Push_Consumer::~Push_Consumer()
{
  QMS_Trace ("STDC::QMS::Push_Consumer::~Push_Consumer", __LINE__, __FILE__);
  DEBUG0 (2, "Destructor of STDC::QMS::Push_Consumer\n");
  ACE_DECLARE_NEW_CORBA_ENV;
  this->disconnect(ACE_TRY_ENV);
  ACE_CHECK;
  CORBA::string_free(this->EventName);
}


/**
 *  @brief Initialization
 *  @param Handles A set of CORBA references and handles required for set up
 *  @param get_event_type The event type to consume from the event channel
 *
 * This is where the real intialization happens. Well, really, most of
 * it has already happened in the caller, we just stash the
 * information locally.
 */
void
STDC::QMS::Push_Consumer::init (STDC::QMS::CORBA_Handles Handles,
				RtecEventComm::EventType get_event_type,
				const char * ec_name_p,
				CORBA_Environment &ACE_TRY_ENV
				)
{
  QMS_Trace ("STDC::QMS::Push_Consumer::init", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: QMS  Consumer initializing\n");
  DEBUG0 (6, "QMS  Consumer initializing\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  
  DEBUG0 (2, "DEBUG: Push_Consumer initWrite_Guard in  \n");
  this->handles          = Handles;
  this->_get_event_type = get_event_type;
  this->EventName        = (char *) "Consume QMS Message";
  this->ec_name_p        = CORBA::string_dup (ec_name_p);
  DEBUG0 (2, "DEBUG: Push_Consumer init Write_Guard out \n");
  ACE_TRY
    {
      this->rt_info = this->handles.get_scheduler_handle()->create (this->EventName,
		            ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0 (2, "DEBUG: Create a supplier rt info\n"); 
      this->default_schedule();

      this->qos.start_disjunction_group ();
	
      this->qos.insert_type (this->_get_event_type, // event type
			     this->rt_info);
      // And these are disconnect events (we need to test for these in
      // the push method
      this->qos.insert_type (QMS_DISCONNECT, this->rt_info);
      this->qos.insert_type (SUPPLIER_DISCONNECT, this->rt_info);
	
      DEBUG0 (6, "Consumer created qos object\n");
      DEBUG3 (0x00000080L,
	      "DEBUG: Added event type = %d Added event type = %d "
	      " Added event type = %d\n", this->_get_event_type,
	      QMS_DISCONNECT, SUPPLIER_DISCONNECT);
      this->Is_Subscribed    = true;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception initializing consumer:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception initializing consumer:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}


/**
 *  @brief The functioncalled when data us available
 *  @param events A set of incoming CORBA events
 *  @param ACE_TRY_ENV TAO excetion handling variable
 *
 * This is a required part of the interface. This is the function
 * that the event channel calls when there is an event for us to
 * consume. We deal with a set of events, one at a time, extracting
 * the data from the message and calling the call back registered with
 * us for that purpose.
 */
void
STDC::QMS::Push_Consumer::push (const RtecEventComm::EventSet &events,
				CORBA::Environment &ACE_TRY_ENV)
        ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace ("STDC::QMS::Push_Consumer::push", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: QMS  Consumer got event\n");
  ACE_TRY
    {
      if (events.length () == 0)
       {
	 DEBUG0 (6, "Push_Consumer (%P|%t) no events\n");
	 return;
       }
      DEBUG0 (2, "Consumer (%P|%t) received events\n");
	  DEBUG0 (2, "DEBUG: Consumer received events\n");
      // We need these to extract data from each event
      string event_data;

      // looping over the set of events
      for (u_int i = 0; i < events.length(); ++i){
	// extract the event from the any
	DEBUG2 (2, "event number %d = type %d\n",
		    i, events[i].header.type);
	DEBUG2 (2, "event number %d = type %d\n",
		          i, events[i].header.type);
		          
	// This is where we shall stash the data
	event_data.erase();
	if (event_data.size() < events[i].data.payload.length())
	 {
	   DEBUG1 (2, "event payload size is %d\n",
		       events[i].data.payload.length());
	   DEBUG1 (2, "event payload size is %d\n",
		               events[i].data.payload.length());
	   event_data.resize (events[i].data.payload.length());
	 }


	{
	  ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
	  DEBUG0 (2, "starting to extract event\n");
	  DEBUG0 (2,"starting to extract event\n");
	  for(CORBA::ULong j = 0; j < events[i].data.payload.length();j++)
	   {
	     event_data[j] = events[i].data.payload[j];
	   }

	  DEBUG1 (2, "DEBUG MEssage is: %s", event_data.c_str());
	  DEBUG0 (2, "Consumer calling callback\n");
	  DEBUG0 (2, "Consumer calling callback\n");
	  DEBUG0 (2, "."); // show some activity
	  if (this->callback)
	   {
		  DEBUG0 (2, "Before Consumer callback\n");
	     this->callback(event_data, this->arg_p);
	     DEBUG0 (2, "Consumer done callback\n");
		 DEBUG0 (2, "Consumer done callback\n");
	   }
	  else
	   {
	     DEBUG0 (6, "Consumer no callback registered\n");
	     ACE_TRY_THROW (CORBA::BAD_PARAM ());
	   }
	}
      }
    }
  ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
    {
      ACE_PRINT_EXCEPTION (ex, "name service already bound :");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception when getting message:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception when getting message:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception when getting message:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}

/**
 * @brief Get scheduling information
 * @return The current scheduling information set
 */
RtecScheduler::handle_t&
STDC::QMS::Push_Consumer::get_schedule(void)
{
  return this->rt_info;
}

/**
 * @brief Set scheduling information
 * @param schedule the scheduling parameters to set for this object
 */
void
STDC::QMS::Push_Consumer::set_schedule(RtecScheduler::handle_t& schedule)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  this->rt_info = schedule;
  this->Is_Scheduled = true;
}

/**
 * @brief Get subscription information
 * @return The current subscription information set
 */
ACE_ConsumerQOS_Factory&
STDC::QMS::Push_Consumer::get_subscription(void)
{
  return this->qos;
}

/**
 * @brief Set subscription information
 * @param qos the new subsciption informati0on for this object
 */
void
STDC::QMS::Push_Consumer::set_subscription(ACE_ConsumerQOS_Factory& qos)
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
STDC::QMS::Push_Consumer::default_schedule(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("QMS_Consumer::default_schedule", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG:  Setting a default Schedule\n");

  // No guards here, since this is a private function only called from
  // the places that already d th guards

  ACE_TRY
    {
      ACE_Time_Value tv (0, 5000);
      TimeBase::TimeT time;
      ORBSVCS_Time::Time_Value_to_TimeT (time, tv);
      RtecScheduler::Period_t rate = ACE_U64_TO_U32(time);
	
      DEBUG0 (2, "set the scheduler information\n");
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
      ACE_PRINT_EXCEPTION (sys_ex, "SYS_EX Setting schedule");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "NON SYS EX Setting schedule");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}




/**
 *  @brief Connect to the event channel as a consumer
 *  @param ACE_TRY_ENV Ace exception handling macro
 *  @exception CORBA::SystemException
 *
 * This is where we do most of the consumer specific tasks to connect
 * to the EC as a consumer (we do not actually start getting events
 * yet; we have to start listening below)
 */
void
STDC::QMS::Push_Consumer::connect (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace ("STDC::QMS::Push_Consumer::connect", __LINE__, __FILE__);
  DEBUG0(6, "(%P|%t) New QMS  Consumer connecting\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  ACE_TRY
    {
      if(this->Is_Scheduled == false)
       {
	 this->default_schedule();
       } /* end of if(this->Is_Scheduled == false) */
	  
      // We need to get a supplier admin object from the event channel
      // The canonical protocol to connect to the EC
      if (CORBA::is_nil (this->_consumer_admin.in ())) {	    
	RtecEventChannelAdmin::EventChannel_var event_channel_var;
	DEBUG1(4, "DEBUG: Connecting to ec %s", this->ec_name_p);
	DEBUG1(4, "DEBUG: Getting event type %ld", this->_get_event_type);
	this->handles.get_event_channel(this->ec_name_p, event_channel_var,
					ACE_TRY_ENV);
	RtecEventChannelAdmin::EventChannel_ptr event_channel = 
	  event_channel_var.in();
	
	this->_consumer_admin = event_channel->for_consumers (ACE_TRY_ENV);
	ACE_TRY_CHECK;
	DEBUG0 (6, "Consumer gettingt consumer admin\n");
	int count = 0;
	while (CORBA::is_nil (this->_consumer_admin.in ())) 
	 {
	   ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
	   ACE_ERROR ((LM_ERROR,
		       "(%P|%t) Unable to get the admin object.\n"));
	   if(count >= 4)
	    {
	      throw std::runtime_error::runtime_error("Unable to get the admin object.\n");
	    } /* end of if(count >= 4) */
	   
	   ACE_OS::sleep (sleep_time);
	   DEBUG0 (6, "retrying getting admin object\n");
	   this->_consumer_admin =
	     this->handles.get_ec_handle()->for_consumers (ACE_TRY_ENV);
	   ACE_TRY_CHECK;   
	   count++;
	 }
	DEBUG0 (6, "Got admin object\n");
      }
      else
       {
	 DEBUG0 (6, "Already had a admin object\n");
       }
	  
	  
      if (CORBA::is_nil (this->_supplier_proxy.in ()))
       {
	 // Get a push supplier proxy from the event channel
	 DEBUG0 (6, "getting supplier proxy\n");
	 this->_supplier_proxy =
	   this->_consumer_admin->obtain_push_supplier (ACE_TRY_ENV);
	 ACE_TRY_CHECK;
	 int count = 0;
	 while (CORBA::is_nil (this->_supplier_proxy.in ())){
	   ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
	   ACE_ERROR((LM_ERROR,"(%P|%t) Unable to get the supplier proxy\n"));
	   if(count >= 4)
	    {
	      throw std::runtime_error::runtime_error("Unable to get the admin object.\n");
	    } /* end of if(count >= 4) */
	   ACE_OS::sleep (sleep_time);
	   DEBUG0 (6, "retrying getting supplier proxy\n");
	   this->_supplier_proxy =
	     this->_consumer_admin->obtain_push_supplier (ACE_TRY_ENV);
	   ACE_TRY_CHECK;
	      
	   count++;
	 }
	 DEBUG0 (6, "Got supplier proxy\n");
       }
      else
       {
	 DEBUG0 (6, "Already had a supplier proxy\n");
       }
	  
      if (this->connected_to_proxy == false){
	// set ourselves up as consumers
	RtecEventComm::PushConsumer_var consumer =
	  this->_this (ACE_TRY_ENV);
	ACE_TRY_CHECK;
	    
	// register with the event channel
	DEBUG0 (6, "connecting consumer\n");
	this->_supplier_proxy->connect_push_consumer
	  (consumer.in (), this->qos.get_ConsumerQOS (), ACE_TRY_ENV);
	ACE_TRY_CHECK;
	this->connected_to_proxy = true;
	DEBUG0 (6, "consumer connected\n");
      }
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, 
			   "System Exception connecting Push Consumer :");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception connecting Push Consumer :");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
  DEBUG0 (2, "DEBUG: Push_Consumer connect Write_Guard out \n");
}


/**
 *  @brief Disconnect from EC
 *  @param ACE_TRY_ENV ACE exceptiona handling variable
 *  @exception CORBA::SystemException
 *
 * A method to have us disconnect. We need to do a number of things to
 * have us die cleanly.
 *   - Check to see if we are still connected
 *   - when the supplier is disabled, we destroy the proxy
 *   - ditto for the admin object we obtained
 */
void
STDC::QMS::Push_Consumer::disconnect (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace ("STDC::QMS::Push_Consumer::disconnect ", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: QMS  Consumer disconnecting\n");
  // we only need do something if we are still connected
  if (CORBA::is_nil (this->_supplier_proxy.in ())
      || CORBA::is_nil (this->_consumer_admin.in ()))
    return;

  if (this->connected_to_proxy == true){
    // First, tell our supplier to stop sending us events
    this->_supplier_proxy->disconnect_push_supplier (ACE_TRY_ENV);
    ACE_CHECK;
    this->connected_to_proxy = false;
  }

  // Now that the supplier is disabled, we destroy the proxy
  if (! CORBA::is_nil (this->_supplier_proxy.in ())){
    this->_supplier_proxy =
      RtecEventChannelAdmin::ProxyPushSupplier::_nil ();
  }

  if (! CORBA::is_nil (this->_consumer_admin.in ())){
    // ditto for the admin object we obtained
    this->_consumer_admin =
      RtecEventChannelAdmin::ConsumerAdmin::_nil ();
  }
}


/**
 *  @brief Handle a disconnect reuest
 *  @param ACE_TRY_ENV ACE exceptiona handling variable
 *  @exception CORBA::SystemException
 *
 * This is a required part of our interface. What _should_ we do here?
 * Just pulling the plug may not be a great idea  Currently we just
 * ignore this request
 */
void
STDC::QMS::Push_Consumer::disconnect_push_consumer (CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace ("STDC::QMS::Push_Consumer::disconnect_push_consumer",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG:  QMS  disconnect_push_consumer\n");
  // Do nothing if the event channel tell us to shut off?
}


/**
 *  @brief Register a callback fundtion to call when we get data
 *  @param callback function to call
 *  @param arg_p pointer to additional arguments for the function
 *
 *
 */
void
STDC::QMS::Push_Consumer::register_callback (void (*callback)(const string &data,
						  void *arg_p),
				 void * arg_p)
{
  QMS_Trace ("STDC::QMS::Push_Consumer::register_callback", 
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG:  QMS  Consumer register callback\n");
  DEBUG0 (6, "Consumer registering CallBack\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  this->callback = callback;
  this->arg_p = arg_p;
}


/**
 * @brief Return a pointer to the internal corba handles
 * @return a pointer to the internal corba handles
 */
STDC::QMS::CORBA_Handles *
STDC::QMS::Push_Consumer::get_handles(void)
{
  return & this->handles;
}
