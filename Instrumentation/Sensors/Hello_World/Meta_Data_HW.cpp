//                              -*- Mode: C++ -*-
// MetaData_HW.cpp ---
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
// Created On       : Sun Jul 22 13:53:44 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Jun  8 02:45:18 2002
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 214
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
 *  @ingroup HelloWorld
 *  @brief Implentation of the Metadata object containing metadata about probes
 *
 * $Id: Meta_Data_HW.cpp,v 1.9 2002/06/08 07:45:38 srivasta Exp $
 */

#include "Meta_Data_HW.h"
#include "Hello_World_Impl.h"
#include "YP_Offer.h"
#include "Parse_Duration.h"
#include "orbsvcs/Time_Utilities.h"
#include "orbsvcs/Event_Utilities.h"

#if !defined (_WIN32)
#  include <sys/time.h>
#  include <time.h>
#endif

extern void CallBack(const string &query, void *arg_p);
extern STDC::QMS::Citizen::Hello_World_Impl *sensor_p;

/// RCS version string
static const char* version =
"$Id: Meta_Data_HW.cpp,v 1.9 2002/06/08 07:45:38 srivasta Exp $";

#if defined(_WIN32)
#  define snprintf _snprintf
#endif


/// List of generic CORBA Trading offer property names that are deemed
/// searcheable
static const char *propnames[11] =
  { "",
    "QMS_YP_PROP_1",  "QMS_YP_PROP_2", "QMS_YP_PROP_3", "QMS_YP_PROP_4",
    "QMS_YP_PROP_5", "QMS_YP_PROP_6", "QMS_YP_PROP_7", "QMS_YP_PROP_8",
    "QMS_YP_PROP_9", "QMS_YP_PROP_10"};

/// Format for the response
const char *response_fmt = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>        \n\
  <qms:QMSMessage xmlns=\"http://www.stdc.com/2001/QMSSchema\"        \n\
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"        \n\
    xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"        \n\
    xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema %s\">    \n\
  <qms:msgSequenceNo>%ld</qms:msgSequenceNo>        \n\
  <qms:msgDate>%d-%d-%d</qms:msgDate>        \n\
  <qms:msgTime>%d:%d:%d-0:00</qms:msgTime>        \n\
  <qms:originatingHost>%s</qms:originatingHost>        \n\
  <qms:msgSender>        \n\
    <id>%d</id>        \n\
    <description>Hello World Probe</description>        \n\
  </qms:msgSender>        \n\
  <qms:QMSUniqueName>        \n\
    <category>%s</category>        \n\
    <host>%s</host>        \n\
    <uuid>%s</uuid>        \n\
  </qms:QMSUniqueName>        \n\
  <qms:Session>        \n\
    <requestID>%ld</requestID>        \n\
    <version>%ld</version>        \n\
    <minRepetitions>        \n\
      <count>%d</count>        \n\
      <current>%d</current>        \n\
    </minRepetitions>        \n\
    <minRepeatInterval>%s</minRepeatInterval>        \n\
  </qms:Session>        \n\
  <qms:payload>        \n\
    <helloWorld xmlns=\"http://www.stdc.com/2001/QMS/helloWorld\"        \n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"        \n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/helloWorld         \n\
      %s\">        \n\
      <Data>        \n\
        <dataid>%d</dataid>        \n\
        <salutation>Hello %s %s !!</salutation>        \n\
      </Data>        \n\
    </helloWorld>            \n\
  </qms:payload>        \n\
  </qms:QMSMessage>        \n\
";

/// Format for the flawed response
const char *err_response_fmt = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>        \n\
  <qms:QMSMessage xmlns=\"http://www.stdc.com/2001/QMSSchema\"        \n\
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"        \n\
    xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"        \n\
    xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema %s\">    \n\
  <qms:msgSequenceNo>%ld</qms:msgSequenceNo>        \n\
  <qms:msgDate>%d-%d-%d</qms:msgDate>        \n\
  <qms:msgTime>%d:%d:%d-0:00</qms:msgTime>        \n\
  <qms:originatingHost>%s</qms:originatingHost>        \n\
  <qms:msgSender>        \n\
    <id>%d</id>        \n\
    <description>Hello World Probe</description>        \n\
  </qms:msgSender>        \n\
  <qms:QMSUniqueName>        \n\
    <category>%s</category>        \n\
    <host>%s</host>        \n\
    <uuid>%s</uuid>        \n\
  </qms:QMSUniqueName>        \n\
  <qms:Session>        \n\
    <minRepetitions>        \n\
      <count>%d</count>        \n\
      <current>%d</current>        \n\
    </minRepetitions>        \n\
    <minRepeatInterval>%s</minRepeatInterval>        \n\
  </qms:Session>        \n\
  <qms:payload>        \n\
    <helloWorld xmlns=\"http://www.stdc.com/2001/QMS/helloWorld\"        \n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"        \n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/helloWorld         \n\
      %s\">        \n\
      <Data>        \n\
        <dataid>%d</dataid>        \n\
        <salutation>Hello %s %s !!</salutation>        \n\
      </Data>        \n\
    </helloWorld>            \n\
  </qms:payload>        \n\
  </qms:QMSMessage>        \n\
";

