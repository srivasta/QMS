
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


#include "ace/OS.h"             // For the LM_DEBUG macros
#include "ace/Log_Msg.h"
#include "ace/Thread.h"
#include "ace/Synch.h"

#include "EC_Adapter.h"
#include "Debug.h"

#include <string>
#include <cstring>
#include <csignal>

/// Where we stash a handle for the QMS API object
STDC::QMS::EC_Adapter ec_adapter;
/// sequence number of the message being sent, initially 0
int count = 0;
/// A mutex to protect the sequence
ACE_Thread_Mutex TD_asset_guard;
/// RCS version string
static const char* version = "$Id: QMS_Test_Client.cpp,v 1.3 2001/10/21 08:54:07 srivasta Exp $";
/// A place to stash the pointer to a file name
char *filename_p = 0;


using namespace std;

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

static const RtecEventComm::EventType QMS_DISCONNECT        = 10000;
static const RtecEventComm::EventType SUPPLIER_DISCONNECT   = 20000;
static const long QMS_DEFAULT_retry_sleep_interval = 60;
static const int  QMS_DEFAULT_number_of_retries     = 3;

CORBA::Long get_supplier_id(int, char **, CORBA_Environment &);

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
  ec_adapter.disconnect();
  exit (sig);
}


/** @fn void mock_message(void)
 *  @brief  Generate a test Remos Query randomly
 *
 * Here we generate a mock query statically, incrementing the request
 * ID every time we are invoked. We instantiate a struct Query_struct,
 * populate it, and use a QMS_Remos_Msg object to facilitate
 * conversion to XML
 */
void
mock_message(void)
{
//******************************
//********************************************

  QMS_Trace ("mock_message", __LINE__, __FILE__);

  char message[BUFSIZ];
  sprintf (message,"<?xml version=\"1.0\" ?>\n<!DOCTYPE QMS_Event PUBLIC \"-//STDC//QMS Event//EN//XML\" \"QMS_Event.dtd\">\n<QMS_Event>\n  <SequenceNo>2</SequenceNo>\n  <SenderID>skywalker.stdc.com</SenderID>\n  <EventDate>9/10/2001</EventDate>\n  <EventTime>15:45:22.214713</EventTime>\n  <EventType>%d</EventType>\n  <EventData>\n\t<bandwidth_request linktype=\"link\">\n\t   <requestid>%s</requestid>\n\t   <hostname>skywalker_t.stdc.com</hostname>\n\t   <hostname>kenobee_t.stdc.com</hostname>\n\t   <hostname>c3po_t.stdc.com</hostname>\n\t   <refreshrate>2.450000</refreshrate>\n\t   <repeatcount>5</repeatcount>\n\t</bandwidth_request>\n  </EventData>\n</QMS_Event>",2416,"start\n"); 
  string data(message);
  ec_adapter.send(data);

  ACE_OS::sleep (ACE_Time_Value (10));
  sprintf (message,"<?xml version=\"1.0\" ?>\n<!DOCTYPE QMS_Event PUBLIC \"-//STDC//QMS Event//EN//XML\" \"QMS_Event.dtd\">\n<QMS_Event>\n  <SequenceNo>2</SequenceNo>\n  <SenderID>skywalker.stdc.com</SenderID>\n  <EventDate>9/10/2001</EventDate>\n  <EventTime>15:45:22.214713</EventTime>\n  <EventType>%d</EventType>\n  <EventData>\n\t<bandwidth_request linktype=\"link\">\n\t   <requestid>%s</requestid>\n\t   <hostname>skywalker_t.stdc.com</hostname>\n\t   <hostname>kenobee_t.stdc.com</hostname>\n\t   <hostname>c3po_t.stdc.com</hostname>\n\t   <refreshrate>2.450000</refreshrate>\n\t   <repeatcount>5</repeatcount>\n\t</bandwidth_request>\n  </EventData>\n</QMS_Event>",2416,"pause\n");

  data.assign(message);
  ec_adapter.send(data);


  ACE_OS::sleep (ACE_Time_Value (10));
  sprintf (message,"<?xml version=\"1.0\" ?>\n<!DOCTYPE QMS_Event PUBLIC \"-//STDC//QMS Event//EN//XML\" \"QMS_Event.dtd\">\n<QMS_Event>\n  <SequenceNo>2</SequenceNo>\n  <SenderID>skywalker.stdc.com</SenderID>\n  <EventDate>9/10/2001</EventDate>\n  <EventTime>15:45:22.214713</EventTime>\n  <EventType>%d</EventType>\n  <EventData>\n\t<bandwidth_request linktype=\"link\">\n\t   <requestid>%s</requestid>\n\t   <hostname>skywalker_t.stdc.com</hostname>\n\t   <hostname>kenobee_t.stdc.com</hostname>\n\t   <hostname>c3po_t.stdc.com</hostname>\n\t   <refreshrate>2.450000</refreshrate>\n\t   <repeatcount>5</repeatcount>\n\t</bandwidth_request>\n  </EventData>\n</QMS_Event>",2416,"resume\n");

  data.assign(message);
  ec_adapter.send(data);

  ACE_OS::sleep (ACE_Time_Value (10));
  sprintf (message,"<?xml version=\"1.0\" ?>\n<!DOCTYPE QMS_Event PUBLIC \"-//STDC//QMS Event//EN//XML\" \"QMS_Event.dtd\">\n<QMS_Event>\n  <SequenceNo>2</SequenceNo>\n  <SenderID>skywalker.stdc.com</SenderID>\n  <EventDate>9/10/2001</EventDate>\n  <EventTime>15:45:22.214713</EventTime>\n  <EventType>%d</EventType>\n  <EventData>\n\t<bandwidth_request linktype=\"link\">\n\t   <requestid>%s</requestid>\n\t   <hostname>skywalker_t.stdc.com</hostname>\n\t   <hostname>kenobee_t.stdc.com</hostname>\n\t   <hostname>c3po_t.stdc.com</hostname>\n\t   <refreshrate>2.450000</refreshrate>\n\t   <repeatcount>5</repeatcount>\n\t</bandwidth_request>\n  </EventData>\n</QMS_Event>",2416,"stop\n");


  data.assign(message);
  ec_adapter.send(data);

  DEBUG0 (DEBUG_L_LEAVE, "DEBUG Sending all done\n");
}

