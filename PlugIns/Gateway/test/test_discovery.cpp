//                              -*- Mode: C++ -*- 
// test_request.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
// Created On       : Mon Dec 10 22:45:26 2001
// Created On Node  : glaurung.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Dec 12 02:50:03 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 8
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
"$Id: test_discovery.cpp,v 1.2 2001/12/12 09:35:20 srivasta Exp $";

#include <exception>


#include "Parse_BV_Request.h"
static const char*  message_p = 
"\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>                                 \n\
								           \n\
<!-- *****************************************************************     \n\
 *** Copyright (c) 2001, System/Technology Development Corporation .       \n\
 ***                						           \n\
 *** Filename:      BVdiscover.xml				           \n\
 *** Version:       1.0						           \n\
 *** Description:   BVT to BVGateway Discover request		           \n\
 ***                						           \n\
 *** Author:        Amarendranath Vadlamudi <nath@vedam>	           \n\
 *** Created at:    Sun Dec  9 17:48:18 2001			           \n\
 *** Modified by:   Amarendranath Vadlamudi <nath@vedam>	           \n\
 *** Modified at:   Sun Dec  9 23:36:53 2001			           \n\
 *** Status:        Experimental, do not distribute.		           \n\
 *** Update count:  24						           \n\
 ***************************************************************** -->     \n\
								           \n\
<discover xmlns=\"http://www.stdc.com/2001/QMS/Plugins/BVGateway\"         \n\
  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"	           \n\
  xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"		           \n\
  xsi:schemaLocation=						           \n\
  \"http://www.stdc.com/2001/QMS/Plugins/BVGateway BVGateway.xsd\">        \n\
  <request>							           \n\
    <BVTlistenAddress>						           \n\
      <host>10.0.0.1</host>					           \n\
      <port>4001</port>						           \n\
    </BVTlistenAddress>						           \n\
    <resource>							           \n\
      <QMSUniqueName>						           \n\
        <qms:category>QMS_CPU</qms:category>			           \n\
      </QMSUniqueName>						           \n\
      <QMSUniqueName>						           \n\
        <qms:category>HelloWorldProbe</qms:category>		           \n\
      </QMSUniqueName>						           \n\
    </resource>							           \n\
  </request>   							           \n\
</discover>    							           \n\
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

  STDC::QMS::Parse_BV_Request *my_parser = 
    new STDC::QMS::Parse_BV_Request();

  MemBufInputSource *buffer_p = new MemBufInputSource((const XMLByte*) 
                                                      message_p,
                                                      strlen(message_p),
                                                      "QMSMessage",
                                                      false);

  STDC::QMS::BV_RequestType config;
  bool parsed_message = my_parser->parse_bv_request(*buffer_p, config);
  
  if(parsed_message)
   {
     if(config.isDiscovery)
      {
	std::cout << "We  have a discovery request" << std::endl
		  << "   Socket Host = " << config.discover_request.address.host
		  << std::endl
		  << "   Socket Port = " << config.discover_request.address.port
		  << std::endl
		  << "   Resource list"  << std::endl
	  ;
	vector<STDC::QMS::uniqueNameType>::const_iterator names;
	for(names = config.discover_request.resources.begin(); 
	    names != config.discover_request.resources.end();
	    names++)
	 {
	   std::cout << "      Category = " << names->category << std::endl;
	   if(!names->host.empty())
	    {
	      std::cout <<"      Host = " << names->host << std::endl;
	    } /* end of if(!names->host.empty()) */
	   if(!names->uuid.empty())
	    {
	      std::cout << "      UUID = " << names->uuid << std::endl;
	    } /* end of if(!names->uuid.empty()) */	     	     
	 }
      } /* end of if(config.isDiscovery) */
     else
      {
	std::cout << "We  have a resource request" << std::endl
		  << "    Request id = " << config.data_request.request_id
		  << std::endl
		  << "    QMSUniqueName catgory = "
		  << config.data_request.QMSUniqueName.category
		  << std::endl
		  << "    QMSUniqueName host = "
		  << config.data_request.QMSUniqueName.host
		  << std::endl
		  << "    QMSUniqueName uuid = "
		  << config.data_request.QMSUniqueName.uuid
		  << std::endl
		  << "    Repeat interval = " << config.data_request.interval
		  << std::endl
		  << "    Action = " << config.data_request.action
		  << std::endl
	  ;
	
      } /* end of else */     
   } /* end of if(parsed_message) */
  // Terminate the parser before the end. This belongs in a destructor
  XMLPlatformUtils::Terminate();
  exit(EXIT_SUCCESS);             
} /* end of main() */
