/*                               -*- Mode: C++ -*- 
 * Client.h --- 
 * Author           : Manoj Srivastava ( manoj.srivastava@stdc.com ) 
 * Created On       : Fri Oct 26 00:09:35 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Sat Dec  1 03:16:35 2001
 * Last Machine Used: ember.stdc.com
 * Update Count     : 43
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
 *  @ingroup HelloWorld 
 *  @brief  A Hello World Client that send the sensor through a test suite
 *
 * This is a sample client that can beused as a simple testing
 * mechanism for testing QMS sensors. 
 *
 * $Id: Client_HW.h,v 1.6 2001/12/02 03:30:25 srivasta Exp $
 */

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string>
#include <cstring>
#include <csignal>
#include <cstdio>

#include <exception>

#if !defined (_WIN32)
#  include <sys/time.h>
#  include <time.h>
#endif 

#include "ace/OS.h"             
#include "ace/Thread.h"
#include "ace/Synch.h"

#include "CORBA_Handles.h"
#include "Push_Supplier.h"
#include "Push_Consumer.h"

#include "YP_Offer.h"
#include "Hello_WorldC.h"
#include "TraderC.h"
#include "Debug.h"

#include "Parse_XML.h"

#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"

#include "Payload_HW.h"

using namespace CosTradingRepos;
using namespace CosTrading;



/**
 * @brief A simple test suite to exercise a QMS sensor
 *
 * 
 */
class Test_Client
{
 public:
  /// The default constructor for the classTest_Client
  Test_Client();
  ///the copy constructor
  Test_Client(const Test_Client& rhs);
  /// the assignment operator

  Test_Client& operator=(const Test_Client& rhs);
  
  /// the default address-of operators
  Test_Client* operator&()             { return this; };
  const Test_Client* operator&() const { return this; };
  
  /// the destructor
  ~Test_Client();

  /// Initialize the object
  void init(STDC::QMS::CORBA_Handles &handles, char * identity_p, 
	    char * category_name_p,
	    CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ());
  

  /// This is where we perform cleanup operations
  void cleanup(void);
  
  /// The callback function to handle incoming data
  static void callback(const string &response, void *arg_p);

  /// Send the test messages for the probe
  static void send_messages(void *arg_p);
  
  
 protected:
  
 private:
  /// Validate an in memory XML  message 
  bool check_message(string &message);
 
  /// Initialize an XML Parser
  void init_parser(void);
  /// Cleanup the parser we created
  void parser_cleanup(void);
  /// Get a reference to the QMS Trader ECInfo component
  void get_ec_registry(CORBA::Environment &ACE_TRY_ENV =
				    TAO_default_environment ());
  /// Get a supplier ID using the QMS Trader
  void get_supplier_id(CORBA::Environment &ACE_TRY_ENV =
		       TAO_default_environment ());
  /// Get an offer for the probe we are testing  
  void get_offers(CORBA_Environment &ACE_TRY_ENV =
		 TAO_default_environment ());
  /// Connect to the Event channels
  void handle_offers(CosTrading::OfferSeq *offer_seq_ptr,
		     CosTrading::OfferIterator_var iterator,
		     CORBA::Environment &ACE_TRY_ENV = 
		     TAO_default_environment ());

  /// Select an offer after pinging the sensor
  void choose_offer(CosTrading::OfferSeq *offer_seq_ptr,
		    CosTrading::OfferIterator_var iterator,
		    CORBA_Environment &ACE_TRY_ENV =
		    TAO_default_environment ());
  /// Handle the list of properties in the selected offer
  void handle_selected_properties(const CosTrading::PropertySeq 
				  &selected_properties,
				  CORBA_Environment &ACE_TRY_ENV =
				  TAO_default_environment ());
  /// Extracts an event channel name and event type from an XML fragment
  void extract_name_id (string &data, RtecEventComm::EventType  &id, 
			string &name);
  /// Connect to the event channel using the values extracted
  void connect_EC(CORBA_Environment &ACE_TRY_ENV =
		  TAO_default_environment ());
  /// Create a in memory message to be sent to the sensor
  void create_message(long version, string &data, const char *action);
  

  /// The name advertiszed in the QMS_Trader_ECInfo
  char * _identity_p;

  /// The EC supplier ID in order to be able to send events 
  RtecEventComm::EventSourceID _supplier_id;

  /// Stash CORBA related handles and references
  STDC::QMS::CORBA_Handles _handles;

  /// an object reference to the EC Registry
  STDC::QMS::Citizen::QMS_Trader_ECInfo_var _ec_registry;

  /// Has the parser  been initialized?
  bool _parser_initialized;

  /// The QMS unique name category for the probe we are testing
  string _category_name;

  /// The URI of the probe schema used in requests 
  string _probe_schema_uri;
  /// The URI of the schema file used in QMS Messages
  string _qms_schema_uri;
  /// The event channel used to send requests on
  string _request_channel;
  /// The event type for the requests we send out
  RtecEventComm::EventType _request_event_type;
  /// The event channel used by the sensor to reply with data
  string _data_channel;
  /// The event type for the data reply
  RtecEventComm::EventType _data_event_type;

  /// The push consumer for reading the data
  STDC::QMS::Push_Consumer _consumer;
  /// The push supplier for sending requests
  STDC::QMS::Push_Supplier _supplier;
  /// The host IP of the machine we are running on
  string _host_addr;
};	// end of class Test_Client


#endif /* _CLIENT_H_ */