/// The default constructor
STDC::QMS::Citizen::Hello_World_Meta_Data::Hello_World_Meta_Data(void) :
  _supplier_id(17), msg_sequence_no_(0), status(STDC::QMS::Citizen::RUN),
  _offer_created(false)
{
  QMS_Trace ("STDC::QMS::Citizen::Hello_World_Meta_Data::Hello_World_Meta_Data", __LINE__,
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Default constructor\n");

}

/**
 * @overload
 */
STDC::QMS::Citizen::Hello_World_Meta_Data::Hello_World_Meta_Data(STDC::QMS::Citizen::Hello_World_Meta_Data &rhs) :
  _config(rhs._config),
  announce_list_info_(rhs.announce_list_info_),
  request_list_info_(rhs.request_list_info_),
  data_list_info_(rhs.data_list_info_),
  _supplier_id(rhs. _supplier_id),
  msg_sequence_no_(0),
  _offer_created(rhs._offer_created),
  _QMS_Schema(rhs._QMS_Schema),
  _criticality_p(rhs._criticality_p),
  _importance_p(rhs._importance_p)
{
  QMS_Trace ("STDC::QMS::Citizen::Hello_World_Meta_Data::Hello_World_Meta_Data", __LINE__,
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Copy constructor\n");
}

/**
 * @brief The = operator
 *
 * This avoids self assignements
 */
const STDC::QMS::Citizen::Hello_World_Meta_Data
STDC::QMS::Citizen::Hello_World_Meta_Data::operator=(STDC::QMS::Citizen::Hello_World_Meta_Data &copy)
{
  QMS_Trace ("STDC::QMS::Citizen::Hello_World_Meta_Data::operator =", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Copy object\n");
  if(&copy != this)
   {
     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

     this->_config                = copy._config;
     this->announce_list_info_ 	  = copy.announce_list_info_;
     this->request_list_info_ 	  = copy.request_list_info_;
     this->data_list_info_ 	  = copy.data_list_info_;
     this->_supplier_id           = copy._supplier_id;
     this->msg_sequence_no_	  = copy.msg_sequence_no_;
     this->status                 = copy.status;
     this->_offer_created         = copy._offer_created;
     this->_QMS_Schema            = copy._QMS_Schema;
     this->_criticality_p         = copy._criticality_p;
     this->_importance_p          = copy._importance_p;
   } /* end of if(&copy != this) */
  return *this;                 // enable cascaded assignments
}

/**
 * @brief Initialize the meta data object
 * @param config The details of the probe as read from the config file
 * @param supplier_id The supplier ID of the sensor deplying this  probe
 * @param QMS_Schema The URI of the QMS Schema we use while sending messages
 *
 * There is not a lot done during initialization, apart from
 * initializing internal variables of the class.
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::init(STDC::QMS::sensorServiceType
						&config,
						CORBA::Long supplier_id,
						string &QMS_Schema,
						const char *criticality_p,
						const char *importance_p)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  this->_config = config;
  this->_supplier_id = supplier_id;
  this->_QMS_Schema = QMS_Schema;
  this->_criticality_p = criticality_p;
  this->_importance_p  = importance_p;
}

/**
 * @brief This is where we perform cleanup operations for the probe
 *
 * The actions taken include withdrawing our YP offer, and then,
 * through the overloaded function, walinkg the lists of Push
 * consumers and push suppliers, and disconnecting them and freeing
 * the associated resources.
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::cleanup(STDC::QMS::CORBA_Handles *handles_p)
{
 this->withdraw_offer(handles_p);
 this->cleanup();
}

/**
 * @overload
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::cleanup(void)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::cleanup\n");

  DEBUG0 (4, "DEBUG: disconnect_announce_suppliers\n");
  this->disconnect_announce_suppliers();
  DEBUG0 (4, "DEBUG: disconnect_request_consumers\n");
  this->disconnect_request_consumers();
  DEBUG0 (4, "DEBUG:disconnect_data_suppliers \n");
  this->disconnect_data_suppliers();

  DEBUG0 (4, "DEBUG: clean_announce_suppliers\n");
  this->clean_announce_suppliers();
  DEBUG0 (4, "DEBUG:clean_request_consumers \n");
  this->clean_request_consumers();
  DEBUG0 (4, "DEBUG: clean_data_suppliers\n");
  this->clean_data_suppliers();

  DEBUG0 (4, "DEBUG: clean_EC_info\n");
  this->clean_EC_info();
  DEBUG0 (4, "DEBUG: probe cleanup done\n");
}


/**
 * @brief Handle incoming messages
 * @param query The incoming message
 * @param config The data contained in the message headers
 * @param request_data The data contained in the message payload
 *
 * Since there is only one probe, and that probe is built in, we can
 * afford to take some short cuts. Also, for the sake of simplicity, we
 * also assume that there is only a single query going on at one
 * time. While multiple quries shall all result in data, modifying a
 * query (as in pause, resume, stop) shall cause all queries to be
 * affected at the same time.  The simple solution is to store
 * requests in a map keyed by concatenated request id's and requestors
 * supplier id, and have the status variable be request specific.
 *
 * The actions taken are simple: If the action field is empty, it is
 * assumed that this is a new request, in which case we set up a
 * response loop for the replies.. In the loop, we test the status of
 * the probe, and exit if required. Or else, we sleep for the required
 * time, and, if the state is RUN, we send off a response (every 7th
 * message is flawed if INTRODUCE_ERROR is defined).  If the state is
 * PAUSE, we just go on to the next loop.
 *
 * If the action variable was not empty, we set the probes status
 * appropriately.
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::handle_query(const string query,
					    STDC::QMS::QMSMessage &config,
					    struct hw_payload_data &request_data)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::handle_query", __LINE__,__FILE__);
  DEBUG0(DEBUG_L_ENTER,"DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::handle_query\n");

  if(request_data.data.request.action.empty())
   {
     /// This is a initial request
     {
       ACE_Write_Guard<ACE_RW_Mutex> guard(this->status_guard);
       this->status = STDC::QMS::Citizen::RUN;
     }
     cout << "New Query" << std::endl;

     unsigned int i = 0;
     size_t buffer_size = 0;
     buffer_size += strlen(response_fmt);
     buffer_size += 8192;
     buffer_size += this->_config.offer_prop.QMSUniqueName.category.size();
     buffer_size += strlen(this->_criticality_p);
     buffer_size += strlen(this->_importance_p);
     buffer_size += this->_config.offer_prop.QMSUniqueName.host.size();
     buffer_size += this->_config.offer_prop.QMSUniqueName.uuid.size();
     buffer_size += request_data.data.request.firstname.size();
     buffer_size += request_data.data.request.lastname.size();
     char * response_p = new char [buffer_size + 1];

     for (i = 0; i < config.Session.repititions.count ; )
      {
	bool run = true;
	run = true;
	{
	  ACE_Read_Guard<ACE_RW_Mutex> guard(this->status_guard);
	  if(this->status == STDC::QMS::Citizen::STOP)
	   {
	     break;
	   } /* end of if(this->status == STDC::QMS::Citizen::STOP) */
	  if(this->status == STDC::QMS::Citizen::PAUSE)
	   {
	     run = false;
	   } /* end of if(this->status == STDC::QMS::Citizen::STOP) */
	}
	struct timespec interval =
	  STDC::QMS::duration_to_tv(config.Session.interval.c_str());
	struct timespec remaining;

	int done = ACE_OS::nanosleep (&interval, &remaining);
	while(done < 0 && errno == EINTR)
	 {
	   interval = remaining;
	   done = ACE_OS::nanosleep (&interval, &remaining);
	 } /* end of if(ret < 0) */

	if(run)
	 {
	   time_t this_time = time(0);
	   struct tm *now_p = gmtime((const time_t *) &this_time);
	   int ret;
	   string name = this->_config.offer_prop.QMSUniqueName.category;
	   const char* env_var_p = this->_criticality_p;
	   if(!strcmp("VERY_HIGH", env_var_p))     name.append("VH");
	   else if(!strcmp("HIGH", env_var_p))     name.append("H");
	   else if(!strcmp("MEDIUM", env_var_p))   name.append("M");
	   else if(!strcmp("LOW", env_var_p))      name.append("L");
	   else if(!strcmp("VERY_LOW", env_var_p)) name.append("VL");
	   else    	   	   	   	   name.append("VH");


	   env_var_p = this->_importance_p;
	   if(!strcmp("VERY_HIGH", env_var_p))     name.append("VH");
	   else if(!strcmp("HIGH", env_var_p))     name.append("H");
	   else if(!strcmp("MEDIUM", env_var_p))   name.append("M");
	   else if(!strcmp("LOW", env_var_p))      name.append("L");
	   else if(!strcmp("VERY_LOW", env_var_p)) name.append("VL");
	   else    	   	   	   	   name.append("M");



#if defined(INTRODUCE_ERROR)
	   if(((i + 3) % 7) == 0)
	    {
	      ret =
		snprintf(response_p, buffer_size, err_response_fmt,
			 this->_QMS_Schema.c_str(),
			 ++this->msg_sequence_no_,
			 (1900 + now_p->tm_year), (1 + now_p->tm_mon),
			 now_p->tm_mday, now_p->tm_hour, now_p->tm_min,
			 now_p->tm_sec,
			 this->_config.offer_prop.QMSUniqueName.host.c_str(),
			 this->_supplier_id,
			 name.c_str(),
			 this->_config.offer_prop.QMSUniqueName.host.c_str(),
			 this->_config.offer_prop.QMSUniqueName.uuid.c_str(),
			 config.Session.repititions.count, i+1,
			 config.Session.interval.c_str(),
			 this->_config.schema_prop.probeSchema.c_str(),
			 i+1,
			 request_data.data.request.firstname.c_str(),
			 request_data.data.request.lastname.c_str());

	    } /* end of if((i % 7) == 0) */
	   else
	    {
#endif
	      ret =
		snprintf(response_p, buffer_size, response_fmt,
			 this->_QMS_Schema.c_str(),
			 ++this->msg_sequence_no_,
			 (1900 + now_p->tm_year), (1 + now_p->tm_mon),
			 now_p->tm_mday, now_p->tm_hour, now_p->tm_min,
			 now_p->tm_sec,
			 this->_config.offer_prop.QMSUniqueName.host.c_str(),
			 this->_supplier_id,
			 name.c_str(),
			 this->_config.offer_prop.QMSUniqueName.host.c_str(),
			 this->_config.offer_prop.QMSUniqueName.uuid.c_str(),
			 config.Session.request_id,
			 config.Session.version,
			 config.Session.repititions.count, i+1,
			 config.Session.interval.c_str(),
			 this->_config.schema_prop.probeSchema.c_str(),
			 i+1,
			 request_data.data.request.firstname.c_str(),
			 request_data.data.request.lastname.c_str());
#if defined(INTRODUCE_ERROR)
	    } /* end of else */
#endif

	   if(ret == -1 || (unsigned int) ret >= buffer_size)
	    {
	      cerr << "Buffer overflow in outgoing message, discarding"
		   << std::endl;
	      cerr << "Query Was: " << query << std::endl;
	    } /* end of if(ret) */
	   else
	    {
	      this->send(response_p);
	    } /* end of else */
	   i++;
	 } /* end of if(run) */
      } /* end of while(true) */
     if(response_p)
      {
	delete response_p;
	response_p = 0;
      } /* end of if(response_p) */
   } // end of request_data.data.request.action.empty()
  else
   {
     if(request_data.data.request.action.compare("pause") == 0)
      {
	ACE_Write_Guard<ACE_RW_Mutex> guard(this->status_guard);
	this->status = STDC::QMS::Citizen::PAUSE;
	cout << "Pause" << std::endl;
      }
     if(request_data.data.request.action.compare("resume") == 0)
      {
	ACE_Write_Guard<ACE_RW_Mutex> guard(this->status_guard);
	this->status = STDC::QMS::Citizen::RUN;
	cout << "Resume" << std::endl;
      }
     if(request_data.data.request.action.compare("stop") == 0)
      {
	ACE_Write_Guard<ACE_RW_Mutex> guard(this->status_guard);
	this->status = STDC::QMS::Citizen::STOP;
	cout << "STOP" << std::endl;
      }
   } /* end of else */
}
/**
 * @brief Add information about an announce channel
 * @param param Event channel information
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::add_announce_info(STDC::QMS::Citizen::Sensor_Data_Element_HW  * param)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  DEBUG2(DEBUG_L_ENTER, "DEBUG: Adding announce channel=%s\n\tevent_id=%d",
	 param->get_name().c_str(), param->get_int_val() );
  this->announce_list_info_.push_back(param);
}

/**
 * @brief Add information about an request channel
 * @param param Event channel information
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::add_request_info(STDC::QMS::Citizen::Sensor_Data_Element_HW * param)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  DEBUG2(DEBUG_L_ENTER, "DEBUG: Adding request channel=%s\n\tevent_id=%d",
	 param->get_name().c_str(), param->get_int_val() );
  this->request_list_info_.push_back(param);
}

/**
 * @brief Add information about an data channel
 * @param param Event channel information
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::add_data_info(STDC::QMS::Citizen::Sensor_Data_Element_HW * param)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  DEBUG2(DEBUG_L_ENTER, "DEBUG: Adding data channel=%s\n\tevent_id=%d",
	 param->get_name().c_str(), param->get_int_val() );
  this->data_list_info_.push_back(param);
}

/**
 * @brief Store a handle to the QMS Trader EC info service
 * @param ec_registry Event channel information object handle
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::add_ec_registry(STDC::QMS::Citizen::QMS_Trader_ECInfo_var ec_registry)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  this->_ec_registry = ec_registry;
}

/**
 * @brief Remove all the event channel information and reclaim resources
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::clean_EC_info(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::clean_EC_info", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::clean_EC_info\n");

  vector<STDC::QMS::Citizen::Sensor_Data_Element_HW *>::iterator iter;

  if(!this->announce_list_info_.empty())
   {
     DEBUG0(4, "DEBUG: !announce_list_info_.empty()\n");

     for(iter = this->announce_list_info_.begin();
	 iter != this->announce_list_info_.end();
	 iter++)
      {
	if(iter)
	 {
	   if(*iter)
	    {
	      delete *iter;
	      *iter = 0;
	    } /* end of if(*iter) */
	 } /* end of if(iter) */
      }
     DEBUG0(4, "DEBUG: clearing announce_list_info \n");
     this->announce_list_info_.clear();
   } /* end of if(!announce_list_info_.empty()) */

  if(!this->request_list_info_.empty())
   {
     DEBUG0(4, "DEBUG: !this->request_list_info_.empty()\n");
     for(iter = this->request_list_info_.begin();
	 iter != this->request_list_info_.end();
	 iter++)
      {
	if(iter)
	 {
	   if(*iter)
	    {
	      delete *iter;
	      *iter = 0;
	    } /* end of if(*iter) */
	 } /* end of if(iter) */
      }
     DEBUG0(4, "DEBUG: clearing request_list_info \n");
     this->request_list_info_.clear();
   }
  if(!this->data_list_info_.empty())
   {
     DEBUG0(4, "DEBUG: !this->data_list_info_.empty()\n");
     for(iter = this->data_list_info_.begin();
	 iter != this->data_list_info_.end();
	 iter++)
      {
	if(iter)
	 {
	   if(*iter)
	    {
	      delete *iter;
	      *iter = 0;
	    } /* end of if(*iter) */
	 } /* end of if(iter) */
      }
     DEBUG0(4, "DEBUG: clearing data_list_info \n");
     this->data_list_info_.clear();
   }
}

