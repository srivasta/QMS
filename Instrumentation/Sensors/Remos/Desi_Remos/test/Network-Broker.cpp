//Network-Broker.cpp
// Author Shivakumar C. Patil (shivakumar.patil@stdc.com)


#pragma warning( disable: 4786 )
#pragma warning( disable: 4788 )

/*****************************************************************************/

#include "ace/OS.h"             
#include "ace/Log_Msg.h"
#include "ace/Containers_T.h"
#include "ace/Get_Opt.h"
#include "ace/Thread.h"
#include "ace/Synch.h"
#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include "tao/ORB_Core.h"

// System Includes

#include <iostream>
#include <fstream>
#include <strstream>
#include <vector>
#include <set>

// User includes

#include "Network-Broker.h"
#include "comm-lib.h"
#include "netorder.h"


#include "Client.h"
#include "Payload.h"

/*****************************************************************************/

// Global Variables

static const char* FILE_ID = "$Id";

NetworkBroker NB;

int count = 0;
double refresh_rate = 5;       // refresh rate in seconds
int repeat_count = 1;            // number of reports
ACE_Thread_Mutex TD_asset_guard;



// local prototypes

void qms_wrapper_cb(const string& data, void* arg_p);
void ace_wrapper_spawn(void *arg_p);


static void
qms_wrapper_cb(const string& data, void* arg_p)
{
  /* * wrapper function to get around return type mismatch */

  NB.process_remos_data(data, arg_p);

}/* qms_wrapper_cd() */


static void
ace_wrapper_spawn(void *arg_p)
{
  /* * wrapper function to get around return type mismatch */

  NB.submit_remos_query(arg_p);

}/* ace_wrapper_spawn() */


/*********************************************************************
** Main function for Network Broker.
*********************************************************************/

/// The client is a global variable
Test_Client *client_p = new Test_Client();

/**
 * @brief A concrete implementation for handling errors 
 *
 * This class is used to register a signal handler registered with the
 * reactor used by the TAO ORB. We over ride the handle_signal method
 * and use it to act on signals we register handlers for.
 */
class client_error_handler : public ACE_Event_Handler
{
public:
  /// The default constructor for the classclient_error_handler
  client_error_handler(Test_Client *client_p):  _client_p(client_p){};
  /// This method takes action on an   signal event.
  int handle_signal (int signum, siginfo_t *info_p, ucontext_t* context_p);
  
private:
  /// Private destructor so that the signal handler is always created
  /// dynamically and hence the heap doesnt get corrupted.
  /// the destructor
  ~client_error_handler(){};
  /// Without this g++ complains about the private destructor
  friend class Shut_Up_G_Plus_Plus;
  
  /// Stash away the sensor object so we can exit gracefully
  Test_Client *_client_p;  
};// end of class client_error_handler

/**
 * @brief The action to take when a registered signal is  handled. 
 *
 * Essentially, we just shut down the sensor object, which
 * causes the ORB to shutdown.
 */
int
client_error_handler::handle_signal (int signum, siginfo_t *info_p, 
     ucontext_t* context_p)
{
  cerr << "Received signal" << signum << std::endl;
  this->_client_p->cleanup();
  //return 0;
  exit(0);
}


/**
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 *
 * Usage:   [CORBA OPTIONS] [OPTIONS]
 *     -  -h             : This help text
 *     -  -v             : Prints out the version
 */

