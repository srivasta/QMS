//                              -*- Mode: C++ -*-
// EC_Adapter.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Oct 18 15:20:44 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu Dec  6 13:36:42 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 264
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: EC_Adapter.cpp,v 1.16 2001/12/06 19:37:43 srivasta Exp $
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
static const char* version = "$Id: EC_Adapter.cpp,v 1.16 2001/12/06 19:37:43 srivasta Exp $";

#include "EC_Adapter.h"


#if defined (_WIN32) /* Only Win32 needs special treatment. */
static const RtecEventComm::EventType QMS_DISCONNECT        = 10000;
#endif



/** @file EC_Adapter.cpp
 *  @ingroup TAOEC
 *  @brief Implentation of the Event Channel Adapter class
 *
 *  This is the main implementation for the class.
 */

/**
 *  @brief  The default constructor
 *  @param  None
 *  @exception  None
 *  @return     The API object
 *
 * This also sets the static constants for the class, including
 *     - DEFAULT_SEND_TYPE  (9000)
 *     - DEFAULT_GET_TYPE   (8100)
 *     - DEFAULT_ID         (7000)
 */
STDC::QMS::EC_Adapter::EC_Adapter (void) : DEFAULT_SEND_TYPE (9000),
					   DEFAULT_GET_TYPE (8100),
					   DEFAULT_ID (7000)
{
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: New QMS  API object\n");
}

/**
 * @overload
 */
STDC::QMS::EC_Adapter::EC_Adapter(STDC::QMS::EC_Adapter & rhs):
  argc (rhs.argc),
  argv (rhs.argv),
  Simple_mode (rhs.Simple_mode),
  send_event_type (rhs.send_event_type),
  get_event_type (rhs.get_event_type),
  my_id (rhs.my_id),
  handles (rhs.handles),
  EC_Name (rhs.EC_Name),
  Consumers (rhs.Consumers),
  Suppliers (rhs.Suppliers),
  DEFAULT_SEND_TYPE (rhs.DEFAULT_SEND_TYPE),
  DEFAULT_GET_TYPE (rhs.DEFAULT_GET_TYPE),
  DEFAULT_ID (rhs.DEFAULT_ID)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::EC_Adapter", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: New  API object\n");
}

/**
 * @brief The = operator
 *
 * This avoids self assignements, but does not make anny attempt to
 * disconnect before the copy. 
 */
const STDC::QMS::EC_Adapter
STDC::QMS::EC_Adapter::operator=(EC_Adapter & copy)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::operator =", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: copy object\n");
  if(&copy != this)
   {  
     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
     
     this->argc            = copy.argc;
     this->argv            = copy.argv;
     this->Simple_mode     = copy.Simple_mode;
     this->send_event_type = copy.send_event_type;
     this->get_event_type  = copy.get_event_type;
     this->my_id 	     = copy.my_id;
     this->handles 	     = copy.handles;
     this->EC_Name 	     = copy.EC_Name;
     this->Consumers       = copy.Consumers;
     this->Suppliers       = copy.Suppliers;
   } /* end of if(&copy != this) */
  return *this;			// enable cascaded assignments
}


/**
 *  @brief     The default destructor
 *  @return    None
 *
 *  Disconnect an destroy all the consumers and supplier in the object.
 */
STDC::QMS::EC_Adapter::~EC_Adapter (void)
{
  unsigned int i = 0;
  for(i = 0; i < this->Consumers.size(); i++)
   {
     this->Consumers[i]->disconnect();
     delete this->Consumers[i];
   } 
  for(i = 0; i < this->Suppliers.size(); i++)
   {
     this->Suppliers[i]->disconnect();
     delete this->Suppliers[i];
   }
}

/**
 * @brief Send data over the event channel using the default Supplier object
 * @param data           The data to be sent over the event channel
 * @param which_supplier The Handle of the supplier to use (default 0)
 * @return The status of the CORBA send call
 *
 * 
 */
