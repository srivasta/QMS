//                              -*- Mode: C++ -*- 
// Parse_XML.h --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Wed Oct  3 12:44:41 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Mon Dec 10 19:59:20 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 67
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

/** @file Parse_XML.h
 *  @ingroup Utilities
 *  @brief A convenient interface to parsing QMS XML documents
 *
 * $Id: Parse_XML.h,v 1.22 2001/12/11 05:10:23 srivasta Exp $
 */


#ifndef _PARSE_XML_H_
#define _PARSE_XML_H_

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctype.h>

#include <vector>
#include <exception>
#include <stdexcept>

#include "ace/Synch.h"
#include "ace/Thread.h"


#include <idom/IDOM.hpp>
#include <idom/IDOM_DOMException.hpp>
#include <parsers/IDOMParser.hpp>
#include <util/PlatformUtils.hpp>
#include <framework/MemBufInputSource.hpp>
#include <util/XMLString.hpp>
#include <util/TranscodingException.hpp>

#include <util/XercesDefs.hpp>
#include <sax/SAXParseException.hpp>
#include <sax/ErrorHandler.hpp>

#include "Debug.h"


/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

/** @class IDOMTreeErrorReporter
 *  @ingroup Utilities
 *  @brief A convenience class for handling errors
 *
 *  This class is used as an abstraction for the details of
 *  parsing the contents of QMS XML documents and converting the
 *  relevant contents into C++ data structures
 */
class IDOMTreeErrorReporter : public ErrorHandler
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  /// Constructor
  IDOMTreeErrorReporter() : fSawErrors(false){}
  /// Destructor
  ~IDOMTreeErrorReporter(){}

  // -----------------------------------------------------------------------
  //  Implementation of the error handler interface
  // -----------------------------------------------------------------------
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

using namespace std;

namespace STDC 
{
  namespace QMS 
  {
    //                    BEGIN Generically useful Data Types

    /**
     * Defining a generically useful variable element with a name and
     * value pair. Useful in the creation of configuration files
     */
    struct variableType 
    {
      string name;
      string value;
    };
    
    /**
     * Restricting the URI's referenced for schemas to file based
     * URL's to avoid having to build in HTTP libraries into the
     * Sensors for now.
     */
    typedef string QMSSchemaURIType;

    /**
     * Restricting the URI's referenced for XSL transforms to file based
     * URL's to avoid having to build in HTTP libraries into the
     * Sensors for now.
     */
    typedef string QMSTransformURIType;
    
    /**
     * Restricting version numbers to be positive decimal numbers
     * with two digits after decimal
     */
    typedef string versionType;
    /**
     * Datatype for representing IP addresses.  Examples,
     * 129.83.64.255, 64.128.2.71, etc.
     * This datatype restricts each field of the IP address
     * to have a value between zero and 255, i.e.,
     * [0-255].[0-255].[0-255].[0-255]
     */
    typedef string ipv4AddressType;
    
    /**
     * This type will be used for supplier ID and recipient ID's in
     * the message. Allocation supplier ID's between 1-1000 for
     * internal QMS use for now. Hence the derived type. This
     * supplierID will be generated by the QMS Trader and allocated
     * to each supplier upon request.
     */
    struct pubsubIDType 
    {
      unsigned long id;
      string description;
    };
    
    /**
     * This is currently a string. This is used to register the
     * offer in the QMS Trader. At a later point, this will get
     * mapped to CIM Schemas at which point the definition of this
     * type will change appropriately
     */
    struct uniqueNameType 
    {
      string category;
      ipv4AddressType host;
      string uuid;
    };
    
    //      END Generically Useful Data Types

    //      BEGIN QMS SESSION ELEMENTS
    /*
     * QMS Session Elements. Separating them out from inline to
     * improve readability and to help people understand Session more
     * easily 
     */

