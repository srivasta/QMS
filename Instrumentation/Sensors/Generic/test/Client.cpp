// test_client.cpp ---
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
 *  @ingroup GenericSensor 
 *  @brief  A Generic Client that sends the sensor through a test suite
 *
 * This is a sample client that can beused as a simple testing
 * mechanism for testing QMS sensors. 
 *
 * $Id: Client.cpp,v 1.35 2002/01/11 20:03:11 nath Exp $
 */
/// RCS version string
static const char* version = 
"$Id: Client.cpp,v 1.35 2002/01/11 20:03:11 nath Exp $";

#include "Client.h"

#if defined(_WIN32)
#  define snprintf _snprintf
#endif


/// Format string for the request
const char *request_fmt = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<qms:QMSMessage xmlns=\"http://www.stdc.com/2001/QMSSchema\"\n\
  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
  xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"\n\
  xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema %s\">\n\
  <qms:msgSequenceNo>%ld</qms:msgSequenceNo>\n\
  <qms:msgDate>%d-%d-%d</qms:msgDate>\n\
  <qms:msgTime>%d:%d:%d-0:00</qms:msgTime>\n\
  <qms:originatingHost>%s</qms:originatingHost>\n\
  <qms:msgSender>\n\
    <id>%d</id>\n\
    <description>Test client for a QMS Probe</description>\n\
  </qms:msgSender>\n\
  <qms:QMSUniqueName>\n\
    <category>%s</category>\n\
  </qms:QMSUniqueName>\n\
  <qms:Session>\n\
    <requestID>%ld</requestID>\n\
    <version>%ld</version>\n\
    <minRepetitions>\n\
     <count>%d</count>\n\
    </minRepetitions>\n\
    <minRepeatInterval>%s</minRepeatInterval>\n\
  </qms:Session>\n\
  <qms:payload>\n\
    %s\n\
  </qms:payload>\n\
</qms:QMSMessage>\n\
";

