//                              -*- Mode: C++ -*-
// test_msg.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Mon Oct 23 23:08:25 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Jan 14 23:28:29 2001
// Last Machine Used: ember
// Update Count     : 89
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: test_msg.cpp,v 1.7 2001/10/21 08:54:10 srivasta Exp $
//
/** @file test_msg.cpp
 *  @ingroup Remos Testing
 *  @brief Exerciser for the QMS_Remos_Msg class
 *
 */

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


#include <signal.h>
#include <string>
#include <vector>
extern "C" {
#include <string.h>
}

#include "Remos_Datastructs.h"
#include "QMS_Remos_Msg.h"
#include "QMS_Debug.h"


/// RCS version string
static const char* version = "$Id: test_msg.cpp,v 1.7 2001/10/21 08:54:10 srivasta Exp $";

/**
 *  @brief The default signal handler
 *  @param sig The signal being handled
 *
 *  The default action is to exit
 */
void
sig_handler(int sig)
{
  QMS_Trace ("sig_handler", __LINE__, __FILE__);
  DEBUG1 (DEBUG_L_ENTER, "caught signal %d \n",sig);
  exit (sig);
}

/**
 *  @brief The main entry point
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 *
 * Usage:    [CORBA OPTIONS] [OPTIONS]
 *   -  -help       : This help text
 *   -  -h          : This help text
 *   -  -version    : Prints out the version
 *   -  -v          : Prints out the version
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

  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");
  DEBUG0 (DEBUG_L_CALL, "DEBUG: parsing arguments\n");
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
	     << "\t-h : This help text"  << endl
	     << "\t-v : Prints out the version"  << endl
	  ;
	exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
	cout << argv[0] << ": version " << version << endl;
	exit (0);
      }
     else
      {
	DEBUG1 (DEBUG_L_ENTER, "unknown argument %s\n", argv[i]);
      }
   }
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
  cerr << "=================================print_data================="
       <<endl;

  print_data(&data);

  cerr << "============================Message_as_string=============="
       <<endl;

  QMS_Remos_Msg data_msg;
  data_msg.insert(data);
  cout << data_msg.as_string();
   cerr << "==========================print_data==========================="
       <<endl;
  struct Data_struct *new_data_p = data_msg.extract_data();
  print_data(new_data_p);
  cerr << "=========================================================="
       <<endl;

  Query_struct query;

  query.request_id = 0;
  query.repeat_count = 5;
  query.refresh_rate = 2.45;
  query.type = Query_struct::link;
  query.host_names = "skywalker_t.stdc.com,kenobee_t.stdc.com,c3po_t.stdc.com";
  cerr << "================================print_query===================="
       <<endl;

  print_query(&query);

  cerr << "============================query as string===================="
       <<endl;
  data_msg.erase();

  QMS_Remos_Msg query_msg;
  query_msg.insert(query);
  cout << query_msg.as_string();
  cerr << "================================print query=================="
       <<endl;

  struct Query_struct *new_query_p = query_msg.extract_query();
  print_query(new_query_p);

  exit (0);
}
