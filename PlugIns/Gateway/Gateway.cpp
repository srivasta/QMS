//                              -*- Mode: C++ -*- 
// Gateway.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
// Created On       : Tue Dec 11 20:03:35 2001
// Created On Node  : glaurung.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Jan  8 22:27:42 2002
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 139
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
version = "$Id: Gateway.cpp,v 1.52 2002/01/24 21:19:14 amit Exp $";
/** @file 
 *  @ingroup Gateway
 *  @brief Convenience object to parse QMS XML documents
 *
 * $Id: Gateway.cpp,v 1.52 2002/01/24 21:19:14 amit Exp $
 */

#include <fstream>
#include <iostream>
#include <strstream>
#include <sstream>
#include <cstdlib>

#include <cstring>
#include <cstring>
#include <ctype.h>

#include <exception>
#include <stdexcept>

#include "Gateway.h"
#include "Instrumentation.h"

#include <Include/PlatformDefinitions.hpp>
#include <util/PlatformUtils.hpp>
#include <XalanTransformer/XalanTransformer.hpp> 


/**
 *  @brief The constructor
 *
 * 
 */
STDC::QMS::Gateway::Gateway() : _parser_initialized(false), _sequence_num(1)
{
  QMS_Trace ("STDC::QMS::Gateway::Gateway", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Gateway created\n");
}

/**
 *  @overload
 * 
 */
STDC::QMS::Gateway::Gateway(const STDC::QMS::Gateway& rhs)
{
  QMS_Trace ("STDC::QMS::Gateway::Gateway", __LINE__,
             __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Gateway created\n");
  this->_parser_initialized = rhs._parser_initialized;
  this->_sequence_num = rhs._sequence_num;
}

/// The assignment operator
STDC::QMS::Gateway & 
STDC::QMS::Gateway::operator=(const STDC::QMS::Gateway& rhs)
{
  QMS_Trace ("STDC::QMS::Gateway::Gateway", __LINE__,
             __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Gateway created\n");
  this->_sequence_num = rhs._sequence_num;
  return *this;
}

/**
 * @brief Initialize an XML Parser
 * 
 * This has to be done before the first invocation of the parser.
 */
void
STDC::QMS::Gateway::init_parser()
{
  QMS_Trace("STDC::QMS::Gateway::init_parser",__LINE__, __FILE__);
  DEBUG0(2, "DEBUG:STDC::QMS::Gateway::init_parser");
  // Initialize the Parser. 
  try 
   {
     XMLPlatformUtils::Initialize();
     // Initialize Xalan.
     XalanTransformer::initialize();
   }
  catch(const XMLException& toCatch)
   {
     std::cerr << "Error during Xerces-c Initialization.\n"
          << "  Exception message:"
          << toCatch.getMessage()
          << std::endl;
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
STDC::QMS::Gateway::parser_cleanup(void)
{
  QMS_Trace("STDC::QMS::Gateway::parser_cleanup",__LINE__, __FILE__);
  DEBUG0(2, "DEBUG:STDC::QMS::Gateway::parser_cleanup\n");
  // Terminate the parser before the end. This belongs in a destructor
  if(!this->_parser_initialized)
   {
     return;
   } /* end of if(!this->_parser_initialized) */
  
  try 
   {
     // Terminate Xalan.  
     XalanTransformer::terminate();
     XMLPlatformUtils::Terminate();
     this->_parser_initialized = false;
   }
  catch(const XMLException& toCatch)
   {
     std::cerr << "Error during Xerces-c termination.\n"
          << "  Exception message:"
          << toCatch.getMessage()
          << std::endl;
   }
  catch (...)
   {
     std::cerr << "Error during Xerces-c termination.\n";
   }
  DEBUG0(4, "DEBUG:parser_cleanup done\n");
}

/** @brief Initialize the sensor object
 *  @param credentials The credentials of the entity making the  request
 *  @param config_file_p The path name to the sensor configuration file
 *  @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 *  This is where most of the setup and initiasation of the sensor
 *  object occurs.
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
STDC::QMS::Gateway::init(STDC::QMS::CORBA_Handles *handles_p,
			 CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Gateway::init", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Gateway::init\n");


    if(handles_p)
   {
     this->handles_p_ = handles_p;
     if(!this->handles_p_)
      {
        std::cerr << __FILE__ << " " << __LINE__ 
             << "corba handles assignment failed" << std::endl;
        throw std::invalid_argument::invalid_argument("corba handles assignment failed");
      } /* end of if(!this->handles_p_) */
   }
  ACE_TRY
    {
      this->init_parser();
      ACE_OS::hostname(this->_hostname, MAXNAMELEN );

      struct hostent *hostinfo = ACE_OS::gethostbyname (this->_hostname);
      in_addr address;
      address.s_addr = 
        (ACE_reinterpret_cast (in_addr * ,
                               hostinfo->h_addr_list[0])->s_addr);
      ACE_OS::strcpy(this->_ip_address, inet_ntoa(address));
      
      int ret = snprintf(this->_uuid, 128, "%d", ACE_OS::getpid ());
      if(ret == -1 || ret >=128)
       {
         std::cerr << "Error handling config" << std::endl;
         std::cerr << __FILE__ << __LINE__ << std::endl;
         this->parser_cleanup();
         exit (EXIT_FAILURE);
       } /* end of if(ret == -1 || ret >=32) */
      if(CORBA::is_nil(this->_ec_registry.in()))
       {
         this->get_ec_registry(ACE_TRY_ENV);
         ACE_TRY_CHECK;
       } /* end of if(CORBA::is_nil(this->_ec_registry)) */

      this->get_supplier_id(ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Error Getting Initializing Gateway");
      this->cleanup();
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}

/**
 * @brief This is where we perform cleanup operations
 *
 */
void
STDC::QMS::Gateway::cleanup(void)
{
  QMS_Trace("STDC::QMS::Gateway::cleanup", __LINE__,__FILE__);
  DEBUG0(2, "DEBUG:STDC::QMS::Gateway::cleanup");

//  DEBUG0(4, "Cleaning up probes");
//   std::map<std::string, STDC::QMS::Citizen::Meta_Data *>::iterator pos;
//    for(pos = this->probes_.begin(); pos != this->probes_.end(); ++pos)
//     {
//       if(pos->second != 0)
//        {
//          pos->second->cleanup(this->handles_p_);
//          delete pos->second;
//          pos->second = 0;
//        } /* end of if(pos && pos->second) */
//     }
//    this->probes_.clear();

   DEBUG0(4, "Cleaning up Parser");
   this->parser_cleanup();
   DEBUG0(4, "Gateway cleaned up");
}

/**
 * @brief Initialize built in reference to CORBA handles
 * @param handles_p A reference to CORBA handles
 */
void
STDC::QMS::Gateway::add_handle(STDC::QMS::CORBA_Handles
                                                 *handles_p)
{
  QMS_Trace("STDC::QMS::Gateway::add_handle", __LINE__,__FILE__);
  DEBUG0(2, "DEBUG:STDC::QMS::Gateway::add_handle");
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
STDC::QMS::Gateway::get_handle(void)
{
  QMS_Trace("STDC::QMS::Gateway::get_handle", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG:STDC::QMS::Gateway::get_handle");
  return this->handles_p_;
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
STDC::QMS::Gateway::get_supplier_id(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Gateway::get_supplier_id", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Gateway::get_supplier_id\n");
  

  ACE_TRY
    {
      if(CORBA::is_nil(this->_ec_registry.in()))
       {
         this->get_ec_registry(ACE_TRY_ENV);
         ACE_TRY_CHECK;
       } /* end of if(CORBA::is_nil(this->_ec_registry)) */

      string identity;
      identity.assign("Basic Validation Gateway: ");
      identity.append(this->_hostname);
      identity.append(":");
      identity.append(this->_uuid);
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
 * @brief Get a reference to the QMS Trader ECInfo component
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * First, if we already have a handle on the QMS Trader component, we
 * return immediately. If not, we query the CORBA Trading service for
 * the YP offer of the EC Info component, narrow it down, and stash
 * the object reference away.
 */
void
STDC::QMS::Gateway::get_ec_registry(CORBA::Environment 
                                                      &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Gateway::get_ec_registry", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Gateway::get_ec_registry\n");
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
      PolicySeq policies;                    //empty sequence

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
         std::cerr << "No Trader Offers found" << std::endl;
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
            std::cerr << "Service provider is not an ec registry" << std::endl;
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
        std::cerr << "Illegal Constraint: " << constex.constr.in () << std::endl;
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
 * @brief Perform the normal steps fpr a client
 * @param hostname The hostname to connect to
 * @param service The service name or port number to connect
 */
int
STDC::QMS::Gateway::tcp_connect(const char * hostname, const char *service)
{
  QMS_Trace ("tcp_connect", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: tcp_connect\n");
  int n = 0;
  int sockfd;
  struct addrinfo *results_talk_p = 0;

  struct addrinfo hints;
  memset ((void *) &hints, 0, sizeof(struct addrinfo));

  hints.ai_flags    			  = AI_CANONNAME;
  hints.ai_family   			  = AF_INET;
  hints.ai_socktype 			  = SOCK_STREAM;  
  

  DEBUG2 (2, "DEBUG: hostname %s, port %s\n", hostname, service);
  if((n = getaddrinfo(hostname, service, &hints, &results_talk_p)) != 0)
   {
     string this_error = "Error Getting address info for host: ";
     this_error.append(hostname);
     this_error.append(" service: ");
     this_error.append(service);
     throw std::runtime_error::runtime_error(this_error);
   } /* end of if((n = getaddrinfo(hostname, service, hints,
	results_talk_p)) != 0) */

  DEBUG0 (2, "DEBUG: Got address info\n");

  struct addrinfo *results_index_p = results_talk_p;
  
  do 
   {
     sockfd = socket(results_index_p->ai_family, 
		     results_index_p->ai_socktype,
		     results_index_p->ai_protocol);
     if(sockfd < 0)
      {
	continue;
      } /* end of if(sockfd < 0) */

     if(connect(sockfd, results_index_p->ai_addr, 
		results_index_p->ai_addrlen) == 0)
     {
       break;
     } /* end of if(connect(sockfd, results_index_p->ai_addr,
	  results_index_p->ai_addrlen) == 0) */
     n = close(sockfd);		// ignore this one
     if(n < 0)
      {
	perror("close");
	std::cerr << "Error closing socket " << __FILE__ << ":" 
		  << __LINE__ << " for " << hostname 
		  << " port " << service << std::endl;
      } /* end of if(n < 0) */
     
   }
  while((results_index_p = results_index_p->ai_next) != 0);
  if(results_index_p == 0)
   {
     string this_error = "Could not find a working connection for host: ";
     this_error.append(hostname);
     this_error.append(" service: ");
     this_error.append(service);
     throw std::runtime_error::runtime_error(this_error);
   } /* end of if(results_index_p == 0) */
  freeaddrinfo(results_talk_p);
  return (sockfd);
}

void
STDC::QMS::Gateway::handle_data(const string &message)
{
  QMS_Trace ("handle_data", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: handle_data\n");
  this->wall(message);
}


void
STDC::QMS::Gateway::wall(const string &message)
{
  QMS_Trace ("wall", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: wall\n");
  ssize_t ret;
  std::set<int>::iterator pos;
  DEBUG0 (2, "DEBUG: going to write\n");
  {
    ACE_Write_Guard<ACE_RW_Mutex> guard(this->_socket_guard);
    for(pos = this->sockets_.begin(); pos != this->sockets_.end(); )
     {
       ret = this->write_line(*pos, message);
       if(ret)
	{
	  std::cerr << "Error writing to socket " << *pos 
		    << std::endl;
	} /* end of if(ret) */
       ret = this->write_line(*pos, STDC::QMS::Citizen::delimiter);
       if(ret)
	{
	  std::cerr << "Error writing to socket " << *pos 
		    << std::endl;
	  if(errno != EFAULT)
	   {
	     this->sockets_.erase(pos++);
	   } /* end of if(errno != EFAULT) */
	  else
	   {
	     ++pos;
	   } /* end of else */
	} /* end of if(ret) */
       else
	{
	  ++pos;
	} /* end of else */
     } /* end of for(pos = this->sockets_.begin(); 
		     pos != this->sockets_.end(); ) */
  }
}

ssize_t
STDC::QMS::Gateway::write_line(int sockfd, const string message)
{
  QMS_Trace ("write_line", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: write_line\n");

  ssize_t nleft;
  ssize_t nwritten;
  
  nleft = strlen(message.c_str());
  char *ptr = const_cast< char * >(message.c_str());
  
  while(nleft > 0)
   {
     if((nwritten = write(sockfd, ptr, nleft)) <= 0)
      {
        if(errno == EINTR)
         {
           nwritten = 0;
         } /* end of if(errno == EINTR) */
        else
         {
           std::cerr << "Error writing to pipe" << std::endl;
           perror("write");
	   return nwritten;
         } /* end of else */
      } /* end of if((nwritten = write(sockfd, ptr, nleft)) <= 0) */
     nleft -= nwritten;
     ptr += nwritten;
   } /* end of while(nleft > 0) */  
  return nleft;
}

static const char *message_top_p = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>                            \n\
<discover xmlns=\"http://www.stdc.com/2001/QMS/Plugins/BVGateway\"    \n\
  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"             \n\
  xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"                    \n\
  xsi:schemaLocation=                                                 \n\
  \"http://www.stdc.com/2001/QMS/Plugins/BVGateway BVGateway.xsd\">   \n\
  <response>                                                          \n\
";

static const char *message_bot_p = "\
    <action>add</action>                                              \n\
  </response>                                                         \n\
</discover>                                                           \n\
";

void
STDC::QMS::Gateway::handle_discovery_req(STDC::QMS::BV_RequestType &config)
{
  QMS_Trace ("handle_discovery_req", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: handle_discovery_req\n");

  int sockfd;
  string response;
  
  char portstr[ 10];
  int ret = snprintf(portstr, 10, "%d", config.discover_request.address.port);
  if(ret < 0 || ret > 10)
   {
     
     std::cerr << "Error allocating memory"  << std::endl;
     return;
   } /* end of if(ret < 0 || ret > 10) */
  
  DEBUG1(4, "DEBUG: Trying to connect to port %s\n", portstr);
  try 
   {
     sockfd = this->tcp_connect(config.discover_request.address.host.c_str(), 
			  portstr);
   }
  catch (... )
   {
     std::cerr << "Caught an exception"  << std::endl;
     return;
   }
  DEBUG1 (4, "DEBUG: Connected to port %d\n",
	  config.discover_request.address.port);

  std::pair<std::set<int>::iterator,bool> status;
  status = this->sockets_.insert(sockfd);
  if(!status.second)
   {
     std::cerr << "Warning: duplicate socket descriptor: " << sockfd 
	       << std::endl;
   } /* end of if(!status.second) */
  

  vector<struct STDC::QMS::uniqueNameType>::iterator cat;
  for(cat = config.discover_request.resources.begin();
      cat != config.discover_request.resources.end(); 
      cat++)
   {
     if(!cat->category.empty())
      {
	response.erase();
	this->get_offers(cat->category, response);
	if(!response.empty())
	 {
	   DEBUG1 (4, 
		   "DEBUG: Sending Message\n---------------------------\n%s",
		   response.c_str());
	   DEBUG0 (4, 
		   "DEBUG: \n---------------------------------------------\n");
	   this->wall(response);	   
	 } /* end of if(response.empty()) */
	
      } /* end of if(!cat->category.empty()) */
   } /* end of for(cat = config.discover_request.resources.begin();
	cat != config.discover_request.resources.end(); cat++) */
}

void
STDC::QMS::Gateway::handle_resource_req(char *message_p,
					 STDC::QMS::BV_RequestType &config)
{
  QMS_Trace ("handle_resource_req", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: handle_resource_req\n");

  if(config.data_request.QMSUniqueName.category.empty())
   {
     std::cerr << "Bad data request: no category in parsed tree" << std::endl
	       << message_p << std::endl
       ;
     return;
   } /* end of if(config.data_request.QMSUniqueName.category.empty()) */
  
  string key;
  key.assign(config.data_request.QMSUniqueName.category);
  key.append(" ");
  key.append(config.data_request.QMSUniqueName.host);
  key.append(" ");
  key.append(config.data_request.QMSUniqueName.uuid);
  DEBUG1(2, "DEBUG: Have we seen this (partial key) before? -- [%s]", 
	 key.c_str());

  STDC::QMS::Multi_Client * client_p = 0;
  string my_category = config.data_request.QMSUniqueName.category;
  char req_id[20];

  if(config.data_request.request_id != 0)
   {
     DEBUG0 (2, "DEBUG: we already know about this\n");
     if(config.data_request.action.compare("start") == 0)
      {
	std::cerr << "Duplicate request for an active stream, ignoring"
		  << std::endl;
	return;
      } /* end of if(config.data_request.action.compare("stop") == 0) */


     int ret = snprintf(req_id, 19, "%ld", config.data_request.request_id);
     if(ret < 0 || ret > 19)
      {
	std::cerr << "Error creating Key" << std::endl;
	return;
      } /* end of if(ret < 0 || ret > 19) */
     key.append(" ");
     key.append(req_id);
     
     DEBUG1(2, "DEBUG: Searching for multiclient with key -- [%s]", 
	    key.c_str());
     
     {
       ACE_Write_Guard<ACE_RW_Mutex> guard(this->_client_guard);
       
       std::map<std::string, STDC::QMS::Multi_Client *>::iterator pos;
       pos = this->clients_.find(key);
       
       if(pos != this->clients_.end())
	{
	  client_p = pos->second;
	  client_p->send(this->_sequence_num++, config, message_p);
	  if(config.data_request.action.compare("stop") == 0)
	   {
	     delete client_p;
	     client_p = 0;
	     this->clients_.erase(key);
	   } /* end of if(config.data_request.action.compare("stop") == 0) */
	  // this->wall("stopping probe with key");
	}
       else
	{
	  std::cerr << "Error: Could not find matching client for request"
		    << std::endl;
	  return;
	} /* end of else */
     }
     return;
   }
  else
   {
     DEBUG0 (2, "DEBUG: New Request\n");
     if(config.data_request.action.compare("start") != 0)
      {
	std::cerr << "Bad new request, ignoring"
		  << std::endl;
	return;
      }

     int ret = snprintf(req_id, 19, "%ld", this->_sequence_num);
     if(ret < 0 || ret > 19)
      {
	std::cerr << "Error creating Key" << std::endl;
	return;
      } /* end of if(ret < 0 || ret > 19) */
     key.append(" ");
     key.append(req_id);
     
     /// See if we can get an offer.
     client_p = new STDC::QMS::Multi_Client();
     assert(client_p);
     DEBUG1 (2, "DEBUG: Saving this request with key\n[%s]\n",
	     key.c_str());
     {
       ACE_Write_Guard<ACE_RW_Mutex> guard(this->_client_guard);
       this->clients_.insert(std::make_pair(key, client_p));
       DEBUG0 (2, "DEBUG: Making Request\n");
       try
	{
	  client_p->init(message_p, config, this->handles_p_,
			 this->_supplier_id,
			 this->_sequence_num++, this->_hostname, 
			 this->_ip_address, this->_uuid);
	}
       catch (...)
	{
	  std::cerr << "Error Could not init multi client. Deleting" 
		    << std::endl;
	  delete client_p;
	  client_p = 0;
	  this->clients_.erase(key);
	}
     }
   } /* end of else */
}


void
STDC::QMS::Gateway::handle_query(char * message_p)
{
  QMS_Trace("STDC::QMS::Gateway::handle_query", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Gateway::handle_query\n");

  DEBUG1(2, "DEBUG: handle_query got argument\n%s\n", message_p);
  
  // Try and parse the message here.
  DEBUG0(2, "DEBUG: Creating XML buffer");
  MemBufInputSource *buffer_p = 0;
  buffer_p = new MemBufInputSource((const XMLByte*) message_p,
                                   strlen(message_p), "GUI_Request",
                                   false);
   DEBUG1(2, "DEBUG: handle_query -- going to parse\n%s\n", message_p);
  //
  //  Parse the XML file, catching any XML exceptions that might propogate
  //  out of it.
  //  
  if(buffer_p)
   {
     STDC::QMS::Parse_BV_Request *my_parser = 
       new STDC::QMS::Parse_BV_Request();
     if(!my_parser)
      {
	std::cerr << "Error Creating a parser" << std::endl;
	delete buffer_p;
	buffer_p = 0;
	return;
      } /* end of if(!my_parser) */
     
     STDC::QMS::BV_RequestType config;

     bool parsed_message = my_parser->parse_bv_request(*buffer_p, config);
     
     if(parsed_message)
      {
	if(config.isDiscovery)
	 {
	   this->handle_discovery_req(config);
	 }
	else
	 {
	   // Handle data request here
	   this->handle_resource_req(message_p, config);
	 } /* end of else */
      }
     // Deleting the parser explicitly  causes a seg fault
     delete buffer_p;
     buffer_p = 0;
   } /* end of if(buffer_p) */
}

void
STDC::QMS::Gateway::create_response(const CosTrading::PropertySeq & properties,
			   string &response, CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Gateway::create_response", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Gateway::create_response\n");
  TAO_Property_Evaluator prop_eval (properties);
  ACE_TRY
    {
      string category;
      string host;
      string uuid;
      string options;
      time_t this_time;
      struct tm *now_p;

      for (int length = properties.length (), k = 0; k < length; k++)
       {
	 CORBA::Any* value = 0;
	 CORBA::TypeCode_ptr tc = 0;
	 
	 value = prop_eval.property_value(k, ACE_TRY_ENV);
	 ACE_TRY_CHECK;

	 tc = value->type ();
	 if (tc == 0)
	   continue;

	 string name;
	 name.assign(properties[k].name.in ());
	 DEBUG1(2, "DEBUG: \tProperty name=%s\n", name.c_str());
	 // @@ Print the any value...
	 CORBA::Char       char_val;
	 CORBA::Octet     octet_val;
	 CORBA::Boolean boolean_val;
	 CORBA::Short     short_val;
	 CORBA::UShort   ushort_val;
	 CORBA::Long       long_val;
	 CORBA::ULong     ulong_val;
	 CORBA::Float     float_val;
	 CORBA::Double   double_val;
	 const char *    string_val;
	 char values[100];
	 values[0]=0;
	 int ret = 0;
	 
	 if ((*value) >>= CORBA::Any::to_char (char_val))
	  {
	    DEBUG1 (2, "char_val=%c", char_val);
	    ret = snprintf(values, 100, "%c", char_val);
	  }
	 else if ((*value) >>= CORBA::Any::to_octet (octet_val))
	  {
	    DEBUG1 (2, "octet_val=%c", octet_val);
	    ret = snprintf(values, 100, "%c", octet_val);
	  }
	 else if ((*value) >>= CORBA::Any::to_boolean (boolean_val))
	  {
	    DEBUG1 (2, "boolean_val=%s", boolean_val?"TRUE":"FALSE");
	    ret = snprintf(values, 100, "%s", boolean_val?"TRUE":"FALSE");
	  }
	 else if ((*value) >>= short_val)
	  {
	    DEBUG1 (2, "short_val=%d", short_val);
	    ret = snprintf(values, 100, "%d", short_val);
	  }
	 else if ((*value) >>= ushort_val)
	  {
	    DEBUG1 (2, "ushort_val=%ld", ushort_val);
	    ret = snprintf(values, 100, "%ld", ushort_val);
	  }
	 else if ((*value) >>= long_val)
	  {
	    DEBUG1 (2, "long_val=%d", long_val);
	    ret = snprintf(values, 100, "%d", long_val);
	  }
	 else if ((*value) >>= ulong_val)
	  {
	    DEBUG1 (2, "ulong_val=%ld", ulong_val);
	    ret = snprintf(values, 100, "%ld", ulong_val);
	  }
	 else if ((*value) >>= float_val)
	  {
	    DEBUG1 (2, "float_val=%f", float_val);
	    ret = snprintf(values, 100, "%f", float_val);
	  }
	 else if ((*value) >>= double_val)
	  {
	    DEBUG1 (2, "double_val=%f", double_val);
	    ret = snprintf(values, 100, "%f", double_val);
	  }
	 else if ((*value) >>= string_val)
	  {
	    DEBUG1 (2, "string_val=%s", string_val);
	  }

	 if(name.find("QMS_UNIQ_NAME_CATEGORY") != string::npos)
	  {
	    category.assign("        <category>");
	    category.append(string_val);
	    category.append("</category>\n");
	    continue;
	  } /* end of if(strcmp(name_p, "QMS_UNIQ_NAME_CATEGORY") == 0) */

	 if(name.find("QMS_UNIQ_NAME_HOST_NAME") != string::npos)
	  {
	    host.assign("        <host>");
	    host.append(string_val);
	    host.append("</host>\n");
	    continue;
	  } /* end of if(strcmp(name_p, "QMS_UNIQ_NAME_HOST_NAME") == 0) */

	 if(name.find("QMS_UNIQ_NAME_UUID") != string::npos)
	  {
	    uuid.assign("        <uuid>");
	    uuid.append(string_val);
	    uuid.append("</uuid>\n");
	    continue;
	  } /* end of if(strcmp(name_p, "QMS_UNIQ_NAME_UUID") == 0) */

	 
	 options.append("      <offerInfo>\n");
	 options.append("        <qms:name>");
	 options.append(name);
	 options.append("</qms:name>\n");

	 options.append("        <qms:value>");
	 string escaped_val;
	 
	 if(!values[0])
	  {
	    escaped_val.assign(string_val);
	  } /* end of if(!values[0]) */
	 else
	  {
	    escaped_val.assign(values);
	  } /* end of else */

	 string::size_type location = 0;
	 
	 while((location = escaped_val.find("&", location + 2))
	       != string::npos)
	  {
	    escaped_val.replace(location,1,"&amp;");
	  } /* end of while((location = escaped_val.find("<"))
	       != string::npos) */

	 while((location = escaped_val.find("<")) != string::npos)
	  {
	    escaped_val.replace(location,1,"&lt;");
	  } /* end of while((location = escaped_val.find("<"))
	       != string::npos) */
	 while((location = escaped_val.find(">")) != string::npos)
	  {
	    escaped_val.replace(location,1,"&gt;");
	  } /* end of while((location = escaped_val.find(">"))
	       != string::npos) */

	 options.append(escaped_val);
	 options.append("</qms:value>\n");
	 options.append("      </offerInfo>\n");
       }
      this_time = time(0);
      now_p = gmtime((const time_t *) &this_time);

      std::ostringstream response_stream;

      response.append(message_top_p);
      response_stream << "    <qms:msgDate>" << (1900 + now_p->tm_year) 
		      << "-" << (1 + now_p->tm_mon) << "-" 
		      << now_p->tm_mday << "</qms:msgDate>" << std::endl
		      << "    <qms:msgTime>" << now_p->tm_hour << ":"
		      << now_p->tm_min << ":" <<  now_p->tm_sec
		      << "-0:00</qms:msgTime>" << std::endl
		      << "    <resource>" << std::endl;
      response.append(response_stream.str());
      response.append("      <QMSUniqueName>\n");
      response.append(category);
      response.append(host);
      response.append(uuid);
      response.append("      </QMSUniqueName>\n");
      response.append(options);
      response.append("    </resource>\n");
      response.append(message_bot_p);
      response.append(STDC::QMS::Citizen::delimiter);
      DEBUG0(4, "DEBUG: appended delimiter");
    } 
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, 
                           "System Exception creating a response");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex,
                           "User Exception creating a response:");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Error creating a response");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;  
}


/**
 * @brief Handle the offers we get
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 * @param offer_seq_ptr Pointer to a sequence of offers
 * @param iterator Offer iterator
 *
 * Here we narrow the reference associated with the ofers to a generic
 * QMS citizen (and not to the specific sensor we wish to talk to, for
 * portability between sensors). We then try and ping the sensor. 
 */
void
STDC::QMS::Gateway::handle_offers(CosTrading::OfferSeq *offer_seq_ptr,
				  CosTrading::OfferIterator_var iterator,
				  string &response,
				  CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Gateway::Handle_offers", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Gateway::Handle_offers\n");
  int length = 0;
  int i = 0;
  
  if(offer_seq_ptr)
   {
     DEBUG0 (2, "DEBUG: We have some offers\n");
     const CosTrading::OfferSeq& offer_seq = *offer_seq_ptr;
     DEBUG1 (2, "DEBUG: We have %d offers\n", offer_seq.length ());
     for (length = offer_seq.length (), i = 0; i < length; i++)
      {
	 DEBUG1 (2, "DEBUG: Trying offer  %d\n", i);
	 if(CORBA::is_nil(offer_seq[i].reference))
	  {
	    DEBUG0 (2, "DEBUG: Null reference\n");
	    continue;
	  } /* end of if(!CORBA::is_nil(offer_seq[i].reference)) */
	 else
	  {
	    DEBUG0 (2, "DEBUG: Good reference\n");
	  } /* end of else */
	 
	 // Call back to the exported object.
	 try
	  {
	    STDC::QMS::Citizen::Command_var sensor_var = 
	      STDC::QMS::Citizen::Command::_narrow(offer_seq[i].reference.in());
	    DEBUG0 (2, "DEBUG: Narrowed\n");
	 
	    CORBA::Short acknowledgement = 0;
	    DEBUG1(2, "DEBUG: Looking at offer %d\n", i);
	    if(CORBA::is_nil(sensor_var.in()))
	     {
	       cerr << "The reference is not a QMS Citizen" << endl
		    << "For offer in sequence  " << i << endl;
	       continue;
	     } /* end of if(CORBA::is_nil(hello_var.in())) */

	    
	    sensor_var->ping(acknowledgement);
	    if(acknowledgement == 0)
	     {
	       cerr << "Could not ping Sensor" << endl
		    << "For offer " << i << endl;
	       continue;
	     } /* end of if(acknowledgement == 0) */
	    cerr << "ping succeded\n";
	  }
	 catch(...)
	  {
	    DEBUG0 (2, "DEBUG: Failed to ping\n");
	    continue;
	  }
	 // Write the offer properties
	 this->create_response(offer_seq[i].properties, response, ACE_TRY_ENV);
      }
   }
  
  // Well, Now we need to look at the iterator
   if(!CORBA::is_nil(iterator.in()))
    {
      DEBUG0(2, "DEBUG: The iterator is not null\n");
      bool more;
      do
       {
        CORBA::ULong length = 10;
        CosTrading::OfferSeq *iter_offers_ptr;
        CosTrading::OfferSeq_out iter_offers_out(iter_offers_ptr);
        
        more = iterator->next_n(length, iter_offers_out);
        
        CosTrading::OfferSeq_var offers (iter_offers_ptr);
        
        for(CORBA::ULong i = 0; i < offers->length(); i++)
         {
           CORBA::Short acknowledgement = 0;
           DEBUG1(2, "DEBUG: Looking at offer %d\n", i);
	   try
	    {
	      STDC::QMS::Citizen::Command_var sensor_var = 
		STDC::QMS::Citizen::Command::_narrow(offers[i].reference.in());
	      if(CORBA::is_nil(sensor_var.in()))
	       {
		 cerr << "The reference is not a QMS Citizen" << endl
		      << "For offer in iterator " << i << endl;
		 continue;
	       } /* end of if(CORBA::is_nil(hello_var.in())) */
	      sensor_var->ping(acknowledgement);
	      if(acknowledgement == 0)
	       {
		 cerr << "Could not ping Sensor" << endl
		      << "For offer " << i << endl;
		 continue;
	       } /* end of if(acknowledgement == 0) */
	      
	      DEBUG0(4, "DEBUG: ping succeded\n");
	    }
	   catch(...)
	    {
	      DEBUG0 (2, "DEBUG: Failed to ping\n");
	      continue;
	    }
	   // Write the offer properties
	   this->create_response(offers[i].properties, response);
         } /* end of for(i = 0; i < offers->length(); i++) */
       } 
      while(more);
    } /* end of if(!CORBA::is_nil(iterator.in())) */
   else
    {
      DEBUG0(2, "DEBUG: The iterator is null\n");
    } /* end of else */ 
} 


/**
 * @brief Query the the trading service for a QMS citizen matchng the category
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * Here we set up and make the query to the trading service, stashing
 * the object away.
 *
 */
void
STDC::QMS::Gateway::get_offers(string &category_name, 
			       string &response,
			       CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Gateway::get_offers", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Gateway::get_offers\n");
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
      PolicySeq policies;                    //empty sequence
      
      CosTrading::Lookup::SpecifiedProps desired_props;  // No properties
      desired_props._d(Lookup::all);         // Return all properties
      
      CosTrading::PolicyNameSeq_var limits_applied;      // out param
      CosTrading::OfferSeq *offer_seq_ptr          = 0;
      CosTrading::OfferSeq_out      offers(offer_seq_ptr);
      CosTrading::OfferIterator_var iterator;

      /// Create a contraint for the query
      string constraint = "QMS_UNIQ_NAME_CATEGORY == '";
      constraint.append(category_name);
      constraint.append("' ");

      DEBUG1(4, "DEBUG: YP_SERVICE_TYPE %s\n", YP_SERVICE_TYPE);
      DEBUG1(4, "DEBUG: constraint %s\n", constraint.c_str());
      // make the query, asking for an empty sequence
      lookup_p->query(YP_SERVICE_TYPE,         // IN string
                      constraint.c_str(),      // IN contraint
                      "",                      // IN preferences
                      policies,                // IN policies
                      desired_props,           // IN desired properties
                      1,                       // IN how many in sequence
                      offers,                  // OUT Offer sequence
                      iterator,                // OUT Iterator
                      limits_applied           // OUT policies applied
                      );
      ACE_TRY_CHECK;

      // Processing the results
      if(offers->length() == 0)
       {
         cerr << "No Sensor Offers found" << endl;
	 return;
       } /* end of if(offer_seq_out->length() == 0) */
      else
       {
         this->handle_offers(offer_seq_ptr, iterator, response, ACE_TRY_ENV);
       } /* end of else */      
      if (!CORBA::is_nil(iterator.in()))
       {
         iterator->destroy();
         ACE_TRY_CHECK;
       }
    } 
  ACE_CATCH (CosTrading::IllegalConstraint, ex)
    {
      ACE_PRINT_EXCEPTION (ex, "Illegal Constraint getting Sensor Offer:");
      if (ex.constr.in() != 0)
        cerr << "Illegal Constraint " << ex.constr.in() << endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception getting sensor offer:");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception getting sensor offer:");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error getting sensor");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}


#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class map<std::string, STDC::QMS::Multi_Client *>;
template class set<int>;
#  if defined(__GNUC_MINOR__) && __GNUC_MINOR__ > 92
template class _Rb_tree<string, pair<string const, STDC::QMS::Multi_Client*>, _Select1st<pair<string const, STDC::QMS::Multi_Client *> >, less<string >, allocator<STDC::QMS::Multi_Client *> >;
template class _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >;
#  else
template class rb_tree<string, pair<string const, STDC::QMS::Multi_Client *>, select1st<pair<string const, STDC::QMS::Multi_Client *> >, less<string>, __default_alloc_template<true, 0> >;
template class rb_tree<int, int, identity<int>, less<int>, __default_alloc_template<true, 0> >;
#  endif

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate class map<std::string, STDC::QMS::Multi_Client *>
#pragma instantiate class _Rb_tree<string, pair<string const, STDC::QMS::Multi_Client *>, _Select1st<pair<string const, STDC::QMS::Multi_Client *> >, less<string >, allocator<STDC::QMS::Multi_Client *> >
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
