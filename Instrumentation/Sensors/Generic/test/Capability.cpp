//                              -*- Mode: C++ -*- 
// Capability.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Fri Sep 28 14:45:31 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Oct 20 03:53:01 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 20
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
 *  @ingroup GenericSensor 
 *  @brief implementation of the capability file parsing program
 *
 * $Id: Capability.cpp,v 1.5 2001/12/09 02:06:24 nath Exp $
 */

/// RCS version string
static const char* 
version = "$Id: Capability.cpp,v 1.5 2001/12/09 02:06:24 nath Exp $";

#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <ctype.h>

#include <idom/IDOM.hpp>
#include <idom/IDOM_DOMException.hpp>
#include <parsers/IDOMParser.hpp>
#include <util/PlatformUtils.hpp>
#include <framework/MemBufInputSource.hpp>


#include "Debug.h"

#include <util/XercesDefs.hpp>
#include <sax/SAXParseException.hpp>
#include <sax/ErrorHandler.hpp>



class IDOMTreeErrorReporter : public ErrorHandler
{
public:
  ///  Constructors
  IDOMTreeErrorReporter() : fSawErrors(false){}
  ///  Destructor
  ~IDOMTreeErrorReporter(){}

  /// Implementation of the error handler interface
  void warning(const SAXParseException& toCatch)
  {
    cerr << "Warning at file \"" 
	 << (char *)XMLString::transcode(toCatch.getSystemId())
	 << "\", line " << toCatch.getLineNumber()
	 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " 
	 << (char *)XMLString::transcode(toCatch.getMessage())
	 << endl;
  };

  void error(const SAXParseException& toCatch){
    fSawErrors = true;
    cerr << "Error at file \"" 
	 << (char *)XMLString::transcode(toCatch.getSystemId())
	 << "\", line " << toCatch.getLineNumber()
	 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " 
	 << (char *)XMLString::transcode(toCatch.getMessage())
	 << endl;
  };

  void fatalError(const SAXParseException& toCatch){
    fSawErrors = true;
    cerr << "Fatal Error at file \"" 
	 << (char *)XMLString::transcode(toCatch.getSystemId())
	 << "\", line " << toCatch.getLineNumber()
	 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: "
	 << (char *)XMLString::transcode(toCatch.getMessage())
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
  cout << " "         << get_node_type(node_p)
       << ";\tName=["  << (char *)XMLString::transcode(node_p->getNodeName())
       << "];\tValue=" << (char *)XMLString::transcode(node_p->getNodeValue())
       << "\n" ;
}
void
create_ruler(int level, string& ruler)
{
  for(int i = 0; i < level; i++)
   {
     ruler.append("=");
   } /* end of for(int i = 0; i < level; i++) */
  ruler.append(">");
  for(int i = level; i < 10; i++)
   {
     ruler.append(" ");
   } /* end of for(int i = 0; i < level; i++) */
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
variable_element_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;
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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p = 0;
        if(strcmp(node_name_p, "name") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "name") == 0) */
        if(strcmp(node_name_p, "value") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "name") == 0) */
        if(strcmp(node_name_p, "searchable") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "name") == 0) */
        if(strcmp(node_name_p, "maptoProperty") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "name") == 0) */
        if(value_p)
	 {
	   int childlevel = level + 1;
	   create_ruler(childlevel, ruler);  
	   cout << childlevel << ruler;
	   ruler.erase();
	   cout << "T 2 " << "\t";
	   cout << node_name_p << " = " << value_p << endl;
	 } /* end of if(value_p) */

      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

// These are the name=value pairs that are absolutely mandatory and
// every entity making an offer has to provide these. This refers to
// the QMSUniqueName corresponding to the probe. Note that the host
// and uuid part of the QMSUniqueName will be generated by the
// instance of the object reading this capability or config file, so
// the type is restricted to remove those two elements.
void
uniq_name_element_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;
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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p = 0;
        if(strcmp(node_name_p, "category") == 0)
         {
	   // element name="category" base="xsd:string"
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "host") == 0)
         {
	   // element name="host" type="ipv4AddressType"
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "uuid") == 0)
         {
	   // element name="uuid" type="xsd:unsignedLong"
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        
        if(value_p)
	 {
	   int childlevel = level + 1;
	   create_ruler(childlevel, ruler);  
	   cout << childlevel << ruler;
	   ruler.erase();
	   cout << "T 2 " << "\t";
	   cout << node_name_p << " = " << value_p << endl;
	 } /* end of if(value_p) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

void
xsl_param_element_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;
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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "variable") == 0)
         {
           variable_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}



void
instance_element_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;
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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "variable") == 0)
         {
           variable_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

void
offer_element_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;
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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "variable") == 0)
         {
           variable_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

void
invoke_element_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;
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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p = 0;
        if(strcmp(node_name_p, "probeExecutable") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "probeXSLTFile") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "xslParameters") == 0)
         {
           xsl_param_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(value_p)
	 {
	   int childlevel = level + 1;
	   create_ruler(childlevel, ruler);  
	   cout << childlevel << ruler;
	   ruler.erase();
	   cout << "T 3 " << "\t";
	   cout << node_name_p << " = " << value_p << endl;
	 } /* end of if(value_p) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

// mandatoryServiceOfferProperties
// These are the name=value pairs that are absolutely mandatory and
// every entity making an offer has to provide these. This refers to
// the QMSUniqueName corresponding to the probe. Note that the host
// and uuid part of the QMSUniqueName will be generated by the
// instance of the object reading this capability or config file, so
// the type is restricted to remove those two elements.
void
mandatoryServiceOfferProperties(IDOM_Node *child_p, int level)
{
  if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
   {
     char * node_name_p = XMLString::transcode(child_p->getNodeName());
     
     if(strcmp(node_name_p, "QMSUniqueName") == 0)
      {
	uniq_name_element_handler(child_p, level);
      } /* end of if(strcmp(node_name_p, "QMSUniqueName") == 0) */     
   } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */  
}