    /**
     * This is a requestID that will be generated by the
     * sender each time a request is sent to a supplier of
     * data. This requestID will be used to maintain the notion
     * of a session. This will allow the sender to later modify
     * the request by sending another request to the supplier
     * with the same requestID but with a different version
     * number. Thus the supplier will know to modify the
     * existing request it is servicing as opposed to starting
     * up another data stream to service this
     * request. This will allow the sender to terminate the
     * request if it is no longer interested in the
     * data. Preferably this will be a UUID of some sort. The
     * supplier of data will also send out the same requestID
     * in its response.
     */
    typedef unsigned long requestID;
    
    /**
     * The default value of this element is "0". If the request is
     * modified by the sender and the session is now modified to send
     * a different stream of data, the version number is
     * incremented. This will enable the supplier of data to realize
     * that the data is for the same session, but just modified.
     */
    typedef unsigned long versionNumber;
    
    /**
     * This is the dataID generated by the supplier of data and
     * incremented per message that the supplier sends out. This will
     * help establish the order of the data that is sent out. Similar
     * to the RequestID, this will be a UUID as well.
     */
    typedef unsigned long dataID;
    
    /**
     * This is a parameter that will be used by the Sensor to
     * determine how many times to send the data requested. Default
     * value will be 1. "current" will be used by the supplier of data
     * to indicate what the count is that it's currently on.
     */
    struct minRepetitions
    {
      unsigned long count;
      unsigned long current;
    };
    
    /**
     * This parameter defines the interval to be used by the Sensor
     * between repeated executions of the request for data. Default
     * value will be 5 seconds.
     */
    typedef string minRepeatInterval;
    
    /**
     * Depending on the nature of the probe that is providing the
     * data, the Sensor will have the ability to tag the data as
     * reusable or not. For example, a CPU probe may tag its data as
     * being reusable. In this case, a request from client A will
     * start the probe data flowing, but since there may be other
     * requests that later originate from other clients, that are also
     * being serviced by the same probe, it is essential to tag this
     * data as being "Private" when it is meant only for the original
     * request generator or "Public", when there are multiple
     * consumers of the data. The client may also request that the
     * data should be sent marked "Private", so that the data message
     * will contain a msgDestination element. If the data comes from a
     * reusable probe, then the forceReuse flag will need to be set
     * too.
     */
    typedef string  dataScope;
    
    /**
     * If the probe is one that generates reusable data, but the
     * sender of the request wishes to force the Sensor to start
     * another probe just for it, this flag will permit that.
     */
    typedef bool forceReuseType;
    
    /**
     * QoS Parameters that will be interpreted by the Sensor to
     * provide high priority handling by the Sensor, to provide high
     * priority scheduling by the Event Channel etc. This is a
     * placeholder as more work needs to be done here.
     */
    struct QoSParameters 
    {
      unsigned long Priority;
    };
    
    /**
     * This type encapsulates all the parameters that will be used to
     * establish the notion of a Session between the suppliers and the
     * consumers.
     */
    struct sessionType
    {
      requestID         request_id;
      dataID            data_id;
      versionNumber     version;
      minRepetitions    repititions;
      minRepeatInterval interval;
      dataScope         scope;
      forceReuseType    forceReuse;
      QoSParameters     qos_params;
    };
    
    //      END QMS SESSION ELEMENTS 

    //      BEGIN QMS MESSAGE ELEMENTS

    /**
     * A Sequence Number to serve as a unique ID per message.
     */
    typedef unsigned long msgSequenceNo;
    
    /**
     * This is the IP address of the host from which this message is
     * originating. This could be correlated to the SupplierID by
     * querying the QMS Trader as well.
     */
    typedef ipv4AddressType originatingHost;
    
    /**
     * All QMS Sensors and QMS Active Clients will obtain this
     * supplier ID from the QMS Trader and use this to identify who is
     * generating this message.
     */
    typedef pubsubIDType msgSender;
    
    /**
     * All QMS Sensors will read this element to determine if they
     * should further process the message. If the message has a
     * destinationID and that is not the same as the Sensor's
     * SupplierID, the message will be discarded.
     */
    typedef pubsubIDType msgDestination;
    
    /**
     * The intended recipient of a message could be someone other than
     * the generator of the request.
     */
    typedef pubsubIDType msgReplyTo;
    
    //  payload
    //     This is where the actual payload of the QMS Message is
    //     carried. This payload is not viewed by the Sensor and
    //     is passed on after the appropriate transform is

