//                              -*- Mode: C++ -*- 
// test_capability.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Wed Oct  3 16:44:41 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Oct 20 02:09:49 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 9
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
"$Id: test_capability.cpp,v 1.5 2001/10/21 08:54:14 srivasta Exp $";

#include "Parse_XML.h"

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

  STDC::QMS::sensorCapability config;
  bool parsed_capability = my_parser->parse_capability(filename_p, config);
  if(parsed_capability)
   {
     STDC::QMS::sensorCapability::const_iterator iter;
     for(iter = config.begin(); iter != config.end(); iter++)
      {
	// begin mandatoryServiceOfferProperties

	// begin uniqueNameType
	cout << "category:";
	if(!iter->offer_prop.QMSUniqueName.category.empty())
	 {
	   cout << iter->offer_prop.QMSUniqueName.category;
	 } /* end of if(!iter->offer_prop.QMSUniqueName.empty()) */
	cout << endl;

	if(!iter->offer_prop.QMSUniqueName.host.empty())
	 {
	   cout << "host:"
		<< iter->offer_prop.QMSUniqueName.host << endl;
	 } /* end of if(!iter->offer_prop.QMSUniqueName.host.empty()) */
	if(!iter->offer_prop.QMSUniqueName.uuid.empty())
	 {
	   cout << "uuid:"
		<< iter->offer_prop.QMSUniqueName.uuid << endl;
	 } /* end of if(!iter->offer_prop.QMSUniqueName.uuid == INT_MAX) */
	// end uniqueNameType
	// end mandatoryServiceOfferProperties

	// begin genericSensorProbeProperties
	if(!iter->generic_prop.probeType.empty())
	 {
	   cout << "Probe Type:"
		<< iter->generic_prop.probeType << endl;
	 } /* end of if(!iter->generic_prop.probeType.empty()) */
	if(iter->generic_prop.dataReusable)
	 {
	   cout << "This probe data is reuseable" << endl;
	 } /* end of if(!iter->generic_prop.QMSUniqueName.uuid == INT_MAX) */
	else
	 {
	   cout << "This probe data is NOT reuseable" << endl;
	 } /* end of else */
	// end genericSensorProbeProperties

	// begin mandatorySchemaOfferProperties
	if(! iter->schema_prop.probeSchema.empty())
	 {
	   cout << "Probe Schemea: ";
	   cout << iter->schema_prop.probeSchema;
	 } /* end of if(! iter->schema_prop.probeSchema.empty()) */
	cout << endl;

	if(!iter->schema_prop.schemaVersion.empty())
	 {
	   cout << "Schema version: ";
	   cout << iter->schema_prop.schemaVersion;
	 } /* end of if(iter->schema_prop.schemaVersion != INT_MAX) */
	cout << endl;
	// end mandatorySchemaOfferProperties
	
	// begin optionalOfferType
	STDC::QMS::optionalOfferType::const_iterator offers;
	for(offers  = iter->offer_param.begin(); 
	    offers != iter->offer_param.end(); 
	    offers++)
	 {
	   cout << "\tName:";
	   if(!offers->variable.name.empty())
	    {
	      cout << offers->variable.name;
	    } /* end of if(!offers->cariable.name.empty()) */
	   cout << endl;
	   cout << "\tValue:";
	   if(!offers->variable.value.empty())
	    {
	      cout << offers->variable.value;
	    } /* end of if(!offers->cariable.name.empty()) */
	   cout << endl;
	   if(offers->searchable)
	    {
	      cout << "\tThis is a searchable parameter" << endl;
	    } /* end of if(offers->searchable) */
	   else
	    {
	      cout << "\tThis is NOT a searchable parameter" << endl;
	    } /* end of else */
	   if(offers->maptoProperty != INT_MAX)
	    {
	      cout << "\tMap Offer to Property Number: ";
	      cout << offers->maptoProperty;
	    } /* end of if(iter->schema_prop.schemaVersion != INT_MAX) */
	   cout << endl;
	 } /* end of for(offers = iter->offer_param.begin(); offers != iter->offer_param.end(); offers++) */
	// end optionalOfferType
	
	// begin invocationType
	if(!iter->invocation_param.probeExecutable.empty())
	 {
	   cout << "\tProbe executable: "
		<< iter->invocation_param.probeExecutable << endl;
	 } /* end of if(!iter->invocation_param.probeExecutable.empty()) */
	if(!iter->invocation_param.probeXSLTFile.empty())
	 {
	   cout << "\tProbe xslt file: "
		<< iter->invocation_param.probeExecutable << endl;
	 } /* end of if(!iter->invocation_param.probeXSLTFile.empty) */
	
	vector<STDC::QMS::variableType>::const_iterator vars;
	for(vars  = iter->invocation_param.xslParameters.begin(); 
	    vars != iter->invocation_param.xslParameters.end(); 
	    vars++)
	 {
	   cout << "\tName:";
	   if(!vars->name.empty())
	    {
	      cout << vars->name;
	    } /* end of if(!vars->name.empty()) */
	   cout << endl;
	   cout << "\tValue:";
	   if(!vars->value.empty())
	    {
	      cout << vars->value;
	    } /* end of if(!vars->value.empty()) */
	   cout << endl;
	 }
	// end invocationType
      } /* end of for(iter = config.begin(); iter != config.end; inter++) */
     
   } /* end of if(parsed_capability) */
  

  // Terminate the parser before the end. This belongs in a destructor
  XMLPlatformUtils::Terminate();
  exit(EXIT_SUCCESS);             
} /* end of main() */
