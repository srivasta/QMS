// test_client.cpp ---
// Author           : Shivakumar C. Patil (shivakumar.patil@stdc.com)

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
 *  @ingroup GenericSensor 
 *  @brief  The server/probe specific parts of the client
 *
 * This is the implementation of the communication protocol that
 * depends on the specific probe we are talking to. By separating out
 * the code in these files, we make it easier to create a client for a
 * new probe type. 
 *
 * $Id: Payload.cpp,v 1.12 2001/12/17 19:41:52 nath Exp $
 */
static const char* version = 
"$Id: Payload.cpp,v 1.12 2001/12/17 19:41:52 nath Exp $";

#include "Payload.h"

#if defined(_WIN32)
#  define snprintf _snprintf
#endif

const char *action_payload_fmt ="\
<genericCProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/Continuous/GenericProbe\"\n\
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
    xsi:schemaLocation= \"http://www.stdc.com/2001/QMS/Probes/Continuous/GenericProbe\n\
    %s\">\n\
    <probeRequest>\n\
      <probeControl>\n\
	<action>%s</action>\n\
      </probeControl>\n\
    </probeRequest>\n\
  </genericCProbe>\n\
";


const char *action_perfmon_payload_fmt ="\
<perfmonProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/perfmonProbes\"\n\
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
    xsi:schemaLocation= \"http://www.stdc.com/2001/QMS/Probes/perfmonProbes\n\
    %s\">\n\
    <perfmonRequest>\n\
      <probeControl>\n\
        <action>%s</action>\n\
      </probeControl>\n\
    </perfmonRequest>\n\
  </perfmonProbe>\n\
";

       
/**
 * @brief Handle the payload data coming back from the sensor
 * @params response_data A pointer to the data returned by the sensor
 *
 * This current implementation merely prints the sensor data out to
 * the standard out, but more complex danling can easily be done.
 */

void
payload_print(string QMSUniqueName_Host, struct Payload_Data & response_data)
{
  QMS_Trace("payload_print", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_print\n");

  cout << QMSUniqueName_Host << " : " << response_data.data_id << \
      " : " << response_data.response << endl;
}


void
perfmon_payload_print(string QMSUniqueName_Host, struct PerfMon_Payload_Data & response_data)
{
  QMS_Trace("payload_print", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_print\n");

  cout << QMSUniqueName_Host << " : " << response_data.data_id << \
      " : " << response_data.resource_name << " : " << \
      response_data.value.resource_value << endl;
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




void 
plotData_handler (IDOM_Node *node_p, struct PerfMon_Payload_Data *results_p)
{
  QMS_Trace("plotData_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: plotData_handler\n");
  
  if(!node_p)
   {
     cerr << "plotData_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }
  if(!results_p)
   {
     cerr << "plotData_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments results_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }

  IDOM_Node *child_p = node_p->getFirstChild();

  results_p->value.resource_value.erase();

  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
  
         if(strcmp(node_name_p, "numericData") == 0)
         {
            value_p = get_child_value(child_p);
            if(value_p)
             {
               results_p->value.resource_value.assign(value_p);
             }
         }

      }
     child_p = child_p->getNextSibling();
   }
}




/**
 * @brief  handle the information inside the tags resource_name,value and dataid.
 * @params node_p Pointer to name of the IDOM node.
 * @params results Reference to Data struct.
 */

void
perfmonData_handler(IDOM_Node *node_p, struct PerfMon_Payload_Data *results_p)
{
  QMS_Trace("perfmonData_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: probeData_handler\n");

  if(!node_p)
   {
     cerr << "perfmonData_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }
  if(!results_p)
   {
     cerr << "perfmonData_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments results_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }

  IDOM_Node *child_p = node_p->getFirstChild();

  results_p->data_id.erase();
  results_p->resource_name.erase();

  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;

        if(strcmp(node_name_p, "dataid") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results_p->data_id.assign(value_p);
            }
         }

        if(strcmp(node_name_p, "resource") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results_p->resource_name.assign(value_p);
            }
         }

        if(strcmp(node_name_p, "plotData") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              plotData_handler(child_p, results_p);
              
            }
         }

      }
     child_p = child_p->getNextSibling();
   }
}