    // error
    //  Any errors generated by the QMS Sensors, clients or
    //  infrastructure will be carried in this element. Since we have not
    //  established any structure to the error format yet, this is
    //  just a string for now.
    
    /**
     * The headers contained in a QMS message. 
     *
     */
    struct QMSMessage
    {
      msgSequenceNo                sequence_no;
      string                       msgDate;
      string                       msgTime;
      originatingHost              sender_host;
      msgSender                    sender;
      vector<msgDestination>       destinations;
      vector<msgReplyTo>           reply_tos;
      uniqueNameType               QMSUniqueName;
      sessionType                  Session;
    };
    
    // END QMS MESSAGE ELEMENTS
    // BEGIN CAPABILITY AND CONFIGURATION FILE ELEMENTS

    /**
     * There are three basic types of probes that are dealt with in
     * different ways by the Sensor upon deployment
     */
    typedef string typeofProbeType;
    /**
     * Similar to the variable type, except that this also has a
     * property that tags the element as being searcheable, and maps
     * it to a pre defined searchable property in the trading service
     * offer service type
     */
    struct expandedVariableType
    {
      struct variableType variable;
      bool                searchable;
      unsigned int        maptoProperty;
    };
    

    /**
     * This element will contain all the optional parameters that will
     * be exported to the QMS Trader. This will contain name/value
     * pairs. Also indicated will be whether this particular property
     * is searchable and to what QMS Trader generic property name this
     * should be mapped.
     */;
    typedef  vector<expandedVariableType> optionalOfferType;
    
    /**
     * This type contains the parameters needed for the Sensor to
     * actively deploy and use the probe. The sensor relies on a
     * parameter named "input" which it sends to the XSL Transform
     * engine along with the XSL file indicated in
     * probeXSLTFile. "input" can take a value of "makeDecision",
     * "getExecString", "getProbeString". The elements in
     * xslParameters constitute other parameters that the Sensor sends
     * to the XSLT engine. Additionally, the location of the actual
     * binary to be executed will be platform dependent.
     */
    struct invocationType
    {
      string               probeExecutable;
      QMSTransformURIType  probeXSLTFile;
      vector<variableType> xslParameters;
    };

    /**
     * This type contains additional name value pairs that are of
     * interest to the probe (analogous to the xslParameters for
     * external probes)
     */
    typedef vector<variableType> instanceType;


    /**
     * Every probe that has a Sensor make an offer on its behalf in
     * the QMS Trader must have a pointer to the XML Schema that it is
     * using to represent its data. This should be available to the
     * Sensor as well as the clients that wish to communicate with it,
     * thus facilitating the validation of the XML data that is
     * created. Additional information needed for the sensor to figure
     * out how to handle the probe is included probeSchema - the URI
     * to the schema used by the probe schemaVersion - version of the
     * schema
     */
    struct mandatorySchemaOfferProperties
    {
      QMSSchemaURIType probeSchema;
      versionType      schemaVersion;
    };
    

    /**
     * These are the name=value pairs that are absolutely mandatory
     * and every entity making an offer has to provide these. This
     * refers to the QMSUniqueName corresponding to the probe. Note
     * that the host and uuid part of the QMSUniqueName will be
     * generated by the instance of the object reading this capability
     * or config file, so the type is restricted to remove those two
     * elements.
     */
    struct mandatoryServiceOfferProperties
    {
      uniqueNameType QMSUniqueName;
    };
    

    /**
     * If the entity making the offer also provides a CORBA interface
     * (all QMS Citizens do and other clients may as well) we'd like
     * to identify the IDL interfaces they offer up to the world with
     * specific version numbers. This will permit clients to figure
     * out if they are using the right version of the IDL interface
     * while trying to talk to the CORBA entity.
     */
    struct mandatoryCorbaOfferProperties
    {
      versionType       interfaceVersion;
      string            interfaceDescription;
    };
    