// mandatoryCorbaOfferProperties
//    If the entity making the offer also provides a CORBA
//    interface (all QMS Citizens do and other clients may as
//    well) we'd like to identify the IDL interfaces they
//    offer up to the world with specific version
//    numbers. This will permit clients to figure out if they
//    are using the right version of the IDL interface while
//    trying to talk to the CORBA entity.
void
mandatoryCorbaOfferProperties(IDOM_Node *child_p, int level)
{
  string ruler;

  if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
   {
     char *value_p = 0;
     char * node_name_p = XMLString::transcode(child_p->getNodeName());
     
     if(strcmp(node_name_p, "interfaceVersion") == 0)
      {
	// element name="interfaceVersion" type="versionType"
	//     Restricting version numbers to be positive decimal
	//     numbers with two digits after decimal
	value_p = get_child_value(child_p);
      } /* end of if(strcmp(node_name_p, "schemaVersion") == 0) */
     if(value_p)
      {
	int childlevel = level + 1;
	create_ruler(childlevel, ruler);  
	cout << childlevel << ruler;
	ruler.erase();
	cout << "T 1 " << "\t";
	cout << node_name_p << " = " << value_p << endl;
      } /* end of if(value_p) */
     
   } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */  
}

// mandatorySchemaOfferProperties
//    Every probe that has a Sensor make an offer on its behalf in the
//    QMS Trader must have a pointer to the XML Schema that it is
//    using to represent its data. This should be available to the
//    Sensor as well as the clients that wish to communicate with it,
//    thus facilitating the validation of the XML data that is
//    created. Additional information needed for the sensor to figure
//    out how to handle the probe is included probeSchema - the URI to
//    the schema used by the probe schemaVersion - version of the
//    schema
void
mandatorySchemaOfferProperties(IDOM_Node *child_p, int level)
{
  string ruler;
  if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
   {
     char *value_p = 0;
     char * node_name_p = XMLString::transcode(child_p->getNodeName());
     
     if(strcmp(node_name_p, "probeSchema") == 0)
      {
	//element name="probeSchema" type="QMSSchemaURIType"
	value_p = get_child_value(child_p);
      } /* end of if(strcmp(node_name_p, "probeSchema") == 0) */
     if(strcmp(node_name_p, "schemaVersion") == 0)
      {
	// element name="schemaVersion" type="versionType"
	value_p = get_child_value(child_p);
      } /* end of if(strcmp(node_name_p, "schemaVersion") == 0) */
     if(value_p)
      {
	int childlevel = level + 1;
	create_ruler(childlevel, ruler);  
	cout << childlevel << ruler;
	ruler.erase();
	cout << "T 1 " <<  "\t";
	cout << node_name_p << " = " << value_p << endl;
      } /* end of if(value_p) */
     
   } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */  
}

