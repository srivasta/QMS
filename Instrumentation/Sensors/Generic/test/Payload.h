// test_client.cpp ---
// Author           : Shivakumar C. Patil (shivakumar.patil@stdc.com)


#ifndef _PAYLOAD_H
#define _PAYLOAD_H



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
 *  @brief  The server/probe specific parts of the client
 *
 * By separating out the code in these files, we make it easier to
 * create a client for a new probe type. 
 *
 * $Id: Payload.h,v 1.10 2001/12/17 19:41:52 nath Exp $
 */

#include <string>
#include "Parse_XML.h"

struct plotData
{
   //The resource value 
   string resource_value;

};

/// The data contained in the responses from the sensor
struct Payload_Data
{
  /// The response string
  string response;
  /// The sensor data id
  string data_id;
};

struct PerfMon_Payload_Data
{
  ///The resource name string
  string resource_name;
  /// The data id
  string data_id;
  struct plotData value;
};




/// The function that handles the parsding of the payload
extern bool payload_Handler(IDOM_Node *node_P, void * arg_p);

/// The function that prints a Payload_Data struct out
extern void payload_print(string QMSUniqueName_Host, struct Payload_Data & response_data);

/// The function that prints a PerfMon_Payload_Data struct out
extern void perfmon_payload_print(string QMSUniqueName_Host, struct PerfMon_Payload_Data & response_data);

/// Generate the payload for a message to the sensor
char * payload_generator(string &probe_schema_uri, const char *action);

/// Generate the payload for a message to the sensor
char * perfmon_payload_generator(string &probe_schema_uri, const char *action);

#endif /* _PAYLOAD_H */
