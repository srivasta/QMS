//                              -*- Mode: C++ -*-
// Multi_Client.cpp ---
// Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com )
// Created On       : Tue Dec 11 20:03:35 2001
// Created On Node  : glaurung.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Jan  8 22:39:37 2002
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 53
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
version = "$Id: Multi_Client.cpp,v 1.45 2002/01/15 21:23:51 srivasta Exp $";
/** @file
 *  @ingroup Gateway
 *  @brief Convenience object to parse QMS XML documents
 *
 * $Id: Multi_Client.cpp,v 1.45 2002/01/15 21:23:51 srivasta Exp $
 */

#include "Multi_Client.h"
#include <exception>
#include <stdexcept>


extern void callback(const string &response, void *arg_p);

/// Format string for the request
const char *request_fmt = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>                      \n\
<qms:QMSMessage xmlns=\"http://www.stdc.com/2001/QMSSchema\"    \n\
  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"       \n\
  xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"              \n\
  xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema %s\"> \n\
  <qms:msgSequenceNo>%ld</qms:msgSequenceNo>                    \n\
  <qms:msgDate>%d-%d-%d</qms:msgDate>                           \n\
  <qms:msgTime>%d:%d:%d-0:00</qms:msgTime>                      \n\
  <qms:originatingHost>%s</qms:originatingHost>                 \n\
  <qms:msgSender>                                               \n\
    <id>%d</id>                                                 \n\
    <description>Test client for a QMS Probe</description>      \n\
  </qms:msgSender>                                              \n\
  <qms:msgDestination>                                               \n\
    <id>%s</id>                                                 \n\
  </qms:msgDestination>                                              \n\
  <qms:QMSUniqueName>                                           \n\
    <category>%s</category>                                     \n\
  </qms:QMSUniqueName>                                          \n\
  <qms:Session>                                                 \n\
    <requestID>%ld</requestID>                                  \n\
    <version>%ld</version>                                      \n\
    <minRepetitions>                                            \n\
     <count>%d</count>                                          \n\
    </minRepetitions>                                           \n\
    <minRepeatInterval>%s</minRepeatInterval>                   \n\
  </qms:Session>                                                \n\
  <qms:payload>                                                 \n\
    %s                                                          \n\
  </qms:payload>                                                \n\
</qms:QMSMessage>                                               \n\
";

/**
 *  @brief The constructor
 *
 *
 */
