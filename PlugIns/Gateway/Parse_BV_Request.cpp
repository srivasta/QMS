//                              -*- Mode: C++ -*- 
// Parse_BV_Request.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
// Created On       : Mon Dec 10 19:38:55 2001
// Created On Node  : glaurung.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Jan  8 22:35:26 2002
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 43
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
static const char* 
version = "$Id: Parse_BV_Request.cpp,v 1.3 2002/01/09 05:53:58 srivasta Exp $";

/** @file 
 *  @ingroup Gateway
 *  @brief Convenience object to parse QMS XML documents
 *
 * $Id: Parse_BV_Request.cpp,v 1.3 2002/01/09 05:53:58 srivasta Exp $
 */

#include "Parse_BV_Request.h"


/**
 * @brief Return true of errors were encountered during parsing
 */
inline bool IDOMTreeErrorReporter::getSawErrors() const
{
  return fSawErrors;
}

char *
get_child_value(IDOM_Node *node_p)
{
  IDOM_Node *child_p = node_p->getFirstChild();
  if(child_p != 0)
   {
     return (char *)XMLString::transcode(child_p->getNodeValue());
   } /* end of if(child_p != 0) */
  else
   {
     return 0;
   } /* end of else */  
}

void
STDC::QMS::Parse_BV_Request::resource_handler(IDOM_Node *node_p, 
					      STDC::QMS::resourceList &results)
{
  QMS_Trace("resource_Handler", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: resource_Handler\n"); 

  if(!node_p)
   {
     cerr << "request_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  IDOM_Node *child_p = node_p->getFirstChild();

  while(child_p != 0)
   {
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "QMSUniqueName") == 0)
	 {
	   struct STDC::QMS::uniqueNameType *name_p = 
	     new struct STDC::QMS::uniqueNameType;
	   uniq_name_element_handler(child_p, *name_p);
	   results.push_back(*name_p);
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}



void
STDC::QMS::Parse_BV_Request::address_handler(IDOM_Node *node_p,
                                         STDC::QMS::BVTlistenAddress &results)
{
  QMS_Trace("address_Handler", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: address_Handler\n"); 

  if(!node_p)
   {
     cerr << "request_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  IDOM_Node *child_p = node_p->getFirstChild();

  while(child_p != 0)
   {
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p     = 0;
	
	if(strcmp(node_name_p, "host") == 0)
	 {
	   value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.host.assign(value_p);
	    } /* end of if(value_p) */
	   else
	    {
	      results.host.erase();
	    } /* end of else */
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
	if(strcmp(node_name_p, "port") == 0)
	 {
	   value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.port=atol(value_p);
	    } /* end of if(value_p) */
	   else
	    {
	      results.port=0;
	    } /* end of else */
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}

void
STDC::QMS::Parse_BV_Request::discovery_req_handler(IDOM_Node *node_p, 
		      STDC::QMS::discoverRequestType &results)
{
  QMS_Trace("discovery_req_Handler", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: discovery_req_Handler\n"); 

  if(!node_p)
   {
     cerr << "request_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  IDOM_Node *child_p = node_p->getFirstChild();

  while(child_p != 0)
   {
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "BVTlistenAddress") == 0)
	 {
	   address_handler(child_p, results.address);
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
	if(strcmp(node_name_p, "resource") == 0)
	 {
	   resource_handler(child_p, results.resources);
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}

void
STDC::QMS::Parse_BV_Request::discovery_handler(IDOM_Node *node_p,
					       STDC::QMS::discoverRequestType
					       &results)
{
  QMS_Trace("discovery_Handler", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: discovery_Handler\n"); 

  if(!node_p)
   {
     cerr << "request_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  IDOM_Node *child_p = node_p->getFirstChild();

  while(child_p != 0)
   {
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "request") == 0)
	 {
	   discovery_req_handler(child_p, results);
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}

void
STDC::QMS::Parse_BV_Request::data_req_handler(IDOM_Node *node_p,
					      STDC::QMS::resourceRequestType
					      &results)
{
  QMS_Trace("data_req_Handler", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: data_req_Handler\n"); 

  if(!node_p)
   {
     cerr << "request_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
	if(strcmp(node_name_p, "requestID") == 0)
	 {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.request_id = atol(value_p);
	    }
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
	if(strcmp(node_name_p, "QMSUniqueName") == 0)
	 {
	   uniq_name_element_handler(child_p, results.QMSUniqueName);
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
	if(strcmp(node_name_p, "minRepetitions") == 0)
	 {
	   minRepetitions_handler(child_p, results.count);
	 } /* end of if(strcmp(node_name_p, "minRepetitions") == 0) */
	
	if(strcmp(node_name_p, "minRepeatInterval") == 0)
	 {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.interval.assign(value_p);
	    }
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
	if(strcmp(node_name_p, "sleepbeforenext") == 0)
	 {
	   value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.sleepbeforenext.assign(value_p);
	    }
	 } /* end of if(strcmp(node_name_p, "sleepbeforenext") == 0) */
	if(strcmp(node_name_p, "action") == 0)
	 {
	   value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.action.assign(value_p);
	    }
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}

void
STDC::QMS::Parse_BV_Request::data_handler(IDOM_Node *node_p,
					      STDC::QMS::resourceRequestType
					      &results)
{
  QMS_Trace("data__Handler", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: data__Handler\n"); 

  if(!node_p)
   {
     cerr << "request_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  IDOM_Node *child_p = node_p->getFirstChild();

  while(child_p != 0)
   {
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "request") == 0)
	 {
           data_req_handler(child_p, results);
	 } /* end of if(strcmp(node_name_p, "discover") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}

bool
STDC::QMS::Parse_BV_Request::bv_request_handler(IDOM_Node *doc_p, 
						STDC::QMS::BV_RequestType 
						&results)
{
  QMS_Trace("request_Handler", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: request_Handler\n");
  bool success = false;
  if(!doc_p)
   {
     cerr << "request_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  // The top level node is unnamed, and is a DOCUMENT_NODE
  // We now look towards the children  
  DEBUG0(2, "DEBUG: getFirstChild\n");
  IDOM_Node *child_p = doc_p->getFirstChild();

  while(child_p != 0)
   {
     // Handle the nodes here. We have first a DOCUMENT_TYPE_NODE, and
     // then a ELEMENT_NODE. We probably do not want to deal with the
     // DTD here (the parser has done all we need to take care of). 
     if(child_p->getNodeType() == IDOM_Node::ELEMENT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "discover") == 0)
	{
	  results.isDiscovery = true;
	  success = true;
	  discovery_handler(child_p, results.discover_request);
	} /* end of if((strcmp(node_name_p, "discover") == 0) */	   
	if(strcmp(node_name_p, "resource") == 0)
	{
	  results.isDiscovery = false;
	  success = true;
	  data_handler(child_p, results.data_request);
	} /* end of if((strcmp(node_name_p, "discover") == 0) */	   
      }
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
  return success;
}




/**
 *  @brief The constructor
 *
 * 
 */
STDC::QMS::Parse_BV_Request::Parse_BV_Request() : Parse_XML()
{
  QMS_Trace ("STDC::QMS::Parse_BV_Request::Parse_BV_Request", __LINE__,
	     __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Parse_BV_Request created\n");
}

/**
 *  @overload
 * 
 */
STDC::QMS::Parse_BV_Request::Parse_BV_Request(const STDC::QMS::Parse_BV_Request& rhs) : Parse_XML()
{
  QMS_Trace ("STDC::QMS::Parse_BV_Request::Parse_BV_Request", __LINE__,
	     __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Parse_BV_Request created\n");
  this->parser = rhs.parser;
  this->errReporter = rhs.errReporter;
}

/// The destructor
STDC::QMS::Parse_BV_Request::~Parse_BV_Request()
{
  QMS_Trace ("STDC::QMS::Parse_BV_Request::~Parse_BV_Request", __LINE__,
	     __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Parse_BV_Request destroyed\n");
  this->cleanup();
}

/// The assignment operator
STDC::QMS::Parse_BV_Request & 
STDC::QMS::Parse_BV_Request::operator=(const STDC::QMS::Parse_BV_Request& rhs)
{
  QMS_Trace ("STDC::QMS::Parse_BV_Request::Parse_BV_Request", __LINE__,
	     __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Parse_BV_Request created\n");
  this->parser = rhs.parser;
  this->errReporter = rhs.errReporter;
  return *this;
}



/**
 * @brief Parse an in memory  Basic Validation GUI message
 * @return True on success, false on failure
 * @params results_p  The resutls of the parse
 * @param payload_handler A function pointer to handle the payload
 * @param payload_arg_p Arguments to pass to the payload handler
 * @param error_handler A function pointer to handle any error message
 * @param error_arg_p Arguments to pass to the error handler
 */
bool 
STDC::QMS::Parse_BV_Request::parse_bv_request(MemBufInputSource &message, 
			     struct STDC::QMS::BV_RequestType &results)
{
  QMS_Trace ("STDC::QMS::Parse_BV_Request::parse_bv_request",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Parse_BV_Request::parse_bv_request\n");
  
  // We are entering a parse session, so we lock the object until we
  // are done
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->request_guard);

  // Create and initialize the parser
  DEBUG0 (2, "DEBUG: Create and initialize the parser\n");
  this->create_parser();

  // Parse the config file
  DEBUG0 (2, "DEBUG: Parse the message\n");
  bool errorsOccured = this->parse_mem(message);
  DEBUG0 (2, "DEBUG: Done parsing\n");
  if(this->errReporter)
   {
     DEBUG0 (2, "DEBUG: We have an error reporter\n");
   } /* end of if(this->errReporter) */
  
  // If there are no errors, we handle the message
  bool success = (!errorsOccured && !this->errReporter->getSawErrors());
  if(success)
   {
     DEBUG0 (2, "DEBUG: no errors, we now handle the message\n");
     IDOM_Node *doc_p = this->parser->getDocument();
     if(doc_p)
      {
	DEBUG0 (2, "DEBUG: we now have a message tree\n");
	try
	 {
	   DEBUG0 (2, "DEBUG: calling message handler\n");
	   success = bv_request_handler(doc_p, results);
	   if(!success)
	    {
	      this->cleanup();
	      cerr << "Error  Failed to grok parsed message structure" 
		   << std::endl;
	      return success;
	    } /* end of if(!success) */
	   
	 }
	catch (const invalid_argument& ex)
	 {
	   this->cleanup();
	   cerr << "Error reading message: " << ex.what() << std::endl;
	   return false;
	 }
      } /* end of if(doc_p) */
   } /* end of if(!errorsOccured && !errReporter->getSawErrors()) */
  else
   {
     cerr << "failed to parse message" << std::endl;
   } /* end of else */
  
  // Cleanup before exiting
  this->cleanup();
  return success;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class vector<STDC::QMS::uniqueNameType>;
template STDC::QMS::uniqueNameType * __uninitialized_copy_aux<STDC::QMS::uniqueNameType *, STDC::QMS::uniqueNameType *>(STDC::QMS::uniqueNameType *, STDC::QMS::uniqueNameType *, STDC::QMS::uniqueNameType *, __false_type);
template STDC::QMS::uniqueNameType * __uninitialized_fill_n_aux<STDC::QMS::uniqueNameType *, unsigned int, STDC::QMS::uniqueNameType>(STDC::QMS::uniqueNameType *, unsigned int, STDC::QMS::uniqueNameType const &, __false_type);
template STDC::QMS::uniqueNameType * fill_n<STDC::QMS::uniqueNameType *, unsigned int, STDC::QMS::uniqueNameType>(STDC::QMS::uniqueNameType *, unsigned int, STDC::QMS::uniqueNameType const &);
template void fill<STDC::QMS::uniqueNameType *, STDC::QMS::uniqueNameType>(STDC::QMS::uniqueNameType *, STDC::QMS::uniqueNameType *, STDC::QMS::uniqueNameType const &);
template STDC::QMS::uniqueNameType * __uninitialized_copy_aux<STDC::QMS::uniqueNameType const *, STDC::QMS::uniqueNameType *>(STDC::QMS::uniqueNameType const *, STDC::QMS::uniqueNameType const *, STDC::QMS::uniqueNameType *, __false_type);

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
