// Simple_Logger.cpp
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

/** @file Simple_Logger.cpp
 *  @ingroup Logger
 *  @brief A Simple Logger that logs information on all the Event Channels.
 *
 */


/// RCS version string
static const char* version = "$Id: Simple_Logger.cpp,v 1.20 2001/12/10 06:52:31 spatil Exp $";

#include "Simple_Logger.h"


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
  DEBUG1 (2,"caught signal %d\n", sig);

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
  {
      DEBUG0 (4,"Disconnecting the Consumers \n");
      disconnect_consumers (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      DEBUG0 (4, "Cleaning the Consumers \n ");
      clean_consumers();
      
      DEBUG0 (4, "Cleaning the consumer info list \n");
      clean_consumer_info_list();

      for ( unsigned int i = 0 ; i < Query_List.size() ; i++ )
                 if ( Query_List[i] )
                     delete Query_List[i];
  }
  ACE_CATCHANY
  {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Signal Handling");
      ACE_RE_THROW;
  }
  ACE_ENDTRY;
  exit(sig);
}



void
my_callback(const string &data, void *arg_p)
{
  DEBUG0 (4,"In call back\n");
  if(arg_p)
   {
     DEBUG0 (4,"We have an argument\n");
     STDC::QMS::Citizen::Consumer_Info *info_p =
                          (STDC::QMS::Citizen::Consumer_Info *)arg_p;
     FILE *handle2File = (FILE *) info_p->file_handle_p;
     ACE_Read_Guard<ACE_Thread_Mutex>  guard(info_p->asset_guard);
     {
       cerr << ".";
       fprintf(handle2File, "%s\t%d\n", info_p->ec_name.c_str(),
                                                              info_p->event_id);
       fprintf(handle2File, "%s\n", data.c_str());
     }

   } /* end of if(arg_p) */

  else
  cerr << data <<endl;

}



