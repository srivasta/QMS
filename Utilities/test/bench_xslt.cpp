//                              -*- Mode: C++ -*- 
// bench_xslt.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Sat Nov 17 22:50:06 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Dec  5 16:35:21 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 48
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
"$Id: bench_xslt.cpp,v 1.1 2001/12/06 01:42:14 srivasta Exp $";

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
#include <ace/High_Res_Timer.h>

int
main(void)
{
  // The name of the xsl transfor file  
  const char *xsl_file_p = "remosProbes.xsl";
  int ret = 0;
  
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

  //Start with a new request
  const int SIZE=82;
  char buffer[SIZE];
     
  string new_request;
  string result;
  
  std::cerr << "DEBUG: Caching message in QMSRemosLinkRequestnew.xml"
	    << std::endl;
     
  ifstream new_file("QMSRemosLinkRequestnew.xml", ios::in);
  if(!new_file)
   {
     std::cerr << "Error: Could not open file QMSRemosLinkRequestnew.xml"
	       << std::endl;
     exit(EXIT_FAILURE);  
   } /* end of if(!new_file) */
     
  while(new_file.getline(buffer, SIZE))
   {
     new_request.append(buffer);
     new_request.append("\n");
   } /* end of while(new_file.getline(buffer, SIZE)) */
  

  std::cerr << std::endl
	    << "DEBUG: Parsing message in QMSRemosLinkRequestnew.xml"
	    << std::endl;
  /// A high resolution (nanosec) time
  ACE_High_Res_Timer timer;
  /// Time stamps for receiving data
  ACE_hrtime_t time_taken;
    
  DEBUG0(4, "Starting run");
  timer.start();
    
  for(int run = 0; run < 1000; run++)
   {
     // Create a XalanTransformer.
     XalanTransformer my_transformer;
     
     string temp_input(new_request);
     std::istringstream new_input_one(temp_input);
     std::ostringstream new_result_one;
     XSLTInputSource new_source_one(&new_input_one);
     XSLTResultTarget new_result_one_target(new_result_one);
     
     my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				       XalanDOMString("'new'"));
     my_transformer.setStylesheetParam(XalanDOMString("input"),
				       XalanDOMString("'getIsTerminate'"));
     my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				       XalanDOMString("'10.0.0.2'"));
     my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				       XalanDOMString("'5002'"));
     
     ret = my_transformer.transform(new_source_one, xsl_file_p,
				    new_result_one_target);
     if(ret)
      {
	std::cerr << "Error running the transform" 
		  <<  my_transformer.getLastError()
		  << std::endl;
	exit(EXIT_FAILURE);  
      } /* end of if(ret) */
     
     temp_input = new_request;
     std::istringstream new_input_two(temp_input);
     std::ostringstream new_result_two;
     XSLTInputSource new_source_two(&new_input_two);
     XSLTResultTarget new_result_two_target(new_result_two);
     
     my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				       XalanDOMString("'new'"));
     my_transformer.setStylesheetParam(XalanDOMString("input"),
				       XalanDOMString("'getAction'"));
     my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				       XalanDOMString("'10.0.0.2'"));
     my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				       XalanDOMString("'5002'"));
     ret = my_transformer.transform(new_source_two, xsl_file_p,
				    new_result_two_target);
     if(ret)
      {
	std::cerr << "Error running the transform" 
		  <<  my_transformer.getLastError()
		  << std::endl;
	exit(EXIT_FAILURE);  
      } /* end of if(ret) */
       
     result = new_result_two.str();
     temp_input = new_request;
     std::istringstream new_input_three(temp_input);
     std::ostringstream new_result_three;
     XSLTInputSource new_source_three(&new_input_three);
     XSLTResultTarget new_result_three_target(new_result_three);
     
     my_transformer.setStylesheetParam(XalanDOMString("collectorhost"),
				       XalanDOMString("'10.0.0.2'"));
     my_transformer.setStylesheetParam(XalanDOMString("collectorport"),
				       XalanDOMString("'5002'"));
     my_transformer.setStylesheetParam(XalanDOMString("msgType"),
				       XalanDOMString("'new'"));
     if(result.find("exec") != string::npos)
      {
	my_transformer.setStylesheetParam(XalanDOMString("input"),
					  XalanDOMString("'getExecString'"));
      } /* end of if(result.find("exec")) */
     else
      {
	my_transformer.setStylesheetParam(XalanDOMString("input"),
					  XalanDOMString("'getProbeString'"));
      } /* end of else */
     
     
     ret = my_transformer.transform(new_source_three, xsl_file_p,
				    new_result_three_target);
     if(ret)
      {
	std::cerr << "Error running the transform" 
		  <<  my_transformer.getLastError()
		  << std::endl;
	exit(EXIT_FAILURE);  
      } /* end of if(ret) */
   }
  timer.stop();
  timer.elapsed_microseconds(time_taken);
  DEBUG0(4, "Finished run");

  std::cout << " It took " << time_taken 
	    << " microseconds to run the three transforms 1000 times."
	    << std::endl;
  
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
