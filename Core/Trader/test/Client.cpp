// Client.cpp
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


/** @file Client.cpp
 * @ingroup Trader
 * @brief Contains Code to import offers from the TAO Trading Service.
 */

//local headers.
#include "Client.h"
#include "YP_Offer.h"


static const char* version = "$Id: Client.cpp,v 1.2 2001/11/01 21:32:47 spatil Exp $";


/** @fn extern "C" void sig_handler(int sig)
 * @brief Signal handling function.
 * @param sig The signal received by the signal handler.
 * @return None.
 *
 *  This function prints the received signal and exits the program.
 *
 */
extern "C" void
sig_handler(int sig)
{
  ACE_OS::printf ("Caught Signal %d\n", sig);
  ACE_OS::sleep(2);
  ACE_OS::exit (sig);
}

/**
 * @brief This function handles import operation on TAO Trading  Service.
 * @param argc Number of command line arguments
 * @param argv[] Holds the Command lines arguments in character array.
 * @return Returns an integer.
 *
 *   The main function performs the following operations.
 * 
 * 1:- Creates an instance of CORBA Handles  and initializes it.
 * 2:- Gets the reference to orb from the handles.
 * 3:- Gets reference to trading_service and narrows it to Lookup interface.
 * 4:- Queries the trading service and gets the reference to QMS_Trader_ECInfo .
 * 5:- Executes either the Event channel related methods or get_supplier_id method
 *     depending on the command line option.
 * 6:- Throws exceptions if any of the operation fails.
 */