int
main(int argc, char *argv[])
{
  QMS_Trace ("main", __LINE__, __FILE__);
  DEBUG0 (4,"DEBUG: starting\n");
  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);
  signal(SIGSEGV,sig_handler);

  DEBUG0 (4," added signal handling\n");
  ACE_OS::srand(time(0));

  STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq *ImportAECSeq = 0;
  STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq * ImportDECSeq = 0;
  STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq * ImportRECSeq = 0;

  char * filename_p = 0;
  char *qms_unique_names=0;

  DEBUG0 (4," parsing arguments\n");
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
     << "\t-q <CATEGORY>,<SUPPLIER_ID>,<EC_NAME>  : Name of the " << endl 
     << "QMS UNIQUE NAME CATEGORY, Supplier Id, Event Channel Name" << endl ;
     exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        cerr << argv[0] << ": Version "<< version << endl;
        exit (0);
      }

     if (! strcmp((argv[i] + j), "file") || strchr((argv[i] + j), 'f'))
      {
          filename_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
          strcpy(filename_p,argv[i + 1]);
          continue;
      }
     if (strchr((argv[i] + j), 'q'))
      {
          qms_unique_names = (char *) malloc (strlen(argv[i + 1]) + 1);
          strcpy(qms_unique_names,argv[i + 1]);
          string temp(qms_unique_names);
          query_strings.push_back(temp);
          continue;
      }
     DEBUG1 (2, "unknown argument %s", argv[i] );
   }

   DEBUG0 (4, "Parsing the Command Line arguments \n");
   fill_query_struct (query_strings , Query_List);
   for ( unsigned int j = 0 ; j < Query_List.size() ; j++ )
     {
            cerr << " ===== displaying the data members ======= " << endl;
            cerr <<  j << "\tname -> "    << Query_List[j]->qun_category
                       << "\t id-> "      << Query_List[j]->supplier_id
                       << "\t ec_name-> " << Query_List[j]->ec_name << endl;
     }


   ACE_DECLARE_NEW_CORBA_ENV;
   ACE_TRY
   {
      STDC::QMS::CORBA_Handles handles;
      DEBUG0 (4, "Initializing the CORBA Handles \n");
      handles.init(argc, argv, "logger", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CosTrading::Lookup_ptr lookup_p = 
                       handles.get_lookup_handle(ACE_TRY_ENV).in();
      ACE_TRY_CHECK;
      assert(lookup_p);
      assert(!CORBA::is_nil(lookup_p));
      DEBUG0 (4,"Got the ptr to the lookup interface\n");

      STDC::QMS::Citizen::QMS_Trader_ECInfo_var ecinfo_var;
      DEBUG0 (4,"Getting the reference to QMS_Trader_ECInfo\n");
      get_qms_trader_ref ( lookup_p , ecinfo_var, ACE_TRY_ENV );
      ACE_TRY_CHECK;

      string filename;
      FILE *file_ptr;
      for ( unsigned int i = 0 ; i < Query_List.size() ; i++ )
      {
        filename.erase();
        filename.assign(Query_List[i]->qun_category);
        filename.append(".log");
        cerr << Query_List[i]->qun_category  << " log file is-> " 
             << filename.c_str() << endl;
   
        if ( ( file_ptr = fopen(filename.c_str(), "a")) == NULL )
             cerr << "Could not open the file " << filename.c_str() << endl;
         
        if ( ! Query_List[i]->supplier_id.empty() ) 
        {
           DEBUG0 (4,"Querying the Trading Service for Offers\n");
	   get_offers(lookup_p, Query_List[i], ACE_TRY_ENV);
	   ACE_TRY_CHECK;
           
	   list<string>::const_iterator iter;
           string data, name;
           int event_id;

           DEBUG0 (4, "Creating the consumers using EC_Info string list\n");
           for (iter = EC_Info.begin(); iter != EC_Info.end() ; iter++ )
           {
              data.assign(*iter);
              get_name_id (data, event_id, name );

                 // skip only when event channel name passed on the command line is 
                 // non-empty and the string compare does not match with event channel
                 // that we got from the offers.

                 if ( ! ( Query_List[i]->ec_name.empty() || 
         	           ( name.compare(Query_List[i]->ec_name) ==  0 ) ) )
                 continue;

                 STDC::QMS::Push_Consumer *consumer_p = 
		                  new STDC::QMS::Push_Consumer;
                 ACE_TRY_CHECK;

                 STDC::QMS::Citizen::Consumer_Info *consumer_info_p =
                                    new STDC::QMS::Citizen::Consumer_Info;

                 consumer_info_p->file_handle_p = file_ptr ;
                 consumer_info_p->ec_name.assign(name);
                 consumer_info_p->event_id = event_id;
                 consumer_p->init(handles, event_id, name.c_str(), 
		                                         ACE_TRY_ENV);
		 ACE_TRY_CHECK;
		 consumer_p->register_callback(&my_callback,
		                                  (void *)consumer_info_p);
		 ACE_TRY_CHECK;
		 consumer_p->connect(ACE_TRY_ENV);
		 ACE_TRY_CHECK;

		 consumer_list.push_back(consumer_p);
		 consumer_info_list.push_back(consumer_info_p);

	  }
		 
        }
        else 
        {
            DEBUG0 (4,"Querying the QMS_Trader_ECInfo for the Offers\n");
            ImportAECSeq = ecinfo_var->getAnnounceChannels(
                                             Query_List[i]->qun_category.c_str());
            ACE_TRY_CHECK;
            if ( ImportAECSeq != NULL )
            {
               DEBUG0 (4,"Got some Announce Channels\n");
               DEBUG1 (2, "Length of ImportAECSeq->%d\n",
                                                    ImportAECSeq->length() );
               for (CORBA::ULong i =0; i < ImportAECSeq->length() ; i++)

                     cerr << (*ImportAECSeq)[i].EventChannelName << "\t"
                          << (*ImportAECSeq)[i].EventId << endl;
            }
            else
            {
              cerr << "UNABLE to get response from Object for Announce Channels\n";
            }

            ImportDECSeq = ecinfo_var->getDataChannels(
                                            Query_List[i]->qun_category.c_str());
            ACE_TRY_CHECK;
            if ( ImportDECSeq != NULL )
            {
               DEBUG0 (4,"Got some Data Channels\n");
               DEBUG1 (2, "Length of ImportDECSeq->%d\n",
                                                     ImportDECSeq->length() );
              for (CORBA::ULong i =0; i < ImportDECSeq->length() ; i++)

                     cerr << (*ImportDECSeq)[i].EventChannelName << "\t"                                    << (*ImportDECSeq)[i].EventId << endl;
            }
           else
           {
                cerr << "UNABLE to get response from Object for Data Channels\n";
           }

            ImportRECSeq = ecinfo_var->getRequestChannels(
                                            Query_List[i]->qun_category.c_str());
            ACE_TRY_CHECK;
            if ( ImportRECSeq != NULL )
            {
               DEBUG0 (4,"Got some Request Channels\n");
               DEBUG1 (2, "Length of ImportRECSeq ->%d\n",
                                               ImportRECSeq->length() );

               for (CORBA::ULong i =0; i < ImportRECSeq->length() ; i++)

                      cerr << (*ImportRECSeq)[i].EventChannelName << "\t"
                           << (*ImportRECSeq)[i].EventId << endl;
            }
            else
            {
             cerr << "UNABLE to get response from Object for Request Channels\n";

            }

            DEBUG0 (4, "Creating Consumers for the Announce Channels \n");
            CORBA::ULong n;
            for ( n=0; n < ImportAECSeq->length() ; n++ )
            {

                // skip only when event channel name passed on the command line is 
                // non-empty and the string compare does not match with event channel
                // that we got from the offers.

                if ( ! ( Query_List[i]->ec_name.empty() ||
                      ( ACE_OS::strcmp ( Query_List[i]->ec_name.c_str(),
                      ((*ImportAECSeq)[n].EventChannelName) ) == 0 ) ) )

                continue;

                STDC::QMS::Push_Consumer *consumer_p = new STDC::QMS::Push_Consumer;
                ACE_TRY_CHECK;

                STDC::QMS::Citizen::Consumer_Info *consumer_info_p =
                                              new STDC::QMS::Citizen::Consumer_Info;

                consumer_info_p->file_handle_p = file_ptr ;
                consumer_info_p->ec_name.assign((*ImportAECSeq)[n].EventChannelName);
                consumer_info_p->event_id = (*ImportAECSeq)[n].EventId ;

                consumer_p->init(handles, (*ImportAECSeq)[n].EventId,
                                             (*ImportAECSeq)[n].EventChannelName,
                                                                       ACE_TRY_ENV);
                ACE_TRY_CHECK;
                consumer_p->register_callback(&my_callback,
                                                           (void *)consumer_info_p);
                ACE_TRY_CHECK;

                consumer_p->connect(ACE_TRY_ENV);
                ACE_TRY_CHECK;

                consumer_list.push_back(consumer_p);
                consumer_info_list.push_back(consumer_info_p);

            }

            DEBUG0 (4, "Creating Consumers for the Data Channels \n");
            for ( n=0; n < ImportDECSeq->length() ; n++ )
            {

                // skip only when event channel name passed on the command line is 
                // non-empty and the string compare does not match with event channel
                // that we got from the offers.

                if ( ! ( Query_List[i]->ec_name.empty() ||
                      ( ACE_OS::strcmp ( Query_List[i]->ec_name.c_str(),
                      ((*ImportDECSeq)[n].EventChannelName) ) == 0 ) ) )

                continue;

                STDC::QMS::Push_Consumer *consumer_p = new STDC::QMS::Push_Consumer;
                ACE_TRY_CHECK;

                STDC::QMS::Citizen::Consumer_Info *consumer_info_p =
                                              new STDC::QMS::Citizen::Consumer_Info;

                consumer_info_p->file_handle_p = file_ptr ;
                consumer_info_p->ec_name.assign((*ImportDECSeq)[n].EventChannelName);
                consumer_info_p->event_id = (*ImportDECSeq)[n].EventId ;

                consumer_p->init(handles, (*ImportDECSeq)[n].EventId,
                                             (*ImportDECSeq)[n].EventChannelName,
                                                                       ACE_TRY_ENV);
                ACE_TRY_CHECK;
                consumer_p->register_callback(&my_callback,
                                                           (void *)consumer_info_p);
                ACE_TRY_CHECK;

                consumer_p->connect(ACE_TRY_ENV);
                ACE_TRY_CHECK;

                consumer_list.push_back(consumer_p);
                consumer_info_list.push_back(consumer_info_p);

            }

            DEBUG0 (4, "Creating Consumers for the Request Channels \n");
            for ( n=0; n < ImportRECSeq->length() ; n++ )
            {

                // skip only when event channel name passed on the command line is 
                // non-empty and the string compare does not match with event channel
                // that we got from the offers.

                if ( ! ( Query_List[i]->ec_name.empty() ||
                      ( ACE_OS::strcmp ( Query_List[i]->ec_name.c_str(),
                      ((*ImportRECSeq)[n].EventChannelName) ) == 0 ) ) )

                continue;

                STDC::QMS::Push_Consumer *consumer_p = new STDC::QMS::Push_Consumer;
                ACE_TRY_CHECK;

                STDC::QMS::Citizen::Consumer_Info *consumer_info_p =
                                              new STDC::QMS::Citizen::Consumer_Info;

                consumer_info_p->file_handle_p = file_ptr ;
                consumer_info_p->ec_name.assign((*ImportRECSeq)[n].EventChannelName);
                consumer_info_p->event_id = (*ImportRECSeq)[n].EventId ;

                consumer_p->init(handles, (*ImportRECSeq)[n].EventId,
                                             (*ImportRECSeq)[n].EventChannelName,
                                                                       ACE_TRY_ENV);
                ACE_TRY_CHECK;
                consumer_p->register_callback(&my_callback,
                                                           (void *)consumer_info_p);
                ACE_TRY_CHECK;

                consumer_p->connect(ACE_TRY_ENV);
                ACE_TRY_CHECK;

                consumer_list.push_back(consumer_p);
                consumer_info_list.push_back(consumer_info_p);

            }

        } // end of else.
      
      } // end of for loop.

      DEBUG0 (4, " ACtivating the POA Manager \n");
      handles.activate_poa_manager(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      DEBUG0 (4, "Entering the orb run loop\n ");
      handles.run(ACE_TRY_ENV);
      ACE_TRY_CHECK;

    } // end of ACE_TRY
    ACE_CATCHANY
    {
        ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
    }
    ACE_ENDTRY;

   return 0;

} // end of main() 



/**
 *  @brief  Gets the offers corresponding to qms unique name category and supplier id.
 *  @param  lookup_if Pointer to the lookup interface.
 *  @param  query_info Pointer to a user query.
 *  @param  ACE_TRY_ENV CORBA Environment variable.
 *  @return NONE.
 *
 *               This functions queries the Trading Service to get the offers 
 *  corresponding to a qms unique name category and a supplier id. iterate_thru_offers
 *  function is called to iterate through the offer list gotten by this function.
 *
 */
void get_offers( CosTrading::Lookup_ptr lookup_if,
                       STDC::QMS::Citizen::Query *query_info,
		       CORBA::Environment& ACE_TRY_ENV)
{
   ACE_TRY
   {
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
     
      string constraint ("QMS_UNIQ_NAME_CATEGORY");
      constraint += " == \'";
      constraint.append(query_info->qun_category);
      constraint += "\' and SUPPLIER_ID == ";
      constraint.append(query_info->supplier_id);

      DEBUG1 (2, "The Query String is -> %s\n", constraint.c_str());
      lookup_if->query(YP_SERVICE_TYPE,
                       constraint.c_str(),
        	       "min SUPPLIER_ID",
		       policies,
		       desired_props,
		       0,
		       offer_seq_out,
		       offer_iterator_out,
		       limits_applied_out,
		       ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CosTrading::OfferIterator_var offer_iterator (offer_iterator_ptr);

      iterate_thru_offers(offer_iterator_ptr, ACE_TRY_ENV);
      ACE_TRY_CHECK;
   }
   ACE_CATCHANY
   {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
                             "get_offers");
      ACE_RE_THROW;
   }
   ACE_ENDTRY;

}



/**
 *  @brief  Iterates through offer list.
 *  @param  offer_iterator Ponter to the offer list.
 *  @param  ACE_TRY_ENV CORBA Environment variable.
 *  @return NONE.
 *
 *             This functions iterates through the offer list, examining each offer 
 *  to get the event channel name and event id associated with Announce , Request and 
 *  Data channels for the given combination of qms unique name category and 
 *  supplier id. Stores this information in the EC_Info data structure.
 *
 */
void
iterate_thru_offers(CosTrading::OfferIterator_ptr offer_iterator,
                    CORBA::Environment& ACE_TRY_ENV)
		    
	ACE_THROW_SPEC ((CORBA::SystemException))
{
   DEBUG0(4, "In function iterate_thru_offers \n");
   ACE_TRY
   {
      if (!CORBA::is_nil(offer_iterator))
      {
         DEBUG0(4, "DEBUG: offer_iterator is not null\n");
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
            const char * value_p;
            string data;

	    DEBUG1(2, "DEBUG: iter_offers->length()->%d\n", iter_offers->length());
	    for (CORBA::ULong i = 0; i < iter_offers->length(); i++)
	    {
	       DEBUG0(DEBUG_L_ENTER, "DEBUG: Inside the for loop\n");
	       TAO_Property_Evaluator_By_Name prop_val(iter_offers[i].properties,
                                                        ACE_TRY_ENV);

               value =  prop_val.property_value((const char *)"Announce_0",
                                                          ACE_TRY_ENV);
               (*value) >>= value_p;
               data = value_p ;
               EC_Info.push_back(data);               
               DEBUG1(2, "DEBUG: %s\n", data.c_str());

               value =  prop_val.property_value((const char *)"Request_0",
                                        ACE_TRY_ENV);
               (*value) >>= value_p;
               data = value_p;
               EC_Info.push_back(data);
               DEBUG1(2, "DEBUG: %s\n", data.c_str());

               
               value =  prop_val.property_value((const char *)"Data_0",
                                        ACE_TRY_ENV);
               (*value) >>= value_p;
               data = value_p;
               EC_Info.push_back(data);
               DEBUG1(2, "DEBUG: %s\n", data.c_str());
               
	    } // end of first for
	    
	 } while (more);
	 
	 DEBUG0(2, "DEBUG: Destroying the iterator\n");
	 offer_iterator->destroy();
	 ACE_TRY_CHECK;

      } // end of if
      else 
            DEBUG0 (4, "offer iterator is NULL \n");

   } //end of ACE_TRY.
   
   ACE_CATCHANY
   {
     ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "iterate_thru_offers");
     ACE_RE_THROW;
   }
   ACE_ENDTRY;
   
}




