// ListOffers.cpp
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

/** @file ListOffers.cpp
 * @ingroup Trader
 * @brief Lists the offers pertaining to a service type.
 */

#include "ListOffers.h"

static const char* version = "$Id: ListOffers.cpp,v 1.14 2001/10/30 17:48:25 spatil Exp $";

/**
 *  @param sig The signal being handled
 *  @brief The Default signal handler
 *
 * Ensure that we disconnect cleanly from QMS
 */
void
sig_handler (int sig)
{
  QMS_Trace ("sig_handler", __LINE__, __FILE__);
  DEBUG1 (DEBUG_L_ENTER, "caught signal %d\n", sig);
  ACE_OS::printf ("Caught Signal %d\n", sig);
  exit (sig);
}


/**
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 * Usage:   [CORBA OPTIONS] [OPTIONS]
 *     -  -h             : This help text
 *     -  -v             : Prints out the version
 *     -  -t <service_type> : Prints the offers related to a servicetype.     
 */
int
main (int argc, char *argv[])
{
  QMS_Trace ("main", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: starting\n");
  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);
  signal(SIGSEGV,sig_handler);

   char *service_type_p = 0;
   char *qun_category_p = 0;
   bool list_all = false;

  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");

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
             << "\t-h                  : This help text"  << endl
             << "\t-v                  : Prints out the version"  << endl
             << "\t-t  <Service Type>  : Name of the Service Type"  << endl
             << "\t OR " << endl
             << "\t-l                  : Lists all the Service Types in the TAO Trader " 
             << "\t OR " << endl
             << "\t -q <QMS_UNIQ_NAME_CATEGORY> : QMS UNIQUE CATEGORY NAME " 
             << endl;
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        cout << argv[0] << ": Version "<< version << endl;
        exit (0);
      }

     if (strchr((argv[i] + j), 't'))
      {
        service_type_p = (char *) malloc (strlen(argv[i + 1]) + 1);
        strcpy(service_type_p,argv[i + 1]);
        continue;
      }
     if (strchr((argv[i] + j), 'q'))
      {
        qun_category_p = (char *) malloc (strlen(argv[i + 1]) + 1);
        strcpy(qun_category_p,argv[i + 1]);
        continue;
      }
      if (strchr((argv[i] + j), 'l'))
      {
        list_all = true;
        continue;
      }

     DEBUG1 (DEBUG_L_ENTER, "unknown argument %s", argv[i] );
   }

   

   ACE_DECLARE_NEW_CORBA_ENV;
   ACE_TRY
    {

       DEBUG0 (DEBUG_L_CALL," Initializing the Corba Handles \n");
       STDC::QMS::CORBA_Handles handles;
       handles.init(argc, argv, "ListOffers", ACE_TRY_ENV);
       ACE_TRY_CHECK;

       DEBUG0 (4, "Getting the lookup interface\n");
       CosTrading::Lookup_var lookup_v =
                          handles.get_lookup_handle(ACE_TRY_ENV);
       ACE_TRY_CHECK;
       CosTrading::Lookup_ptr lookup_p = lookup_v.in();
       ACE_TRY_CHECK;
       assert(lookup_p);
       assert(!CORBA::is_nil(lookup_p));
       DEBUG0(DEBUG_L_ENTER, "Got the ptr to the lookup interface\n");

       if (list_all)
         {
             list_all_types(lookup_p, ACE_TRY_ENV);
             ACE_TRY_CHECK;
         }

       else
        {
            if ( argc == 1 )
            { 
               service_type_p = (char *) malloc (strlen (YP_SERVICE_TYPE) + 1);
               strcpy ( service_type_p, YP_SERVICE_TYPE);
            }
            
            print_offers(lookup_p, service_type_p, qun_category_p, ACE_TRY_ENV);
            ACE_TRY_CHECK;
        }

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

  exit (0);
}

     
void
list_all_types (CosTrading::Lookup_ptr lookup_if, CORBA::Environment& ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_TRY
    {
  
      DEBUG0(DEBUG_L_ENTER, "In list_all_types (....) Function\n");
      // Obtain the Service Type Repository.
      CORBA::Object_var obj = lookup_if->type_repos (ACE_TRY_ENV);
      ACE_TRY_CHECK;;

      // Narrow the Service Type Repository.
      CosTradingRepos::ServiceTypeRepository_var repos_ = 
               CosTradingRepos::ServiceTypeRepository::_narrow (obj.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;
 
      CosTradingRepos::ServiceTypeRepository::SpecifiedServiceTypes sst;
      ACE_DEBUG ((LM_DEBUG, "Listing All Service Types in the TAO Trader.\n"));
      ACE_DEBUG ((LM_DEBUG, "======================================="
                                          "=============\n"));

      sst.all_ (1);
      CosTradingRepos::ServiceTypeRepository::ServiceTypeNameSeq_var type_names =
        repos_->list_types (sst, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::ULong l = type_names->length ();
      for (CORBA::ULong i = 0; i != l; ++i)
        {
          CORBA::ULong index = l - 1 - i;
              ACE_DEBUG ((LM_DEBUG, "%d  : %s\n",i,
                          ACE_static_cast (const char *,
                                           type_names[index])));
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "list_all_types");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
  
}
 
  
/**
 *  @brief  Prints offers related to a service type.
 *  @param  handles handles Reference to CORBA Handles.
 *  @param  type_name Name of the Service Type.
 *  @param  qun_category
 *  @param  ACE_TRY_ENV CORBA_Environment env variable.
 *  @return None.
 *
 *  This method makes a query on the TAO Trading Service for a service type and prints 
 *  those offers in a proper format.
 */
void 
print_offers (CosTrading::Lookup_ptr lookup_if, char * type_name, 
                                                char * category_p,
                                                CORBA_Environment &ACE_TRY_ENV)
{

   ACE_TRY
   {
      DEBUG0(DEBUG_L_ENTER, "In print_offers(....) Function\n");

      // Now doing an import operation
      PolicySeq policies; //empty sequence
      Lookup::SpecifiedProps desired_props;
      desired_props._d(Lookup::all);

      CosTrading::OfferSeq *offer_seq_ptr = 0;
      CosTrading::OfferIterator_ptr offer_iterator_ptr = 0;
      CosTrading::PolicyNameSeq *limits_applied_ptr = 0;

      CosTrading::OfferSeq_out offer_seq_out (offer_seq_ptr);
      CosTrading::OfferIterator_out offer_iterator_out (offer_iterator_ptr);
      CosTrading::PolicyNameSeq_out limits_applied_out (limits_applied_ptr);
 
      if ( type_name )
      {
   
       // Make sure that all the parameters are proper.
       lookup_if->query ( type_name,
                        "TRUE",
                        "",
                        policies,
                        desired_props,
                        0,
                        offer_seq_out,
                        offer_iterator_out,
                        limits_applied_out,
                        ACE_TRY_ENV);
      ACE_TRY_CHECK;

      }
  
      else  if ( category_p )
      {
        string category (category_p);
        string constraint ("QMS_UNIQ_NAME_CATEGORY");
        constraint += " == \'";
        constraint.append(category);
        constraint += "\' ";
 
        lookup_if->query (YP_SERVICE_TYPE,
                          constraint.c_str(),
                          "",
                          policies,
                          desired_props,
                          0,
                          offer_seq_out,
                          offer_iterator_out,
                          limits_applied_out,
                          ACE_TRY_ENV);
      ACE_TRY_CHECK;
      
      }
      else
           exit(0);

      CosTrading::OfferIterator_ptr offer_iterator = offer_iterator_ptr;
   
      if (!CORBA::is_nil(offer_iterator))
      {
         DEBUG0(DEBUG_L_ENTER, "DEBUG: offer_iterator is not null\n");
         CORBA::Boolean more = 0;
         
         do
         {
            DEBUG0(DEBUG_L_ENTER, "DEBUG: Inside the do while loop\n");
            CosTrading::OfferSeq *iter_offers_ptr;
            CosTrading::OfferSeq_out iter_offers_out (iter_offers_ptr);

            more = offer_iterator->next_n(1, iter_offers_out,ACE_TRY_ENV);
            ACE_TRY_CHECK;

            CosTrading::OfferSeq_var iter_offers (iter_offers_ptr);
            CORBA::Any* value = 0;
            DEBUG1(DEBUG_L_ENTER, "DEBUG: iter_offers->length()->%d\n",
                                                    iter_offers->length());
            cerr << "===================================================" << endl;

            for (CORBA::ULong i = 0; i < iter_offers->length(); i++)
            {
              DEBUG0(DEBUG_L_ENTER, "DEBUG: Inside the for loop\n");
              TAO_Property_Evaluator prop_eval (iter_offers[i].properties);

              for (int length = (iter_offers[i].properties).length(), 
                       k=0; k < length ; k++ )
              {
                  value = prop_eval.property_value(k, ACE_TRY_ENV);  
                  ACE_TRY_CHECK;

                  const char *    string_val;
                  CORBA::ULong       long_val;
               
                  if ((*value) >>= long_val)
                  {
                     cout << setw (30) << setiosflags ( ios::left ) 
                                       << iter_offers[i].properties[k].name.in() 
                          << setw (20) << setiosflags ( ios::left ) 
                                       << long_val << endl;
                  }
                  else if ((*value) >>= string_val)
                  {
                    cout << setw (30) << setiosflags ( ios::left )
                                      << iter_offers[i].properties[k].name.in() 
                         << setw (20) << setiosflags ( ios::left )
                                      << string_val << endl;
                  }

              } // end of second for loop.
                  
            } // end of first for loop.
                
         } while (more);

         DEBUG0(DEBUG_L_ENTER, "DEBUG: Destroying the iterator\n");
         offer_iterator->destroy();
         ACE_TRY_CHECK;
 
      } // end of if ..
      else 
           cerr << "No Offers available" << endl;

   }

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

}
