//                              -*- Mode: C++ -*- 
// CallBack_Remos.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Tue Sep 18 01:20:47 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Dec  1 00:47:47 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 21
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
static const char* version = 
"$Id: CallBack_Remos.cpp,v 1.20 2001/12/09 02:14:17 nath Exp $";

/** @file 
 *  @ingroup RemosSensor 
 *  @brief  This file specifies the action taken when requests are recieved
 *
 *  $Id: CallBack_Remos.cpp,v 1.20 2001/12/09 02:14:17 nath Exp $
 */


#include "Remos_Sensor_Impl.h"

/// The structure that the query is packed into in order to spawn a thread
struct pack_args 
{
  /// A pointer ot a sensor object
  STDC::QMS::Citizen::Remos_Sensor_Impl *sensor_p;
  /// The query string of interest
  string query;
};

/**
 * @brief An function passed to a new thread to handle the incoming query
 * @param args_p A struct pack_args with the information required
 *
 * This function is needed since we need a global (or a static method)
 * to be passed to pthread_create. A non-method in this file was
 * deemed to be clearer rather than creating a static method that
 * would tend to get lost in all the other mehtods in the sensor
 * object. 
 */
void
do_query (void * args_p)
{
  QMS_Trace ("do_query", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: do_query\n");  

  struct pack_args *packed_p = (struct pack_args *)args_p;
  if(packed_p)
   {
     if(packed_p->sensor_p)
      {
	packed_p->sensor_p->handle_query(packed_p->query);
      } /* end of if(sensor_p) */
     delete packed_p;
     packed_p = 0;
   } /* end of if(packed_p) */
  else
   {
     std::cerr << "Error: null argument passed in to thread" << std::endl;
   } /* end of else */
  
  DEBUG0(6, "DEBUG: Finished Handling Query\n");  
}

/**
 * @brief The callback function registered woth all the Push Consumers
 * @param query The incoming query that we are handling
 * @param arg_p A pointer to a sensor object cast to void *
 *
 * We just spawn a thread and pass in the incoming query, and a
 * pointer to the global sensor object, and allow the query to be
 * handled in the context of the sensor. This function is needed since
 * a method can not be registered as a Push Consumer callback method.
 *
 * We choose to spawn a new thread instead of continuing to operate in
 * the thread created by the ORB since handling the query can be a
 * long operation, espescially for Continous Probes.
 *
 * For scalability purposes, this should probably use a thread pool,
 * and not spawn off a thread per request.
 */
void
CallBack (const string &query, void *arg_p)
{
  QMS_Trace ("CallBack", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: CallBack\n");
  
  struct pack_args  *packed_p = new pack_args;
  packed_p->sensor_p = (STDC::QMS::Citizen::Remos_Sensor_Impl *) arg_p;
  packed_p->query    = query;
  
  int ret = ACE_Thread::spawn((ACE_THR_FUNC)do_query,
 			      (void *)packed_p,  // arg
 			      THR_JOINABLE, // flags
 			      0,  // t_id
 			      0,  // t_handle
 			      ACE_DEFAULT_THREAD_PRIORITY,
 			      0,  // stack
 			      0,  // stack_size
 			      0   // thread_adapter
 			      );
  if(ret == -1)
   {
     ACE_OS::perror ("Thread Cretion failed\n");
   } /* end of if(ret == -1) */
  DEBUG0(4, "DEBUG: Created thread to handle query\n");
}