int
main(int argc,
     char *argv[])
{
  char* NS_host = 0;
  int NS_port;
  char* NA = 0;
  char* host_file = 0;
  remos_link_type flow = remos_flow;// -- mr - verify if value is okay?

  // Initialize the CORBA Handles and signal handler for Client.
  client_error_handler *signal_handler_p = new client_error_handler(client_p);

  STDC::QMS::CORBA_Handles *handles_p = new STDC::QMS::CORBA_Handles();
  if(!handles_p)
   {
       cerr << "Error creating corba handles" <<std::endl;
       exit (EXIT_FAILURE);
   } /* end of if(!handles_p) */


  switch(argc)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      cout << endl << "Usage:  " << argv[0]
           << " <reporting_interval> <repeat_count> <name_server_host> "
           << "<name_server_port> <network-analyzer> <host_file>"
           << endl;
      exit(0);
    case 11:
      refresh_rate = atof(argv[1]);
      repeat_count = atoi(argv[2]);
      NS_host = argv[3];
      NS_port = atoi(argv[4]);
      NA = argv[5];
      host_file = argv[6];
      break;
    default:
      cout << endl << "Usage:  " << argv[0]
           << " <reporting_interval> <repeat_count> <name_server_host> "
           << " <name_server_port> <network-analyzer> <host_file>"
           << endl; 
      exit(0);
    }

  NB.init(NS_host, NS_port, NA);

  if(!NB.connect_network_analyzer())
    {
      cerr << "Could not connect to Network Analyzer" << endl;
      exit(1);
    }

  NB.init_host_pairs(host_file);

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
  
      DEBUG0 (4," Initializing the Corba Handles \n");
      handles_p->init(argc, argv, "Remos_Client", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      DEBUG0 (4,"Activating POA Manager using the handles.\n ");
      handles_p->activate_poa_manager(ACE_TRY_ENV);
      ACE_TRY_CHECK;
 
      if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler
                                            (SIGINT, signal_handler_p) == -1)
       {
          cerr << "Error:register_handler for SIGINT" << std::endl;
          delete handles_p;
          exit (EXIT_FAILURE);
       }
#if !defined (_WIN32)
      if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler
                                            (SIGHUP, signal_handler_p) == -1)
       {
         cerr << "Error:register_handler for SIGHUP" << std::endl;
         delete handles_p;
         exit (EXIT_FAILURE);
       }
#endif
      if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler
                                           (SIGABRT, signal_handler_p) == -1)
       {
         cerr << "Error:register_handler for SIGABRT" << std::endl;
         delete handles_p;
         exit (EXIT_FAILURE);
       }
      if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler
                                           (SIGTERM, signal_handler_p) == -1)
       {
          cerr << "Error:register_handler for SIGTERM" << std::endl;
          delete handles_p;
          exit (EXIT_FAILURE);
       }

      client_p->init(*handles_p, (char *)"Remos_Network_Graph client", 
                     host_file, repeat_count, refresh_rate, 
                          (char *)"Remos_Network_Graph",  ACE_TRY_ENV);

      client_p->connect_EC(&qms_wrapper_cb, (void *)client_p, ACE_TRY_ENV);

      DEBUG0 (4, "DEBUG: Client intialized. Client going to run\n");
      DEBUG0 (4, "DEBUG: Spawning the message sending thread\n");
      if (ACE_Thread::spawn((ACE_THR_FUNC)&ace_wrapper_spawn,
                            (void *)client_p,// arg
                            THR_JOINABLE, // flags
                            0,// t_id
                            0,// t_handle
                            ACE_DEFAULT_THREAD_PRIORITY,
                            0,// stack
                            0,// stack_size
                            0// thread_adapter
                            )==-1)
       {
          cerr << "DEBUG: Error in spawning thread" << std::endl;
       }
       DEBUG0 (4, "DEBUG: Entering Loop\n");
       handles_p->run(ACE_TRY_ENV);
       ACE_TRY_CHECK;
    }
   ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      client_p->cleanup();
      exit (1);
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      client_p->cleanup();
      exit (2);
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      client_p->cleanup();
      exit (3);
    }
  ACE_ENDTRY;

  return(0);

}        /* main() */


NetworkBroker::NetworkBroker(void)
{
  _name_server_host = NULL;
  _name_server_port = -1;
  _network_analyzer = NULL;
  _network_analyzer_socket = -1;

}        /* NetworkBroker::NetworkBroker() */


NetworkBroker::NetworkBroker(char* name_server_host,
     int name_server_port,
     char* network_analyzer)
{
  _name_server_host = name_server_host;
  _name_server_port = name_server_port;
  _network_analyzer = network_analyzer;
  _network_analyzer_socket = -1;

}        /* NetworkBroker::NetworkBroker() */


int
NetworkBroker::init(char* name_server_host, int name_server_port,
                                          char* network_analyzer)
{
  _name_server_host = name_server_host;
  _name_server_port = name_server_port;
  _network_analyzer = network_analyzer;
  _network_analyzer_socket = -1;

  return(0);

}       /* NetworkBroker::init() */


