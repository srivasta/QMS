//                              -*- Mode: C++ -*- 
// test_xslt.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Sat Nov 17 22:50:06 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sun Nov 18 04:35:01 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 41
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
"$Id: test_xslt.cpp,v 1.6 2001/11/20 18:14:18 srivasta Exp $";

#include <fstream>
#include <iostream>
#include <strstream>
#include <sstream>
#include <cstdlib>

#include <cstring>
#include <string>
#include <ctype.h>

#include <exception>
#include <stdexcept>

#include <Include/PlatformDefinitions.hpp>
#include <util/PlatformUtils.hpp>
#include <XalanTransformer/XalanTransformer.hpp> 

#include "Debug.h"

int
main(void)
{
  // The name of the xsl transfor file  
  const char *xsl_file_p = "remosProbes.xsl";
  
  // Initialize the Parser. 
  try 
   {
     XMLPlatformUtils::Initialize();
     // Initialize Xalan.
     XalanTransformer::initialize();
   }
  catch(const XMLException& toCatch)
   {
     cerr << "Error during Xerces-c Initialization.\n"
          << "  Exception message:"
          << toCatch.getMessage()
          << endl;
     return 1;
   }
  
  {
    
    // Create a XalanTransformer.
    XalanTransformer my_transformer;

    // Compile the stylesheet.
    const XalanCompiledStylesheet * compiled_sheet_p = 0;
    int ret = my_transformer.compileStylesheet(xsl_file_p, compiled_sheet_p);
    if(ret != 0)
     {
       std::cerr << "Error: could not compile style sheet!" << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret == 0) */
    assert(compiled_sheet_p != 0);
  
    //Start with a new request
    const int SIZE=82;
    char buffer[SIZE];
  
    string new_request;
    string modify_request;
    string pause_request;
    string stop_request;
    string result;
  
    std::cerr << "DEBUG: Caching message in QMSRemosLinkRequestnew.xml"
	      << std::endl;
  
    ifstream new_file("QMSRemosLinkRequestnew.xml", ios::in);
    if(!new_file)
     {
       std::cerr << "Error: Could not open input file QMSRemosLinkRequestnew.xml"
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(!new_file) */
  
    while(new_file.getline(buffer, SIZE))
     {
       new_request.append(buffer);
       new_request.append("\n");
     } /* end of while(new_file.getline(buffer, SIZE)) */
  
    std::cerr << "DEBUG: Caching message in QMSRemosLinkRequestModify.xml"
	      << std::endl;
    ifstream modify_file("QMSRemosLinkRequestModify.xml", ios::in);
    if(!modify_file)
     {
       std::cerr << "Error: Could not open QMSRemosLinkRequestModify.xml"
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(!modify_file) */
  
    while(modify_file.getline(buffer, SIZE))
     {
       modify_request.append(buffer);
       modify_request.append("\n");
     } /* end of while(modify_file.getline(buffer, SIZE)) */
  
    std::cerr << "DEBUG: Caching message in QMSRemosPauseRequest.xml"
	      << std::endl;
    ifstream pause_file("QMSRemosPauseRequest.xml", ios::in);
    if(!pause_file)
     {
       std::cerr << "Error: Could not open QMSRemosPauseRequest.xml"
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(!pause_file) */
  
    while(pause_file.getline(buffer, SIZE))
     {
       pause_request.append(buffer);
       pause_request.append("\n");
     } /* end of while(pause_file.getline(buffer, SIZE)) */
  
    
    std::cerr << "DEBUG: Caching message in QMSRemosStopRequest.xml"
	      << std::endl;
    ifstream stop_file("QMSRemosStopRequest.xml", ios::in);
    if(!stop_file)
     {
       std::cerr << "Error: Could not open QMSRemosStopRequest.xml"
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(!stop_file) */
  
    while(stop_file.getline(buffer, SIZE))
     {
       stop_request.append(buffer);
       stop_request.append("\n");
     } /* end of while(stop_file.getline(buffer, SIZE)) */
  
  
    std::cerr << std::endl
	      << "DEBUG: Parsing message in QMSRemosLinkRequestnew.xml"
	      << std::endl;
    string temp_input(new_request);
    std::istringstream new_input_one(temp_input);
    std::ostringstream new_result_one;
    XSLTInputSource new_source_one(&new_input_one);
    XSLTResultTarget new_result_one_target(new_result_one);

    std::cerr << "DEBUG: \tParam: msgType='new'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'new'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getIsTerminate'"));

    ret = my_transformer.transform(new_source_one, compiled_sheet_p,
				   new_result_one_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << new_result_one.str() << std::endl;

  
    temp_input = new_request;
    std::istringstream new_input_two(temp_input);
    std::ostringstream new_result_two;
    XSLTInputSource new_source_two(&new_input_two);
    XSLTResultTarget new_result_two_target(new_result_two);

    std::cerr << std::endl
	      << "DEBUG: \tParam: msgType='new'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'new'"));
    std::cerr << "DEBUG: \tParam: input='getAction'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getAction'"));
    ret = my_transformer.transform(new_source_two, compiled_sheet_p,
				   new_result_two_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << new_result_two.str() << std::endl;

    result = new_result_two.str();
    temp_input = new_request;
    std::istringstream new_input_three(temp_input);
    std::ostringstream new_result_three;
    XSLTInputSource new_source_three(&new_input_three);
    XSLTResultTarget new_result_three_target(new_result_three);

    std::cerr << std::endl
	      << "DEBUG: \tParam: msgType='new'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'new'"));
    if(result.find("exec") != string::npos)
     {
       std::cerr << "DEBUG: \tParam: input='getExecString'"
		 << std::endl;
       my_transformer.setStylesheetParam(XalanDOMString("input"),
					 XalanDOMString("'getExecString'"));
     } /* end of if(result.find("exec")) */
    else
     {
       std::cerr << "DEBUG: \tParam: input='getProbeString'"
		 << std::endl;
       my_transformer.setStylesheetParam(XalanDOMString("input"),
					 XalanDOMString("'getProbeString'"));
     } /* end of else */
  
  
    ret = my_transformer.transform(new_source_three, compiled_sheet_p,
				   new_result_three_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << new_result_three.str() << std::endl;

    // This is where we take the result apart.
    string unparsed_output = new_result_three.str();
    
    char argument[1024];    
    std::istringstream unparsed_result_stream(unparsed_output);
    while(!unparsed_result_stream.eof())
     {
       unparsed_result_stream.getline((char *)argument, 1024);
       std::cout << " '" << argument << "' " ;
     } /* end of while(unparsed_result_stream.getline()) */
    std::cout << std::endl;

    string result_out = unparsed_output;
    std::istringstream result_stream(result_out);
    vector<char *> arguments;
    // Chop up the results into individual parts
    while(!result_stream.eof())
     {
       char * arg_str = new char [1024];
       result_stream.getline((char *)arg_str, 1024);
       arguments.push_back(arg_str);
     }
    vector<char *>::iterator arg;
    char **arg_list = new char *[arguments.size() + 1];
    arg_list[arguments.size()] = 0;
    
    int i = 0;
    
    for(i=0, arg = arguments.begin(); arg != arguments.end(); i++,arg++)
     {
       arg_list[i] = 0;
       if(*arg)
	{
	  arg_list[i] = new char [strlen(*arg)];
	  strncpy(arg_list[i], *arg, strlen(*arg) + 1);
	  delete [] *arg;
	} /* end of if(arg) */
     } /* end of for(arg = arguments.begin(); arg != arguments.end(); arg++) */
    i = 0;
    while(arg_list[i])
     {
       std::cout << " '" << arg_list[i] << "' " ;
       i++;
     } /* end of while(arg_list[i]) */
    
    std::cout << std::endl;


    std::cerr << std::endl
	      << "DEBUG: Parsing message in QMSRemosLinkRequestModify.xml"
	      << std::endl;
    temp_input = modify_request;
    std::istringstream modify_input_one(temp_input);
    std::ostringstream modify_result_one;
    XSLTInputSource modify_source_one(&modify_input_one);
    XSLTResultTarget modify_result_one_target(modify_result_one);

    std::cerr << "DEBUG: \tParam: msgType='modify'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'modify'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getIsTerminate'"));
    std::cerr << "DEBUG: \tParam: collectorhost='10.0.0.2'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				      XalanDOMString("'10.0.0.2'"));
    std::cerr << "DEBUG: \tParam: collectorport='5002'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				      XalanDOMString("'5002'"));

    ret = my_transformer.transform(modify_source_one, compiled_sheet_p,
				   modify_result_one_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << modify_result_one.str() << std::endl;

  
    temp_input = modify_request;
    std::istringstream modify_input_two(temp_input);
    std::ostringstream modify_result_two;
    XSLTInputSource modify_source_two(&modify_input_two);
    XSLTResultTarget modify_result_two_target(modify_result_two);

    std::cerr << std::endl
	      << "DEBUG: \tParam: msgType='modify'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'modify'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    std::cerr << "DEBUG: \tParam: collectorhost='10.0.0.2'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				      XalanDOMString("'10.0.0.2'"));
    std::cerr << "DEBUG: \tParam: collectorport='5002'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				      XalanDOMString("'5002'"));

    std::cerr << "DEBUG: \tParam: input='getAction'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getAction'"));
    ret = my_transformer.transform(modify_source_two, compiled_sheet_p,
				   modify_result_two_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << modify_result_two.str() << std::endl;

    result = modify_result_two.str();
    temp_input = modify_request;
    std::istringstream modify_input_three(temp_input);
    std::ostringstream modify_result_three;
    XSLTInputSource modify_source_three(&modify_input_three);
    XSLTResultTarget modify_result_three_target(modify_result_three);

    std::cerr << std::endl
	      << "DEBUG: \tParam: msgType='modify'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'modify'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    std::cerr << "DEBUG: \tParam: collectorhost='10.0.0.2'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				      XalanDOMString("'10.0.0.2'"));
    std::cerr << "DEBUG: \tParam: collectorport='5002'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				      XalanDOMString("'5002'"));

    if(result.find("exec") != string::npos)
     {
       std::cerr << "Error: \tWe should not be execing here!."
		 << std::endl;
     } /* end of if(result.find("exec")) */
    std::cerr << "DEBUG: \tParam: input='getProbeString'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getProbeString'"));

    ret = my_transformer.transform(modify_source_three, compiled_sheet_p,
				   modify_result_three_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << modify_result_three.str() << std::endl;



    std::cerr << std::endl
	      << "DEBUG: Parsing message in QMSRemosPauseRequest.xml"
	      << std::endl;
    temp_input = pause_request;
    std::istringstream pause_input_one(temp_input);
    std::ostringstream pause_result_one;
    XSLTInputSource pause_source_one(&pause_input_one);
    XSLTResultTarget pause_result_one_target(pause_result_one);

    std::cerr << "DEBUG: \tParam: msgType='modify'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'modify'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getIsTerminate'"));
    std::cerr << "DEBUG: \tParam: collectorhost='10.0.0.2'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				      XalanDOMString("'10.0.0.2'"));
    std::cerr << "DEBUG: \tParam: collectorport='5002'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				      XalanDOMString("'5002'"));

    ret = my_transformer.transform(pause_source_one, compiled_sheet_p,
				   pause_result_one_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << pause_result_one.str() << std::endl;

  
    temp_input = pause_request;
    std::istringstream pause_input_two(temp_input);
    std::ostringstream pause_result_two;
    XSLTInputSource pause_source_two(&pause_input_two);
    XSLTResultTarget pause_result_two_target(pause_result_two);

    std::cerr << std::endl
	      << "DEBUG: \tParam: msgType='modify'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'modify'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    std::cerr << "DEBUG: \tParam: collectorhost='10.0.0.2'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				      XalanDOMString("'10.0.0.2'"));
    std::cerr << "DEBUG: \tParam: collectorport='5002'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				      XalanDOMString("'5002'"));

    std::cerr << "DEBUG: \tParam input='getAction'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getAction'"));
    ret = my_transformer.transform(pause_source_two, compiled_sheet_p,
				   pause_result_two_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << pause_result_two.str() << std::endl;

    result = pause_result_two.str();
    temp_input = pause_request;
    std::istringstream pause_input_three(temp_input);
    std::ostringstream pause_result_three;
    XSLTInputSource pause_source_three(&pause_input_three);
    XSLTResultTarget pause_result_three_target(pause_result_three);

    std::cerr << std::endl
	      << "DEBUG: \tParam: msgType='modify'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'modify'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    std::cerr << "DEBUG: \tParam: collectorhost='10.0.0.2'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				      XalanDOMString("'10.0.0.2'"));
    std::cerr << "DEBUG: \tParam: collectorport='5002'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				      XalanDOMString("'5002'"));

    if(result.find("exec") != string::npos)
     {
       std::cerr << "ERROR: \tWe should not be execing here!."
		 << std::endl;
     } /* end of if(result.find("exec")) */

    std::cerr << "DEBUG: \tParam: input='getProbeString'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getProbeString'"));

    ret = my_transformer.transform(pause_source_three, compiled_sheet_p,
				   pause_result_three_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << pause_result_three.str() << std::endl;




    std::cerr << std::endl
	      << "DEBUG: Parsing message in QMSRemosStopRequest.xml"
	      << std::endl;
    temp_input = stop_request;
    std::istringstream stop_input_one(temp_input);
    std::ostringstream stop_result_one;
    XSLTInputSource stop_source_one(&stop_input_one);
    XSLTResultTarget stop_result_one_target(stop_result_one);

    std::cerr << "DEBUG: \tParam: msgType='modify'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'modify'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getIsTerminate'"));
    std::cerr << "DEBUG: \tParam: collectorhost='10.0.0.2'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				      XalanDOMString("'10.0.0.2'"));
    std::cerr << "DEBUG: \tParam: collectorport='5002'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				      XalanDOMString("'5002'"));

    ret = my_transformer.transform(stop_source_one, compiled_sheet_p,
				   stop_result_one_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << stop_result_one.str() << std::endl;

  
    temp_input = stop_request;
    std::istringstream stop_input_two(temp_input);
    std::ostringstream stop_result_two;
    XSLTInputSource stop_source_two(&stop_input_two);
    XSLTResultTarget stop_result_two_target(stop_result_two);

    std::cerr << std::endl
	      << "DEBUG: \tParam: msgType='modify'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'modify'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    std::cerr << "DEBUG: \tParam: collectorhost='10.0.0.2'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				      XalanDOMString("'10.0.0.2'"));
    std::cerr << "DEBUG: \tParam: collectorport='5002'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				      XalanDOMString("'5002'"));

    std::cerr << "DEBUG: \tParam input='getAction'."
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getAction'"));
    ret = my_transformer.transform(stop_source_two, compiled_sheet_p,
				   stop_result_two_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << stop_result_two.str() << std::endl;

    result = stop_result_two.str();
    temp_input = stop_request;
    std::istringstream stop_input_three(temp_input);
    std::ostringstream stop_result_three;
    XSLTInputSource stop_source_three(&stop_input_three);
    XSLTResultTarget stop_result_three_target(stop_result_three);

    std::cerr << std::endl
	      << "DEBUG: \tParam: msgType='modify'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				      XalanDOMString("'modify'"));
    std::cerr << "DEBUG: \tParam: input='getIsTerminate'"
	      << std::endl;
    std::cerr << "DEBUG: \tParam: collectorhost='10.0.0.2'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				      XalanDOMString("'10.0.0.2'"));
    std::cerr << "DEBUG: \tParam: collectorport='5002'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				      XalanDOMString("'5002'"));

    if(result.find("exec") != string::npos)
     {
       std::cerr << "Error: \tWe should not be execing here!."
		 << std::endl;
     } /* end of if(result.find("exec")) */
    std::cerr << "DEBUG: \tParam: input='getProbeString'"
	      << std::endl;
    my_transformer.setStylesheetParam(XalanDOMString("input"),
				      XalanDOMString("'getProbeString'"));

    ret = my_transformer.transform(stop_source_three, compiled_sheet_p,
				   stop_result_three_target);
    if(ret)
     {
       std::cerr << "Error running the transform" 
		 <<  my_transformer.getLastError()
		 << std::endl;
       exit(EXIT_FAILURE);  
     } /* end of if(ret) */
  
    std::cout << stop_result_three.str() << std::endl;
  
  }
  
  // Terminate Xalan.  
  XalanTransformer::terminate();
  // Terminate the parser before the end. Causes a segfault
  XMLPlatformUtils::Terminate();

  std::cerr << "DEBUG: all done:" << std::endl;
  
  exit(EXIT_SUCCESS);             
} /* end of main() */

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class vector<char *>;
template char ** fill_n<char **, unsigned int, char *>(char **, unsigned int, char * const &);
template void fill<char **, char *>(char **, char **, char * const &);
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate class vector<char *>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
