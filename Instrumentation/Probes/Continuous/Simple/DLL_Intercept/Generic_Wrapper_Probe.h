// Generic_Wrapper_Probe.h
// Author      : Shivakumar C. Patil (shivakumar.patil@stdc.com)
// Description : 
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

/** @defgroup DLLInterceptProbe DLL Intercept Probe - probes for transparent insrumentation 
 * @ingroup Continuous
 * This probe performs transparent instrumentation of any Windows NT system
 * DLL to gather any desired data.
 *
 */

/** @file
 *  @ingroup DLLInterceptProbe
 *  @brief Contains implementation of DLL Intercept Probe that delivers
 *  transparent instrumentation of DLL's on Windows NT
 */


#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include <windows.h>
#include <wrappers.h>
#include <tchar.h>
#include <signal.h>

#include <string>
#include <iostream>

using namespace std;

#include "ace/OS.h"   
#include "ace/Log_Msg.h"
#include "ace/Thread_Manager.h"
#include "ace/Synch.h"

#define LENGTH	1024
enum status_states { start_probe, stop_probe };
static status_states status;
