// Generic_OneShot_Probe.cpp
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


/** @file Generic_OneShot_Probe.cpp
 *  @ingroup Probes
 *  @brief Contains implementation of a One_Shot Probe 
 *
 */

#include <cstdio>
#include "ace/Get_Opt.h"

#include "Generic_OneShot_Probe.h"
#include "get_data_O.h"

/** @ingroup Probes */

/// RCS version
static const char* version = "$Id: Generic_OneShot_Probe.cpp,v 1.3 2001/10/21 08:54:06 srivasta Exp $";

/**
 * @brief Implementation of the common elements of a one shot probe
 * @param argc Count of command line arguments.
 * @param  argv List  of command line arguments.
 * @return returns the exit status of the program.
 *
 * Writing a one shot probe -- that is, a class of probes where the
 * probe has no state, and does not implement recurrring data
 * publication. Instead, for each request, the requested data is
 * provided, and the probe exits. Any periodic functionality is
 * provided by the Probe Proxy built into the sensor itself. 
 * 
 * This makes implementing the probe easy: we just need to perform
 * the following tasks:
 *  - Stores the Command line information into variables.
 *  - Calls the get_data function these variables.
 */

int 
main (int argc, char *argv[])
{
  /// The variables required to hold host1, host2 
  /// passed from the Child to Probe.
  char *host1 = 0, *host2 = 0;
  
  ACE_Get_Opt get_opts (argc, argv, "s:d:u");
  int c;

  // Handle Command line options
  while  ( (c = get_opts()) != EOF )
   {
     switch (c) {
	 case 's':
	   host1 = (ACE_OS::strdup (get_opts.optarg));
	   //fprintf(stderr,"\n The host1 is ->%d",host1);
	   break;
	 case 'd':
	   host2 = (ACE_OS::strdup (get_opts.optarg));
	   //fprintf(stderr,"\n The host2 is ->%d",host2);
	   break;
	 case '?':
	   fprintf(stderr,"\nGeneric_OneShot_Probe: You must specify ");
	   fprintf(stderr,"-s -d options\n\n");
	   fprintf(stderr,"Try `Generic_OneShot_Probe  -u' for more ");
	   fprintf(stderr,"information.\n\n");
	   exit(0);
	   break;
	 case 'u':
	   fprintf(stderr,"\n Generic_OneShot_Probe -s <src_host> ");
	   fprintf(stderr,"-d <destination_host> \n\n");
	   exit(0);
	   break;
     }
   }
  
  // This is where the majority of the work is done, and is the only
  // point of difference between different probes.   
  get_data(host1, host2 );
  exit(0);
}
