//                              -*- Mode: C++ -*-
// bench_send.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Dec  6 10:30:09 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Jan 14 23:27:49 2001
// Last Machine Used: ember
// Update Count     : 86
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


/** @file bench_send.cpp
 *  @ingroup Remos Benchmarks
 *  @brief The sender/reporter part of the QMS benchmark test.
 *
 *  This is a part of a two part test designed to provide round trip
 *  latency metrics of a typical QMS event transaction.
 */


#include <signal.h>

#include <string>
extern "C" {
#include <string.h>
}

#include "ace/OS.h"             // For the LM_DEBUG macros
#include "ace/Log_Msg.h"
#include "ace/Thread.h"
#include "ace/Synch.h"
#include "QMS_Remos_Msg.h"
#include "Remos_Datastructs.h"
#include "QMS_Config.h"
#include "QMS_Api.h"
#include "QMS_Debug.h"

#include "orbsvcs/Time_Utilities.h"
#include "orbsvcs/Event_Utilities.h"
#include <ace/High_Res_Timer.h>


#include <iostream>
#include <iomanip>
#include <vector>

/// Where we stash the QMS_API object
QMS_Api qms_api;

/// RCS version string
static const char* version = "$Id: bench_send.cpp,v 1.11 2001/10/21 08:54:10 srivasta Exp $";

/** @struct thread_arg
 *  @brief Data passed to the sending thread
 */
struct thread_arg
{
  /// number of time to repeat the experiment
  int repeat;

  /// numer of iterations per run
  int iterations;
  /// current run
  int run;

  /// count of the message sent
  int count;
  /// A mutex that protects count
  ACE_Thread_Mutex TD_count_guard;

  /// number of iterations done
  int iter_count;
  /// protects iter_count;
  ACE_Thread_Mutex TD_iteration_guard;
  /// The file to get message from
  char *filename_p;

  /// A mutex to protect the condition variable cond
  ACE_Thread_Mutex run_mutex;
  /// A condition variable used to determine whether the run is over
  ACE_Condition_Thread_Mutex *cond;
  /// A variable set to true at the end of a run
  bool are_we_done_yet;

  /// A high resolution (nanosec) time
  ACE_High_Res_Timer timer;

  /// The mutex that protects the results
  ACE_Thread_Mutex TD_asset_guard; // protects results
  /// Time stamp for sending data
  ACE_hrtime_t *sending;
  /// Time stamp for receiving data
  ACE_hrtime_t *receiving;
};


/**
 *  @param sig The signal being handled
 *  @brief The default signal handler
 *
 *  Ensure that we disconnect cleanly from QMS
 */
void
sig_handler (int sig)
{
  QMS_Trace ("sig_handler", __LINE__, __FILE__);
  DEBUG1 (DEBUG_L_ENTER, "caught signal %d\n", sig);
  qms_api.disconnect();
  exit (sig);
}

/**
 *  @param arg_p Optional argument, unused
 *  @brief  Generate a test Remos Query randomly
 *
 * Here we generate a mock query statically, incrementing the request
 * ID every time we are invoked. We instantiate a struct Query_struct,
 * populate it, and use a QMS_Remos_Msg object to facilitate
 * conversion to XML
 */
char *
mock_message(struct thread_arg *arg_p)
{
  QMS_Trace ("mock_message", __LINE__, __FILE__);
  Query_struct query;
  ACE_Write_Guard<ACE_Thread_Mutex> guard(arg_p->TD_count_guard);
  {
    query.request_id = arg_p->count++;
  }
  query.request_id = 0;
  query.repeat_count = 5;
  query.refresh_rate = 2.45;
  query.type = Query_struct::link;
  query.host_names = "skywalker_t.stdc.com,kenobee_t.stdc.com,c3po_t.stdc.com";
  DEBUG0 (DEBUG_L_CALL, "DEBUG Created Query\n");
  //  cout << "============================================================"
  //   <<endl;
  //  print_query(&query);
  //  cout << "============================================================"
  //   <<endl;

  QMS_Remos_Msg message;
  message.insert(query);
  return (char *)message.as_string();
}

/// The maximum number of characters in a path name
#ifndef PATH_MAX
# define PATH_MAX 4095
#endif

/**
 *  @param file_p Name fo the file to read the data from
 *  @brief  Generate a test Remos Query from a file
 *
 * Instead of generating a mock query by populating a struct on the
 * fly, we read the query directly from a file. It is assumed that the
 * file is in a format that is being expected by the remote end.
 */
