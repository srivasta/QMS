//                              -*- Mode: C++ -*-
// Remos_Instrumentation.cpp ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Fri Oct 27 11:16:59 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Jan 14 21:49:27 2001
// Last Machine Used: ember
// Update Count     : 85
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: Remos_Instrumentation.cpp,v 1.13 2001/10/21 08:54:09 srivasta Exp $
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


/** @file Remos_Instrumentation.cpp
 *  @ingroup Remos
 *  @brief Contains implementation of a QMS Sensor that delivers Remos data
 *
 *  This file provides the implementation of a QMS sensor (complete
 *  with an interface to the QMS infrastructure) that provides an
 *  interface to Remos. This implementation also delivers periodic
 *  updates of Remos data at configurable intervals
 */


#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdarg.h>

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
static const char* version = "$Id: Remos_Instrumentation.cpp,v 1.13 2001/10/21 08:54:09 srivasta Exp $";

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
             << "\t-file Filename : Read XML data from here"  << endl
             << "\t-f    Filename : Read XML data from here"  << endl
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



/**
 * @brief  Used to get Graph information of a node w.r.t to switch.
 * @param  node_names[] names of the nodes involved.
 * @param  num_nodes number of nodes involved.
 * @param  request_id request_id of a request.
 * @param  data_id number of data messages associated with a request_id.
 * @return returns 0 on success.
 *
 * This function uses the Remos Utility,Status,List and Graph
 * functions to get the graph structure for a set of nodes and
 * sends this information to Event Channel using qms_api send method.
 *
 *     - Remos Utility function remos_getidbyname
 *     - Remos Status function  remos_get_node
 *     - Remos List function    remos_list_append
 *     - Remos Graph function   remos_get_graph
 *
 */
int
getGraphInfo(char *node_names[], int num_nodes, int request_id,
             int &data_id)
{
  Remos_Node      node[MAX_NODES];
  Remos_Graph     graph;
  remos_remulac_id node_id[MAX_NODES];
  int i = 0, j = 0;

  Remos_Status stats;
  Remos_Node_List node_list;
  Remos_Link cur_link;

  double time = 0;              // Time is not relevant here
  QMS_Trace ("getGraphInfo", __LINE__, __FILE__);
  node_list = (Remos_Node_List)remos_new_list(num_nodes);

  for(i=0; i < num_nodes; i++)
   {

     stats = remos_getidbyname(node_names[i], 0, &(node_id[i]), &error);
     if (stats != REMOS_OK)
      {
        errMsg("Error getting ID for node %s", node_names[i]);
      }

     stats = remos_get_node(node_id[i], &(node[i]), &time, &error);
     if (stats != REMOS_OK)
      {
        errMsg("Error getting Node Info for node %s", node_names[i]);
      }
     else
      {
        remos_list_append(node[i],node_list);
      }

   }

  stats = remos_get_graph(node_list,&graph,&time,TRUE,&error);
  if(stats != REMOS_OK)
   {
     errMsg("Prob getting graph...in iteration %d \n",i);
   }

  for(j=0;j<graph->edges->elem_count;j++)
   {
     Data_struct reply_data_ptr;
     cur_link = graph->edges->list[j];

     ACE_Write_Guard<ACE_Thread_Mutex> guard(TR_asset_guard);
     {
       reply_data_ptr.request_id = request_id;
       reply_data_ptr.data_id = data_id++;
     }
     reply_data_ptr.refresh_rate = sleep_interval;
     reply_data_ptr.latency = (cur_link->latency);
     reply_data_ptr.available_bandwidth = ((cur_link->bandwidth*8));
     reply_data_ptr.maximum_bandwidth = ((cur_link->static_bandwidth*8));
     reply_data_ptr.type = Data_struct::link;
     string src(cur_link->src->node_name), dest(cur_link->dst->node_name);
     reply_data_ptr.source.assign ( src );
     reply_data_ptr.destination.assign ( dest );

     QMS_Remos_Msg message;
     message.insert(reply_data_ptr);
     qms_api.send(message.as_string());

     printf("\nSent a  remos graph Message");
     cout << "src -> " << src << "dest -> " << dest <<" "
	  << ((cur_link->bandwidth*8)) << "bps" << endl;

   }

  return 0;
}