/// Constructor
Test_Client::Test_Client() : _identity_p(0), _supplier_id(99),
			     _parser_initialized(false),
			     _request_event_type(0),
			     _data_event_type(0),
			     _host_addr("")
{
  QMS_Trace("Test_Client::Test_Client()", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::Test_Client()\n");

}

/**
 * @overload
 */
Test_Client::Test_Client(const Test_Client& rhs) :
  _identity_p(rhs._identity_p), _supplier_id(rhs._supplier_id), 
  _handles(rhs._handles), _ec_registry(rhs._ec_registry), 
  _parser_initialized(rhs._parser_initialized), 
  _category_name(rhs._category_name), 
  _probe_schema_uri(rhs._probe_schema_uri),
  _qms_schema_uri(rhs._qms_schema_uri),
  _request_channel(rhs._request_channel),
  _request_event_type(rhs._request_event_type),
  _data_channel(rhs._data_channel),
  _data_event_type(rhs._data_event_type),
  _host_addr(rhs._host_addr)
{
  QMS_Trace("Test_Client::Test_Client()", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::Test_Client()\n");

}

/**
 * @brief The = operator
 *
 * This avoids self assignements
 */
Test_Client&
Test_Client::operator=(const Test_Client &copy)
{
  QMS_Trace ("Test_Client::operator =", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Copy object\n");
  if(&copy != this)
   {
     this->_identity_p         = copy._identity_p ;
     this->_supplier_id        = copy._supplier_id ;
     this->_handles            = copy._handles ;
     this->_ec_registry        = copy._ec_registry ;     
     this->_parser_initialized = copy._parser_initialized ;     
     this->_category_name      = copy._category_name;
     this->_probe_schema_uri   = copy._probe_schema_uri;
     this->_qms_schema_uri     = copy._qms_schema_uri;
     this->_request_channel    = copy._request_channel;
     this->_request_event_type = copy._request_event_type;
     this->_data_channel       = copy._data_channel;
     this->_data_event_type    = copy._data_event_type;
     this->_host_addr          = copy._host_addr;
   }
  return *this;                 // enable cascaded assignments 
}

/// Destructor
Test_Client::~Test_Client()
{
  QMS_Trace ("Test_Client::~Test_Client()", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Test_Client::~Test_Client()\n");
}

/**
 * @brief initialize the object
 * @param handles A previously initialized CORBA Handles object
 * @param identity_p A string, used for trader registration, naming the object
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 */
void
Test_Client::init(STDC::QMS::CORBA_Handles &handles, char * identity_p, 
		  char * category_name_p, CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace ("Test_Client::init", __LINE__, __FILE__);
  DEBUG0 (28, "Initializing the client\n");

  // An identification string, to be used to get a supplier ID
  this->_identity_p = CORBA::string_dup(identity_p);

  // This is the category name of the probe we are going to be testing
  this->_category_name.erase();
  this->_category_name.assign(CORBA::string_dup(category_name_p));

  // Stash a local copy of the CORBA Handles
  this->_handles = handles;

  /// Get our IP address
  char hostname[ MAXNAMELEN ];
  char ip_address[1024];

  ACE_OS::hostname( hostname, MAXNAMELEN );
  struct hostent *hostinfo = ACE_OS::gethostbyname (hostname);

  in_addr address;
  address.s_addr = 
    (ACE_reinterpret_cast (in_addr * ,
			   hostinfo->h_addr_list[0])->s_addr);
  ACE_OS::strcpy(ip_address, inet_ntoa(address));
 
  this->_host_addr.erase();
  this->_host_addr.assign(ip_address);
  DEBUG1 (4, "DEBUG: Our IP address is %s\n", 
	  this->_host_addr.c_str());
  
  // From here there are a number of calls that must occur in
  // sequence. We could force the ordering, by setting boolean flags,
  // and explicitly enforcing the order, but that is not yet being
  // done for the sake of simplicity
  this->init_parser();
  DEBUG0 (26, "DEBUG:parser initialized\n");

  this->get_supplier_id(ACE_TRY_ENV);
  ACE_TRY_CHECK;
  DEBUG0 (28, "DEBUG: Got supplier ID\n");

  this->get_offers(ACE_TRY_ENV);
  ACE_TRY_CHECK;  
  DEBUG0 (28, "DEBUG: Got offers\n");
  DEBUG0 (28, "DEBUG: Finished init\n");
}

/**
 * @brief Using the information gathered in the init(), connect and run
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * This is where we use the data gathered before, and connect to the
 * event channel
 */
void
Test_Client::handle_offers(CosTrading::OfferSeq *offer_seq_ptr,
			   CosTrading::OfferIterator_var iterator,
			   CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace ("Test_Client::handle_offers", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG:Test_Client::handle_offers \n");

  DEBUG0 (4, "DEBUG: Trying to select offer\n");
  this->choose_offer(offer_seq_ptr, iterator, ACE_TRY_ENV);
  ACE_TRY_CHECK;
  DEBUG0 (4, "DEBUG: Selected Offer\n");

  this->connect_EC(ACE_TRY_ENV);  
  ACE_TRY_CHECK;
  cerr << "Client version " << version << " initialized." << endl;
}

/**
 * @brief This is where we perform cleanup operations for the sensor
 *
 * The actions taken include withdrawing our YP offer, walking through
 * the list of current probes, and performing a probe cleanup, 
 * cleaning up after the XML parser, and, fianlly, shutting down the ORB
 */
void
Test_Client::cleanup(void)
{
  QMS_Trace("Test_Client::cleanup", __LINE__,__FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG:Test_Client::cleanup");
  
  this->_consumer.disconnect();
  this->_supplier.disconnect();
  this->parser_cleanup();
  DEBUG0(28, "Client cleaned up");
  this->_handles.get_orb_handle()->shutdown ();
}

/**
 * @brief Validate an in memory XML  message 
 * @return true on success
 *
 * Since a message that fails to parse shall not generate any
 * diagnostics from the sensor (the sensor not having any idea about
 * the originator unless the message parses), we need to validate any
 * messages that we send out
 */
bool
Test_Client::check_message(string &message)
{
  QMS_Trace ("Test_Client::check__message", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "Test_Client::check__message\n");

  if(!this->_parser_initialized)
   {
     cerr << "Attempt to use the prser without initialization"
	  << __FILE__ << __LINE__ << endl;
     return false;
   } /* end of if(!this->_parser_initialized) */
  

  DEBUG0 (4,"Initializing the message_p\n");
  char *message_p = (char *)message.data();
  message_p[message.length()] = 0;

  DEBUG0 (4,"Initializing the buffer_p of type MemBufInputSource\n");
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
     DEBUG0 (4,"Creating the parser_p\n ");
     STDC::QMS::Parse_XML *parser_p = new STDC::QMS::Parse_XML();
     STDC::QMS::QMSMessage msg_header;
     
     DEBUG0 (4,"Validating the message to be sent.\n ");
     bool parsed_message = parser_p->parse_message(*buffer_p, msg_header);
     return parsed_message;
   }
  return false;
}


/**
 * @brief Initialize an XML Parser
 * 
 * This has to be done before the first invocation of the parser.
 */
void
Test_Client::init_parser(void)
{
  QMS_Trace("Test_Client::init_parser",__LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG:Test_Client::init_parser");
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
  DEBUG0(4, "DEBUG:parser initialized");
}

/**
 * @brief Cleanup the parser we created
 * 
 * This has to be done after we are all done with the parsers that
 * were used.
 */
void 
Test_Client::parser_cleanup(void)
{
  QMS_Trace("Test_Client::parser_cleanup",__LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG:Test_Client::parser_cleanup\n");
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
 * @brief Get a reference to the QMS Trader ECInfo component
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * First, if we already have a handle on the QMS Trader component, we
 * return immediately. If not, we query the CORBA Trading service for
 * the YP offer of the EC Info component, narrow it down, and stash
 * the object reference away.
 */
void
Test_Client::get_ec_registry(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Client::get_ec_registry", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::get_ec_registry\n");
  if(!CORBA::is_nil(this->_ec_registry.in()))
   {
     return;
   } /* end of if(!CORBA::is_nil(this->_ec_registry)) */
  
  ACE_TRY
    {
      CosTrading::Lookup_var lookup_var =
	this->_handles.get_lookup_handle(ACE_TRY_ENV);
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
		      "QMS_UNIQ_NAME_CATEGORY == 'QMS_TRADER' ",// IN contraint
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
	ACE_DEBUG ((LM_DEBUG, "Invalid name: %s\n", constex.constr.in ()));
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
Test_Client::get_supplier_id(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Client::get_supplier_id", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::get_supplier_id\n");
  
  ACE_TRY
    {
      if(CORBA::is_nil(this->_ec_registry.in()))
       {
	 this->get_ec_registry(ACE_TRY_ENV);
	 ACE_TRY_CHECK;
       } /* end of if(CORBA::is_nil(this->_ec_registry)) */
      string identity;
      identity.assign("Client for ");
      identity.append(this->_category_name);
      identity.append(" on host ");
      identity.append(this->_host_addr);

      this->_supplier_id =
	this->_ec_registry->getSupplierID(identity.c_str());
      ACE_TRY_CHECK;
      DEBUG1(2, "DEBUG: supplier id is %d\n", this->_supplier_id);
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error Getting Suppkier ID");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
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
Test_Client::get_offers(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Client::get_offers", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::get_offers\n");
  ACE_TRY
    {
      CosTrading::Lookup_var lookup_var =
	this->_handles.get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CosTrading::Lookup_ptr lookup_p = lookup_var.in();
      assert(lookup_p);
      assert(!CORBA::is_nil(lookup_p));
      
      // Perparing to do an import operation.  Should some of these go
      // into the sensor object itself?
      PolicySeq policies;	             //empty sequence
      
      CosTrading::Lookup::SpecifiedProps desired_props;  // No properties
      desired_props._d(Lookup::all);         // Return all properties
      
      CosTrading::PolicyNameSeq_var limits_applied;      // out param
      CosTrading::OfferSeq *offer_seq_ptr          = 0;
      CosTrading::OfferSeq_out      offers(offer_seq_ptr);
      CosTrading::OfferIterator_var iterator;


      /// Create a contraint for the query
      string constraint = "QMS_UNIQ_NAME_CATEGORY == '";
      constraint.append(this->_category_name);
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
	 ACE_TRY_THROW (CORBA::BAD_PARAM ());
       } /* end of if(offer_seq_out->length() == 0) */
      else
       {
	 this->handle_offers(offer_seq_ptr, iterator, ACE_TRY_ENV);
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

/**
 * @brief Select the first valid offer from those recieved
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 * @param offer_seq_ptr Pointer to a sequence of offers
 * @param iterator Offer iterator
 *
 * Here we narrow the reference associated with the ofers to a generic
 * QMS citizen (and not to the specific sensor we wish to talk to, for
 * portability between sensors). We then try and ping the sensor, and
 * if we get a result, we stash the properties of the selected offer. 
 */
void
Test_Client::choose_offer(CosTrading::OfferSeq *offer_seq_ptr,
			  CosTrading::OfferIterator_var iterator,
			  CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Client::choose_offer", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: Test_Client::choose_offer\n");
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
	  }
	catch(...)
	 {
	   DEBUG0 (2, "DEBUG: Failed to ping\n");
	   continue;
	  }
	this->handle_selected_properties(offer_seq[i].properties,
					    ACE_TRY_ENV);
	cerr << "ping succeeded\n";
	return;
      }
     
   } /* end of if(offer_seq_ptr) */
  
  
  // Well, the sequence failed us. Now we need to look at the iterator
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
	    }
	   catch(...)
	    {
	      DEBUG0 (2, "DEBUG: Failed to ping\n");
	      continue;
	    }
	   
	   this->handle_selected_properties(offers[i].properties,
					    ACE_TRY_ENV);
	   std::cerr << "ping succeeded\n";
	   return;
	 } /* end of for(i = 0; i < offers->length(); i++) */
      } 
     while(more);
   } /* end of if(!CORBA::is_nil(iterator.in())) */
  else
   {
     DEBUG0(2, "DEBUG: The iterator is null\n");
   } /* end of else */ 
  // If we reached here, we have an error
  throw STDC::QMS::QMS_Error();
} 

/**
 * @brief  Extracts an event channel name and event type from an XML fragment
 * @param  data The XML fragment
 * @param  id   Where the Event Type is returned
 * @param  name The evet cannel name is returned here
 *
 */
void 
Test_Client::extract_name_id (string &data, RtecEventComm::EventType &id,
			      string &name)
{
  DEBUG0(DEBUG_L_ENTER, "In get_name_id (....) Function\n");
  size_t location = 0;
  size_t start = 0;
  size_t stop = 0;

  location = data.find("<Event_Channel_Name>", location);
  if (location == string::npos)
   {
     cerr << "End of string encountered.\n";
   }
  location += strlen("<Event_Channel_Name>");
  start = location;

  location = data.find("</Event_Channel_Name>", location);
  if (location == string::npos)
   {
     cerr << "End of string encountered.\n";
   }
  stop = location;

  name.assign( (data.substr(start, stop - start)).data() );

  location += strlen("</Event_Channel_Name>");
  location = data.find("<Event_Type>", location);
  if (location != string::npos)
   {
     location += strlen("<Event_Type>");
     start = location;
     location = data.find("</Event_Type>", location);
     if (location == string::npos)
      {
	cerr << "End of string encountered.\n";
      }
     stop = location;

     string x;
     x.assign( (data.substr(start, stop - start)).data() );
     id = CORBA::Long ( atol(x.c_str()) ) ;
   }

  DEBUG2(2, "Channel Name->%s\t Event Id->%d\n", name.c_str(),id);
}

/**
 * @brief Extract information from the stashed properties of the selected offer
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 * @param selected_properties The properties of the offer we select
 *
 */
void
Test_Client::handle_selected_properties(const CosTrading::PropertySeq &
					selected_properties,
					CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Client::handle_selected_properties", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::handle_selected_properties\n");
  ACE_TRY
    {
      TAO_Property_Evaluator_By_Name prop_val(selected_properties,
					      ACE_TRY_ENV);

      CORBA::Any* value = 0;
      const char * value_p;
      
      value =  prop_val.property_value((const char *)"PROBE_SCHEMA_URI",
				       ACE_TRY_ENV);
      (*value) >>= value_p;
      this->_probe_schema_uri.assign(value_p);
      DEBUG1(4, "DEBUG: probe schema %s\n", this->_probe_schema_uri.c_str());

      value =  prop_val.property_value((const char *)"QMS_SCHEMA_URI",
				       ACE_TRY_ENV);
      (*value) >>= value_p;
      this->_qms_schema_uri.assign(value_p);
      DEBUG1(4, "DEBUG: QMS schema %s\n", this->_qms_schema_uri.c_str());

      value =  prop_val.property_value((const char *)"Request_0",
				       ACE_TRY_ENV);
      (*value) >>= value_p;
      
      string data = value_p;
      extract_name_id (data, this->_request_event_type,
		       this->_request_channel);
      DEBUG2(4, "DEBUG: request %s %d\n", this->_request_channel.c_str(),
	     this->_request_event_type);
      
      value =  prop_val.property_value((const char *)"Data_0",
				       ACE_TRY_ENV);
      (*value) >>= value_p;

      data = value_p;
      extract_name_id (data, this->_data_event_type,
		       this->_data_channel);
      DEBUG2(4, "DEBUG: data %s %d\n", this->_data_channel.c_str(),
	     this->_data_event_type);
      
      
    } 
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, 
			   "System Exception getting sensor offer:");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex,
			   "User Exception getting sensor offer:");
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
			   "Error getting sensor");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}
