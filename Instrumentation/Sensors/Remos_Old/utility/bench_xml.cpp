//                              -*- Mode: C++ -*-
// bench_xml.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Thu Dec  7 14:46:16 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Jan 14 23:27:59 2001
// Last Machine Used: ember
// Update Count     : 76
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: bench_xml.cpp,v 1.9 2001/10/21 08:54:10 srivasta Exp $
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


/** @file bench_xml.cpp
 *  @ingroup Remos Benchmarks
 *  @brief QMS_Remos_Msg class performance metrics
 *
 *  This is a test designed to provide performance metrics about the
 *  impact of conversion to and from XML
 */

#include <signal.h>
#include <string>
#include <vector>
extern "C" {
#include <string.h>
}

#include <ace/OS.h>
#include "Remos_Datastructs.h"
#include "QMS_Remos_Msg.h"
#include "QMS_Debug.h"
#include <ace/High_Res_Timer.h>
#include <iostream>
#include <iomanip>


using namespace std;

/// RCS version string
static const char* version = "$Id: bench_xml.cpp,v 1.9 2001/10/21 08:54:10 srivasta Exp $";

/**
 *  @param sig The signal being handled
 *  @brief The default signal handler
 */
void
sig_handler (int sig)
{
  QMS_Trace ("sig_handler", __LINE__, __FILE__);
  DEBUG1 (DEBUG_L_ENTER, "caught signal %d \n",sig);
  exit (sig);
}

/**
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 *  @brief The main entry point
 *
 * Usage: [CORBA OPTIONS] [OPTIONS]
 *
 *   -  -help       : This help text
 *   -  -h          : This help text
 *   -  -version    : Prints out the version
 *   -  -v          : Prints out the version
 *   -  -number num : number of times to run the test[10]
 *   -  -n      num : number of times to run the test[10]
 *   -  -iter   num : number of iterations per run[1000]
 *   -  -i      num : number of iterations per run[1000]
 */