/**
 * @brief Get event channel information for this probe
 *
 * Using the handle to the EC information service of the QMS Trader
 * that we have stored, we request information about the set of CORBA
 * event channel names and event types associated with each of the
 * following categories:
 *   - Announce Channels for announcing changes to the service
 *   - Request Channels on which clients may send us requests
 *   - Data channels on which our responses flow out
 *
 * So we make three independent queris, walk through the responses,
 * and store the information away in three sets of vectors.
 * Subsequently, we shall walk through these vectors and create push
 * consumers and suppliers as needed.
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::get_EC_info(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::get_EC_info", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::get_EC_info\n");

  STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq 	*ImportAECSeq = 0;
  STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq 	*ImportDECSeq = 0;
  STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq 	*ImportRECSeq = 0;
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      CORBA::ULong i =0;
      char *uniq_name_p =
	const_cast< char * >
	(this->_config.offer_prop.QMSUniqueName.category.c_str());

      ImportAECSeq =
	this->_ec_registry->getAnnounceChannels(uniq_name_p);
      ACE_TRY_CHECK;

      if(ImportAECSeq)
       {
	 for(i =0; i < ImportAECSeq->length() ; i++)
	  {
	    STDC::QMS::Citizen::Sensor_Data_Element_HW * data_p =
	      new STDC::QMS::Citizen::Sensor_Data_Element_HW();

	    string 	ec_name  = (const char *)
				   (*ImportAECSeq)[i].EventChannelName;
	    long 	event_id = (*ImportAECSeq)[i].EventId;

	    data_p->set_name(ec_name);
	    data_p->set_int_val(event_id);
	    DEBUG3(4,
		   "DEBUG: announce channel Number %d, Name %s, EventType %ld",
		   i, ec_name.c_str(), event_id);

	    this->add_announce_info(data_p);
	  } /* end of for(i =0; i < ImportAECSeq->length() ; i++) */

       } /* end of if(ImportAECSeq) */


      ImportDECSeq = this->_ec_registry->getDataChannels(uniq_name_p);
      ACE_TRY_CHECK;

      if(ImportDECSeq)
       {
	 for(i =0; i < ImportDECSeq->length() ; i++)
	  {
	    STDC::QMS::Citizen::Sensor_Data_Element_HW * data_p =
	      new STDC::QMS::Citizen::Sensor_Data_Element_HW();

	    string 	ec_name  = (const char *)
				   (*ImportDECSeq)[i].EventChannelName;
	    long 	event_id = (*ImportDECSeq)[i].EventId;


	    data_p->set_name(ec_name);
	    data_p->set_int_val(event_id);
	    DEBUG3(4,
		   "DEBUG: data channel Number %d, Name %s, EventType %ld",
		   i, ec_name.c_str(), event_id);

	    this->add_data_info(data_p);
	  } /* end of for(i =0; i < ImportDECSeq->length() ; i++) */

       } /* end of if(ImportDECSeq) */


      ImportRECSeq =
	this->_ec_registry->getRequestChannels(uniq_name_p);
      ACE_TRY_CHECK;

      if(ImportRECSeq)
       {
	 for(i =0; i < ImportRECSeq->length() ; i++)
	  {
	    STDC::QMS::Citizen::Sensor_Data_Element_HW * data_p =
	      new STDC::QMS::Citizen::Sensor_Data_Element_HW();

	    string 	ec_name  = (const char *)
				   (*ImportRECSeq)[i].EventChannelName;
	    long 	event_id = (*ImportRECSeq)[i].EventId;

	    data_p->set_name(ec_name);
	    data_p->set_int_val(event_id);

	    DEBUG3(4,
		   "DEBUG: request channel Number %d, Name %s, EventType %ld",
		   i, ec_name.c_str(), event_id);
	    this->add_request_info(data_p);
	  } /* end of for(i =0; i < ImportRECSeq->length() ; i++) */
       } /* end of if(ImportRECSeq) */
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_CATCHALL
    {
      cerr << " A unknown exception was caught " << endl;
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}

