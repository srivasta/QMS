/*                               -*- Mode: C++ -*- 
 * MetaData.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Fri Jun 22 15:23:12 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Sat Nov  3 02:08:21 2001
 * Last Machine Used: ember.stdc.com
 * Update Count     : 49
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
 */

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



/** @file
 *  @ingroup GenericSensor
 *  @brief A class that contains meta data about probes
 *
 * $Id: Meta_Data.h,v 1.27 2001/12/09 02:11:58 nath Exp $
 */


#ifndef _METADATA_H_
#define _METADATA_H_

#include <vector>
#include <map>

#include "ace/Synch.h"
#include "ace/Synch_T.h"
#include "ace/Thread.h"
#include "ace/Containers_T.h"

#include "orbsvcs/CosNamingC.h"
#include "orbsvcs/Event_Utilities.h"

#include "Debug.h"
#include "List_Data.h"
#include "Probe_Proxy.h"


#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingDynamicC.h"
#include "orbsvcs/CosTradingReposC.h"
#include "orbsvcs/Trader/Trader.h"
#include "orbsvcs/Trader/Trader_Utils.h"
#include "tao/PortableServer/ORB_Manager.h"

#include "TraderC.h"

#include "CORBA_Handles.h"
#include "Push_Consumer.h"
#include "Push_Supplier.h"
#include "Parse_XML.h"
#include "Message_Format.h"

namespace STDC
{
  namespace QMS
  {
    namespace Citizen
    {
      /// The state that a request may be in
      enum status_Type 
	{ 
	  RUN, PAUSE, STOP
	};   
      // forward definition
      class Probe_Proxy;
      class Meta_Data;

      /**
       * @brief A container class of meta-data about probes
       *
       * This is where we maintain all the meta data about the probes
       * that the sensor can deploy. This object also mediates all
       * communication between the sensor and the probes. 
       */
      class Meta_Data
      {
      public:
	/// The default constructor for the classMeta_Data
	Meta_Data();
	///the copy constructor
	Meta_Data(Meta_Data& rhs);
	/// the assignment operator
	const Meta_Data operator=(Meta_Data& copy);

	/// The place where most of the initialization takes place
	void init(STDC::QMS::sensorServiceType  &config,
		  CORBA::Long supplier_id, string &QMS_Schema);
	void init(STDC::QMS::ProbeDefinitionType  &capability,
		  CORBA::Long supplier_id, string &QMS_Schema);

	/// This is where we perform cleanup operations for the probe
	void cleanup(void);
	/// @overload
	void cleanup(STDC::QMS::CORBA_Handles *handles_p);
	
	/// the default address-of operators
	// Meta_Data* operator&()             { return this; };
	// const Meta_Data* operator&() const { return this; };

	/// the destructor
	~Meta_Data(){ this->cleanup(); };

	/// Send the data out to all the data channel suppliers
	int send (const string data, CORBA::Environment &ACE_TRY_ENV = 
		  TAO_default_environment ());
	/// Store a handle to the QMS Trader EC info service
	void add_ec_registry(STDC::QMS::Citizen::QMS_Trader_ECInfo_var 
			     ec_registry);
	/// Get event channel information for this probe
	void get_EC_info(void);
	/// Remove all the event channel information and reclaim resources
	void clean_EC_info(void);
	
	/// Create announce channel suppliers based on stored information
	void create_announce_suppliers(RtecEventComm::EventSourceID my_id,
				       STDC::QMS::CORBA_Handles *handles_p,
				       CORBA::Environment &ACE_TRY_ENV = 
				       TAO_default_environment ());
	/// Create request channel consumers based on stored information
	void create_request_consumers(STDC::QMS::CORBA_Handles *handles_p,
				      CORBA::Environment &ACE_TRY_ENV = 
				      TAO_default_environment ());
	/// Create data channel suppliers based on stored information
	void create_data_suppliers(RtecEventComm::EventSourceID my_id,
				   STDC::QMS::CORBA_Handles *handles_p,
				   CORBA::Environment &ACE_TRY_ENV = 
				   TAO_default_environment ());
   
	/// Connect the announce channel suppliers to the event channel
	void connect_announce_suppliers(CORBA::Environment &ACE_TRY_ENV = 
					TAO_default_environment ());
	/// Connect the reqeust channel consumers to the event channel
	void connect_request_consumers(CORBA::Environment &ACE_TRY_ENV = 
				       TAO_default_environment ());
	/// Connect the data channel suppliers to the event channel
	void connect_data_suppliers(CORBA::Environment &ACE_TRY_ENV = 
				    TAO_default_environment ());
   
