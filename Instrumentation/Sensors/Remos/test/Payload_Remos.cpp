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
 *  @ingroup RemosSensor 
 *  @brief  The server/probe specific parts of the client
 *
 * This is the implementation of the communication protocol that
 * depends on the specific probe we are talking to. By separating out
 * the code in these files, we make it easier to create a client for a
 * new probe type. 
 *
 * $Id: Payload_Remos.cpp,v 1.7 2001/12/06 00:42:57 nath Exp $
 */
/// RCS version string
static const char* version = 
"$Id: Payload_Remos.cpp,v 1.7 2001/12/06 00:42:57 nath Exp $";

#include "Payload_Remos.h"

#if defined(_WIN32)
#  define snprintf _snprintf
#endif


const char *flow_payload_fmt = "\
    <remosProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\"\n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\n\
      %s\">\n\
      <bandwidthRequest>\n\
        <flowRequest>\n\
%s\n\
        </flowRequest>\n\
      </bandwidthRequest>\n\
    </remosProbe>\n\
";
          

const char *graph_payload_fmt = "\
    <remosProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\"\n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\n\
      %s\">\n\
      <bandwidthRequest>\n\
        <linkRequest>\n\
%s\n\
        </linkRequest>\n\
      </bandwidthRequest>\n\
    </remosProbe>\n\
";

const char *action_payload_fmt = "\
    <remosProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\"\n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/RemosProbes\n\
      %s\">\n\
      <bandwidthRequest>\n\
        <probeControl>\n\
          <action>%s</action>\n\
        </probeControl>\n\
      </bandwidthRequest>\n\
    </remosProbe>\n\
";



/**
 * @brief Handle the payload data coming back from the sensor
 * @params response_data A pointer to the data returned by the sensor
 *
 * This current implementation merely prints the sensor data out to
 * the standard out, but more complex danling can easily be done.
 */

void
payload_print(struct Payload_Data & response_data)
{
  QMS_Trace("payload_print", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_print\n");

  for (unsigned int i = 0; i < response_data.remos_data.bandwidth_data.size() ; i++ )
   {
       if ( response_data.remos_data.bandwidth_data[i] != NULL )
        {
           cerr << response_data.remos_data.bandwidth_data[i]->linkdata.dataID << endl;
           cerr << response_data.remos_data.bandwidth_data[i]->linkdata.source << endl;
           cerr << response_data.remos_data.bandwidth_data[i]->linkdata.destination << endl;
           cerr << response_data.remos_data.bandwidth_data[i]->linkdata.latency << endl;
           cerr << response_data.remos_data.bandwidth_data[i]->linkdata.available << endl;
           cerr << response_data.remos_data.bandwidth_data[i]->linkdata.maximum << endl;

           //cerr << "deleting i-> " << i << endl ;
           //delete response_data.remos_data.bandwidth_data[i];
        }
    }
 
}

/**
 * @brief return the value of a child node
 * @params node_p A pointer to the node of interest
 * @return Returns the pointer to leaf node.
 *
 * Generally used to get values of leaf nodes
 */
char *
get_child_value(IDOM_Node *node_p)
{
  IDOM_Node *child_p = node_p->getFirstChild();
  if(child_p != 0)
   {
     return (char *)XMLString::transcode(child_p->getNodeValue());
   } /* end of if(child_p != 0) */
  else
   {
     return 0;
   } /* end of else */
}

/**
 * @brief  handle the information inside the tag linkData.
 * @params node_p Pointer to name of the IDOM node.
 * @params results Reference to Data struct.
 */ 

void
linkData_handler(IDOM_Node *node_p, struct linkData & results)
{
  QMS_Trace("linkData_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: linkData_handler\n");

  if(!node_p)
   {
     cerr << "linkData_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }

  IDOM_Node *child_p = node_p->getFirstChild();

  results.dataID.erase();
  results.source.erase();
  results.destination.erase();
  results.latency.erase();
  results.available.erase();
  results.maximum.erase();

  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;

        if(strcmp(node_name_p, "dataID") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results.dataID.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "dataID") == 0) */

        if(strcmp(node_name_p, "source") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results.source.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "source") == 0) */

        if(strcmp(node_name_p, "destination") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results.destination.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "destination") == 0) */

        if(strcmp(node_name_p, "latency") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results.latency.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "latency") == 0) */

        if(strcmp(node_name_p, "available") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results.available.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "available") == 0) */

        if(strcmp(node_name_p, "maximum") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results.maximum.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "maximum") == 0) */

      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}