char *
file_message(char * file_p)
{
  QMS_Trace ("file_message", __LINE__, __FILE__);
  // We need to read this file
  // We assume that the file has a genuine XML message, since until we
  // have a validating parser, little can be done about error checking
  DEBUG0 (DEBUG_L_ENTER, "DEBUG opening file\n");
  FILE *input_file_p = fopen(file_p, "r");
  if (!input_file_p)
   {
     DEBUG1 (DEBUG_L_ENTER, "Error reading file %s \n", file_p);
     perror("fopen error");
     exit (errno);
   }
  char buffer[PATH_MAX];
  string file;
  DEBUG0 (DEBUG_L_CALL, "DEBUG reading file\n");
  while (fgets (buffer, PATH_MAX, input_file_p))
  {
    file.append(buffer);
  }
  char * tmp_p = (char *) file.data();
  tmp_p[file.length()] = 0;

  return tmp_p;
}

/**
 *  @param arg_p Configuration values passed in to the thread
 *  @brief This is the thread that generates all the queries
 *
 *  This is where we send all the test messages. Depending o the
 *  argument, either we read a static XML evnt from a file (and thus
 *  there is no XML conversion overhead incurred), or we instantiate
 *  and populate a struct Query_struct for every message and convert
 *  it to XML format using a QMS_Remos_Msg object on the fly.
 *
 *  In either case, we loop through the number of runs requested. For
 *  each run, we send the number of messages we are supposed to send
 *  in a loop, and then wait (using a condition variable) for all the
 *  responses to be recieved before recording the time taken and
 *  moving on to the next run.
 *
 * Finally, when all the runs have been done and recorded, we
 * calculate the averages and produce the report on the stdout
 */
void
generate_query(void *arg_p)
{
  QMS_Trace ("generate_query", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG Thread Created\n");
  ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval *
			     ACE_OS::rand() % 30, 0);
  DEBUG0 (DEBUG_L_CALL, "DEBUG Thread sleeping\n");
  ACE_Thread::yield();
  ACE_OS::sleep (sleep_time);
  DEBUG0 (DEBUG_L_CALL, "DEBUG Thread awake\n");
  string message;
  struct thread_arg *argument_p = (struct thread_arg *) arg_p;
  ACE_High_Res_Timer send_timer;

  // well, do the sending here
  if (argument_p && argument_p->filename_p)
   {
     // well, we do not want to do any XML processing here
     message = file_message(argument_p->filename_p);
     // Start the loop here
     for (int run = 0; run < argument_p->repeat; run++)
      {
	argument_p->timer.reset();
	argument_p->timer.start();
	send_timer.start();
	for (int i = 0; i < argument_p->iterations; i++)
	 {
	   qms_api.send(message);
	 }
	send_timer.stop();
	send_timer.elapsed_time(argument_p->sending[run]);
	send_timer.reset();

	argument_p->run_mutex.acquire();
	while(argument_p->are_we_done_yet == false)
	 {
	   argument_p->cond->wait();
	 }
	argument_p->are_we_done_yet = false;
	argument_p->run++;
	argument_p->run_mutex.release();
	ACE_Write_Guard<ACE_Thread_Mutex> guard(argument_p->TD_iteration_guard);
	{
	  argument_p->iter_count = argument_p->iterations;
	}
      }
   }
  else
   {
     // Start the loop here
     for (int run = 0; run < argument_p->repeat; run++)
      {

	argument_p->timer.reset();
	argument_p->timer.start();
	send_timer.start();
	for (int i = 0; i < argument_p->iterations; i++)
	 {
	   message = mock_message(argument_p);
	   qms_api.send(message);
	 }
	send_timer.stop();
	send_timer.elapsed_time(argument_p->sending[run]);
	send_timer.reset();

	argument_p->run_mutex.acquire();
	while(argument_p->are_we_done_yet == false)
	 {
	   argument_p->cond->wait();
	 }
	argument_p->are_we_done_yet = false;
	argument_p->run++;
	argument_p->run_mutex.release();
	ACE_Write_Guard<ACE_Thread_Mutex> guard(argument_p->TD_iteration_guard);
	{
	  argument_p->iter_count = argument_p->iterations;
	}
      }
   }

  // Whew. Now to print everything.
  double avg_send = 0;
  double avg_recv = 0;
  cout << "------------------------------------------------------"
       << "----------------"
       << endl;
  printf("                Elapsed nanoseconds for %d iterations\n",
	 argument_p->iterations);
    cout << "------------------------------------------------------"
       << "----------------"
       << endl;

  printf(" Run   | Sending      Round Trip\n");

  for (int run = 0; run < argument_p->repeat; run++)
   {
     // VC++ 6.0 cout doent support unsigned _int64 as well as signed _int64.
     // The conversion from unsigned _int64 to double is not supported.
     // Because of this the unsigned _int64 has to be
     // converted to signed _int64 and then to double , in order for
     // cout to print.

#if defined (_WIN32) /* Only Win32 needs special treatment. */

     double a = (signed _int64)argument_p->sending[run];
     double b = (signed _int64)argument_p->receiving[run];

#else

     double a = (double)argument_p->sending[run];
     double b = (double)argument_p->receiving[run];

#endif

     cout << "    " << run       << "  | "
	  << std::setw( 12 ) << a << "    "
	  << std::setw( 12 ) << b <<  endl;

#if defined (_WIN32) /* Only Win32 needs special treatment. */

     avg_send += (signed _int64)argument_p->sending[run];
     avg_recv += (signed _int64)argument_p->receiving[run];

#else

     avg_send += (double)argument_p->sending[run];
     avg_recv += (double)argument_p->receiving[run];

#endif

   }

  cout << "------------------------------------------------------"
       << "----------------"
       << endl;


  avg_send /= argument_p->repeat;
  avg_recv /= argument_p->repeat;

  avg_send /= argument_p->iterations;
  avg_recv /= argument_p->iterations;


  cout << "------------------------------------------------------"
       << "----------------"
       << endl;

  cout << "  avg  |      "
	  << std::setw( 12 ) << avg_send << "         "
	  << std::setw( 12 ) << avg_recv << endl;

  cout << "------------------------------------------------------"
       << "----------------"
       << endl;

  cout << "     The average is the average number of nanoseconds per iteration"
       << endl;

  DEBUG0 (DEBUG_L_LEAVE, "DEBUG Thread all done, exiting\n");
}