/**
 *  @brief  This method returns event id and name by taking a string.
 *  @param  data The string that contains event name and id information.
 *  @param  id Holds event id .
 *  @param  name Holds the event channel name.
 *  @return NONE.
 *
 *
 */
void
get_name_id ( string &data, CORBA::Long  &id, string &name)
{
    DEBUG0(4, "In get_name_id (....) Function\n");
    size_t location = 0;
    size_t start = 0;
    size_t stop = 0;

    location = data.find("<Event_Channel_Name>", location);
    if (location == string::npos)
    {
       cerr << "End of string encountered.\n";
    }
    location += strlen("<Event_Channel_Name>");
    start = location;

    location = data.find("</Event_Channel_Name>", location);
    if (location == string::npos)
    {
       cerr << "End of string encountered.\n";
    }
    stop = location;
      
    name.assign( (data.substr(start, stop - start)).data() );
    location += strlen("</Event_Channel_Name>");
    location = data.find("<Event_Type>", location);
  
    if (location != string::npos)
    {
        location += strlen("<Event_Type>");
        start = location;
        location = data.find("</Event_Type>", location);
        if (location == string::npos)
         {
               cerr << "End of string encountered.\n";
         }
         stop = location;
         string x;
         x.assign( (data.substr(start, stop - start)).data() );
         id = CORBA::Long ( atol(x.c_str()) ) ;
    }

    DEBUG2(2, "Channel Name->%s\t Event Id->%d\n", name.c_str(),id);
      
}