/**
 * @brief  Handle the information inside the tag bandwidthData.
 * @params node_p Pointer to name of the IDOM node.
 * @params results pointer to the outpput struxt
 */
void
bandwidthData_handler(IDOM_Node *node_p, struct bandwidthData  &results)
{
  QMS_Trace("bandwidthData_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: bandwidthData_handler\n");

  if(!node_p)
   {
     cerr << "bandwidthData_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "linkData") == 0)
         {

           linkData_handler(child_p, results.linkdata);

         } /* end of if(strcmp(node_name_p, "linkData") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}




/**
 * @brief  Handle the information inside the tag remosProbe.
 * @params node_p Pointer to name of the IDOM node.
 * @params results pointer to the outpput struxt
 */ 
void
remosProbe_handler(IDOM_Node *node_p, struct RemosData &results)
{
  QMS_Trace("remosProbe_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: remosProbe_handler\n");

  if(!node_p)
   {
     cerr << "remosProbe_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "bandwidthData") == 0)
         {
           struct bandwidthData *bandwidth_data_p = new struct bandwidthData; 
           try 
           {
              bandwidthData_handler(child_p, *bandwidth_data_p);
           }
           catch (const invalid_argument & ex)
           {
              delete bandwidth_data_p;
              throw;
           }
           results.bandwidth_data.push_back(bandwidth_data_p);

         } /* end of if(strcmp(node_name_p, "bandwidthData") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}

/**
 * @brief  handle the QMS Payload information under the tag qms:payload.
 * @params node_p Pointer to name of the IDOM node .
 * @param  arg_p void pointer to the Payload_Data structure.
 * @return true on success
 */
bool
payload_Handler(IDOM_Node *node_p, void * arg_p)
{
  QMS_Trace("payload_Handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_Handler\n");
  bool success = false;
  
  struct Payload_Data *results_p = (struct Payload_Data *)arg_p;
  if(!results_p)
   {
     cerr << "payload_Handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments results_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } /* end of if(!results_p) */

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "remosProbe") == 0)
         {
	   remosProbe_handler(child_p, results_p->remos_data);
	   success = true;
         } /* end of if(strcmp(node_name_p, "remosProbe") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();

   } /* end of while(child != 0) */
  return success;
}

char * 
payload_generator(string &probe_schema_uri, list<string> & hosts, const char *action)
{
  QMS_Trace("payload_generator", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_generator\n");
  int ret = 0;
  char * payload_p = new char[4096];

  string hostnames;
  hostnames.erase();
  
  if (action)
   {
      ret =
       snprintf(payload_p, 4096, action_payload_fmt, probe_schema_uri.c_str(),
                action);
   } /* end of if(action) */
   else
   {

       list<string>::const_iterator iter;
       for (iter = hosts.begin(); iter != hosts.end(); iter++)
       {
           hostnames.append("\t  <hostname>");
           hostnames.append(*iter);
           hostnames.append("</hostname>\n");
       }
 
       ret = snprintf(payload_p, 4096, graph_payload_fmt, probe_schema_uri.c_str(),
	                 	hostnames.c_str());
   }

  return payload_p;
}

void
payload_clean( struct Payload_Data & response_data)
{
   for (unsigned int i = 0; i < response_data.remos_data.bandwidth_data.size() ; i++ )
     {
                if ( response_data.remos_data.bandwidth_data[i] != NULL )

                            delete response_data.remos_data.bandwidth_data[i];
     }

}


#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class vector<bandwidthData *>;

template void fill<bandwidthData **, bandwidthData *>(bandwidthData **, bandwidthData **, bandwidthData * const &);

template bandwidthData ** fill_n<bandwidthData **, unsigned int, bandwidthData *>(bandwidthData **, unsigned int, bandwidthData * const &);

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

