//                              -*- Mode: C++ -*- 
// Remos_Sensor.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Sun Feb 25 20:38:56 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Feb 25 22:46:02 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 11
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


/** @file Remos_Sensor.cpp
 *  @ingroup Remos
 *  @brief A QMS Sensor that provides Remos data
 *
 */


#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

extern "C" {
#include "remos.h"
}


/// Using standard C++ namespace.
using namespace std;

#include <iostream>
#include <string>
#include <vector>


#include "ace/Log_Msg.h"


#include "QMS_Debug.h"
#include "QMS_Api.h"
#include "QMS_Remos_Msg.h"
#include "Remos_Datastructs.h"

#include "Remos_Instrumentation.h"

/** @ingroup Remos */

/// RCS version
static const char* version = "$Id: Remos_Sensor.cpp,v 1.3 2001/10/21 08:54:09 srivasta Exp $";

/// We log remos errors to this file
static const char *errFile_p = "remos.err";

/** @var    Remos_Error error
 *  @brief  Remos error.
 */
Remos_Error error;
/** @var       double sleep_interval
 *  @brief  The default refresh rate between each query to Remos.
 */
double sleep_interval = DEFAULT_SLEEP;


///An instance of the QMS_Api.Pl refer QMS_Api documentation.
QMS_Api qms_api;
/** @var       int count
 *  @brief  yet to be documented.
 */
int count = 0;

/// Set a mutex to guard the data
ACE_Thread_Mutex TR_asset_guard;

/**
 *  @brief  Handler to handle the Remos Errors
 *  @param  None
 *  @return None
 *
 *  Uses Remos utility function remos_print_errorinfo to print a
 *  brief description of the error represented by Remos_Error to stderr.
 */
void
handler(Remos_Error err, Remos_Ptr ptr)
{
  QMS_Trace ("handler", __LINE__, __FILE__);
  fprintf (stderr, "Remos Error -- Aborting\n");
  remos_print_errorinfo(err);
  abort();
}

/**
 * @brief  Signal Handler to handle Signals.
 * @param  sig the integer value of different signals.
 * @return None
 *
 * This function, upon receiving a signal,
 *   - Disconnects the qms_api from the Event Channel.
 *   - Uses Remos utility function remos_finish to indicate that
 *     application has finished using the the remos interface. It
 *     doesnot imply that the application is exiting. It is  intended
 *     so any resources allocated by the remos interface internally
 *     can be releases. remos_finish takes standard error argument and
 *     returns a standard  Remos_Status.
 *
 */
void
sig_handler(int sig)
{
  Remos_Status stats;
  QMS_Trace ("sig_handler", __LINE__, __FILE__);
  fprintf (stderr, "Caught Signal %d\n", sig);
  qms_api.disconnect();
  fprintf(stderr, "Done - signalled \n");
  stats = remos_finish(&error);
  fprintf(stderr,"Closed Remos Connection \n");
  exit (sig);
}

void Client (int,int);
void Server (int,int);

/**
 *      @brief  Initializes the remos, connects consumer and suppliers, waits for request.
 *      @param  argc Count of command line arguments.
 *      @param  argv List  of command line arguments.
 *      @return returns the exit status of the program.
 *
 *      This is function is responsible for performing the following tasks.
 *        - Uses remos_start to initialize the Remulac system. This function may include opening a
 *              connection with the lower layer, initializing memory structures etc.
 *        - does corba initialization.
 *        - Registers a function to be called when data is recieved -> Remos_CallBack(..)
 *        - Connects the supplier object (using prior defaults).
 *        - Connects the consumer object (using prior defaults).
 *        - Puts the consumer object into a listen loop, awaiting events.
 */