int
main (int argc, char** argv)
{
  /// Variables for holding the qms unique category and supplier names.
  char *qms_unique_name=0, *supplier_name=0;

 /// Variables for holding the information about Announce, Data and Request
 /// Channel for a given qms unique category name.
  STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq *ImportAECSeq = 0;
  STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq * ImportDECSeq = 0;
  STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq * ImportRECSeq = 0;

  /// Installing the signal handlers.
  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);
  signal(SIGSEGV,sig_handler);

   DEBUG0 (DEBUG_L_CALL, "DEBUG: parsing arguments\n");
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
            cerr << argv[0] << version << endl
           << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
           << endl
           << "\t-h             : This help text"  << endl
           << "\t-v             : Prints out the version"  << endl
           << "\t-q qms_unique_name  : "  << endl
           << "\t OR                   "  << endl
           << "\t-n supplier_name    : "  << endl;
            exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
          cerr << argv[0] << ": Version "<< version << endl;
          exit (0);
      }
     if (strchr((argv[i] + j), 'q'))
      {
          qms_unique_name = (char *) malloc (strlen(argv[i + 1]) + 1);
          strcpy(qms_unique_name,argv[i + 1]);
          continue;
      }
     if (strchr((argv[i] + j), 'n'))
      {
          supplier_name = (char *) malloc (strlen(argv[i + 1]) + 1);
          strcpy(supplier_name,argv[i + 1]);
          continue;
      }

   }


  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
  {
  
      DEBUG0 (DEBUG_L_CALL," Initializing the Corba Handles \n");
      STDC::QMS::CORBA_Handles *handles_p = new STDC::QMS::CORBA_Handles();
      handles_p->init(argc, argv, "Client", ACE_TRY_ENV);
      ACE_TRY_CHECK;


      CosTrading::Lookup_var lookup_v = 
                          handles_p->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CosTrading::Lookup_ptr lookup_p = lookup_v.in();
      ACE_TRY_CHECK;
      assert(lookup_p);
      assert(!CORBA::is_nil(lookup_p));
      DEBUG0 (DEBUG_L_CALL,"Got the ptr to the lookup interface\n");

      // Now doing an import operation
      PolicySeq policies; //empty sequence
      Lookup::SpecifiedProps desired_props;
      desired_props._d(Lookup::all);
      PolicyNameSeq_var policies_applied; // out param
  
      CosTrading::OfferSeq *offer_seq_ptr = 0;
      CosTrading::OfferSeq_out offer_seq_out (offer_seq_ptr);
      OfferIterator_var iterator;     // out param

      //Run the query without preferences using the default policies
      //changed the iterator to offer_iterator_out and how many to zero 
      //instead of 1

      lookup_p->query(YP_SERVICE_TYPE, "QMS_UNIQ_NAME_CATEGORY == 'QMS_TRADER' ", "", policies, desired_props, 1, 
                                  offer_seq_out, iterator, policies_applied);
      ACE_TRY_CHECK;

     //process the results
     STDC::QMS::Citizen::QMS_Trader_ECInfo_var ecinfo_var;
     const CosTrading::OfferSeq& offer_seq = *offer_seq_ptr;

     if ( offer_seq.length() == 0) 

          ACE_DEBUG ((LM_DEBUG, "No matching service offer\n"));
     else 
     {
       // extract the EventChannelInfo reference from the returned offer.
       ecinfo_var = STDC::QMS::Citizen::QMS_Trader_ECInfo::_narrow(offer_seq[0].reference);
       ACE_TRY_CHECK;
       if (CORBA::is_nil(ecinfo_var))
            DEBUG0 (DEBUG_L_CALL,"The reference is not of type QMS_Trader_ECInfo\n"); 
     }

    // Clean up the iterator
    if (!CORBA::is_nil(iterator))
    {
        iterator->destroy();
        ACE_TRY_CHECK;
    }


    if (supplier_name)
    {
      //get the supplier id using the supplier_name
      cerr << "The Supplier id is -> " << ecinfo_var->getSupplierID(supplier_name) 
      << endl;
    }
    else if (qms_unique_name)
    {

      // use the STDC reference now to invoke the getID operation
      ImportAECSeq = ecinfo_var->getAnnounceChannels(qms_unique_name );
      ACE_TRY_CHECK;

      ImportDECSeq = ecinfo_var->getDataChannels(qms_unique_name );
      ACE_TRY_CHECK;

      ImportRECSeq = ecinfo_var->getRequestChannels(qms_unique_name );
      ACE_TRY_CHECK;

      if ( ImportAECSeq != NULL )
      {
        DEBUG0 (DEBUG_L_CALL,"Got some Announce Channels\n");

        DEBUG1(DEBUG_L_ENTER, "Length of ImportAECSeq ->%d\n", 
                                              ImportAECSeq->length() );
        for (CORBA::ULong i =0; i < ImportAECSeq->length() ; i++)

                cerr << (const char *) (*ImportAECSeq)[i].EventChannelName  
                     << "\t\t" 
                     << (*ImportAECSeq)[i].EventId << endl;

      }

      else
      {
        cerr << "UNABLE to get response from Objectfor Announce Channels \n" ;
      }

      if ( ImportDECSeq != NULL )
      {
        DEBUG0 (DEBUG_L_CALL,"Got some Data Channels\n");

        DEBUG1(DEBUG_L_ENTER, "Length of ImportDECSeq->%d\n", 
                                               ImportDECSeq->length() );

        for (CORBA::ULong i =0; i < ImportDECSeq->length() ; i++)

                cerr << (const char *) (*ImportDECSeq)[i].EventChannelName  
                     << "\t\t" 
                     << (*ImportDECSeq)[i].EventId << endl;

      }

      else
      {
          cerr << "UNABLE to get response from Object for Data Channels\n" ;
      }

      if ( ImportRECSeq != NULL )
      {
        DEBUG0 (DEBUG_L_CALL,"Got some Request Channels\n");

        DEBUG1(DEBUG_L_ENTER, "Length of ImportRECSeq->%d\n", 
                                           ImportRECSeq->length() );

        for (CORBA::ULong i =0; i < ImportRECSeq->length() ; i++)

                cerr << (const char *) (*ImportRECSeq)[i].EventChannelName  
                     << "\t\t" 
                     << (*ImportRECSeq)[i].EventId << endl;

      }

      else
      {
        cerr << "UNABLE to get response from Object for Request Channels\n";
      }

    handles_p->~CORBA_Handles();
    ACE_TRY_CHECK;

    } // for qms_unique_name 
    else {
             cerr << "Pl use -h to see the command line options\n ";

         }
  } // end of ACE_TRY

  ACE_CATCH(CORBA::COMM_FAILURE, commEx)
  {
    ACE_PRINT_EXCEPTION (commEx, "A communication failure occured:");
  }

  ACE_CATCH(CORBA::NO_PERMISSION, perEx)
  {
    ACE_PRINT_EXCEPTION (perEx, "A no permission failure occured:");
  }

  ACE_CATCH (CORBA::UserException, ex)
  {
    cerr << " A CORBA user exception was caught: ";
    cerr << "ID = " << ex._id() << endl;
  }
  ACE_CATCH (CORBA::SystemException, sysex)
  {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      cerr << "ID = " << sysex._id() << "; minor code = " << sysex.minor()
       << endl;
        //ACE_RE_THROW;
  }
  ACE_CATCHANY
   {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      //ACE_RE_THROW;
   }
  ACE_CATCHALL
  {
     cerr << " A unknown exception was caught " << endl;
  }
  ACE_ENDTRY;
  
  return 0;

}

