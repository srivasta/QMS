/// Using standard C++ namespace.

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


#include "ace/OS.h"
#include "ace/Thread.h"
#include "ace/Signal.h"
#include "ace/Pipe.h"
#include "ace/Process.h"

#include "EC_Adapter.h"
#include "YP_Offer.h"
#include "TraderC.h"
#include "STDC_i.h"
#include "Debug.h"

#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"


#include <string>
#include <cstring>
#include <csignal>


using namespace CosTradingRepos;
using namespace CosTrading;

using namespace std;

STDC::QMS::EC_Adapter ec_adapter;

STDC_i stdc;

static const char* version = "$Id: QMS_Generic_Sensor.cpp,v 1.7 2001/10/23 06:51:58 spatil Exp $";



/// The Remos query event type
static const RtecEventComm::EventType
QMS_Remos_Query =  ACE_ES_EVENT_UNDEFINED  + 2300;

/// The Remos data event type
static const RtecEventComm::EventType
QMS_Remos_Data =  ACE_ES_EVENT_UNDEFINED  + 2400;

/// The supplier ID of the entity making Remos queries
static const RtecEventComm::EventSourceID
Query_Supplier =  ACE_ES_EVENT_SOURCE_ANY + 2300;

// The supplier ID of the enntity providing the Remos Data
static const RtecEventComm::EventSourceID
    Data_Supplier = ACE_ES_EVENT_SOURCE_ANY + 2400;


void Remos_CallBack(const string &query, void * arg_p = 0);
CORBA::Long get_supplier_id( STDC::QMS::CORBA_Handles *, char *,
                                                 CORBA::Environment &);
void add_Sub_Type_Offer(STDC::QMS::CORBA_Handles *, CORBA::Environment &);



extern "C" void
sig_handler(int sig)
{
  QMS_Trace ("sig_handler", __LINE__, __FILE__);

  ACE_OS::printf ("Caught Signal %d\n", sig);
  ec_adapter.disconnect();
  sleep(2);
  ACE_OS::exit (sig);
}



int
main (int argc, char *argv[])
{
  QMS_Trace ("main", __LINE__, __FILE__);

  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);
  signal(SIGSEGV,sig_handler);


  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");
  DEBUG3(DEBUG_L_CALL, "DEBUG: starting the API With ID = %d "
         " Send event type = %d Recieve event type = %d\n",  Data_Supplier,
         QMS_Remos_Data,  QMS_Remos_Query );

  char * ecname_p = (char *) "QMS_Channel";

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
        cerr << argv[0] << version << endl
             << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
             << endl
             << "\t-h              : This help text"  << endl
             << "\t-v              : Prints out the version"  << endl
             << "\t-ecname    NAME : The name of the event channel"  << endl
             << "\t-e         NAME : The name of the event channel"  << endl
             << "\t-collector NAME : The name of the Collector Host"  << endl
             << "\t-c         NAME : The name of the Collector Host"  << endl
             << "\t-p       NUMBER : The name of the Collector Port"  << endl
             << "\t-port    NUMBER : The name of the Collector Port"  << endl
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        cerr << argv[0] << ": Version " << version << endl;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "ecname") || strchr((argv[i] + j), 'f'))
      {
        ecname_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
        strcpy(ecname_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (DEBUG_L_ERROR, "unknown argument", argv[i]);
   }



  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
     
     CORBA::Long supplierid_num;
 
     STDC::QMS::CORBA_Handles *handles_p = new STDC::QMS::CORBA_Handles();
     handles_p->init(argc, argv, "Generic Sensor", ACE_TRY_ENV);
     ACE_TRY_CHECK;
 
     supplierid_num = get_supplier_id(handles_p, "Generic Sensor", ACE_TRY_ENV);

     ec_adapter.init(argc, argv,
                   //Data_Supplier,   // My ID
                   supplierid_num,  // My ID
                   QMS_Remos_Data,  //  The data I send
                   QMS_Remos_Query, // The data I get
                   ecname_p,
                   handles_p
                   );
      ACE_TRY_CHECK;
      
      ec_adapter.register_callback(Remos_CallBack, 0);
      ACE_TRY_CHECK;
      ec_adapter.connect_supplier();
      ACE_TRY_CHECK;
      ec_adapter.connect_consumer();
      ACE_TRY_CHECK;

      //Adding the YP_SubType using STDC::QMS::Add_YP_SubType method.

      STDC::QMS::Add_YP_SubType(handles_p, "STDC_QMS_CITIZEN_SENSOR",
                        stdc._interface_repository_id (), ACE_TRY_ENV);
      ACE_TRY_CHECK;
      ACE_DEBUG ((LM_DEBUG, "Added the Sensor Service Type "
                  "STDC_QMS_CITIZEN_SENSOR  using STDC::QMS::Add_YP_SubType" ));
  
      // Adding the offer for my subType.    
      add_Sub_Type_Offer(handles_p,ACE_TRY_ENV);
      ACE_TRY_CHECK; 

      ec_adapter.listen();
      ACE_TRY_CHECK; 
    }

  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ec_adapter.connect_supplier();
      ec_adapter.connect_consumer();
      exit (1);
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      ec_adapter.connect_supplier();
      ec_adapter.connect_consumer();
      exit (2);
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ec_adapter.connect_supplier();
      ec_adapter.connect_consumer();
      exit (3);
    }
  ACE_ENDTRY;

}


