// NT_Command_Probe.h
// uthor           : Shivakumar C. Patil (shivakumar.patil@stdc.com)
// Description      :
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


#ifndef	NT_COMMAND_PROBE_H
#define NT_COMMAND_PROBE_H


/** @file NT_Command_Probe.h
 *  @ingroup GenericProbe
 *  @brief Contains implementation of Continuous Probe that delivers
 *  QMS Metrics. 
 */

/** @defgroup GenericProbe Generic Probes - simple probe to test Generic Sensor
 * @ingroup Continuous
 * This probe is a simple probe that generates a one line response and can
 * be readily used to test any Sensor.
 *
 */

#include <time.h>
#include <string>
using std::string;

/** @def LENGTH
 *  @brief The default length of the command in characters.
 */
#define LENGTH 80

/// Global variables :-(

/** @enum status_states
 * @brief This holds the state of the Continuous Probe.
 */
enum status_states {start_probe, stop_probe };

/** @var status
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
int listener (void *);

/** Function to set the flags depending on the commands received */
int setflags(string &, void *);

#endif /* NT_COMMAND_PROBE_H */
