//                              -*- Mode: C++ -*- 
// test_XML.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Thu Aug 23 15:06:32 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Oct 20 02:38:22 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 77
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// 
// 

/** @file 
 *  @ingroup GenericSensor 
 *  @brief implementation of a test program
 *
 * $Id: test_XML.cpp,v 1.5 2001/12/09 02:06:24 nath Exp $
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



/// RCS version string
static const char* 
version = "$Id: test_XML.cpp,v 1.5 2001/12/09 02:06:24 nath Exp $";

#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>

#include <idom/IDOM.hpp>
#include <idom/IDOM_DOMException.hpp>
#include <parsers/IDOMParser.hpp>
#include <util/PlatformUtils.hpp>
#include <framework/MemBufInputSource.hpp>


#include "Debug.h"




#include <util/XercesDefs.hpp>
#include <sax/SAXParseException.hpp>
#include <sax/ErrorHandler.hpp>


static const char*  message_p = 
"\
<?xml version='1.0' encoding='us-ascii'?>\n\
<!DOCTYPE QMS_Event SYSTEM 'QMS_Event.dtd'>\n\
<QMS_Event>\n\
<SequenceNo>1001</SequenceNo>\n\
<SenderID>Remoshost</SenderID>\n\
<EventDate>10/2/2000</EventDate>\n\
<EventTime>10:00:00am</EventTime>\n\
<EventType>NETWORK_BANDWIDTH</EventType>\n\
<EventData>\n\
   <bandwidth_request linktype=\"flow\">\n\
      <requestid>11021</requestid>\n\
      <hostname>desinode1</hostname>\n\
      <hostname>desinode2</hostname>\n\
      <refreshrate>5</refreshrate>\n\
   </bandwidth_request>\n\
   <bandwidth_request>\n\
      <requestid>11023</requestid>\n\
      <hostname>desinode3</hostname>\n\
      <hostname>desinode4</hostname>\n\
      <hostname>desinode1</hostname>\n\
   </bandwidth_request>\n\
   <bandwidth_request linktype=\"link\">\n\
      <requestid>11027</requestid>\n\
      <hostname>desinode5</hostname>\n\
      <refreshrate units=\"sec\">100</refreshrate>\n\
   </bandwidth_request>\n\
</EventData>\n\
</QMS_Event>\n\
";



class IDOMTreeErrorReporter : public ErrorHandler
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  IDOMTreeErrorReporter() : fSawErrors(false){}

  ~IDOMTreeErrorReporter(){}

  // -----------------------------------------------------------------------
  //  Implementation of the error handler interface
  // -----------------------------------------------------------------------
  void warning(const SAXParseException& toCatch)
  {
    cerr << "Warning at file \"" 
	 << toCatch.getSystemId()
	 << "\", line " << toCatch.getLineNumber()
	 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << toCatch.getMessage()
	 << endl;
  };

  void error(const SAXParseException& toCatch){
    fSawErrors = true;
    cerr << "Error at file \"" 
	 << toCatch.getSystemId()
	 << "\", line " << toCatch.getLineNumber()
	 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << toCatch.getMessage()
	 << endl;
  };

  void fatalError(const SAXParseException& toCatch){
    fSawErrors = true;
    cerr << "Fatal Error at file \"" 
	 << toCatch.getSystemId()
	 << "\", line " << toCatch.getLineNumber()
	 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << toCatch.getMessage()
	 << endl;
  };
  void resetErrors(){};
  
  // -----------------------------------------------------------------------
  //  Getter methods
  // -----------------------------------------------------------------------
  bool getSawErrors() const;

  // -----------------------------------------------------------------------
  //  Private data members
  //
  //  fSawErrors
  //      This is set if we get any errors, and is queryable via a getter
  //      method. Its used by the main code to suppress output if there are
  //      errors.
  // -----------------------------------------------------------------------
  bool    fSawErrors;
};

inline bool IDOMTreeErrorReporter::getSawErrors() const
{
  return fSawErrors;
}


/*
 * enum NodeType {
 *      ELEMENT_NODE                = 1,
 *      ATTRIBUTE_NODE              = 2,
 *      TEXT_NODE                   = 3,
 *      CDATA_SECTION_NODE          = 4,
 *      ENTITY_REFERENCE_NODE       = 5,
 *      ENTITY_NODE                 = 6,
 *      PROCESSING_INSTRUCTION_NODE = 7,
 *      COMMENT_NODE                = 8,
 *      DOCUMENT_NODE               = 9,
 *      DOCUMENT_TYPE_NODE          = 10,
 *      DOCUMENT_FRAGMENT_NODE      = 11,
 *      NOTATION_NODE               = 12,
 *      XML_DECL_NODE               = 13
 *  };
 */


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

void
sequence_element_handler(IDOM_Node *node_p)
{
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
     cout << "\n\tGreat Grand Child number " << ++childnum << endl;
     print_node_details(child_p);
     
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
  
}

void
sender_id_element_handler(IDOM_Node *node_p)
{
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
     cout << "\n\tGreat Grand Child number " << ++childnum << endl;
     print_node_details(child_p);
     
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
  
}

void
event_date_element_handler(IDOM_Node *node_p)
{
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
     cout << "\n\tGreat Grand Child number " << ++childnum << endl;
     print_node_details(child_p);
     
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
  
}

