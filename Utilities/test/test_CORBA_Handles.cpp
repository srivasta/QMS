//                              -*- Mode: C++ -*- 
// test_CORBA_Handles.cpp --- 
// Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
// Created On       : Sun Aug 12 00:24:40 2001
// Created On Node  : ember.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Sat Oct 20 02:05:00 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 14
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
static const char* version = "$Id: test_CORBA_Handles.cpp,v 1.3 2001/10/21 08:54:14 srivasta Exp $";

#include "CORBA_Handles.h"
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
     DEBUG1 (DEBUG_L_ARGS, "unknown argument %s", argv[i] );
   }

  STDC::QMS::CORBA_Handles handles;
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      handles.init(argc, argv, "TEST_ORB", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      handles.add_event_channel("QMS_Channel", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      RtecEventChannelAdmin::EventChannel_var event_channel;
      handles.get_event_channel("QMS_Channel", event_channel, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      handles.activate_poa_manager(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      char * str_p = 0;
      
      CORBA::ORB_ptr  orb_p     = handles.get_orb_handle();
      
      PortableServer::POA_ptr 	poa_p     = handles.get_root_poa_handle();
      str_p = orb_p->object_to_string(poa_p);
      cout << str_p << endl;
      CORBA::string_free(str_p);

      PortableServer::POAManager_ptr poa_mgr_p = handles.get_poa_mgr_handle();
      str_p = orb_p->object_to_string(poa_mgr_p);
      cout << str_p << endl;
      CORBA::string_free(str_p);

      CosNaming::NamingContext_ptr  name_p    = handles.get_naming_handle();
      str_p = orb_p->object_to_string(name_p);
      cout << str_p << endl;
      CORBA::string_free(str_p);

      RtecScheduler::Scheduler_ptr sched_p   = handles.get_scheduler_handle();
      str_p = orb_p->object_to_string(sched_p);
      cout << str_p << endl;
      CORBA::string_free(str_p);

      CosTrading::Lookup_ptr lookup_p = handles.get_lookup_handle(ACE_TRY_ENV);
      str_p = orb_p->object_to_string(lookup_p);
      cout << str_p << endl;
      CORBA::string_free(str_p);

      RtecEventChannelAdmin::EventChannel_ptr ec_p = handles.get_ec_handle();
      str_p = orb_p->object_to_string(ec_p);
      cout << str_p << endl;
      CORBA::string_free(str_p);

    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
} /* end of main() */
