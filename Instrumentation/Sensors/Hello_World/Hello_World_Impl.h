//                              -*- Mode: C++ -*- 
// Hello_World_Impl.h --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Mon Sep  3 14:02:55 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Fri Jun  7 17:40:24 2002
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 115
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



/** @file Hello_World_Impl.h
 *  @ingroup HelloWorld 
 *  @brief  A concrete, example server
 *
 *
 * This is a concrete implementation of a QMS Sensor. This is
 * supposed to be the reference implementation of a sensor that does
 * not have any domain specific information whatsoever, and should
 * serve as a basis for other Sensor implementations.
 *
 * This implementation includes Local resource discovery, publishing
 * capabilities to enable global resource discovery, implementation
 * of QoS aware adaptive.  
 *
 * $Id: Hello_World_Impl.h,v 1.22 2002/06/08 06:26:56 srivasta Exp $
 */

#ifndef _GS_IMPL_H_
#define _GS_IMPL_H_

#include <string>
#include <map>

#include "ace/OS.h"
#include "tao/ORB.h"

#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingDynamicC.h"
#include "orbsvcs/CosTradingReposC.h"
#include "orbsvcs/Trader/Trader.h"
#include "orbsvcs/Trader/Trader_Utils.h"
#include "tao/PortableServer/ORB_Manager.h"

#include "Debug.h"
#include "Hello_WorldS.h"
#include "CORBA_Handles.h"
#include "Parse_XML.h"
#include "QMS_Trader_ECInfo_Impl.h"

#include "Meta_Data_HW.h"

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

#include "Message_Format_HW.h"

namespace STDC
{
  namespace QMS
  {
    namespace Citizen
    {
      /**
       * @brief An servant implementation of an minimalist QMS Sensor
       *
       * The Hello World servant is a reference implementation of a
       * QMS Sensor that provides an example of the interactions that
       * a sensor has with the rest of the distributed QMS
       * infrastructure. It is a simplified implementation, since this
       * sensor deploys no external probes, and has only a single,
       * simple built in probe; hence only one side of the
       * interactions of a generic sensor are exposed here. 
       *
       * Additionally, this sensor implementation demonstrates the
       * utility of validation of the messages that flow in the QMS
       * infrastructure by optionally providing a slightly flawed data
       * message every 7 messages.
       *
       * Additionally, this implementation does not imlemnt the full
       * synchronization mechanisms required for handling multiple,
       * simultaneous modifiable requests; in this implementation,
       * pausing, resuming, and stopping any request pauses, resumes,
       * and stops all requests currently active. 
       */
      class Hello_World_Impl : public POA_STDC::QMS::Citizen::Hello_World
      {
      public:
	/// The default constructor for the class Hello_World_Impl
	Hello_World_Impl();
	///the copy constructor
	Hello_World_Impl(const Hello_World_Impl& rhs);
	/// the assignment operator
	Hello_World_Impl& operator=(const Hello_World_Impl& rhs);
	
	/// the default address-of operators
	// Hello_World_Impl* operator&()             { return this; };
	// const Hello_World_Impl* operator&() const { return this; };
	
	/// the destructor
	~Hello_World_Impl(){ this->cleanup(); };
	

	/// Pause the sensor temporarily
	Dllexport virtual void pause(  const char * reason,
				       const char * credentials,
				       CORBA::Short_out ack
				       )
 	  ACE_THROW_SPEC ((STDC::QMS::QMS_Error, CORBA::SystemException));
	
	/// Resume the sensor
	Dllexport virtual void resume (const char * reason,
				       const char * credentials,
				       CORBA::Short_out ack
				       )
 	  ACE_THROW_SPEC ((STDC::QMS::QMS_Error, CORBA::SystemException));

	/// Stop the sensor
	Dllexport virtual void stop (const char * reason,
				     const char * credentials,
				     CORBA::Short_out ack
				       )
 	  ACE_THROW_SPEC ((STDC::QMS::QMS_Error, CORBA::SystemException));
	/// register the object with the CORBA naming service
	Dllexport virtual void 
	register_with_naming(CORBA::Environment &ACE_TRY_ENV = 
			     TAO_default_environment ());

	Dllexport virtual void 
	unregister_with_naming(CORBA::Environment &ACE_TRY_ENV = 
			       TAO_default_environment ());
	

	///  Initial connection to the event channel
	virtual void connect_EC (string credentials);
  
	/// Instruct the citizen to disconnect from the event channel(s)
	Dllexport virtual void disconnect_EC (const char * reason,
					      const char * credentials)
          ACE_THROW_SPEC ((STDC::QMS::Citizen::QMS_Citizen_Error,
                           CORBA::SystemException));

  
  
  
	/// Instruct the citizen to re-connect from the event channel(s)  
	Dllexport virtual void reconnect_EC (const char * reason,
					     const char * EC_Name,
					     const char * credentials)
          ACE_THROW_SPEC ((STDC::QMS::Citizen::QMS_Citizen_Error,
                           CORBA::SystemException));

  
  
  
	/// Instruct the citizen to show its operating level
	Dllexport virtual void show_operating_level (CORBA::Short_out level)
          ACE_THROW_SPEC ((CORBA::SystemException));