	/// Disconnect the announce channel suppliers from the event channel
	void disconnect_announce_suppliers(void);
	/// Disconnect the request channel consumers from the event channel
	void disconnect_request_consumers(CORBA::Environment &ACE_TRY_ENV = 
					  TAO_default_environment ());
	/// Disconnect the data channel suppliers from the event channel
	void disconnect_data_suppliers(void);
   
	/// Cleanup the announce channel suppliers and reclaim resources
	void clean_announce_suppliers(void);
	/// Cleanup the request channel consumers and reclaim resources
	void clean_request_consumers(void);
	/// Cleanup the data channel suppliers and reclaim resources
	void clean_data_suppliers(void);
 	/// Handle incoming messages
	void handle_query(struct query_info *request_p);
 	/// Handle incoming data from probes
	void handle_data(string key, string data);
	
	
	/// The driving function for making yellow page offers
	void yp_offer(CORBA::Object_ptr obj,
		      STDC::QMS::CORBA_Handles * handles_p,
		      CORBA::Environment &ACE_TRY_ENV = 
		      TAO_default_environment ())
	  ACE_THROW_SPEC ((CORBA::SystemException));

      protected:

	/// Add information about an announce channel
	void add_announce_info(STDC::QMS::Citizen::Sensor_Data_Element* param);
	/// Add information about an request channel
	void add_request_info(STDC::QMS::Citizen::Sensor_Data_Element * param);
	/// Add information about an data channel
	void add_data_info(STDC::QMS::Citizen::Sensor_Data_Element    * param);

	/// Is this metadata about an internal probe?
	bool _is_internal;
	/// Internal store of the probe parameters from the config file
	STDC::QMS::sensorServiceType _config;
	/// Internal store of the external probe parameters
	STDC::QMS::ProbeDefinitionType _capability;
	
	
	/// EC information about announce channels
	vector<STDC::QMS::Citizen::Sensor_Data_Element *> announce_list_info_;
	/// EC information about request channels
	vector<STDC::QMS::Citizen::Sensor_Data_Element *> request_list_info_;
	/// EC information about data channels
	vector<STDC::QMS::Citizen::Sensor_Data_Element *> data_list_info_;
  
      private:
	///Make a yellow Pages offer for the probe
	void make_offer(CORBA::Object_ptr obj,
			STDC::QMS::CORBA_Handles * handles_p,
			CORBA::Environment &ACE_TRY_ENV = 
			TAO_default_environment ());
	/// Withdraw the YP offer made for the probe
	void withdraw_offer(STDC::QMS::CORBA_Handles * handles_p,
			    CORBA::Environment &ACE_TRY_ENV = 
			    TAO_default_environment ());
	
	void internal_handle_query(const string &query);

	int send_error(const string &error, 
		       STDC::QMS::QMSMessage &config,
		       CORBA::Environment &ACE_TRY_ENV = 
		       TAO_default_environment ());

	/// The offer ID of the offer we create
	CosTrading::OfferId_var offer_id;
	/// list of announce push suppliers
	vector<STDC::QMS::Push_Supplier *> Announcement_Suppliers;
	/// list of request push consumers
	vector<STDC::QMS::Push_Consumer *> Request_Consumers;
	/// list of data push suppliers
	vector<STDC::QMS::Push_Supplier *> Data_Suppliers;

	/// List of probe objects associated with us
	std::map<string, struct probe_info *> _probes;
	
	/// Store the requests that come in for this probe
	std::map<string, struct query_info *> _requests;
	
	/// The EC supplier ID in order to be able to send events 
	CORBA::ULong _supplier_id;
	/// an object reference to the EC Registry
        STDC::QMS::Citizen::QMS_Trader_ECInfo_var _ec_registry;
	/// mutex to guard internal variables
	ACE_Thread_Mutex asset_guard;
	/// Message sequence number
	long msg_sequence_no_;
	/// The number of probes created
	unsigned long _num_probes;
	

	/// The status of the probe
	enum status_Type status;
	/// mutex to guard the status
	ACE_RW_Mutex status_guard;
	/// Has the YP offer been created?
        bool _offer_created;
	/// The lcation of the QMS Schema file we shall be using iun
	/// generated messages
	string _QMS_Schema;
      };	// end of class Meta_Data
    };
  };
};


#endif /* _METADATA_H_ */