NetworkBroker::~NetworkBroker()
{

}       /* NetworkBroker::~NetworkBroker() */


bool
NetworkBroker::connect_network_analyzer()
{
  int i = 0;
  const int timeout = 6;

  while (((_network_analyzer_socket = NewClientInitialize("NB", _network_analyzer, _name_server_host, _name_server_port)) < 0) && (i++ < timeout))
    {
      cerr << "Error in initialization with Network Analyzer" << endl;
      Sleep(10000);
    }

  if (i >= timeout)
    {
      return(false);
    }

/* Note:  The following two Desi comm-lib functions are defined
** as void and therefore return no status.
*/

  InitializeClientTable();
  AddAppSocket(_network_analyzer, _network_analyzer_socket);

  return(true);

}       /* NetworkBroker::connect_network_analyzer() */


bool
NetworkBroker::init_host_pairs(const char* filename)
{
  ifstream hf_stream(filename, ios::in);
  string hostname;
  unsigned int i = 0;// host counter


  cerr << "ENTER - NB::init_host_pairs(filename)\n";

  hf_stream >> hostname;

  while (!hostname.empty())
    {
      _hosts.insert(hostname);
      cerr << "NB::init_host_pairs() inserted host["
   << i << "] = <" << hostname << ">\n";
      i++;
      hf_stream >> hostname;
    }

/* -- mr
while(getline(hf_stream, hostname))
{
_hosts.insert(hostname);

cerr << "NB::init_host_pairs() inserted host[" << i << "] = <" << hostname << ">\n";
i++;
}

*/

  cerr << "NB::init_host_pairs() - inserted a total of <"
       << i << "> hosts\n";

  set<string>::const_iterator h_iter1;
  set<string>::const_iterator h_iter2;
  i = 0;

  for (h_iter1 = _hosts.begin(); h_iter1 != _hosts.end(); ++h_iter1)
    {
      for (h_iter2 = _hosts.begin(); h_iter2 != _hosts.end(); ++h_iter2)
      {
         if (!(*h_iter1).compare(*h_iter2))
         {
             break;
         }
         else
         {
           _host_pairs.push_back(make_pair(*h_iter1, *h_iter2));
            cerr << "NB::init_host_pairs() - making _host_pairs["
                 << i << "] <" << *h_iter1 << ", " << *h_iter2 << ">\n";
            i++;
         }
      }

    }

    cerr << "NB::init_host_pairs() - made <" << i << "> host_pairs\n";
    cerr << "EXIT - NB::init_host_pairs()\n";

    return(true);

} /* NetworkBroker::init_host_pairs(const char * filename) */




void
NetworkBroker::init_host_pairs()
{
  cerr << "NB::init_host_pairs() " << endl;

  set<string>::const_iterator h_iter1;
  set<string>::const_iterator h_iter2;
  unsigned int i = 0;// host counter

  for (h_iter1 = _hosts.begin(); h_iter1 != _hosts.end(); ++h_iter1)
    {
      for (h_iter2 = _hosts.begin(); h_iter2 != _hosts.end(); ++h_iter2)
      {
         if (!(*h_iter1).compare(*h_iter2))
         {
             break;
         }
         else
         {
           _host_pairs.push_back(make_pair(*h_iter1, *h_iter2));
            cerr << "NB::init_host_pairs() - making _host_pairs["
                 << i << "] <" << *h_iter1 << ", " << *h_iter2 << ">\n";
            i++;
         }
      }

    }

    cerr << "NB::init_host_pairs() - made <" << i << "> host_pairs\n";
    cerr << "EXIT - NB::init_host_pairs()\n";

} /* NetworkBroker::init_host_pairs() */




bool
NetworkBroker::submit_remos_query(void *arg_p)
{
  cerr << "ENTER - NB::submit_remos_query()\n";

  client_p->send_messages(arg_p);

  cerr << "EXIT - NB::submit_remos_query()\n";

  return(true);

}/* NetworkBroker::submit_remos_query() */