void
event_time_element_handler(IDOM_Node *node_p)
{
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
     cout << "\n\tGreat Grand Child number " << ++childnum << endl;
     print_node_details(child_p);
     
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
  
}

void
event_type_element_handler(IDOM_Node *node_p)
{
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
     cout << "\n\tGreat Grand Child number " << ++childnum << endl;
     print_node_details(child_p);
     
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
  
}


void 
qms_data_element_handler(IDOM_Node *node_p)
{
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
     cout << "\n\tGrand Child number " << ++childnum << endl;
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
	char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "SequenceNo") == 0)
	 {
	   sequence_element_handler(child_p);
	 } /* end of if(strcmp(node_name_p, "SequenceNo") == 0) */

	if(strcmp(node_name_p, "SenderID") == 0)
	 {
	   sender_id_element_handler(child_p);
	 } /* end of if(strcmp(node_name_p, "SenderID") == 0) */
	
	if(strcmp(node_name_p, "EventDate") == 0)
	 {
	   event_date_element_handler(child_p);
	 } /* end of if(strcmp(node_name_p, "EventDate") == 0) */
	
	
	if(strcmp(node_name_p, "EventTime") == 0)
	 {
	   event_time_element_handler(child_p);
	 } /* end of if(strcmp(node_name_p, "EventTime") == 0) */
	
	
	if(strcmp(node_name_p, "EventType") == 0)
	 {
	   event_type_element_handler(child_p);
	 } /* end of if(strcmp(node_name_p, "EventType") == 0) */
	
	// We don't really want to peek into event data
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
  
}


void
doc_handler (IDOM_Node *doc_p)
{
  // The top level node is unnamed, and is a DOCUMENT_NODE
  cout << "====The Top level node==\n";
  print_node_details(doc_p);
  cout << "\n====The children, now==\n";
  
  // We now look towards the children
  IDOM_Node *child_p = doc_p->getFirstChild();
  int childnum = 0;
  while(child_p != 0)
   {
     cout << "\n\n\tChild number " << ++childnum << endl;
     print_node_details(child_p);

     // Handle the nodes here. We have first a DOCUMENT_TYPE_NODE, and
     // then a ELEMENT_NODE. We probably do not want to deal with the
     // DTD here (the parser has done all we need to take care of). 
     
     if(child_p->getNodeType() == IDOM_Node::ELEMENT_NODE)
      {
	qms_data_element_handler(child_p);
      } /* end of if(doc_p->getNodeType() == IDOM_Node::ELEMENT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */
  
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
        filename_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
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
  
  
  //
  //  Create our parser, then attach an error handler to the parser.
  //  The parser will call back to methods of the ErrorHandler if it
  //  discovers errors during the course of parsing the XML document.
  //
  IDOMParser *parser = new IDOMParser;
  parser->setValidationScheme(IDOMParser::Val_Auto);
  parser->setDoNamespaces(false);
  parser->setDoSchema(false);

  IDOMTreeErrorReporter *errReporter = new IDOMTreeErrorReporter();
  
  parser->setErrorHandler(errReporter);
  parser->setCreateEntityReferenceNodes(false);

  //
  //  Create MemBufferInputSource from the buffer containing the XML
  //  statements.
  //
  //  NOTE: We are using strlen() here, since we know that the chars in
  //  our hard coded buffer are single byte chars!!! The parameter wants
  //  the number of BYTES, not chars, so when you create a memory buffer
  //  give it the byte size (which just happens to be the same here.)
  //
  MemBufInputSource *buffer_p = new MemBufInputSource((const XMLByte*) 
						      message_p,
						      strlen(message_p),
						      "QMSMessage",
						      false);
  

  //
  //  Parse the XML file, catching any XML exceptions that might propogate
  //  out of it.
  //
  bool errorsOccured = false;
  try
   {
     parser->parse(*buffer_p);
     int errorCount = parser->getErrorCount();
     if (errorCount > 0)
       errorsOccured = true;
   }
  catch (const XMLException& e)
   {
     cerr << "An error occured during parsing\n   Message: "
	  << e.getMessage() << endl;
     errorsOccured = true;
   }
  catch (const IDOM_DOMException& e)
   {
     cerr << "A IDOM error occured during parsing\n   IDOMException code: "
	  << e.code << endl;
     errorsOccured = true;
   }
  catch (...)
   {
     cerr << "An error occured during parsing\n " << endl;
     errorsOccured = true;
   }

  // If there are no errors, we handle the message
  if(!errorsOccured && !errReporter->getSawErrors())
   {
     IDOM_Node *doc_p = parser->getDocument();
     
     doc_handler(doc_p);
     
     delete doc_p;
   } /* end of if(!errorsOccured && !errReporter->getSawErrors()) */

  /*
   *  Clean up the error handler. The parser does not adopt handlers
   *  since they could be many objects or one object installed for multiple
   *  handlers.
   */
  delete errReporter;
  
  /*
   * Delete the parser itself.  Must be done prior to calling
   * Terminate, below.  
   */
  delete parser;

  // Terminate the parser before the end. This belongs in a destructor
  XMLPlatformUtils::Terminate();
  exit(EXIT_SUCCESS);
} /* end of main() */