/**
 * @brief Create announce channel suppliers based on stored information
 * @param my_id The supplier ID to use in the push supplier
 * @param handles_p A pointer to a CORBA Handles object
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::create_announce_suppliers(RtecEventComm::EventSourceID my_id,
				     STDC::QMS::CORBA_Handles *handles_p,
				     CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::create_announce_suppliers",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::create_announce_suppliers\n");
  if(!announce_list_info_.empty())
   {
     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

     ACE_TRY
       {
	 unsigned int i = 0;
	 for(i = 0; i < announce_list_info_.size(); i++)
	  {
	    STDC::QMS::Push_Supplier *supplier_p =
	      new STDC::QMS::Push_Supplier();

	    string ec_name  = announce_list_info_[i]->get_name();
	    long event_type = announce_list_info_[i]->get_int_val();
	    DEBUG3(4,
		   "DEBUG: Anounce channel Number %d, Name %s, EventType %ld",
		   i, ec_name.c_str(), event_type);

	    if(!ec_name.empty())
	     {
	       supplier_p->init(*handles_p, event_type, my_id, ec_name.c_str(),
				ACE_TRY_ENV);

	       RtecScheduler::handle_t& schedule_t =
		 supplier_p->get_schedule();

	       enum RtecScheduler::Criticality_t criticality;
	       enum RtecScheduler::Importance_t  importance;
	       if(!strcmp("VERY_HIGH", this->_criticality_p))
		 criticality = RtecScheduler::VERY_HIGH_CRITICALITY;
	       else if(!strcmp("HIGH", this->_criticality_p))
		 criticality = RtecScheduler::HIGH_CRITICALITY;
	       else if(!strcmp("MEDIUM", this->_criticality_p))
		 criticality = RtecScheduler::MEDIUM_CRITICALITY;
	       else if(!strcmp("LOW", this->_criticality_p))
		 criticality = RtecScheduler::LOW_CRITICALITY;
	       else if(!strcmp("VERY_LOW", this->_criticality_p))
		 criticality = RtecScheduler::VERY_LOW_CRITICALITY;
	       else
		 criticality = RtecScheduler::VERY_HIGH_CRITICALITY;

	       if(!strcmp("VERY_HIGH", this->_importance_p))
		 importance = RtecScheduler::VERY_HIGH_IMPORTANCE;
	       else if(!strcmp("HIGH", this->_importance_p))
		 importance = RtecScheduler::HIGH_IMPORTANCE;
	       else if(!strcmp("MEDIUM", this->_importance_p))
		 importance = RtecScheduler::MEDIUM_IMPORTANCE;
	       else if(!strcmp("LOW", this->_importance_p))
		 importance = RtecScheduler::LOW_IMPORTANCE;
	       else if(!strcmp("VERY_LOW", this->_importance_p))
		 importance = RtecScheduler::VERY_LOW_IMPORTANCE;
	       else
	       importance = RtecScheduler::MEDIUM_IMPORTANCE;

	       RtecScheduler::Period_t rate = ACE_U64_TO_U32(time(0));
	       handles_p->get_scheduler_handle()->set 
		 (schedule_t, criticality, 0, 0, 0, rate, importance,
		  0, 1, RtecScheduler::OPERATION, ACE_TRY_ENV);
	       ACE_TRY_CHECK;

	       supplier_p->set_schedule(schedule_t);


	       this->Announcement_Suppliers.push_back(supplier_p);
	     } /* end of if(!ec_name.empty()) */
	    else
	     {
	       DEBUG0(DEBUG_L_ENTER,"DEBUG: empty announce list\n");
	     } /* end of else */

	  } /* end of for(i = 0; i < announce_list_info_.size(); i++) */

       } /* end of if(!announce_list_info_.empty) */
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "create_announce_suppliers");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
   }
}

