// QMS_Trader_ECInfo.cpp
// Author           : Shivakumar C. Patil (shivakumar.patil@stdc.com)
// Description      :
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


/** @file QMS_Trader_ECInfo.cpp
 * @ingroup Trader
 * @brief Contains Code to add service types to the Trader.
 */

//local headers.
#include "QMS_Trader_ECInfo.h"
#include <cstring>

 /// Creating an instance of the QMS_Trader_ECInfo servant.
 STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl *ecreg = 
                          new STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl();

 /// Creating the CORBA Handles.
 STDC::QMS::CORBA_Handles *handles_p = new STDC::QMS::CORBA_Handles();

/** @fn extern "C" void sig_handler(int sig)
 * @brief Signal handling function.
 * @param sig The signal received by the signal handler.
 * @return None.
 *
 *  This function prints the received signal and exits the program.
 *  
 *  1:- Calls the destructor of the QMS_Trader_ECInfo servant, which deletes 
 *      offers exported by the QMS_Trader_ECInfo servant.
 *
 *  2:- Calls the destructor of the CORBA_Handles.
 *
 */
extern "C" void
sig_handler(int sig)
{
  
  ACE_OS::printf ("Caught Signal %d\n", sig);
  ACE_OS::sleep(2);
  delete ecreg;
  delete handles_p;
  ACE_OS::exit (sig);
}

static const char* version = "$Id: QMS_Trader_ECInfo.cpp,v 1.1 2001/10/24 15:52:40 spatil Exp $";


/** @fn int main (int argc, char *argv[])
 * @brief This function handles export operation on Trader.
 * @param argc Number of command line arguments
 * @param argv[] Holds the Command lines arguments in character array.
 * @return Returns an integer.
 *
 *   The main function performs the following operations.
 * 
 * 1:- Initializes  the CORBA Handles.
 * 2:- Gets the reference to orb from the handles.
 * 3:- Initializes the QMS_Trader_ECInfo servant.
 * 4:- ACtivates the POA Manager using the handles.
 * 6:- Infinitely waits in the loop for requests.
 * 7:- Throws exceptions if any of the operation fails.
 */
int
main (int argc, char *argv[])
{

  char *config_file=0;


  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);
  signal(SIGSEGV,sig_handler);


    for (int i = 0; i < argc; i++)
   {
     if (!argv[i])           { break; }
     if (argv[i][0] != '-')  { continue; }
     int j = 1;
     if (argv[i][1] == '-')  {
       if (argv[i][2] == 0)  { break; }// handle -- end of options
       j = 2;// handle --argument
     }
     if (strstr((argv[i] + j), "ORB"))  { continue; }
     if (! strcmp((argv[i] + j), "help") || strchr((argv[i] + j), 'h'))
      {// -h or --help
          cout << argv[0] << version << endl
         << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
         << endl
         << "\t-h             : This help text"  << endl
         << "\t-v             : Prints out the version"  << endl
         << "\t-f file_name        : config file name to read"  << endl;
          exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
          cout << argv[0] << ": Version "<< version << endl;
          exit (0);
      }
     if (strchr((argv[i] + j), 'f'))
      {
          config_file = (char *) malloc (strlen(argv[i + 1]) + 1);
          strcpy(config_file,argv[i + 1]);
          continue;
      }
   }


  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      // r u deleting this memory.
      handles_p->init(argc, argv, "QMS_Trader_ECInfo", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::ORB_ptr orb_p = handles_p->get_orb_handle();
      ACE_TRY_CHECK;

      // create an instance of QMS_Trader_ECInfo_Impl
      ecreg->init(config_file, handles_p, ACE_TRY_ENV);


      // Ready to receive the requests
      handles_p->activate_poa_manager(ACE_TRY_ENV);
      orb_p->run(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      handles_p->~CORBA_Handles();
      delete ecreg;

    }

  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      exit (1);
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      exit (2);
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      exit (3);
    }
  ACE_ENDTRY;
  ACE_CHECK;
 
  return 0;

}