/**
 * @brief Connect to the event channel using the values extracted
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 * @return true if some offers were found
 *
 * This is where we connect the Push supplier on the request event
 * channel, and register the fact that we shall be sending requests
 * with the event type specified. Additionally, we connect a push
 * consumer on to the data channel, and subscribe to the event types
 * as defined in the offer we have selected. We also register a
 * callback that shall handle the data coming in from the sensor
 */
void
Test_Client::connect_EC(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Client::connect_EC", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::connect_EC\n");
  ACE_TRY
    {
      // initialize a supplier
      this->_supplier.init(this->_handles, (int)this->_request_event_type,
			   (int)this->_supplier_id, 
			   this->_request_channel.c_str(), ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0(4, "DEBUG: supplier initialized\n");
      
      // Initialize the consumer
      this->_consumer.init(this->_handles, (int)this->_data_event_type,
			   this->_data_channel.c_str(), ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0(4, "DEBUG: consumer initialized\n");

      // Register the callback for the consumer
      this->_consumer.register_callback(&this->callback, (void *)this);
      DEBUG0(4, "DEBUG: registerr callback\n");
      
      // connect the supplier
      this->_supplier.connect(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0(4, "DEBUG: supplier connected\n");
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error initializing EC");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
  
  /// So far, we have not done anything that really needs undoing
  /// before aborting. From this point on, the supplier needs to be
  /// disconnected on error
  
  ACE_TRY
    {
      //connect the consumer
      this->_consumer.connect(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0(4, "DEBUG: consumer connected\n");
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error Connecting the consumer");
      this->_supplier.disconnect();
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}

/**
 * @brief The callback function to handle incoming data
 * @param response The incoming message to handle
 * @param arg_p A pointer to a Client Object
 *
 */
void
Test_Client::callback(const string &response, void *arg_p)
{
  QMS_Trace("Test_Client::callback", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::callback\n");
  DEBUG1(2, " The response is -> %s\n", response.c_str());
  Test_Client * client_p = (Test_Client *)arg_p;
  
  //
  //  Create MemBufferInputSource from the buffer containing the XML
  //  statements.
  //
  //  NOTE: We are using strlen() here, since we know that the chars in
  //  our hard coded buffer are single byte chars!!! The parameter wants
  //  the number of BYTES, not chars, so when you create a memory buffer
  //  give it the byte size (which just happens to be the same here.)
  //

  DEBUG0 (4,"Initializing the message_p\n");
  char *message_p = (char *)response.data();
  message_p[response.length()] = 0;

  DEBUG0 (4,"Initializing the buffer_p of type MemBufInputSource\n");
  MemBufInputSource *buffer_p = new MemBufInputSource((const XMLByte*)
						      message_p,
						      strlen(message_p),
						      "QMSMessage",
						      false);

  //  Parse the XML file, catching any XML exceptions that might propogate
  //  out of it.
  if(buffer_p)
   {
     DEBUG0 (4,"Creating the parser_p\n ");
     STDC::QMS::Parse_XML *parser_p = new STDC::QMS::Parse_XML();
     STDC::QMS::QMSMessage msg_header;
     // set default values
     msg_header.sequence_no = INT_MAX;
     msg_header.msgDate.erase();
     msg_header.msgTime.erase();
     msg_header.sender_host.erase();
     msg_header.sender.id = INT_MAX;
     msg_header.sender.description.erase();

     for ( unsigned int i = 0; i < msg_header.destinations.size() ; i++ )
      {
	msg_header.destinations[i].id = ( unsigned long ) 0;
	msg_header.destinations[i].description.erase();
      }
     
     msg_header.QMSUniqueName.category.erase();
     msg_header.QMSUniqueName.host.erase();
     msg_header.QMSUniqueName.uuid.erase();
     msg_header.Session.request_id = INT_MAX;
     msg_header.Session.data_id = INT_MAX;
     msg_header.Session.version = INT_MAX;
     msg_header.Session.repititions.count = 1;
     msg_header.Session.repititions.current = 0;
     msg_header.Session.interval = "PT5S";
     msg_header.Session.scope.erase();
     msg_header.Session.forceReuse = false;
     msg_header.Session.qos_params.Priority = 10;
	
     struct Payload_Data response_data;
     struct PerfMon_Payload_Data perfmon_response_data;
     bool parsed_message;
	
     DEBUG0 (4,"Parsing the received message.\n ");
	
     if ((strcmp(client_p->_category_name.c_str(),"QMS_CPU_Utilization")
	 == 0 ) ||
	 (strcmp(client_p->_category_name.c_str(),"QMS_Memory_Utilization")
	 == 0 ) ||
	 (strcmp(client_p->_category_name.c_str(),"QMS_Swap_Utilization")
	  == 0 ) ||
	 (strcmp(client_p->_category_name.c_str(),"QMS_Disk_Utilization")
	  == 0 ) ||
	 (strcmp(client_p->_category_name.c_str(),"QMS_Network")
	  == 0 ) ||
	 (strcmp(client_p->_category_name.c_str(),"QMS_Network_Bytes")
	  == 0 )
	 )
      {
	parsed_message = 
	  parser_p->parse_message(*buffer_p, msg_header,
				  payload_Handler,
				  (void *) &perfmon_response_data);
      }
     else 
      {
	parsed_message = 
	  parser_p->parse_message(*buffer_p, msg_header,
				  payload_Handler,
				  (void *) &response_data);
      }
	
	
     if(parsed_message)
      {
	DEBUG0 (4,"Successfully parsed the message\n");
	if(!msg_header.QMSUniqueName.category.empty())
	 {
	   DEBUG0 (4,"QMSUniqueName is not empty\n");
	   if (strcmp (msg_header.QMSUniqueName.category.c_str(),
		       client_p->_category_name.c_str()) != 0 )
	    {
	      cerr << "ERROR: Recieved a response for category "
		   << msg_header.QMSUniqueName.category << std::endl
		   << "Which I do not have any knowledge of." << std::endl
		   << "I was Looking for " << client_p->_category_name
		   << std::endl << "\tAborting" << std::endl
		   << response;
	    } 
	   else 
	    {
	      DEBUG1 (4,"QMSUniqueName is %s \n", 
		      msg_header.QMSUniqueName.category.c_str());
		 
	      for ( unsigned int j = 0; j < msg_header.destinations.size();
		    j++ )
	       {
		 if ( msg_header.destinations[j].id == 
		      (unsigned long )client_p->_supplier_id )
		  {
		    if ((strcmp(client_p->_category_name.c_str(),
			       "QMS_CPU_Utilization") == 0 ) ||
			(strcmp(client_p->_category_name.c_str(),
				"QMS_Memory_Utilization") == 0 ) ||
			(strcmp(client_p->_category_name.c_str(),
				"QMS_Swap_Utilization") == 0 ) ||
			(strcmp(client_p->_category_name.c_str(),
				"QMS_Disk_Utilization") == 0 ) ||
			(strcmp(client_p->_category_name.c_str(),
				"QMS_Network") == 0 ) ||
			(strcmp(client_p->_category_name.c_str(),
				"QMS_Network_Bytes") == 0 )
			)
		     {
		       perfmon_payload_print(msg_header.QMSUniqueName.host,
					     perfmon_response_data);   
		     }
		    else 
		     {
		       payload_print(msg_header.QMSUniqueName.host,
				     response_data);
		     }
		  }
	       }
	    } 
	 }
	else
	 {
	   cerr << "ERROR: message did not have a valid category" 
		<< std::endl
		<< "\tAborting" << std::endl
		<< "I got " << msg_header.QMSUniqueName.category 
		<< std::endl
		<< response;
	 } 
      }
     else
      {
	cerr << "Error: parsing message" << std::endl
	     << "\tAborting" << std::endl
	     << response;
      } 
   }
  else 
   {
     DEBUG0 (4,"buffer_p is null !!!!\n");
   }
  DEBUG0 (4,"Deleting the memory allocated for the  buffer_p\n");
  delete buffer_p;  
}

/**
 * @brief Validate an in memory XML  message 
 * @return true on success
 *
 * Since a message that fails to parse shall not generate any
 * diagnostics from the sensor (the sensor not having any idea about
 * the originator unless the message parses), we need to validate any
 * messages that we send out
 */
bool
check_message(string &message)
{
  QMS_Trace ("check__message", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "check__message\n");
 
  DEBUG0 (4,"Initializing the message_p\n");
  char *message_p = (char *)message.data();
  message_p[message.length()] = 0;


  DEBUG0 (4,"Initializing the buffer_p of type MemBufInputSource\n");
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
     DEBUG0 (4,"Creating the parser_p\n ");
     STDC::QMS::Parse_XML *parser_p = new STDC::QMS::Parse_XML();
     STDC::QMS::QMSMessage msg_header;
     
     DEBUG0 (4,"Parsing the received message.\n ");
     bool parsed_message = parser_p->parse_message(*buffer_p, msg_header);
     return parsed_message;
   }
  return false;
}

/**
 * @brief Create a in memory message to be sent to the sensor
 * @param version The version of the message. 0 means reqwuest
 * @param data The string the message shall be stuffed into
 * @param action The action to take on non 0 versions (request modification)
 */
void
Test_Client::create_message(long version, string &data, const char *action)
{
  QMS_Trace("Test_Client::create_message", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::create_message\n");
  
  /// Start off with a sequence number that is artificially inflated
  long sequence_no = 1000;
  /// The request number of this request
  long request_id = 1;
  /// temporary storage for the message
  char message[8192 + BUFSIZ];
  /// The interval requested between messages
  string interval = "PT5.0S";
  /// The number of repetitions of messages
  int repetitions = 200;
 

  time_t this_time = time(0);
  struct tm *now_p = gmtime((const time_t *) &this_time);

  char * payload_p = 0;

  if ((strcmp(this->_category_name.c_str(),"QMS_CPU_Utilization") == 0 ) ||
      (strcmp(this->_category_name.c_str(),"QMS_Memory_Utilization") == 0 ) ||
      (strcmp(this->_category_name.c_str(),"QMS_Swap_Utilization")== 0 ) ||
      (strcmp(this->_category_name.c_str(),"QMS_Disk_Utilization")== 0 ) ||
      (strcmp(this->_category_name.c_str(),"QMS_Network") == 0 ) ||
      (strcmp(this->_category_name.c_str(),"QMS_Network_Bytes") == 0 )
      )
   {
     payload_p = perfmon_payload_generator(this->_probe_schema_uri, action);
   }
  else 
   {
     payload_p = payload_generator(this->_probe_schema_uri, action);
   }

  int ret = 
    snprintf (message, 8192 + BUFSIZ, request_fmt, 
	      this->_qms_schema_uri.c_str(), 
	      sequence_no + version, 
	      (1900 + now_p->tm_year),(1 + now_p->tm_mon), now_p->tm_mday,
	      now_p->tm_hour, now_p->tm_min, now_p->tm_sec,
	      this->_host_addr.c_str(), this->_supplier_id, 
	      this->_category_name.c_str(),
	      request_id, version, repetitions, interval.c_str(),
	      payload_p);
  if(ret == -1 || ret >= (8192 + BUFSIZ))
   {
     cerr << "Buffer overflow in outgoing message"
	  << std::endl;
   } /* end of if(ret) */
  data.assign((char *)message);
  delete [] payload_p;
}

/** 
 *  @brief  Send the test messages for the probe
 *  
 *  Use the stored information to send messages to the probe
 *
 *    -# Send first name and last name.
 *    -# Send pause action message.
 *    -# Send kill action message , which is a wrong command.
 *    -# Send restart action message, which is a wrong command.
 *    -# Send resume action message.
 *    -# Send stop action message.
 *
 */
void
Test_Client::send_messages(void *arg_p)
{
  QMS_Trace("Test_Client::send_messages", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Client::messages\n");
  Test_Client * client_p = (Test_Client *) arg_p;
  
  // The data to be sent
  string data;
  
  /// initially, the version is 0, meaning that this is the first request
  long version = 0; 
  
  cerr << "Sleeping for 6 seconds before starting\n";
  // Sleeping 6 secs before start sending the request messages.
  ACE_OS::sleep (ACE_Time_Value (6));
  
  cerr << "Sending the Request\n";
  client_p->create_message(version++, data, "start");
  if(client_p->check_message(data))
   {
     client_p->_supplier.send(data);
   } /* end of if(check_message(data)) */
  else
   {
     cerr << "Message failed to validate" << data << endl;
     cerr << "Still continuing" << endl;
   } /* end of else */
  ACE_OS::sleep (ACE_Time_Value (20));

  cerr << "Sending the Request containing STOP command \n";
  data.erase();
  client_p->create_message(version++, data, "stop");
  if(client_p->check_message(data))
   {
     client_p->_supplier.send(data);
   } /* end of if(check_message(data)) */
  else
   {
     cerr << "Message failed to validate" << data << endl;
     cerr << "Still continuing" << endl;
   } /* end of else */

  cerr << "Sending all done\n";
  DEBUG0 (6, "Sleeping for 10 secs\n ");
  cerr << "Ensuring we've got all the messages - waiting for 30 seconds \n";
  ACE_OS::sleep (ACE_Time_Value (30));
 
  client_p->cleanup();
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class list<string>;

#if defined(__GNUC_MINOR__) && __GNUC_MINOR__ > 92
template class _List_base<string, allocator<string > >;

template void list<string>::_M_insert_dispatch<_List_iterator<string, string const &, string const *> >(_List_iterator<string, string &, string *>, _List_iterator<string, string const &, string const *>, _List_iterator<string, string const &, string const *>, __false_type);

#else

template void list<string, __default_alloc_template<true, 0> >::insert<__list_iterator<string, string const &, string const *> >(__list_iterator<string, string &, string *>, __list_iterator<string, string const &, string const *>, __list_iterator<string, string const &, string const *>);

#endif

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

