//                              -*- Mode: C++ -*- 
// bench_message.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Wed Oct  3 16:44:41 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Dec  5 15:43:22 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 30
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
"$Id: bench_message.cpp,v 1.1 2001/12/05 23:28:27 srivasta Exp $";

#include <exception>

#include <ace/High_Res_Timer.h>


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
  /// A high resolution (nanosec) time
  ACE_High_Res_Timer timer;
  /// Time stamps for receiving data
  ACE_hrtime_t time_taken;

  STDC::QMS::QMSMessage config;

  MemBufInputSource *buffer_p = 0;
  
  DEBUG0(4, "Starting run");
  timer.start();

  for(int run = 0; run < 1000; run++)
   {
     STDC::QMS::Parse_XML *my_parser = 
       new STDC::QMS::Parse_XML::Parse_XML();

     buffer_p = 
       new MemBufInputSource((const XMLByte*) message_p, strlen(message_p),
			     "QMSMessage",false);
     bool parsed_message = my_parser->parse_message(*buffer_p, config);
     if(buffer_p)
      {
	delete buffer_p;
	buffer_p = 0;
      } /* end of if(buffer_p) */
   } /* end of for(int run = 0; run < 1000; run++) */
  timer.stop();
  timer.elapsed_microseconds(time_taken);
  DEBUG0(4, "Finished run");

  std::cout << " It took " << time_taken 
	    << " microseconds to parse the message 1000 times."
	    << std::endl;
  
  // Terminate the parser before the end. This belongs in a destructor
  XMLPlatformUtils::Terminate();
  exit(EXIT_SUCCESS);             
} /* end of main() */
