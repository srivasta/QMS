//                              -*- Mode: C++ -*- 
// test_duration.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Sat Nov 17 22:50:06 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Dec  5 23:17:42 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 64
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
"$Id: test_duration.cpp,v 1.3 2001/12/08 14:52:19 nath Exp $";


#include <fstream>
#include <iostream>
#include <strstream>
#include <sstream>
#include <cstdlib>

#include <cstring>
#include <string>
#include <ctype.h>

#include <exception>
#include <stdexcept>

#include "Debug.h"

#include "Parse_Duration.cpp"

int
main(int argc, char *argv[])
{
  char * duration_p = 0;
  DEBUG0 (DEBUG_L_CALL, "DEBUG: parsing arguments\n");
  for (int i = 0; i < argc; i++)
   {
     if (!argv[i])           { break; }
     if (argv[i][0] != '-')  { continue; }
     int j = 1;
     if (argv[i][1] == '-')  {
       if (argv[i][2] == 0)  { break; } // handle -- end of options
       j = 2;                   // handle --argument
     }
     if (strstr((argv[i] + j), "ORB"))  { continue; }
     if (! strcmp((argv[i] + j), "help") || strchr((argv[i] + j), 'h'))
      {                         // -h or --help
        cout << argv[0] << version << endl
             << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
             << endl
             << "\t-h                  : This help text"  << endl
             << "\t-v                  : Prints out the version"  << endl
             << "\t-duration duration  : The name of the event channel"  << endl
             << "\t-d        duration  : The name of the event channel"  << endl
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        cout << argv[0] << ": Version "<< version << endl;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "duration") || strchr((argv[i] + j), 'd'))
      {
        duration_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
        strcpy(duration_p,argv[i + 1]);
        continue;
      }
     std::cerr << "unknown argument %s" << argv[i] << std::endl;
   }
  if(!duration_p)
   {
     duration_p = (char *) malloc (sizeof("P12000.456S"));
     strcpy(duration_p,"P12000.456S");
   } /* end of if(!duratoin_P) */
  
  std::cerr << "DEBUG: Duration = " << duration_p << std::endl;  
  struct timespec period = STDC::QMS::duration_to_tv(duration_p);
  std::cerr << "The number of seconds is " << period.tv_sec
	    << " and the nanoseconds is "  << period.tv_nsec
	    << std::endl;

  std::cerr << "*****Sleeping for above number of seconds " << endl;
  ACE_OS::nanosleep(&period);

  if(duration_p)
   {
     free(duration_p);
     duration_p = 0;
   } /* end of if(duration_p) */
  
  std::cerr << "DEBUG: Done" << std::endl; 
  exit(EXIT_SUCCESS);             
} /* end of main() */