/**
 * @brief Create request channel consumers based on stored information
 * @param handles_p A pointer to a CORBA Handles object
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::create_request_consumers
(STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::create_request_consumers",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::create_request_consumers\n");
  if(!request_list_info_.empty())
   {
     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
     ACE_TRY
       {
	 unsigned int i = 0;
	 for(i = 0; i < request_list_info_.size(); i++)
	  {
	    STDC::QMS::Push_Consumer *consumer_p =
	      new STDC::QMS::Push_Consumer;

	    string ec_name  = request_list_info_[i]->get_name();
	    long event_type = request_list_info_[i]->get_int_val();
	    DEBUG3(4,
		   "DEBUG: Request channel Number %d, Name %s, EventType %ld",
		   i, ec_name.c_str(), event_type);

	    if(!ec_name.empty())
	     {
	       consumer_p->init(*handles_p, event_type, ec_name.c_str(),
				ACE_TRY_ENV);
	       // Now we need to add a callback function.
	       consumer_p->register_callback(CallBack, (void *) ::sensor_p);
	       this->Request_Consumers.push_back(consumer_p);
	     } /* end of if(!ec_name.empty()) */
	    else
	     {
	       DEBUG0(DEBUG_L_ENTER,"DEBUG: empty request list\n");
	     } /* end of else */

	  } /* end of for(i = 0; i < announce_list_info_.size(); i++) */

       } /* end of if(!announce_list_info_.empty) */
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "create_announce_suppliers");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
   } /* end of if(!request_list_info_.empty()) */
}

/**
 * @brief Create data channel suppliers based on stored information
 * @param my_id The supplier ID to use in the push supplier
 * @param handles_p A pointer to a CORBA Handles object
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::create_data_suppliers(RtecEventComm::EventSourceID my_id,
				 STDC::QMS::CORBA_Handles *handles_p,
				 CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::create_data_suppliers", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::create_data_suppliers\n");
  if(!data_list_info_.empty())
   {
     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
     ACE_TRY
       {
	 unsigned int i = 0;
	 for(i = 0; i < data_list_info_.size(); i++)
	  {
	    STDC::QMS::Push_Supplier *supplier_p =
	      new STDC::QMS::Push_Supplier;

	    string ec_name  = data_list_info_[i]->get_name();
	    long event_type = data_list_info_[i]->get_int_val();
	    DEBUG3(4,
		   "DEBUG: Data channel Number %d, Name %s, EventType %ld",
		   i, ec_name.c_str(), event_type);

	    if(!ec_name.empty())
	     {
	       supplier_p->init(*handles_p, event_type, my_id,
				ec_name.c_str(), ACE_TRY_ENV);
	       RtecScheduler::handle_t& schedule_t =
		 supplier_p->get_schedule();

	       enum RtecScheduler::Criticality_t criticality;
	       enum RtecScheduler::Importance_t  importance;
	       if(!strcmp("VERY_HIGH", this->_criticality_p))
		 criticality = RtecScheduler::VERY_HIGH_CRITICALITY;
	       else if(!strcmp("HIGH", this->_criticality_p))
		 criticality = RtecScheduler::HIGH_CRITICALITY;
	       else if(!strcmp("MEDIUM", this->_criticality_p))
		 criticality = RtecScheduler::MEDIUM_CRITICALITY;
	       else if(!strcmp("LOW", this->_criticality_p))
		 criticality = RtecScheduler::LOW_CRITICALITY;
	       else if(!strcmp("VERY_LOW", this->_criticality_p))
		 criticality = RtecScheduler::VERY_LOW_CRITICALITY;
	       else
		 criticality = RtecScheduler::VERY_HIGH_CRITICALITY;

	       if(!strcmp("VERY_HIGH", this->_importance_p))
		 importance = RtecScheduler::VERY_HIGH_IMPORTANCE;
	       else if(!strcmp("HIGH", this->_importance_p))
		 importance = RtecScheduler::HIGH_IMPORTANCE;
	       else if(!strcmp("MEDIUM", this->_importance_p))
		 importance = RtecScheduler::MEDIUM_IMPORTANCE;
	       else if(!strcmp("LOW", this->_importance_p))
		 importance = RtecScheduler::LOW_IMPORTANCE;
	       else if(!strcmp("VERY_LOW", this->_importance_p))
		 importance = RtecScheduler::VERY_LOW_IMPORTANCE;
	       else
	       importance = RtecScheduler::MEDIUM_IMPORTANCE;

	       RtecScheduler::Period_t rate = ACE_U64_TO_U32(time(0));
	       handles_p->get_scheduler_handle()->set 
		 (schedule_t, criticality, 0, 0, 0, rate, importance,
		  0, 1, RtecScheduler::OPERATION, ACE_TRY_ENV);
	       ACE_TRY_CHECK;

	       supplier_p->set_schedule(schedule_t);

	       this->Data_Suppliers.push_back(supplier_p);
	     } /* end of if(!ec_name.empty()) */
	    else
	     {
	       DEBUG0(DEBUG_L_ENTER,"DEBUG: empty data list\n");
	     } /* end of else */
	  } /* end of for(i = 0; i < announce_list_info_.size(); i++) */

       } /* end of if(!announce_list_info_.empty) */
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "create_data_suppliers");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
   } /* end of if(!data_list_info_.empty()) */
}