    /**
     * These are properties defined for the probe in the capabilities
     * file that will allow the Sensor to make a determination as to
     * how to handle the deployment and use of the data provided by
     * the probe.
     *   probeType - continuous or oneshot
     *   dataReusable - Whether the probe data can be reused
     */
    struct genericSensorProbeProperties
    {
      typeofProbeType probeType;
      bool            dataReusable;
    };
    
    /**
     * The Probe Definition list. The Probe has some configuration
     * parameters that are required by the Generic Sensor to figure
     * out what Service it provides and what to do with
     * it. Additionally there are some mandatory offer properties such
     * as the SchemaOffer that the Probe needs to define. All of these
     * put together will generate a Service that the Sensor will
     * provide when it reads this probe definition.
     */
    struct ProbeDefinitionType
    {
      genericSensorProbeProperties    generic_prop;
      mandatoryServiceOfferProperties offer_prop;
      mandatorySchemaOfferProperties  schema_prop;
      optionalOfferType               offer_param;
      invocationType                  invocation_param;
    };
    

    /**
     * The Sensor capability file consists of many fragments that are
     * put into the file by each Probe that the sensor is capable of
     * providing data for.
     */
    typedef vector<ProbeDefinitionType> sensorCapability;
    

    /**
     * Each Sensor offers many services to the QMS world and each of
     * those services will make offers into the QMS Trader. Since each
     * Sensor implements the Command and Control Corba interface, at a
     * minimum, there will be a Sensor service that will use the
     * mandatoryCorbaOfferProperties in the choice below. This is the
     * case with the Generic Sensor. However, if the QMS citizen
     * (Sensor) offers up other services from built-in probes, for
     * instance, then it makes the corresponding offers in the QMS
     * Trader again.
     */
    struct sensorServiceType
    {
      genericSensorProbeProperties    generic_prop;
      mandatoryServiceOfferProperties offer_prop;
      mandatorySchemaOfferProperties  schema_prop;
      optionalOfferType               offer_param;
      instanceType                    Instance;
    };
    
    /**
     * The Sensor configuration file will have all the elements that
     * will be necessary for the Sensor to make an offer to the QMS
     * Trader. Note that not all Sensors will be passive either. There
     * may be Sensors that have Probes built into them and will
     * correspondingly make the requisite offers into the Trader
     */
    struct sensorConfiguration
    {  
      QMSSchemaURIType                QMS_Schema;
      mandatoryServiceOfferProperties offer_prop;
      mandatoryCorbaOfferProperties   corba_prop;
      optionalOfferType               offer_param;
      instanceType                    Instance;
      vector<sensorServiceType>       sensorServices;
    };
    
    /** @class Parse_XML
     *  @ingroup Utilities
     *  @brief A convenience class for parsing QMS XML documents
     *
     *  This class is used as an abstraction for the details of
     *  parsing the contents of QMS XML documents and converting the
     *  relevant contents into C++ data structures
     */
    class Parse_XML
    {
    public:
      /// The default constructor for the classParse_XML
      Parse_XML();
      // The copy constructor
      Parse_XML(const Parse_XML& rhs);
      // The assignment operator
      Parse_XML& operator=(const Parse_XML& rhs);
      
      /// the default address-of operators
      Parse_XML* operator&()             { return this; };
      const Parse_XML* operator&() const { return this; };
      
      /// the destructor
      ~Parse_XML();
      
      /// Parse a QMS citizen configuration file
      bool parse_config(char *filename_p, sensorConfiguration &results);
      /// parse a sensor capability file
      bool parse_capability(char *filename_p, sensorCapability &results);
      /// PArse an in memory QMS message
      bool parse_message(MemBufInputSource &message, QMSMessage &results,
			 bool (*payload_handler)(IDOM_Node *doc_p,
						 void *arg_p) = 0,
			 void *payload_arg_p = 0,
			 void (*error_handler)(IDOM_Node *doc_p,
					       void *arg_p) = 0,
			 void *error_arg_p = 0);
      
    protected:
      /// Get the text value of a leaf node
      char * get_child_value(IDOM_Node *node_p);
      
      /// Handle the session element
      void session_handler(IDOM_Node *node_p, sessionType &results);

