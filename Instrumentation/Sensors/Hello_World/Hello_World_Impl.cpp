//                              -*- Mode: C++ -*- 
// Hello_World_Impl.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Mon Sep  3 15:21:17 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Jun  8 00:29:33 2002
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 264
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


/** @file Hello_World_Impl.cpp
 *  @ingroup HelloWorld 
 *  @brief The implementation of the servant
 *
 *  $Id: Hello_World_Impl.cpp,v 1.63 2002/06/08 06:27:15 srivasta Exp $
 */


#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>

#include <ctype.h>

#include <map>
 
#include "Hello_World_Impl.h"

#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingDynamicC.h"
#include "orbsvcs/CosTradingReposC.h"
#include "orbsvcs/Trader/Trader.h"
#include "orbsvcs/Trader/Trader_Utils.h"
#include "tao/PortableServer/ORB_Manager.h"

#include "QMS_Trader_ECInfo_Impl.h"
#include "YP_Offer.h"
using std::invalid_argument;

/// List of generic CORBA Trading offer property names that are deemed
/// searcheable 
static const char *propnames[11] = 
  { "", 
    "QMS_YP_PROP_1",  "QMS_YP_PROP_2", "QMS_YP_PROP_3", "QMS_YP_PROP_4",
    "QMS_YP_PROP_5", "QMS_YP_PROP_6", "QMS_YP_PROP_7", "QMS_YP_PROP_8",
    "QMS_YP_PROP_9", "QMS_YP_PROP_10"};

/// RCS version string
static const char* version = 
"$Id: Hello_World_Impl.cpp,v 1.63 2002/06/08 06:27:15 srivasta Exp $";

#if defined(_WIN32)
#  define snprintf _snprintf
#endif

/**
 * @brief return the value of a child node
 * @param node_p A pointer to the node of interest
 *
 * Generally used to get values of leaf nodes,  This function is part
 * of the handle_query mechanism
 */
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

/**
 * @brief Fill in the values of the payload 
 * @param node_p A IDOM node that contains the values
 * @param results Where we stuff the results into
 *
 * As is the case with most parsing functions, it is assumed that the
 * validation has been handled by the parser.  We only take action on
 * values that we know, and ignore any potential newer
 * extentions. This function is part of the handle_query mechanism 
 */