/*
 *  @brief  Gets the reference to QMS_Trader_ECInfo.
 *  @param  lookup_if Pointer to the lookup interface.
 *  @param  qt_var Reference to the QMS_Trader_ECInfo var.
 *  @param  ACE_TRY_ENV CORBA Environment variable.
 *  @return NONE.
 *
 *               This functions gets a reference to the QMS_Trader_ECInfo, so that 
 *  this reference can be used any number of times.  This reference is used to query 
 *  QMS_Trader_ECInfo for a given qms unique name category passed on the command line 
 *  for which no supplier id is available.
 */
void
get_qms_trader_ref ( CosTrading::Lookup_ptr lookup_if, 
                     STDC::QMS::Citizen::QMS_Trader_ECInfo_var  & qt_var,
                     CORBA::Environment& ACE_TRY_ENV)
{
    DEBUG0(4, "In get_qms_trader_ref (....) Function\n");
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

    lookup_if->query(YP_SERVICE_TYPE,
                    "QMS_UNIQ_NAME_CATEGORY == 'QMS_TRADER'",
                    "",
                    policies,
                    desired_props,
                    1,
                    offer_seq_out,
                    iterator,
                    policies_applied );
      ACE_TRY_CHECK;

     //process the results
     const CosTrading::OfferSeq& offer_seq = *offer_seq_ptr;
     
     if ( offer_seq.length() == 0)
     DEBUG0 (4,"No matching service offer\n");
     else
     {
       // extract the EventChannelInfo reference from the returned offer.
       qt_var =
         STDC::QMS::Citizen::QMS_Trader_ECInfo::_narrow(offer_seq[0].reference);
       ACE_TRY_CHECK;

       if (CORBA::is_nil(qt_var.in()))
             DEBUG0 (4,"The reference is not of type QMS_Trader_ECInfo\n");
     }

     // Clean up the iterator
     if (!CORBA::is_nil(iterator.in()))
     {
        iterator->destroy();
        ACE_TRY_CHECK;
     }

}



