//                              -*- Mode: C++ -*- 
// CORBA_Handles.cpp --- 
// Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
// Created On       : Sat Aug 11 20:16:28 2001
// Created On Node  : ember.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Mon Oct 22 13:54:05 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 28
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


/// RCS version string
static const char* version = 
    "$Id: CORBA_Handles.cpp,v 1.18 2001/10/29 22:50:53 srivasta Exp $";

/** @file CORBA_Handles.cpp
 *  @ingroup Utilities
 *  @brief Convenience object to stash CORBA handles and references
 */


#include "CORBA_Handles.h"
#include "Debug.h"

/**
 *  @brief The constructor
 *  @return The CORBA handles object
 *
 * This routine just returns an non functional object, which has to be
 * initialized in order to be useful.
 */
STDC::QMS::CORBA_Handles::CORBA_Handles (CORBA::ORB_ptr orb, PortableServer::POA_ptr poa, PortableServer::POAManager_ptr poa_manager) :
  _orb (orb), _root_poa (poa), _poa_manager (poa_manager), _initialized(false),
  _poa_activated(false) 
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::CORBA_Handles", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: STDC::QMS::CORBA_Handles created\n");
}


/**
 *  @brief The destructor
 */
STDC::QMS::CORBA_Handles::~CORBA_Handles ()
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::~CORBA_Handles", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: STDC::QMS::CORBA_Handles  dying\n");
}


/**
 *  @brief The workhorse routine
 *  @param argc The count of the command line arguments
 *  @param argv A pointer to the list of command line arguments
 *  @param ACE_TRY_ENV The CORBA Env variable
 *  @exception CORBA::SystemException
 *
 * This is where the bulk of the work gets done. The sequence of steps is
 *   - The orb is initialized, using the command line options, if any
 *   - The portable Object Adapter is next
 *   - Then we create a POA manager
 *   - The naming service handle is the next
 *   - After the naming context, we get a scheduler handle
 *   - Finally, we get hold of the event channel
 *
 * An overloaded variant exists that provides a similar functionality,
 * except that the event channel handle is deferred until later.
 */