void
request_handler(IDOM_Node *node_p, struct Hello_World_Request &results)
{
  QMS_Trace("request_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: request_handler\n");

  if(!node_p)
   {
     cerr << "request_handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 

  IDOM_Node *child_p = node_p->getFirstChild();

  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p = 0;
	if(strcmp(node_name_p, "firstname") == 0)
         {
	   value_p = get_child_value(child_p);
	   if(value_p)
            {
              results.firstname.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "firstname") == 0) */
	if(strcmp(node_name_p, "lastname") == 0)
         {
	   value_p = get_child_value(child_p);
	   if(value_p)
            {
              results.lastname.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "lastname") == 0) */
	if(strcmp(node_name_p, "action") == 0)
         {
	   value_p = get_child_value(child_p);
	   if(value_p)
            {
              results.action.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "lastname") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}

/**
 * @brief Handle the helloWorld tag of the incoming request
 * @param node_p Pointer to the IDOM node we are handling
 * @param results where the output is stashed
 *
 * This function is part of the handle_query mechanism 
 */
void
helloWorld_handler(IDOM_Node *node_p, struct helloWorld &results)
{
  QMS_Trace("helloWorld_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: helloWorld_handler\n");

  if(!node_p)
   {
     cerr << "helloWorld_handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "Request") == 0)
         {
           request_handler(child_p, results.request);
         } /* end of if(strcmp(node_name_p, "helloWorld") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}

/**
 * @brief Handle the payload of the incoming request
 * @param node_p Pointer to the IDOM node we are handling
 * @param arg_p A pointer to the struct where the results are to be stashed
 *
 * This function is part of the handle_query mechanism 
 */
bool
payload_Handler(IDOM_Node *node_p, void *arg_p)
{
  QMS_Trace("payload_Handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_Handler\n");

  bool success = false;
  
  struct hw_payload_data *results_p = (struct hw_payload_data *)arg_p;
  if(!results_p)
   {
     cerr << "payload_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments results_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } /* end of if(!results_p) */
  
  if(!node_p)
   {
     cerr << "ayload_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments node_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "helloWorld") == 0)
         {
           helloWorld_handler(child_p, results_p->data);
	   success = true;
         } /* end of if(strcmp(node_name_p, "helloWorld") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
  return success;
}

/** @brief The default constructor
 *
 */
STDC::QMS::Citizen::Hello_World_Impl::Hello_World_Impl() :
  _criticality_p("VERY_HIGH"), _importance_p("MEDIUM"),
  _parser_initialized(false), _activated(false), _offer_created(false)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::Hello_World_Impl", 
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::Hello_World_Impl\n");
}


/** @brief Initialize the sensor object
 *  @param credentials The credentials of the entity making the  request
 *  @param config_file_p The path name to the sensor configuration file
 *  @param criticality_p How critical is the data produced
 *  @param importance_p  How important is the data produced
 *  @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 *  This is where most of the setup and initiasation of the sensor
 *  object occurs. The criticality and importance constants are used
 in setting scheduling paramters for the event channel.
 *
 *  First, we parse the configuration file, and fill
 *  out the full QMS Unique name (enhancng the category that we find
 *  in the configuration file).
 *
 *  Next, we advertize our presence by creating a Yellow Pages Offer
 *  -- ensuring, in the process, that the service type tags are
 *  present in the CORBA trading service.  
 *
 *  After that, we obtain an object reference to the QMS Trader ECInfo
 *  service, and obtain from it a supplier ID.
 *
 * Next, we handle any builtin probes -- including getting event
 * channel information for the probes, creating offers for them, and 
 * connecting to the event channel.
 */
void
STDC::QMS::Citizen::Hello_World_Impl::init(STDC::QMS::CORBA_Handles *handles_p,
					   string credentials, 
					   char *config_file_p,
					   const char *criticality_p,
					   const char *importance_p,
					   CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::init", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::init\n");
  DEBUG1(DEBUG_L_ENTER, "DEBUG: Credentials %s\n", credentials.c_str());

  this->_criticality_p = criticality_p;
  this->_importance_p  = importance_p;
  
  if(!credentials.empty())
   {
     cout << "init: credentials" << credentials.c_str() << endl;
   } /* end of if(!credentials.empty()) */
  if(handles_p)
   {
     this->handles_p_ = handles_p;
     if(!this->handles_p_)
      {
	cerr << __FILE__ << " " << __LINE__ 
	     << "corba handles assignment failed" << endl;
	throw invalid_argument("corba handles assignment failed");
      } /* end of if(!this->handles_p_) */
   }
  
  ACE_TRY
    {
      this->activate(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      this->init_parser();
      bool parsed_config = this->parse_config(config_file_p);
      ACE_TRY_CHECK;
      if(!parsed_config)
       {
	 cerr << "Failed to parse configuration file: " << config_file_p
	      << endl << "Aborting now." << endl;
	 cerr << __FILE__ << __LINE__ << std::endl;
	 this->parser_cleanup();
	 exit (EXIT_FAILURE);
       } 

      if(this->config.offer_prop.QMSUniqueName.category.empty())
       {
	 cerr << "Error handling config -- no QMSUniqueName.category"
	      << std::endl;
	 cerr << __FILE__ << __LINE__ << std::endl;
	 this->parser_cleanup();
	 exit (EXIT_FAILURE);
       }
      if(this->config.QMS_Schema.empty())
       {
	 cerr << "Error handling config - no QMS_Schema" << std::endl;
	 cerr << __FILE__ << __LINE__ << std::endl;
	 this->parser_cleanup();
	 exit (EXIT_FAILURE);
       } /* end of if(this->config.QMS_Schema.empty()) */
      
      /// add in our host an uuid bits for the unique name
      char hostname[ MAXNAMELEN ];
      char ip_address[INET_ADDRSTRLEN + 1];
      char uuid[128];
	
      ACE_OS::hostname( hostname, MAXNAMELEN );
      struct hostent *hostinfo = ACE_OS::gethostbyname (hostname);

      in_addr address;
      address.s_addr = 
	(ACE_reinterpret_cast (in_addr * ,
			       hostinfo->h_addr_list[0])->s_addr);
      ACE_OS::strcpy(ip_address, inet_ntoa(address));
      
      this->config.offer_prop.QMSUniqueName.host.assign(ip_address);

      int ret = snprintf(uuid, 128, "%d", ACE_OS::getpid ());
      if(ret == -1 || ret >=128)
       {
	 cerr << "Error handling config" << std::endl;
	 cerr << __FILE__ << __LINE__ << std::endl;
	 this->parser_cleanup();
	 exit (EXIT_FAILURE);
       } /* end of if(ret == -1 || ret >=32) */
      this->config.offer_prop.QMSUniqueName.uuid.assign(uuid);
      
      // Ready to make a yp offer now
      this->_offer_created=false;
      this->yp_offer(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      this->register_with_naming(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if(CORBA::is_nil(this->_ec_registry.in()))
       {
	 this->get_ec_registry(ACE_TRY_ENV);
	 ACE_TRY_CHECK;
       } /* end of if(CORBA::is_nil(this->_ec_registry)) */

      this->get_supplier_id(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Handles the builtin probes
      this->builtin_probes();
      this->get_ECInfo(ACE_TRY_ENV);
      this->connect_EC(credentials);
      this->probe_offers(credentials);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
			   "Error Initializing Sensor");
      this->cleanup();
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}

/**
 * @brief This is where we perform cleanup operations for the sensor
 *
 * The actions taken include withdrawing our YP offer, walking through
 * the list of current probes, and performing a probe cleanup, 
 * cleaning up after the XML parser, and, fianlly, shutting down the ORB
 */
void
STDC::QMS::Citizen::Hello_World_Impl::cleanup(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::cleanup", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::cleanup");
  DEBUG0(4, "withdrawing offers");
  this->withdraw_offer();

  DEBUG0(4, "Cleaning up probes");
  std::map<std::string, STDC::QMS::Citizen::Hello_World_Meta_Data *>::iterator pos;
   for(pos = this->probes_.begin(); pos != this->probes_.end(); ++pos)
    {
      if(pos->second != 0)
       {
	 pos->second->cleanup(this->handles_p_);
	 delete pos->second;
	 pos->second = 0;
       } /* end of if(pos->second) */
    }
   this->probes_.clear();
   DEBUG0(4, "Deactivating");
   this->deactivate();
   DEBUG0(4, "unregister_with_naming");
   this->unregister_with_naming();
   DEBUG0(4, "Cleaning up Parser");
   this->parser_cleanup();
   DEBUG0(4, "Sensor cleaned up");
}

/**
 * @brief Create Meta Data objects for all probes defined in the config file
 *
 * We walk through all built in probe definitions in the configuration
 * file, create a Meta Data object for each, initialize it with data
 * gleaned from the config file, and add it to the list of available
 * probes. 
 *
 */
void
STDC::QMS::Citizen::Hello_World_Impl::builtin_probes(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::builtin_probes", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::builtin_probes");

  if(this->config.sensorServices.empty())
   {
     DEBUG0(6, "DEBUG: There are no builtin probes");
     return;
   } /* end of if(this->config.sensorServices.empty()) */
  
  vector<STDC::QMS::sensorServiceType>::iterator iter;

  for(iter = this->config.sensorServices.begin(); 
      iter != this->config.sensorServices.end(); 
      iter++)
   {
     iter->offer_prop.QMSUniqueName.uuid = 
       this->config.offer_prop.QMSUniqueName.uuid;
     iter->offer_prop.QMSUniqueName.host = 
       this->config.offer_prop.QMSUniqueName.host;
     STDC::QMS::Citizen::Hello_World_Meta_Data *probe_p = 
       new STDC::QMS::Citizen::Hello_World_Meta_Data();
     assert(probe_p);
     if(!iter->offer_prop.QMSUniqueName.category.empty())
      {
	probe_p->init(*iter, this->_supplier_id, this->config.QMS_Schema,
		      this->_criticality_p, this->_importance_p);
	this->probes_.insert(std::make_pair(iter->offer_prop.QMSUniqueName.category, probe_p));
      } /* end of if(!iter->offer_prop.QMSUniqueName.empty()) */
     else
      {
	if(probe_p)
	 {
	   delete probe_p;
	   probe_p = 0;
	 } /* end of if(probe_p) */
      } /* end of else */
   }
}

/**
 * @brief Initialize built in reference to CORBA handles
 * @param handles_p A reference to CORBA handles
 */
void
STDC::QMS::Citizen::Hello_World_Impl::add_handle(STDC::QMS::CORBA_Handles
						 *handles_p)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::add_handle", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::add_handle");
  if(!handles_p)
   {
     throw invalid_argument("empty corba handles");
   } /* end of if(!handles_p) */
  this->handles_p_ = handles_p;
  if(!this->handles_p_)
   {
     throw invalid_argument("corba handles assignment failed");
   } /* end of if(!this->handles_p_) */
}

/**
 * @brief return the built in reference to CORBA handles
 * @return A reference to CORBA handles
 */
STDC::QMS::CORBA_Handles *
STDC::QMS::Citizen::Hello_World_Impl::get_handle(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::get_handle", __LINE__, 
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::get_handle");
  return this->handles_p_;
}

/**
 * @brief Activate the servant with the root_poa
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * We activate the object explicitly with the root POA, and we stash
 * the object ID returned to be used later for deactivation.
 */
void
STDC::QMS::Citizen::Hello_World_Impl::activate(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::activate", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::activate");
  if(this->_activated)
   {
     return;
   } /* end of if(this->_activated) */
  
  ACE_TRY
    {
      this->handles_p_->activate_poa_manager(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      
      this->oid_ = this->handles_p_->activate(this, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      this->obj_ =
	this->handles_p_->get_root_poa_handle()->id_to_reference (this->oid_.in (), 
							   ACE_TRY_ENV);
      ACE_TRY_CHECK;

      this->id_ = 
	this->handles_p_->get_orb_handle()->object_to_string (this->obj_.in (),
							      ACE_TRY_ENV);
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, 
			   "System Exception  while activating the sensor:");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, 
			   "User Exception while activating the sensor :");
      ACE_RE_THROW;
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
			   "Caught exception while activating the sensor:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
  this->_activated = true;}

/**
 * @brief Deactivate the servant using the object ID stashed
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * We deactivate the object explicitly with the root POA using the
 * stored object ID.
 */
void
STDC::QMS::Citizen::Hello_World_Impl::deactivate(CORBA::Environment 
						 &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::deactivate", __LINE__, 
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::deactivate");
  if(! this->_activated)
   {
     return;
   } /* end of if(! this->_activated) */
  
  ACE_TRY
    {
      this->handles_p_->deactivate(this->id_, ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
    }
  ACE_ENDTRY;
  this->_activated = false;
}


/*
 * 
 * 
 *           The Parmeters
 *
 * 
 */



/** @brief Get the current sensor security policy
 *  @param credentials The credentials of the entity making the request
 *  @param policy the requested policy
 */
void
STDC::QMS::Citizen::Hello_World_Impl::get_security_policy(string credentials, 
						 string &policy)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::get_security_policy",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::get_security_policy\n");
  DEBUG1(DEBUG_L_ENTER, "DEBUG: Credentials %s\n", credentials.c_str());
  if(!credentials.empty())
   {
     cout << "init: credentials" << credentials.c_str() << endl;
   } /* end of if(!credentials.empty()) */
  policy = "";
}


/** @brief Set a new security policy
 *  @param credentials The credentials of the entity making the request
 *  @param policy The new security policy to be implemented by the sensor
 */
void
STDC::QMS::Citizen::Hello_World_Impl::set_security_policy(string policy, 
						 string credentials)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::set_security_policy",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::set_security_policy\n");
  DEBUG1(DEBUG_L_ENTER, "DEBUG: Credentials %s\n", credentials.c_str());

  if(!credentials.empty())
   {
     cout << "set_security_policy: credentials" << credentials.c_str() 
	  << endl;
   } /* end of if(!credentials.empty()) */
  if(!policy.empty())
   {
     cout << "set_security_policy:policy" << policy.c_str() << endl;
   } /* end of if(!credentials.empty()) */
}

/** @brief Get the current sensor attributes
 *  @param credentials The credentials of the entity making the request
 *  @param attributes  The requested attributes
 */
void
STDC::QMS::Citizen::Hello_World_Impl::get_attributes(string credentials, 
						     string &attributes)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::get_attributes",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::get_attributes\n");
  DEBUG1(DEBUG_L_ENTER,
	 "DEBUG: Credentials %s\n", credentials.c_str());
  if(!credentials.empty())
   {
     cout << "get_attributes: credentials" << credentials.c_str() << endl;
   } /* end of if(!credentials.empty()) */
  if(!attributes.empty())
   {
     cout << "get_attributes:policy" << attributes.c_str() << endl;
   } /* end of if(!credentials.empty()) */
}