/// The maximum number of characters in a path element
#ifndef PATH_MAX
# define PATH_MAX 4095
#endif

/**
 *  @param file_p Name of the file to read the message from
 *  @brief  Generate a test Remos Query from a file
 *
 * Instead of generating a mock query by populating a struct on the
 * fly, we read the query directly from a file. It is assumed that the
 * file is in a format that is being expected by the remote end.
 */
void
file_message(char * file_p)
{
  QMS_Trace ("file_message", __LINE__, __FILE__);
  // We need to read this file
  // We assume that the file has a genuine XML message, since until we
  // have a validating parser, little can be done about error checking
  DEBUG0 (DEBUG_L_ENTER, "DEBUG opening file\n");
  FILE *input_file_p = fopen(file_p, "r");
  if (!input_file_p)
   {
     DEBUG1 (DEBUG_L_ENTER, "Error reading file %s \n", file_p);
     perror("fopen error");
     exit (errno);
   }
  char buffer[PATH_MAX];
  string file;
  DEBUG0 (DEBUG_L_CALL, "DEBUG reading file\n");
  while (fgets (buffer, PATH_MAX, input_file_p))
  {
    file.append(buffer);
  }
  DEBUG0 (DEBUG_L_CALL, "DEBUG sending file\n");
  ec_adapter.send(file);

#if 0
  string query;

  //QMS_Remos_Msg message;
  // OK. Now for parsing the message

  size_t location = 0;
  size_t start = 0;
  size_t stop = 0;
#endif
  DEBUG0 (DEBUG_L_LEAVE, "DEBUG Sending all done\n");
}



/**
 *  This is where we send all the test messages. Depending o the
 *  argument, either we read a static XML evnt from a file (and thus
 *  there is no XML conversion overhead incurred), or we instantiate
 *  and populate a struct Query_struct for every message and convert
 *  it to XML format using a QMS_Remos_Msg object on the fly.
 */