STDC::QMS::Multi_Client::Multi_Client() : handles_p_(0),
					  _supplier_id(0),
					  _hostname_p(0),
					  _ip_address_p(0),
					  _uuid_p(0),
					  _request_id(1)
{
  QMS_Trace ("STDC::QMS::Multi_Client::Multi_Client", __LINE__,__FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Multi_Client created\n");
}

/**
 *  @overload
 *
 */
STDC::QMS::Multi_Client::Multi_Client(const STDC::QMS::Multi_Client&rhs) :
  handles_p_(rhs.handles_p_), _supplier_id(rhs._supplier_id),
  _message(rhs._message),   _probe_schema_uri(rhs._probe_schema_uri),
  _qms_schema_uri(rhs._qms_schema_uri),
  _destination_id(rhs._destination_id),
  _request_channel(rhs._request_channel),
  _request_event_type(rhs._request_event_type),
  _data_channel(rhs._data_channel),
  _data_event_type(rhs._data_event_type),
  _hostname_p(rhs._hostname_p),
  _ip_address_p(rhs._ip_address_p),
  _uuid_p(rhs._uuid_p),
  _request_id(rhs._request_id)
{
  QMS_Trace ("STDC::QMS::Multi_Client::Multi_Client", __LINE__,
             __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Multi_Client created\n");

}

/// The destructor
STDC::QMS::Multi_Client::~Multi_Client()
{
  QMS_Trace ("STDC::QMS::Multi_Client::~Multi_Client", __LINE__,
             __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Multi_Client destroyed\n");

}

/// The assignment operator
STDC::QMS::Multi_Client &
STDC::QMS::Multi_Client::operator=(const STDC::QMS::Multi_Client& rhs)
{
  QMS_Trace ("STDC::QMS::Multi_Client::Multi_Client", __LINE__,
             __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Multi_Client created\n");
  this->handles_p_   = rhs.handles_p_;
  this->_supplier_id = rhs._supplier_id;
  this->_message.assign(rhs._message);
  this->_probe_schema_uri   = rhs._probe_schema_uri;
  this->_qms_schema_uri     = rhs._qms_schema_uri;
  this->_destination_id     = rhs._destination_id;
  this->_request_channel    = rhs._request_channel;
  this->_request_event_type = rhs._request_event_type;
  this->_data_channel       = rhs._data_channel;
  this->_data_event_type    = rhs._data_event_type;
  this->_hostname_p         = rhs._hostname_p;
  this->_ip_address_p       = rhs._ip_address_p;
  this->_uuid_p             = rhs._uuid_p;
  this->_request_id         = rhs._request_id;
  return *this;
}

void
STDC::QMS::Multi_Client::send(long sequence_no, 
			      STDC::QMS::BV_RequestType &config,
			      char * message_p)
{
  QMS_Trace ("STDC::QMS::Multi_Client::send", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Multi_Client sending\n");
  string my_category = config.data_request.QMSUniqueName.category;

  /// temporary storage for the message
  DEBUG0 (2, "DEBUG: creating message\n");
  ssize_t length;
  string payload;
  string outgoing_message = message_p;

  string::size_type start;
  string::size_type stop;
  start = outgoing_message.find("<qms:payload>");
  if(start != string::npos)
   {
     start += strlen("<qms:payload>");
     stop = outgoing_message.find("</qms:payload>");
     if(stop != string::npos)
      {
	payload.append((outgoing_message.substr(start, 
						stop - start)).c_str());
      } /* end of if(stop != string::npos) */
   } /* end of if(start != string::npos) */


  length = strlen(request_fmt) +1;
  length += payload.size();
  length += 8192;
  time_t this_time = time(0);
  struct tm *now_p = gmtime((const time_t *) &this_time);


  char *message = new char[length];
  int ret =
    snprintf (message, length, request_fmt,
	      this->_qms_schema_uri.c_str(),
	      sequence_no,
	      (1900 + now_p->tm_year),(1 + now_p->tm_mon),
	      now_p->tm_mday,
	      now_p->tm_hour, now_p->tm_min, now_p->tm_sec,
	      this->_ip_address_p, this->_supplier_id,
	      this->_destination_id.c_str(),
	      config.data_request.QMSUniqueName.category.c_str(),
	      config.data_request.request_id, 1,
	      86400,
	      config.data_request.interval.c_str(),
	      payload.c_str());
  if(ret == -1 || ret >= (8192 + BUFSIZ))
   {
     cerr << "Buffer overflow in outgoing message"
	  << std::endl;
   } /* end of if(ret) */
  DEBUG1 (2, "DEBUG: Message is\n%s\n", message);
  string data(message);
  DEBUG0 (2, "DEBUG: Sending Message\n");
  this->_supplier.send(data);
  delete [] message;
  return;
}

void
STDC::QMS::Multi_Client::init (char *message_p,
			       STDC::QMS::BV_RequestType &config,
			       STDC::QMS::CORBA_Handles *handles_p,
			       CORBA::Long supplier_id,
			       long sequence_no,
			       const char *hostname_p,
			       const char *ip_address_p,
			       const char *uuid_p,
			       CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::Multi_Client::init", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::init\n");
  if(handles_p)
   {
     this->handles_p_ = handles_p;
   } /* end of if(handles_p) */
  this->_supplier_id = supplier_id;
  this->_config = config;
  this->_hostname_p = hostname_p;
  this->_ip_address_p = ip_address_p;
  this->_uuid_p = uuid_p;
  this->_request_id = sequence_no;
  this->_message.assign(message_p);

  try
   {
     this->get_offers(ACE_TRY_ENV);
     this->connect_EC(ACE_TRY_ENV);
   }
  catch (...)
   {
     std::cerr << "Error exception caught" << std::endl;
     throw;
   }
  
  DEBUG0 (2, "DEBUG: All connected\n");
  string my_category = config.data_request.QMSUniqueName.category;

  string payload;
  string incoming_message = message_p;

  string::size_type start;
  string::size_type stop;
  start = incoming_message.find("<qms:payload>");
  if(start != string::npos)
   {
     start += strlen("<qms:payload>");
     stop = incoming_message.find("</qms:payload>");
     if(stop != string::npos)
      {
	payload.append((incoming_message.substr(start, 
						stop - start)).c_str());
      } /* end of if(stop != string::npos) */
   } /* end of if(start != string::npos) */
	
  ssize_t length;
  length = strlen(request_fmt) +1;
  length += strlen(message_p);
  length += payload.size() + 1;
  length += 8192;
  time_t this_time = time(0);
  struct tm *now_p = gmtime((const time_t *) &this_time);


  char *message = new char[length];
  int ret =
    snprintf (message, length, request_fmt,
	      this->_qms_schema_uri.c_str(),
	      sequence_no,
	      (1900 + now_p->tm_year),(1 + now_p->tm_mon),
	      now_p->tm_mday,
	      now_p->tm_hour, now_p->tm_min, now_p->tm_sec,
	      this->_ip_address_p, this->_supplier_id,
	      this->_destination_id.c_str(),
	      config.data_request.QMSUniqueName.category.c_str(),
	      this->_request_id, 0,
	      config.data_request.count.count,
	      config.data_request.interval.c_str(),
	      payload.c_str());
  if(ret == -1 || ret >= (8192 + BUFSIZ))
   {
     cerr << "Buffer overflow in outgoing message"
	  << std::endl;
   } /* end of if(ret) */
  string data(message);
  DEBUG1 (2, "DEBUG: sending request \n%s\n\n", message);
  this->_supplier.send(data);
  delete [] message;
  return;
}

void
STDC::QMS::Multi_Client::add_handle(STDC::QMS::CORBA_Handles *handles_p)
{
  QMS_Trace ("STDC::QMS::Multi_Client::add_handle", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::add_handle\n");
  if(!handles_p)
   {
     throw std::invalid_argument::invalid_argument("empty corba handles");
   } /* end of if(!handles_p) */
  this->handles_p_ = handles_p;
  if(!this->handles_p_)
   {
     throw
       std::invalid_argument::invalid_argument("corba handles assignment failed");
   } /* end of if(!this->handles_p_) */
}

STDC::QMS::CORBA_Handles *
STDC::QMS::Multi_Client::get_handle(void)
{
  QMS_Trace ("STDC::QMS::Multi_Client::get_handle", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::get_handle\n");
  return this->handles_p_;
}

/**
 * @brief  Extracts an event channel name and event type from an XML fragment
 * @param  data The XML fragment
 * @param  id   Where the Event Type is returned
 * @param  name The evet cannel name is returned here
 *
 */
void
STDC::QMS::Multi_Client::extract_name_id(string &data,
					 RtecEventComm::EventType &id,
					 string &name)
{
  QMS_Trace ("STDC::QMS::Multi_Client::extract_name_id", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::extract_name_id\n");

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

  name.assign( (data.substr(start, stop - start)).c_str() );

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
     x.assign( (data.substr(start, stop - start)).c_str() );
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
STDC::QMS::Multi_Client::handle_selected_properties(const CosTrading::PropertySeq &
						    selected_properties,
						    CORBA_Environment &
						    ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Multi_Client::handle_selected_properties", __LINE__,
	    __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Multi_Client::handle_selected_properties\n");
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


      value =  prop_val.property_value((const char *)"SUPPLIER_ID",
				       ACE_TRY_ENV);
      CORBA::ULong     ulong_val;
      (*value) >>= ulong_val;
      char values[20];
      values[0]=0;
      int ret = snprintf(values, 100, "%ld", ulong_val);
      if(ret < 0 || ret > 100)
       {
	 std::cerr << "Error creating property value" << std::endl;
       } /* end of if(ret < 0 || ret > 100) */
      
      this->_destination_id.assign(values);
      DEBUG1(4, "DEBUG: Destination ID %s\n", this->_destination_id.c_str());



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

void
STDC::QMS::Multi_Client::handle_offers(CosTrading::OfferSeq *offer_seq_ptr,
				       CosTrading::OfferIterator_var iterator,
				       CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::Multi_Client::handle_offers", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::handle_offers\n");
  int length = 0;
  int i = 0;


  if(offer_seq_ptr)
   {
     DEBUG0 (2, "DEBUG: We have some offers\n");
     const CosTrading::OfferSeq& offer_seq = *offer_seq_ptr;
     DEBUG1 (2, "DEBUG: We have %d offers\n", offer_seq.length ());
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
	cerr << "ping succeded\n";
	this->handle_selected_properties(offer_seq[i].properties,
					 ACE_TRY_ENV);

	return;
      }     
   } /* end of if(offer_seq_ptr) */
  

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
	   this->handle_selected_properties(offers[i].properties,
                                            ACE_TRY_ENV);	   return;
         } /* end of for(i = 0; i < offers->length(); i++) */
       }
      while(more);
    } /* end of if(!CORBA::is_nil(iterator.in())) */
   else
    {
      DEBUG0(2, "DEBUG: The iterator is null\n");
    } /* end of else */
}

void
STDC::QMS::Multi_Client::get_offers(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace ("STDC::QMS::Multi_Client::get_offers", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::get_offers\n");
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
      CosTrading::PolicySeq policies;                    //empty sequence

      CosTrading::Lookup::SpecifiedProps desired_props;  // No properties
      desired_props._d(CosTrading::Lookup::all);     // Return all properties

      CosTrading::PolicyNameSeq_var limits_applied;      // out param
      CosTrading::OfferSeq *offer_seq_ptr          = 0;
      CosTrading::OfferSeq_out      offers(offer_seq_ptr);
      CosTrading::OfferIterator_var iterator;

      /// Create a contraint for the query
      string constraint = " QMS_UNIQ_NAME_CATEGORY == '";
      constraint.append(this->_config.data_request.QMSUniqueName.category);
      constraint.append("' and QMS_UNIQ_NAME_HOST_NAME == '");
      constraint.append(this->_config.data_request.QMSUniqueName.host);
      constraint.append("' and QMS_UNIQ_NAME_UUID == '");
      constraint.append(this->_config.data_request.QMSUniqueName.uuid);
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
void
STDC::QMS::Multi_Client::cleanup(void)
{
  QMS_Trace ("STDC::QMS::Multi_Client::cleanup", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::cleanup\n");
  this->_consumer.disconnect();
  this->_supplier.disconnect();
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
STDC::QMS::Multi_Client::connect_EC(CORBA_Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Multi_Client::connect_EC", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Multi_Client::connect_EC\n");
  if( this->_request_channel.empty() || this->_data_channel.empty())
   {
     std::cerr << "Error: no event channels configured" << std::endl;
     throw std::runtime_error::runtime_error("no event channels configured");
   } /* end of if( this->_request_channel.empty() || this->_data_channel.emptyu()) */
  
  ACE_TRY
    {
      // initialize a supplier
      this->_supplier.init(*this->handles_p_, (int)this->_request_event_type,
                           (int)this->_supplier_id,
                           this->_request_channel.c_str(), ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG3(4, "DEBUG: supplier initialized id=%d ec=%s, req event=%d\n",
	     (int)this->_supplier_id, this->_request_channel.c_str(),
	     (int)this->_request_event_type);

      // Initialize the consumer
      this->_consumer.init(*this->handles_p_, (int)this->_data_event_type,
                            this->_data_channel.c_str(), ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG2(4, "DEBUG: consumer initialized ec=%s, data event=%d\n",
	     this->_data_channel.c_str(), (int)this->_data_event_type);

      // Register the callback for the consumer
      this->_consumer.register_callback(&this->init_callback, (void *)this);
      DEBUG0(4, "DEBUG: registered callback &this->init_callback\n");

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
STDC::QMS::Multi_Client::init_callback(const string &response, void *arg_p)
{
  QMS_Trace("STDC::QMS::Multi_Client::init_callback", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Multi_Client::init_callback\n");
  DEBUG1(2, " The response is -> \n%s\n", response.c_str());

  STDC::QMS::Multi_Client * client_p = (STDC::QMS::Multi_Client *)arg_p;
  string::size_type start;
  string::size_type stop;
  string::size_type index;

  string req_id;
  string host;
  string uuid;

  string data = response;

  time_t this_time = time(0);
  struct tm *now_p = gmtime((const time_t *) &this_time);

  DEBUG0(2, "DEBUG: Processing response\n");
  index = data.find("<qms:QMSUniqueName>");
  if(index == string::npos)
   {
     std::cerr << "Error: message does not have a qms:QMSUniqueName" 
	       << std::endl;
     return;
   } /* end of if(start == string::npos) */
  start = data.find("<host>", index);
  if(start != string::npos)
   {
     start += strlen("<host>");
     stop = data.find("</host>");
     if(stop != string::npos)
      {
	host.assign((data.substr(start, stop - start)).c_str());
      } /* end of if(stop != string::npos) */
     else
      {
	std::cerr << "Error: message does not have a host end tag" 
		  << std::endl;
	return;
      } /* end of else */
   } /* end of if(start != string::npos) */
  else
   {
     std::cerr << "Error: message does not have a qms:QMSUniqueName host" 
	       << std::endl;
     return;
   } /* end of else */
  
  start = data.find("<uuid>", index);
  if(start != string::npos)
   {
     start += strlen("<uuid>");
     stop = data.find("</uuid>");
     if(stop != string::npos)
      {
	uuid.assign((data.substr(start, stop - start)).c_str());
      } /* end of if(stop != string::npos) */
     else
      {
	std::cerr << "Error: message does not have a uuid end tag" 
		  << std::endl;
	return;
      } /* end of else */
   } /* end of if(start != string::npos) */
  else
   {
     std::cerr << "Error: message does not have a qms:QMSUniqueName uuid" 
	       << std::endl;
     return;
   } /* end of else */
  
  start = data.find("<requestID>");
  if(start != string::npos)
   {
     start += strlen("<requestID>");
     stop = data.find("</requestID>");
     if(stop != string::npos)
      {
	req_id.assign((data.substr(start, stop - start)).c_str());
      } /* end of if(stop != string::npos) */
     else
      {
	std::cerr << "Error: message does not have a request ID end tag" 
		  << std::endl;
	return;
      } /* end of else */
   } /* end of if(start != string::npos) */
  else
   {
     std::cerr << "Error: message does not have a request ID" 
	       << std::endl;
     return;
   } /* end of else */
  
  
  if((uuid.compare(client_p->_config.data_request.QMSUniqueName.uuid)) !=0)
   {
     DEBUG0(2, "DEBUG: Message not meant for us -- wrong uuid");
     return;
   } 
  if((host.compare(client_p->_config.data_request.QMSUniqueName.host)) !=0)
   {
     DEBUG0(2, "DEBUG: Message not meant for us -- wrong host");
     return;
   } 
  long message_req_id = atol(req_id.c_str());
  if(message_req_id != client_p->_request_id)
   {
     DEBUG0(2, "DEBUG: Message not meant for us -- wrong request id");
     return;
   } /* end of if(message_req_id != client_p->_request_id) */
  
  index = data.find("<qms:payload>");
  if(index != string::npos)
   {
     DEBUG0(2, "DEBUG: Found <qms:payload>\n");
     data.erase(0, index);
     index = data.find("</qms:payload>");
     if(index != string::npos)
      {
	DEBUG0(2, "DEBUG: Found </qms:payload>\n");
	data.erase(index + strlen("</qms:payload>"));
      }
   }
  else
   {
     std::cerr << "Error: unknown payload, passing through"
	       << std::endl;
     return;
   } /* end of else */
  

  req_id.erase();
  host.erase();
  uuid.erase();
  data.erase();
  
  DEBUG0(2, "DEBUG: Going to call callback\n");
  callback(response, 0);
}