/** @brief Set a new set of attributes 
 *  @param credentials The credentials of the entity making the request
 *  @param attributes The new set of attributes for the sensor
 */
void
STDC::QMS::Citizen::Hello_World_Impl::set_attributes(string attributes,
					    string credentials)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::set_attributes", 
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::set_attributes\n");
  DEBUG1(DEBUG_L_ENTER, "DEBUG: Credentials %s\n", credentials.c_str());
 
  if(!credentials.empty())
   {
     cout << "set_attributes: credentials" << credentials.c_str() << endl;
   } /* end of if(!credentials.empty()) */
  if(!attributes.empty())
   {
     cout << "set_attributes:policy" << attributes.c_str() << endl;
   } /* end of if(!credentials.empty()) */
}



/*
 * 
 * 
 *           The Configuration
 *
 * 
 */


/** @brief Reread the configuration files
 *  @param credentials The credentials of the entity making the request
 *  @param reason      The reason for pausing the sensor
 *   
 *  Often used after and administrator has changed values, or after
 *  a probe has been installed or removed from the machine, causing
 *  the capabilities file to be changed. 
 */
void
STDC::QMS::Citizen::Hello_World_Impl::reload_configuration(string reason, 
						  string credentials)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::reload_configuration",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	"DEBUG: STDC::QMS::Citizen::Hello_World_Impl::reload_configuration\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n",
	 credentials.c_str(), reason.c_str() );
  if(!credentials.empty())
   {
     cout << "reload_configuration: credentials" << credentials.c_str() 
	  << endl;
   } /* end of if(!credentials.empty()) */
  if(!reason.empty())
   {
     cout << "reload_configuration: reason" << reason.c_str() << endl;
   } /* end of if(!credentials.empty()) */
}



/*
 * 
 * 
 *           The Control Interface
 *
 * 
 */




/** @brief Start the sensor
 *  @param credentials The credentials of the entity making the request
 */
void
STDC::QMS::Citizen::Hello_World_Impl::start(string credentials)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::start", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::start\n");
  DEBUG1(DEBUG_L_ENTER, "DEBUG: Credentials %s\n", credentials.c_str());
  if(!credentials.empty())
   {
     cout << "start: credentials" << credentials.c_str() 
	  << endl;
   } /* end of if(!credentials.empty()) */
}

/** @brief Pause the sensor temporarily
 *  @param credentials The credentials of the entity making the request
 *  @param reason      The reason for pausing the sensor
 *  @param ack         The out parameter where the response is sent in
 *
 *  Unless the sensor is running, this is a no op.
 */
void
STDC::QMS::Citizen::Hello_World_Impl::pause(const char * reason, 
				   const char * credentials, 
				   CORBA::Short_out ack)
  ACE_THROW_SPEC ((STDC::QMS::QMS_Error, CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::pause", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::pause\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n",
	 credentials, reason );
  ACE_TRY
    {
      if(credentials)
       {
	 cout << "reload_configuration: credentials" << credentials 
	      << endl;
       } /* end of if(!credentials) */
      if(reason)
       {
	 cout << "reload_configuration: reason" << reason << endl;
       } /* end of if(!credentials) */
      ack = 0;
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "perform_queries");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;  
}

  
/** @brief Resume a previously paused sensor
 *  @param credentials The credentials of the entity making the request
 *  @param reason      The reason for pausing the sensor
 *   
 *  The sensor has to be in a paused state
 */
void
STDC::QMS::Citizen::Hello_World_Impl::resume(const char * reason, 
				    const char * credentials, 
				    CORBA::Short_out ack)
  ACE_THROW_SPEC ((STDC::QMS::QMS_Error, CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::resume", __LINE__, 
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::resume\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n",
	 credentials, reason );
  ACE_TRY
    {
      if(credentials)
       {
	 cout << "reload_configuration: credentials" << credentials 
	      << endl;
       } /* end of if(!credentials.empty()) */
      if(reason)
       {
	 cout << "reload_configuration: reason" << reason << endl;
       } /* end of if(!credentials.empty()) */
      ack = 0;
      ACE_TRY_CHECK; 
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "perform_queries");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;  
}


/** @brief Stop the sensor
 *  @param credentials The credentials of the entity making the request
 *  @param reason      The reason for pausing the sensor
 *   
 */
void
STDC::QMS::Citizen::Hello_World_Impl::stop(const char *reason, 
				  const char *credentials, 
				  CORBA::Short_out ack)
  ACE_THROW_SPEC ((STDC::QMS::QMS_Error, CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::stop", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::stop\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n",
	 credentials, reason );
  ACE_TRY
    {
      if(credentials)
       {
	 cout << "reload_configuration: credentials" << credentials 
	      << endl;
       } /* end of if(!credentials.empty()) */
      if(reason)
       {
	 cout << "reload_configuration: reason" << reason << endl;
       } /* end of if(!credentials.empty()) */
      ack = 0;
      ACE_TRY_CHECK; 
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "perform_queries");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}

/*
 * 
 * 
 *           The Command Interface
 *
 * 
 */


/**
 * @brief Initial connection to the event channel
 * @param reason The reason given for the command
 * @param credentials The security credentials 
 * @param ACE_TRY_ENV The CORBA exception environment
 *
 * Essentially, we walk down the list of extant probes, creating, in
 * turn, announce channel push suppliers, request channel push
 * consumers, data channel push suppliers. After that, we walk down
 * the list of probes again and connect all these push suppliers and
 * consumers. 
 */
void 
STDC::QMS::Citizen::Hello_World_Impl::connect_EC (string credentials)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::connect_EC", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::connect_EC\n");
  DEBUG1(DEBUG_L_ENTER, 
	 "DEBUG: Credentials %s\n", credentials.c_str() );
  if(!credentials.empty())
   {
     cout << "reload_configuration: credentials" << credentials.c_str() 
	  << endl;
   } /* end of if(!credentials.empty()) */
  std::map<std::string, STDC::QMS::Citizen::Hello_World_Meta_Data *>::iterator pos;
   for(pos = this->probes_.begin(); pos != this->probes_.end(); ++pos)
    {
      pos->second->create_announce_suppliers(this->_supplier_id, 
                                           this->handles_p_);
      pos->second->create_request_consumers(this->handles_p_);
      pos->second->create_data_suppliers(this->_supplier_id, 
                                       this->handles_p_);
   
      pos->second->connect_announce_suppliers();
      pos->second->connect_request_consumers();
      pos->second->connect_data_suppliers();
    }
}
/**
 * @brief make YP_Offers for the probes
 * @param reason The reason given for the command
 * @param credentials The security credentials 
 * @param ACE_TRY_ENV The CORBA exception environment
 *
 * We walk down the list of probes and have each meta data object make
 * a yellow pages offer for its underlying probe.
 */