void
NetworkBroker::process_remos_data(const string& data, void *arg_p)
{
   cerr << "ENTER - NB::process_remos_data()\n";

   struct Payload_Data response_data;
   remos_link_type graph = remos_link;
   vector<RemosLinkData>::iterator _ldv_iter;
   string source, dest;
   int x;

   client_p->callback(data, arg_p, response_data);
   //Test_Client * client_p = (Test_Client *)arg_p;
   //payload_print(response_data);

   for (unsigned int i = 0; 
                  i < response_data.remos_data.bandwidth_data.size() ; i++ )

   {
       //cerr << "BANDWIDTH_DATA SIZE IS NOT NULL " << endl;
       if ( response_data.remos_data.bandwidth_data[i] != NULL )
       {   
           if ( !((response_data.remos_data.bandwidth_data[i]->linkdata.source.find("skywalker") != string::npos) ||
			    (response_data.remos_data.bandwidth_data[i]->linkdata.source.find("r2d2") != string::npos) ))
           {
			   x = response_data.remos_data.bandwidth_data[i]->linkdata.source.find(".stdc.com");
               response_data.remos_data.bandwidth_data[i]->linkdata.source.replace(x,9,"");
		   }

		   if (! ((response_data.remos_data.bandwidth_data[i]->linkdata.destination.find("skywalker") != string::npos) ||
			    (response_data.remos_data.bandwidth_data[i]->linkdata.destination.find("r2d2") != string::npos) ))
           {
			   x = response_data.remos_data.bandwidth_data[i]->linkdata.destination.find(".stdc.com");
               response_data.remos_data.bandwidth_data[i]->linkdata.destination.replace(x,9,"");
		   }

           source.assign(response_data.remos_data.
                                    bandwidth_data[i]->linkdata.source);
           dest.assign(response_data.remos_data.
                                bandwidth_data[i]->linkdata.destination);

           if ( _hosts.find(source) == _hosts.end() ) 
           {
              cerr << "Adding the new host " << source << endl;
              _hosts.insert(source);
              init_host_pairs();

           }
           else if ( _hosts.find(dest) == _hosts.end() )
           {
              cerr << "Adding the new host " << dest << endl;
              _hosts.insert(dest);
              init_host_pairs();

           }
           
		   bool link_data_exists = false;
           remos_link_type temp_link_type = graph;
           RemosLinkData remos_link_data((remos_link_type) temp_link_type,
           response_data.remos_data.bandwidth_data[i]->linkdata.source,
           response_data.remos_data.bandwidth_data[i]->linkdata.destination,
           atof(response_data.remos_data.
                                bandwidth_data[i]->linkdata.latency.c_str()),
           atof(response_data.remos_data.
                              bandwidth_data[i]->linkdata.available.c_str()),
           atof(response_data.remos_data.
                              bandwidth_data[i]->linkdata.maximum.c_str()) );
   
           vector<host_pair>::iterator hp_iter;
           // true if incoming host pair exists in host list
           bool exists = false;  

           for (hp_iter = _host_pairs.begin(); hp_iter != _host_pairs.end(); 
                                            ++hp_iter)
           {
            
			 //
             // see if the host pair already exists in the list
             /*
             cerr << "NB::process_remos_data()-comparing _host_pairs.first = <"
                  << (*hp_iter).first
                  << "> to _host_pairs.second = <"
                  << (*hp_iter).second
                  << ">\n";
              */

      
              if ((!(*hp_iter).first.compare(response_data.remos_data.
                                           bandwidth_data[i]->linkdata.source)
                  && !(*hp_iter).second.compare(response_data.remos_data.
                                    bandwidth_data[i]->linkdata.destination))
                  ||
                  (!(*hp_iter).second.compare(response_data.remos_data.
                                           bandwidth_data[i]->linkdata.source)
                  && !(*hp_iter).first.compare(response_data.remos_data.
                                     bandwidth_data[i]->linkdata.destination)))
             {
                // incoming host pair found in the host pair list
                /*
				cerr << "Exists is true for "
                     << (*hp_iter).first << "\t" << (*hp_iter).second << endl;
				*/
                
                exists = true;
                break;
             }

           } // end of host compare for loop.
   
           // defined above, so that this works for both the loops.
           //vector<RemosLinkData>::iterator _ldv_iter;
   
          if (exists && (_link_data_vector.size() > 0))
          {
      
            //host pair DATA may already exists in the populated vector list
            //find the host pair in the vector and update the link data 
            // if found.

      
           for (_ldv_iter = _link_data_vector.begin();
                _ldv_iter != _link_data_vector.end();
                ++_ldv_iter)
   
           {
               string temp_source_1 = (*_ldv_iter).source_node();
               string temp_source_2 = response_data.remos_data.
                                      bandwidth_data[i]->linkdata.source;
               string temp_destination_1 = (*_ldv_iter).destination_node();
               string temp_destination_2 = response_data.remos_data.
                                      bandwidth_data[i]->linkdata.destination;
                   
               remos_link_type temp_link_type = graph;
  
               if((!temp_source_1.compare(temp_source_2)
                        && !temp_destination_1.compare(temp_destination_2))
                        ||
                      (!temp_source_1.compare(temp_destination_2)
                       && !temp_destination_1.compare(temp_source_2)))
   
               {
                  // incoming host pair match found - update link data
                  link_data_exists = true;

                  (*_ldv_iter).set_link_type((remos_link_type) temp_link_type);
                  (*_ldv_iter).set_latency(atof(response_data.remos_data.
                                bandwidth_data[i]->linkdata.latency.c_str()) );
                  (*_ldv_iter).set_available_bandwidth(atof(response_data.
                   remos_data.bandwidth_data[i]->linkdata.available.c_str()) );
                  (*_ldv_iter).set_static_bandwidth(atof(response_data.
                     remos_data.bandwidth_data[i]->linkdata.maximum.c_str()) );

                  //
                  /*
                  cerr << "NB::process_remos_data() - Updated link data "
                       << "for vector host pair <"
                       << (*_ldv_iter).source_node()
                       << ", "
                       << (*_ldv_iter).destination_node()
                       << ">\n";
                  */
                  
                  break;
               } // enf of if for source and destination comparison.
   
            } // end of for

         }// end of if (exists && (_link_data_vector.size() > 0))
  
  
       if (link_data_exists == false)
       {
          //this is the first instance for this incoming host pair
          //insert host pair and link data into the vector.
       
          _link_data_vector.push_back(remos_link_data);

		  //
          /*   
          cerr << "NB::process_remos_data() - Added link data for " 
               << "new vector host pair <"
               << response_data.remos_data.bandwidth_data[i]->linkdata.source
               << ", "
               << response_data.remos_data.bandwidth_data[i]->linkdata.destination
               << ">\n";
          */
          
       }
 
        
       delete response_data.remos_data.bandwidth_data[i];

      } // end of if 

    } // end of for 


   //cerr << "DONE WITH THE BANDWIDTH_DATA VECTOR " << endl;
   ostrstream _NB_out;
   _NB_out << _link_data_vector.size();


   // append the link data of all the host pairs

  for (_ldv_iter = _link_data_vector.begin();
       _ldv_iter != _link_data_vector.end();
       ++_ldv_iter)

    {
      _NB_out << " "
              << (*_ldv_iter).link_type() << " "
              << (*_ldv_iter).source_node() << " "
              << (*_ldv_iter).destination_node() << " "
              << (*_ldv_iter).latency() << " "
              << (*_ldv_iter).available_bandwidth() << " "
              << (*_ldv_iter).static_bandwidth();
    }

  _NB_out << ends;
  _NB_data = _NB_out.str();
  _NB_out.freeze(false);

  
  //cerr << "NB::process_remos_data() - Sending to NA, _NB_data = <" 
       //<< _NB_data << ">\n";
  cerr << "NB::process_remos_data() - Sending to NA, _NB_data" << endl;

  // send the host pair link data to the DeSi Network Ananlyzer

  if (Send_Message(_network_analyzer_socket, "NB", _NB_data, 
                       (strlen(_NB_data) + 1)) < 0)
  {
      cerr <<"EXIT - NB::process_remos_data() - send ERROR - data NOT sent!\n";
      return;
  }

  cerr << "EXIT - NB::process_remos_data() - returning successfully\n";
  // -- mrreturn(true);
  return;

}        /* NetworkBroker::process_remos_data() */

