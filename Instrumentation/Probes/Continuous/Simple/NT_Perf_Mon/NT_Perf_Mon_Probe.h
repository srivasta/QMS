//                              -*- Mode: C++ -*- 
// NT_Perf_Mon_Probe.h --- 
// Author           : Shivakumar Patil and Bhanu Hosangadi.
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



#ifndef	NT_PERF_MON_PROBE_H
#define NT_PERF_MON_PROBE_H



/** @file NT_Perf_Mon_Probe.h
 *  @ingroup NTPerfMonProbe
 *  @brief Contains implementation Probe that delivers NT performance data
 *  
 */

/** @defgroup NTPerfMonProbe Windows NT Performance Monitor Probes 
 * @ingroup Continuous
 *
 * This probe delivers Windows NT system and performance monitor QoS metrics
 * data. Any system counter is avilable.
 */


/** @def LENGTH
 *  @brief The default length of the command in characters.
 */

#include <time.h>
#include <string>
using std::string;

#define LENGTH 1024

/// Global variables :-(

/** @enum status_states
 * @brief This holds the state of the Continuous Probe.
 */
enum status_states {start_probe, pause_probe, stop_probe, 
                    read_repetitions, read_repeatInterval };

/** 
 * @brief Variable of type enum, for holding the Probe's state.
 */
static enum status_states status;

/** @var TD_asset_guard
 * @brief Set a mutex to guard the data.
 */
ACE_Thread_Mutex TD_asset_guard;

/// default values for global variables.
int repeat_count = 1;
struct timespec refresh_rate;

/** Function associated with the Worker thread. */
void worker(void *);

/** Function associated with the listener thread. */
int listener (void);

/** Function to set the flags depending on the commands received */
int setflags(string &, void *);

#endif /* NT_PERF_MON_PROBE_H */