void 
STDC::QMS::Citizen::Hello_World_Impl::probe_offers (string credentials)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::probe_offers", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::probe_offers\n");
  DEBUG1(DEBUG_L_ENTER, 
	 "DEBUG: Credentials %s\n", credentials.c_str() );
  if(!credentials.empty())
   {
     cout << "reload_configuration: credentials" << credentials.c_str() 
	  << endl;
   } /* end of if(!credentials.empty()) */
  std::map<std::string, STDC::QMS::Citizen::Hello_World_Meta_Data *>::iterator pos;
   for(pos = this->probes_.begin(); pos != this->probes_.end(); ++pos)
    {
      pos->second->yp_offer(this->obj_.in(), this->handles_p_);
    }
}

/** @brief Disconnect from the event channel
 *  @param reason The reason given for the command
 *  @param credentials The security credentials 
 *  @param ACE_TRY_ENV The CORBA exception environment
 */
void
STDC::QMS::Citizen::Hello_World_Impl::disconnect_EC (const char * reason, 
			       const char * credentials)
  ACE_THROW_SPEC ((STDC::QMS::Citizen::QMS_Citizen_Error, 
                   CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::disconnect_EC", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::disconnect_EC\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n",
	 credentials, reason );
  ACE_TRY
    {
      if(credentials)
       {
	 cout << "reload_configuration: credentials" << credentials
	      << endl;
       } /* end of if(!credentials.empty()) */
      if(reason)
       {
	 cout << "reload_configuration: reason" << reason << endl;
       } /* end of if(!credentials.empty()) */
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "perform_queries");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;  

}

  
/** @brief Reconnect to the event channel
 *  @param reason The reason given for the command
 *  @param EC_Name The event Channel name to use
 *  @param credentials The security credentials 
 *  @param ACE_TRY_ENV The CORBA exception environment
 */
void
STDC::QMS::Citizen::Hello_World_Impl::reconnect_EC (const char * reason, 
			      const char * EC_Name,
			      const char * credentials)
  ACE_THROW_SPEC ((STDC::QMS::Citizen::QMS_Citizen_Error, 
                   CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::reconnect_EC", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::reconnect_EC\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n",
	 credentials, reason );
  ACE_TRY
    {
      if(credentials)
       {
	 cout << "reconnect_EC: credentials" << credentials
	      << endl;
       } /* end of if(!credentials.empty()) */
      if(reason)
       {
	 cout << "reconnect_EC: reason" << reason << EC_Name 
	      << endl;
       } /* end of if(!credentials.empty()) */
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "perform_queries");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;  
}

/** @brief Show the current operating level
 *  @param level result
 *  @param ACE_TRY_ENV The CORBA exception environment
 */
void
STDC::QMS::Citizen::Hello_World_Impl::show_operating_level (CORBA::Short_out 
							    level)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::show_operating_level",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::show_operating_level\n");
  level = this->level_;
}

  
/** @brief Set the current operating level
 *  @param level The desired operating level
 *  @param credentials The security credentials of the requesting entity
 *  @param ACE_TRY_ENV The CORBA exception environment
 */
void
STDC::QMS::Citizen::Hello_World_Impl::set_operating_level (CORBA::Short level,
				     const char * credentials)
  ACE_THROW_SPEC ((STDC::QMS::Citizen::QMS_Citizen_Error,
                   CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::set_operating_level",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::set_operating_level\n");
  DEBUG1(DEBUG_L_ENTER, "DEBUG: Credentials %s\n", credentials);
  ACE_TRY
    {
      if(credentials)
       {
	 cout << "reload_configuration: credentials" << credentials 
	      << endl;
       } /* end of if(!credentials.empty()) */
      if(level > 0)
       {
	 this->level_ = level;
       } /* end of if(level > 0) */
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "perform_queries");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;  

}

/** @brief Dump the statistics of the program
 *  @param ACE_TRY_ENV The CORBA exception environment
 *  @param credentials The security credentials of the requesting entity
 *  @param stats The requested statistics
 */
void
STDC::QMS::Citizen::Hello_World_Impl::stats (const char * credentials,
					     CORBA::String_out stats)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::stats", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::stats\n");
  DEBUG1(DEBUG_L_ENTER, "DEBUG: Credentials %s\n", credentials);
  if(credentials)
   {
     cout << "reload_configuration: credentials" << credentials 
	  << "version" << version
	  << endl;
   } /* end of if(!credentials.empty()) */
  stats = "No Stats\n";
}


/** @brief Send back an I-am-alive
 *  @param ack set to 1 in the call
 *
 * This is a basic, rapid, acknowledgement
 */
void
STDC::QMS::Citizen::Hello_World_Impl::ping (CORBA::Short_out ack)
  ACE_THROW_SPEC ((STDC::QMS::Citizen::QMS_Citizen_Error,
                   CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::ping", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::ping\n");
  ack = 1;
}


/*
 * 
 * 
 *           The Naming Service
 *
 * 
 */

/**
 * @brief register the object with the CORBA naming service
 * @param *name_p The name to use at the leaf level registration
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * We register this sensor under /stdc/QMS/Instrumentation/Sensor/HelloWorld
 * This routine handles cases where parts of the path may already be
 * already bound.
 */