/**
 *  @param data The event data recieved
 *  @param arg_p Configuration values passed in
 *  @brief Function called when there is an event to be consumed
 *
 *  Whenever an event is recieved, we convert it from XML into a a
 *  struct Data_struct. Then we decrement a counter, and test to see
 *  if the current run is completed. If it is, we stop the run timer,
 *  calculate the time taken, and signal the sending thread that it is
 *  OK to either start another run, or to generate the termination
 *  report.
 */
void
my_cb_func(const string &data, void *arg_p = 0)
{
  QMS_Trace ("my_cb_func", __LINE__, __FILE__);
  struct thread_arg *argument_p = (struct thread_arg *) arg_p;
  bool done = false;


  QMS_Remos_Msg message;
  message.insert(data);
  struct Data_struct *data_p = message.extract_data();
  ACE_Write_Guard<ACE_Thread_Mutex> guard(argument_p->TD_iteration_guard);
  {
    argument_p->iter_count--;
    if (argument_p->iter_count <= 0)
     {
       argument_p->timer.stop();
       done = true;
     }
  }
  if (done)
   {
     ACE_Write_Guard<ACE_Thread_Mutex> guard(argument_p->TD_asset_guard);
     {
       argument_p->are_we_done_yet = true;
       argument_p->timer.elapsed_time(argument_p->receiving[argument_p->run]);
       argument_p->timer.reset();
     }
     //  argument_p->run_mutex.acquire();
      argument_p->cond->signal();
      // argument_p->run_mutex.release();
   }

 }


/**
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 *  @brief The main entry point
 *
 * Usage:  [CORBA OPTIONS] [OPTIONS]
 *
 *     - -h             : This help text
 *     - -v             : Prints out the version
 *     - -file Filename : Read XML data from here
 *     - -f    Filename : Read XML data from here
 *     - -iter   num    : number of iterations per run[1000]
 *     - -i      num    : number of iterations per run[1000]
 *     - -num  number   : The number of times to run the test[10]
 *     - -n    number   : The number of times to run the test[10]
 *     - -raw           : Use the raw corba interface(NIY)
 *     - -r             : Use the raw corba interface(NIY)
 *     - -ecname NAME   : The name of the event channel
 *     - -e      NAME   : The name of the event channel
 */
