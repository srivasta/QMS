//                              -*- Mode: C++ -*-
// MetaData.cpp ---
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
// Created On       : Sun Jul 22 13:53:44 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Jan  2 12:52:27 2002
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 270
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
 *  @brief Implentation of the Metadata object containing metadata about probes
 *
 * $Id: Meta_Data.cpp,v 1.113 2002/01/25 17:25:16 srivasta Exp $
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

#include "Meta_Data.h"
#include "Generic_Sensor_Impl.h"
#include "YP_Offer.h"

#if !defined(_WIN32)
#include <sys/time.h>
#include <time.h>
#endif

#include <Include/PlatformDefinitions.hpp>
#include <util/PlatformUtils.hpp>
#include <XalanTransformer/XalanTransformer.hpp>

#include "Continuous_Pipe_Proxy.h"

extern void CallBack(const string &query, void *arg_p);
extern STDC::QMS::Citizen::Generic_Sensor_Impl *sensor_p;

/// RCS version string
static const char* version =
"$Id: Meta_Data.cpp,v 1.113 2002/01/25 17:25:16 srivasta Exp $";

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

/// The default constructor
STDC::QMS::Citizen::Meta_Data::Meta_Data(void) :
  _supplier_id(17), msg_sequence_no_(0), _num_probes(0), 
  status(STDC::QMS::Citizen::RUN), _offer_created(false)
{
  QMS_Trace ("STDC::QMS::Citizen::Meta_Data::Meta_Data", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: Default constructor\n");
}

/**
 * @overload
 */
STDC::QMS::Citizen::Meta_Data::Meta_Data(STDC::QMS::Citizen::Meta_Data &rhs) :
  _config(rhs._config),
  _capability(rhs._capability),
  announce_list_info_(rhs.announce_list_info_),
  request_list_info_(rhs.request_list_info_),
  data_list_info_(rhs.data_list_info_),
  _supplier_id(rhs. _supplier_id),
  msg_sequence_no_(0),
  _num_probes(rhs._num_probes), 
  _offer_created(rhs._offer_created),
  _QMS_Schema(rhs._QMS_Schema)
{
  QMS_Trace ("STDC::QMS::Citizen::Meta_Data::Meta_Data", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: Copy constructor\n");
}

/**
 * @brief The = operator
 *
 * This avoids self assignements
 */
const STDC::QMS::Citizen::Meta_Data
STDC::QMS::Citizen::Meta_Data::operator=(STDC::QMS::Citizen::Meta_Data &copy)
{
  QMS_Trace ("STDC::QMS::Citizen::Meta_Data::operator =", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: Copy object\n");
  if(&copy != this)
   {
     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

     this->_config                = copy._config;
     this->_capability            = copy._capability;
     this->announce_list_info_ 	  = copy.announce_list_info_;
     this->request_list_info_ 	  = copy.request_list_info_;
     this->data_list_info_ 	  = copy.data_list_info_;
     this->_supplier_id           = copy._supplier_id;
     this->msg_sequence_no_	  = copy.msg_sequence_no_;
     this->_num_probes            = copy._num_probes;
     this->status                 = copy.status;
     this->_offer_created         = copy._offer_created;
     this->_QMS_Schema            = copy._QMS_Schema;
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
STDC::QMS::Citizen::Meta_Data::init(STDC::QMS::sensorServiceType  &config,
				    CORBA::Long supplier_id,
				    string &QMS_Schema)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  this->_config = config;
  this->_supplier_id = supplier_id;
  this->_QMS_Schema = QMS_Schema;
  this->_is_internal = true;
}

/** * @overload
 */
void
STDC::QMS::Citizen::Meta_Data::init(STDC::QMS::ProbeDefinitionType  &probe,
				    CORBA::Long supplier_id,
				    string &QMS_Schema)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  this->_capability = probe;
  this->_supplier_id = supplier_id;
  this->_QMS_Schema = QMS_Schema;
  this->_is_internal = false;
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
STDC::QMS::Citizen::Meta_Data::cleanup(STDC::QMS::CORBA_Handles *handles_p)
{
 this->withdraw_offer(handles_p);
 this->cleanup();
}

/**
 * @overload
 */
void
STDC::QMS::Citizen::Meta_Data::cleanup(void)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  DEBUG0 (2, "DEBUG: STDC::QMS::Citizen::Meta_Data::cleanup\n");

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
 * @param request_p A pointer to a struct containing the message and
 *                   the parsed data
 */
void
STDC::QMS::Citizen::Meta_Data::handle_query(struct query_info *request_p)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::handle_query", __LINE__,__FILE__);
  DEBUG0(2,"DEBUG: STDC::QMS::Citizen::Meta_Data::handle_query\n");
  int ret;

  // If the destinations flag is set, and we are not it, return
  if(!request_p->config.destinations.empty())
   {
     bool match = false;
     vector<STDC::QMS::msgDestination>::iterator dest;
     for(dest = request_p->config.destinations.begin();
	 dest != request_p->config.destinations.end(); dest++)
      {
	if(dest->id == this->_supplier_id)
	 {
	   match = true;
	   break;
	 } /* end of if(dest->id) */
      } /* end of for(dest = request_p.config.destinations.begin();
	   dest != request_p.config.destinations.end(); dest++)  */
     if(!match)
      {
	DEBUG0 (4, "Request not meant for us");
	return;
      }
   } /* end of if(!request_p.config.destinations.empty()) */

  // See if we have seen this key before
  std::map<string, struct query_info *>::iterator pos;
  pos = this->_requests.find(request_p->key);
  if(pos == this->_requests.end())
   {
     // We have not seen this key before
     if(request_p->config.Session.version != 0)
      {
	// Error!!
	string this_error("A request modification for a unknown request");

	std::cerr << this_error << std::endl;
	ret = this->send_error(this_error, request_p->config);
	return;
      } /* end of if(request_p->config.Session.version != 0) */

     // Handle new request


     // Do we have a probe in place or if the data is not reusable,
     // we need to create a new probe.
     if(!this->_capability.generic_prop.dataReusable || this->_probes.empty())
      {
	// Create a XalanTransformer.
	XalanTransformer transformer;

	string temp_input (request_p->query);
	std::istringstream input_stream(temp_input);
	std::ostringstream result_stream;
	XSLTInputSource xslt_source(&input_stream);
	XSLTInputSource
	  xsl_file(this->_capability.invocation_param.probeXSLTFile.c_str());
	XSLTResultTarget result_target(result_stream);

	transformer.setStylesheetParam(XalanDOMString("msgType"),
					  XalanDOMString("'new'"));

	transformer.setStylesheetParam(XalanDOMString("input"),
					  XalanDOMString("'getExecString'"));

	vector<STDC::QMS::variableType>::iterator iter;
	for(iter = this->_capability.invocation_param.xslParameters.begin();
	    iter != this->_capability.invocation_param.xslParameters.end();
	    iter++)
	 {
	   transformer.setStylesheetParam(XalanDOMString(iter->name.c_str()),
					  XalanDOMString(iter->value.c_str()));

	 } /* end of for(iter = a; iter != b; iter++) */

	int ret = transformer.transform(xslt_source, xsl_file, result_target);
	if(ret)
	 {
	   std::cerr << "Error running the transform"
		     <<  transformer.getLastError()
		     << std::endl;
	   string this_error("Error running the transform");
	   ret = this->send_error(this_error, request_p->config);
	   return;
	 } /* end of if(ret) */

	string result = result_stream.str();
	DEBUG1(2, "command line = %s", result.c_str());

	if(result.find("Error") != string::npos)
	 {
	   std::cerr << "Error running the transform"
		     << result
		     << std::endl;
	   ret = this->send_error(result, request_p->config);
	   return;
	 } /* end of if(result.find("Error") != string::npos) */

	std::istringstream unparsed_result_stream(result);
	vector<char *> arguments;
	// Chop up the results into individual parts
	while(!unparsed_result_stream.eof())
	 {
	   char * arg_str = new char [1024];
	   unparsed_result_stream.getline((char *)arg_str, 1024);
	   arguments.push_back(arg_str);
	 }
	vector<char *>::iterator arg;
	char **arg_list = new char *[arguments.size() + 2];
	int i = 0;
	for(i = 0; i < arguments.size() + 2; i++)
	 {
	   arg_list[i] = 0;
	 } /* end of for(i = 0; i < arguments.size() + 2; i++) */
	
	arg_list[0] = 
	  new char [this->_capability.invocation_param.probeExecutable.size() +
		    1];
	strncpy(arg_list[0],
		this->_capability.invocation_param.probeExecutable.c_str(),
		this->_capability.invocation_param.probeExecutable.size()
		+ 1);

	for(i=1, arg = arguments.begin(); arg != arguments.end(); i++,arg++)
	 {
	   arg_list[i] = 0;
           if(*arg && strlen(*arg))
	    {
	      arg_list[i] = new char [strlen(*arg) + 1];
	      strncpy(arg_list[i], *arg, strlen(*arg) + 1);
	      delete [] *arg;
	      *arg = 0;
	      if(iscntrl(arg_list[i][strlen(arg_list[i]) - 1]))
	       {
		  DEBUG0(6, "zapping newline");
		  arg_list[i][strlen(arg_list[i]) - 1] = '\0';
	       } /* end of if(iscntrl(arg_list[i][strlen(arg_list[i]) - 1])) */
	    } /* end of if(arg) */
	 }  /* end of for(arg = arguments.begin(); arg !=
	       arguments.end(); arg++) */

	if(this->_capability.generic_prop.probeType.compare("continuous") == 0)
	 {
	   DEBUG0(6, "Creating a continuous probe");

	   struct probe_info * probe_info_p = new struct probe_info;
	   probe_info_p->current_index = 0;
	   probe_info_p->data_count    = 0;
	   for(int i = 0; i < MAX_DATA; i++)
	    {
	      probe_info_p->data_store[i] = 0;
	    } /* end of for(int i = 0; i < MAX_DATA; i++) */

	   {
	     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
	     probe_info_p->id = this->_num_probes++;
	   }

	   char key_array[100];
	   ret = snprintf(key_array, 100, "%ld", probe_info_p->id);
	   if(ret == -1 || ret > 100)
	    {
	      std::cerr << "Buffer overflow in message, ignoring"
			<< std::endl;
	    } /* end of if(ret == -1 || ret > 100) */
	   string key = (char *)key_array;
	   string use_key;
	   if(!this->_capability.generic_prop.dataReusable)
	    {
	      use_key = request_p->key;
	    }
	   else
	    {
	      use_key = key;
	    } /* end of else */

	   DEBUG2(2, "Path for probe = %s, key = %s",
		  this->_capability.invocation_param.probeExecutable.c_str(),
		  use_key.c_str());
	   STDC::QMS::Citizen::Continuous_Pipe_Proxy * probe_p =
	     new  STDC::QMS::Citizen::Continuous_Pipe_Proxy(this->_capability.invocation_param.probeExecutable.c_str(), arg_list, *this, use_key);

	   // stash pointers to the probe
	   probe_info_p->probe_p = probe_p;

	   
	   request_p->probe_p = probe_p;
	   request_p->probe_info_p = probe_info_p;
	   
	   this->_requests.insert(std::make_pair(request_p->key, request_p));
	   this->_probes.insert(std::make_pair( key, probe_info_p));

	   // This operation does not return
	   DEBUG0(6, "Deploying a probe");
	   probe_p->deploy();
	   DEBUG0(6, "probe done");
	   DEBUG0(4, "DEBUG: Request terminated");
	   {
	     ACE_Write_Guard<ACE_RW_Mutex> guard(this->status_guard);
	     int index = 0;
	     if(probe_info_p)
	      {
		DEBUG0(6, "DEBUG: Cleaning data store");
		for(index = 0; index < MAX_DATA; index++)
		 {
		   if(probe_info_p->data_store[index])
		    {
		      DEBUG1(4, "DEBUG: Deleting stored data at index %d",
			     index);
		      delete [] probe_info_p->data_store[index];
		      probe_info_p->data_store[index] = 0;
		    } /* end of if(probe_info_p->data_store[index]) */
		 } /* end of for(index = 0; index < MAX_DATA; index++) */
		if(probe_info_p->probe_p)
		 {
		   probe_info_p->probe_p->destroy();
		   probe_info_p->probe_p = 0;
		 } /* end of if(probe_info_p) */
	      } /* end of if(probe_info_p) */
	     
	     if(request_p)
	      {
		DEBUG0(4, "DEBUG: erasing the request");
		pos = this->_requests.find(request_p->key);
		if(pos != this->_requests.end())
		 {
		   this->_requests.erase(pos);
		 } /* end of if(pos != this->_requests.end()) */
	      } /* end of if(request_p) */
	   }
	 }
	else
	 {
	   std::cerr << "Error: non continuous probes not yet implemented"
		     << std::endl;
	 } /* end of else */
      } /* end of if(!this->_capability.generic_prop.dataReusable) */
     else
      {
	// The data is reusable, and there already is a probe.
	// Add this request on to the probe

      } /* end of else */


   } /* end of if(pos == this->_requests.end()) */
  else
   {
     // We have seen this request before
     if(request_p->config.Session.version == 0)
      {
	string this_error("A duplicate request received ");
	std::cerr << this_error << request_p->config.Session.version
		  << std::endl;
	ret = this->send_error(this_error, request_p->config);
	return;
      } /* end of if(request_p->config.Session.version == 0) */

     // Create a XalanTransformer.
     XalanTransformer transformer;
     int ret = 0;

     string temp_input (request_p->query);

     std::istringstream input_stream(temp_input);
     std::ostringstream result_stream;
     XSLTInputSource xslt_source(&input_stream);
     XSLTInputSource
       xsl_file(this->_capability.invocation_param.probeXSLTFile.c_str());
     XSLTResultTarget result_target(result_stream);

     transformer.setStylesheetParam(XalanDOMString("msgType"),
				    XalanDOMString("'modify'"));

     transformer.setStylesheetParam(XalanDOMString("input"),
				    XalanDOMString("'getAction'"));

     vector<STDC::QMS::variableType>::iterator iter;
     for(iter = this->_capability.invocation_param.xslParameters.begin();
	 iter != this->_capability.invocation_param.xslParameters.end();
	 iter++)
      {
	transformer.setStylesheetParam(XalanDOMString(iter->name.c_str()),
				       XalanDOMString(iter->value.c_str()));

      } /* end of for(iter = a; iter != b; iter++) */
     DEBUG0(2, "Do the transform, looking for an action");
     ret = transformer.transform(xslt_source, xsl_file, result_target);
     if(ret)
     {
       std::cerr << "Error running the transform"
                 <<  transformer.getLastError()
                 << std::endl;
       string this_error("Error running the transform");
       ret = this->send_error(this_error, request_p->config);
       return;
     } /* end of if(ret) */

     string result = result_stream.str();
     DEBUG1(4, "DEBUG: action = %s", result.c_str());
     if(result.find("Error") != string::npos)
      {
	std::cerr << "Error running the transform"
		  << result
		  << std::endl;
	ret = this->send_error(result, request_p->config);
	return;
      } /* end of if(result.find("Error") != string::npos) */

     if(result.find("start") != string::npos)
      {
	DEBUG0(2, "DEBUG: invoking start");
	pos->second->config.destinations.clear();
	pos->second->config.reply_tos.clear();
	pos->second->config = request_p->config;
	ret = pos->second->probe_p->start();
      } /* end of if(result.find("start") != string::npos) */
     if(result.find("pause") != string::npos)
      {
	DEBUG0(2, "DEBUG: invoking pause");
	pos->second->config.destinations.clear();
	pos->second->config.reply_tos.clear();
	pos->second->config = request_p->config;
	ret = pos->second->probe_p->pause();
      } /* end of if(result.find("pause") != string::npos) */
     if(result.find("resume") != string::npos)
      {
	DEBUG0(2, "DEBUG: invoking resume");
	pos->second->config.destinations.clear();
	pos->second->config.reply_tos.clear();
	pos->second->config = request_p->config;
	ret = pos->second->probe_p->resume();
      } /* end of if(result.find("resume") != string::npos) */
     if(result.find("stop") != string::npos)
      {
	DEBUG0(2, "DEBUG: invoking stop");
	pos->second->config.destinations.clear();
	pos->second->config.reply_tos.clear();
	pos->second->config = request_p->config;
	ret = pos->second->probe_p->kill();
      } /* end of if(result.find("stop") != string::npos) */


     if(result.find("write-to-pipe") != string::npos)
      {
	DEBUG0(4, "DEBUG: writing to pipe");
	std::istringstream pipe_input_stream(temp_input);
	std::ostringstream pipe_result_stream;
	XSLTInputSource pipe_xslt_source(&pipe_input_stream);
	XSLTResultTarget pipe_result_target(pipe_result_stream);

	transformer.setStylesheetParam(XalanDOMString("msgType"),
				       XalanDOMString("'modify'"));

	transformer.setStylesheetParam(XalanDOMString("input"),
				       XalanDOMString("'getProbeString'"));

	for(iter = this->_capability.invocation_param.xslParameters.begin();
	    iter != this->_capability.invocation_param.xslParameters.end();
	    iter++)
	 {
	   transformer.setStylesheetParam(XalanDOMString(iter->name.c_str()),
					  XalanDOMString(iter->value.c_str()));

	 } /* end of for(iter = a; iter != b; iter++) */

	ret = transformer.transform(pipe_xslt_source, xsl_file,
				    pipe_result_target);
	if(ret)
	 {
	   std::cerr << "Error running the transform"
		     <<  transformer.getLastError()
		     << std::endl;
	   string this_error("Error running the transform");
	   ret = this->send_error(this_error, request_p->config);
	   return;
	 } /* end of if(ret) */
	string pipe_result = pipe_result_stream.str();
	DEBUG1(4, "DEBUG: string to write = %s", pipe_result.c_str());
	if(pipe_result.find("Error") != string::npos)
	 {
	   std::cerr << "Error running the transform"
		     << pipe_result
		     << std::endl;
	   ret = this->send_error(pipe_result, request_p->config);
	   return;
	 } /* end of if(result.find("Error") != string::npos) */

	pos->second->config.destinations.clear();
	pos->second->config.reply_tos.clear();
	pos->second->config = request_p->config;
	pos->second->probe_p->send_command(pipe_result);
      } /* end of if(result.find("exec") != string::npos) */

     // WELL, SEE IF WE ARE TERMINAL


     std::istringstream end_input_stream(temp_input);
     std::ostringstream end_result_stream;
     XSLTInputSource end_xslt_source(&end_input_stream);
     XSLTResultTarget end_result_target(end_result_stream);

     transformer.setStylesheetParam(XalanDOMString("msgType"),
				    XalanDOMString("'modify'"));

     transformer.setStylesheetParam(XalanDOMString("input"),
				    XalanDOMString("'getIsTerminate'"));

     for(iter = this->_capability.invocation_param.xslParameters.begin();
	 iter != this->_capability.invocation_param.xslParameters.end();
	 iter++)
      {
	transformer.setStylesheetParam(XalanDOMString(iter->name.c_str()),
				       XalanDOMString(iter->value.c_str()));

      } /* end of for(iter = a; iter != b; iter++) */

     ret = transformer.transform(end_xslt_source, xsl_file, end_result_target);
     if(ret)
      {
	std::cerr << "Error running the transform"
		  <<  transformer.getLastError()
		  << std::endl;
	string this_error("Error running the transform");
	ret = this->send_error(this_error, request_p->config);
	return;
      } /* end of if(ret) */

     string end_result = end_result_stream.str();
     DEBUG1(4, "DEBUG: are we terminated? = %s", end_result.c_str());
     if(end_result.find("Error") != string::npos)
      {
	std::cerr << "Error running the transform"
		  << end_result
		  << std::endl;
	ret = this->send_error(end_result, request_p->config);
	return;
      } /* end of if(result.find("Error") != string::npos) */

     if(end_result.find("true") != string::npos)
      {
	DEBUG0(6, "DEBUG: Request terminated");
	if(request_p)
	 {
	   ACE_Write_Guard<ACE_RW_Mutex> guard(this->status_guard);
	   pos = this->_requests.find(request_p->key);
	   if(pos != this->_requests.end())
	    {
	      DEBUG0(4, "DEBUG: erasing the request");
	      pos->second->config.destinations.clear();
	      pos->second->config.reply_tos.clear();

	      int index = 0;
	      if(pos->second->probe_info_p)
	       {
		 DEBUG0(4, "DEBUG: Cleaning data store");
		 for(index = 0; index < MAX_DATA; index++)
		  {
		    if(pos->second->probe_info_p->data_store[index])
		     {
		       DEBUG1(4, "DEBUG: Deleting stored data at index %d",
			      index);
		       delete [] pos->second->probe_info_p->data_store[index];
		       pos->second->probe_info_p->data_store[index] = 0;
		     } /* if(pos->second->probe_info_p->data_store[index]) */
		  } /* end of for(index = 0; index < MAX_DATA; index++) */
		 if(pos->second->probe_p)
		  {
		    pos->second->probe_p->destroy();
		    pos->second->probe_p = 0;
		    pos->second->probe_info_p->probe_p = 0;
		  } /* end of if(pos->second->probe_p) */
	       } /* end of if(pos->second->probe_info_p) */
	      DEBUG0(3, "DEBUG: erasing the request");
	      this->_requests.erase(pos);
	    } /* end of if(pos != this->_requests.end()) */
	 } /* end of if(request_p) */
      } /* end of if(end_result.find("true") != string::npos) */
   } /* end of else */
}

/**
 * @brief Handle the data coming in from the probe.
 * @param key The request this data belongs to (helps identify the probe)
 * @param data  The data to be dispatched
 */
void
STDC::QMS::Citizen::Meta_Data::handle_data(string key, string data)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::handle_data", __LINE__,__FILE__);
  DEBUG0(2,"DEBUG: STDC::QMS::Citizen::Meta_Data::handle_data\n");

  // remove the <?xml version="1.0" encoding="UTF-8"?> from the data
  int ret = 0;
  string::size_type index = data.find("?>");
  if(index != string::npos)
   {
     DEBUG0(2, "DEBUG: Editing out the first  line of data");
     data.erase(0, index + 2);
   } /* end of if(ret != string::npos) */

  std::ostringstream response_stream;

  time_t this_time = time(0);
  struct tm *now_p = gmtime((const time_t *) &this_time);


  if(!this->_capability.generic_prop.dataReusable)
   {
     std::map<string, struct query_info *>::iterator pos;
     pos = this->_requests.find(key);
     if(pos == this->_requests.end())
      {
	// The request must have been clsoed out
	DEBUG0(6, "DEBUG: Request no longer exists");
	return;
      }
     response_stream
       << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" <<             std::endl
       << "  <qms:QMSMessage xmlns=\"http://www.stdc.com/2001/QMSSchema\" "
       <<                                                             std::endl
       << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
       <<                                                             std::endl
       << "    xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\" "
       <<                                                             std::endl
       << "    xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema "
       << this->_QMS_Schema << "\"> " <<                              std::endl
       << "  <qms:msgSequenceNo>" << ++this->msg_sequence_no_
       << "</qms:msgSequenceNo>" <<                                   std::endl
       << "  <qms:msgDate>" << (1900 + now_p->tm_year) << "-"
       << (1 + now_p->tm_mon) << "-" << now_p->tm_mday
       << "</qms:msgDate>" <<                                         std::endl
       << "  <qms:msgTime>" << now_p->tm_hour << ":"
       << now_p->tm_min << ":" <<  now_p->tm_sec
       << "-0:00</qms:msgTime>" <<                                    std::endl
       << "  <qms:originatingHost>"
       << this->_capability.offer_prop.QMSUniqueName.host
       << "</qms:originatingHost>" <<                                 std::endl
       << "  <qms:msgSender>" <<                                      std::endl
       << "    <id>" << this->_supplier_id << "</id>" <<              std::endl
       << "    <description>Generic Seonsor Response</description>" <<std::endl
       << "  </qms:msgSender>" <<                                     std::endl
       << "  <qms:msgDestination>" <<                                 std::endl
       << "    <id>" << pos->second->config.sender.id  << "</id>" <<  std::endl
       << "    <description>Generic Sensor Data</description>" <<     std::endl
       << "</qms:msgDestination>" <<                                  std::endl
       << "  <qms:QMSUniqueName> " <<                                 std::endl
       << "    <category>" 
       << this->_capability.offer_prop.QMSUniqueName.category 
       << "</category>" <<                                            std::endl
       << "    <host>" << this->_capability.offer_prop.QMSUniqueName.host
       << "</host>"     <<                                            std::endl
       << "    <uuid>" << this->_capability.offer_prop.QMSUniqueName.uuid
       << "</uuid> " <<                                               std::endl
       << "  </qms:QMSUniqueName>" <<                                 std::endl
       << "  <qms:Session>" <<                                        std::endl
       << "    <requestID>" << pos->second->config.Session.request_id
       << "</requestID>" <<                                           std::endl
       << "    <version>" << pos->second->config.Session.version
       << "</version>"  << std::endl << "    <minRepetitions>" <<     std::endl
       << "      <count>" << pos->second->config.Session.repititions.count
       << "</count>" << std::endl << "      <current>"
       << pos->second->probe_info_p->data_count++ + 1 << "</current>"
       <<                                                             std::endl
       << "    </minRepetitions>" << std::endl << "    <minRepeatInterval>"
       << pos->second->config.Session.interval << "</minRepeatInterval>"
       << std::endl << "  </qms:Session> " << std::endl << "  <qms:payload>"
       << std::endl << data << std::endl << "  </qms:payload>" <<     std::endl
       << "</qms:QMSMessage>" << std::endl
       ;

     DEBUG1(2, "DEBUG: Data to be sent is = %s", 
	    response_stream.str().c_str());

     char **data_store = pos->second->probe_info_p->data_store;
     int index = pos->second->probe_info_p->current_index;
     if(data_store[index])
      {
	DEBUG2 (2, "Deleting data at location data_store[%d]=%s", index,
		data_store[index]);

	delete [] data_store[index];
	data_store[index] = 0;
	
	DEBUG1 (2, "Adding data at location  %d", index);
	data_store[index] = new char [data.size() + 3 ];
	strncpy(data_store[index], data.c_str(), data.size() + 2);
	DEBUG1 (2, "Copied  %d bytes of dsta", data.size());
      } /* end of if(pos->data_store[pos->current_index]) */
     
     DEBUG0(2, "DEBUG: incrementing index");
     pos->second->probe_info_p->current_index =
       ++index % MAX_DATA;
     DEBUG1(2, "DEBUG: Data store index now = %d",
	    pos->second->probe_info_p->current_index);
   } // if(!this->_capability.generic_prop.dataReusable)
  else
   {
     std::map<string, struct probe_info *>::iterator pos;
     pos = this->_probes.find(key);
     if(pos == this->_probes.end())
      {
	// The request must have been clsoed out
	DEBUG0(6, "DEBUG: Probe no longer exists");
	return;
      }
     response_stream
       << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" <<             std::endl
       << "  <qms:QMSMessage xmlns=\"http://www.stdc.com/2001/QMSSchema\" "
       <<                                                             std::endl
       << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
       <<                                                             std::endl
       << "    xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\" "
       <<                                                             std::endl
       << "    xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema "
       << this->_QMS_Schema << "\"> " <<                              std::endl
       << "  <qms:msgSequenceNo>" << ++this->msg_sequence_no_
       << "</qms:msgSequenceNo>" <<                                   std::endl
       << "  <qms:msgDate>" << (1900 + now_p->tm_year) << "-"
       << (1 + now_p->tm_mon) << "-" << now_p->tm_mday
       << "</qms:msgDate>" <<                                         std::endl
       << "  <qms:msgTime>" << now_p->tm_hour << ":"
       << now_p->tm_min << ":" <<  now_p->tm_sec
       << "-0:00</qms:msgTime>" <<                                    std::endl
       << "  <qms:originatingHost>"
       << this->_capability.offer_prop.QMSUniqueName.host
       << "</qms:originatingHost>" <<                                 std::endl
       << "  <qms:msgSender>" <<                                      std::endl
       << "    <id>" << this->_supplier_id << "</id>" <<              std::endl
       << "    <description>Generic Seonsor Response</description>" <<std::endl
       << "  </qms:msgSender>" <<                                     std::endl
       << "  <qms:QMSUniqueName> " <<                                 std::endl
       << "    <category>" 
       << this->_capability.offer_prop.QMSUniqueName.category 
       << "</category>" <<                                            std::endl
       << "    <host>" << this->_capability.offer_prop.QMSUniqueName.host
       << "</host>"     <<                                            std::endl
       << "    <uuid>" << this->_capability.offer_prop.QMSUniqueName.uuid
       << "</uuid> " <<                                               std::endl
       << "  </qms:QMSUniqueName>" <<                                 std::endl
       << "  <qms:Session>" <<                                        std::endl
       << "    <requestID>" << 1000 << "</requestID>" <<              std::endl
       << "    <version>" << 0 << "</version>"  <<                    std::endl
       << "    <minRepetitions>" <<                                   std::endl
       << "      <count>" << 9999 << "</count>" <<                    std::endl
       << "      <current>" << pos->second->data_count++ + 1 
       << "</current>" <<                                             std::endl
       << "    </minRepetitions>" << std::endl << "    <minRepeatInterval>"
       << "PT1.0S" << "</minRepeatInterval>"
       << std::endl << "  </qms:Session> " << std::endl << "  <qms:payload>"
       << std::endl << data << std::endl << "  </qms:payload>" <<     std::endl
       << "</qms:QMSMessage>" << std::endl
       ;
     DEBUG1(2, "DEBUG: Data to e sent is = %s", response_stream.str().c_str());

     if(pos->second->data_store[pos->second->current_index])
      {
	delete pos->second->data_store[pos->second->current_index];
	pos->second->data_store[pos->second->current_index] = 0;
	
	pos->second->data_store[pos->second->current_index] =
	  new char [data.size() + 1 ];
	strncpy(pos->second->data_store[pos->second->current_index],
		data.c_str(), data.size() + 1);
      } /* end of if(pos->data_store[pos->current_index]) */

     pos->second->current_index = ++pos->second->current_index % MAX_DATA;
     DEBUG1(2, "DEBUG: Dta store index now = %d",
	    pos->second->current_index);
   } /* end of else */
  DEBUG1(2, "DEBUG: sending %s", response_stream.str().c_str());
  ret = this->send(response_stream.str());
}


/**
 * @brief Add information about an announce channel
 * @param param Event channel information
 */
void
STDC::QMS::Citizen::Meta_Data::add_announce_info(STDC::QMS::Citizen::Sensor_Data_Element  * param)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  DEBUG2(2, "DEBUG: Adding announce channel=%s\n\tevent_id=%d",
	 param->get_name().c_str(), param->get_int_val() );
  this->announce_list_info_.push_back(param);
}

/**
 * @brief Add information about an request channel
 * @param param Event channel information
 */
void
STDC::QMS::Citizen::Meta_Data::add_request_info(STDC::QMS::Citizen::Sensor_Data_Element * param)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  DEBUG2(2, "DEBUG: Adding request channel=%s\n\tevent_id=%d",
	 param->get_name().c_str(), param->get_int_val() );
  this->request_list_info_.push_back(param);
}