/**
 * @brief Connect the announce channel suppliers to the event channel
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::connect_announce_suppliers(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::connect_announce_suppliers",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::connect_announce_suppliers\n");
  if(!Announcement_Suppliers.empty())
   {
     ACE_TRY
       {
	 unsigned int i = 0;
	 for(i = 0; i < Announcement_Suppliers.size(); i++)
	  {
	    Announcement_Suppliers[i]->connect(ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	  }
       }
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "create_data_suppliers");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
   } /* end of if(!Announcement_Suppliers.empty()) */
}

/**
 * @brief Connect the reqeust channel consumers to the event channel
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::connect_request_consumers(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::connect_request_consumers",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::connect_request_consumers\n");
  if(!Request_Consumers.empty())
   {
     ACE_TRY
       {
	 unsigned int i = 0;
	 for(i = 0; i < Request_Consumers.size(); i++)
	  {
	    Request_Consumers[i]->connect(ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	  }
       }
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "create_data_suppliers");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
   } /* end of if(!Resquest_Consumers.empty()) */

}

/**
 * @brief Connect the data channel suppliers to the event channel
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::connect_data_suppliers(CORBA::Environment &
						      ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::connect_data_suppliers", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::connect_data_suppliers\n");
  if(!Data_Suppliers.empty())
   {
     ACE_TRY
       {
	 unsigned int i = 0;
	 for(i = 0; i < Data_Suppliers.size(); i++)
	  {
	    Data_Suppliers[i]->connect(ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	  }
       }
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "create_data_suppliers");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
   } /* end of if(!Resquest_Consumers.empty()) */

}

/**
 * @brief Disconnect the announce channel suppliers from the event channel
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::disconnect_announce_suppliers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::disconnect_announce_suppliers",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Meta_Data::disconnect_announce_suppliers\n");
  if(!Announcement_Suppliers.empty())
   {
     unsigned int i = 0;
     for(i = 0; i < Announcement_Suppliers.size(); i++)
      {
	Announcement_Suppliers[i]->disconnect();
      }
   }
}

/**
 * @brief Disconnect the request channel consumers from the event channel
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::disconnect_request_consumers(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::disconnect_request_consumers",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::disconnect_request_consumers\n");
  if(!Request_Consumers.empty())
   {
     ACE_TRY
       {
	 unsigned int i = 0;
	 for(i = 0; i < Request_Consumers.size(); i++)
	  {
	    Request_Consumers[i]->disconnect(ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	  }
       }
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "disconnect_data_suppliers");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
   } /* end of if(!Resquest_Consumers.empty()) */

}

/**
 * @brief Disconnect the data channel suppliers from the event channel
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::disconnect_data_suppliers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::disconnect_data_suppliers",
	    __LINE__,  __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::disconnect_data_suppliers\n");
  if(!Data_Suppliers.empty())
   {
     unsigned int i = 0;
     for(i = 0; i < Data_Suppliers.size(); i++)
      {
	Data_Suppliers[i]->disconnect();
	ACE_TRY_CHECK;
      }
   }
}

/**
 * @brief Send the data out to all the data channel suppliers
 * @param data The data to be sent
 *  @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * We walk the list of data suppliers, and invoke the send method on
 * each push supplier.
 */
int
STDC::QMS::Citizen::Hello_World_Meta_Data::send(const string data,
				    CORBA::Environment &ACE_TRY_ENV)
{
  int ret = 0;
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::send", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,	"DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::send\n");

  if(!Data_Suppliers.empty())
   {
     ACE_TRY
       {
	 unsigned int i = 0;
	 for(i = 0; i < Data_Suppliers.size(); i++)
	  {
	    ret += Data_Suppliers[i]->send(data, ACE_TRY_ENV);
	    ACE_TRY_CHECK;
	  }
       }
     ACE_CATCHANY
       {
	 ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "create_data_suppliers");
	 ACE_RE_THROW;
       }
     ACE_ENDTRY;
   } /* end of if(!Resquest_Consumers.empty()) */
  return ret;
}

