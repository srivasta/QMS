//                              -*- Mode: C++ -*- 
// test_Push_Supplier.cpp --- 
// Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
// Created On       : Mon Aug 13 12:18:43 2001
// Created On Node  : ember.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Mon Aug 13 12:26:58 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 1
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
static const char* version = "$Id: test_Push_Supplier.cpp,v 1.4 2001/10/21 08:54:12 srivasta Exp $";

#include "EC_Adapter/Push_Supplier.h"
#include "Debug.h"


int
main(int argc, char *argv[])
{
  char * ecname_p = (char *) "QMS_Channel";
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
             << "\t-ecname NAME   : The name of the event channel"  << endl
             << "\t-e      NAME   : The name of the event channel"  << endl
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
     if (! strcmp((argv[i] + j), "ecname") || strchr((argv[i] + j), 'e'))
      {
        ecname_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
        strcpy(ecname_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (DEBUG_L_ERROR, "unknown argument %s", argv[i] );
   }

  STDC::QMS::Push_Supplier supplier;
  STDC::QMS::CORBA_Handles handles;

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {

	  handles.init(argc, argv, "test_supplier", ACE_TRY_ENV);
	  ACE_TRY_CHECK;

	  handles.add_event_channel(ecname_p, ACE_TRY_ENV);
	  ACE_TRY_CHECK;

      //supplier.init(handles, 20000, 20001);
	  supplier.init(handles, 2416, 20001);
      ACE_TRY_CHECK;
      
      supplier.connect(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_SupplierQOS_Factory &qos = supplier.get_subscription();
      ACE_TRY_CHECK;
      
      supplier.set_subscription(qos);
      ACE_TRY_CHECK;
       
      string message = "This is a test";
	  for (int i = 0; i < 10 ; i++ )
	  {
		  int sent = supplier.send(message, ACE_TRY_ENV);
		  ACE_TRY_CHECK;
	  }

	  //handles.run(ACE_TRY_ENV);
	  //ACE_TRY_CHECK;
      supplier.disconnect();
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;  

  return 0;
} /* end of main() */