/**
 * @brief Add information about an data channel
 * @param param Event channel information
 */
void
STDC::QMS::Citizen::Meta_Data::add_data_info(STDC::QMS::Citizen::Sensor_Data_Element * param)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  DEBUG2(2, "DEBUG: Adding data channel=%s\n\tevent_id=%d",
	 param->get_name().c_str(), param->get_int_val() );
  this->data_list_info_.push_back(param);
}

/**
 * @brief Store a handle to the QMS Trader EC info service
 * @param ec_registry Event channel information object handle
 */
void
STDC::QMS::Citizen::Meta_Data::add_ec_registry(STDC::QMS::Citizen::QMS_Trader_ECInfo_var ec_registry)
{
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  this->_ec_registry = ec_registry;
}

/**
 * @brief Remove all the event channel information and reclaim resources
 */
void
STDC::QMS::Citizen::Meta_Data::clean_EC_info(void)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::clean_EC_info", __LINE__,
	    __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::clean_EC_info\n");

  vector<STDC::QMS::Citizen::Sensor_Data_Element *>::iterator iter;

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
STDC::QMS::Citizen::Meta_Data::get_EC_info(void)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::get_EC_info", __LINE__,
	    __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Citizen::Meta_Data::get_EC_info\n");

  STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq 	*ImportAECSeq = 0;
  STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq 	*ImportDECSeq = 0;
  STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq 	*ImportRECSeq = 0;
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      CORBA::ULong i =0;

      char *uniq_name_p = 0;

      if(this->_is_internal)
       {
	 uniq_name_p =
	   const_cast< char * >
	   (this->_config.offer_prop.QMSUniqueName.category.c_str());
       } /* end of if(this->_is_internal) */
      else
       {
	 uniq_name_p =
	   const_cast< char * >
	   (this->_capability.offer_prop.QMSUniqueName.category.c_str());
       } /* end of else */


      ImportAECSeq =
	this->_ec_registry->getAnnounceChannels(uniq_name_p);
      ACE_TRY_CHECK;

      if(ImportAECSeq)
       {
	 for(i =0; i < ImportAECSeq->length() ; i++)
	  {
	    STDC::QMS::Citizen::Sensor_Data_Element * data_p =
	      new STDC::QMS::Citizen::Sensor_Data_Element();

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
	    STDC::QMS::Citizen::Sensor_Data_Element * data_p =
	      new STDC::QMS::Citizen::Sensor_Data_Element();

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
	    STDC::QMS::Citizen::Sensor_Data_Element * data_p =
	      new STDC::QMS::Citizen::Sensor_Data_Element();

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
      std::cerr << " A unknown exception was caught " << std::endl;
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
STDC::QMS::Citizen::Meta_Data::create_announce_suppliers(RtecEventComm::EventSourceID my_id,
				     STDC::QMS::CORBA_Handles *handles_p,
				     CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::create_announce_suppliers",
	    __LINE__, __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::create_announce_suppliers\n");
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

	       this->Announcement_Suppliers.push_back(supplier_p);
	     } /* end of if(!ec_name.empty()) */
	    else
	     {
	       DEBUG0(4,"DEBUG: empty announce list\n");
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
STDC::QMS::Citizen::Meta_Data::create_request_consumers
(STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::create_request_consumers",
	    __LINE__, __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::create_request_consumers\n");
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
	       DEBUG0(4,"DEBUG: empty request list\n");
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
STDC::QMS::Citizen::Meta_Data::create_data_suppliers(RtecEventComm::EventSourceID my_id,
				 STDC::QMS::CORBA_Handles *handles_p,
				 CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::create_data_suppliers", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Citizen::Meta_Data::create_data_suppliers\n");
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
	       this->Data_Suppliers.push_back(supplier_p);
	     } /* end of if(!ec_name.empty()) */
	    else
	     {
	       DEBUG0(4,"DEBUG: empty data list\n");
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
STDC::QMS::Citizen::Meta_Data::connect_announce_suppliers(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::connect_announce_suppliers",
	    __LINE__, __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::connect_announce_suppliers\n");
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
STDC::QMS::Citizen::Meta_Data::connect_request_consumers(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::connect_request_consumers",
	    __LINE__, __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::connect_request_consumers\n");
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
STDC::QMS::Citizen::Meta_Data::connect_data_suppliers(CORBA::Environment &
						      ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::connect_data_suppliers", __LINE__,
	    __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::connect_data_suppliers\n");
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
STDC::QMS::Citizen::Meta_Data::disconnect_announce_suppliers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::disconnect_announce_suppliers",
	    __LINE__, __FILE__);
  DEBUG0(2,
	 "DEBUG:STDC::QMS::Citizen::Meta_Data::disconnect_announce_suppliers\n");
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
STDC::QMS::Citizen::Meta_Data::disconnect_request_consumers(CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::disconnect_request_consumers",
	    __LINE__, __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::disconnect_request_consumers\n");
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
STDC::QMS::Citizen::Meta_Data::disconnect_data_suppliers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::disconnect_data_suppliers",
	    __LINE__,  __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::disconnect_data_suppliers\n");
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
 * @brief Send out an error message
 * @param error The error string to send out
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 * @ret the count of errors encountered while sending
 */
int
STDC::QMS::Citizen::Meta_Data::send_error(const string &error,
					  STDC::QMS::QMSMessage &config,
					  CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::send_error", __LINE__, __FILE__);
  DEBUG0(2,	"DEBUG: STDC::QMS::Citizen::Meta_Data::send_error\n");

  std::ostringstream response_stream;

  time_t this_time = time(0);
  struct tm *now_p = gmtime((const time_t *) &this_time);

  std::cerr << "QMS_Schema" << this->_QMS_Schema << std::endl;
  std::cerr << "sequence" << this->msg_sequence_no_ << std::endl;
  std::cerr << "year" <<(1900 + now_p->tm_year) << std::endl;
  std::cerr << "mon" << (1 + now_p->tm_mon) << std::endl;
  std::cerr << "mday" << now_p->tm_mday << std::endl;
  std::cerr << "hour" << now_p->tm_hour << std::endl;
  std::cerr << "min" << now_p->tm_min << std::endl;
  std::cerr << "sec" << now_p->tm_sec << std::endl;
  std::cerr << "category" << this->_capability.offer_prop.QMSUniqueName.category
	    << std::endl;
  std::cerr << "host" << this->_capability.offer_prop.QMSUniqueName.host
	     << std::endl;
  std::cerr << "uuid" << this->_capability.offer_prop.QMSUniqueName.uuid
	     << std::endl;
  std::cerr << "supplier" << this->_supplier_id << std::endl;
  std::cerr << "sender" << config.sender.id << std::endl;
  std::cerr << "request" << config.Session.request_id << std::endl;
  std::cerr << "version" << config.Session.version << std::endl;
  std::cerr << "repititions" <<config.Session.repititions.count << std::endl;
  std::cerr << "interval" << config.Session.interval  << std::endl;
  std::cerr << "error " << error << std::endl;

  response_stream
    << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" <<                std::endl
    << "  <qms:QMSMessage xmlns=\"http://www.stdc.com/2001/QMSSchema\" "
    <<                                                                std::endl
    << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
    <<                                                                std::endl
    << "    xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\" "
    <<                                                                std::endl
    << "    xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema "
    << this->_QMS_Schema << "\"> " <<                                 std::endl
    << "  <qms:msgSequenceNo>" << ++this->msg_sequence_no_
    << "</qms:msgSequenceNo>" <<                                      std::endl
    << "  <qms:msgDate>" << (1900 + now_p->tm_year) << "-"
    << (1 + now_p->tm_mon) << "-" << now_p->tm_mday
    << "</qms:msgDate>" <<                                            std::endl
    << "  <qms:msgTime>" << now_p->tm_hour << ":"
    << now_p->tm_min << ":" <<  now_p->tm_sec
    << "-0:00</qms:msgTime>" <<                                       std::endl
    << "  <qms:originatingHost>"
    << this->_capability.offer_prop.QMSUniqueName.host
    << "</qms:originatingHost>" <<                                    std::endl
    << "  <qms:msgSender>" <<                                         std::endl
    << "    <id>" << this->_supplier_id << "</id>" <<                 std::endl
    << "    <description>Generic Seonsor Response</description>" <<   std::endl
    << "  </qms:msgSender>" <<                                        std::endl
    << "  <qms:msgDestination>" <<                                    std::endl
    << "    <id>" << config.sender.id  << "</id>" <<                  std::endl
    << "    <description>Generic Sensor Error </description>" <<      std::endl
    << "</qms:msgDestination>" <<                                     std::endl
    << "  <qms:QMSUniqueName> " <<                                    std::endl
    << "    <category>" 
    << this->_capability.offer_prop.QMSUniqueName.category 
    << "</category>" <<                                               std::endl
    << "    <host>" << this->_capability.offer_prop.QMSUniqueName.host
    << "</host>"     <<                                               std::endl
    << "    <uuid>" << this->_capability.offer_prop.QMSUniqueName.uuid
    << "</uuid> " <<                                                  std::endl
    << "  </qms:QMSUniqueName>" <<                                    std::endl
    << "  <qms:Session>" <<                                        std::endl
    << "    <requestID>" << config.Session.request_id
    << "</requestID>" <<                                           std::endl
    << "    <version>" << config.Session.version
    << "</version>"  << std::endl << "    <minRepetitions>" <<     std::endl
    << "      <count>" << config.Session.repititions.count
    << "</count>" << std::endl << "      <current>"
    << 1 << "</current>"  <<     std::endl
    << "    </minRepetitions>" << std::endl << "    <minRepeatInterval>"
    << config.Session.interval << "</minRepeatInterval>"
    << std::endl << "  </qms:Session> " << std::endl << "  <qms:error>"
    << std::endl << error << std::endl << "  </qms:error>" <<     std::endl
    << "</qms:QMSMessage>" << std::endl
    ;
  
  DEBUG1(4, "The error message being sent is %s", 
	 response_stream.str().c_str());
  return this->send(response_stream.str(), ACE_TRY_ENV);
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
STDC::QMS::Citizen::Meta_Data::send(const string data,
				    CORBA::Environment &ACE_TRY_ENV)
{
  int ret = 0;
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::send", __LINE__, __FILE__);
  DEBUG0(2,	"DEBUG: STDC::QMS::Citizen::Meta_Data::send\n");

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
STDC::QMS::Citizen::Meta_Data::withdraw_offer(STDC::QMS::CORBA_Handles *
					      handles_p,
					      CORBA::Environment
					      &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::withdraw_offer", __LINE__,
	    __FILE__);
  DEBUG0(2,
	 "DEBUG:STDC::QMS::Citizen::Meta_Data::withdraw_offer\n");
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
         std::cerr << "trader does not support updates" << std::endl;
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
STDC::QMS::Citizen::Meta_Data::make_offer(CORBA::Object_ptr obj,
					  STDC::QMS::CORBA_Handles * handles_p,
					  CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::make_offer", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Citizen::Meta_Data::make_offer\n");
  ACE_TRY
    {
      CosTrading::Lookup_var lookup_var =
	handles_p->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CosTrading::Register_var reg_var = lookup_var->register_if();
      if(CORBA::is_nil(reg_var.in()))
       {
	 std::cerr << "trader does not support updates" << std::endl;
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
      if(this->_is_internal)
       {
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
       } /* end of if(this->_is_internal) */
      else
       {
	 for(offers  = this->_capability.offer_param.begin();
	     offers != this->_capability.offer_param.end();
	     offers++)
	  {
	    count ++;
	    if(offers->searchable)
	     {
	       count ++;
	     } /* end of if(offers->searchable) */
	  }
       } /* end of else */

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

      props[count].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
      if(this->_is_internal)
       {
	 props[count].value <<=
	   this->_config.offer_prop.QMSUniqueName.category.c_str();
       } /* end of if(this->_is_internal) */
      else
       {
	 props[count].value <<=
	   this->_capability.offer_prop.QMSUniqueName.category.c_str();
       } /* end of else */
      count ++;

      props[count].name  = CORBA::string_dup ("QMS_UNIQ_NAME_HOST_NAME");
      if(this->_is_internal)
       {
	 props[count].value <<=
	   this->_config.offer_prop.QMSUniqueName.host.c_str();
       } /* end of if(this->_is_internal) */
      else
       {
	 props[count].value <<=
	   this->_capability.offer_prop.QMSUniqueName.host.c_str();
       } /* end of else */

      count ++;

      props[count].name  = CORBA::string_dup ("QMS_UNIQ_NAME_UUID");
      if(this->_is_internal)
       {
	 props[count].value <<=
	   this->_config.offer_prop.QMSUniqueName.uuid.c_str();
       } /* end of if(this->_is_internal) */
      else
       {
	 props[count].value <<=
	   this->_capability.offer_prop.QMSUniqueName.uuid.c_str();
       }/* end of else */
      count ++;

      props[count].name  = CORBA::string_dup ("VERSION");
      if(this->_is_internal)
       {
	 props[count].value <<=
	   this->_config.schema_prop.schemaVersion.c_str();
       } /* end of if(this->_is_internal) */
      else
       {
	 props[count].value <<=
	   this->_capability.schema_prop.schemaVersion.c_str();
       }/* end of else */
      count ++;

      props[count].name  = CORBA::string_dup ("PROBE_SCHEMA_URI");
      if(this->_is_internal)
       {
	 props[count].value <<= this->_config.schema_prop.probeSchema.c_str();
       } /* end of if(this->_is_internal) */
      else
       {
	 props[count].value <<=
	   this->_capability.schema_prop.probeSchema.c_str();
       }/* end of else */
      count ++;

      props[count].name  = CORBA::string_dup ("QMS_SCHEMA_URI");
      props[count].value <<= this->_QMS_Schema.c_str();
      count ++;

      props[count].name  = CORBA::string_dup ("SUPPLIER_ID");
      props[count].value <<= this->_supplier_id;
      count ++;
      if(this->_is_internal)
       {
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
       }
      else
       {
	 for(offers  = this->_capability.offer_param.begin();
	     offers != this->_capability.offer_param.end();
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
       } /* end of else */

      if(this->_is_internal)
       {
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
       } /* end of if(this->_is_internal) */
      else
       {
	 for(offers  = this->_capability.offer_param.begin();
	     offers != this->_capability.offer_param.end();
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
       } /* end of else */

      string value;
      string name;
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
	       value.append("</Event_Type>\n");

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
	       value.append("</Event_Type>\n");

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
	       value.append("</Event_Type>\n");

	       name.assign("Data_");
	       name.append(index_buf);

	       props[count].name  = name.c_str();
	       props[count].value <<= value.c_str();
	       count ++;
	     }
	  }
       }

      this->offer_id  = reg_var->_cxx_export(obj,
					     "STDC_QMS_CITIZEN_GENERIC_SENSOR",
					     props, ACE_TRY_ENV);
      ACE_TRY_CHECK;

    }
  ACE_CATCH (CosTrading::UnknownServiceType, excp)
    {
      DEBUG0(2, "DEBUG: No service type making probe yp offer\n");
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::IllegalPropertyName, excp)
    {
      DEBUG0(6,
	     "DEBUG: IllegalPropertyName making probe yp offer\n");
      ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType-IllegalPropertyName");

      if (excp.name.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Invalid name: %s\n", excp.name.in ()));
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
	     vtr)
    {
      DEBUG0(2,
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
 * This method is simpler than the one used in Generic_Sensor_Impl.cpp
 * because we can be sure that the service type for the offer must
 * exist.  First, if the yp_offer has already been created, we
 * just return, making this function idempotent. If that is not the
 * case, we just go ahead and make an offer, using make_offer()
 * above. If it throws an unexpected exception, we just allow that to
 * bubble up.
 */
void
STDC::QMS::Citizen::Meta_Data::yp_offer(CORBA::Object_ptr obj,
					STDC::QMS::CORBA_Handles * handles_p,
					CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::yp_offer", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: STDC::QMS::Citizen::Meta_Data::yp_offer\n");
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
      std::cerr << "No service type (ignored  need to add service type (probe)"
		<< std::endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::PropertyTypeMismatch, excp)
    {
      DEBUG0(6, "DEBUG: Property type mismatch\n");
       if (excp.type.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Invalid type: %s\n", excp.type.in ()));
       if(excp.prop.name.in())
        {
          std::cerr << "Invalid property name " << excp.prop.name.in ()
		    << std::endl;
        } /* end of if(excp.something.name.in()) */
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::IllegalPropertyName, excp)
    {
      DEBUG0(6, "DEBUG: IllegalPropertyName\n");
      ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType-IllegalPropertyName");

      if (excp.name.in () != 0)
        ACE_DEBUG ((LM_DEBUG, "Invalid name: %s\n", excp.name.in ()));
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition, vtr)
    {
      DEBUG0(6, "DEBUG: ValueTypeRedefinition\n");
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
STDC::QMS::Citizen::Meta_Data::clean_announce_suppliers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::clean_announce_suppliers",
	    __LINE__, __FILE__);
  DEBUG0(2,
	 "DEBUG:STDC::QMS::Citizen::Meta_Data::clean_announce_suppliers\n");
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
STDC::QMS::Citizen::Meta_Data::clean_request_consumers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::clean_request_consumers",
	    __LINE__, __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::clean_request_consumers\n");
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
STDC::QMS::Citizen::Meta_Data::clean_data_suppliers(void)
{
  QMS_Trace("STDC::QMS::Citizen::Meta_Data::clean_data_suppliers",
	    __LINE__,  __FILE__);
  DEBUG0(2,
	 "DEBUG: STDC::QMS::Citizen::Meta_Data::clean_data_suppliers\n");
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
template class vector<STDC::QMS::Citizen::Sensor_Data_Element *>;
template STDC::QMS::Citizen::Sensor_Data_Element ** fill_n<STDC::QMS::Citizen::Sensor_Data_Element **, unsigned int, STDC::QMS::Citizen::Sensor_Data_Element *>(STDC::QMS::Citizen::Sensor_Data_Element **, unsigned int, STDC::QMS::Citizen::Sensor_Data_Element * const &);
template void fill<STDC::QMS::Citizen::Sensor_Data_Element **, STDC::QMS::Citizen::Sensor_Data_Element *>(STDC::QMS::Citizen::Sensor_Data_Element **, STDC::QMS::Citizen::Sensor_Data_Element **, STDC::QMS::Citizen::Sensor_Data_Element * const &);
template class vector<STDC::QMS::Push_Supplier *> ;
template class vector<STDC::QMS::Push_Consumer *> ;
template STDC::QMS::Push_Supplier ** fill_n<STDC::QMS::Push_Supplier **, unsigned int, STDC::QMS::Push_Supplier *>(STDC::QMS::Push_Supplier **, unsigned int, STDC::QMS::Push_Supplier * const &);
template void fill<STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier *>(STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier * const &);
template STDC::QMS::Push_Consumer ** fill_n<STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer * const &);
template void fill<STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer * const &);

template class vector<char *>;
template char ** fill_n<char **, unsigned int, char *>(char **, unsigned int, char * const &);
template void fill<char **, char *>(char **, char **, char * const &);

template class map<std::string, probe_info *>;
#  if defined(__GNUC_MINOR__) && __GNUC_MINOR__ > 92
template class _Rb_tree<string, pair<string const, probe_info *>, _Select1st<pair<string const, probe_info *> >, less<string >, allocator<probe_info *> >;
#  else
template class rb_tree<string, pair<string const, probe_info *>, select1st<pair<string const, probe_info *> >, less<string>, __default_alloc_template<true, 0> >;
#  endif



#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate vector<STDC::QMS::Citizen::Sensor_Data_Element *>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