/**
 * @brief Withdraw the YP offer made for the probe
 * @param handles_p A pointer to a CORBA Handles object
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * We withdraw the YP offer using the stored object id that we
 obtained while making the offer.
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::withdraw_offer(STDC::QMS::CORBA_Handles *
					      handles_p,
					      CORBA::Environment
					      &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::withdraw_offer", __LINE__,
	    __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Meta_Data::withdraw_offer\n");
  if(!this->_offer_created)
   {
     return;
   } /* end of if(!this->_offer_created) */
  ACE_TRY
    {
      CosTrading::Lookup_var lookup_var =
        handles_p->get_lookup_handle(ACE_TRY_ENV);
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
 * We also need to put in infromnation about all the event channels we
 * send announcements on, that we listen to requests on, and where we
 * publish our data. This entails walking the event channel
 * information for all the announce, requests and data lists and
   counting the distinct event channel name/event type pairs.
 *
 * Next, we create a property struct, and fill in the fixed properties
 * detailed above. After that, we walk down the list of offer
 * parameters, looking for the searchable flag, and create the
 * properties, mapping them to the fixed names appropriately. Finally,
 * we make our third pass down the offer parameters, filling in the
 * property names and values. Finally, we walk down the event channels
 * relevant to us and put that infdormation in the offer.
 *
 * Finally, we register an offer with the CORBA trading service.
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::make_offer(CORBA::Object_ptr obj,
					  STDC::QMS::CORBA_Handles * handles_p,
					  CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::make_offer", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::make_offer\n");
  ACE_TRY
    {
      CosTrading::Lookup_var lookup_var =
	handles_p->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CosTrading::Register_var reg_var = lookup_var->register_if();
      if(CORBA::is_nil(reg_var.in()))
       {
	 cerr << "trader does not support updates" << endl;
	 throw STDC::QMS::QMS_Error();
       } /* end of if(CORBA::is_nil(reg_var)) */
      // We need a number of fixed property names:
      //  (a) QMSUniqueName category
      //  (b) QMSUniqueName host
      //  (c) QMSUniqueName uuid
      //  (d) CORBA IDL Version
      //  (e) Description
      //  (f) QMS Schema URI
      // Add to that however many optional offers params we have

      CosTrading::PropertySeq props;
      // Count the parameters we have
      int count = 7;
      STDC::QMS::optionalOfferType::const_iterator offers;
      for(offers  = this->_config.offer_param.begin();
          offers != this->_config.offer_param.end();
          offers++)
       {
         count ++;
         if(offers->searchable)
          {
            count ++;
          } /* end of if(offers->searchable) */
       }

      if(!announce_list_info_.empty())
       {
	 unsigned int i = 0;
	 for(i = 0; i < announce_list_info_.size(); i++)
	  {
	    string ec_name  = announce_list_info_[i]->get_name();
	    if(!ec_name.empty())
	     {
	       count ++;
	     }
	  }
       }
      if(!request_list_info_.empty())
       {
	 unsigned int i = 0;
	 for(i = 0; i < request_list_info_.size(); i++)
	  {
	    string ec_name  = request_list_info_[i]->get_name();
	    if(!ec_name.empty())
	     {
	       count ++;
	     }
	  }
       }
      if(!data_list_info_.empty())
       {
	 unsigned int i = 0;
	 for(i = 0; i < data_list_info_.size(); i++)
	  {
	    string ec_name  = data_list_info_[i]->get_name();
	    if(!ec_name.empty())
	     {
	       count ++;
	     }
	  }
       }


      int maxcount = count;

      props.length(maxcount);

      count = 0 ;

      string name = this->_config.offer_prop.QMSUniqueName.category;
      const char* env_var_p = this->_criticality_p;
      if(!strcmp("VERY_HIGH", env_var_p))     name.append("VH");
      else if(!strcmp("HIGH", env_var_p))     name.append("H");
      else if(!strcmp("MEDIUM", env_var_p))   name.append("M");
      else if(!strcmp("LOW", env_var_p))      name.append("L");
      else if(!strcmp("VERY_LOW", env_var_p)) name.append("VL");
      else    	   	   	   	   name.append("VH");


      env_var_p = this->_importance_p;
      if(!strcmp("VERY_HIGH", env_var_p))     name.append("VH");
      else if(!strcmp("HIGH", env_var_p))     name.append("H");
      else if(!strcmp("MEDIUM", env_var_p))   name.append("M");
      else if(!strcmp("LOW", env_var_p))      name.append("L");
      else if(!strcmp("VERY_LOW", env_var_p)) name.append("VL");
      else    	   	   	   	   name.append("M");

      props[count].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
      props[count].value <<= name.c_str();
      count ++;

      props[count].name  = CORBA::string_dup ("QMS_UNIQ_NAME_HOST_NAME");
      props[count].value <<=
	this->_config.offer_prop.QMSUniqueName.host.c_str();

      count ++;

      props[count].name  = CORBA::string_dup ("QMS_UNIQ_NAME_UUID");
      props[count].value <<=
	this->_config.offer_prop.QMSUniqueName.uuid.c_str();

      count ++;

      props[count].name  = CORBA::string_dup ("VERSION");
      props[count].value <<= this->_config.schema_prop.schemaVersion.c_str();

      count ++;

      props[count].name  = CORBA::string_dup ("PROBE_SCHEMA_URI");
      props[count].value <<= this->_config.schema_prop.probeSchema.c_str();

      count ++;

      props[count].name  = CORBA::string_dup ("QMS_SCHEMA_URI");
      props[count].value <<= this->_QMS_Schema.c_str();

      //count = 6;

      count ++;

      props[count].name  = CORBA::string_dup ("SUPPLIER_ID");
      props[count].value <<= this->_supplier_id;

      count ++;

       for(offers  = this->_config.offer_param.begin();
          offers != this->_config.offer_param.end();
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

      for(offers  = this->_config.offer_param.begin();
          offers != this->_config.offer_param.end();
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


      string value;
      name.erase();
      int ret = 0;

      if(!announce_list_info_.empty())
       {
	 unsigned int i = 0;
	 for(i = 0; i < announce_list_info_.size(); i++)
	  {
            long event_type = announce_list_info_[i]->get_int_val();
	    string ec_name  = announce_list_info_[i]->get_name();
	    if(!ec_name.empty())
	     {
	       char event_type_buf[128];
	       char index_buf[128];

	       ret = snprintf(event_type_buf, 128, "%ld", event_type);
	       if(ret == -1|| ret >= 128)
		{
		  continue;
		} /* end of if(ret == -1|| ret >= 128) */

	       ret = snprintf(index_buf, 128, "%d", i);
	       if(ret == -1|| ret >= 128)
		{
		  continue;
		} /* end of if(ret == -1|| ret >= 128) */

	       value.erase();
	       name.erase();

	       value.assign("<Event_Channel_Name>");
	       value.append(ec_name);
	       value.append("</Event_Channel_Name>\n<Event_Type>");
	       value.append(event_type_buf);
	       value.append("</Event_Type>");

	       name.assign("Announce_");
	       name.append(index_buf);

	       props[count].name  = name.c_str();
	       props[count].value <<= value.c_str();
	       count ++;
	     }
	  }
       }
      if(!request_list_info_.empty())
       {
	 unsigned int i = 0;
	 for(i = 0; i < request_list_info_.size(); i++)
	  {
	    string ec_name  = request_list_info_[i]->get_name();
            long event_type = request_list_info_[i]->get_int_val();
	    if(!ec_name.empty())
	     {
	       char event_type_buf[128];
	       char index_buf[128];

	       ret = snprintf(event_type_buf, 128, "%ld", event_type);
	       if(ret == -1|| ret >= 128)
		{
		  continue;
		} /* end of if(ret == -1|| ret >= 128) */

	       ret = snprintf(index_buf, 128, "%d", i);
	       if(ret == -1|| ret >= 128)
		{
		  continue;
		} /* end of if(ret == -1|| ret >= 128) */

	       value.erase();
	       name.erase();

	       value.assign("<Event_Channel_Name>");
	       value.append(ec_name);
	       value.append("</Event_Channel_Name>\n<Event_Type>");
	       value.append(event_type_buf);
	       value.append("</Event_Type>");

	       name.assign("Request_");
	       name.append(index_buf);

	       props[count].name  = name.c_str();
	       props[count].value <<= value.c_str();
	       count ++;
	     }
	  }
       }
      if(!data_list_info_.empty())
       {
	 unsigned int i = 0;
	 for(i = 0; i < data_list_info_.size(); i++)
	  {
	    string ec_name  = data_list_info_[i]->get_name();
            long event_type = data_list_info_[i]->get_int_val();
	    if(!ec_name.empty())
	     {
	       char event_type_buf[128];
	       char index_buf[128];

	       ret = snprintf(event_type_buf, 128, "%ld", event_type);
	       if(ret == -1|| ret >= 128)
		{
		  continue;
		} /* end of if(ret == -1|| ret >= 128) */

	       ret = snprintf(index_buf, 128, "%d", i);
	       if(ret == -1|| ret >= 128)
		{
		  continue;
		} /* end of if(ret == -1|| ret >= 128) */

	       value.erase();
	       name.erase();

	       value.assign("<Event_Channel_Name>");
	       value.append(ec_name);
	       value.append("</Event_Channel_Name>\n<Event_Type>");
	       value.append(event_type_buf);
	       value.append("</Event_Type>");

	       name.assign("Data_");
	       name.append(index_buf);

	       props[count].name  = name.c_str();
	       props[count].value <<= value.c_str();
	       count ++;
	     }
	  }
       }

      this->offer_id  = reg_var->_cxx_export(obj,
					     "STDC_QMS_CITIZEN_HW_SENSOR",
					     props, ACE_TRY_ENV);
      ACE_TRY_CHECK;

    }
  ACE_CATCH (CosTrading::UnknownServiceType, excp)
    {
      DEBUG0(DEBUG_L_ENTER, "DEBUG: No service type making probe yp offer\n");
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::IllegalPropertyName, excp)
    {
      DEBUG0(DEBUG_L_ENTER,
	     "DEBUG: IllegalPropertyName making probe yp offer\n");
      ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType-IllegalPropertyName");

      if (excp.name.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Invalid name: %s\n", excp.name.in ()));
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
	     vtr)
    {
      DEBUG0(DEBUG_L_ENTER,
	     "DEBUG: ValueTypeRedefinition making probe yp offer\n");
      ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType -ValueTypeRedefinition");

      if (vtr.type_1.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Type One: %s\n", vtr.type_2.in ()));
      if (vtr.type_2.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Type Two: %s\n", vtr.type_2.in ()));
      ACE_RE_THROW;
    }
  ACE_CATCHANY
  {
    ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making probe yp offer");
    ACE_RE_THROW;
  }
  ACE_ENDTRY;
}


/**
 * @brief The driving function for making yellow page offers
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 * @param obj The object reference for the sensor
 * @param handles_p A reference to a CORBA Handles object
 *
 * This method is simpler than the one used in Hello_World_Impl.cpp
 * because we can be sure that the service type for the offer must
 * exist.  First, if the yp_offer has already been created, we
 * just return, making this function idempotent. If that is not the
 * case, we just go ahead and make an offer, using make_offer()
 * above. If it throws an unexpected exception, we just allow that to
 * bubble up.
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::yp_offer(CORBA::Object_ptr obj,
					STDC::QMS::CORBA_Handles * handles_p,
					CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::yp_offer", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::yp_offer\n");
  if(this->_offer_created)
   {
     return;
   } /* end of if(!this->_offer_created) */

  ACE_TRY
    {
      make_offer(obj, handles_p, ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CosTrading::UnknownServiceType, excp)
    {
      cerr << "No service type (ignored -- need to add service type (probe)"
	   << endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::PropertyTypeMismatch, excp)
    {
      DEBUG0(DEBUG_L_ENTER, "DEBUG: Property type mismatch\n");
       if (excp.type.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Invalid type: %s\n", excp.type.in ()));
       if(excp.prop.name.in())
        {
          ACE_DEBUG ((LM_DEBUG, "Invalid property name : %s\n", excp.prop.name.in ()));
        } /* end of if(excp.something.name.in()) */
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::IllegalPropertyName, excp)
    {
      DEBUG0(DEBUG_L_ENTER, "DEBUG: IllegalPropertyName\n");
      ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType-IllegalPropertyName");

      if (excp.name.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Invalid name: %s\n", excp.name.in ()));
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition, vtr)
    {
      DEBUG0(DEBUG_L_ENTER, "DEBUG: ValueTypeRedefinition\n");
      ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType -ValueTypeRedefinition");

      if (vtr.type_1.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Type One: %s\n", vtr.type_2.in ()));
      if (vtr.type_2.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Type Two: %s\n", vtr.type_2.in ()));
      ACE_RE_THROW;
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
 * @brief Cleanup the announce channel suppliers and reclaim resources
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::clean_announce_suppliers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::clean_announce_suppliers",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG:STDC::QMS::Citizen::Hello_World_Meta_Data::clean_announce_suppliers\n");
  if(!Announcement_Suppliers.empty())
   {
     unsigned int i = 0;
     for(i = 0; i < Announcement_Suppliers.size(); i++)
      {
	if(Announcement_Suppliers[i])
	 {
	   delete Announcement_Suppliers[i];
	   Announcement_Suppliers[i] = 0;
	 } /* end of if(Announcement_Suppliers[i]) */
      }
     Announcement_Suppliers.clear();
   }
}

/**
 * @brief Cleanup the request channel consumers and reclaim resources
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::clean_request_consumers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::clean_request_consumers",
	    __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::clean_request_consumers\n");
  if(!Request_Consumers.empty())
   {
     unsigned int i = 0;
     for(i = 0; i < Request_Consumers.size(); i++)
      {
	if(Request_Consumers[i])
	 {
	   delete Request_Consumers[i];
	   Request_Consumers[i] = 0;
	 } /* end of if(Request_Consumers[i]) */
      }
     Request_Consumers.clear();
   }
}

/**
 * @brief Cleanup the data channel suppliers and reclaim resources
 */
void
STDC::QMS::Citizen::Hello_World_Meta_Data::clean_data_suppliers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Hello_World_Meta_Data::clean_data_suppliers",
	    __LINE__,  __FILE__);
  DEBUG0(DEBUG_L_ENTER,
	 "DEBUG: STDC::QMS::Citizen::Hello_World_Meta_Data::clean_data_suppliers\n");
  if(!Data_Suppliers.empty())
   {
     unsigned int i = 0;
     for(i = 0; i < Data_Suppliers.size(); i++)
      {
	if(Data_Suppliers[i])
	 {
	   delete Data_Suppliers[i];
	   Data_Suppliers[i] = 0;
	 } /* end of if(Data_Suppliers[i]) */
      }
     Data_Suppliers.clear();
   }
}


#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class vector<STDC::QMS::Citizen::Sensor_Data_Element_HW *>;
template STDC::QMS::Citizen::Sensor_Data_Element_HW ** fill_n<STDC::QMS::Citizen::Sensor_Data_Element_HW **, unsigned int, STDC::QMS::Citizen::Sensor_Data_Element_HW *>(STDC::QMS::Citizen::Sensor_Data_Element_HW **, unsigned int, STDC::QMS::Citizen::Sensor_Data_Element_HW * const &);
template void fill<STDC::QMS::Citizen::Sensor_Data_Element_HW **, STDC::QMS::Citizen::Sensor_Data_Element_HW *>(STDC::QMS::Citizen::Sensor_Data_Element_HW **, STDC::QMS::Citizen::Sensor_Data_Element_HW **, STDC::QMS::Citizen::Sensor_Data_Element_HW * const &);
template class vector<STDC::QMS::Push_Supplier *> ;
template class vector<STDC::QMS::Push_Consumer *> ;
template STDC::QMS::Push_Supplier ** fill_n<STDC::QMS::Push_Supplier **, unsigned int, STDC::QMS::Push_Supplier *>(STDC::QMS::Push_Supplier **, unsigned int, STDC::QMS::Push_Supplier * const &);
template void fill<STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier *>(STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier * const &);
template STDC::QMS::Push_Consumer ** fill_n<STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer * const &);
template void fill<STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer * const &);


#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate vector<STDC::QMS::Citizen::Sensor_Data_Element_HW *>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

