//                              -*- Mode: C++ -*-
// QMS_Remos_Msg.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Oct 18 17:38:28 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Jan 14 21:38:22 2001
// Last Machine Used: ember
// Update Count     : 220
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
//
//
/** @file QMS_Remos_Msg.cpp
 *  @ingroup Remos
 *  @brief Implentation of the QMS Remose message class
 *
 *  This is the main implementation for the class.
 */

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




#include "QMS_Remos_Msg.h"
#include <string>
#include "ace/OS.h"		// For the LM_DEBUG macros
#include "ace/Log_Msg.h"

#include "QMS_Debug.h"
/** @var long QMS_Remos_Msg::sequence_no
 * This static variable holds a monotonically increasing sequence
 * number incrementred each time a new message is created in this
 * process.
 */
long QMS_Remos_Msg::sequence_no = 0;


/// Constructor
QMS_Remos_Msg::QMS_Remos_Msg(void)
{
  QMS_Trace ("QMS_Remos_Msg::QMS_Remos_Msg", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: New message created\n");
  this->data.erase();
}


/**
 *  @brief Returns the size of the message
 *  @return size of the message
 *
 */
size_t
QMS_Remos_Msg::size(void)
{
  QMS_Trace ("QMS_Remos_Msg::size", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Message size\n");
  ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  {
    return this->data.length();
  }
}

/**
 *  @brief Erase the contents of the message
 */
void
QMS_Remos_Msg::erase(void)
{
  QMS_Trace ("QMS_Remos_Msg::erase", __LINE__, __FILE__);
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  {
    this->data.erase();
  }
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Message erased\n");
}

/**
 *  @brief Convert the string into a char array
 *  @return The contents as a char array
 */
const char *
QMS_Remos_Msg::as_string(void)
{
  QMS_Trace ("QMS_Remos_Msg::as_string", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Message as string\n");
  ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  {
    char * tmp_p = (char *)this->data.data();
    tmp_p[this->data.length()] = 0;

    return tmp_p;
  }
}

/**
 *  @param data_p The string to append
 *  @brief append a character string to the contents
 */
void
QMS_Remos_Msg::append(const char *data_p)
{
  QMS_Trace ("QMS_Remos_Msg::append", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: text appended into message\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  {
    this->data.append(data_p);
  }
}

/**
 *  @data The query struct to insert
 *  @brief Insert a struct Query_struct into the message
 *
 *  We convert to XML on the fly
 */
void
QMS_Remos_Msg::insert(const struct Query_struct &data)
{
  QMS_Trace ("QMS_Remos_Msg::insert", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Query inserted into message\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  {
    char temp[MAXNAMELEN];
    time_t now = 0;
    struct tm *now_p = 0;

#if defined (_WIN32) /* Windows only has ftime */
    struct timeb tb;
    ftime(&tb);
    now = (time_t) tb.time;
#else
    struct timeval tv;
    gettimeofday(&tv, 0);
    now = (time_t) tv.tv_sec;     /* time_t now = time (0); */
#endif

    now_p = ACE_OS::gmtime(&now);


    char hostname[ MAXNAMELEN ];
    ACE_OS::hostname( hostname, MAXNAMELEN );

    this->data.erase();
    if (this->data.length() != 0)
     {
       DEBUG0 (DEBUG_L_ERROR, "data has things in it after erasure\n");
     }

    this->data = "<?xml version=\"1.0\" ?>\n";
    this->data.append("<!DOCTYPE QMS_Event PUBLIC \"-//STDC//QMS Event//EN//XML\" \"QMS_Event.dtd\">\n");
    this->data.append("<QMS_Event>\n");
    this->data.append("  <SequenceNo>");
    int ret = sprintf(temp, "%ld", this->sequence_no++);
    // really should look at the return value
    this->data.append(temp);
    this->data.append("</SequenceNo>\n");
    this->data.append("  <SenderID>");
    this->data.append(hostname);
    this->data.append("</SenderID>\n");
    this->data.append("  <EventDate>");
    ret = sprintf(temp, "%d/%d/%d", now_p->tm_mon + 1, now_p->tm_mday,
		  1900 + now_p->tm_year);
    // really should look at the return value
    this->data.append(temp);
    this->data.append("</EventDate>\n");
    this->data.append("  <EventTime>");
    ret = sprintf(temp, "%d:%d:%f", now_p->tm_hour, now_p->tm_min,
#if defined (_WIN32) /* Windows only has ftime */
		  (double)now_p->tm_sec + ((double)tb.millitm / 1000 ));
#else
		  (double)now_p->tm_sec + ((double)tv.tv_usec / 1000000 ));
#endif
    // really should look at the return value
    this->data.append(temp);
    this->data.append("</EventTime>\n");
    this->data.append("  <EventType>");
    if (data.type == Query_struct::link){
      this->data.append("Remos Bandwidth Query type link");
    }
    else {
      this->data.append("Remos Bandwidth Query type flow");
    }
   this->data.append("</EventType>\n");
    this->data.append("  <EventData>\n");

    this->data.append("    <bandwidth_request linktype=\"");
    if (data.type == Query_struct::link){
      this->data.append("link");
    }
    else {
      this->data.append("flow");
    }
    this->data.append("\">\n");

    this->data.append("        <requestid>");
    ret = sprintf(temp, "%d", data.request_id);
    // really should look at the return value
    this->data.append(temp);
    this->data.append("</requestid>\n");

#if 0
    // Iterate over hostnames
    vector<string>::const_iterator hosts;
    for (hosts = data.host_names.begin(); hosts != data.host_names.end();
	 ++hosts)
     {
       this->data.append("        <hostname>");
       this->data.append(*hosts);
       this->data.append("</hostname>\n");
     }
#endif // 0
    if (!data.host_names.empty())
     {
       bool done = false;
       size_t location = 0;
       size_t start = 0;
       size_t stop = data.host_names.length();
       while (done == false)
	{

	  location = data.host_names.find(",",start);
	  if (location == string::npos)
	   {
	     this->data.append("        <hostname>");
	     this->data.append(data.host_names.substr(start,
						      data.host_names.length() - 1));
	     this->data.append("</hostname>\n");
	     done = true;
	   }
	  else
	   {
	     stop = location;
	     this->data.append("        <hostname>");
	     this->data.append(data.host_names.substr(start, stop - start));
	     this->data.append("</hostname>\n");
	     start = location +1;
	   }
	}
     }

    if (data.refresh_rate){
      this->data.append("        <refreshrate>");
      ret = sprintf (temp, "%f", data.refresh_rate);
      // test ret?
      this->data.append(temp);
      this->data.append("</refreshrate>\n");
    }
    if (data.repeat_count){
      this->data.append("        <repeatcount>");
      ret = sprintf (temp, "%d", data.repeat_count);
      this->data.append(temp);
      this->data.append("</repeatcount>\n");
    }
    this->data.append("  </bandwidth_request>\n");
    this->data.append("  </EventData>\n");
    this->data.append("</QMS_Event>\n");
  }
}


/**
 *  @param data The data to insert
 *  @brief Insert a struct Data_struct into the message
 *
 *  We convert to XML on the fly
 */
void
QMS_Remos_Msg::insert(const struct Data_struct &data)
{
  QMS_Trace ("QMS_Remos_Msg::insert", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: inserting Data into message\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  {

    char temp[MAXNAMELEN];
    time_t now = 0;
    struct tm *now_p = 0;

#if defined (_WIN32) /* Windows only has ftime */
    struct timeb tb;
    ftime(&tb);
    now = (time_t) tb.time;
#else
    struct timeval tv;
    gettimeofday(&tv, 0);
    now = (time_t) tv.tv_sec;     /* time_t now = time (0); */
#endif

    now_p = ACE_OS::gmtime(&now);

    char hostname[ MAXNAMELEN ];
    ACE_OS::hostname( hostname, MAXNAMELEN );

    this->data.erase();
    this->data = "<?xml version=\"1.0\" ?>\n";
    this->data.append("<!DOCTYPE QMS_Event PUBLIC \"-//STDC//QMS Event//EN//XML\" \"QMS_Event.dtd\">\n");
    this->data.append("<QMS_Event>\n");
    this->data.append("<SequenceNo>");
    int ret = sprintf(temp, "%ld", this->sequence_no++);
    // really should look at the return value
    this->data.append(temp);
    this->data.append("</SequenceNo>\n");
    this->data.append("<SenderID>");
    this->data.append(hostname);
    this->data.append("</SenderID>\n");
    this->data.append("<EventDate>");
    ret = sprintf(temp, "%d/%d/%d", 1 + now_p->tm_mon, now_p->tm_mday,
		      1900 + now_p->tm_year);
    // really should look at the return value
    this->data.append(temp);
    this->data.append("</EventDate>\n");
    this->data.append("<EventTime>");
    ret = sprintf(temp, "%d:%d:%f", now_p->tm_hour, now_p->tm_min,
#if defined (_WIN32) /* Windows only has ftime */
		  (double)now_p->tm_sec + ((double)tb.millitm / 1000 ));
#else
		  (double)now_p->tm_sec + ((double)tv.tv_usec / 1000000 ));
#endif

    // really should look at the return value
    this->data.append(temp);
    this->data.append("</EventTime>\n");
    this->data.append("<EventType>");
    if (data.type == Data_struct::link){
      this->data.append("Remos Bandwidth data type link");
    }
    else {
      this->data.append("Remos Bandwidth data type flow");
    }
    this->data.append("</EventType>\n");
    this->data.append("  <EventData>\n");

    this->data.append("    <bandwidth_data linktype=\"");
    if (data.type == Data_struct::link){
      this->data.append("link");
    }
    else {
      this->data.append("flow");
    }
    this->data.append("\">\n");


    this->data.append("          <requestid>");
    ret = sprintf(temp, "%d", data.request_id);
    // really should look at the return value
    this->data.append(temp);
    this->data.append("</requestid>\n");

    this->data.append("          <dataid>");
    ret = sprintf(temp, "%d", data.data_id);
    // really should look at the return value
    this->data.append(temp);
    this->data.append("</dataid>\n");

    this->data.append("          <source>");
    this->data.append(data.source);
    this->data.append("</source>\n");
    this->data.append("          <destination>");
    this->data.append(data.destination);
    this->data.append("</destination>\n");

    this->data.append("          <latency>");
    ret = sprintf (temp, "%f", data.latency);
    this->data.append(temp);
    this->data.append("</latency>\n");

    this->data.append("          <available>");
    ret = sprintf (temp, "%f", data.available_bandwidth);
    this->data.append(temp);
    this->data.append("</available>\n");

    if (data.maximum_bandwidth){
      this->data.append("          <maximum>");
      ret = sprintf (temp, "%f", data.maximum_bandwidth);
      this->data.append(temp);
      this->data.append("</maximum>\n");
    }

    this->data.append("            <collectrate>");
    ret = sprintf (temp, "%f", data.refresh_rate);
    this->data.append(temp);
    this->data.append("</collectrate>\n");

    this->data.append("    </bandwidth_data>\n");
    this->data.append("  </EventData>\n");
    this->data.append("</QMS_Event>\n");
  }
}


/**
 *  @param The string data to insert
 *  @brief Insert a string into the message
 */
void
QMS_Remos_Msg::insert(const string &data)
{
  QMS_Trace ("QMS_Remos_Msg::insert", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: String inserted into message\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  {
	  this->data = data;
  }
}




/**
 *  @brief Extract message contents into a struct Query_struct
 *
 *  We parse the XML contents on the fly, and cast the contents
 *  appropriately into struct members
 */
struct Query_struct *
QMS_Remos_Msg::extract_query(void)
{
  QMS_Trace ("QMS_Remos_Msg::extract_query", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Query extracted from message message\n");
  //ADDED THE struct followed by new
  struct Query_struct *result_p = new struct Query_struct;
  ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  {
    ACE_DECLARE_NEW_CORBA_ENV;

    size_t location = 0;
    size_t start = 0;
    size_t stop = 0;

#if 0
    location = this->data.find("<SequenceNo>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }

    location += strlen("<SequenceNo>");		// skip over tag
    start = location;		// start of data
    location = this->data.find("</SequenceNo>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }

    stop = location;
    location += strlen("</SequenceNo>");
#endif // 0

    // look for <EventData>
    location = this->data.find("<EventData>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<EventData>");		// skip over tag
    // Now we should have a request
    location = this->data.find("<bandwidth_request", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<bandwidth_request"); // skip over tag
    if (this->data.substr(location, 1) == " ")
     {
       // we have a link type
       location = this->data.find("linktype=\"", location);
       location += strlen("linktype=\""); //
       start = location;
       location = this->data.find("\">", location);
       stop=location;
       location = this->data.find("link", start);
       if (location < stop)
	{
	  result_p->type = Query_struct::link;
	}
       else
	{
	  location = this->data.find("flow", start);
	  if (location < stop)
	   {
	     result_p->type = Query_struct::flow;
	   }
	  else
	   {
	     ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
	   }
	}
     }
    else
     {
       result_p->type =  Query_struct::flow;
     }
    location = start;

    location = this->data.find("<requestid>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<requestid>");
    start = location;

    location = this->data.find("</requestid>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    stop = location;

    // stuff added to make sure we are getting this data on NT side
    string x;
    x.assign( (this->data.substr(start, stop - start)).data() );
    int len = stop - start;
    char *temp_p = new char[len +1];
    x.copy(temp_p, len, 0);
    temp_p[len] = 0;

    result_p->request_id =  atoi(temp_p);
    delete temp_p;

    location += strlen("</requestid>");

    // loop over the hostnames
    start = location;		// save location
    // test whether we have a hostname
    location = this->data.find("<hostname>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location = start;		// test succeeded, restart

    while ((location = this->data.find("<hostname>", location))
	   != string::npos)
    {
      location +=  strlen("<hostname>");
      start = location;
      location = this->data.find("</hostname>", location);
      if (location == string::npos)
       {
	 ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
       }
      stop = location;
      if (result_p->host_names.length())
       {
	 result_p->host_names.append(",");
       }
      result_p->host_names.append(this->data.substr(start, stop - start));
      location += strlen("</hostname>");
    }
    stop = strlen("</hostname>");

    location = stop;

    location = this->data.find("<refreshrate>", stop);
    if (location != string::npos)
     {
       location += strlen("<refreshrate>");
       start = location;
       location = this->data.find("</refreshrate>", location);
       if (location == string::npos)
	{
	  ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
	}
       stop = location;

       // stuff added to make sure we are getting this data on NT side
       x.assign( (this->data.substr(start, stop - start)).data() );
       len = stop - start;
       temp_p = new char[len +1];
       x.copy(temp_p, len, 0);
       temp_p[len] = 0;
       result_p->refresh_rate =	 atof(temp_p);
       delete temp_p;

       location += strlen("</refreshrate>");
     }
    else
     {
       location = stop;
     }


    location = this->data.find("<repeatcount>", location);
    if (location != string::npos)
     {
       location += strlen("<repeatcount>");
       start = location;
       location = this->data.find("</repeatcount>", location);
       if (location == string::npos)
	{
	  ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
	}
       stop = location;


       // stuff added to make sure we are getting this data on NT side
       x.assign( (this->data.substr(start, stop - start)).data() );
       len = stop - start;
       temp_p = new char[len +1];
       x.copy(temp_p, len, 0);
       temp_p[len] = 0;
       result_p->repeat_count =	 atoi(temp_p);
       delete temp_p;

       location += strlen("</repeatcount>");
     }

    return result_p;
  }
}

// added the struct in the definitation
/**
 *  @brief Extract message contents into a struct Data_struct
 *
 *  We parse the XML contents on the fly, and cast the contents
 *  appropriately into struct members
 */
struct Data_struct *
QMS_Remos_Msg::extract_data(void)
{
  QMS_Trace ("QMS_Remos_Msg::extract_data", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: extracting Data from message message\n");
  //added struct followd by new
  struct Data_struct  *result_p = new struct Data_struct;
  ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
  {
    ACE_DECLARE_NEW_CORBA_ENV;

    size_t location = 0;
    size_t start = 0;
    size_t stop = 0;
#if 0
    location = this->data.find("<RequestID>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }

    location += strlen("<RequestID>");		// skip over tag
    start = location;		// start of data
    location = this->data.find("</RequestID>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }

    stop = location;

    string x;
    x.assign( (this->data.substr(start, stop - start)).data() );
    int len = stop - start;
    char *temp_p = new char[len +1];
    x.copy(temp_p, len, 0);
    temp_p[len] = 0;

    result_p->request_id =  atoi(temp_p);
    delete temp_p;


    location += strlen("</RequestID>");

     location = this->data.find("<SequenceNo>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }

    location += strlen("<SequenceNo>");		// skip over tag
    start = location;		// start of data
    location = this->data.find("</SequenceNo>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }

    stop = location;

    string x;
    x.assign( (this->data.substr(start, stop - start)).data() );
    int len = stop - start;
    char *temp_p = new char[len +1];
    x.copy(temp_p, len, 0);
    temp_p[len] = 0;

    result_p->data_id =  atoi(temp_p);
    delete temp_p;


    location += strlen("</SequenceNo>");
#endif // 0

   // look for <EventData>
    location = this->data.find("<EventData>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<EventData>");		// skip over tag

    // Now we should have a request
    location = this->data.find("<bandwidth_data", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }

	//location += strlen("<bandwidth_data"); // skip over tag

	//changed the bandwidt_data to bandwidth

	location += strlen("<bandwidth_data"); // skip over tag
    if (this->data.substr(location, 1) == " ")
     {
       // we have a link type
       location = this->data.find("linktype=\"", location);
       location += strlen("linktype=\""); //
       start = location;
       location = this->data.find("\">", location);
       stop=location;
       location = this->data.find("link", start);
       if (location < stop)
	{
	  result_p->type = Data_struct::link;
	}
       else
	{
	  location = this->data.find("flow", start);
	  if (location < stop)
	   {
	     result_p->type = Data_struct::flow;
	   }
	  else
	   {
	     ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
	   }
	}
     }
    else
     {
       result_p->type =  Data_struct::flow;
     }
    location = this->data.find("<requestid>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<requestid>");		// skip over tag
    start = location;
    location = this->data.find("</requestid>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    stop = location;

    // stuff added to make sure we are getting this data on NT side
    string x;
    x.assign( (this->data.substr(start, stop - start)).data() );
    int len = stop - start;
    char *temp_p = new char[len +1];
    x.copy(temp_p, len, 0);
    temp_p[len] = 0;
    result_p->request_id =	 atoi(temp_p);
    delete temp_p;

    location += strlen("</requestid>");		// skip over tag


    location = this->data.find("<dataid>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<dataid>");		// skip over tag
    start = location;
    location = this->data.find("</dataid>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    stop = location;

    // stuff added to make sure we are getting this data on NT side
    x.assign( (this->data.substr(start, stop - start)).data() );
    len = stop - start;
    temp_p = new char[len +1];
    x.copy(temp_p, len, 0);
    temp_p[len] = 0;
    result_p->data_id =	 atoi(temp_p);
    delete temp_p;

    location += strlen("</dataid>");		// skip over tag


    location = this->data.find("<source>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<source>");		// skip over tag
    start = location;
    location = this->data.find("</source>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    stop = location;
    result_p->source = this->data.substr(start, stop - start);
    location += strlen("</source>");		// skip over tag


    location = this->data.find("<destination>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<destination>");		// skip over tag
    start = location;
    location = this->data.find("</destination>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    stop = location;
    result_p->destination = this->data.substr(start, stop - start);
    location += strlen("</destination>");		// skip over tag

    location = this->data.find("<latency>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<latency>");
    start = location;
    location = this->data.find("</latency>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    stop = location;

    //temp_p = (char *)this->data.substr(start, stop - start).data();
    //temp_p[this->data.substr(start, stop - start).length()] = 0;



    // stuff added to make sure we are getting this data on NT side
    x.assign( (this->data.substr(start, stop - start)).data() );
    len = stop - start;
    temp_p = new char[len +1];
    x.copy(temp_p, len, 0);
    temp_p[len] = 0;
    result_p->latency =	 atof(temp_p);
    delete temp_p;

    location += strlen("</latency>");

    location = this->data.find("<available>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<available>");
    start = location;
    location = this->data.find("</available>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    stop = location;

    //temp_p = (char *)this->data.substr(start, stop - start).data();
    //temp_p[this->data.substr(start, stop - start).length()] = 0;


    // stuff added to make sure we are getting this data on NT side
    x.assign( (this->data.substr(start, stop - start)).data() );
    len = stop - start;
    temp_p = new char[len +1];
    x.copy(temp_p, len, 0);
    temp_p[len] = 0;
    result_p->available_bandwidth =	 atof(temp_p);
    delete temp_p;

    location += strlen("</available>");


    location = this->data.find("<maximum>", location);
    if (location != string::npos)
     {
       location += strlen("<maximum>");
       start = location;
       location = this->data.find("</maximum>", location);
       if (location == string::npos)
	{
	  ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
	}
       stop = location;

      // temp_p = (char *)this->data.substr(start, stop - start).data();
       //temp_p[this->data.substr(start, stop - start).length()] = 0;


      // stuff added to make sure we are getting this data on NT side
       x.assign( (this->data.substr(start, stop - start)).data() );
       len = stop - start;
       temp_p = new char[len +1];
       x.copy(temp_p, len, 0);
       temp_p[len] = 0;
       result_p->maximum_bandwidth =	 atof(temp_p);
       delete temp_p;

       location += strlen("</maximum>");
     }


    location = this->data.find("<collectrate>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    location += strlen("<collectrate>");
    start = location;
    location = this->data.find("</collectrate>", location);
    if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
    stop = location;

    //temp_p = (char *)this->data.substr(start, stop - start).data();
    //temp_p[this->data.substr(start, stop - start).length()] = 0;

    // stuff added to make sure we are getting this data on NT side
    x.assign( (this->data.substr(start, stop - start)).data() );
    len = stop - start;
    temp_p = new char[len +1];
    x.copy(temp_p, len, 0);
    temp_p[len] = 0;
    result_p->refresh_rate =	 atof(temp_p);
    delete temp_p;

    location += strlen("</collectrate>");

    return result_p;

  }
}

// template class vector<basic_string<char, string_char_traits<char>, __default_alloc_template<false, 0> >, allocator<basic_string<char, string_char_traits<char>, __default_alloc_template<false, 0> > > >;
