// get_data_GCP.h
// Author           : Shivakumar C. Patil (shivakumar.patil@stdc.com)
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


#ifndef GET_DATA_GCP_H
#define GET_DATA_GCP_H

#include "Instrumentation.h"


/** @file get_data_GCP.h
 *  @ingroup GenericProbe
 *  @brief Implementation of a one shot probe for Remos data
 *
 *  This file defines the data structures and the method invoked to
 *  get data from the Remos system.  This file is for a continuous
 *  probe -- This is a more sophisticated probe that operates
 *  continuously, maintaining state in between data pulses.  This
 *  probe implements its own periodic behavior, and only requires a
 *  rate setting to periodically pump out data.
 */

/** Resonsible for getting Metrics information */
char *get_data (void *);

#endif /* GET_DATA_GCP_H */