void
STDC::QMS::CORBA_Handles::init (int argc, char **argv, 
				const char * orb_name_p,
				CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::init", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API object initializing\n");
  if(this->_initialized)
   {
     return;
   } /* end of if(this->_initialized) */
  
  ACE_TRY
    {
      // ORB initialization. We shall be using the string QMS_API
      // all through this application
      this->_orb =
	CORBA::ORB_init (argc, argv, orb_name_p, ACE_TRY_ENV);
      ACE_TRY_CHECK;
      if (CORBA::is_nil (this->_orb.in ())){
	ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
	int count = 0;
	while (CORBA::is_nil (this->_orb.in ())){
	  if (count >= QMS_DEFAULT_number_of_retries){
	    ACE_ERROR ((LM_ERROR,"(%P|%t) Unable to initialize the orb.\n"));
	    ACE_TRY_THROW (CORBA::BAD_PARAM ());
	  }
	  ACE_OS::sleep (sleep_time);
	  DEBUG0 (6, "retrying getting the orb\n");
	  this->_orb =
	    CORBA::ORB_init (argc, argv, "QMS_API", ACE_TRY_ENV);
	  ACE_TRY_CHECK;
	  count++;
	}
      }
      else
       {
	 DEBUG0 (6, "Orb initilized(no external data yet)\n");
       }

      // Ok. The portable Object Adapter is next
      if (CORBA::is_nil (this->_root_poa.in ())){
	CORBA::Object_var poa_object =
	  this->_orb->resolve_initial_references("RootPOA");
	ACE_TRY_CHECK;

	this->_root_poa =
	  PortableServer::POA::_narrow (poa_object.in (), ACE_TRY_ENV);
	ACE_TRY_CHECK;
	DEBUG0 (6, "Narrowed the root poa\n");

	if (CORBA::is_nil (poa_object.in ())){
	  ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
	  int count = 0;
	  while (CORBA::is_nil (this->_root_poa.in ())){
	    if (count >= QMS_DEFAULT_number_of_retries){
	      ACE_ERROR ((LM_ERROR," Unable to initialize the POA.\n"));
	      ACE_TRY_THROW (CORBA::BAD_PARAM ());
	    }
	    ACE_OS::sleep (sleep_time);
	    DEBUG0 (6, "retrying getting root poa\n");

	    CORBA::Object_var poa_object =
	      this->_orb->resolve_initial_references("RootPOA");
	    ACE_TRY_CHECK;

	    this->_root_poa =
	      PortableServer::POA::_narrow (poa_object.in (), ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	    DEBUG0 (6, "Narrowed the root poa\n");
	    
	    count++;
	  }
	}
	else {
	  DEBUG0 (6, "Got the root poa(no external data yet)\n");
	}
      }
      else
       {
	 DEBUG0 (6, "Already had root poa handle\n");
       }

      // Now we get the manager
      if (CORBA::is_nil (this->_poa_manager.in ())) {
	this->_poa_manager =
	  this->_root_poa->the_POAManager (ACE_TRY_ENV);
	ACE_TRY_CHECK;
	if (CORBA::is_nil (this->_poa_manager.in ())) {
	  ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
	  int count = 0;
	  while (CORBA::is_nil (this->_poa_manager.in ())){
	    if (count >= QMS_DEFAULT_number_of_retries){
	      ACE_ERROR ((LM_ERROR,"(%P|%t) Unable to get the POA mgr.\n"));
	      ACE_TRY_THROW (CORBA::BAD_PARAM ());
	    }
	    ACE_OS::sleep (sleep_time);
	    DEBUG0 (6, "retrying getting the poa manager\n");

	    this->_poa_manager =
	      this->_root_poa->the_POAManager (ACE_TRY_ENV);
	    ACE_TRY_CHECK;

	    count++;
	  }
	}
	else {
	  DEBUG0(6, "Got the poa manager(no external data yet)\n");
	}
      }
      else
       {
	 DEBUG0 (6, "Already had poa manager handle\n");
       }

      // Obtain a reference to the naming service...
      if (CORBA::is_nil (this->_naming_context.in ())) {
	CORBA::Object_var naming_obj =
	  this->_orb->resolve_initial_references ("NameService", ACE_TRY_ENV);
	ACE_TRY_CHECK;
	this->_naming_context =
	  CosNaming::NamingContext::_narrow (naming_obj.in (), ACE_TRY_ENV);
	ACE_TRY_CHECK;
	DEBUG0 (6, "Narrowed the naming context(Connected)\n");

	if (CORBA::is_nil (this->_naming_context.in())) {
	  ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
	  int count = 0;
	  while (CORBA::is_nil (this->_naming_context.in ())){
	    if (count >= QMS_DEFAULT_number_of_retries){
	      ACE_ERROR ((LM_ERROR,
			  "(%P|%t) Unable to get the naming context.\n"));
	      ACE_TRY_THROW (CORBA::BAD_PARAM ());
	    }
	    ACE_OS::sleep (sleep_time);
	    DEBUG0 (6, "retrying getting naming context\n");
	    CORBA::Object_var naming_obj =
	      this->_orb->resolve_initial_references ("NameService",
						      ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	    this->_naming_context =
	      CosNaming::NamingContext::_narrow (naming_obj.in (), 
						 ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	    DEBUG0 (6, "Narrowed the naming context(Connected)\n");
	    count++;
	  }
	}
	else {
	  DEBUG0 (6, "Got the naming context(Connected)\n");
	}
      }
      else
       {
	 DEBUG0 (6, "Already Had naming context(Connected)\n");
       }

      // and now for the scheduling service
      if  (CORBA::is_nil (this->_scheduler.in ())) {
	CosNaming::Name schedule_name (1);
	schedule_name.length (1);
	schedule_name[0].id = CORBA::string_dup ("ScheduleService");

	CORBA::Object_var sched_obj=
	  this->_naming_context->resolve (schedule_name, ACE_TRY_ENV);
	ACE_TRY_CHECK;

	this->_scheduler =
	  RtecScheduler::Scheduler::_narrow(sched_obj.in (), ACE_TRY_ENV);
	ACE_TRY_CHECK;
	DEBUG0 (6, "Narrowed  the scheduler handle\n");

	if (CORBA::is_nil (this->_scheduler.in ())) {
	  ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
	  int count = 0;
	  while (CORBA::is_nil (this->_scheduler.in ())){
	    if (count >= QMS_DEFAULT_number_of_retries){
	      ACE_ERROR ((LM_ERROR,"(%P|%t) Unable to get the scheduler.\n"));
	      ACE_TRY_THROW (CORBA::BAD_PARAM ());
	    }
	    ACE_OS::sleep (sleep_time);
	    DEBUG0 (6, "retrying getting scheduler\n");
	    CORBA::Object_var sched_obj=
	      this->_naming_context->resolve (schedule_name, ACE_TRY_ENV);
	    ACE_TRY_CHECK;

	    this->_scheduler =
	      RtecScheduler::Scheduler::_narrow(sched_obj.in (), ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	    DEBUG0 (6, "Narrowed  the scheduler handle\n");
	    count++;
	  }
	}
	else {
	  DEBUG0 (6, "Got the scheduler\n");
	}
      }
      else
       {
	 DEBUG0 (6, "Already Had scheduler\n");
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
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      this->disconnect();
      ACE_RE_THROW;
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
  this->_initialized = true;
  return;
}

/**
 * @brief create and return an event channel handle
 *  @param     event_channel_name_p The event channel to use
 *  @param     event_channel The handle is returned in this variable
 *  @exception None
 *
 *  This function returns a handle to the event channel, using the
 *  handles for the other CORBA enntities already initialized in this
 *  object. 
 */
void
STDC::QMS::CORBA_Handles::get_event_channel (const char * event_channel_name_p,
		            RtecEventChannelAdmin::EventChannel_var& event_channel,
					     CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::get_event_channel", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API creating event channel\n");
  ACE_TRY
    {
      // And now for the event channel
      if (CORBA::is_nil (event_channel.in ())) {
	CosNaming::Name event_channel_name (1);
	event_channel_name.length (1);
	if (! event_channel_name_p)
	 {
	   event_channel_name[0].id = CORBA::string_dup ("QMS_Channel");
	 }
	else
	 {
	   event_channel_name[0].id = CORBA::string_dup (event_channel_name_p);
	 }

        CORBA::Object_var event_channel_obj=
          this->_naming_context->resolve (event_channel_name, ACE_TRY_ENV);
        ACE_TRY_CHECK;
        event_channel =
          RtecEventChannelAdmin::EventChannel::_narrow(event_channel_obj.in (),
                                                       ACE_TRY_ENV);
        ACE_TRY_CHECK;
        if (CORBA::is_nil (event_channel.in ())){
          ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
          int count = 0;
          while (CORBA::is_nil (event_channel.in ())){
            if (count >= QMS_DEFAULT_number_of_retries){
              ACE_ERROR ((LM_ERROR,"(%P|%t) Unable to get the event chan.\n"));
              ACE_TRY_THROW (CORBA::BAD_PARAM ());
            }
            ACE_OS::sleep (sleep_time);
            DEBUG0 (6, "retrying getting event channel\n");
            CORBA::Object_var event_channel_obj=
              this->_naming_context->resolve (event_channel_name, ACE_TRY_ENV);
            ACE_TRY_CHECK;
            event_channel =
              RtecEventChannelAdmin::EventChannel::_narrow(event_channel_obj.in
							   (),
                                                           ACE_TRY_ENV);

            count++;
          }
        }
        else {
          DEBUG0 (6, "Got the Event Channel\n");
        }
      }
      else
       {
         DEBUG0 (6, "Already Had EC\n");
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
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      this->disconnect();
      ACE_RE_THROW;
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      this->disconnect();
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return;
}

/**
 * Creates a child poa under the root poa with PERSISTENT and
 * USER_ID policies.  Call this if you want a <child_poa> with the
 * above policies, otherwise call init.  
 */
void
STDC::QMS::CORBA_Handles::init_child_poa (int &argc, char *argv[], 
					  const char *poa_name,
					  const char *orb_name,
					  CORBA_Environment &ACE_TRY_ENV )
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::init_child_poa", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: STDC::QMS::CORBA_Handles::init_child_poa\n");
  if(this->_initialized)
   {
     return;
   } /* end of if(this->_initialized) */
  ACE_TRY
    {
      // check to see if root poa has to be created.
      this->init (argc, argv, orb_name, ACE_TRY_ENV);
      ACE_TRY_CHECK;
 
      // Create the default policies - user-supplied ID, and persistent
      // objects.
      CORBA::PolicyList policies (2);
      policies.length (2);
 
      // Id Assignment policy
      policies[0] =
	this->_root_poa->create_id_assignment_policy (PortableServer::USER_ID,
						      ACE_TRY_ENV);
      ACE_TRY_CHECK;
      
      // Lifespan policy
      policies[1] =
	this->_root_poa->create_lifespan_policy (PortableServer::PERSISTENT,
					    ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // We use a different POA, otherwise the user would have to change
      // the object key each time it invokes the server.
      
      this->_child_poa =
	this->_root_poa->create_POA (poa_name,
				     this->_poa_manager.in (),
				     policies,
				     ACE_TRY_ENV);
      // Warning!  If create_POA fails, then the policies won't be
      // destroyed and there will be hell to pay in memory leaks!
      ACE_TRY_CHECK;


      // Creation of the new POAs over, so destroy the Policy_ptr's.
      for (CORBA::ULong i = 0; i < policies.length (); ++i)
       {
	 CORBA::Policy_ptr policy = policies[i];
	 policy->destroy (ACE_TRY_ENV);
	 ACE_TRY_CHECK;
       } 
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
  this->_initialized = true;
}

/**
 * @brief Activate the POA Manager
 *
 */
void
STDC::QMS::CORBA_Handles::activate_poa_manager(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::activate_poa_manager", __LINE__,
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: STDC::QMS::CORBA_Handles::activate_poa_manager\n");
  if(!this->_poa_activated)
   {
  
     if(!CORBA::is_nil (this->_poa_manager.in ()))
      {
	ACE_TRY
	  {   
	    this->_poa_manager->activate (ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	    this->_poa_activated = true;
	  }
	ACE_CATCH (PortableServer::POAManager::AdapterInactive, pex)
	  {
	    ACE_PRINT_EXCEPTION (pex,
				 "PortableServer::AdapterInactive Exception :");
	    ACE_RE_THROW;
	  }
	ACE_CATCH (CORBA::SystemException, sysex)
	  {
	    ACE_PRINT_EXCEPTION (sysex, "System Exception :");
	    ACE_RE_THROW;
	  }
	ACE_CATCHANY
	  {
	    ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
	    ACE_RE_THROW;
	  }
	ACE_ENDTRY;
      } /* end of if(!CORBA::is_nil (this->_poa_manager.in ())) */
     
   } /* end of if(!this->__poa_activated) */
}

/**
 *  Activate servant under the ROOT POA
 */
PortableServer::ObjectId_var
STDC::QMS::CORBA_Handles::activate(PortableServer::Servant servant,
				   CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::activate", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: STDC::QMS::CORBA_Handles::activate\n");
  ACE_TRY
    {
      PortableServer::ObjectId_var id =
	this->_root_poa->activate_object (servant, ACE_TRY_ENV);
      ACE_TRY_CHECK;
      return id;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex,
			   "System Exception while activating servant:");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception while activating servant:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}

void
STDC::QMS::CORBA_Handles::deactivate(const char * id_p,
				     CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::deactivate", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: STDC::QMS::CORBA_Handles::deactivate\n");
  ACE_TRY
    {
      CORBA::Object_var object =
	this->_orb->string_to_object(id_p, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      PortableServer::ObjectId_var object_id =
	this->_root_poa->reference_to_id (object.in (),
					  ACE_TRY_ENV);
      ACE_TRY_CHECK;

      this->_root_poa->deactivate_object (object_id.in (),
					  ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}
// Activate the object with the object_name under the child POA.
char *
STDC::QMS::CORBA_Handles::activate_under_child_poa 
(const char *object_name, PortableServer::Servant servant,
 CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::poa_activate", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: STDC::QMS::CORBA_Handles::poa_activate\n");
  ACE_TRY
    {
      if(object_name ==0)
       {
	 // Raise an exception, perhaps?
	 return 0;
       } /* end of if(object_name ==0) */
      PortableServer::ObjectId_var id =
	PortableServer::string_to_ObjectId (object_name);

      this->_child_poa->activate_object_with_id (id.in (), servant,
						 ACE_TRY_ENV);
      ACE_CHECK_RETURN (0);

      CORBA::Object_var obj =
	this->_child_poa->id_to_reference (id.in (), ACE_TRY_ENV);
      ACE_CHECK_RETURN (0);
      
      char * str =
	this->_orb->object_to_string (obj.in (), ACE_TRY_ENV);
      
      ACE_CHECK_RETURN (0);
      
      return str;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}

void
STDC::QMS::CORBA_Handles::deactivate_under_child_poa(const char * id_p,
						CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::deactivate under child", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: STDC::QMS::CORBA_Handles::deactivate child\n");
  ACE_TRY
    {
      CORBA::Object_var object =
	this->_orb->string_to_object(id_p, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      PortableServer::ObjectId_var object_id =
	this->_root_poa->reference_to_id (object.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      this->_child_poa->deactivate_object (object_id.in (),ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}


/**
 * @brief Start the ORB
 *
 */
void
STDC::QMS::CORBA_Handles::run(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::run", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: STDC::QMS::CORBA_Handles::run\n");
  if(!CORBA::is_nil (this->_orb.in ()))
   {
     ACE_TRY
       {   
	 this->_orb->run (ACE_TRY_ENV);
	 ACE_TRY_CHECK;
       }
     ACE_CATCH (CORBA::SystemException, sysex)
       {
	 ACE_PRINT_EXCEPTION (sysex, "System Exception :");
	 ACE_RE_THROW;
       }
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
   } /* end of if(!CORBA::is_nil (this->_poa_manager.in ())) */
}


/**
 *  @brief DEPRECATED: Add the event channel handle to the object
 *  @param     event_channel_name_p The event channel to use
 *  @exception CORBA::SystemException 
 *
 * This function uses the get_event_channel method above and adds the
 * resulting event channel handle to the object. This is now
 * deprecated, since there may be multiple event channels that the
 * client objects need to connect tro, a single stored event channel
 * handle make little sense. Use the get_event_channel() method
 * directly. 
 *
 * This method may go away in the future
 */
void
STDC::QMS::CORBA_Handles::add_event_channel (const char * event_channel_name_p,
					     CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::add_event_channel", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API adding event channel\n");
  this->get_event_channel (event_channel_name_p, this->_event_channel,
			   ACE_TRY_ENV);
  return;
}


/**
 *  @brief DEPRECATED: delete the event channel handle
 * This is now deprecated, since there may be multiple event channels
 * that the client objects need to connect tro, a single stored event
 * channel handle make little sense. Use the get_event_channel() method
 * directly.  
 *
 * This method may go away in the future
 */
void 
STDC::QMS::CORBA_Handles::delete_event_channel (void)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::disconnect", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API object disconnecting\n");

  this->_event_channel  = RtecEventChannelAdmin::EventChannel::_nil ();
}

void
STDC::QMS::CORBA_Handles::fini(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::disconnect", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API object disconnecting\n");
  ACE_TRY
    {
      this->_root_poa->destroy (1, 1, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      this->_root_poa = 0;

      this->_orb->destroy (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      this->_orb = 0;
    }
  
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}


/**
 *  @brief deallocates all the resources acquired by the init functions
 *
 */
void
STDC::QMS::CORBA_Handles::disconnect(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::disconnect", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: QMS  API object disconnecting\n");
  this->_event_channel  = RtecEventChannelAdmin::EventChannel::_nil ();
  this->_scheduler      = RtecScheduler::Scheduler::_nil();
  this->_naming_context = CosNaming::NamingContext::_nil ();
  this->fini(ACE_TRY_ENV);
}

/** @brief Return the handle to the ORB
 *  @return The ORB handle
 */
CORBA::ORB_var
STDC::QMS::CORBA_Handles::get_orb_handle(void) const
{
  return this->_orb;
}

/** @brief Return the handle to the portable object adapter
 *  @return The POA handle
 */
PortableServer::POA_var
STDC::QMS::CORBA_Handles::get_root_poa_handle(void) const
{
  return this->_root_poa;
}

/** @brief Return the handle to the portable object adapter
 *  @return The POA handle
 */
PortableServer::POA_var
STDC::QMS::CORBA_Handles::get_poa_handle(void) const
{
  return this->_root_poa;
}

/** @brief Return the handle to the portable object adapter manager
 *  @return The POA manager handle
 */
PortableServer::POAManager_var
STDC::QMS::CORBA_Handles::get_poa_mgr_handle(void) const
{
  return this->_poa_manager;
}


/** @brief Return the handle to the name service
 *  @return The name service handle
 */
CosNaming::NamingContext_var
STDC::QMS::CORBA_Handles::get_naming_handle(void) const
{
  return this->_naming_context;
}

/** @brief Return the handle to the scheduler
 *  @return The Scheduler handle
 */
RtecScheduler::Scheduler_var
STDC::QMS::CORBA_Handles::get_scheduler_handle(void) const
{
  return this->_scheduler;
}

/** @brief Return the handle to the event channel
 *  @return The event channel handle
 */
RtecEventChannelAdmin::EventChannel_var
STDC::QMS::CORBA_Handles::get_ec_handle(void) const
{
  return this->_event_channel;
}



/**
 * @brief Return an handle to the lookup interface
 * @return the lookup interface handle
 */
CosTrading::Lookup_var 
STDC::QMS::CORBA_Handles::get_lookup_handle(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::CORBA_Handles::get_lookup_handle",__LINE__, __FILE__);
  if(CORBA::is_nil(this->_lookup_var.in ()))
   {
     ACE_TRY
       {
         CORBA::Object_var trading_obj =
           this->_orb->resolve_initial_references ("TradingService");
         ACE_TRY_CHECK;
	 
         if (CORBA::is_nil (trading_obj.in ())){
           ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
           int count = 0;
           while (CORBA::is_nil (trading_obj.in ())){
             if (count >= QMS_DEFAULT_number_of_retries) {
               ACE_ERROR ((LM_ERROR," Unable to locate Trading service\n"));
               ACE_TRY_THROW (CORBA::BAD_PARAM ());
	     } // end of if(count >= QMS_DEFAULT_number_of_retries)
             ACE_OS::sleep (sleep_time);
             DEBUG0 (6, "retrying getting Trading service\n");
	     
             trading_obj =
               this->_orb->resolve_initial_references("TradingService");
             ACE_TRY_CHECK;
	     
             count++;
           } // end of while(CORBA::is_nil (trading_obj.in ())
	   
         } /* end of if(CORBA::is_nil (this->_trading_obj.in ())) */
	 
         _lookup_var = CosTrading::Lookup::_narrow (trading_obj.in (), 
						    ACE_TRY_ENV);
         ACE_TRY_CHECK;
	 
       } // end of ACE_TRY
     
     ACE_CATCH (CORBA::SystemException, sysex)
       {
         ACE_PRINT_EXCEPTION (sysex, "System Exception :");
         ACE_RE_THROW;
       }
     ACE_CATCH (CORBA::UserException, userex)
       {
         ACE_PRINT_EXCEPTION (userex, "User Exception :");
         ACE_RE_THROW;
       }
     ACE_CATCHANY
       {
         ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
         ACE_RE_THROW;
       }
     ACE_ENDTRY;

  } // end of if(CORBA::is_nil(this->_lookup_var))

  return this->_lookup_var;
}


