//                              -*- Mode: C++ -*- 
// Receiver.cpp --- 
// Author           : Manoj Srivastava ( srivasta@ember.green-gryphon.com ) 
// Created On       : Fri Dec 14 11:22:51 2001
// Created On Node  : ember.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Fri Dec 14 11:54:57 2001
// Last Machine Used: ember.green-gryphon.com
// Update Count     : 13
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

/** @file 
 *  @ingroup GenericSensor 
 *  @brief  A Generic Client that just listens
 *
 * $Id: Receiver.cpp,v 1.3 2001/12/15 02:52:38 srivasta Exp $
 */
/// RCS version string
static const char* version = 
"$Id";

#include "Receiver.h"

#if defined(_WIN32)
#  define snprintf _snprintf
#endif

/// Constructor
Test_Receiver::Test_Receiver() :
  _identity_p(0), _data_event_type(0),_host_addr(""),
  _limiter_p(const_cast< char * >("qms:payload>"))
{
  QMS_Trace("Test_Receiver::Test_Receiver()", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Receiver::Test_Receiver()\n");

}

/**
 * @overload
 */
Test_Receiver::Test_Receiver(const Test_Receiver& rhs) :
  _identity_p(rhs._identity_p), 
  _handles(rhs._handles), 
  _category_name(rhs._category_name), 
  _data_channel(rhs._data_channel),
  _data_event_type(rhs._data_event_type),
  _host_addr(rhs._host_addr), _limiter_p(rhs._limiter_p)
{
  QMS_Trace("Test_Receiver::Test_Receiver()", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Receiver::Test_Receiver()\n");

}

/**
 * @brief The = operator
 *
 * This avoids self assignements
 */
Test_Receiver&
Test_Receiver::operator=(const Test_Receiver &copy)
{
  QMS_Trace ("Test_Receiver::operator =", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Copy object\n");
  if(&copy != this)
   {
     this->_identity_p         = copy._identity_p ;
     this->_handles            = copy._handles ;
     this->_category_name      = copy._category_name;
     this->_data_channel       = copy._data_channel;
     this->_data_event_type    = copy._data_event_type;
     this->_host_addr          = copy._host_addr;
     this->_limiter_p          = copy._limiter_p;
   }
  return *this;                 // enable cascaded assignments 
}

/// Destructor
Test_Receiver::~Test_Receiver()
{
  QMS_Trace ("Test_Receiver::~Test_Receiver()", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Test_Receiver::~Test_Receiver()\n");
}

/**
 * @brief initialize the object
 * @param handles A previously initialized CORBA Handles object
 * @param identity_p A string, used for trader registration, naming the object
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 */
void
Test_Receiver::init(STDC::QMS::CORBA_Handles &handles, char * identity_p, 
		    char * category_name_p, char *limiter_p, 
		    CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace ("Test_Receiver::init", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG:Test_Receiver::init \n");

  // An identification string, to be used to get a supplier ID
  this->_identity_p = CORBA::string_dup(identity_p);
  this->_limiter_p  = limiter_p;
  
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
  this->get_offers(ACE_TRY_ENV);
  ACE_TRY_CHECK;  
  DEBUG0 (4, "DEBUG: Got offers\n");
  DEBUG0 (4, "DEBUG: Finished init\n");
}

/**
 * @brief Using the information gathered in the init(), connect and run
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * This is where we use the data gathered before, and connect to the
 * event channel
 */
void
Test_Receiver::handle_offers(CosTrading::OfferSeq *offer_seq_ptr,
			   CosTrading::OfferIterator_var iterator,
			   CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace ("Test_Receiver::handle_offers", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG:Test_Receiver::handle_offers \n");

  DEBUG0 (4, "DEBUG: Trying to select offer\n");
  this->choose_offer(offer_seq_ptr, iterator, ACE_TRY_ENV);
  ACE_TRY_CHECK;
  DEBUG0 (4, "DEBUG: Selected Offer\n");

  this->connect_EC(ACE_TRY_ENV);  
  ACE_TRY_CHECK;
  cerr << "Client version " << version << "initialized." << endl;
}

/**
 * @brief This is where we perform cleanup operations for the sensor
 *
 * The actions taken include withdrawing our YP offer, walking through
 * the list of current probes, and performing a probe cleanup, 
 * cleaning up after the XML parser, and, fianlly, shutting down the ORB
 */
void
Test_Receiver::cleanup(void)
{
  QMS_Trace("Test_Receiver::cleanup", __LINE__,__FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG:Test_Receiver::cleanup");
  
  this->_consumer.disconnect();
  DEBUG0(4, "Client cleaned up");
  this->_handles.get_orb_handle()->shutdown ();
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
Test_Receiver::get_offers(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Receiver::get_offers", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Receiver::get_offers\n");
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
Test_Receiver::choose_offer(CosTrading::OfferSeq *offer_seq_ptr,
			  CosTrading::OfferIterator_var iterator,
			  CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Receiver::choose_offer", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: Test_Receiver::choose_offer\n");
  int length = 0;
  int i = 0;
  
  const CosTrading::OfferSeq& offer_seq = *offer_seq_ptr;
  for (length = offer_seq.length (), i = 0; i < length; i++)
   {
     // Call back to the exported object.
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
     this->handle_selected_properties(offer_seq[i].properties,
				      ACE_TRY_ENV);
     cerr << "ping succeded\n";
     return;
   }
  
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
	   
 	   this->handle_selected_properties(offers[i].properties,
					    ACE_TRY_ENV);
 	   DEBUG0(4, "DEBUG: ping succeded\n");
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
Test_Receiver::extract_name_id (string &data, RtecEventComm::EventType &id,
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
Test_Receiver::handle_selected_properties(const CosTrading::PropertySeq &
					selected_properties,
					CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Receiver::handle_selected_properties", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Receiver::handle_selected_properties\n");
  ACE_TRY
    {
      TAO_Property_Evaluator_By_Name prop_val(selected_properties,
					      ACE_TRY_ENV);

      CORBA::Any* value = 0;
      const char * value_p;
      
      value =  prop_val.property_value((const char *)"Data_0",
				       ACE_TRY_ENV);
      (*value) >>= value_p;
      
      string data = value_p;
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
Test_Receiver::connect_EC(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("Test_Receiver::connect_EC", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Receiver::connect_EC\n");
  ACE_TRY
    {
      // Initialize the consumer
      this->_consumer.init(this->_handles, (int)this->_data_event_type,
			    this->_data_channel.c_str(), ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0(4, "DEBUG: consumer initialized\n");

      // Register the callback for the consumer
      this->_consumer.register_callback(&this->callback, (void *)this);
      DEBUG0(4, "DEBUG: registerr callback\n");
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
Test_Receiver::callback(const string &response, void *arg_p)
{
  QMS_Trace("Test_Receiver::callback", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: Test_Receiver::callback\n");
  DEBUG1(2, " The response is -> %s\n", response.c_str());
  Test_Receiver * client_p = (Test_Receiver *)arg_p;

  string message = response;
  string::size_type  location = 0;

  string start_tag("<");
  start_tag.append(client_p->_limiter_p);
  start_tag.append(">");

  string end_tag("</");
  end_tag.append(client_p->_limiter_p);
  end_tag.append(">");

  location = message.find(start_tag);
  if (location == string::npos)
   {
     location = message.find("<qms:error>");
     if(location == string::npos)
      {
	std::cerr << "Could not parse message:\n" << message;
      } /* end of if(location == string::npo) */
     else
      {
	message.erase(0, location);
	location = message.find("</qms:error>");
	if(location != string::npos)
	 {
	   message.erase(location);
	 } /* end of if(location == string::npos) */
      } /* end of else */ 
   }
  else
   {
     message.erase(0, location);
     location = message.find(end_tag);
     if(location != string::npos)
      {
	message.erase(location);
      } /* end of if(location == string::npos) */
   } /* end of else */
  std::cout << "<!-- ===================================== -->" << std::endl
	    << message
	    << std::endl
	    << "<!-- ===================================== -->" << std::endl
    ;
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

