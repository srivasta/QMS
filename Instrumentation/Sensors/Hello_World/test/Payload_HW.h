/*                               -*- Mode: C -*- 
 * Payload.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Fri Oct 26 12:07:17 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Sun Oct 28 01:49:58 2001
 * Last Machine Used: ember.stdc.com
 * Update Count     : 5
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
 */

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
 *  @ingroup HelloWorld 
 *  @brief  The server/probe specific parts of the client
 *
 * By separating out the code in these files, we make it easier to
 * create a client for a new probe type. 
 *
 * $Id: Payload_HW.h,v 1.3 2001/12/02 03:30:25 srivasta Exp $
 */

#include <string>
#include "Parse_XML.h"

/// The data contained in the responses from the sensor
struct Payload_Data
{
  /// The response srting
  string salutation;
  /// The sensor data id
  string data_id;
};

/// The function that handles the parsding of the payload
extern bool payload_Handler(IDOM_Node *node_P, void * arg_p);
/// The function that prints a Payload_Data struct out
extern void payload_print(struct Payload_Data & response_data);
/// Generate the payload for a message to the sensor
char * payload_generator(string &probe_schema_uri, const char *action);

#endif /* _PAYLOAD_H_ */