int
main (int argc, char *argv[])
{
  remos_remulac_id my_id;
  Remos_Status stats;
  QMS_Trace ("main", __LINE__, __FILE__);

  DEBUG0 (DEBUG_L_ENTER, "DEBUG: starting\n");
  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);

  DEBUG0 (DEBUG_L_CALL, "DEBUG: Starting Remos ...\n");

  //Function remos_start has the following prototype.
  //Remos_Status remos_start (char *name, remos_remulac_id *callersid,
  //                          void *errarg, Remos_Handler errhand,
  //                          Remos_Error *error);
  //name          Name for application
  //callers_id    Address of a remos_remulac_id. Will be filled in
  //              with Remulac ID of the  calling node. Must be present.
  //errarg        Pointer to an application defined block of data used
  //              to communicate error  information from the shared
  //              error handler routine to the rest of
  //              application. May be NULL.
  //errhand       Addres of the application default error handler
  //              routine. May be NULL
  //error         Address of a Remos_Error descriptor for error
  //              reporting. May be NULL.

  stats = remos_start((char *)"test", &my_id, NULL, &handler, &error);
  fprintf(stderr, "status of remos_start was: %d\n", stats);
  if (stats != REMOS_OK)
   {
     fprintf(stderr,"Remos Start  FAILED.\n\tVerify collector is running\n");
     fprintf(stderr, "\ton the host and port that you specified.\n\n");
     remos_print_errorinfo(error);
     fprintf (stderr, "\n %d\n", remos_errno (error));
     exit(1);
   }


  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");
  DEBUG3(DEBUG_L_CALL, "DEBUG: starting the API With ID = %d "
         " Send event type = %d Recieve event type = %d\n",  Data_Supplier,
         QMS_Remos_Data, << QMS_Remos_Query );

  char * ecname_p = (char *) "QMS_Channel";

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
             << "\t-h             : This help text"  << endl
             << "\t-v             : Prints out the version"  << endl
             << "\t-ecname NAME   : The name of the event channel"  << endl
             << "\t-e      NAME   : The name of the event channel"  << endl
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        cout << argv[0] << ": Version " << version << endl;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "ecname") || strchr((argv[i] + j), 'f'))
      {
        ecname_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
        strcpy(ecname_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (DEBUG_L_ERROR, "unknown argument", argv[i]);
   }

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {

      qms_api.init(argc, argv,
                   Data_Supplier,   // My ID
                   QMS_Remos_Data,  //  The data I send
                   QMS_Remos_Query, // The data I get
                   ecname_p
                   );
      ACE_TRY_CHECK;
      qms_api.register_callback(Remos_CallBack, 0);
      ACE_TRY_CHECK;
      qms_api.connect_supplier();
      ACE_TRY_CHECK;
      qms_api.connect_consumer();
      ACE_TRY_CHECK;
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

}

char *env_init[] = { "PATH=/home/quite/SensorProbes/TestPrograms/Pipes:/usr/local/share/jdk1.2.2/bin:$PATH", "LD_LIBRARY_PATH=/opt/ACE_wrappers/ace:/home/quite/remos/Remos/java:/opt/QMS", "COLLECTOR=r2d2 8001", "CLASSPATH=/home/quite/remos/Remos/java",  NULL };


/**
 *  @brief  This is the callback function used when the data arrives.
 *  @param  query   The query string that contains the request.
 *  @param  arg_p   This is a NULL argument.
 *  @return void
 *
 *  when the request for data comes in, this call back function is
 *  invoked with the request as an argument. The request (in the form
 *  of string) is extracted and request id, number of iterations as
 *  well as refresh rate are stored in different local variables.
 *
 *  Depending on the type of remos data requested , either the
 *  getGraphInfo or getFlowInfo function is called, which in turn is
 *  repeated for number of iterations requested with a refresh rate in
 *  between.
 */
void
Remos_CallBack(const string &query, void *arg_p)
{
  QMS_Trace ("Remos_CallBack", __LINE__, __FILE__);
  char *node_names[MAX_NODES];
  int request_id = 0;
  QMS_Remos_Msg message;
  int ctrlpipe[2], datapipe[2];
  pid_t childpid;


  printf("\n In Remos_CallBack\n");
  if (arg_p)
   {
     cout << "With a non null argument"  << endl;
   }

  message.insert(query);
  struct Query_struct *query_data_ptr = message.extract_query();

  int iterations= 1;
  int data_id = 0;
  int i = 0;

  request_id = query_data_ptr->request_id;
  iterations = query_data_ptr->repeat_count;
  sleep_interval = query_data_ptr->refresh_rate ;

  int num_nodes = StringToCharHosts(query_data_ptr->host_names, node_names);

  if(iterations == 0)
   {
     iterations = 9999;
   } /* end of if(iterations == 0) */
  
  for(i=0;i<iterations;i++)
   {
     ACE_DECLARE_NEW_CORBA_ENV;
     
     int ret = pipe(ctrlpipe);
     if(ret < 0)
      {
	perror("Error opening control pipe\n");
	ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
      } /* end of if() */
     
     int ret = pipe(datapipe);
     if(ret < 0)
      {
	perror("Error opening data pipe\n");
	ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
      } /* end of if() */
     
     if((childpid = fork()) == 0)
      {
	close(ctrlpipe[1]);
	close(datapipe[0]);
	if (query_data_ptr->type == Query_struct::link)
	 {
	   ret = 
	     execle ("/home/quite/SensorProbes/TestPrograms/Pipes/Remos_Graph_Probe", 
		     "Remos_Graph_Probe", 
		     (char **) node_names, 
		     num_nodes, 
		     (char *) 0, 
		     env_init);
	   perror("Error executing Remos_Graph_Probe\n");
	 }
	else
	 {
	   ret = 
	     execle ("/home/quite/SensorProbes/TestPrograms/Pipes/Remos_Flow_Probe", 
		     "Remos_Flow_Probe", 
		     (char **) node_names, 
		     num_nodes, 
		     (char *) 0, 
		     env_init);
	   perror("Error executing Remos_Flow_Probe\n");
	 }
	
      } /* end of if((childpid = fork()) == ) */
     else
      {
	string message;
	size_t len;
	char buff[MAXLINE];

	close(ctrlpipe[0]);
	close(datapipe[1]);

	while(read(datapipe[0],buff,MAXLINE))
	 {
	   message.append(buff);
	    } /* end of while(read(,buff,MAXLINE)>0) */
	
	char * tmp_p = (char *) message.data();
	tmp_p[message.length()] = 0;
	qms_api.send(tmp_p);
	
      } /* end of else */
     
     printf("Sleeping for %f secs \n",sleep_interval);
     printf("*********************\n");
     ACE_Time_Value sleep_time(sleep_interval, 0);
     ACE_OS::sleep (sleep_time);
   }
}

/**
 *  @brief  Converts the string of host names to array of host names.
 *  @param  hostnames string of hostnames seperated by semicolon.
 *  @param  node_names      Array of node names.
 *  @return the number of nodes in the array.
 *
 *  This function takes a string in which hostnames are seperated by
 *  semicolon and puts these hostnames into an array. The criteria
 *  used here is to put the hostnames in to the array, until the end
 *  of string has been reached.
 */
int
StringToCharHosts(string hostnames, char *node_names[])
{
  QMS_Trace ("StringToCharHosts", __LINE__, __FILE__);
  string x;
  int len, i = 0;
  int num_nodes = 0;

  if (!hostnames.empty())
   {
     bool done = false;
     size_t location = 0;
     size_t start = 0;
     size_t stop = hostnames.length();
     while (done == false)
      {
        location = hostnames.find(",", start);
        if (location == string::npos)
         {
           x.assign(hostnames.substr(start, hostnames.length()-1));
           len = x.length();
           node_names[i] = new char [len + 1];
           x.copy(node_names[i], len, 0);
           node_names[i][len] = 0;
           cout << "node " << node_names[i] << endl;
           i++;

           cout << "\nnew string -> " << x << endl;
           done = true;
         }
        else
         {
           stop = location;
           x.assign(hostnames.substr(start, stop - start));
           len = x.length();
           node_names[i] = new char [len + 1];
           x.copy(node_names[i], len, 0);
           node_names[i][len] = 0;
           cout << "node " << node_names[i] << endl;
           i++;

           cout << "\nnew string -> " << x;
           start = location +1;
         }
      }
     num_nodes = i;
     cout << "num_nodes -> " << num_nodes << endl;
   }
  return num_nodes;
}

/**
 * @brief  Displays the error messages.
 * @param  format  The format in which the error message needs to printed.
 * @return void
*/
void
errMsg(const char *format,...)
{
  QMS_Trace ("errMsg", __LINE__, __FILE__);
  FILE    *eFile;
  va_list args;

  if((eFile = fopen(errFile_p,"a")) == NULL)
   {
     printf("Error Writing to error File. Errors will not be recorded\n");
     return;
   }
  va_start (args,format);
  vfprintf(eFile, format,args);
  va_end(args);
  fprintf(eFile,"\n");
  fclose(eFile);
}

