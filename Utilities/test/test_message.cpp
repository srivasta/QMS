//                              -*- Mode: C++ -*- 
// test_message.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Wed Oct  3 16:44:41 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Nov 17 23:35:10 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 15
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


/// RCS version string
static const char* version = 
"$Id: test_message.cpp,v 1.8 2001/12/02 03:30:27 srivasta Exp $";

#include <exception>


#include "Parse_XML.h"
static const char*  message_p = 
"\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>                                 \n\
<qms:QMSMessage xmlns=\"http://www.stdc.com/2001/QMSSchema\"               \n\
  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"                  \n\
  xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"                         \n\
  xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema QMSSchema.xsd\"> \n\
  <qms:msgSequenceNo>1001</qms:msgSequenceNo>                              \n\
  <qms:msgDate>2001-09-18</qms:msgDate>                                    \n\
  <qms:msgTime>15:05:05-05:00</qms:msgTime>                                \n\
  <qms:originatingHost>192.168.200.1</qms:originatingHost>                 \n\
  <qms:msgSender>                                                          \n\
    <id>100002</id>                                                        \n\
    <description>Hello World Client</description>                          \n\
  </qms:msgSender>                                                         \n\
  <qms:QMSUniqueName>                                                      \n\
    <category>HelloWorld</category>                                        \n\
  </qms:QMSUniqueName>                                                     \n\
  <qms:Session>                                                            \n\
    <requestID>1</requestID>                                               \n\
    <version>0</version>                                                   \n\
    <minRepetitions>                                                       \n\
      <count>1</count>                                                     \n\
    </minRepetitions>                                                      \n\
    <minRepeatInterval>PT0S</minRepeatInterval>                            \n\
  </qms:Session>                                                           \n\
  <qms:payload>                                                            \n\
    <helloWorld xmlns=\"http://www.stdc.com/2001/QMS/helloWorld\"          \n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"              \n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/helloWorld         \n\
      helloWorld.xsd\">                                                    \n\
      <Request>                                                            \n\
        <firstname>Foo</firstname>                                         \n\
        <lastname>Bar</lastname>                                           \n\
      </Request>                                                           \n\
    </helloWorld>                                                          \n\
  </qms:payload>                                                           \n\
</qms:QMSMessage>                                                          \n\
";


struct Request 
{
  string firstname;
  string lastname;
  string action;
};

struct helloWorld
{
  struct Request request;
};
  

struct payload_data 
{
  struct helloWorld data;
};

const char *
get_node_type(IDOM_Node *doc_p)
{
  switch(doc_p->getNodeType())
   {
       case IDOM_Node::ELEMENT_NODE:
         return "Type=[ELEMENT_NODE]";
         break;
   
       case IDOM_Node::ATTRIBUTE_NODE :
         return "Type=[ATTRIBUTE_NODE]";
         break;
         
       case IDOM_Node::TEXT_NODE:
        return "Type=[TEXT_NODE]";
         break;
         
       case IDOM_Node::CDATA_SECTION_NODE:
        return "Type=[CDATA_SECTION_NODE]";
         break;
         
       case IDOM_Node::ENTITY_REFERENCE_NODE:
        return "Type=[ENTITY_REFERENCE_NODE]";
         break;
         
       case IDOM_Node::ENTITY_NODE:
        return "Type=[ENTITY_NODE]";
         break;
         
       case IDOM_Node::PROCESSING_INSTRUCTION_NODE:
        return "Type=[PROCESSING_INSTRUCTION_NODE]";
         break;
         
       case IDOM_Node::COMMENT_NODE:
        return "Type=[COMMENT_NODE]";
         break;
         
       case IDOM_Node::DOCUMENT_NODE:
        return "Type=[DOCUMENT_NODE]";
         break;
         
       case IDOM_Node::DOCUMENT_TYPE_NODE:
        return "Type=[DOCUMENT_TYPE_NODE]";
         break;
         
       case IDOM_Node::DOCUMENT_FRAGMENT_NODE:
        return "Type=[DOCUMENT_FRAGMENT_NODE]";
         break;
         
         
       case IDOM_Node::XML_DECL_NODE:
        return "Type=[XML_DECL_NODE]";
         break;
         
       default:
        return "Type=[Unknown]";
         break;
   } /* end of switch(doc_p->getNodeType()) */
}