// These are properties defined for the probe in the capabilities file
// that will allow the Sensor to make a determination as to how to
// handle the deployment and use of the data provided by the probe.
//  probeType - continuous or oneshot
//  dataReusable - Whether the probe data can be reused
void
genericSensorProbeProperties(IDOM_Node *child_p, int level)
{
  string ruler;
  if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
   {
     char *value_p = 0;
     char * node_name_p = XMLString::transcode(child_p->getNodeName());
     
     // genericSensorProbeProperties
     if(strcmp(node_name_p, "probeType") == 0)
      {
	// name="probeType" type="typeofProbeType"
	value_p = get_child_value(child_p);
      } /* end of if(strcmp(node_name_p, "probeType") == 0) */
     if(strcmp(node_name_p, "dataReusable") == 0)
      {
	// name="dataReusable" type="xsd:boolean"
	value_p = get_child_value(child_p);
      } /* end of if(strcmp(node_name_p, "dataReusable") == 0) */
     
     if(value_p)
      {
	int childlevel = level + 1;
	create_ruler(childlevel, ruler);  
	cout << childlevel << ruler;
	ruler.erase();
	cout << "T 1 " << "\t";
	cout << node_name_p << " = " << value_p << endl;
      } /* end of if(value_p) */
     
   } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */  
}

     
//  The Probe Definition list. The Probe has some configuration
//  parameters that are required by the Generic Sensor to figure
//  out what Service it provides and what to do with
//  it. Additionally there are some mandatory offer properties
//  such as the SchemaOffer that the Probe needs to define. All of
//  these put together will generate a Service that the Sensor
//  will provide when it reads this probe definition.
void
probe_element_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;

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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	
	genericSensorProbeProperties(child_p, level);
	mandatorySchemaOfferProperties(child_p,  level);
	mandatoryCorbaOfferProperties(child_p, level);
	mandatoryServiceOfferProperties(child_p, level);

	// Offers
        if(strcmp(node_name_p, "Offer") == 0)
         {
           offer_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "Offer") == 0) */

	// Invocation
        if(strcmp(node_name_p, "Invoke") == 0)
         {
           invoke_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "Invoke") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

void
sensorService_element_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;


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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());

	mandatoryServiceOfferProperties(child_p, level);
	mandatorySchemaOfferProperties(child_p, level);
	mandatoryCorbaOfferProperties(child_p, level);

       if(strcmp(node_name_p, "Offer") == 0)
         {
           offer_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "Offer") == 0) */
	// Invocation
        if(strcmp(node_name_p, "Instance") == 0)
         {
           instance_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "Invoke") == 0) */
         
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

