//                              -*- Mode: C++ -*- 
// NT_Perf_Mon_getdata.h --- 
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

/** @file 
 *  @ingroup NTPerfMonProbe
 *  @brief Contains implementation of a Probe that delivers NT Performance Monitor data
 *
 * This probe contains an implementation of a probe that delivers Windows
 * NT performance monitor data. It can deliver any system counter that is
 * available on Windows NT.
 */



#ifndef NT_PERF_MON_GETDATA_H
#define NT_PERF_MON_GETDATA_H

#include "Debug.h"

#include <pdhmsg.h>
#include <pdh.h>
#include <psapi.h>

int getdata
      (char *,  char *);

#endif // NT_PERF_MON_GETDATA_H