void
print_node_details(IDOM_Node *node_p)
{
  cout << get_node_type(node_p)
       << ";\tName=["   << (char *)XMLString::transcode(node_p->getNodeName())
       << "];\tValue=[" << (char *)XMLString::transcode(node_p->getNodeValue())
       << "]\n" ;
}

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
request_handler(IDOM_Node *node_p, struct Request results)
{
  QMS_Trace("request_Handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: request_Handler\n");

  if(!node_p)
   {
     cerr << "ayload_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  // Do we have attributes for this element?
  IDOM_NamedNodeMap *attr_p = node_p->getAttributes();
  int num_attr = attr_p->getLength();
  int i = 0;
  for(i = 0; i <  num_attr; i++)
   {
     IDOM_Node  *attribute_p = attr_p->item(i);
     cout << "====Attribute " << i << "====\n";
     print_node_details(attribute_p);
   } /* end of for(i = 0; i <  num_attr; i++) */

  IDOM_Node *child_p = node_p->getFirstChild();
  results.firstname.erase();
  results.lastname.erase();
  results.action.erase();
  int childnum = 0;
  while(child_p != 0)
   {
     cout << "Child number " << ++childnum << endl;
     print_node_details(child_p);
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p = 0;
	if(strcmp(node_name_p, "firstname") == 0)
         {
	   value_p = get_child_value(child_p);
	   if(value_p)
            {
              results.firstname.assign(value_p);
	      cout << "\t\t\tFirst Name: " << value_p << endl;
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "firstname") == 0) */
	if(strcmp(node_name_p, "lastname") == 0)
         {
	   value_p = get_child_value(child_p);
	   if(value_p)
            {
              results.lastname.assign(value_p);
	      cout << "\t\t\tLast Name: " << value_p << endl;
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "lastname") == 0) */
	if(strcmp(node_name_p, "action") == 0)
         {
	   value_p = get_child_value(child_p);
	   if(value_p)
            {
              results.action.assign(value_p);
	      cout << "\t\t\tAction: " << value_p << endl;	      
            } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "lastname") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


void
helloWorld_handler(IDOM_Node *node_p, struct helloWorld results)
{
  QMS_Trace("helloWorld_handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: helloWorld_handler\n");

  if(!node_p)
   {
     cerr << "ayload_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  // Do we have attributes for this element?
  IDOM_NamedNodeMap *attr_p = node_p->getAttributes();
  int num_attr = attr_p->getLength();
  int i = 0;
  for(i = 0; i <  num_attr; i++)
   {
     IDOM_Node  *attribute_p = attr_p->item(i);
     cout << "====Attribute " << i << "====\n";
     print_node_details(attribute_p);
   } /* end of for(i = 0; i <  num_attr; i++) */

  IDOM_Node *child_p = node_p->getFirstChild();
  int childnum = 0;
  while(child_p != 0)
   {
     cout << "Child number " << ++childnum << endl;
     print_node_details(child_p);
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "Request") == 0)
         {
           request_handler(child_p, results.request);
         } /* end of if(strcmp(node_name_p, "helloWorld") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

bool
payload_Handler(IDOM_Node *node_p, void *arg_p)
{
  QMS_Trace("payload_Handler", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: payload_Handler\n");
  bool success = false;
  
  struct payload_data *results_p = (struct payload_data *)arg_p;
  if(!node_p)
   {
     cerr << "ayload_Handler " << __LINE__ << __FILE__ << endl 
	  << "Missing arguments" <<endl;
     throw std::invalid_argument::invalid_argument("Missing arguments");
   } 
  // Do we have attributes for this element?
  IDOM_NamedNodeMap *attr_p = node_p->getAttributes();
  int num_attr = attr_p->getLength();
  int i = 0;
  for(i = 0; i <  num_attr; i++)
   {
     IDOM_Node  *attribute_p = attr_p->item(i);
     cout << "====Attribute " << i << "====\n";
     print_node_details(attribute_p);
   } /* end of for(i = 0; i <  num_attr; i++) */

  IDOM_Node *child_p = node_p->getFirstChild();
  int childnum = 0;
  while(child_p != 0)
   {
     cout << "Child number " << ++childnum << endl;
     print_node_details(child_p);
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "helloWorld") == 0)
         {
           helloWorld_handler(child_p, results_p->data);
	   success = true;
         } /* end of if(strcmp(node_name_p, "helloWorld") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
  return success;
}




int
main(int argc, char *argv[])
{
  char *filename_p = 0;

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
        filename_p = (char *) malloc (strlen(argv[i + 1]) + 1);
        strcpy(filename_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (DEBUG_L_ARGS, "unknown argument %s", argv[i] );
   }
  
  // Initialize the Parser. 
  try 
   {
     XMLPlatformUtils::Initialize();
   }
  catch(const XMLException& toCatch)
   {
     cerr << "Error during Xerces-c Initialization.\n"
          << "  Exception message:"
          << toCatch.getMessage()
          << endl;
     return 1;
   }

  STDC::QMS::Parse_XML *my_parser = 
    new STDC::QMS::Parse_XML::Parse_XML();

  MemBufInputSource *buffer_p = new MemBufInputSource((const XMLByte*) 
                                                      message_p,
                                                      strlen(message_p),
                                                      "QMSMessage",
                                                      false);

  struct payload_data request_data;

  STDC::QMS::QMSMessage config;
  bool parsed_message = my_parser->parse_message(*buffer_p, config, 
						 payload_Handler,
						 (void *) &request_data);
  
  if(parsed_message)
   {
     
   } /* end of if(parsed_message) */
  // Terminate the parser before the end. This belongs in a destructor
  XMLPlatformUtils::Terminate();
  exit(EXIT_SUCCESS);             
} /* end of main() */