/*
 *  @brief  converts list of strings to structure related to the query.
 *  @param  The required three fields seperated by commas in a string.
 *  @param  quns list of strings containing command line arguments.
 *  @return NONE.
 *
 *             This function converts the command line arguments following the option 
 *  "-q" to data structure STDC::QMS::Citizen::Query . Thus each structure represents 
 *  a user requirement. Information in each struct is used to make decision on 
 *  whether to query the QMS_Trader_ECInfo or Trading Service to get the offers 
 *  corresponding to qms unique name category, supplier id and event channel name.
 */
void
fill_query_struct(list<string> & quns , 
                         vector<STDC::QMS::Citizen::Query *> & query_list )
{

  DEBUG0 (4, "In function fill_query_struct (...) \n");
  string x, y;
  list<string>::const_iterator iter;

     for (iter = quns.begin(); iter != quns.end() ; iter++ )
     {
        y.assign(*iter);
        DEBUG1 (2, "The string content is ->%s\n", y.c_str() );

        if (!y.empty())
        {
           STDC::QMS::Citizen::Query *query_p = new STDC::QMS::Citizen::Query;
           query_p->qun_category.erase();
           query_p->supplier_id.erase();
           query_p->ec_name.erase();
           bool done = false;
           size_t location = 0;
           size_t start = 0;
           int i  = 0;
           size_t stop = x.length();

          while (done == false)
          {
             x.erase();
             location = y.find(",", start);
             if ( location == start )
             {
                if ( i == 0 ) 
                {
                  cerr << "Pl Enter the QMS UNIQUE NAME CATEGORY" << endl;
                  exit(0); 
                }
                  start = location + 1;
             }
             else if  (location == string::npos)
             {
                   if ( y[y.length()-1] == ',' )
                      x.assign(y.substr(start, y.length()-2));
                   else
                      x.assign(y.substr(start));

                   done = true;
             }
             else
             {
                stop = location;
                x.assign(y.substr(start, stop - start));
                start = location +1;
             }

             switch ( i )  
                {

                  case 0:
                         query_p->qun_category.assign(x);
                         break;
                  case 1:
                         query_p->supplier_id.assign(x);
                         break;
                  case 2:
                         query_p->ec_name.assign(x);
                         break;
             
                }
              
             i++;

          } // end of while

          query_list.push_back(query_p);

        } // end of if

    } // end of for

} // end of the function



