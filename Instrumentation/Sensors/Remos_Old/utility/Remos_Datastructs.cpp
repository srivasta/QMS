//                              -*- Mode: C++ -*-
// Remos_Datastructs.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Thu Oct 26 09:35:52 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Jan 14 21:39:45 2001
// Last Machine Used: ember
// Update Count     : 12
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: Remos_Datastructs.cpp,v 1.6 2001/10/21 08:54:10 srivasta Exp $
//
/** @file Remos_Datastructs.cpp
 *  @ingroup Remos
 *  @brief Implentation of the Remos datastructs class.
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


#include "Remos_Datastructs.h"
#include "QMS_Debug.h"
/**
 *  @param query_p The query data structure to print
 *  @brief Prints the contents of a Remos query on to standard output
 */
void
print_query(const Query_struct *query_p)
{
  QMS_Trace ("print_query", __LINE__, __FILE__);
  cout << "Request ID   = "  << query_p->request_id   << endl
       << "Repeat Count = "  << query_p->repeat_count  << endl
       << "Refresh Rate = "  << query_p->refresh_rate  << endl
    ;
  if (query_p->type == Query_struct::link)
   {
     cout << "Type      = Link"  << endl;
   }
  else
   {
     cout << "Type      = Flow"  << endl;
   }
#if 0
  vector < string >::const_iterator ptr;
  for (ptr = query_p->host_names.begin(); ptr != query_p->host_names.end();
       ptr++)
   {
     cout << "Hostname" << ptr << endl;
   }
#endif // 0
  cout << "Hostnames " << query_p->host_names << endl;
}

/**
 *  @param query_p The Remos Data structure to print
 *  @brief Prints the contents of a Remos data packet on to standard output
 */
void
print_data(const Data_struct *query_p)
{
  QMS_Trace ("print_data", __LINE__, __FILE__);
  cout << "Request ID          = " << query_p->request_id    << endl
       << "Data ID             = " << query_p->data_id       << endl
       << "Refresh Rate        = " << query_p->refresh_rate  << endl
       << "Latency             = " << query_p->latency       << endl
       << "Available Bandwidth = " << query_p->available_bandwidth  << endl
       << "Maximum Bandwidth   = " << query_p->maximum_bandwidth    << endl
   ;
  if (query_p->type == Data_struct::link)
   {
     cout << "Type      = Link"  << endl;
   }
  else
   {
     cout << "Type      = Flow"  << endl;
   }

  cout << "Source              = "  << query_p->source       << endl
       << "Destination         = "  << query_p->destination       << endl
    ;
}

