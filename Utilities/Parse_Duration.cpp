//                              -*- Mode: C++ -*- 
// Parse_Duration.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
// Created On       : Wed Dec  5 18:25:20 2001
// Created On Node  : glaurung.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Dec  5 23:21:35 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 36
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
 *  @ingroup Utilities
 *  @brief A convenient interface to parsing QMS XML durations
 *
 * $Id: Parse_Duration.cpp,v 1.3 2001/12/12 22:35:08 spatil Exp $
 */

/// RCS version string



#include <time.h>
#include <string>
#include "Debug.h"

namespace STDC 
{
  namespace QMS 
  {

struct timespec
duration_to_tv(const char * duration_p)
{
  QMS_Trace ("STDC::QMS::duration_to_tv", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::duration_to_tv\n");

  struct timespec value;
  value.tv_nsec = 0;
  value.tv_sec  = 0;

  char number[100];
  char *start = const_cast< char * >(duration_p);
  char *end   = const_cast< char * >(duration_p); 

  if(*start == 'P')
   {
     // We have the required designator
     bool seen_secs = false;
     bool seen_T    = false;
     start++;
     if(*start && *start == 'T')
      {
	start++;
	seen_T    = true;
      } /* end of if(*start == 'T') */
     
     while(*start)
      {
	if(seen_T && *start == '.')
	 {
	   start++;
	   seen_secs = true;
	 } /* end of if(seen_T && *start == '.') */
	
	end = start;
	while(isdigit((int) *end))
	 {
	   end++;	   
	 } /* end of if(isdigit((int) *end)) */
	if(end <= start)
	 {
	   break;
	 } /* end of if(end > start) */
	
	strncpy(number, start, end - start);
	number[end - start] = 0;
	int val = atol(number);
	switch(*end)
	 {
	     case 'Y':
	       value.tv_sec  += (time_t) (val * 365.25 * 86400);
	       break;
	       
	     case 'M':
	       if(seen_T)
		{
		  value.tv_sec  += val * 60;
		} /* end of if(seen_T) */
	       else
		{
		  value.tv_sec  += val * 30  * 86400;
		} /* end of else */
	       break;
	       
	     case 'D':
	       value.tv_sec  += val * 86400;
	       break;
	     
	     case 'H':
	       value.tv_sec  += val * 3600;
	       break;
	     
	     case '.':
	       value.tv_sec  += val;
	       seen_secs=true;
	       break;
	       
	     case 'S':
	       if(seen_secs)
		{
		  strncpy(number, start -1, end - start + 1);
		  number[end - start + 1] = 0;
		  double frac = atof(number);
		  value.tv_nsec = (long int) (frac * 1000000000);
		} /* end of if(seen_secs) */
	       else
		{
		  value.tv_sec  += val;
		} /* end of else */
	       break;
	       
	       
	     default:
	       
	       break;
	 } /* end of switch(*end) */
	start = ++end;
	if(*start && *start == 'T')
	 {
	   start++;
	   seen_T = true;
	 } /* end of if(*start == 'T') */
      } /* end of while(*start) */
     
   } /* end of if(*start == 'P') */

  else
   {
     // Hmm No P? 
     value.tv_sec  = atol(duration_p);
   } /* end of else */
  return value;
}

};
};