/**
 * @brief Disconnect the consumers from the event channel
 */
void
disconnect_consumers (CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace(" disconnect_consumers", __LINE__, __FILE__);
  DEBUG0 (4," disconnect_consumers \n");
  if(!consumer_list.empty())
   {
     ACE_TRY
       {
         unsigned int i = 0;
         for(i = 0; i < consumer_list.size(); i++)
          {
            consumer_list[i]->disconnect(ACE_TRY_ENV);
            ACE_TRY_CHECK;
          }
       }
     ACE_CATCHANY
       {
         ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "disconnect_consumers");
         ACE_RE_THROW;
       }
     ACE_ENDTRY;
   } // end of if

}



/**
 * @brief Cleanup the consumers and reclaim resources
 */
void
clean_consumers(void)
{
  QMS_Trace("clean_consumers", __LINE__, __FILE__);
  DEBUG0 (4,"DEBUG: clean_consumers \n");
  if(!consumer_list.empty())
   {
     unsigned int i = 0;
     for(i = 0; i < consumer_list.size(); i++)
      {
        delete consumer_list[i];
      }
     consumer_list.clear();
   }
}




/**
 * @brief Cleanup the consumer_info_list  and reclaim resources.
 */
void
clean_consumer_info_list(void)
{
  QMS_Trace("clean_consumer_info_list", __LINE__, __FILE__);
  DEBUG0 (4,"DEBUG: clean_consumer_info_list\n");
  if(!consumer_info_list.empty())
   {
     unsigned int i = 0;
     for(i = 0; i < consumer_info_list.size(); i++)
      {
        delete consumer_info_list[i];
      }
     consumer_info_list.clear();
   }
}