// QoS Parameters that will be interpreted by the Sensor to provide
// high priority handling by the Sensor, to provide high priority
// scheduling by the Event Channel etc. This is a placeholder as more
// work needs to be done here.
void
QoSParameters_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;


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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p = 0;
	
        if(strcmp(node_name_p, "Priority") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "Priority") == 0) */

        if(value_p)
	 {
	   int childlevel = level + 1;
	   create_ruler(childlevel, ruler);  
	   cout << childlevel << ruler;
	   ruler.erase();
	   cout << "T 2 " << "\t";
	   cout << node_name_p << " = " << value_p << endl;
	 } /* end of if(value_p) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


// This is a parameter that will be used by the Sensor to determine
// how many times to send the data requested. Default value will be
// 1. "current" will be used by the supplier of data to indicate what
// the count is that it's currently on.
void
minRepetitions_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;


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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p = 0;
	
        if(strcmp(node_name_p, "count") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "count") == 0) */
        if(strcmp(node_name_p, "current") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "current") == 0) */
        if(value_p)
	 {
	   int childlevel = level + 1;
	   create_ruler(childlevel, ruler);  
	   cout << childlevel << ruler;
	   ruler.erase();
	   cout << "T 2 " << "\t";
	   cout << node_name_p << " = " << value_p << endl;
	 } /* end of if(value_p) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

void
session_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;


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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p = 0;

	// This is a requestID that will be generated by the sender
	// each time a request is sent to a supplier of data. This
	// requestID will be used to maintain the notion of a
	// session. This will allow the sender to later modify the
	// request by sending another request to the supplier with the
	// same requestID but with a different version number. Thus
	// the supplier will know to modify the existing request it is
	// servicing as opposed to starting up another data stream to
	// service this request. This will allow the sender to
	// terminate the request if it is no longer interested in the
	// data. Preferably this will be a UUID of some sort. The
	// supplier of data will also send out the same requestID in
	// its response.
        if(strcmp(node_name_p, "requestID") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "") == 0) */

	// The default value of this element is "0". If the request is
	// modified by the sender and the session is now modified to
	// send a different stream of data, the version number is
	// incremented. This will enable the supplier of data to
	// realize that the data is for the same session, but just
	// modified.
        if(strcmp(node_name_p, "version") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "version") == 0) */

	// This is the dataID generated by the supplier of data and
	// incremented per message that the supplier sends out. This
	// will help establish the order of the data that is sent
	// out. Similar to the RequestID, this will be a UUID as well.
        if(strcmp(node_name_p, "dataID") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "dataID") == 0) */

        if(strcmp(node_name_p, "minRepetitions") == 0)
         {
           minRepetitions_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "minRepetitions") == 0) */

	// This parameter defines the interval to be used by the
	// Sensor between repeated executions of the request for
	// data. Default value will be 5 seconds.
        if(strcmp(node_name_p, "minRepeatInterval") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "minRepeatInterval") == 0) */


	// Depending on the nature of the probe that is providing the
	// data, the Sensor will have the ability to tag the data as
	// reusable or not. For example, a CPU probe may tag its data
	// as being reusable. In this case, a request from client A
	// will start the probe data flowing, but since there may be
	// other requests that later originate from other clients,
	// that are also being serviced by the same probe, it is
	// essential to tag this data as being "Private" when it is
	// meant only for the original request generator or "Public",
	// when there are multiple consumers of the data. The client
	// may also request that the data should be sent marked
	// "Private", so that the data message will contain a
	// msgDestination element. If the data comes from a reusable
	// probe, then the forceReuse flag will need to be set too.
        if(strcmp(node_name_p, "dataScope") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "dataScope") == 0) */


	// If the probe is one that generates reusable data, but
	// the sender of the request wishes to force the Sensor to
	// start another probe just for it, this flag will permit
	// that.
        if(strcmp(node_name_p, "forceReuse") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "forceReuse") == 0) */


        if(strcmp(node_name_p, "QoSParameters") == 0)
         {
           QoSParameters_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "QoSParameters") == 0) */


        if(value_p)
	 {
	   int childlevel = level + 1;
	   create_ruler(childlevel, ruler);  
	   cout << childlevel << ruler;
	   ruler.erase();
	   cout << "T 2 " << "\t";
	   cout << node_name_p << " = " << value_p << endl;
	 } /* end of if(value_p) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


void
QMSMessage_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;


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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p = 0;

	// A Sequence Number to serve as a unique ID per message.
        if(strcmp(node_name_p, "msgSequenceNo") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "") == 0) */


	// This is the IP address of the host from which this message
	// is originating. This could be correlated to the SupplierID
	// by querying the QMS Trader as well.
        if(strcmp(node_name_p, "originatingHost") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "originatingHost") == 0) */
        if(strcmp(node_name_p, "msgSender") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "msgDestination") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "msgReplyTo") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "msgDate") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "msgTime") == 0)
         {
           value_p = get_child_value(child_p);
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "Session") == 0)
         {
           session_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(value_p)
	 {
	   int childlevel = level + 1;
	   create_ruler(childlevel, ruler);  
	   cout << childlevel << ruler;
	   ruler.erase();
	   cout << "T 2 " << "\t";
	   cout << node_name_p << " = " << value_p << endl;
	 } /* end of if(value_p) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


void
sensorConfiguration_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;


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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "sensorService") == 0)
         {
           sensorService_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


// The Sensor capability file consists of many fragments that are put
// into the file by each Probe that the sensor is capable of providing
// data for.
void
sensorCapability_handler(IDOM_Node *node_p, int level)
{
  level++;
  string ruler;


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
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();
     cout << ++childnum << "\t";
     print_node_details(child_p);
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "Probe") == 0)
         {
	   // element name="Probe" type="ProbeDefinitionType"
           probe_element_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


void
doc_handler (IDOM_Node *doc_p)
{
  // The top level node is unnamed, and is a DOCUMENT_NODE
  int level = 0;
  string ruler;

  create_ruler(level, ruler);  
  cout << level << ruler;
  ruler.erase();

  print_node_details(doc_p);

  
  // We now look towards the children
  IDOM_Node *child_p = doc_p->getFirstChild();
  int childnum = 0;
  while(child_p != 0)
   {
     level ++;
     
     create_ruler(level, ruler);  
     cout << level << ruler;
     ruler.erase();

     cout << ++childnum << "\t";
     print_node_details(child_p);

     // Handle the nodes here. We have first a DOCUMENT_TYPE_NODE, and
     // then a ELEMENT_NODE. We probably do not want to deal with the
     // DTD here (the parser has done all we need to take care of). 
     if(child_p->getNodeType() == IDOM_Node::ELEMENT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	if(strcmp(node_name_p, "sensorCapability") == 0)
         {
	   // element name="sensorCapability
           sensorCapability_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "sensorConfiguration") == 0)
         {
           sensorConfiguration_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "QMSMessage") == 0)
         {
           QMSMessage_handler(child_p, level);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        
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
  
  
  //
  //  Create our parser, then attach an error handler to the parser.
  //  The parser will call back to methods of the ErrorHandler if it
  //  discovers errors during the course of parsing the XML document.
  //
  IDOMParser *parser = new IDOMParser;
  parser->setValidationScheme(IDOMParser::Val_Auto);
  parser->setDoNamespaces(true);
  parser->setDoSchema(true);

  IDOMTreeErrorReporter *errReporter = new IDOMTreeErrorReporter();
  
  parser->setErrorHandler(errReporter);
  parser->setCreateEntityReferenceNodes(false);


  //
  //  Parse the XML file, catching any XML exceptions that might propogate
  //  out of it.
  //
  bool errorsOccured = false;
  try
   {
     parser->parse(filename_p);
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