int
main (int argc, char *argv[])
{
  QMS_Trace ("main", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: starting\n");
  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);

  int iterations = 1000;
  int repeat     = 10;


  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");
  DEBUG0 (DEBUG_L_CALL, "DEBUG: parsing arguments\n");

  ACE_High_Res_Timer timer;


  for (int i = 0; i < argc; i++)
   {
     if (!argv[i])           { break; }
     if (argv[i][0] != '-')  { continue; }
     int j = 1;
     if (argv[i][1] == '-')  {
       if (argv[i][2] == 0)  { break; }	// handle -- end of options
       j = 2;			// handle --argument
     }
     if (strstr((argv[i] + j), "ORB"))  { continue; }
     if (! strcmp((argv[i] + j), "help") || strchr((argv[i] + j), 'h'))
      {				// -h or --help
	cout << argv[0] << version << endl
	     << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
	     << endl
	     << "\t-help       : This help text"  << endl
	     << "\t-h          : This help text"  << endl
	     << "\t-version    : Prints out the version"  << endl
	     << "\t-v          : Prints out the version"  << endl
	     << "\t-number num : number of times to run the test[10]"  << endl
	     << "\t-n      num : number of times to run the test[10]"  << endl
	     << "\t-iter   num : number of iterations per run[1000]"  << endl
	     << "\t-i      num : number of iterations per run[1000]"  << endl
	  ;
	  ;
	exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
	cout << argv[0] << ": version " << version << endl;
	exit (0);
      }

     if (! strcmp((argv[i] + j), "iter") || strchr((argv[i] + j), 'i'))
      {
	iterations = atoi (argv[i + 1]);;
	continue;
      }

     if (! strcmp((argv[i] + j), "number") || strchr((argv[i] + j), 'n'))
      {
	repeat = atoi (argv[i + 1]);
	continue;
      }


     DEBUG1 (DEBUG_L_ENTER, "unknown argument %s\n", argv[i]);
   }

  // create the dummy remos data struct
  Data_struct data;
  data.request_id = 0;
  data.data_id = 4;
  data.refresh_rate = 2.45;
  data.latency = 0.235;
  data.available_bandwidth = 100000.0;
  data.maximum_bandwidth  = 200000.0;
  data.type = Data_struct::link;
  data.source = "Host One";
  data.destination = "Host Two";


  Query_struct query;

  query.request_id = 0;
  query.repeat_count = 5;
  query.refresh_rate = 2.45;
  query.type = Query_struct::link;
  query.host_names = "skywalker_t.stdc.com,kenobee_t.stdc.com,c3po_t.stdc.com";

  // Allocate memory to store the results
  ACE_hrtime_t *create_data_p  = 0;
  ACE_hrtime_t *extract_data_p = 0;

  ACE_hrtime_t *create_req_p   = 0;
  ACE_hrtime_t *extract_req_p  = 0;

  create_data_p  = (ACE_hrtime_t *) malloc (repeat * sizeof(ACE_hrtime_t));
  if (!create_data_p)
   {
     fprintf (stderr, "Out of Memory\n");
     exit (1);
   }

  extract_data_p  = (ACE_hrtime_t *) malloc (repeat * sizeof(ACE_hrtime_t));
  if (!extract_data_p)
   {
     fprintf (stderr, "Out of Memory\n");
     exit (1);
   }

  create_req_p  = (ACE_hrtime_t *) malloc (repeat * sizeof(ACE_hrtime_t));
  if (!create_req_p)
   {
     fprintf (stderr, "Out of Memory\n");
     exit (1);
   }

  extract_req_p  = (ACE_hrtime_t *) malloc (repeat * sizeof(ACE_hrtime_t));
  if (!extract_req_p)
   {
     fprintf (stderr, "Out of Memory\n");
     exit (1);
   }


  // Start testing here
  QMS_Remos_Msg data_msg;
  QMS_Remos_Msg query_msg;

  int run;

  for (run = 0; run < repeat; run++)
   {
     timer.start();
     for (int i = 0; i < iterations; i++)
      {
	data_msg.insert(data);
      }
     timer.stop();
     timer.elapsed_time(create_data_p[run]);
     timer.reset();
   }

  struct Data_struct *new_data_p = 0;
  for (run = 0; run < repeat; run++)
   {
     timer.start();
     for (int i = 0; i < iterations; i++)
      {

	new_data_p = data_msg.extract_data();

      }
     timer.stop();
     timer.elapsed_time(extract_data_p[run]);
     timer.reset();
   }

  for ( run = 0; run < repeat; run++)
   {
     timer.start();
     for (int i = 0; i < iterations; i++)
      {
	query_msg.insert(query);
      }
     timer.stop();
     timer.elapsed_time(create_req_p[run]);
     timer.reset();
   }

  struct Query_struct *new_query_p = 0;
  for ( run = 0; run < repeat; run++)
   {
     timer.start();
     for (int i = 0; i < iterations; i++)
      {

	new_query_p = query_msg.extract_query();

      }
     timer.stop();
     timer.elapsed_time(extract_req_p[run]);
     timer.reset();
   }


  double avg_cd = 0;
  double avg_ed = 0;
  double avg_cr = 0;
  double avg_er = 0;

  cout << "------------------------------------------------------"
       << "----------------"
       << endl;
  printf("     XML conversion overhead For remos queries and data events\n");
  printf("                Elapsed nanoseconds for %d iterations\n",
	 iterations);

  cout << "------------------------------------------------------"
       << "----------------"
       << endl;

  printf(" Run   |              query           |             Data\n");
  printf("Number |     create          extract  |     create       extract\n");

  cout << "------------------------------------------------------"
       << "----------------"
       << endl;

  for ( run = 0; run < repeat; run++)
   {

#if defined (_WIN32) /* Only Win32 needs special treatment. */

	  double a = (signed _int64) create_data_p[run];
	  double b = (signed _int64) extract_data_p[run];
	  double c = (signed _int64) create_req_p[run];
	  double d = (signed _int64) extract_req_p[run];

#else

	  double a = (double) create_data_p[run];
	  double b = (double) extract_data_p[run];
	  double c = (double) create_req_p[run];
	  double d = (double) extract_req_p[run];
#endif
/*

	  cout << "    " << run       << "  | "
	  << setw( 12 ) << create_data_p[run]  << "    "
	  << setw( 12 ) << extract_data_p[run] << " | "
	  << setw( 12 ) << create_req_p[run]   << "    "
	  << setw( 12 ) << extract_req_p[run]  << endl;
*/

	  // VC++ 6.0 cout doent support unsigned _int64 as well as signed _int64.
	  // The conversion from unsigned _int64 to double is not supported.
	  // Because of this the unsigned _int64 has to be
	  // converted to signed _int64 and then to double , in order for cout to print.




	  cout << "    " << run       << "  | "
		  << std::setw( 12 ) << a  << "    "
		  << std::setw( 12 ) << b << " | "
		  << std::setw( 12 ) << c   << "    "
		  << std::setw( 12 ) << d  << endl;

	  // here signed _int64 is implicitly converted to double.

#if defined (_WIN32) /* Only Win32 needs special treatment. */

     avg_cd += (signed _int64) create_data_p[run];
     avg_ed += (signed _int64) extract_data_p[run];
     avg_cr += (signed _int64)create_req_p[run];
     avg_er += (signed _int64) extract_req_p[run];
#else
     avg_cd += (double) create_data_p[run];
     avg_ed += (double) extract_data_p[run];
     avg_cr += (double)create_req_p[run];
     avg_er += (double) extract_req_p[run];
#endif
     }

  avg_cd /= repeat;
  avg_ed /= repeat;
  avg_cr /= repeat;
  avg_er /= repeat;

  avg_cd /= iterations;
  avg_ed /= iterations;
  avg_cr /= iterations;
  avg_er /= iterations;

  cout << "------------------------------------------------------"
       << "----------------"
       << endl;

  cout << "  avg  |      "
	  << std::setw( 12 ) << avg_cd << "         "
	  << std::setw( 12 ) << avg_ed << " |     "
	  << std::setw( 12 ) << avg_cr << "         "
	  << std::setw( 12 ) << avg_er << endl;

  cout << "------------------------------------------------------"
       << "----------------"
       << endl;

  cout << "     The average is the average number of nanoseconds per iteration"
       << endl;

  exit (0);
}