void
generate_query(void)
{
  QMS_Trace ("generate_query", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG Thread Created\n");
  ACE_Time_Value sleep_time (STDC::QMS::QMS_DEFAULT_retry_sleep_interval * ACE_OS::rand()%30, 0);
  DEBUG0 (DEBUG_L_CALL, "DEBUG Thread sleeping\n");
  ACE_Thread::yield();
  ACE_OS::sleep (sleep_time);
  DEBUG0 (DEBUG_L_CALL, "DEBUG Thread awake\n");

  if (filename_p)
   {
     file_message(filename_p);
   }
  else
   {
     mock_message();
   }
  DEBUG0 (DEBUG_L_LEAVE, "DEBUG Thread all done, exiting\n");
}



/**
 *  @param data The data recieved from the event channel
 *  @param arg_p Optional argument
 *  @brief Function called when there is an event to be consumed
 *
 *  Whenever an event is recieved, we convert it from XML into a a
 *  struct Data_struct, printing out both the data structure and the
 *  converted XML
 */
void
my_cb_func(const string &data, void *arg_p = 0)
{
  QMS_Trace ("my_cb_func", __LINE__, __FILE__);
  cout << "============================================================"
       <<endl;

  cout << "Got some data" << endl
       << data << endl;

  if (arg_p)
   {
     cout << "With a non null argument"  << endl;
   }


/*  QMS_Remos_Msg message;
  message.insert(data);
  struct Data_struct *data_p = message.extract_data();
  cout << "============================================================"
       <<endl;
   print_data(data_p);
  cout << "============================================================"
       <<endl;
*/
 }


/**
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 * Usage:   [CORBA OPTIONS] [OPTIONS]
 *     -  -h             : This help text
 *     -  -v             : Prints out the version
 *     -  -file Filename : Read XML data from here
 *     -  -f    Filename : Read XML data from here
 *     -  -ecname NAME   : The name of the event channel
 *     -  -e      NAME   : The name of the event channel
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

  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");
  ACE_OS::srand(time(0));

  DEBUG3 (DEBUG_L_CALL, "DEBUG: starting the API With ID = %d"
	  " Send event type = %d Recieve event type = %d\n" ,
	  Query_Supplier, QMS_Remos_Query, QMS_Remos_Data);

  char * ecname_p = (char *) "QMS_Channel";

  DEBUG0 (DEBUG_L_CALL, "DEBUG: parsing arguments\n");
  for (int i = 0; i < argc; i++)
   {
     if (!argv[i])           { break; }
     if (argv[i][0] != '-')  { continue; }
     int j = 1;
     if (argv[i][1] == '-')  {
       if (argv[i][2] == 0)  { break; }	// handle -- end of options
       j = 2;			// handle --argument
     }
     if (strstr((argv[i] + j), "ORB"))  { continue; }
     if (! strcmp((argv[i] + j), "help") || strchr((argv[i] + j), 'h'))
      {				// -h or --help
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
     if (! strcmp((argv[i] + j), "ecname") || strchr((argv[i] + j), 'f'))
      {
	ecname_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
	strcpy(ecname_p,argv[i + 1]);
	continue;
      }
     DEBUG1 (DEBUG_L_ERROR, "unknown argument %s", argv[i] );
   }


  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {

      STDC::QMS::CORBA_Handles *handles_p = new STDC::QMS::CORBA_Handles();
      handles_p->init(argc, argv, "Hello World  Client", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_TRY_CHECK;
      ec_adapter.init(argc, argv,
		   Query_Supplier,  // My ID
		   QMS_Remos_Query, //  The data I send
		   QMS_Remos_Data,  // The data I get
		   ecname_p,
                   handles_p
		   );
      ACE_TRY_CHECK;

      ec_adapter.register_callback(my_cb_func, 0);
      ACE_TRY_CHECK;
      ec_adapter.connect_supplier();
      ACE_TRY_CHECK;
      ec_adapter.connect_consumer();
      ACE_TRY_CHECK;

      DEBUG0 (DEBUG_L_CALL, "DEBUG: Spawning a thread\n");

      if (ACE_Thread::spawn((ACE_THR_FUNC)generate_query,
			    0,	// arg
			    THR_JOINABLE, // flags
			    0,	// t_id
			    0,	// t_handle
			    ACE_DEFAULT_THREAD_PRIORITY,
			    0,	// stack
			    0,	// stack_size
			    0	// thread_adapter
			    )==-1)
       {
	 DEBUG0 (DEBUG_L_ERROR, "DEBUG: Error in spawning thread\n");
       }
      DEBUG0 (DEBUG_L_CALL, "DEBUG: Entering Loop\n");
      //CORBA::Long supplier_id = get_supplier_id(argc, argv, ACE_TRY_ENV);
      printf ("Entering the Listen \n");
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

  exit (0);
}

CORBA::Long
get_supplier_id(int argc, char **argv, CORBA_Environment &ACE_TRY_ENV)
{
    CORBA::Long supplier_id = 2000;
    ACE_TRY
    {
      CORBA::ORB_var orb;
      PortableServer::POA_var root_poa;
      PortableServer::POAManager_var poa_manager;

      orb = CORBA::ORB_init (argc, argv, "Hello World Client", ACE_TRY_ENV);
      ACE_TRY_CHECK;
      if (CORBA::is_nil (orb.in ())){
        ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
        int count = 0;
        while (CORBA::is_nil (orb.in ())){
          if (count >= QMS_DEFAULT_number_of_retries){
            ACE_ERROR ((LM_ERROR,"(%P|%t) get_supplier_id :- Unable to initialize the orb.\n"));
            ACE_TRY_THROW (CORBA::BAD_PARAM ());
          }
          ACE_OS::sleep (sleep_time);
          ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- retrying getting the orb\n"));
          orb =
            CORBA::ORB_init (argc, argv, "Hello World Client", ACE_TRY_ENV);
          ACE_TRY_CHECK;
          count++;
        }
      }
      else
       {
         ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- Orb initilized(no external data yet)\n"));
       }

     // Ok. The portable Object Adapter is next
      if (CORBA::is_nil (root_poa.in ())){
        CORBA::Object_var poa_object =
          orb->resolve_initial_references("RootPOA");
        ACE_TRY_CHECK;

        root_poa =
          PortableServer::POA::_narrow (poa_object.in (), ACE_TRY_ENV);
        ACE_TRY_CHECK;
        ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- Narrowed the root poa\n"));

        if (CORBA::is_nil (poa_object.in ())){
          ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
          int count = 0;
          while (CORBA::is_nil (root_poa.in ())){
            if (count >= QMS_DEFAULT_number_of_retries){
              ACE_ERROR ((LM_ERROR," get_supplier_id :- Unable to initialize the POA.\n"));
              ACE_TRY_THROW (CORBA::BAD_PARAM ());
            }
            ACE_OS::sleep (sleep_time);
            ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- retrying getting root poa\n"));

            CORBA::Object_var poa_object =
              orb->resolve_initial_references("RootPOA");
            ACE_TRY_CHECK;

            root_poa =
              PortableServer::POA::_narrow (poa_object.in (), ACE_TRY_ENV);
            ACE_TRY_CHECK;
            ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- Narrowed the root poa\n"));

            count++;
          }
        }
        else {
          ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- Got the root poa(no external data yet)\n"));
        }
      }
      else
       {
         ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- Already had root poa handle\n"));
       }

      // Now we get the manager
      if (CORBA::is_nil (poa_manager.in ())) {
        poa_manager =
          root_poa->the_POAManager (ACE_TRY_ENV);
        ACE_TRY_CHECK;
        if (CORBA::is_nil (poa_manager.in ())) {
          ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
          int count = 0;
          while (CORBA::is_nil (poa_manager.in ())){
            if (count >= QMS_DEFAULT_number_of_retries){
              ACE_ERROR ((LM_ERROR,"(%P|%t) get_supplier_id :- Unable to get the POA mgr.\n"));
              ACE_TRY_THROW (CORBA::BAD_PARAM ());
            }
            ACE_OS::sleep (sleep_time);
            ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- retrying getting the poa manager\n"));

            poa_manager =
              root_poa->the_POAManager (ACE_TRY_ENV);
            ACE_TRY_CHECK;

            count++;
          }
        }
        else {
          ACE_DEBUG((LM_DEBUG, "get_supplier_id :- Got the poa manager(no external data yet)\n"));
        }
      }
      else
       {
         ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- Already had poa manager handle\n"));
       }

      // Getting the lookup interface next.
      CORBA::Object_var trading_obj = 
                          orb->resolve_initial_references ("TradingService");
      ACE_TRY_CHECK;
      if (CORBA::is_nil (trading_obj.in ())){
           ACE_Time_Value sleep_time (QMS_DEFAULT_retry_sleep_interval, 0);
           int count = 0;
           while (CORBA::is_nil (trading_obj.in ())){
             if (count >= QMS_DEFAULT_number_of_retries) {
               ACE_ERROR ((LM_ERROR," get_supplier_id :- Unable to locate Trading service\n"));
               ACE_TRY_THROW (CORBA::BAD_PARAM ());
             } // end of if(count >= QMS_DEFAULT_number_of_retries)
             ACE_OS::sleep (sleep_time);
             ACE_DEBUG ((LM_DEBUG, "get_supplier_id :- retrying getting Trading service\n"));

             trading_obj =
               orb->resolve_initial_references("TradingService");
             ACE_TRY_CHECK;

             count++;
           } // end of while(CORBA::is_nil (trading_obj.in ())

         } // end of if(CORBA::is_nil (_trading_obj.in ())) 

         CosTrading::Lookup_var lookup_var = 
                     CosTrading::Lookup::_narrow (trading_obj.in (), ACE_TRY_ENV);
         ACE_TRY_CHECK;
    }

    ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      ACE_RE_THROW;
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return supplier_id;

}



#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

//template class vector<STDC::QMS::Push_Consumer *, __default_alloc_template<true, 0> >;

template void fill<STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer **, STDC::QMS::Push_Consumer * const &);

template STDC::QMS::Push_Consumer ** fill_n<STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer *>(STDC::QMS::Push_Consumer **, unsigned int, STDC::QMS::Push_Consumer * const &);

//template class vector<STDC::QMS::Push_Supplier *, __default_alloc_template<true, 0> >;

template void fill<STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier *>(STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier **, STDC::QMS::Push_Supplier * const &);

template STDC::QMS::Push_Supplier ** fill_n<STDC::QMS::Push_Supplier **, unsigned int, STDC::QMS::Push_Supplier *>(STDC::QMS::Push_Supplier **, unsigned int, STDC::QMS::Push_Supplier * const &);

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

