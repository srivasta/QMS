/*                               -*- Mode: C -*- 
 * Receiver.h --- 
 * Author           : Manoj Srivastava ( srivasta@ember.green-gryphon.com ) 
 * Created On       : Fri Dec 14 11:21:12 2001
 * Created On Node  : ember.green-gryphon.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Fri Dec 14 11:54:16 2001
 * Last Machine Used: ember.green-gryphon.com
 * Update Count     : 7
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
 */

#ifndef _RECEIVER_H_
#define _RECEIVER_H_

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
 *  @brief  A Generic Client that just listens
 *
 * This is a sample client that can beused as a simple testing
 * mechanism for testing QMS sensors. 
 *
 * $Id: Receiver.h,v 1.2 2001/12/15 02:53:03 srivasta Exp $
 */

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
#include "Push_Consumer.h"

#include "YP_Offer.h"
#include "Generic_SensorC.h"
#include "TraderC.h"
#include "Debug.h"

#include "Parse_XML.h"

#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"

using namespace CosTradingRepos;
using namespace CosTrading;



/**
 * @brief A simple test suite to exercise a QMS sensor
 *
 * 
 */
class Test_Receiver
{
 public:
  /// The default constructor for the classTest_Receiver
  Test_Receiver();
  ///the copy constructor
  Test_Receiver(const Test_Receiver& rhs);
  /// the assignment operator

  Test_Receiver& operator=(const Test_Receiver& rhs);
  
  /// the default address-of operators
  Test_Receiver* operator&()             { return this; };
  const Test_Receiver* operator&() const { return this; };
  
  /// the destructor
  ~Test_Receiver();

  /// Initialize the object
  void init(STDC::QMS::CORBA_Handles &handles, char * identity_p, 
	    char * category_name_p, char *limiter_p,
	    CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ());
  

  /// This is where we perform cleanup operations
  void cleanup(void);
  
  /// The callback function to handle incoming data
  static void callback(const string &response, void *arg_p);

 protected:
  
 private:

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

  /// The name advertiszed in the QMS_Trader_ECInfo
  char * _identity_p;

  /// Stash CORBA related handles and references
  STDC::QMS::CORBA_Handles _handles;

  /// The QMS unique name category for the probe we are testing
  string _category_name;
  /// The event channel used by the sensor to reply with data
  string _data_channel;
  /// The event type for the data reply
  RtecEventComm::EventType _data_event_type;

  /// The push consumer for reading the data
  STDC::QMS::Push_Consumer _consumer;
  /// The host IP of the machine we are running on
  string _host_addr;
  /// The tag containing interesting data
  char *_limiter_p;
};	// end of class Test_Receiver

#endif /* _RECEIVER_H_ */
