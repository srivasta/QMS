//                              -*- Mode: C++ -*-
// Remos_Datastructs.h ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Oct 18 14:58:14 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu May  3 16:47:49 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 65
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: Remos_Datastructs.h,v 1.9 2001/10/21 08:54:10 srivasta Exp $
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


#ifndef DATASTRUCTS_H
#define  DATASTRUCTS_H
/** @file Remos_Datastructs.h
 *  @ingroup Remos
 *  @brief Interface definition of the Remos data structures class.
 */

#include <string>
#include <vector>
#include "orbsvcs/CosNamingC.h"
#include "orbsvcs/Event_Utilities.h"

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

using namespace std;

/// The Remos query event type
static const RtecEventComm::EventType
QMS_Remos_Query =  ACE_ES_EVENT_UNDEFINED  + 2300;

/// The Remos data event type
static const RtecEventComm::EventType
QMS_Remos_Data =  ACE_ES_EVENT_UNDEFINED  + 2400;

/// The supplier ID of the entity making Remos queries
static const RtecEventComm::EventSourceID
Query_Supplier =  ACE_ES_EVENT_SOURCE_ANY + 2300;

// The supplier ID of the enntity providing the Remos Data
static const RtecEventComm::EventSourceID
    Data_Supplier = ACE_ES_EVENT_SOURCE_ANY + 2400;

/** @struct Query_struct
 * @ingroup Remos
 * @brief The structure of a Remos Query
 *
 * This data structure encapslates the information that one may need
 * to convey to Remos to have it generate the network data
 * required. Please note that both flow and graph versions of the
 * queries are supported.
 */
struct Query_struct {
  /// The request ID
  int request_id;

  /// How many responses are requested
  int repeat_count;

  /// Refresh rate in seconds
  double refresh_rate;

  /**
   *  The type Information types
   *  The request type can be either a flow or link
   */
  enum link_type {link, flow} type;

  ///  host names  include domains
  string host_names;
  /* This is a problem with ACE, so we change host names from a vector
   * to a comma separated string
   */
  //vector< string > host_names;

};

/** @struct Data_struct
 * @ingroup Remos
 * @brief The structure of the Remos Data
 *
 * This data structure encapslates the information that may be
 * returned by Remos. Please note that both flow and graph versions of
 * the queries are supported.
 */
struct Data_struct {
  /// The request ID
  int request_id;

  /// The ID of this data response
  int data_id;

  /// Refresh rate requested (in seconds)
  double refresh_rate;

  ///  latency in seconds
  double latency;

  ///  available bandwidth in bps
  double available_bandwidth;

  /// maximum bandwidth in bps
  double maximum_bandwidth;

  /**
   *  The type of information requested
   *  The request type can be either a flow or link
   */
  enum link_type {link, flow} type;

  /// Link source node
  string source;

  /// Link destination node
  string destination;
};

/// Print a Remos Query to the standard ourput
Dllexport void print_query(const Query_struct *query_p);

/// Print a Remos Data object to the standard ourput
Dllexport void print_data(const Data_struct *query_p);

#endif //  DATASTRUCTS_H