int
STDC::QMS::EC_Adapter::send (const string &data, unsigned int which_supplier)
{
  QMS_Trace("STDC::QMS::EC_Adapter::send", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API object sending text\n");

  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  return this->Suppliers[which_supplier]->send(data);
}

/**
 *  @brief     Register a function to be called when data is recieved
 *  @param     callback       A pointer to the function
 *  @param     arg_p          Pointer to additional arguments for the function
 *  @param     which_consumer The Handle of the consumer to use
 *  @exception None
 *
 * This is ultimately called by the push function of the Consumer
 * API. The registered function takes a string argument which shall be
 * filled in with the incoming message, and also a pointer to void,
 * where any aditional options can be passed in as well. You can also
 * specify which consumer to register this call back function with,
 * with the default being 0 (the first consumer object)
 */
int
STDC::QMS::EC_Adapter::register_callback (void (*callback)(const string &data,
							   void * arg_p),
					  void * arg_p,
					  unsigned int which_consumer)
{
  QMS_Trace("STDC::QMS::EC_Adapter::register_callback", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS Remos API register data callback\n");
  
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  this->Consumers[which_consumer]->register_callback(callback, arg_p);
  
  return 0;
}


/**
 *  @brief  This is where we do corba initialization
 *  @param  argc       Count of command line arguments
 *  @param  argv       List  of command line arguments
 *  @param  my_id      The value to be used as supplier ID on the event channel
 *  @param  send_event The event type we register as suppliers for
 *  @param  get_event  The event type we register to consume
 *  @param  event_channel_name_p The name of the event channel we link to
 *
 * This is where we initialize the orb, and resolve the various
 * services that we shall need. This is a common set of handles we
 * shall need both for the consumer as well as the supplier. 
 *
 * Use this version of the function if you just want a
 * consumer-supplier pair, and already know things like the event
 * channel name and other parameters for the event channel. You can
 * add additional supplier(s) and consumer(s) by calling add_supplier
 * and add_consumer expplicitly.
 * 
 * If you need more control, you can use the overloaded format that
 * does not specify my_id, send_event, get_event, or
 * event_channel_name_p. In that case, you can use the add_supplier
 * and add_consumer calls to add even the default supplier and
 * consumers. 
 */
void
STDC::QMS::EC_Adapter::init (int argc, char **argv,
			     RtecEventComm::EventSourceID my_id,
			     RtecEventComm::EventType send_event,
			     RtecEventComm::EventType get_event,
			     char * event_channel_name_p,
			     STDC::QMS::CORBA_Handles *handle_p,
			     CORBA_Environment &ACE_TRY_ENV
			     )
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace ("STDC::QMS::EC_Adapter::init", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API object initializing\n");
  
  {
    
    ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
    
    this->argc 	      = argc;
    this->argv 	      = argv;
    this->Simple_mode = true;
    
    
    if (!my_id){      this->my_id           = EC_Adapter::DEFAULT_ID;        }
    else       {      this->my_id           = my_id;                         }
    
    if (!send_event){ this->send_event_type = EC_Adapter::DEFAULT_SEND_TYPE; }
    else            { this->send_event_type = send_event;                    }
    
    if (!get_event){  this->get_event_type  = EC_Adapter::DEFAULT_GET_TYPE;  }
    else           {  this->get_event_type  = get_event;                     }
    
    ACE_TRY
      {
	if(handle_p)
	 {
	   this->handles = *handle_p;
	 } // end of if(handle_p) 
	
	this->handles.init(argc, argv, event_channel_name_p);
	ACE_TRY_CHECK;
	
	this->handles.activate_poa_manager(ACE_TRY_ENV);
	ACE_TRY_CHECK;
      }
    ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
      {
	ACE_PRINT_EXCEPTION (ex, "name service already bound :");
	this->disconnect();
	ACE_RE_THROW;
      }
    ACE_CATCH (CORBA::SystemException, sysex)
      {
	ACE_PRINT_EXCEPTION (sysex, 
			     "System Exception initializing EC_Adapter:");
	this->disconnect();
	ACE_RE_THROW;
      }
    ACE_CATCH (CORBA::UserException, userex)
      {
	ACE_PRINT_EXCEPTION (userex, 
			     "User Exception initializing EC_Adapter:");
	this->disconnect();
	ACE_RE_THROW;
      }
  
    ACE_CATCHANY
      {
	ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			     "Caught exception initializing EC_Adapter:");
	this->disconnect();
	ACE_RE_THROW;
      }
    ACE_ENDTRY;
  }
  
  int slot_num;
  
  this->add_supplier(slot_num, event_channel_name_p,
		     this->my_id, this->send_event_type) ;
  this->add_consumer(slot_num, event_channel_name_p, this->get_event_type) ;
  return;
}

/** @overload
 *
 */
void
STDC::QMS::EC_Adapter::init (int argc, char **argv,
			     CORBA_Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace ("STDC::QMS::EC_Adapter::init", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API object initializing\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  this->argc 	      = argc;
  this->argv 	      = argv;
  this->Simple_mode = false;
  
  ACE_TRY
    {
      this->handles.init(argc, argv, "QMS_API", ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
    {
      ACE_PRINT_EXCEPTION (ex, "name service already bound :");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception in EC_Adapter::init:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception in EC_Adapter::init:");
      this->disconnect();
      ACE_RE_THROW;
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception in EC_Adapter::init:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
  
  return;
}

/**
 *  @brief Add a new push supplier object
 *  @param     slot_num             The opaque handle of the supplier created 
 *  @param     event_channel_name_p The event channel to use
 *  @param     my_id                The supplier ID to use
 *  @param     send_event           The event type we shall be sending
 *  @return    A pointer to the element that was added
 *  @exception None
 * 
 * This is the method to use when one wants more control over the
 * event channel adapter objects than is provided by the default
 * invocation of the EC_Adapter object, or if one wants more than the
 * default Push_Supplier object. You can specify the most common
 * atributes required to set up a push supplier object.
 *
 * However, for the cases where more control is required, as in the 
 * case when you need to add more eventID supplier ID pairs, there is
 * an overloaded variant that just creates an unintialized push
 * supplier, and you may use the get_supplier method  below to
 * directly manipulate the schedule and subscription information. 
 */
STDC::QMS::Push_Supplier *
STDC::QMS::EC_Adapter::add_supplier (int &slot_num,
				     char * event_channel_name_p,
				     RtecEventComm::EventSourceID my_id,
				     RtecEventComm::EventType send_event
				     )
{
  QMS_Trace ("STDC::QMS::EC_Adapter::add_supplier", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API adding supplier\n");
  
  // This call also guards the mutex
  STDC::QMS::Push_Supplier *supplier_p  = this->add_supplier(slot_num);
  { 
    ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
    supplier_p->init(this->handles, send_event, my_id, event_channel_name_p);
    return supplier_p;
  }
}


/**
 *  @brief Add a new push consumer object
 *  @param     slot_num             The opaque handle of the supplier created 
 *  @param     event_channel_name_p The event channel to use
 *  @param     get_event            The event type we shall be consuming
 *  @return    A pointer to the element that was added
 *  @exception None
 * 
 * This is the method to use when one wants more control over the
 * event channel adapter objects than is provided by the default
 * invocation of the EC_Adapter object, or if one wants more than the
 * default Push_consumer object. You can specify the most common
 * atributes required to set up a push consumer object.
 *
 * However, for the cases where more control is required, as in the 
 * case when you need to add more eventID+supplier ID pairs, there is
 * an overloaded variant that just creates an unintialized push
 * consumer, and you may use the get_consumer method  below to
 * directly manipulate the schedule and subscription information. 
 */
STDC::QMS::Push_Consumer *
STDC::QMS::EC_Adapter::add_consumer(int &slot_num,
	     char * event_channel_name_p,
	     RtecEventComm::EventType get_event
	     )
{
  QMS_Trace ("STDC::QMS::EC_Adapter::add_consumer", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API adding consumer\n");

  // This call also guards the mutex
  STDC::QMS::Push_Consumer * consumer_p = this->add_consumer(slot_num);
  {
    ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
    consumer_p->init(this->handles, get_event, event_channel_name_p);
    return consumer_p;
  }
}

/**
 *  @overload
 */
STDC::QMS::Push_Supplier *
STDC::QMS::EC_Adapter::add_supplier  (int &slot_num)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::add_supplier", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API adding supplier\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  slot_num = this->Suppliers.size();
  STDC::QMS::Push_Supplier *item_p = new STDC::QMS::Push_Supplier;
  this->Suppliers.push_back(item_p);
  return item_p;
}

  
/**
 *  @overload
 */
STDC::QMS::Push_Consumer  *
STDC::QMS::EC_Adapter::add_consumer(int &slot_num)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::add_consumer", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API adding consumer\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  slot_num = this->Consumers.size();
  STDC::QMS::Push_Consumer *item_p = new STDC::QMS::Push_Consumer;
  this->Consumers.push_back(item_p);
  return item_p;
}


/**
 *  @brief Disconnect from the event channel
 *
 * This routine initiates a clean disconnect, taking care to
 * disconnect the consumer consumer first, since that involves sending
 * a disconnect event via the supplier. It then takes care of
 * deallocating the resources acquired by the corba handles object.
 */
void
STDC::QMS::EC_Adapter::disconnect(void)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::disconnect", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API object disconnecting\n");

  // Disconnect consumer first, since that involves sending a
  // disconnect event
  this->disconnect_consumer();
  this->disconnect_supplier();
  
  {
    ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

    this->handles.disconnect();
  }
}

/** 
 *  @brief Disconnect the supplier object
 *  @param     which_supplier The handle of the supplier to disconnect
 *  @return    returns -1 if the handle is invalid, 0 otherwise
 */
int
STDC::QMS::EC_Adapter::disconnect_supplier(unsigned int which_supplier,
					   CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::disconnect_supplier", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API supplier disconnecting\n");

  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  ACE_TRY
    {
      if(which_supplier >= this->Suppliers.size())
       {
	 ACE_TRY_THROW (CORBA::BAD_PARAM ());
       }
      this->Suppliers[which_supplier]->disconnect(QMS_DISCONNECT, ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "disconnecting supplier");
      // do nothing
    }
  ACE_ENDTRY;
  
  return 0;
}

/**
 *  @brief Disconnect the consumer object
 *  @param     which_consumer The handle of the consumer to disconnect
 *  @return    returns -1 if the handle is invalid, 0 otherwise
 */
int
STDC::QMS::EC_Adapter::disconnect_consumer(unsigned int which_consumer,
					   CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::disconnect_consumer", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API consumer disconnecting\n");

  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  ACE_TRY
    {
      if(which_consumer >= this->Consumers.size())
       {
	 ACE_TRY_THROW (CORBA::BAD_PARAM ());
       }

      this->Consumers[which_consumer]->disconnect(ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "disconnecting consumer");
      // do nothing else
    }
  ACE_ENDTRY;

  return 0;
}

/**
 *  @brief Connect the supplier object (using prior defaults)
 *  @param     which_supplier The handle of the supplier to disconnect
 *  @return    returns -1 if the handle is invalid, 0 otherwise
 *
 * Care should be taken that the supplier object has been properly
 * initialized before calling this. The full form of STDC::QMS::EC_Adapter::init and
 * the full form of STDC::QMS::EC_Adapter::add_supplier take care of that, but the
 * bare bones alternatives may not.
 */
int
STDC::QMS::EC_Adapter::connect_supplier(unsigned int which_supplier,
					CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::connect_supplier", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API supplier connecting\n");

  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  ACE_TRY
    {
      if(which_supplier >= this->Suppliers.size())
       {
	 ACE_TRY_THROW (CORBA::BAD_PARAM ());
       }

      this->Suppliers[which_supplier]->connect(ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception connecting supplier :");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception while connecting supplier:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return 0;
}

/**
 *  @brief Connect the consumer object (using prior defaults)
 *  @param     which_consumer The handle of the consumer to disconnect
 *  @return    returns -1 if the handle is invalid, 0 otherwise
 *
 * Care should be taken that the consumer object has been properly
 * initialized before calling this. The full form of STDC::QMS::EC_Adapter::init and
 * the full form of STDC::QMS::EC_Adapter::add_consumer take care of that, but the
 * bare bones alternatives may not.
 */
int
STDC::QMS::EC_Adapter::connect_consumer(unsigned int which_consumer,
					CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::connect_consumer", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API consumer connecting\n");

  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  ACE_TRY
    {
      if(which_consumer >= this->Consumers.size())
       {
	 ACE_TRY_THROW (CORBA::BAD_PARAM ());
       }

      this->Consumers[which_consumer]->connect(ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, 
			   "System Exception during consumer connect :");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception during consumer connect:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return 0;
}

/**
 *  @brief Put the consumer object into a listen loop, awaiting events
 *
 * The consumer should already have been connected, using
 * STDC::QMS::EC_Adapter::connect_consumer above. 
 */
int
STDC::QMS::EC_Adapter::listen(void)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::listen", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API consumer listening\n");

  // Don't guard, since this is a long operation that never returns
  ACE_TRY
    {
      this->handles.run();
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception trying to listen:");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception trying to listen:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return 0;
}
/**
 *  @brief     Retrieve a Push_consumer object for direct interaction
 *  @param     consumer_p     Where a pointer to the object is returned
 *  @param     which_consumer The handle of the consumer to disconnect
 *  @return    returns -1 if the handle is invalid, 0 otherwise
 *  @exception None
 */
int
STDC::QMS::EC_Adapter::get_consumer(STDC::QMS::Push_Consumer *&consumer_p, 
				    unsigned int which_consumer)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::get_consumer", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API get_consumer\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  if(which_consumer >= this->Consumers.size())
   {
     ACE_TRY_THROW (CORBA::BAD_PARAM ());
   }

  consumer_p = this->Consumers[which_consumer];

  return 0;
}

