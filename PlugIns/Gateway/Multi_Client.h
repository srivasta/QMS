/*                               -*- Mode: C -*- 
 * Multi_Client.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
 * Created On       : Tue Dec 11 19:48:50 2001
 * Created On Node  : glaurung.green-gryphon.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Mon Dec 17 18:34:18 2001
 * Last Machine Used: ember.green-gryphon.com
 * Update Count     : 2
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
 */

#ifndef _MULTI_CLIENT_H_
#define _MULTI_CLIENT_H_


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
 *  @ingroup Gateway
 *  @brief A convenient interface to parsing Basic Validation Requests
 *
 * $Id: Multi_Client.h,v 1.8 2001/12/27 17:15:55 srivasta Exp $
 */

#include <time.h>
#include "Parse_BV_Request.h"
#include "CORBA_Handles.h"
#include "YP_Offer.h"
#include "TraderC.h"
#include "CommandC.h"
#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"
#include "Debug.h"
#include "Push_Consumer.h"
#include "Push_Supplier.h"

namespace STDC 
{
  namespace QMS 
  {
    class Multi_Client
      {
      public:
	/// The default constructor for the classMulti_Client
	Multi_Client();
	///the copy constructor
	Multi_Client(const Multi_Client& rhs);
	/// the assignment operator
	Multi_Client& operator=(const Multi_Client& rhs);
	
	/// the default address-of operators
	// Multi_Client* operator&()             { return this; };
	// const Multi_Client* operator&() const { return this; };
	
	/// the destructor
	virtual ~Multi_Client();
	/// Stop the client, and call the destructor
	void send(long sequence_num, STDC::QMS::BV_RequestType &config,
		  char * message_p);
	void init (char *message_p, STDC::QMS::BV_RequestType &config, 
		   STDC::QMS::CORBA_Handles *handles_p, 
		   CORBA::Long supplier_id,
		   long sequence_num,
		   const char *hostname_p,
		   const char *ip_address_p,
		   const char *uuid_p,
		   CORBA::Environment &ACE_TRY_ENV = 
		   TAO_default_environment ());
        /// Initialize built in reference to CORBA handles
        Dllexport virtual void add_handle(STDC::QMS::CORBA_Handles *handles_p);
        /// return the built in reference to CORBA handles
        Dllexport virtual STDC::QMS::CORBA_Handles * get_handle(void);
	static void init_callback(const string &response, void *arg_p);
	
      protected:
        void handle_offers(CosTrading::OfferSeq *offer_seq_ptr,
                           CosTrading::OfferIterator_var iterator,
                           CORBA_Environment &ACE_TRY_ENV = 
                           TAO_default_environment ());
        void get_offers(CORBA_Environment &ACE_TRY_ENV = 
                        TAO_default_environment ());
	
      private:

	void extract_name_id(string &data, RtecEventComm::EventType &id,
			     string &name);
	void handle_selected_properties(const CosTrading::PropertySeq &
                                        selected_properties,
                                        CORBA_Environment &ACE_TRY_ENV = 
					TAO_default_environment ());
	void cleanup(void);
	void connect_EC(CORBA_Environment &ACE_TRY_ENV = 
			TAO_default_environment ());
	
        /// Stash CORBA related handles and references
        STDC::QMS::CORBA_Handles *handles_p_;

        /// The EC supplier ID in order to be able to send events 
        CORBA::Long _supplier_id;
	STDC::QMS::BV_RequestType _config;
	string _message;

	/// The URI of the probe schema used in requests 
	string _probe_schema_uri;
	/// The URI of the schema file used in QMS Messages
	string _qms_schema_uri;
	/// The supplier ID of the sensor (used for destination id's
	string _destination_id;
	
	/// The event channel used to send requests on
	string _request_channel;
	/// The event type for the requests we send out
	RtecEventComm::EventType _request_event_type;
	/// The event channel used by the sensor to reply with data
	string _data_channel;
	/// The event type for the data reply
	RtecEventComm::EventType _data_event_type;
        /// Store the hostname we are running on
        const char *_hostname_p;
        const char *_ip_address_p;
        const char *_uuid_p;
	
	/// The push consumer for reading the data
	STDC::QMS::Push_Consumer _consumer;
	/// The push supplier for sending requests
	STDC::QMS::Push_Supplier _supplier;
	/// The host IP of the machine we are running on
	string _host_addr;
	long _request_id;
      };	// end of class Multi_Client
  };
};


#endif /* _MULTI_CLIENT_H_ */
