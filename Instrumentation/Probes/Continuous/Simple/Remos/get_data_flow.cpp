// get_data_flow.cpp
// Author           : Shivakumar C. Patil (shivakumar.patil@stdc.com)
// Description      :
//

/** @file get_data_flow.cpp
 *  @ingroup RemosProbes
 *  @brief Contains implementation of a Probe that delivers Remos data
 *
 *  This file provides the implementation of a QMS sensor (complete
 *  with an interface to the QMS infrastructure) that provides an
 *  interface to Remos. This implementation also delivers periodic
 *  updates of Remos data at configurable intervals
 */

#include <unistd.h>

#include <cstring>
#include <cstdio>

#include "get_data_flow.h"
#include "Instrumentation.h"


/**
 * @brief Used to get flow information between two nodes.
 * @param node_names[] names of the nodes involved.
 * @param num_nodes number of nodes involved.
 * @param request_id request_id of a request.
 * @param data_id number of data messages associated with a request_id.
 * @param sleep_interval associated with the request message
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
char *
get_data (void *args)
{
  //QMS_Trace ("getFlowInfo", __LINE__, __FILE__);
  char *hostlist = 0, *node_names[MAX_NODES];
  char **args_pa = (char **) args;

  /// The remos data structures needed to communicate with remos to get flow topology.
  remos_remulac_id node_id[MAX_NODES];
  Remos_Flow flow[MAX_NODES][MAX_NODES];
  Remos_Status stats;
  Remos_Error error;
  bool node_status[MAX_NODES];

  /// local variables.
  int i = 0,k = 0,l = 0,m = 0, num_nodes = 0;
  double time = TIME_NOT_RELEVANT;
  char tmp[ MAXNAMELEN ], *message = 0;
  message = new char[BUFSIZ];
  static long data_id = 0;

  // parsing the command line options.
  for ( i = 1; args_pa[i] != 0 ; i++)
   {
     //fprintf (stderr, "%s\n", args_pa[i]);
     if (strcmp(args_pa[i],"-l") == 0)
      {
        hostlist = (args_pa[++i]);
        continue;
      }
   }


   for ( i = 0; i < MAX_NODES ; i++ )
         node_names[i] = 0;

  string hostnames (hostlist);
  num_nodes = StringToCharHosts(hostnames, node_names);

  for(i=0;i<num_nodes;i++)
   {
     stats = remos_getidbyname(node_names[i], 0, &(node_id[i]), &error);
     if (stats!= REMOS_OK)
      {
        fprintf(stderr,"Error getting ID for node %s", node_names[i]);
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
          fprintf(stderr,"Error getting node info %s\n", node_names[i]);
      }
   }

   sprintf(message, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<remosProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\"\n   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n   xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\n   remosProbes.xsd\">\n");

  for(l=0;l<num_nodes;l++)
   {

     if(node_status[l] != true)
       continue;
     for(i=0,m=l+1;m<num_nodes;m++, i++)
      {
        if(node_status[m] != true) {  continue;}

        sprintf(tmp,"  <bandwidthData>\n\t<flowData>\n\t  <dataID>%ld</dataID>\n\t  <source>%s</source>\n\t  <destination>%s</destination>\n\t  <latency>%.0f</latency>\n\t  <available>%.0f</available>\n\t</flowData>\n  </bandwidthData>\n", data_id++, (flow[l][m]->src_node->hostname), (flow[l][m]->dst_node->hostname), flow[l][m]->latency, (flow[l][m]->bandwidth *8));

        strcat(message,tmp);
        //cout << "src -> " << src << "dest -> " << dest << " " << ((flow[l][m]->bandwidth *8)) <<"bps" << endl;

      }

   }

   strcat(message, " </remosProbe>\n");
   strcat(message,STDC::QMS::Citizen::delimiter);
   strcat(message, "\n");
   //n = strlen(message);

   //if ( write (STDOUT_FILENO, message, n) != n)
     //    perror ("Remos_Graph_Probe: error in writing to STDOUT");

   for ( i = 0; i < MAX_NODES ; i++ )
         if (node_names[i])
            delete node_names[i];

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