/**
 *  @brief     Retrieve a Push_Supplier object for direct interaction
 *  @param     supplier_p     Where a pointer to the object is returned
 *  @param     which_supplier The handle of the consumer to disconnect
 *  @return    returns -1 if the handle is invalid, 0 otherwise
 *  @exception None
 */
int
STDC::QMS::EC_Adapter::get_supplier(Push_Supplier *&supplier_p, 
				    unsigned int which_supplier)
{
  QMS_Trace ("STDC::QMS::EC_Adapter::get_supplier", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API get_supplier\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  if(which_supplier >= this->Suppliers.size())
   {
     ACE_TRY_THROW (CORBA::BAD_PARAM ());
   }

  supplier_p =  this->Suppliers[which_supplier];

  return 0;
}

/**
 * @brief  Get a pointer to the list of consumer elements
 * @return a pointer to the double linked list of consumer elements
 *
 * This allows the user to use the concrete iterator class
 * ACE_Double_Linked_List_Iterator<EC_Adapter_Element<Push_consumer> >  
 * or the concrete reverse iterator class
 * ACE_Double_Linked_List_Reverse_Iterator<EC_Adapter_Element<Push_consumer> > 
 * to walk the list and operate on all the consumer objects.
 */
std::vector<STDC::QMS::Push_Consumer *>  *
STDC::QMS::EC_Adapter::get_consumer_list(void)
{
  return & this->Consumers;
}

/**
 * @brief  Get a pointer to the vector of supplier elements
 * @return a pointer to the double linked list of supplier elements
 *
 * This allows the user to use the concrete iterator class
 * ACE_Double_Linked_List_Iterator<QMS_Api_Element<Push_Supplier> >  
 * or the concrete reverse iterator class
 * ACE_Double_Linked_List_Reverse_Iterator<QMS_Api_Element<Push_Supplier> > 
 * to walk the list and operate on all the supplier objects.
 */
std::vector<STDC::QMS::Push_Supplier *> *
STDC::QMS::EC_Adapter::get_supplier_list(void)
{
  return & this->Suppliers;
}

/**
 * @brief Return a pointer to the internal corba handles
 * @return a pointer to the internal corba handles
 */
STDC::QMS::CORBA_Handles *
STDC::QMS::EC_Adapter::get_handles(void)
{
  return  & this->handles;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template std::vector<STDC::QMS::Push_Consumer *>;
template std::vector<STDC::QMS::Push_Supplier *>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate std::vector<STDC::QMS::Push_Consumer *>
#pragma instantiate std::vector<STDC::QMS::Push_Supplier *>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