/**
 * @brief  handle the information inside the tags response and dataid.
 * @params node_p Pointer to name of the IDOM node.
 * @params results Reference to Data struct.
 */ 

void
probeData_handler(IDOM_Node *node_p, struct Payload_Data *results_p)
{
  QMS_Trace("probeData_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: probeData_handler\n");

  if(!node_p)
   {
     cerr << "probeData_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }
  if(!results_p)
   {
     cerr << "probeData_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments results_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 

  IDOM_Node *child_p = node_p->getFirstChild();

  results_p->data_id.erase();
  results_p->response.erase();

  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
        if(strcmp(node_name_p, "dataid") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results_p->data_id.assign(value_p);
            } 
         } 

        if(strcmp(node_name_p, "response") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results_p->response.assign(value_p);

            } 
         } 
      } 
     child_p = child_p->getNextSibling();
   } 
}



/**
 * @brief  Handle the information inside the tag perfmonProbe.
 * @params node_p Pointer to name of the IDOM node.
 * @params results pointer to the outpput struxt
 */
void
perfmonProbe_handler(IDOM_Node *node_p, struct PerfMon_Payload_Data *results_p)
{
  QMS_Trace("perfmonProbe_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: genericCProbe_handler\n");

  if(!node_p)
   {
     cerr << "perfmonProbe_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }
  if(!results_p)
   {
     cerr << "perfmonProbe_Handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments results_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "perfmonData") == 0)
         {
           perfmonData_handler(child_p, results_p);
         }
      }
     child_p = child_p->getNextSibling();
   }
}




/**
 * @brief  Handle the information inside the tag genericCProbe.
 * @params node_p Pointer to name of the IDOM node.
 * @params results pointer to the outpput struxt
 */ 
void
genericCProbe_handler(IDOM_Node *node_p, struct Payload_Data *results_p)
{
  QMS_Trace("genericCProbe_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: genericCProbe_handler\n");

  if(!node_p)
   {
     cerr << "genericCProbe_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }
  if(!results_p)
   {
     cerr << "genericCProbe_Handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments results_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "probeData") == 0)
         {
           probeData_handler(child_p, results_p);
         } 
      } 
     child_p = child_p->getNextSibling();
   }
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

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());

        if(strcmp(node_name_p, "genericCProbe") == 0)
         {
           struct Payload_Data *results_p = (struct Payload_Data *)arg_p;
           if(!results_p)
           {
              cerr << "payload_Handler " << __LINE__ << __FILE__ << endl
                   << "Missing arguments results_p" <<endl;
              throw std::invalid_argument::invalid_argument("Missing arguments");
           }

           genericCProbe_handler(child_p, results_p);
	   success = true;
         }

        if(strcmp(node_name_p, "perfmonProbe") == 0)
         {
           struct PerfMon_Payload_Data *results_p = (struct PerfMon_Payload_Data *)arg_p;
           if(!results_p)
           {
              cerr << "payload_Handler " << __LINE__ << __FILE__ << endl
                   << "Missing arguments results_p" <<endl;
              throw std::invalid_argument::invalid_argument("Missing arguments");
           }

           perfmonProbe_handler(child_p, results_p);
           success = true;
         }
            
      } 
     child_p = child_p->getNextSibling();
   } 
  return success;
}

char * 
payload_generator(string &probe_schema_uri, const char *action)
{
  QMS_Trace("payload_generator", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_generator\n");
  int ret = 0;
  char * payload_p = new char[ BUFSIZ + 8192 ];
  if(action)
   {
     ret =
       snprintf(payload_p, BUFSIZ + 8192, action_payload_fmt, probe_schema_uri.c_str(),
		action);
   } 

  return payload_p;
}




char * 
perfmon_payload_generator(string &probe_schema_uri, const char *action)
{
  QMS_Trace("payload_generator", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_generator\n");
  int ret = 0;
  char * payload_p = new char[ BUFSIZ + 8192 ];
  if(action)
   {
     ret =
       snprintf(payload_p, BUFSIZ + 8192, action_perfmon_payload_fmt, 
                                            probe_schema_uri.c_str(),
		                                             action);
   } 

  return payload_p;
}
