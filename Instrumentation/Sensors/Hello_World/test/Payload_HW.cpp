//                              -*- Mode: C++ -*- 
// Payload.cpp --- 
// Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
// Created On       : Sat Oct 27 15:36:01 2001
// Created On Node  : ember.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Dec  1 03:17:29 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 10
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

/** @file 
 *  @ingroup HelloWorld 
 *  @brief  The server/probe specific parts of the client
 *
 * This is the implementation of the communication protocol that
 * depends on the specific probe we are talking to. By separating out
 * the code in these files, we make it easier to create a client for a
 * new probe type. 
 *
 * $Id: Payload_HW.cpp,v 1.6 2001/12/04 23:27:58 nath Exp $
 */
/// RCS version string
static const char* version = 
"$Id: Payload_HW.cpp,v 1.6 2001/12/04 23:27:58 nath Exp $";

#include "Payload_HW.h"

#if defined(_WIN32)
#  define snprintf _snprintf
#endif


const char *request_payload_fmt = "\
    <helloWorld xmlns=\"http://www.stdc.com/2001/QMS/helloWorld\"\n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/helloWorld\n\
      %s\">\n\
      <Request>\n\
        <firstname>John</firstname>\n\
        <lastname>Doe</lastname>\n\
      </Request>\n\
    </helloWorld>\n\
";

const char *action_payload_fmt = "\
    <helloWorld xmlns=\"http://www.stdc.com/2001/QMS/helloWorld\"\n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/helloWorld\n\
      %s\">\n\
      <Request>\n\
        <action>%s</action>\n\
      </Request>\n\
    </helloWorld>\n\
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
  
  cout << response_data.data_id << "\t\t" << response_data.salutation << endl;
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
 * @brief  handle the information inside the tags salutation and dataid.
 * @params node_p Pointer to name of the IDOM node.
 * @params results Reference to Data struct.
 */ 

void
data_handler(IDOM_Node *node_p, struct Payload_Data *results_p)
{
  QMS_Trace("data_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: data_handler\n");

  if(!node_p)
   {
     cerr << "data_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }
  if(!results_p)
   {
     cerr << "data_Handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments results_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } /* end of if(!results_p) */

  IDOM_Node *child_p = node_p->getFirstChild();

  results_p->data_id.erase();
  results_p->salutation.erase();

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
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "dataid") == 0) */

        if(strcmp(node_name_p, "salutation") == 0)
         {
           value_p = get_child_value(child_p);
           if(value_p)
            {
              results_p->salutation.assign(value_p);
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "salutation") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
}


/**
 * @brief  Handle the information inside the tag helloWorld.
 * @params node_p Pointer to name of the IDOM node.
 * @params results pointer to the outpput struxt
 */ 
void
helloWorld_handler(IDOM_Node *node_p, struct Payload_Data *results_p)
{
  QMS_Trace("helloWorld_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: helloWorld_handler\n");

  if(!node_p)
   {
     cerr << "helloWorld_handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   }
  if(!results_p)
   {
     cerr << "helloWorld_Handler " << __LINE__ << __FILE__ << endl
          << "Missing arguments results_p" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } /* end of if(!results_p) */

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "Data") == 0)
         {
           data_handler(child_p, results_p);
         } /* end of if(strcmp(node_name_p, "helloWorld") == 0) */
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

  results_p->data_id.erase();
  results_p->salutation.erase();

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "helloWorld") == 0)
         {
           helloWorld_handler(child_p, results_p);
	   success = true;
         } /* end of if(strcmp(node_name_p, "helloWorld") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
  return success;
}

char * 
payload_generator(string &probe_schema_uri, const char *action)
{
  QMS_Trace("payload_generator", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_generator\n");
  int ret = 0;
  char * payload_p = new char[1024];
  if(action)
   {
     ret =
       snprintf(payload_p, 1024, action_payload_fmt, probe_schema_uri.c_str(),
		action);
   } /* end of if(action) */
  else
   {
     ret =
       snprintf(payload_p, 1024, request_payload_fmt,
		probe_schema_uri.c_str());
     
   } /* end of else */
  return payload_p;
}