/**
 * @brief Used to get flow information between two nodes.
 * @param node_names[] names of the nodes involved.
 * @param num_nodes number of nodes involved.
 * @param request_id request_id of a request.
 * @param data_id number of data messages associated with a request_id.
 * @retur returns 0 on success.
 *
 * This function uses the Remos Utility and Status functions to get the
 * path(flow) information for a set of nodes and sends this information
 * to Event Channel using qms_api.send method.
 *
 *        - Remos Utility function      remos_getidbyname
 *        - Remos Status function       remos_get_flow
 *        - remos_get_graph accepts two arguments for the start and
 *          end node of the path and fills in the structure with the
 *          informaion about this path.
 */
int
getFlowInfo(char *node_names[], int num_nodes, int request_id,
            int &data_id)
{
  remos_remulac_id node_id[MAX_NODES];
  Remos_Flow      flow[MAX_NODES][MAX_NODES];

  int i = 0,k = 0,l = 0,m = 0;
  double time = TIME_NOT_RELEVANT;
  Remos_Status stats;
  bool node_status[MAX_NODES];
  QMS_Trace ("getFlowInfo", __LINE__, __FILE__);


  for(i=0;i<num_nodes;i++)
   {
     stats = remos_getidbyname(node_names[i], 0, &(node_id[i]), &error);
     if (stats!= REMOS_OK)
      {
        errMsg("Error getting ID for node %s", node_names[i]);
        node_status[i] = false;
      }
     else
       node_status[i] = true;
   }

  for(i=0;i<num_nodes;i++)
   {
     if(node_status[i] != true)
       continue;
     for(k=i+1;k<num_nodes;k++)
      {
        if(node_status[k] != true)
          continue;
        stats = remos_get_flow(node_id[i],node_id[k],
                               &(flow[i][k]),&time,&error);
        if (stats != REMOS_OK)
          errMsg("Error getting node info %s\n", node_names[i]);
      }
   }

  for(l=0;l<num_nodes;l++)
   {

     if(node_status[l] != true)
       continue;
     for(i=0,m=l+1;m<num_nodes;m++, i++)
      {
        if(node_status[m] != true) {  continue;}
        Data_struct reply_data_ptr;

        ACE_Write_Guard<ACE_Thread_Mutex> guard(TR_asset_guard);
        {
          reply_data_ptr.request_id = request_id;
          reply_data_ptr.data_id = data_id++;
        }
        reply_data_ptr.refresh_rate = sleep_interval;
        reply_data_ptr.latency = flow[l][m]->latency;
        reply_data_ptr.available_bandwidth = (flow[l][m]->bandwidth *8);
        reply_data_ptr.maximum_bandwidth = (flow[l][m]->static_bandwidth *8);
        reply_data_ptr.type = Data_struct::flow;
        string src(flow[l][m]->src_node->hostname),
	  dest(flow[l][m]->dst_node->hostname);
        reply_data_ptr.source.assign ( src );
        reply_data_ptr.destination.assign ( dest );

        QMS_Remos_Msg message;
        message.insert(reply_data_ptr);
        qms_api.send(message.as_string());

        printf("\n Sent a remos Flow Message");
        cout << "src -> " << src << "dest -> " << dest << " "
	     << ((flow[l][m]->bandwidth *8)) <<"bps" << endl;

      }

   }

  return 0;
}


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


  if (iterations == 0)
   {
     for(;;)
      {
	if (query_data_ptr->type == Query_struct::link)
	 {
	   getGraphInfo(node_names, num_nodes, request_id, data_id);
	 }
	else
	 {
	   getFlowInfo(node_names, num_nodes, request_id, data_id);
	 }

        printf("Sleeping for %f secs \n",sleep_interval);
        printf("*********************\n");
        ACE_Time_Value sleep_time(sleep_interval, 0);
        ACE_OS::sleep (sleep_time);
      }
   }
  else
   {
     for(i=0;i<iterations;i++)
      {
	if (query_data_ptr->type == Query_struct::link)
	 {
	   getGraphInfo(node_names, num_nodes, request_id, data_id);
	 }
	else
	 {
	   getFlowInfo(node_names, num_nodes, request_id, data_id);
	 }

	if(iterations > 1)
	 {
	   printf("Sleeping for %f secs \n",sleep_interval);
	   printf("*********************\n");
	   ACE_Time_Value sleep_time(sleep_interval, 0);
	   ACE_OS::sleep (sleep_time);
	 }
      }
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