void
Remos_CallBack(const string &query, void *arg_p)
{
  QMS_Trace ("Remos_CallBack", __LINE__, __FILE__);
  fprintf(stderr,"\n In Remos_CallBack\n");
  fprintf(stderr,"\n Query ->%s\n",query.c_str());

  if (arg_p)
   {
     cerr << "With a non null argument"  << endl;
   }

   string reply;
   reply.assign("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<helloWorld xmlns=\"http://www.stdc.com/2001/QMS/helloWorld\"\n  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n  xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/helloWorld helloWorld.xsd\">\n  <Data>\n    <dataid>1</dataid>\n    <salutation>Hello Shivakumar Patil</salutation>\n  </Data>\n</helloWorld>\n");
   ec_adapter.send(reply);

}


void 
add_Sub_Type_Offer(STDC::QMS::CORBA_Handles *handles_p, 
                                      CORBA::Environment &ACE_TRY_ENV)
{
   ACE_TRY
   {

      // Exporting the offer for my sub type.

      CosTrading::Lookup_var lookup_v =
                           handles_p->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CosTrading::Lookup_ptr lookup_p = lookup_v.in();
      ACE_TRY_CHECK;
      assert(lookup_p);
      assert(!CORBA::is_nil(lookup_p));
      ACE_DEBUG ((LM_ERROR, "Got the ptr to the lookup interface\n"));

      CosTrading::Register_var register_;
      register_ = lookup_p->register_if (ACE_TRY_ENV);
      CosTrading::Register_ptr reg = register_.in();
      ACE_TRY_CHECK;
      cerr << "Got the CosTrading::Register_ptr reg" << endl;

      CosTrading::PropertySeq eprops;
      eprops.length(5);
      CosTrading::OfferId_var offer_id;
      CORBA::Object_ptr offer_obj = stdc._this();
      cerr << "Got the offer_obj " << endl;

      char hostname[MAXNAMELEN], hostip[MAXNAMELEN],pid[MAXNAMELEN];
      if ( gethostname (hostname, MAXNAMELEN) != 0 )
                   perror ("Problem  with getting hostname ");

      struct hostent *hostinfo;
      hostinfo = gethostbyname(hostname);
      char str[INET6_ADDRSTRLEN];
      char **addr_list = (char **)hostinfo->h_addr_list;
      strcpy(hostip, (char *) inet_ntop(hostinfo->h_addrtype, *addr_list, str,
                                                   sizeof(str)));


      eprops[0].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
      eprops[0].value <<= CORBA::string_dup("GENERIC_SENSOR");

      eprops[1].name = CORBA::string_dup("QMS_UNIQ_NAME_HOST_NAME");
      eprops[1].value <<= CORBA::string_dup(hostip);

      sprintf(pid,"%d",ACE_OS::getpid ());
      eprops[2].name = CORBA::string_dup("QMS_UNIQ_NAME_UUID");
      eprops[2].value <<= CORBA::string_dup(pid);

      eprops[3].name = CORBA::string_dup("VERSION");
      eprops[3].value <<= "1.0";

      eprops[4].name = CORBA::string_dup("DESCRIPTION");
      eprops[4].value <<= "Generic Sensor";

       offer_id = reg->_cxx_export(offer_obj,
                      "STDC_QMS_CITIZEN_SENSOR", eprops, ACE_TRY_ENV);
       ACE_TRY_CHECK;
       ACE_DEBUG ((LM_DEBUG, "Registered GS offer id for GS Service Type: %s.\n", offer_id.in ()));

       // end of exporting  offer.
   }
   ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;


}


CORBA::Long
get_supplier_id (STDC::QMS::CORBA_Handles *handles_p, char *desc,
                                       CORBA::Environment &ACE_TRY_ENV)
{
   CORBA::Long num;

   ACE_TRY
   {
      cerr << "The Description is -> " << desc << endl;
      CosTrading::Lookup_var lookup_v =
                          handles_p->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CosTrading::Lookup_ptr lookup_p = lookup_v.in();
      ACE_TRY_CHECK;
      assert(lookup_p);
      assert(!CORBA::is_nil(lookup_p));
      ACE_DEBUG ((LM_ERROR, "Got the ptr to the lookup interface\n"));

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
     STDC::QMS::Citizen::QMS_Trader_var ecinfo_var;
     const CosTrading::OfferSeq& offer_seq = *offer_seq_ptr;

     if ( offer_seq.length() == 0)

          ACE_DEBUG ((LM_DEBUG, "No matching service offer\n"));
     else
     {
       // extract the EventChannelInfo reference from the returned offer.
       ecinfo_var = STDC::QMS::Citizen::QMS_Trader::_narrow(offer_seq[0].reference);
       ACE_TRY_CHECK;
       if (CORBA::is_nil(ecinfo_var))
           ACE_DEBUG ((LM_DEBUG, "The reference is not of type"
                          "QMS_Trader\n"));
     }

    // Clean up the iterator
    if (!CORBA::is_nil(iterator))
    {
        iterator->destroy();
        ACE_TRY_CHECK;
    }

      //get the supplier id using the supplier_name
       num = ecinfo_var->getSupplierID(desc);
       ACE_DEBUG ((LM_DEBUG, "The Supplier id is ->%d\n", num));

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

  return num;

}


#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

//template class vector<STDC::QMS::Push_Consumer *, __default_alloc_template<true, 0> >;
template void fill<STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer * const &);

template STDC::QMS::Push_Consumer ** fill_n<STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer * const &);

//template class vector<STDC::QMS::Push_Supplier *, __default_alloc_template<true, 0> >;
template void fill<STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier *>(STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier * const &);

template STDC::QMS::Push_Supplier ** fill_n<STDC::QMS::Push_Supplier **, unsigned int, STDC::QMS::Push_Supplier *>(STDC::QMS::Push_Supplier **, unsigned int, STDC::QMS::Push_Supplier * const &);

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

