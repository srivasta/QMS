//                              -*- Mode: C++ -*- 
// Parse_XML.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Wed Oct  3 12:54:48 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu Oct 25 14:37:24 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 166
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
static const char* 
version = "$Id: Parse_XML.cpp,v 1.37 2001/12/05 23:30:26 srivasta Exp $";

/** @file Parse_XML.cpp
 *  @ingroup Utilities
 *  @brief Convenience object to parse QMS XML documents
 *
 * $Id: Parse_XML.cpp,v 1.37 2001/12/05 23:30:26 srivasta Exp $
 */

#include "Parse_XML.h"

/**
 * @brief Return true of errors were encountered during parsing
 */
inline bool IDOMTreeErrorReporter::getSawErrors() const
{
  return fSawErrors;
}

/**
 *  @brief The constructor
 *
 * 
 */
STDC::QMS::Parse_XML::Parse_XML() : parser(0), errReporter(0)
{
  QMS_Trace ("STDC::QMS::Parse_XML::Parse_XML", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Parse_XML created\n");
}

/**
 *  @overload
 * 
 */
STDC::QMS::Parse_XML::Parse_XML(const STDC::QMS::Parse_XML& rhs)
{
  QMS_Trace ("STDC::QMS::Parse_XML::Parse_XML", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Parse_XML created\n");
  this->parser = rhs.parser;
  this->errReporter = rhs.errReporter;
}

/// The destructor
STDC::QMS::Parse_XML::~Parse_XML()
{
  QMS_Trace ("STDC::QMS::Parse_XML::~Parse_XML", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Parse_XML destroyed\n");
  this->cleanup();
}

/// The assignment operator
STDC::QMS::Parse_XML & 
STDC::QMS::Parse_XML::operator=(const STDC::QMS::Parse_XML& rhs)
{
  QMS_Trace ("STDC::QMS::Parse_XML::Parse_XML", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::Parse_XML created\n");
  this->parser = rhs.parser;
  this->errReporter = rhs.errReporter;
  return *this;
}

/**
 * @brief Create a new XML parser, and initialize it
 *
 * We default to caring about namespaces and validating schemas, if
 * any. We also set the validation policy to validate if the document
 * contains a DTD reference or a schema. We also set up error handling
 * during parsing at this point. 
 */
void
STDC::QMS::Parse_XML::create_parser(void)
{
  QMS_Trace ("STDC::QMS::Parse_XML::create_parser", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::create_parser\n");
  //
  //  Create our parser, then attach an error handler to the parser.
  //  The parser will call back to methods of the ErrorHandler if it
  //  discovers errors during the course of parsing the XML document.
  //
  this->parser = new IDOMParser;
  this->parser->setValidationScheme(IDOMParser::Val_Auto);
  this->parser->setDoNamespaces(true);
  this->parser->setDoSchema(true);

  this->errReporter = new IDOMTreeErrorReporter();
  this->parser->setErrorHandler(this->errReporter);
  this->parser->setCreateEntityReferenceNodes(false);
}

/**
 * @brief Cleanup the error reporter and the parser and reclaim resources
 *
 * All parser5s need to be cleaned up before terminating the XML
 * parsing platform
 */
void
STDC::QMS::Parse_XML::cleanup(void)
{
  QMS_Trace ("STDC::QMS::Parse_XML::cleanup", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::cleanup\n");
  /*
   *  Clean up the error handler. The parser does not adopt handlers
   *  since they could be many objects or one object installed for multiple
   *  handlers.
   */
  if(this->errReporter)
   {
     delete errReporter;
   } /* end of if(this->errReporter) */
  
  /*
   * Delete the parser itself.  Must be done prior to calling
   * Terminate, below.  
   */
  if(this->parser)
   {
     delete parser;
   } /* end of if(this->parser) */
}

using std::invalid_argument;

/**
 * @brief Parse an XML file 
 * @param filename_p The name of the file to parse
 * @return true on success
 *
 * This is a fairly straight forward operation
 */
bool 
STDC::QMS::Parse_XML::parse_file(char *filename_p)
{
  QMS_Trace ("STDC::QMS::Parse_XML::parse_file", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::parse_file\n");

  if(!filename_p)
   {
     cerr << "STDC::QMS::Parse_XML::parse_config:" << __LINE__ << __FILE__
	  <<endl
	  << "Mandatory parameter file name missing. Ending parse"
	  <<endl;
     throw invalid_argument("Mandatory parameter file name missing");
   } /* end of if(!filename_p) */
  //
  //  Parse the XML file, catching any XML exceptions that might propogate
  //  out of it.
  //
  bool errorsOccured = false;
  try
   {
     this->parser->parse(filename_p);
     int errorCount = this->parser->getErrorCount();
     if (errorCount > 0)
       errorsOccured = true;
   }
  catch (const XMLException& e)
   {
     cerr << "An error occured during parsing " << filename_p 
	  << ":\n  Message: "
          << XMLString::transcode(e.getMessage()) << endl;
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
  return errorsOccured;
}

/**
 * @brief Parse an in memory buffer
 * @param message The in memory message to parse
 * @return true on success
 * 
 * This is a fairly straight forward operation
 */
bool 
STDC::QMS::Parse_XML::parse_mem(MemBufInputSource &message)
{
  QMS_Trace ("STDC::QMS::Parse_XML::parse_mem", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::parse_mem\n");

  //
  //  Parse the XML file, catching any XML exceptions that might propogate
  //  out of it.
  //
  bool errorsOccured = false;
  try
   {
     DEBUG0 (2, "DEBUG: Calling the Xerces Parser\n");
     this->parser->parse(message);
     DEBUG0 (2, "DEBUG: Xerces done parsing\n");

     int errorCount = this->parser->getErrorCount();
     if (errorCount > 0)
      {
	errorsOccured = true;
	DEBUG1 (2, "DEBUG: %d Errors Occurred\n", errorCount);
      }
     else
      {
	DEBUG0 (2, "DEBUG: No errors from Xerces\n");
      } /* end of else */
     
   }
  catch (const XMLException& e)
   {
     cerr << "An error occured during parsing\n   Message: "
          << XMLString::transcode(e.getMessage()) << endl;
     errorsOccured = true;
   }
  catch (const IDOM_DOMException& e)
   {
     cerr << "A IDOM error occured during parsing the message\n" 
	  << " IDOMException code: "
          << e.code << endl;
     errorsOccured = true;
   }
  catch (...)
   {
     cerr << "An error occured during parsing\n " << endl;
     errorsOccured = true;
   }
  return errorsOccured;
}

/**
 * @brief return the value of a child node
 * @param node_p A pointer to the node of interest
 *
 * Generally used to get values of leaf nodes,  This function is part
 * of the handle_query mechanism
 */
char *
STDC::QMS::Parse_XML::get_child_value(IDOM_Node *node_p)
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
 * @brief Handle the expanded variable type
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::expanded_variable_element_handler(IDOM_Node *node_p,
					         expandedVariableType &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::expanded_variable_element_handler",
             __LINE__, __FILE__);
  DEBUG0 (2,
	  "DEBUG: STDC::QMS::expanded_variable_element_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::expanded_variable_element_handlerr:" 
          << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } 

  IDOM_Node *child_p = node_p->getFirstChild();
  // set defaults
  results.variable.name.erase();
  results.variable.value.erase();
  results.searchable = false;
  results.maptoProperty = INT_MAX;
  
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
        if(strcmp(node_name_p, "name") == 0)
         {
           value_p = get_child_value(child_p);
	   
	   if(value_p)
	    {
	      results.variable.name.assign(value_p);
	    } /* end of if(value_p) */
         } /* end of if(strcmp(node_name_p, "name") == 0) */
        if(strcmp(node_name_p, "value") == 0)
         {
           value_p = get_child_value(child_p);
	   
	   if(value_p)
	    {
	      results.variable.value.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "name") == 0) */
        if(strcmp(node_name_p, "searchable") == 0)
         {
           value_p = get_child_value(child_p);
	   if( value_p &&
	       (!strcmp(value_p, "FALSE") || !strcmp(value_p, "false") ||
		!strcmp(value_p, "False") || !strcmp(value_p, "NO")    ||
		!strcmp(value_p, "no") || !strcmp(value_p, "No")       ||
		!strcmp(value_p, "0")) )
	    {
	      results.searchable = false;
	    } /* end of if(!strcmp(value_p, "FALSE")) */
	   else
	    {
	      results.searchable = true;
	    } /* end of else */
	   
         } /* end of if(strcmp(node_name_p, "name") == 0) */
        if(strcmp(node_name_p, "maptoProperty") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.maptoProperty = atoi(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "name") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

/**
 * @brief Handle the variable type
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::variable_element_handler(IDOM_Node *node_p,
					       variableType &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::variable_element_handler",
             __LINE__, __FILE__);
  DEBUG0 (2,
	  "DEBUG: STDC::QMS::variable_element_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::variable_element_handlerr:" 
          << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } 
  //set defaults
  results.name.erase();
  results.value.erase();

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
        if(strcmp(node_name_p, "name") == 0)
         {
           value_p = get_child_value(child_p);
	   
	   if(value_p)
	    {
	      results.name.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "name") == 0) */
        if(strcmp(node_name_p, "value") == 0)
         {
           value_p = get_child_value(child_p);
	   
	   if(value_p)
	    {
	      results.value.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "name") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

/**
 * @brief Handle the pubsubIDType_ type
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::pubsubIDType_handler(IDOM_Node *node_p,
					   pubsubIDType &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::pubsubIDType_handler",
             __LINE__, __FILE__);
  DEBUG0 (2,
	  "DEBUG: STDC::QMS::pubsubIDType_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::pubsubIDType_handler:" 
          << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } 
  // set defaults
  results.id = INT_MAX;
  results.description.erase();
  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
        if(strcmp(node_name_p, "id") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.id = atol(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "name") == 0) */
        if(strcmp(node_name_p, "description") == 0)
         {
           value_p = get_child_value(child_p);
	   
	   if(value_p)
	    {
	      results.description.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "name") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


/**
 * @brief Handle the QoSParameters type
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::QoSParameters_handler(IDOM_Node *node_p, 
					    QoSParameters &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::QoSParameters_handler",
             __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::QoSParameters_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::QoSParameters_handler:" 
          << __LINE__ << __FILE__ <<endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */

  // set defaults
  results.Priority = 0;
  
  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
        
        if(strcmp(node_name_p, "Priority") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.Priority = atol(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "Priority") == 0) */
	child_p = child_p->getNextSibling();
      } /* end of while(child != 0) */  
   }
}


/**
 * @brief Handle the minRepetitions type
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 *
 * This is a parameter that will be used by the Sensor to determine
 * how many times to send the data requested. Default value will be
 * 1. "current" will be used by the supplier of data to indicate what
 * the count is that it's currently on.
 */
void
STDC::QMS::Parse_XML::minRepetitions_handler(IDOM_Node *node_p, 
					     minRepetitions &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::minRepetitions_handler",
             __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::minRepetitions_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::minRepetitions_handler:" 
          << __LINE__ << __FILE__ <<endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */
  // set defaults
  results.count = 0;
  results.current = 0;
  
  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
        
        if(strcmp(node_name_p, "count") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.count = atol(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "count") == 0) */
        if(strcmp(node_name_p, "current") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.current = atol(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "current") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

/**
 * @brief Handle the Session type
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::session_handler(IDOM_Node *node_p, sessionType &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::session_handler",__LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::session_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::session_handler:" 
          << __LINE__ << __FILE__ <<endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */
  // set defaults
  results.request_id = INT_MAX;
  results.version = INT_MAX;
  results.data_id = INT_MAX;
  results.interval = "5";
  results.scope.erase();
  results.forceReuse = false;

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
        if(strcmp(node_name_p, "requestID") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.request_id = atol(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "") == 0) */

        if(strcmp(node_name_p, "version") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.version = atol(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "version") == 0) */
        if(strcmp(node_name_p, "dataID") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.data_id = atol(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "dataID") == 0) */

        if(strcmp(node_name_p, "minRepetitions") == 0)
         {
           minRepetitions_handler(child_p, results.repititions);
         } /* end of if(strcmp(node_name_p, "minRepetitions") == 0) */

        if(strcmp(node_name_p, "minRepeatInterval") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.interval.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "minRepeatInterval") == 0) */
        if(strcmp(node_name_p, "dataScope") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.scope.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "dataScope") == 0) */

        if(strcmp(node_name_p, "forceReuse") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p && 
	      (!strcmp(value_p, "FALSE") || !strcmp(value_p, "false") ||
	       !strcmp(value_p, "False") || !strcmp(value_p, "NO")    ||
	       !strcmp(value_p, "no") || !strcmp(value_p, "No")       ||
	       !strcmp(value_p, "0") ))
	    {
	      results.forceReuse = false;
	    } /* end of if(!strcmp(value_p, "FALSE")) */
	   else
	    {
	      results.forceReuse = true;
	    } /* end of else */
         } /* end of if(strcmp(node_name_p, "forceReuse") == 0) */

        if(strcmp(node_name_p, "QoSParameters") == 0)
         {
           QoSParameters_handler(child_p, results.qos_params);
         } /* end of if(strcmp(node_name_p, "QoSParameters") == 0) */

      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

/**
 * @brief Handle the unique name type
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 *
 * These are the name=value pairs that are absolutely mandatory and
 * every entity making an offer has to provide these. This refers to
 * the QMSUniqueName corresponding to the probe. Note that the host
 * and uuid part of the QMSUniqueName will be generated by the
 * instance of the object reading this capability or config file, so
 * the type is restricted to remove those two elements.
 */
void
STDC::QMS::Parse_XML::uniq_name_element_handler(IDOM_Node *node_p,
						uniqueNameType& results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::uniq_name_element_handler",
             __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::uniq_name_element_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::uniq_name_element_handler:" 
          << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } 
  // set defaults
  results.category.erase();
  results.host.erase();
  results.uuid.erase();

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
        if(strcmp(node_name_p, "category") == 0)
         {
           // element name="category" base="xsd:string"
           value_p = get_child_value(child_p);
	   
	   if(value_p)
	    {
	      results.category.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "host") == 0)
         {
           // element name="host" type="ipv4AddressType"
           value_p = get_child_value(child_p);
	   
	   if(value_p)
	    {
	      results.host.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "uuid") == 0)
         {
           // element name="uuid" type="xsd:unsignedLong"
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.uuid.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}



/**
 * @brief Handle the instance element
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::instance_element_handler(IDOM_Node *node_p, 
					       vector<variableType> &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::instance_element_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::instance_element_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::instance_element_handler:" 
	  << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */
  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "variable") == 0)
         {
	   struct variableType *variable_p = new struct variableType;
	   try 
	    {
	      variable_element_handler(child_p, *variable_p);
	    }
	   catch (const invalid_argument & ex)
            {
              delete variable_p;
              throw;
            }

	   results.push_back(*variable_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

/**
 * @brief Handle the invocation element
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::invoke_element_handler(IDOM_Node *node_p, 
					     invocationType &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::invoke_element_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::invoke_element_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::invoke_element_handler:" 
	  << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */

  // set defaults
  results.probeExecutable.erase();
  results.probeXSLTFile.erase();
  

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;
        if(strcmp(node_name_p, "probeExecutable") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.probeExecutable.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "probeXSLTFile") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.probeXSLTFile.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if(strcmp(node_name_p, "xslParameters") == 0)
         {
	   // well, xsl parameters are exactly like instance elements
           instance_element_handler(child_p, results.xslParameters);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


/**
 * @brief Handle the odder parameters
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::offer_element_handler(IDOM_Node *node_p, 
					    optionalOfferType &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::offer_element_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::offer_element_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::offer_element_handler:" 
	  << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */
  
  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "variable") == 0)
         {
	   struct expandedVariableType *variable_p = 
	     new struct expandedVariableType;
	   try 
	    {
	      expanded_variable_element_handler(child_p, *variable_p);
	    }
           catch (const invalid_argument & ex)
            {
              delete variable_p;
              throw;
            }
	   results.push_back(*variable_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}

/**
 * @brief Handle the generic sensor probe properties elements
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 *
 * These are properties defined for the probe in the capabilities file
 * that will allow the Sensor to make a determination as to how to
 * handle the deployment and use of the data provided by the probe.
 *   - probeType - continuous or oneshot
 *   - dataReusable - Whether the probe data can be reused
 */
void
STDC::QMS::Parse_XML::genericSensorProbeProperties_handler
(IDOM_Node *child_p, genericSensorProbeProperties &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::genericSensorProbeProperties_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::genericSensorProbeProperties\n");
  if(!child_p)
   {
     cerr << "STDC::QMS::Parse_XML::genericSensorProbeProperties_handler:" 
	  << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */
  
  char *value_p = 0;
  char * node_name_p = XMLString::transcode(child_p->getNodeName());
  
  // genericSensorProbeProperties
  if(strcmp(node_name_p, "probeType") == 0)
   {
     // name="probeType" type="typeofProbeType"
     value_p = get_child_value(child_p);
     
     if(value_p)
      {
	results.probeType.assign(value_p);
      }
   } /* end of if(strcmp(node_name_p, "probeType") == 0) */
  if(strcmp(node_name_p, "dataReusable") == 0)
   {
     // name="dataReusable" type="xsd:boolean"
     value_p = get_child_value(child_p);
     if(value_p &&
	(!strcmp(value_p, "FALSE") || !strcmp(value_p, "false") ||
	 !strcmp(value_p, "False") || !strcmp(value_p, "NO")    ||
	 !strcmp(value_p, "no") || !strcmp(value_p, "No")       ||
	 !strcmp(value_p, "0")))
      {
	results.dataReusable = false;
      } /* end of if(!strcmp(value_p, "FALSE")) */
     else
      {
	results.dataReusable = true;
      } /* end of else */
     
   } /* end of if(strcmp(node_name_p, "dataReusable") == 0) */
}


/**
 * @brief Handle the mandatory service offer properties
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 *
 *
 * These are the name=value pairs that are absolutely mandatory and
 * every entity making an offer has to provide these. This refers to
 * the QMSUniqueName corresponding to the probe. Note that the host
 * and uuid part of the QMSUniqueName will be generated by the
 * instance of the object reading this capability or config file, so
 * the type is restricted to remove those two elements.
 */
void
STDC::QMS::Parse_XML::mandatoryServiceOfferProperties_handler
(IDOM_Node *child_p, mandatoryServiceOfferProperties &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::mandatoryServiceOfferProperties_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::mandatoryServiceOfferProperties\n");
  if(!child_p)
   {
     cerr << "STDC::QMS::Parse_XML::mandatoryServiceOfferProperties_handler:" 
	  << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */
 
  char * node_name_p = XMLString::transcode(child_p->getNodeName());
  
  if(strcmp(node_name_p, "QMSUniqueName") == 0)
   {
     uniq_name_element_handler(child_p, results.QMSUniqueName);
   } /* end of if(strcmp(node_name_p, "QMSUniqueName") == 0) */     
} /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */



/**
 * @brief Handle the mandatory Corba offer properties
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 *
 *
 *  If the entity making the offer also provides a CORBA
 *  interface (all QMS Citizens do and other clients may as
 *  well) we'd like to identify the IDL interfaces they
 *  offer up to the world with specific version
 *  numbers. This will permit clients to figure out if they
 *  are using the right version of the IDL interface while
 *  trying to talk to the CORBA entity.
 */
void
STDC::QMS::Parse_XML::mandatoryCorbaOfferProperties_handler(IDOM_Node *child_p, 
			mandatoryCorbaOfferProperties &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::mandatoryCorbaOfferProperties_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::mandatoryCorbaOfferProperties\n");
  if(!child_p)
   {
     cerr << "STDC::QMS::Parse_XML::mandatoryCorbaOfferProperties_handler:" 
	  << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } 
  
  char *value_p = 0;
  char * node_name_p = XMLString::transcode(child_p->getNodeName());
  if(strcmp(node_name_p, "interfaceDescription") == 0)
   {
     value_p = get_child_value(child_p);
     results.interfaceDescription.assign(value_p);
   } /* end of if(strcmp(node_name_p, "interfaceDescription" == 0) */
  if(strcmp(node_name_p, "interfaceVersion") == 0)
   {
     // element name="interfaceVersion" type="versionType"
     //     Restricting version numbers to be positive decimal
     //     numbers with two digits after decimal
     value_p = get_child_value(child_p);
     if(value_p)
      {
	results.interfaceVersion.assign(value_p);
      }
   } /* end of if(strcmp(node_name_p, "interfaceVersion") == 0) */
}

/**
 * @brief Handle the mandatory schema offer properties
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 *
 * Every probe that has a Sensor make an offer on its behalf in the
 * QMS Trader must have a pointer to the XML Schema that it is
 * using to represent its data. This should be available to the
 * Sensor as well as the clients that wish to communicate with it,
 * thus facilitating the validation of the XML data that is
 * created. Additional information needed for the sensor to figure
 * out how to handle the probe is included probeSchema - the URI to
 * the schema used by the probe schemaVersion - version of the
 * schema
 */
void
STDC::QMS::Parse_XML::mandatorySchemaOfferProperties_handler(IDOM_Node *child_p, mandatorySchemaOfferProperties &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::mandatorySchemaOfferProperties_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::mandatorySchemaOfferProperties\n");
  if(!child_p)
   {
     cerr << "STDC::QMS::Parse_XML::mandatorySchemaOfferProperties_handler:" 
	  << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */
  // set defaults

  char *value_p = 0;
  char * node_name_p = XMLString::transcode(child_p->getNodeName());
  
  if(strcmp(node_name_p, "probeSchema") == 0)
   {
     //element name="probeSchema" type="QMSSchemaURIType"
     value_p = get_child_value(child_p);
     if(value_p)
      {
	results.probeSchema.assign(value_p);
      }
   } /* end of if(strcmp(node_name_p, "probeSchema") == 0) */
  if(strcmp(node_name_p, "schemaVersion") == 0)
   {
     // element name="schemaVersion" type="versionType"
     value_p = get_child_value(child_p);
     if(value_p)
      {
	results.schemaVersion.assign(value_p);
      }
   } /* end of if(strcmp(node_name_p, "schemaVersion") == 0) */
}

/**
 * @brief Handle the probe elements
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::probe_element_handler(IDOM_Node *node_p, 
					    ProbeDefinitionType &results)
{
  IDOM_Node *child_p = node_p->getFirstChild();

  results.generic_prop.probeType.erase();
  results.generic_prop.dataReusable = false;
  results.schema_prop.probeSchema.erase();
  results.schema_prop.schemaVersion.erase();
  while(child_p != 0)
   { 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());

        if((strcmp(node_name_p, "probeType") == 0) || 
	   (strcmp(node_name_p, "dataReusable") == 0))
	 {
	   genericSensorProbeProperties_handler(child_p, results.generic_prop);
	 } /* end of if((strcmp(node_name_p, "probeType") == 0) || 
	      (strcmp(node_name_p, "dataReusable") == 0)) */
	
        if(strcmp(node_name_p, "QMSUniqueName") == 0)
	 {
	   mandatoryServiceOfferProperties_handler(child_p, 
						   results.offer_prop);
	 } /* end of if(strcmp(node_name_p, "QMSUniqueName") == 0) */
	
        if((strcmp(node_name_p, "probeSchema") == 0) ||
	   (strcmp(node_name_p, "schemaVersion") == 0))
	 {
	    mandatorySchemaOfferProperties_handler(child_p, 
						   results.schema_prop);
	 } /* end of if((strcmp(node_name_p, "probeSchema") == 0) ||
	      (strcmp(node_name_p, "schemaVersion") == 0)) */

        // Offers
        if(strcmp(node_name_p, "Offer") == 0)
         {
           offer_element_handler(child_p, results.offer_param);
         } /* end of if(strcmp(node_name_p, "Offer") == 0) */

        // Invocation
        if(strcmp(node_name_p, "Invoke") == 0)
         {
           invoke_element_handler(child_p, results.invocation_param);
         } /* end of if(strcmp(node_name_p, "Invoke") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


/**
 * @brief Handle the sensor service elements for built-in probes
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::sensorService_element_handler(IDOM_Node *node_p, struct sensorServiceType &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::sensorService_element_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::sensorService_element_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::sensorService_element_handler:" 
	  << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */
  IDOM_Node *child_p = node_p->getFirstChild();

  results.generic_prop.probeType.erase();
  results.generic_prop.dataReusable = false;
  results.schema_prop.probeSchema.erase();
  results.schema_prop.schemaVersion.erase();

  while(child_p)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
	char * node_name_p = XMLString::transcode(child_p->getNodeName());

        if((strcmp(node_name_p, "probeType") == 0) || 
	   (strcmp(node_name_p, "dataReusable") == 0))
	 {
	   genericSensorProbeProperties_handler(child_p, results.generic_prop);
	 } /* end of if((strcmp(node_name_p, "probeType") == 0) || 
	      (strcmp(node_name_p, "dataReusable") == 0)) */
        if(strcmp(node_name_p, "QMSUniqueName") == 0)
	 {
	   mandatoryServiceOfferProperties_handler(child_p, 
						   results.offer_prop);
	 } /* end of if(strcmp(node_name_p, "QMSUniqueName") == 0) */

        if((strcmp(node_name_p, "probeSchema") == 0) ||
	   (strcmp(node_name_p, "schemaVersion") == 0))
	 {
	    mandatorySchemaOfferProperties_handler(child_p, 
						   results.schema_prop);
	 } /* end of if((strcmp(node_name_p, "probeSchema") == 0) ||
	      (strcmp(node_name_p, "schemaVersion") == 0)) */

       if(strcmp(node_name_p, "Offer") == 0)
         {
	   offer_element_handler(child_p, results.offer_param);
         } /* end of if(strcmp(node_name_p, "Offer") == 0) */
        // Invocation
        if(strcmp(node_name_p, "Instance") == 0)
         {
	   instance_element_handler(child_p, results.Instance);
         } /* end of if(strcmp(node_name_p, "Instance") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child_p) */
}


/**
 * @brief Handle a QMS message
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 * @param payload_handler A function pointer to handle the payload
 * @param payload_arg_p Arguments to pass to the payload handler
 * @param error_handler A function pointer to handle any error message
 * @param error_arg_p Arguments to pass to the error handler
 * @return true on success
 */
bool
STDC::QMS::Parse_XML::QMSMessage_handler(IDOM_Node *node_p,QMSMessage &results,
					 bool (*payload_handler)(IDOM_Node 
								 *doc_p,  
								 void *arg_p),
					 void *payload_arg_p,
					 void (*error_handler)(IDOM_Node *
							       doc_p, 
							       void *arg_p),
					 void *error_arg_p)
{
  QMS_Trace ("STDC::QMS::Parse_XML::QMSMessage_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::QMSMessage_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::QMSMessage_handler:" 
	  << __LINE__ << __FILE__ << endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */

  // Well, this should work, unless reset by the payload handler
  bool success = true;

  // set defaults
  results.sequence_no = INT_MAX;
  results.sender_host.erase();
  results.msgDate.erase();
  results.msgTime.erase();

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        char * value_p = 0;

        // A Sequence Number to serve as a unique ID per message.
        if(strcmp(node_name_p, "msgSequenceNo") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.sequence_no = atol(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "") == 0) */

        // This is the IP address of the host from which this message
        // is originating. This could be correlated to the SupplierID
        // by querying the QMS Trader as well.
        if(strcmp(node_name_p, "originatingHost") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.sender_host.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "originatingHost") == 0) */
	if(strcmp(node_name_p, "QMSUniqueName") == 0)
	 {
	   uniq_name_element_handler(child_p, results.QMSUniqueName);
	 } /* end of if(strcmp(node_name_p, "QMSUniqueName") == 0) */
        if(strcmp(node_name_p, "msgSender") == 0)
         {
	   pubsubIDType_handler(child_p, results.sender);
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "msgDestination") == 0)
         {
           struct pubsubIDType *identity_p =
	     new  struct pubsubIDType;
	   try
	    {
	      pubsubIDType_handler(child_p, *identity_p);
	    }
	   catch (const invalid_argument & ex)
	    {
	      delete identity_p;
	      throw;
	    }
	   results.destinations.push_back(*identity_p);
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "msgReplyTo") == 0)
         {
           struct pubsubIDType *identity_p =
	     new  struct pubsubIDType;
	   try
	    {
	      pubsubIDType_handler(child_p, *identity_p);
	    }
	   catch (const invalid_argument & ex)
	    {
	      delete identity_p;
	      throw;
	    }
	   results.reply_tos.push_back(*identity_p);           
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "msgDate") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.msgDate.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "msgTime") == 0)
         {
           value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.msgTime.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "Session") == 0)
         {
           session_handler(child_p, results.Session);
         } /* end of if(strcmp(node_name_p, "") == 0) */
        if(strcmp(node_name_p, "payload") == 0)
         {
	   if(payload_handler)
	    {
	      success = payload_handler(child_p, payload_arg_p);
	    } /* end of if(payload_handler) */
         } /* end of if(strcmp(node_name_p, "payload") == 0) */
        if(strcmp(node_name_p, "error") == 0)
         {
	   if(error_handler)
	    {
	      error_handler(child_p, error_arg_p);
	    } /* end of if(error_handler) */
         } /* end of if(strcmp(node_name_p, "error") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
  return success;
}

/**
 * @brief Handle a sensor capability file detailing external probes
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 *
 * The Sensor capability file consists of many fragments that are put
 * into the file by each Probe that the sensor is capable of providing
 * data for.
 */
void
STDC::QMS::Parse_XML::sensorCapability_handler(IDOM_Node *node_p, 
					       sensorCapability  &results)
{
QMS_Trace ("STDC::QMS::Parse_XML::sensorCapability_handler", __LINE__,
	     __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::sensorCapability_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::sensorCapability_handler:" 
	  << __LINE__ << __FILE__ <<endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "Probe") == 0)
         {
	   struct ProbeDefinitionType *config_p =  new ProbeDefinitionType;
	   try 
	    {
	      // element name="Probe" type="ProbeDefinitionType"
	      probe_element_handler(child_p, *config_p);
	    }
	   catch (const invalid_argument & ex)
	    {
	      delete config_p;
	      throw;
	    }
	   results.push_back(*config_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}



/**
 * @brief Handle a QMS citizen configuration element
 * @param node_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 */
void
STDC::QMS::Parse_XML::sensorConfiguration_handler(IDOM_Node *node_p, struct sensorConfiguration &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::sensorConfiguration_handler", __LINE__,
	     __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::sensorConfiguration_handler\n");
  if(!node_p)
   {
     cerr << "STDC::QMS::Parse_XML::sensorConfiguration_handler:" 
	  << __LINE__ << __FILE__ <<endl << "Missing arguments" <<endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!filename_p) */
  
  results.QMS_Schema.erase();
  results.QMS_Schema.assign("QMSSchema.xsd");

  results.corba_prop.interfaceVersion.erase();
  results.corba_prop.interfaceDescription.erase();
    

  IDOM_Node *child_p = node_p->getFirstChild();
  while(child_p != 0)
   {
     // Well, the text nodes are not really interesting. They don't
     // have a value, really. We are interested in the non text nodes
     // here. 
     if(child_p->getNodeType() != IDOM_Node::TEXT_NODE)
      {
        char * node_name_p = XMLString::transcode(child_p->getNodeName());
	char * value_p     = 0;
        if(strcmp(node_name_p, "QMSUniqueName") == 0)
	 {
	   mandatoryServiceOfferProperties_handler(child_p, 
						   results.offer_prop);
	 } /* end of if(strcmp(node_name_p, "QMSUniqueName") == 0) */
	if((strcmp(node_name_p, "interfaceDescription") == 0) ||
	   (strcmp(node_name_p, "interfaceVersion") == 0))
	 {
	   mandatoryCorbaOfferProperties_handler(child_p, results.corba_prop);
	 } /* end of if((strcmp(node_name_p, "interfaceDescription") == 0) ||
	      (strcmp(node_name_p, "interfaceVersion") == 0)) */
	
        
	
	if(strcmp(node_name_p, "QMSSchema") == 0)
         {
	   value_p = get_child_value(child_p);
	   if(value_p)
	    {
	      results.QMS_Schema.erase();
	      results.QMS_Schema.assign(value_p);
	    }
         } /* end of if(strcmp(node_name_p, "QMSSchema"") == 0) */

       if(strcmp(node_name_p, "Offer") == 0)
         {
	   offer_element_handler(child_p, results.offer_param);
         } /* end of if(strcmp(node_name_p, "Offer") == 0) */
        if(strcmp(node_name_p, "Instance") == 0)
         {
	   instance_element_handler(child_p, results.Instance);
         } /* end of if(strcmp(node_name_p, "Instance") == 0) */
        // Invocation
         if(strcmp(node_name_p, "sensorService") == 0)
         {
 	   struct sensorServiceType *config_p =  new sensorServiceType;
	   try 
	    {
	      sensorService_element_handler(child_p, *config_p);
	    }
	   catch (const invalid_argument & ex)
	    {
	      delete config_p;
	      throw;
	    }
	   results.sensorServices.push_back(*config_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */        
      } /* end of if(child_p->getNodeType() != IDOM_Node::TEXT_NODE) */
     child_p = child_p->getNextSibling();
   } /* end of while(child != 0) */  
}


/**
 * @brief Handle a configuration element
 * @param doc_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 * @return true if we found the top level element
 */
bool
STDC::QMS::Parse_XML::config_handler(IDOM_Node *doc_p, 
				     sensorConfiguration &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::config_handler", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::config_handler\n");
  bool success = false;
  // The top level node is unnamed, and is a DOCUMENT_NODE
  // We now look towards the children
  IDOM_Node *child_p = doc_p->getFirstChild();
  while(child_p)
   {
     // Handle the nodes here. We have first a DOCUMENT_TYPE_NODE, and
     // then a ELEMENT_NODE. We probably do not want to deal with the
     // DTD here (the parser has done all we need to take care of). 
     if(child_p->getNodeType() == IDOM_Node::ELEMENT_NODE)
      {
	char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "sensorConfiguration") == 0)
         {
	   sensorConfiguration_handler(child_p, results);
	   success = true;
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if((strcmp(node_name_p, "sensorCapability") == 0) ||
	   (strcmp(node_name_p, "QMSMessage") == 0))
         {
	   cerr << "This is not a configuration file as was expected"
		<< endl
		<< "Since something got confused, I am stopping the parse"
		<<endl;
	   throw invalid_argument("file not a configuration file");;
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
	
      } /* end of if(child_p->getNodeType() == IDOM_Node::ELEMENT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child_p) */
  return success;
}

/**
 * @brief Handle a capability element
 * @param doc_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 * @return true if we found the top level element
 */
bool
STDC::QMS::Parse_XML::capability_handler(IDOM_Node *doc_p, 
					 sensorCapability &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML:capability:_handler", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::capability_handler\n");
  bool success = false;
  // The top level node is unnamed, and is a DOCUMENT_NODE
  // We now look towards the children
  IDOM_Node *child_p = doc_p->getFirstChild();
  while(child_p)
   {
     // Handle the nodes here. We have first a DOCUMENT_TYPE_NODE, and
     // then a ELEMENT_NODE. We probably do not want to deal with the
     // DTD here (the parser has done all we need to take care of). 
     if(child_p->getNodeType() == IDOM_Node::ELEMENT_NODE)
      {
	char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "sensorCapability") == 0)
         {
	   sensorCapability_handler(child_p, results);
	   success = true;
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if((strcmp(node_name_p, "sensorConfiguration") == 0) ||
	   (strcmp(node_name_p, "QMSMessage") == 0))
         {
	   cerr << "This is not a capability file as was expected"
		<< endl
		<< "Since something got confused, I am stopping the parse"
		<<endl;
	   throw invalid_argument("file not a capability file");;
         }
      } /* end of if(child_p->getNodeType() == IDOM_Node::ELEMENT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child_p) */
  return success;
}

/**
 * @brief Handle a message element
 * @param doc_p A pointer to the node of interest
 * @param results A reference to the struct where we stash the results
 * @param payload_handler A function pointer to handle the payload
 * @param payload_arg_p Arguments to pass to the payload handler
 * @param error_handler A function pointer to handle any error message
 * @param error_arg_p Arguments to pass to the error handler
 * @return true if we found the top level element
 */
bool
STDC::QMS::Parse_XML::message_handler(IDOM_Node *doc_p, 
				      QMSMessage &results,
				      bool (*payload_handler)(IDOM_Node *doc_p,
							      void *arg_p),
				      void *payload_arg_p,
				      void (*error_handler)(IDOM_Node *doc_p, 
							    void *arg_p),
				      void *error_arg_p)
{
  QMS_Trace ("STDC::QMS::Parse_XML:capability:message_handler",
	     __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::message_handler\n");
  bool success = false;
  // The top level node is unnamed, and is a DOCUMENT_NODE
  // We now look towards the children
  IDOM_Node *child_p = doc_p->getFirstChild();
  while(child_p)
   {
     // Handle the nodes here. We have first a DOCUMENT_TYPE_NODE, and
     // then a ELEMENT_NODE. We probably do not want to deal with the
     // DTD here (the parser has done all we need to take care of). 
     if(child_p->getNodeType() == IDOM_Node::ELEMENT_NODE)
      {
	char * node_name_p = XMLString::transcode(child_p->getNodeName());
        if(strcmp(node_name_p, "QMSMessage") == 0)
         {
	   success = QMSMessage_handler(child_p, results, 
			      payload_handler, payload_arg_p,
			      error_handler, error_arg_p);
         } /* end of if(strcmp(node_name_p, "PROBE") == 0) */
        if((strcmp(node_name_p, "sensorConfiguration") == 0) ||
	   (strcmp(node_name_p, "sensorCapability") == 0))
         {
	   cerr << "This is not a QMS Message as was expected"
		<< endl
		<< "Since something got confused, I am stopping the parse"
		<<endl;
	   throw invalid_argument("file not a QMS Message");;
         }
      } /* end of if(child_p->getNodeType() == IDOM_Node::ELEMENT_NODE) */

     child_p = child_p->getNextSibling();
   } /* end of while(child_p) */
  return success;
}

/**
 * @brief Parse a citizen configuration file
 * @return True on success, false on failure
 * @params filename_p The path of the configuration file
 * @params results_p  The resutls of the parse
 */
bool
STDC::QMS::Parse_XML::parse_config(char *filename_p,  
				   sensorConfiguration &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::parse_config", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::parse_config\n");
  
  if(!filename_p)
   {
     cerr << "STDC::QMS::Parse_XML::parse_config:" << __LINE__ << __FILE__
	  <<endl
	  << "Mandatory parameter file name missing. Ending parse"
	  <<endl;
     return false;
   } /* end of if(!filename_p) */
  

  // We are entering a parse session, so we lock the object until we
  // are done
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  // Create and initialize the parser
  DEBUG0 (2, "DEBUG: Create and initialize the parser\n");
  this->create_parser();

  // Parse the config file
  DEBUG0 (2, "DEBUG: Parse the file\n");
  bool errorsOccured = this->parse_file(filename_p);
  DEBUG0 (2, "DEBUG: Done parsing\n");

  bool success = (!errorsOccured && !this->errReporter->getSawErrors());
  
  // If there are no errors, we handle the file
  if(success)
   {
     DEBUG0 (2, "DEBUG: no errors, we now handle the file\n");
     IDOM_Node *doc_p = this->parser->getDocument();
     if(doc_p)
      {
	DEBUG0 (2, "DEBUG: we now have a DOM tree\n");
	try
	 {
	   success = config_handler(doc_p, results);
	   if(!success)
	    {
	      this->cleanup();
	      cerr << "Error  Failed to grok parsed config data" 
		   << std::endl;
	      return success;
	    } /* end of if(!success) */
	 }
	catch (const invalid_argument& ex)
	 {
	   this->cleanup();
	   cerr << "Error reading config file: " << ex.what() << std::endl;
	   return false;
	 }
      } /* end of if(doc_p) */
   } /* end of if(!errorsOccured && !errReporter->getSawErrors()) */
  else
   {
     cerr << "failed to parse config file." << std::endl;
   } /* end of else */
  
  // Cleanup before exiting
  this->cleanup();
  return success;
}


/**
 * @brief Parse a Sensor capability file
 * @return True on success, false on failure
 * @params filename_p The path of the capability file
 * @params results_p  The resutls of the parse
 */
bool
STDC::QMS::Parse_XML::parse_capability(char *filename_p,  
				   sensorCapability &results)
{
  QMS_Trace ("STDC::QMS::Parse_XML::parse_capability", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::parse_capability\n");
  
  if(!filename_p)
   {
     cerr << "STDC::QMS::Parse_XML::parse_capability:" << __LINE__ << __FILE__
	  <<endl
	  << "Mandatory parameter file name missing. Ending parse"
	  <<endl;
     return false;
   } /* end of if(!filename_p) */
  

  // We are entering a parse session, so we lock the object until we
  // are done
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  // Create and initialize the parser
  DEBUG0 (2, "DEBUG: Create and initialize the parser\n");
  this->create_parser();

  // Parse the config file
  DEBUG0 (2, "DEBUG: Parse the file\n");
  bool errorsOccured = this->parse_file(filename_p);
  DEBUG0 (2, "DEBUG: Done parsing\n");

  // If there are no errors, we handle the file
  bool success = (!errorsOccured && !this->errReporter->getSawErrors());
  if(success)
   {
     DEBUG0 (2, "DEBUG: no errors, we now handle the file\n");
     IDOM_Node *doc_p = this->parser->getDocument();
     if(doc_p)
      {
	DEBUG0 (2, "DEBUG: we now have a DOM tree\n");
	try
	 {
	   success = capability_handler(doc_p, results);
	   if(!success)
	    {
	      this->cleanup();
	      cerr << "Error  Failed to grok parsed capability data" 
		   << std::endl;
	      return success;
	    } /* end of if(!success) */
	 }
	catch (const invalid_argument& ex)
	 {
	   this->cleanup();
	   cerr << "Error reading capability file: " << ex.what() << std::endl;
	   return false;
	 }
      } /* end of if(doc_p) */
   } /* end of if(!errorsOccured && !errReporter->getSawErrors()) */
  else
   {
     cerr << "failed to parse capability file." << std::endl;
   } /* end of else */
  
  // Cleanup before exiting
  this->cleanup();
  return success;
}

/**
 * @brief Parse an in memory  QMS message
 * @return True on success, false on failure
 * @params results_p  The resutls of the parse
 * @param payload_handler A function pointer to handle the payload
 * @param payload_arg_p Arguments to pass to the payload handler
 * @param error_handler A function pointer to handle any error message
 * @param error_arg_p Arguments to pass to the error handler
 */
bool
STDC::QMS::Parse_XML::parse_message(MemBufInputSource &message,  
				    QMSMessage &results,
				    bool (*payload_handler)(IDOM_Node *doc_p,  
							    void *arg_p),
				    void *payload_arg_p,
				    void (*error_handler)(IDOM_Node *doc_p, 
							  void *arg_p),
				    void *error_arg_p)
{
  QMS_Trace ("STDC::QMS::Parse_XML::parse_message", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: STDC::QMS::parse_message\n");
  
  // We are entering a parse session, so we lock the object until we
  // are done
  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);

  // Create and initialize the parser
  DEBUG0 (2, "DEBUG: Create and initialize the parser\n");
  this->create_parser();

  // Parse the config file
  DEBUG0 (2, "DEBUG: Parse the message\n");
  bool errorsOccured = this->parse_mem(message);
  DEBUG0 (2, "DEBUG: Done parsing\n");
  
  // If there are no errors, we handle the message
  bool success = (!errorsOccured && !this->errReporter->getSawErrors());
  if(success)
   {
     DEBUG0 (2, "DEBUG: no errors, we now handle the message\n");
     IDOM_Node *doc_p = this->parser->getDocument();
     if(doc_p)
      {
	DEBUG0 (2, "DEBUG: we now have a message tree\n");
	try
	 {
	   results.sequence_no = INT_MAX;
	   results.msgDate.erase();
	   results.msgTime.erase();
	   results.sender_host.erase();
	   results.sender.id = INT_MAX;
	   results.sender.description.erase();
	   results.QMSUniqueName.category.erase();
	   results.QMSUniqueName.host.erase();
	   results.QMSUniqueName.uuid.erase();
	   results.Session.request_id = INT_MAX;
	   results.Session.data_id = INT_MAX;
	   results.Session.version = INT_MAX;
	   results.Session.repititions.count = 1;
	   results.Session.repititions.current = 0;
	   results.Session.interval = "5";
	   results.Session.scope.erase();
	   results.Session.forceReuse = false;
	   results.Session.qos_params.Priority = 10;
	   
	   DEBUG0 (2, "DEBUG: calling message handler\n");
	   success = 
	     message_handler(doc_p, results, 
			     payload_handler, payload_arg_p,
			     error_handler, error_arg_p);
	   if(!success)
	    {
	      this->cleanup();
	      cerr << "Error  Failed to grok parsed message structure" 
		   << std::endl;
	      return success;
	    } /* end of if(!success) */
	   
	 }
	catch (const invalid_argument& ex)
	 {
	   this->cleanup();
	   cerr << "Error reading message: " << ex.what() << std::endl;
	   return false;
	 }
      } /* end of if(doc_p) */
   } /* end of if(!errorsOccured && !errReporter->getSawErrors()) */
  else
   {
     cerr << "failed to parse message" << std::endl;
   } /* end of else */
  
  // Cleanup before exiting
  this->cleanup();
  return success;
}

      
     

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class vector<STDC::QMS::pubsubIDType>;
template class vector<STDC::QMS::expandedVariableType>;
template class vector<STDC::QMS::variableType>;
template class vector<STDC::QMS::ProbeDefinitionType>;
template class vector<STDC::QMS::sensorServiceType>;
template STDC::QMS::ProbeDefinitionType * __uninitialized_copy_aux<STDC::QMS::ProbeDefinitionType *, STDC::QMS::ProbeDefinitionType *>(STDC::QMS::ProbeDefinitionType *, STDC::QMS::ProbeDefinitionType *, STDC::QMS::ProbeDefinitionType *, __false_type);
template STDC::QMS::ProbeDefinitionType * __uninitialized_copy_aux<STDC::QMS::ProbeDefinitionType const *, STDC::QMS::ProbeDefinitionType *>(STDC::QMS::ProbeDefinitionType const *, STDC::QMS::ProbeDefinitionType const *, STDC::QMS::ProbeDefinitionType *, __false_type);
template STDC::QMS::ProbeDefinitionType * __uninitialized_fill_n_aux<STDC::QMS::ProbeDefinitionType *, unsigned int, STDC::QMS::ProbeDefinitionType>(STDC::QMS::ProbeDefinitionType *, unsigned int, STDC::QMS::ProbeDefinitionType const &, __false_type);
template STDC::QMS::ProbeDefinitionType * fill_n<STDC::QMS::ProbeDefinitionType *, unsigned int, STDC::QMS::ProbeDefinitionType>(STDC::QMS::ProbeDefinitionType *, unsigned int, STDC::QMS::ProbeDefinitionType const &);
template STDC::QMS::expandedVariableType * __uninitialized_copy_aux<STDC::QMS::expandedVariableType *, STDC::QMS::expandedVariableType *>(STDC::QMS::expandedVariableType *, STDC::QMS::expandedVariableType *, STDC::QMS::expandedVariableType *, __false_type);
template STDC::QMS::expandedVariableType * __uninitialized_copy_aux<STDC::QMS::expandedVariableType const *, STDC::QMS::expandedVariableType *>(STDC::QMS::expandedVariableType const *, STDC::QMS::expandedVariableType const *, STDC::QMS::expandedVariableType *, __false_type);
template STDC::QMS::expandedVariableType * __uninitialized_fill_n_aux<STDC::QMS::expandedVariableType *, unsigned int, STDC::QMS::expandedVariableType>(STDC::QMS::expandedVariableType *, unsigned int, STDC::QMS::expandedVariableType const &, __false_type);
template STDC::QMS::expandedVariableType * fill_n<STDC::QMS::expandedVariableType *, unsigned int, STDC::QMS::expandedVariableType>(STDC::QMS::expandedVariableType *, unsigned int, STDC::QMS::expandedVariableType const &);
template STDC::QMS::pubsubIDType * __uninitialized_copy_aux<STDC::QMS::pubsubIDType *, STDC::QMS::pubsubIDType *>(STDC::QMS::pubsubIDType *, STDC::QMS::pubsubIDType *, STDC::QMS::pubsubIDType *, __false_type);
template STDC::QMS::pubsubIDType * __uninitialized_copy_aux<STDC::QMS::pubsubIDType const *, STDC::QMS::pubsubIDType *>(STDC::QMS::pubsubIDType const *, STDC::QMS::pubsubIDType const *, STDC::QMS::pubsubIDType *, __false_type);
template STDC::QMS::pubsubIDType * __uninitialized_fill_n_aux<STDC::QMS::pubsubIDType *, unsigned int, STDC::QMS::pubsubIDType>(STDC::QMS::pubsubIDType *, unsigned int, STDC::QMS::pubsubIDType const &, __false_type);
template STDC::QMS::pubsubIDType * fill_n<STDC::QMS::pubsubIDType *, unsigned int, STDC::QMS::pubsubIDType>(STDC::QMS::pubsubIDType *, unsigned int, STDC::QMS::pubsubIDType const &);
template STDC::QMS::variableType * __uninitialized_copy_aux<STDC::QMS::variableType *, STDC::QMS::variableType *>(STDC::QMS::variableType *, STDC::QMS::variableType *, STDC::QMS::variableType *, __false_type);
template STDC::QMS::variableType * __uninitialized_copy_aux<STDC::QMS::variableType const *, STDC::QMS::variableType *>(STDC::QMS::variableType const *, STDC::QMS::variableType const *, STDC::QMS::variableType *, __false_type);
template STDC::QMS::variableType * __uninitialized_fill_n_aux<STDC::QMS::variableType *, unsigned int, STDC::QMS::variableType>(STDC::QMS::variableType *, unsigned int, STDC::QMS::variableType const &, __false_type);
template STDC::QMS::variableType * fill_n<STDC::QMS::variableType *, unsigned int, STDC::QMS::variableType>(STDC::QMS::variableType *, unsigned int, STDC::QMS::variableType const &);
template void fill<STDC::QMS::ProbeDefinitionType *, STDC::QMS::ProbeDefinitionType>(STDC::QMS::ProbeDefinitionType *, STDC::QMS::ProbeDefinitionType *, STDC::QMS::ProbeDefinitionType const &);
template void fill<STDC::QMS::expandedVariableType *, STDC::QMS::expandedVariableType>(STDC::QMS::expandedVariableType *, STDC::QMS::expandedVariableType *, STDC::QMS::expandedVariableType const &);
template void fill<STDC::QMS::pubsubIDType *, STDC::QMS::pubsubIDType>(STDC::QMS::pubsubIDType *, STDC::QMS::pubsubIDType *, STDC::QMS::pubsubIDType const &);
template void fill<STDC::QMS::variableType *, STDC::QMS::variableType>(STDC::QMS::variableType *, STDC::QMS::variableType *, STDC::QMS::variableType const &);
template STDC::QMS::sensorServiceType * __uninitialized_copy_aux<STDC::QMS::sensorServiceType *, STDC::QMS::sensorServiceType *>(STDC::QMS::sensorServiceType *, STDC::QMS::sensorServiceType *, STDC::QMS::sensorServiceType *, __false_type);



template STDC::QMS::sensorServiceType * __uninitialized_copy_aux<STDC::QMS::sensorServiceType const *, STDC::QMS::sensorServiceType *>(STDC::QMS::sensorServiceType const *, STDC::QMS::sensorServiceType const *, STDC::QMS::sensorServiceType *, __false_type);

template STDC::QMS::sensorServiceType * __uninitialized_fill_n_aux<STDC::QMS::sensorServiceType *, unsigned int, STDC::QMS::sensorServiceType>(STDC::QMS::sensorServiceType *, unsigned int, STDC::QMS::sensorServiceType const &, __false_type);
template void fill<STDC::QMS::sensorServiceType *, STDC::QMS::sensorServiceType>(STDC::QMS::sensorServiceType *, STDC::QMS::sensorServiceType *, STDC::QMS::sensorServiceType const &);

template STDC::QMS::sensorServiceType * fill_n<STDC::QMS::sensorServiceType *, unsigned int, STDC::QMS::sensorServiceType>(STDC::QMS::sensorServiceType *, unsigned int, STDC::QMS::sensorServiceType const &);











#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate vector<STDC::QMS::pubsubIDType>
#pragma instantiate vector<STDC::QMS::expandedVariableType>
#pragma instantiate vector<STDC::QMS::variableType>
#pragma instantiate vector<STDC::QMS::ProbeDefinitionType>
#pragma instantiate vector<STDC::QMS::sensorServiceType>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */


