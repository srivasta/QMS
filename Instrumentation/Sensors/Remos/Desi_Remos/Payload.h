//Payload.h
// Author           : Shivakumar C. Patil (shivakumar.patil@stdc.com)


#ifndef _PAYLOAD_H_
#define _PAYLOAD_H_



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
 *  @ingroup RemosSensor 
 *  @brief  The server/probe specific parts of the client
 *
 * By separating out the code in these files, we make it easier to
 * create a client for a new probe type. 
 *
 * $Id: Payload.h,v 1.2 2001/12/11 00:23:49 spatil Exp $
 */

#include <string>
#include <list>
#include "Parse_XML.h"

struct linkData
{
    string dataID;
    string source;
    string destination;
    string latency;
    string available;
    string maximum;
};

struct bandwidthData
{
   struct linkData linkdata;
};


struct RemosData
{
   vector<bandwidthData *> bandwidth_data;
};

struct Payload_Data
{
   struct RemosData remos_data;
};


/// The function that handles the parsding of the payload
extern bool payload_Handler(IDOM_Node *node_P, void * arg_p);
/// The function that prints a Payload_Data struct out
extern void payload_print(struct Payload_Data & response_data);
/// Generate the payload for a message to the sensor
char * payload_generator(string &probe_schema_uri, list<string> & hosts, const char *action);

///Cleaning vector of bandwidthData pointers .
extern void payload_clean(struct Payload_Data &);


#endif /* _PAYLOAD_H_ */
