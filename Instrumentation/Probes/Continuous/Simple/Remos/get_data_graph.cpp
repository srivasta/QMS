// get_data_graph.cpp
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


/** @file get_data_graph.cpp
 *  @ingroup RemosProbes
 *  @brief Contains implementation of a Probe that delivers Remos graph data
 *
 *  This file provides the implementation of a QMS sensor (complete
 *  with an interface to the QMS infrastructure) that provides an
 *  interface to Remos. This implementation also delivers periodic
 *  updates of Remos data at configurable intervals
 */

#include <unistd.h>

#include <cstring>
#include <cstdio>

#include "get_data_graph.h"
#include "Instrumentation.h"

/**
 * @brief  Used to get Graph information of a node w.r.t to switch.
 * @param  node_names[] names of the nodes involved.
 * @param  num_nodes number of nodes involved.
 * @param  request_id request_id of a request.
 * @param  data_id number of data messages associated with a request_id.
 * @param  sleep_interval associated with the request message.
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
char *
get_data (void *args)
{
  //QMS_Trace ("getGraphInfo", __LINE__, __FILE__);
  char *hostlist = 0, *node_names[MAX_NODES];
  char **args_pa = (char **) args;

  /// The remos data structures needed to communicate with remos to get graph 
  /// topology.
  Remos_Node      node[MAX_NODES];
  Remos_Graph     graph;
  Remos_Error error;
  remos_remulac_id node_id[MAX_NODES];
  Remos_Status stats;
  Remos_Node_List node_list;
  Remos_Link cur_link;

  /// local variables.
  int i = 0, j = 0, num_nodes;
  double time = 0;
  char tmp[ MAXNAMELEN ], *message = 0;
  message = new char [BUFSIZ];
  static long data_id = 0;

  // parsing the command line options.
  for ( int i = 1; args_pa[i] != 0 ; i++)
   {
     //fprintf (stderr, "%s\n", args_pa[i]);
     if (strcmp(args_pa[i],"-l") == 0)
      {
        hostlist = (args_pa[++i]);
        continue;
      }
   }

  for ( j = 0; j < MAX_NODES ; j++ )
         node_names[j] = 0;

  string hostnames (hostlist);
  num_nodes = StringToCharHosts(hostnames, node_names);

  node_list = (Remos_Node_List)remos_new_list(num_nodes);

  for(i=0; i < num_nodes; i++)
   {

     stats = remos_getidbyname(node_names[i], 0, &(node_id[i]), &error);
     if (stats != REMOS_OK)
      {
        fprintf(stderr,"Error getting ID for node %s", node_names[i]);
      }

     stats = remos_get_node(node_id[i], &(node[i]), &time, &error);
     if (stats != REMOS_OK)
      {
        fprintf(stderr,"Error getting Node Info for node %s", node_names[i]);
      }
     else
      {
        remos_list_append(node[i],node_list);
      }

   }

  stats = remos_get_graph(node_list,&graph,&time,TRUE,&error);
  if(stats != REMOS_OK)
   {
     fprintf(stderr,"Prob getting graph...in iteration %d \n",i);
   }

   sprintf(message, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<remosProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\"\n   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n   xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\n   remosProbes.xsd\">\n");

  for(j=0;j<graph->edges->elem_count;j++)
   {
     cur_link = graph->edges->list[j];

  // Make sure that we don't pass through negative bandwidth information
  // since the schema prohibits it.
     sprintf(tmp,"  <bandwidthData>\n\t<linkData>\n\t  <dataID>%ld</dataID>\n\t  <source>%s</source>\n\t  <destination>%s</destination>\n\t  <latency>%.0f</latency>\n\t  <available>%.0f</available>\n\t  <maximum>%.0f</maximum>\n\t</linkData>\n  </bandwidthData>\n", data_id++, (cur_link->src->node_name), (cur_link->dst->node_name), cur_link->latency, ( (cur_link->bandwidth < 0) ? 0 : (cur_link->bandwidth*8)), (cur_link->static_bandwidth*8));

     //cout << "src -> " << src << "dest -> " << dest <<" " << ((cur_link->bandwidth*8)) << "bps" << endl;

     strcat(message,tmp);

   }

   strcat(message, " </remosProbe>\n");
   strcat(message,STDC::QMS::Citizen::delimiter);
   strcat(message, "\n");
   //n = strlen(message);

   //if ( write (STDOUT_FILENO, message, n) != n)
         //perror ("Remos_Graph_Probe: error in writing to STDOUT");

   for ( j = 0; j < MAX_NODES ; j++ )
         if (node_names[j])
            delete node_names[j];

   return message;

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
           //cout << "node " << node_names[i] << endl;
           i++;

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
           //cout << "node " << node_names[i] << endl;
           i++;

           start = location +1;
         }
      }
     num_nodes = i;
     //cout << "num_nodes -> " << num_nodes << endl;
   }
   return num_nodes;
}



