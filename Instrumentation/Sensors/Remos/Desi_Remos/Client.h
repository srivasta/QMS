//Client.h
// Author           : Shivakumar C. Patil (shivakumar.patil@stdc.com)


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
 *  @ingroup RemosSensor 
 *  @brief  A Hello World Client that send the sensor through a test suite
 *
 * This is a sample client that can beused as a simple testing
 * mechanism for testing QMS sensors. 
 *
 * $Id: Client.h,v 1.2 2001/12/11 00:23:49 spatil Exp $
 */

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string>
#include <cstring>
#include <csignal>
#include <cstdio>
#include <list>
#include <iostream>
#include <fstream>

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
#include "Remos_SensorC.h"
#include "TraderC.h"
#include "Debug.h"

#include "Parse_XML.h"

#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"

#include "Payload.h"

using namespace CosTradingRepos;
using namespace CosTrading;

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

/**
 * @brief A simple test suite to exercise a QMS sensor
 *
 * 
 */
class Test_Client
{
 public:
  /// The default constructor for the classTest_Client
  Dllexport Test_Client();
  ///the copy constructor
  Dllexport Test_Client(const Test_Client& rhs);
  /// the assignment operator

  Dllexport Test_Client& operator=(const Test_Client& rhs);
  
  /// the default address-of operators
  Dllexport Test_Client* operator&()             { return this; };
  Dllexport const Test_Client* operator&() const { return this; };
  
  /// the destructor
  Dllexport ~Test_Client();

  /// Initialize the object
  Dllexport void init(STDC::QMS::CORBA_Handles &handles, char * identity_p, 
            char * filename_p, int repeats, double refresh_rate,
	    char * category_name_p,
	    CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ());
  

  /// Connect to the event channel using the values extracted
  Dllexport void connect_EC(void (*callback)(const string &data,void * arg_p),
                          void * arg_p = 0,
                          CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ());

  /// This is where we perform cleanup operations
  Dllexport void cleanup(void);
  
  /// The callback function to handle incoming data
  Dllexport static void callback(const string &response, void *arg_p, struct Payload_Data &);

  /// Send the test messages for the probe
  Dllexport static void send_messages(void *arg_p);
  
  
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
  /// List of the hostnames to store
  list<string> hosts;
  /// repetitions 
  int repetitions;
  /// repeat interval 
  double interval;
};	// end of class Test_Client


#endif /* _CLIENT_H_ */