      /// Handle a QMS citizen configuration element
      void sensorConfiguration_handler(IDOM_Node *node_p, 
				       struct sensorConfiguration &results);
      /// Handle the sensor service elements for built-in probes
      void sensorService_element_handler(IDOM_Node *node_p, 
					 struct sensorServiceType &results);
      ///  Handle a sensor capability file detailing external probes
      void sensorCapability_handler(IDOM_Node *node_p, 
				    sensorCapability &results);
      ///  Handle a QMS message
      bool QMSMessage_handler(IDOM_Node *node_p, QMSMessage &result,
			      bool (*payload_handler)(IDOM_Node *doc_p, 
						      void *arg_p) = 0,
			      void *payload_arg_p = 0,
			      void (*error_handler)(IDOM_Node *doc_p, 
						    void *arg_p) = 0,
			      void *error_arg_p = 0);
      /// Handle the unique name type
      void uniq_name_element_handler(IDOM_Node *node_p,
				     uniqueNameType& results);
      ///   Handle the generic sensor probe properties elements    
      void genericSensorProbeProperties_handler(IDOM_Node *child_p, 
	                               genericSensorProbeProperties &results);
      /// Handle the mandatory service offer properties
      void mandatoryServiceOfferProperties_handler(IDOM_Node *child_p, 
		                   mandatoryServiceOfferProperties &results);
      /// Handle the mandatory schema offer properties
      void mandatorySchemaOfferProperties_handler(IDOM_Node *child_p,
                                      mandatorySchemaOfferProperties &results);
      /// Handle the mandatory Corba offer properties
      void mandatoryCorbaOfferProperties_handler(IDOM_Node *child_p, 
				       mandatoryCorbaOfferProperties &results);
      ///  Handle the probe elements
      void probe_element_handler(IDOM_Node *node_p, 
				 ProbeDefinitionType &results);
      /// Handle the instance element
      void instance_element_handler(IDOM_Node *node_p, 
				    vector<variableType> &results);
      /// Handle the invocation element
      void invoke_element_handler(IDOM_Node *node_p, invocationType &results);
      /// Handle the odder parameters
      void offer_element_handler(IDOM_Node *node_p,optionalOfferType &results);
      ///  Handle the expanded variable type
      void expanded_variable_element_handler(IDOM_Node *node_p,
					     expandedVariableType &results);
      /// Handle the variable type
      void variable_element_handler(IDOM_Node *node_p, variableType &results);
      /// Handle the pubsubIDType_ type
      void pubsubIDType_handler(IDOM_Node *node_p, pubsubIDType &results);
      /// Handle the QoSParameters type
      void QoSParameters_handler(IDOM_Node *node_p, QoSParameters &results);
      /// Handle the minRepetitions type
      void minRepetitions_handler(IDOM_Node *node_p, minRepetitions &results);
      
      /// Cleanup the error reporter and the parser and reclaim resources
      void cleanup(void);
      /// Create a new XML parser and initialize it
      void create_parser(void);
      /// Parse an XML file 

      bool parse_file(char *filename_p);
      /// Parse an in memory buffer
      bool parse_mem(MemBufInputSource &message);
      
      // Handle the tope level details of the file
      /// handle a config element
      bool config_handler(IDOM_Node *doc_p, sensorConfiguration &results);
      /// handle the capability element
      bool capability_handler(IDOM_Node *doc_p, sensorCapability &results);
      /// Handle the message element
      bool message_handler(IDOM_Node *doc_p, QMSMessage &results,
			   bool (*payload_handler)(IDOM_Node *doc_p,
						 void *arg_p) = 0,
			   void *payload_arg_p = 0,
			   void (*error_handler)(IDOM_Node *doc_p,
						 void *arg_p) = 0,
			   void *error_arg_p = 0);
      
      /// A pointer to our own parser copy
      IDOMParser *parser;
      /// The method to handle errors
      IDOMTreeErrorReporter *errReporter;
      
    private:
      /// Set a mutex to guard the data (lock the object while parsing)
      ACE_Thread_Mutex asset_guard;
      
    };	// end of class Parse_XML
  };
};

#endif /* _PARSE_XML_H_ */