int
main (int argc, char **argv)
{
  QMS_Trace ("main", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: starting\n");
  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);
  bool use_raw_interface = false;



  struct thread_arg argument;
  argument.count           = 0;
  argument.run             = 0;
  argument.repeat          = 10;
  argument.iterations      = 1000;
  argument.filename_p      = 0;
  argument.iter_count      = 1000;
  argument.are_we_done_yet = false;
  argument.sending         = 0;
  argument.receiving       = 0;


  ACE_Condition_Thread_Mutex cond(argument.run_mutex);
  argument.cond = &cond;

  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");
  ACE_OS::srand(time(0));

  DEBUG3 (DEBUG_L_CALL, "DEBUG: starting the API With ID = %d"
	  " Send event type = %d Recieve event type = %d\n" ,
	  Query_Supplier, QMS_Remos_Query, QMS_Remos_Data);

  char * ecname_p = (char *) "QMS_Channel";

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
	     << "\t-h             : This help text"  << endl
	     << "\t-v             : Prints out the version"  << endl
	     << "\t-file Filename : Read XML data from here"  << endl
	     << "\t-f    Filename : Read XML data from here"  << endl
             << "\t-iter   num    : number of iterations per run[1000]"
	     << endl
             << "\t-i      num    : number of iterations per run[1000]"
	     << endl
	     << "\t-num  number   : The number of times to run the test[10]"
	     << endl
	     << "\t-n    number   : The number of times to run the test[10]"
	     << endl
	     << "\t-raw           : Use the raw corba interface(NIY)"  << endl
	     << "\t-r             : Use the raw corba interface(NIY)"  << endl
	     << "\t-ecname NAME   : The name of the event channel"  << endl
	     << "\t-e      NAME   : The name of the event channel"  << endl
	  ;
	exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
	cout << argv[0] << ": Version "<< version << endl;
	exit (0);
      }

     if (! strcmp((argv[i] + j), "file") || strchr((argv[i] + j), 'f'))
      {
	argument.filename_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
	strcpy(argument.filename_p,argv[i + 1]);
	continue;
      }

     if (! strcmp((argv[i] + j), "raw") || strchr((argv[i] + j), 'r'))
      {
	use_raw_interface = true;
	continue;
      }
     if (! strcmp((argv[i] + j), "iter") || strchr((argv[i] + j), 'i'))
      {
        argument.iterations = atoi (argv[i + 1]);;
        argument.iter_count = argument.iterations;
        continue;
      }

     if (! strcmp((argv[i] + j), "number") || strchr((argv[i] + j), 'n'))
      {
        argument.repeat = atoi (argv[i + 1]);
        continue;
      }
     if (! strcmp((argv[i] + j), "ecname") || strchr((argv[i] + j), 'e'))
      {
        ecname_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
        strcpy(ecname_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (DEBUG_L_ERROR, "unknown argument %s", argv[i] );
   }
  argument.sending   =
    (ACE_hrtime_t *) malloc (argument.repeat * sizeof(ACE_hrtime_t));
  argument.receiving =
    (ACE_hrtime_t *) malloc (argument.repeat * sizeof(ACE_hrtime_t));

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {

      qms_api.init(argc, argv,
		   Query_Supplier,  // My ID
		   QMS_Remos_Query, //  The data I send
		   QMS_Remos_Data,  // The data I get
		   ecname_p
		   );
      ACE_TRY_CHECK;


      qms_api.register_callback(my_cb_func, (void *) &argument);
      ACE_TRY_CHECK;
      qms_api.connect_supplier();
      ACE_TRY_CHECK;
      qms_api.connect_consumer();
      ACE_TRY_CHECK;

      DEBUG0 (DEBUG_L_CALL, "DEBUG: Spawning a thread\n");

      if (ACE_Thread::spawn((ACE_THR_FUNC)generate_query,
			    (void *) &argument,	 // arg
			    THR_JOINABLE,        // flags
			    0,	                 // t_id
			    0,	                 // t_handle
			    ACE_DEFAULT_THREAD_PRIORITY,
			    0,	                 // stack
			    0,	                 // stack_size
			    0	                 // thread_adapter
			    )==-1)
       {
	 DEBUG0 (DEBUG_L_ERROR, "DEBUG: Error in spawning thread\n");
       }
      DEBUG0 (DEBUG_L_CALL, "DEBUG: Entering Loop\n");
      qms_api.listen();
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      qms_api.connect_supplier();
      qms_api.connect_consumer();
	exit (1);
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      qms_api.connect_supplier();
      qms_api.connect_consumer();
      exit (2);
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      qms_api.connect_supplier();
      qms_api.connect_consumer();
      exit (3);
    }
  ACE_ENDTRY;

  exit (0);
}
