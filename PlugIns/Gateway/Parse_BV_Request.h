/*                               -*- Mode: C++ -*- 
 * Parse_BV_Request.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
 * Created On       : Mon Dec 10 17:56:59 2001
 * Created On Node  : glaurung.green-gryphon.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Tue Jan  8 22:30:25 2002
 * Last Machine Used: glaurung.green-gryphon.com
 * Update Count     : 21
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
 */

#ifndef _PARSE_BV_REQUEST_H_
#define _PARSE_BV_REQUEST_H_

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
 * $Id: Parse_BV_Request.h,v 1.3 2002/01/09 05:53:58 srivasta Exp $
 */

#include "Parse_XML.h"

namespace STDC 
{
  namespace QMS 
  {

    /**
     * This will be used by the Gateway to know where to communicate
     * back its data in a socket based world. 
     */
    struct BVTlistenAddress
    {
      ipv4AddressType host;
      int port;
    };
    
    /**
     *  The BVT controller specifies all the QMSUniqueName/Categories
     *  that it is interested in. It could specify things more
     *  specifically if desired by using all the fields of the
     *  QMSUniqueName 
     */
    typedef  vector<struct uniqueNameType> resourceList;

    /**
     *  When the controller initializes, it sends out a discovery
     *  request to the gateway, which then uses the request contents
     *  to obtain appropriate offers from the QMSTrader. The offer
     *  data is passed back to the controller for use in the GUI.
     */
    struct discoverRequestType
    {
      BVTlistenAddress address;
      resourceList resources;
    };
    
    /**
     *  Every message initiated by the controller is destined to be
     *  sent to a specific client host for action. This request is in
     *  turn translated into the appropriate request that the client
     *  probe is expecting by the BVGateway. When the response comes
     *  back, the BVGateway converts the QMSMessage response to the
     *  formats understood by the Controller. The minRepetitions value
     *  is not used directly by the BVT controller. But since it is
     *  required for the probe to produce any useful data, it can be
     *  set to a default of a very large number, like 86400 for
     *  instance.
     *  From an automation standpoint, the BVTool will need to execute
     *  requests in some timed order. So the sleepbeforenext specifies
     *  how much time to sleep before the next request in the list is
     *  to be processed.
     */
    struct resourceRequestType
    {
      requestID 	request_id;
      uniqueNameType 	QMSUniqueName;
      minRepetitions    count;
      minRepeatInterval interval;
      string            sleepbeforenext;
      string            action;      
    };

    /**
     * The data contained in a request from a basic validation GUI
     */
    struct BV_RequestType
    {
      bool isDiscovery;
      struct discoverRequestType discover_request;
      struct resourceRequestType data_request;
    };
    
    class Parse_BV_Request : public Parse_XML
      {
      public:
	/// The default constructor for the classParse_BV_Request
	Parse_BV_Request();
	///the copy constructor
	Parse_BV_Request(const Parse_BV_Request& rhs);
	/// the assignment operator
	Parse_BV_Request& operator=(const Parse_BV_Request& rhs);
	
	/// the default address-of operators
	// Parse_BV_Request* operator&()             { return this; };
	// const Parse_BV_Request* operator&() const { return this; };
	
	/// the destructor
	~Parse_BV_Request();
	
	bool parse_bv_request(MemBufInputSource &message, 
			      BV_RequestType &results);
      protected:
	bool bv_request_handler(IDOM_Node *doc_p, BV_RequestType &results);
	void discovery_handler(IDOM_Node *node_p,discoverRequestType &results);
	void discovery_req_handler(IDOM_Node *node_p, 
				   discoverRequestType &results);
	void address_handler(IDOM_Node *node_p, BVTlistenAddress &results);
	void resource_handler(IDOM_Node *node_p, resourceList &results);
	void data_handler(IDOM_Node *node_p, resourceRequestType &results);
	void data_req_handler(IDOM_Node *node_p, 
			      resourceRequestType &results);
	
      private:
	ACE_Thread_Mutex request_guard;
      };	// end of class Parse_BV_Request
  };
};



#endif /* _PARSE_REQUEST_H_ */