	/// Instruct the citizen to set its operating level
	Dllexport virtual void set_operating_level (CORBA::Short level,
						    const char * credentials)
          ACE_THROW_SPEC ((STDC::QMS::Citizen::QMS_Citizen_Error,
                           CORBA::SystemException));

	/// Dump the statistics of the program
	Dllexport virtual void stats (const char * credentials,
				      CORBA::String_out stats)
          ACE_THROW_SPEC ((CORBA::SystemException));


	/// Instruct the citizen to respond to a ping
	Dllexport virtual void ping (CORBA::Short_out ack)
          ACE_THROW_SPEC ((STDC::QMS::Citizen::QMS_Citizen_Error,
                           CORBA::SystemException));

	/// Start the sensor
	Dllexport virtual void start(string credentials);
	/// Initialize the sensor object
	Dllexport virtual void init(STDC::QMS::CORBA_Handles *handles_p,
				    string credentials, 
				    char *config_file_p,
				    const char *criticality_p,
				    const char *importance_p,
				    CORBA::Environment &ACE_TRY_ENV = 
				    TAO_default_environment ());
	/// This is where we perform cleanup operations for the sensor
	Dllexport virtual void cleanup(void);
	
	/// Update the Sensors registration with the trading and
	/// fault detection services
	virtual void update_registration(string reason, string credentials);


	/// @brief Reread the configuration files
	virtual void reload_configuration(string reason, string credentials);

	/// Get the current sensor security policy
	virtual void get_security_policy(string credentials, string &policy);

	/// Set a new security policy
	virtual void set_security_policy(string policy, string credentials);

	/// Get the current sensor attributes
	virtual void get_attributes(string credentials, string &attributes);

	/// Set a new set of attributes 
	virtual void set_attributes(string attributes, string credentials);
  



	/// Initialize built in reference to CORBA handles
	Dllexport virtual void add_handle(STDC::QMS::CORBA_Handles *handles_p);
	/// return the built in reference to CORBA handles
	Dllexport virtual STDC::QMS::CORBA_Handles * get_handle(void);
	/// Activate the servant with the root_poa
	Dllexport virtual void activate(CORBA::Environment &ACE_TRY_ENV = 
					TAO_default_environment ());
	/// Deactivate the servant using the object ID stashed
	Dllexport virtual void deactivate(CORBA::Environment &ACE_TRY_ENV = 
					  TAO_default_environment ());
	/// Handle incoming messages
	Dllexport virtual void handle_query(const string &query);

	
      protected:
	/// Read the capability file ad create the meta data objects
	bool parse_config(char * file_name_p);
	/// Get the EC supplier ID in order to be able to send events
	/// down the channels
	void get_supplier_id(CORBA::Environment &ACE_TRY_ENV = 
			     TAO_default_environment ());
	/// Get event channel information for all probes
	void get_ECInfo(CORBA::Environment &ACE_TRY_ENV = 
			TAO_default_environment ());

	/// The driving function for making yellow page offers
	void yp_offer(CORBA::Environment &ACE_TRY_ENV = 
		      TAO_default_environment ());
	
      private:
	/// Initialize an object reference to the EC Registry
	void get_ec_registry(CORBA::Environment &ACE_TRY_ENV = 
			     TAO_default_environment ());
	///Make a yellow Pages offer for the sensor
	void make_offer(CORBA::Environment &ACE_TRY_ENV = 
			TAO_default_environment ());
	/// Withdraw the yellow pages offer made for the sensor
	void withdraw_offer(CORBA::Environment &ACE_TRY_ENV = 
			    TAO_default_environment ());
	/// Handle the builtin probes
	void builtin_probes(void);
	/// make YP_Offers for the probes
	void  probe_offers (string credentials);
	
	/// Initialize an XML Parser
	void init_parser(void);
	/// Cleanup the parser we created
	void parser_cleanup(void);
	
	
	/// Stash CORBA related handles and references
	STDC::QMS::CORBA_Handles *handles_p_;
	/// The set of attributes for the sensor (this is a place holder)
	string attributes;
	/// The security policy for the sensor (this is a place holder)
	string policy;

	/// The offer ID of the YP offer we make as a trader
	CosTrading::OfferId_var offer_id;
	/// The id when we are activated
	PortableServer::ObjectId_var oid_;
	/// Another form of the id when we are activated
	CORBA::Object_var obj_;
	/// Yet another form of the id when we are activated
	char * id_;

	/// Current operating level
	unsigned int level_;
	
	/// The EC supplier ID in order to be able to send events 
	CORBA::Long _supplier_id;

        /// The stash of meta data about each supported probe
        std::map<std::string, STDC::QMS::Citizen::Hello_World_Meta_Data *> probes_;

	/// an object reference to the EC Registry
 	STDC::QMS::Citizen::QMS_Trader_ECInfo_var _ec_registry;
	/// The parsed configuration
	STDC::QMS::sensorConfiguration config;
	// record status of various things

	/// How critical is our data?
	const char* _criticality_p;
	/// how important is our data?
	const char* _importance_p;

	/// Have we been initialized?
	bool _parser_initialized;
	/// Have we been activated?
	bool _activated;
	/// Has the Trading service YP offer been made?
	bool _offer_created;
	/// Have we been registerred with the naming service?
	bool _registered;
      };	// end of class Hello_World_Impl
    };
  }
};

#endif /* _GS_IMPL_H_ */
