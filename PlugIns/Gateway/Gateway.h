/*                               -*- Mode: C -*- 
 * Gateway.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
 * Created On       : Tue Dec 11 19:44:50 2001
 * Created On Node  : glaurung.green-gryphon.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Mon Dec 17 22:31:06 2001
 * Last Machine Used: ember.green-gryphon.com
 * Update Count     : 34
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
 */

#ifndef _GATEWAY_H_
#define _GATEWAY_H_

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
 * $Id: Gateway.h,v 1.12 2002/01/11 22:53:43 srivasta Exp $
 */
#include <set>
#include <map>

#include "Parse_BV_Request.h"
#include "CORBA_Handles.h"
#include "QMS_Trader_ECInfo_Impl.h"
#include "YP_Offer.h"
#include "Multi_Client.h"

namespace STDC 
{
  namespace QMS 
  {
    class Gateway
      {
      public:
	/// The default constructor for the classGateway
	Gateway();
	///the copy constructor
	Gateway(const Gateway& rhs);
	/// the assignment operator
	Gateway& operator=(const Gateway& rhs);
	
	/// the default address-of operators
	// Gateway* operator&()             { return this; };
	// const Gateway* operator&() const { return this; };
	
	/// the destructor
	virtual ~Gateway(){ this->cleanup(); };
        /// Initialize the sensor object
        virtual void init(STDC::QMS::CORBA_Handles *handles_p,
			  CORBA::Environment &ACE_TRY_ENV = 
			  TAO_default_environment ());
	
        /// This is where we perform cleanup operations
        virtual void cleanup(void);
        
        /// Initialize built in reference to CORBA handles
        Dllexport virtual void add_handle(STDC::QMS::CORBA_Handles *handles_p);
        /// return the built in reference to CORBA handles
        Dllexport virtual STDC::QMS::CORBA_Handles * get_handle(void);

        /// Handle incoming messages
        Dllexport virtual void handle_query(char * message_p);

	void handle_data(const string &message);

      protected:
        /// Initialize an XML Parser
	void init_parser(void);
        /// Cleanup the parser we created
	void parser_cleanup(void);

        /// Get the EC supplier ID in order to be able to send events
        /// down the channels
        void get_supplier_id(CORBA::Environment &ACE_TRY_ENV = 
                             TAO_default_environment ());
	void handle_discovery_req(BV_RequestType &config);
	void handle_resource_req(char *message_p,
				 STDC::QMS::BV_RequestType &config);
	void  create_response(const CosTrading::PropertySeq & properties,
			      string &response, 
			      CORBA_Environment &ACE_TRY_ENV =
			      TAO_default_environment ())	;
	
      private:
        /// Initialize an object reference to the EC Registry
        void get_ec_registry(CORBA::Environment &ACE_TRY_ENV = 
                             TAO_default_environment ());
	ssize_t write_line(int sockfd, const string message);
	int tcp_connect(const char * hostname, const char *service);
	void handle_offers(CosTrading::OfferSeq *offer_seq_ptr,
			   CosTrading::OfferIterator_var iterator,
			   string &response,
			   CORBA_Environment &ACE_TRY_ENV = 
			   TAO_default_environment ());
	void get_offers(string &category_name, 
			string &response,
			CORBA_Environment &ACE_TRY_ENV = 
			TAO_default_environment ());
	void wall(const string &message);
	
        /// Stash CORBA related handles and references
        STDC::QMS::CORBA_Handles *handles_p_;

        /// The EC supplier ID in order to be able to send events 
        CORBA::Long _supplier_id;

	/// Store the hostname we are running on
	char _hostname[ MAXNAMELEN ];
	char _ip_address[INET_ADDRSTRLEN + 1];
	char _uuid[128];

        /// The stash of meta data about each supported probe
        std::map<std::string, STDC::QMS::Multi_Client *> clients_;
	mutable ACE_RW_Mutex _client_guard;
	
	std::set<int> sockets_;
	mutable ACE_RW_Mutex _socket_guard;
	
	
        /// an object reference to the EC Registry
        STDC::QMS::Citizen::QMS_Trader_ECInfo_var _ec_registry;
	bool _parser_initialized;
	long _sequence_num;
      };	// end of class Gateway
    
  };
};

#endif /* _GATEWAY_H_ */