void 
STDC::QMS::Citizen::Hello_World_Impl::register_with_naming(CORBA::Environment 
							   &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::register_with_naming", 
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::register_with_naming");
  if(this->_registered)
   {
     return;
   } /* end of if(this->_registered) */
  
  if(!this->handles_p_)
   {
     throw STDC::QMS::QMS_Error();
   } /* end of if(!this->handles_p_) */

  CosNaming::Name name (1);
  CosNaming::NamingContext_ptr init_context_p = 
    this->handles_p_->get_naming_handle().in();
  CosNaming::NamingContext_var stdc_context_p = 
    init_context_p->new_context();

  CosNaming::NamingContext_var qms_context_p;
  CosNaming::NamingContext_var instr_context_p;
  CosNaming::NamingContext_var sensor_context_p;
  CosNaming::NamingContext_var generic_context_p;

  // Bind STDC to the Naming Context
  name.length (1);
  name[0].id = CORBA::string_dup ("STDC");
  
  // We need to verify that the recovery process is adequate, perhaps
  // we need to resolve the context when we get an already bound
  // exception? 

  ACE_TRY
    {
      stdc_context_p = init_context_p->bind_new_context (name);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
    {
      ACE_PRINT_EXCEPTION (ex, "STDC: name service already bound :(ignored)");
      ACE_TRY_ENV.clear();
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:STDC");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
 
  ACE_TRY
    {
      name.length (2);
      name[1].id = CORBA::string_dup ("QMS");
      qms_context_p = init_context_p->bind_new_context (name);
    }
  ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
    {
      ACE_PRINT_EXCEPTION (ex, "QMS-name service context already bound :(ignored)");
      ACE_TRY_ENV.clear();
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:QMS");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
 
  ACE_TRY
    {
      name.length (3);
      name[2].id = CORBA::string_dup ("Instrumentation");
      instr_context_p = init_context_p->bind_new_context (name);
    }
  ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
    {
      ACE_PRINT_EXCEPTION (ex, 
			   "Instrumentation -NS context already bound :(ignored)");
      ACE_TRY_ENV.clear();
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:Instrumentation");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
 
  ACE_TRY
    {
      name.length (4);
      name[3].id = CORBA::string_dup ("Sensor");
      sensor_context_p = init_context_p->bind_new_context (name);
    }
  ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
    {
      ACE_PRINT_EXCEPTION (ex, "Sensor:NS context already bound :(ignored)");
      ACE_TRY_ENV.clear();
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:Sensor");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
 
  ACE_TRY
    {
      name.length (5);
      name[4].id = CORBA::string_dup ("HelloWorld");
      generic_context_p = init_context_p->bind_new_context (name);
    }
  ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
    {
      ACE_PRINT_EXCEPTION (ex, "HelloWorld:NS context already bound :(ignored)");
      ACE_TRY_ENV.clear();
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:Sensor");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
 


  ACE_TRY
    {  
      // Bind Status to the Naming Context
      name.length (6);

      string identity;
      identity.assign(this->config.offer_prop.QMSUniqueName.category);
      identity.append(":");
      identity.append(this->config.offer_prop.QMSUniqueName.host);
      identity.append(":");
      identity.append(this->config.offer_prop.QMSUniqueName.uuid);
      
      name[5].id = CORBA::string_dup (identity.c_str());
      DEBUG1(6,"DEBUG: Registering as %s\n", identity.c_str());
      
      init_context_p->rebind (name, this->obj_.in(), ACE_TRY_ENV);
      ACE_TRY_CHECK; 
    }
  ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
    {
      ACE_PRINT_EXCEPTION (ex, "name service already bound : YIKES");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :YIKES");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :YIKES");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:YIKES");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
  this->_registered = true;
}

// Not yet implemented
void 
STDC::QMS::Citizen::Hello_World_Impl::unregister_with_naming(CORBA::Environment
							     &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::unregister_with_naming",
	    __LINE__,__FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::unregister_with_naming");
  if(!this->handles_p_)
   {
     throw STDC::QMS::QMS_Error();
   } /* end of if(!this->handles_p_) */
  if(!this->_registered)
   {
     return;
   } /* end of if(!this->_registered) */
  ACE_TRY
    {  
      CosNaming::Name name (1);
      CosNaming::NamingContext_ptr init_context_p = 
	this->handles_p_->get_naming_handle().in();
      CosNaming::NamingContext_var stdc_context_p = 
	init_context_p->new_context();
      
      name.length (6);
      name[0].id = CORBA::string_dup ("STDC");
      name[1].id = CORBA::string_dup ("QMS");
      name[2].id = CORBA::string_dup ("Instrumentation");
      name[3].id = CORBA::string_dup ("Sensor");
      name[4].id = CORBA::string_dup ("HelloWorld");
      string identity;
      identity.assign(this->config.offer_prop.QMSUniqueName.category);
      identity.append(":");
      identity.append(this->config.offer_prop.QMSUniqueName.host);
      identity.append(":");
      identity.append(this->config.offer_prop.QMSUniqueName.uuid);
      
      name[5].id = CORBA::string_dup (identity.c_str());
      DEBUG1(6,"DEBUG: Unregistering %s\n", identity.c_str());
      
      init_context_p->unbind (name, ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CosNaming::NamingContext::AlreadyBound, ex)
    {
      ACE_PRINT_EXCEPTION (ex, "name service already bound : YIKES");
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :YIKES");
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :YIKES");
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:YIKES");
    }
  ACE_ENDTRY;
  this->_registered = false;
}

/*
 * 
 * 
 *           The Trading service
 *
 * 
 */


/** @brief Update the Sensors registration with the trading and
 *  fault detection services
 *  @param credentials The credentials of the entity making the request
 *  @param reason      The reason for pausing the sensor
 */
void
STDC::QMS::Citizen::Hello_World_Impl::update_registration(string reason,
							  string credentials)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::update_registration", 
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::update_registration\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n",
	 credentials.c_str(), reason.c_str() );
  
  if(!credentials.empty())
   {
     cout << "reload_configuration: credentials" << credentials.c_str() 
	  << endl;
   } /* end of if(!credentials.empty()) */
  if(!reason.empty())
   {
     cout << "reload_configuration: reason" << reason.c_str() << endl;
   } /* end of if(!credentials.empty()) */
}


/**
 * @brief Withdraw the yellow pages offer made for the sensor
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 * 
 * We use the offer ID stashed away when me made the YP offer to
 * withdraw the ypoffer from the CORBA Trading service
 */
void
STDC::QMS::Citizen::Hello_World_Impl::withdraw_offer(CORBA::Environment 
						     &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::withdraw_offer", __LINE__, 
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::withdraw_offer\n");
  if(!this->_offer_created)
   {
     return;
   } /* end of if(!this->_offer_created) */
  
  ACE_TRY
    {
      CosTrading::Lookup_var lookup_var =
	this->handles_p_->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CosTrading::Register_var reg_var = lookup_var->register_if();
      if(CORBA::is_nil(reg_var.in()))
       {
	 cerr << "trader does not support updates" << endl;
	 throw STDC::QMS::QMS_Error();
       } /* end of if(CORBA::is_nil(reg_var)) */

      reg_var->withdraw(this->offer_id.in(), ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
  {
    ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error withdrawING yp offer");
    ACE_RE_THROW;
  }
  ACE_ENDTRY;
  this->_offer_created = false;
}

/**
 * @brief Make a yellow Pages offer for the sensor
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 * 
 * This function handles the nitty gritty details of making an offer,
 * but does not concern itself with service types. Please look at the
 * function yp_offer() below, which drives the process, to see how
 * service types are handled.
 *
 * First, we need to determine the number of properties we need in the
 * offer that we make. We need a certain number of fixed properties: 
 *
 *          - QMSUniqueName category
 *          - QMSUniqueName host  
 *          - QMSUniqueName uuid
 *          - CORBA IDL Version
 *          - Description
 *          - URI of the Schema we shall be using for messages
 *
 * And to these fixed properties we have to add however many optional
 * offer parameters we have. Adding to the complexity is the fact that
 * some of the offer parameters are going to be mapped to predefined
 * property names in order to be searchable; and these offer
 * parameters need to be listed twice (once with a predetermined
 * generic property name for searcheability, a second time with a more
 * descriptive name to allow for discovery.and for readability.
 *
 * In order to accomplish this, we make a first pass over the offer
 * parameters, counting the parameters, and counting searchable
 * parameters twice.
 *
 * Next, we create a property struct, and fill in the fixed properties
 * detailed above. After that, we walk down the list of offer
 * parameters, looking for the searchable flag, and create the
 * properties, mapping them to the fixed names appropriately. Finally,
 * we make our third pass down the offer parameters, filling in the
 * property names and values.
 *
 * Finally, we register an offer with the CORBA trading service.
 */

void
STDC::QMS::Citizen::Hello_World_Impl::make_offer(CORBA::Environment 
						 &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::make_offer", __LINE__, 
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::make_offer\n");
  ACE_TRY
    {
      CosTrading::Lookup_var lookup_var =
	this->handles_p_->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CosTrading::Register_var reg_var = lookup_var->register_if();
      if(CORBA::is_nil(reg_var.in()))
       {
	 cerr << "trader does not support updates" << endl;
	 throw STDC::QMS::QMS_Error();
       } /* end of if(CORBA::is_nil(reg_var)) */

      CosTrading::PropertySeq props;
      // We need a number of fixed property names:
      //  (a) QMSUniqueName category
      //  (b) QMSUniqueName host 
      //  (c) QMSUniqueName uuid
      //  (d) CORBA IDL Version
      //  (e) Description
      //  (f) QMS Schema URI
      // Add to that however many optional offers params we have
      
      // Count the parameters we have
      int count = 6;
      STDC::QMS::optionalOfferType::const_iterator offers;
      for(offers  = this->config.offer_param.begin(); 
	  offers != this->config.offer_param.end(); 
	  offers++)
       {
	 count ++;
	 if(offers->searchable)
	  {
	    count ++;
	  } /* end of if(offers->searchable) */
       }
      int maxcount = count;
    
      props.length(maxcount);

      count = 0 ;
      
      props[count].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
      props[count].value <<= 
	this->config.offer_prop.QMSUniqueName.category.c_str();

      count++;
      
      props[count].name  = CORBA::string_dup ("QMS_UNIQ_NAME_HOST_NAME");      
      props[count].value <<= 
	this->config.offer_prop.QMSUniqueName.host.c_str();  
      
      count++;
      
      props[count].name  = CORBA::string_dup ("QMS_UNIQ_NAME_UUID");
      props[count].value 
	<<= this->config.offer_prop.QMSUniqueName.uuid.c_str();
      
      count++;
      
      props[count].name  = CORBA::string_dup ("VERSION");
      props[count].value <<= this->config.corba_prop.interfaceVersion.c_str(); 

      count++;
      
      props[count].name  = CORBA::string_dup ("DESCRIPTION");
      props[count].value <<= 
	this->config.corba_prop.interfaceDescription.c_str();
      
      count++;
      
      props[count].name  = CORBA::string_dup ("QMS_SCHEMA_URI");
      props[count].value <<= this->config.QMS_Schema.c_str();
      
      count++;
      
      for(offers  = this->config.offer_param.begin(); 
	  offers != this->config.offer_param.end(); 
	  offers++)
       {
	 if(offers->searchable  && !offers->variable.value.empty())
	  {
	    if(offers->maptoProperty != INT_MAX  &&
	       offers->maptoProperty <= 10) 
	     {
	       props[count].name  = 
		 CORBA::string_dup (propnames[offers->maptoProperty]);
	       props[count].value <<= offers->variable.value.c_str();
	       count ++;
	     }
	  }
       }
      
      for(offers  = this->config.offer_param.begin(); 
	  offers != this->config.offer_param.end(); 
	  offers++)
       {
	 if(!offers->variable.name.empty()  && 
	    !offers->variable.value.empty())
	  {
	    props[count].name  = 
	      CORBA::string_dup (offers->variable.name.c_str());
	    props[count].value <<= offers->variable.value.c_str();
	    count ++;
	  }
       }

      this->offer_id  = reg_var->_cxx_export(this->obj_.in(),
					     "STDC_QMS_CITIZEN_HW_SENSOR",
					     props, ACE_TRY_ENV);
      ACE_TRY_CHECK;
      
    }
  ACE_CATCH (CosTrading::UnknownServiceType, excp)    
    {
      cerr <<  "DEBUG: No service type While trying to make an Sensor offer"
	   <<endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::IllegalPropertyName, excp)
    {
      cerr << "DEBUG: IllegalPropertyName" <<endl;
      ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType-IllegalPropertyName");
      
      if (excp.name.in () != 0)
	cerr << "IllegalPropertyName : " << excp.name.in () <<endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition, vtr)
    {
      cerr <<  "DEBUG: ValueTypeRedefinition\n" << endl;
      ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType -ValueTypeRedefinition");
      
      if (vtr.type_1.in () != 0)
	cerr << "Type One: " << vtr.type_2.in () << endl;
      if (vtr.type_2.in () != 0)
	cerr << "Type Two: " << vtr.type_2.in () << endl;
      ACE_RE_THROW;
    }
  ACE_CATCHANY
  {
    cerr <<  "DEBUG: Error making yp offer\n";
    ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
    ACE_RE_THROW;
  }
  ACE_ENDTRY;
}

/**
 * @brief The driving function for making yellow page offers
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 * 
 * This method is all about handling exceptions and error
 * conditions. First, if the yp_offer has already been create4d, we
 * just return, making this function idempotent. If tghat is not the
 * case, we just go ahead and make an offer, using make_offer()
 * above. If that works, fine. If it throws an unexpected exceptoin,
 * we just allow that to bubble up. 
 *
 * However, if we get an unknown service type exception, we note that,
 * and proceed to make a STDC::QMS::Add_YP_ServiceType() call, which
 * adds the STDC::QMS::Citizen service type to the CORBA Trading
 * service. We ignore errors to the effect that this service type was
 * alredy known. 
 *
 * Next, we make a STDC::QMS::Add_YP_SubType() call to add our own
 * service subtype to the type repository.
 *
 * Finally, we make the offer again, using make_offer(), and this time
 * it should go through, since the service types have just been added.
 */
void
STDC::QMS::Citizen::Hello_World_Impl::yp_offer(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::yp_offer", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::yp_offer\n");
  bool retry = true;
  bool no_yp_service = false;
  if(this->_offer_created)
   {
     return;
   } /* end of if(this->_offer_created) */
  
  ACE_TRY
    {
      make_offer(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      retry = false;
    }
  ACE_CATCH (CosTrading::UnknownServiceType, excp)    
    {
      cerr << "DEBUG: No service type (ignored -- need to add service type)"
	   << endl;
      no_yp_service = true;
      ACE_TRY_ENV.clear ();
    }
  ACE_CATCH (CosTrading::PropertyTypeMismatch, excp)    
    {
      cerr << "DEBUG: Property type mismatch\n";
       if (excp.type.in () != 0)
	 cerr << "Invalid type: " << excp.type.in () << endl;
       if(excp.prop.name.in())
	{
	  cerr << "Invalid property name : " << excp.prop.name.in () << endl;
	} /* end of if(excp.something.name.in()) */
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::IllegalPropertyName, excp)
    {
      cerr << "DEBUG: IllegalPropertyName\n";
      ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType-IllegalPropertyName");
      
      if (excp.name.in () != 0)
	cerr << "Illegal Property  name: " << excp.name.in () << endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition, vtr)
    {
      cerr << "DEBUG: ValueTypeRedefinition\n";
      ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType -ValueTypeRedefinition");
      
      if (vtr.type_1.in () != 0)
	cerr << "Type One: " << vtr.type_2.in () << endl;
      if (vtr.type_2.in () != 0)
	cerr << "Type Two: " << vtr.type_2.in () << endl;
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      cerr << "DEBUG: Yikes. Another unexpected exception\n";
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  if(no_yp_service)
   {
     ACE_TRY
       {
	 STDC::QMS::Add_YP_ServiceType(this->handles_p_, ACE_TRY_ENV);
	 ACE_TRY_CHECK;      
       }
     ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ServiceTypeExists, ste)
       {
	 ACE_PRINT_EXCEPTION (ste, "Adding YP_ServiceType");
	 
	 if (ste.name.in () != 0)
	   cerr << "Service Type Exists: (ignored)" << ste.name.in () << endl;
	 ACE_TRY_ENV.clear ();
       }
     ACE_CATCH (CosTrading::IllegalPropertyName, excp)
       {
	 ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType");
	 
	 if (excp.name.in () != 0)
	   cerr << "IllegalPropertyName,: " << excp.name.in () << endl;
	 ACE_RE_THROW;
       }
     ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
		vtr)
       {
	 ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType");
	 
	 if (vtr.type_1.in () != 0)
	   cerr << "Type One: " << vtr.type_2.in () << endl;
	 if (vtr.type_2.in () != 0)
	   cerr << "Type Two: " << vtr.type_2.in () << endl;
	 ACE_RE_THROW;
       }
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
     
     ACE_TRY
       {
	 STDC::QMS::Add_YP_SubType(this->handles_p_, 
				   "STDC_QMS_CITIZEN_HW_SENSOR",
				   this->_interface_repository_id(),
				   ACE_TRY_ENV);
	 ACE_TRY_CHECK;      
       }
     ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ServiceTypeExists, ste)
       {
	 ACE_PRINT_EXCEPTION (ste, "Adding Generic Sensor ServiceType");
	 
	 if (ste.name.in () != 0)
	   cerr << "ServiceTypeExists: " << ste.name.in () << endl;
	 ACE_RE_THROW;
       }
     ACE_CATCH (CosTrading::IllegalPropertyName, excp)
       {
	 ACE_PRINT_EXCEPTION (excp, "Adding Generic Sensor ServiceType");
	 
	 if (excp.name.in () != 0)
	   cerr << "Illegal Property name: " << excp.name.in () << endl;
	 ACE_RE_THROW;
       }
     ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
		vtr)
       {
	 ACE_PRINT_EXCEPTION (vtr, "Adding Generic Sensor ServiceType");
	 
	 if (vtr.type_1.in () != 0)
	   cerr << "Type One: " << vtr.type_2.in () << endl;
	 if (vtr.type_2.in () != 0)
	   cerr << "Type Two: " << vtr.type_2.in () << endl;
	 ACE_RE_THROW;
       }
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
     
       
   } /* end of if(no_yp_service) */
  
  ACE_TRY
    {
      if(retry)
       {
	 make_offer(ACE_TRY_ENV);
	 ACE_TRY_CHECK;
       } /* end of if(retry) */      
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  this->_offer_created = true;
}

/**
 * @brief Get a reference to the QMS Trader ECInfo component
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * First, if we already have a handle on the QMS Trader component, we
 * return immediately. If not, we query the CORBA Trading service for
 * the YP offer of the EC Info component, narrow it down, and stash
 * the object reference away.
 */
void
STDC::QMS::Citizen::Hello_World_Impl::get_ec_registry(CORBA::Environment 
						      &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::get_ec_registry", 
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::get_ec_registry\n");
  if(!CORBA::is_nil(this->_ec_registry.in()))
   {
     return;
   } /* end of if(!CORBA::is_nil(this->_ec_registry)) */
  
  ACE_TRY
    {
      CosTrading::Lookup_var lookup_var =
	this->handles_p_->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CosTrading::Lookup_ptr lookup_p = lookup_var.in();
      assert(lookup_p);
      assert(!CORBA::is_nil(lookup_p));

      // Perparing to do an import operation.  Should some of these go
      // into the sensor object itself?
      PolicySeq policies;	             //empty sequence

      CosTrading::Lookup::SpecifiedProps desired_props;  // No properties
      desired_props._d(Lookup::all);         // Return all properties

      CosTrading::PolicyNameSeq_var policies_applied;      // out param
      CosTrading::OfferSeq *offer_seq_ptr = 0; // out param
      CosTrading::OfferSeq_out offer_seq_out (offer_seq_ptr);
      CosTrading::OfferIterator_var iterator;              // out param

      // We ask for a single result to be returned, since we
      // essentially want the first ec registry object. This
      // simplifies the code; however, if  needed, we can go through
      // and iterate over all offers.
      lookup_p->query("STDC_QMS_CITIZEN_QMS_TRADER",    // IN string
		      "QMS_UNIQ_NAME_CATEGORY == 'QMS_TRADER' ", // IN contraint 
		      "",                             // IN preferences
		      policies,                       // IN policies
		      desired_props,                  // IN desired properties
		      1,                              // IN how many
		      offer_seq_out,                  // OUT Offers
		      iterator,                       // OUT Iterator
		      policies_applied                // OUT policies applied
		      );
      ACE_TRY_CHECK;

      // Processing the results
      if(offer_seq_out->length() == 0)
       {
	 cerr << "No Trader Offers found" << endl;
	 ACE_TRY_THROW (CORBA::BAD_PARAM ());
       } /* end of if(offer_seq_out->length() == 0) */
      else
       {
	 // Extract asn object reference
	 const CosTrading::OfferSeq& offer_seq = *offer_seq_ptr;
	 this->_ec_registry = 
	   STDC::QMS::Citizen::QMS_Trader_ECInfo::_narrow(offer_seq[0].reference);
	 if(CORBA::is_nil(this->_ec_registry.in()))
	  {
	    cerr << "Service provider is not an ec registry" << endl;
	    ACE_TRY_THROW (CORBA::BAD_PARAM());
	  } /* end of if(CORBA::is_nil(this->_ec_registry)) */
       } /* end of else */
      if (!CORBA::is_nil(iterator.in()))
       {
	 iterator->destroy();
	 ACE_TRY_CHECK;
       }
    }
  ACE_CATCH (CosTrading::IllegalConstraint, constex)
    {
      ACE_PRINT_EXCEPTION (constex, 
			   "Illegal Constraint getting QMS_Trader_ECInfo:");
      if (constex.constr.in () != 0)
        cerr << "Illegal Constraint: " << constex.constr.in () << endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex,
			   "System Exception getting QMS_Trader_ECInfo:");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, 
			   "User Exception getting QMS_Trader_ECInfo:");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
			   "Error getting QMS_Trader_ECInfo");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;  
}

/**
 * @brief Get a supplier ID using the QMS Trader
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * We invoke the getSupplierID method on the QMS Trader ECInfo
 * object.  Please note that there is only one supplier ID for the
 * sensor as a whole, not one per probe.
 */
void
STDC::QMS::Citizen::Hello_World_Impl::get_supplier_id(CORBA::Environment 
						      &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::get_supplier_id", 
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Impl::get_supplier_id\n");
  

  ACE_TRY
    {
      if(CORBA::is_nil(this->_ec_registry.in()))
       {
	 this->get_ec_registry(ACE_TRY_ENV);
	 ACE_TRY_CHECK;
       } /* end of if(CORBA::is_nil(this->_ec_registry)) */
      string identity;
      identity.assign(this->config.offer_prop.QMSUniqueName.category);
      identity.append(":");
      identity.append(this->config.offer_prop.QMSUniqueName.host);
      identity.append(":");
      identity.append(this->config.offer_prop.QMSUniqueName.uuid);

      this->_supplier_id =
	this->_ec_registry->getSupplierID(identity.c_str());
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error Getting Suppkier ID");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}


/**
 * @brief Get event channel information for all probes
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * We walk down the list of current probes, and add a handle to the
 * QMS Trader EC info object to each metadata object. Then we get
 * event channel information for all probes.
 */
void
STDC::QMS::Citizen::Hello_World_Impl::get_ECInfo(CORBA::Environment 
						 &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::get_ECInfo", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:  STDC::QMS::Citizen::Hello_World_Impl::get_ECInfo\n");
  ACE_TRY
    {
     if(CORBA::is_nil(this->_ec_registry.in()))
       {
	 this->get_ec_registry(ACE_TRY_ENV);
	 ACE_TRY_CHECK;
       } /* end of if(CORBA::is_nil(this->_ec_registry)) */
     std::map<std::string, STDC::QMS::Citizen::Hello_World_Meta_Data *>::iterator pos;
     for(pos = this->probes_.begin(); pos != this->probes_.end(); ++pos)
      {
	pos->second->add_ec_registry(this->_ec_registry);
	pos->second->get_EC_info();
      }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "perform_queries");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}

/*
 * 
 * 
 *           The XML interfaces
 *
 * 
 */


/**
 * @brief Return true of errors were encountered during parsing
 */
inline bool IDOMTreeErrorReporter::getSawErrors() const
{
  return fSawErrors;
}

/*
 * enum NodeType {
 *      ELEMENT_NODE                = 1,
 *      ATTRIBUTE_NODE              = 2,
 *      TEXT_NODE                   = 3,
 *      CDATA_SECTION_NODE          = 4,
 *      ENTITY_REFERENCE_NODE       = 5,
 *      ENTITY_NODE                 = 6,
 *      PROCESSING_INSTRUCTION_NODE = 7,
 *      COMMENT_NODE                = 8,
 *      DOCUMENT_NODE               = 9,
 *      DOCUMENT_TYPE_NODE          = 10,
 *      DOCUMENT_FRAGMENT_NODE      = 11,
 *      NOTATION_NODE               = 12,
 *      XML_DECL_NODE               = 13
 *  };
 */


/**
 * @brief Initialize an XML Parser
 * 
 * This has to be done before the first invocation of the parser.
 */
void
STDC::QMS::Citizen::Hello_World_Impl::init_parser()
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::init_parser",__LINE__, 
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::init_parser");
  // Initialize the Parser. 
  try 
   {
     XMLPlatformUtils::Initialize();
   }
  catch(const XMLException& toCatch)
   {
     cerr << "Error during Xerces-c Initialization.\n"
          << "  Exception message:"
          << toCatch.getMessage()
          << endl;
     throw STDC::QMS::QMS_Error();
   }
  this->_parser_initialized = true;
}

/**
 * @brief Cleanup the parser we created
 * 
 * This has to be done after we are all done with the parsers that
 * were used.
 */
void 
STDC::QMS::Citizen::Hello_World_Impl::parser_cleanup(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::parser_cleanup",__LINE__, 
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::parser_cleanup\n");
  // Terminate the parser before the end. This belongs in a destructor
  if(!this->_parser_initialized)
   {
     return;
   } /* end of if(!this->_parser_initialized) */
  
  try 
   {
     XMLPlatformUtils::Terminate();
     this->_parser_initialized = false;
   }
  catch(const XMLException& toCatch)
   {
     cerr << "Error during Xerces-c termination.\n"
          << "  Exception message:"
          << toCatch.getMessage()
          << endl;
   }
  catch (...)
   {
     cerr << "Error during Xerces-c termination.\n";
   }
  DEBUG0(4, "DEBUG:parser_cleanup done\n");
}

/**
 * @brief Parse the configuration file
 * @param file_name_p The path for the configuration file
 * @return true if the parse was succesfull.
 *
 * We create a new parser for the confg file, and we pass in the file name
 * to parse.
 */
bool 
STDC::QMS::Citizen::Hello_World_Impl::parse_config(char * file_name_p)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::parse_config",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::parse_config");
  if(file_name_p)
   {
     STDC::QMS::Parse_XML *parser_p =new STDC::QMS::Parse_XML();
     return parser_p->parse_config(file_name_p, this->config);
   } /* end of if(file_name_p) */  
  else
   {
     cerr << "Error during parsing configuration file -- empty file name\n"
	  << endl;
   } /* end of else */  
  return false;
}

/**
 * @brief A diagnostic function that prints out message related structs
 * @param config Message header data
 * @param request_data Message payload data
 * 
 * This is not used in general use, but may be helpful in diagnosing
 * problems with a new message format.
 */
void
print_message_data(STDC::QMS::QMSMessage &config, 
		   struct hw_payload_data &request_data)
{
   QMS_Trace("print_message_data", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG:print_message_data\n");
  cerr << "DEBUG: Message data" << std::endl
       << "config.sequence_no = " << config.sequence_no  << std::endl
       << "config.msgDate= " << config.msgDate << std::endl
       << "config.msgTime= " << config.msgTime << std::endl
       << "config.sender_host= " << config.sender_host << std::endl
       << "config.sender.id = " << config.sender.id  << std::endl
       << "config.sender.description= " << config.sender.description
       << std::endl
       << "config.QMSUniqueName.category= " << config.QMSUniqueName.category
       << std::endl
       << "config.QMSUniqueName.host= " << config.QMSUniqueName.host 
       << std::endl
       << "config.QMSUniqueName.uuid= " << config.QMSUniqueName.uuid
       << std::endl
       << "config.Session.request_id = " << config.Session.request_id 
       << std::endl
       << "config.Session.data_id = " << config.Session.data_id  << std::endl
       << "config.Session.version = " << config.Session.version  << std::endl
       << "config.Session.repititions.count = " 
       << config.Session.repititions.count  << std::endl
       << "config.Session.repititions.current = "
       << config.Session.repititions.current  << std::endl
       << "config.Session.interval = " << config.Session.interval.c_str()
       << std::endl
       << "config.Session.scope= " << config.Session.scope << std::endl
       << "config.Session.forceReuse = " << config.Session.forceReuse 
       << std::endl
       << "config.Session.qos_params.Priority = "
       << config.Session.qos_params.Priority  << std::endl
    ;
  
  cerr << "DEBUG: Payload data"  << std::endl
       << "request_data.data.request.firstname = "
       << request_data.data.request.firstname << std::endl
       << "request_data.data.request.lastname = "
       <<  request_data.data.request.lastname << std::endl
       << "request_data.data.request.action = "
       <<  request_data.data.request.action << std::endl
    ;
  
}

/**
 * @brief Handle incoming messages
 * @param query The incoming message
 *
 * This function sets up a general message contents struct,
 * initializes it to default values, and invokes the parser on the
 * message, also including a pointer to a callback function to parse
 * the payload. This function, and the argument to it, are the
 * entities that need to be changed if you are interested in using
 * this sensor as a template for your own sensor object.
 *
 * Please note that as coded, this function assumes unibyte characters,
 */

void
STDC::QMS::Citizen::Hello_World_Impl::handle_query(const string &query)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Impl::handle_query", 
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, 
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Impl::handle_query");

  //
  //  Create MemBufferInputSource from the buffer containing the XML
  //  statements.
  //
  //  NOTE: We are using strlen() here, since we know that the chars in
  //  our hard coded buffer are single byte chars!!! The parameter wants
  //  the number of BYTES, not chars, so when you create a memory buffer
  //  give it the byte size (which just happens to be the same here.)
  //
  char *message_p = (char *)query.data();
  message_p[query.length()] = 0;
  
  
  MemBufInputSource *buffer_p = new MemBufInputSource((const XMLByte*) 
                                                      message_p,
                                                      strlen(message_p),
                                                      "QMSMessage",
                                                      false);
  //
  //  Parse the XML file, catching any XML exceptions that might propogate
  //  out of it.
  //  

  if(buffer_p)
   {
     STDC::QMS::Parse_XML *parser_p = new STDC::QMS::Parse_XML();
     STDC::QMS::QMSMessage config;
     config.sequence_no = INT_MAX;
     config.msgDate.erase();
     config.msgTime.erase();
     config.sender_host.erase();
     config.sender.id = INT_MAX;
     config.sender.description.erase();
     config.QMSUniqueName.category.erase();
     config.QMSUniqueName.host.erase();
     config.QMSUniqueName.uuid.erase();
     config.Session.request_id = INT_MAX;
     config.Session.data_id = INT_MAX;
     config.Session.version = INT_MAX;
     config.Session.repititions.count = 1;
     config.Session.repititions.current = 0;
     config.Session.interval = "PT5S";
     config.Session.scope.erase();
     config.Session.forceReuse = false;
     config.Session.qos_params.Priority = 10;

     struct hw_payload_data request_data;
     // Default values 
     request_data.data.request.firstname.erase();
     request_data.data.request.lastname.erase();
     request_data.data.request.action.erase();

     
     bool parsed_message = parser_p->parse_message(*buffer_p, config, 
						   payload_Handler,
						   (void *) &request_data);
     if(parsed_message)
      {
	if(!config.QMSUniqueName.category.empty())
	 {
	   STDC::QMS::Citizen::Hello_World_Meta_Data * probe_p = 
	     this->probes_[config.QMSUniqueName.category];
	   if(probe_p)
	    {
	      probe_p->handle_query(query, config, request_data);
	    } /* end of if(probe_p) */
	   else
	    {
	      cerr << "ERROR: Recieved a request for category " 
		   << config.QMSUniqueName.category << std::endl
		   << "Which I do not have any knowledge of." << std::endl
		   << "\tAborting" << std::endl
		   << query;
	      print_message_data(config, request_data);
	      
	    } /* end of else */
	 } /* end of if(!config.QMSUniqueName.category.empty()) */
	else
	 {
	   cerr << "ERROR: message did not have a valid category" << std::endl
		<< "\tAborting" << std::endl 
		<< "I got " << config.QMSUniqueName.category << std::endl
		<< query;
	      print_message_data(config, request_data);
	 } /* end of else */
      }
     else
      {
	cerr << "Error: parsing message" << std::endl
	     << "\tAborting" << std::endl
	     << query;
      } /* end of else */
   } /* end of if(buffer_p) */
  if(buffer_p)
   {
     delete buffer_p;
     buffer_p = 0;
   } /* end of if(buffer_p) */
}


// template <class _Key,     class _Value, class _KeyOfValue, 
//           class _Compare, class _Alloc = class allocator<_T2> >
// _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc> 
using namespace STDC::QMS::Citizen;



#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class map<std::string, STDC::QMS::Citizen::Hello_World_Meta_Data *>;

#  if defined(__GNUC_MINOR__) && __GNUC_MINOR__ > 92
template class _Rb_tree<string, pair<string const, STDC::QMS::Citizen::Hello_World_Meta_Data *>, _Select1st<pair<string const, STDC::QMS::Citizen::Hello_World_Meta_Data *> >, less<string >, allocator<STDC::QMS::Citizen::Hello_World_Meta_Data *> >;
#  else
template class rb_tree<string, pair<string const, STDC::QMS::Citizen::Hello_World_Meta_Data *>, select1st<pair<string const, STDC::QMS::Citizen::Hello_World_Meta_Data *> >, less<string>, __default_alloc_template<true, 0> >;
#  endif
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate class map<std::string, STDC::QMS::Citizen::Hello_World_Meta_Data *>
#pragma instantiate class _Rb_tree<string, pair<string const, STDC::QMS::Citizen::Hello_World_Meta_Data *>, _Select1st<pair<string const, STDC::QMS::Citizen::Hello_World_Meta_Data *> >, less<string >, allocator<STDC::QMS::Citizen::Hello_World_Meta_Data *> >
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