#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class list<string>;
template class vector<STDC::QMS::Citizen::Query *>;
template class vector<STDC::QMS::Push_Consumer *>;
template class vector<STDC::QMS::Citizen::Consumer_Info *>;

// related to list<string> and vector<STDC::QMS::Citizen::Query *>

template void fill<STDC::QMS::Citizen::Query **, STDC::QMS::Citizen::Query *>(STDC::QMS::Citizen::Query **, STDC::QMS::Citizen::Query **, STDC::QMS::Citizen::Query * const &);

template STDC::QMS::Citizen::Query ** fill_n<STDC::QMS::Citizen::Query **, unsigned int, STDC::QMS::Citizen::Query *>(STDC::QMS::Citizen::Query **, unsigned int, STDC::QMS::Citizen::Query * const &);

#  if defined(__GNUC_MINOR__) && __GNUC_MINOR__ > 92
template _List_base<string, allocator<string> >;
template void list<string, allocator<string > >::_M_insert_dispatch<_List_iterator<string, string const &, string const *> >(_List_iterator<string, string &, string *>, _List_iterator<string, string const &, string const *>, _List_iterator<string, string const &, string const *>, __false_type);
#  else
template void list<string, __default_alloc_template<true, 0> >::insert<__list_iterator<string, string const &, string const *> >(__list_iterator<string, string &, string *>, __list_iterator<string, string const &, string const *>, __list_iterator<string, string const &, string const *>);
#endif


// related to vector<STDC::QMS::Push_Consumer *> and 
// vector<STDC::QMS::Citizen::Consumer_Info *>

template void fill<STDC::QMS::Citizen::Consumer_Info **, STDC::QMS::Citizen::Consumer_Info *>(STDC::QMS::Citizen::Consumer_Info **, STDC::QMS::Citizen::Consumer_Info **, STDC::QMS::Citizen::Consumer_Info * const &);

template STDC::QMS::Citizen::Consumer_Info ** fill_n<STDC::QMS::Citizen::Consumer_Info **, unsigned int, STDC::QMS::Citizen::Consumer_Info *>(STDC::QMS::Citizen::Consumer_Info **, unsigned int, STDC::QMS::Citizen::Consumer_Info * const &);

template void fill<STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer * const &);

template STDC::QMS::Push_Consumer ** fill_n<STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer * const &);

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
