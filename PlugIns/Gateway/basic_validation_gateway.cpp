//                              -*- Mode: C++ -*- 
// basic_validation_gateway.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
// Created On       : Fri Dec  7 15:12:18 2001
// Created On Node  : glaurung.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu Dec 27 18:17:15 2001
// Last Machine Used: ember.green-gryphon.com
// Update Count     : 55
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
static const char* 
version = "$Id: basic_validation_gateway.cpp,v 1.26 2002/01/15 21:23:51 srivasta Exp $";

/** @file 
 *  @ingroup Facilities
 *  @brief The main file of the gateway
 *
 * $Id: basic_validation_gateway.cpp,v 1.26 2002/01/15 21:23:51 srivasta Exp $
 */

#include <string>
#include <cstring>
#include <csignal>
#include <cstdio>
#include <exception>
#include <stdexcept>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


#include "ace/Synch.h"
#include "ace/Thread.h"
#include "ace/Containers_T.h"
#include "ace/Get_Opt.h"
#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include "tao/ORB_Core.h"


#include "Debug.h"
#include "Parse_BV_Request.h"
#include "Gateway.h"
#include "Instrumentation.h"


STDC::QMS::Gateway *gateway_p = new STDC::QMS::Gateway::Gateway();

/**
 * @brief Perform the normal steps fpr a server
 * @param hostname The hostname to connect to
 * @param service The service name or port number to connect
 * @param hints  The kind of connection requested
 */
int
tcp_listen(const char * hostname, const char *service, 
	   socklen_t *address_length_p)
{
  QMS_Trace ("tcp_listen", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: tcp_listen\n");

  int n = 0;
  const int on = 1;
  
  int listenfd;
  struct addrinfo *results_listen_p = 0;
  struct addrinfo hints;
  DEBUG0 (2, "DEBUG: resetting memory\n");
  memset ((void *) &hints, 0, sizeof(struct addrinfo));

  DEBUG0 (2, "DEBUG: Initializing hints\n");
  hints.ai_flags    			  = AI_PASSIVE;
  hints.ai_family   			  = AF_INET;
  hints.ai_socktype 			  = SOCK_STREAM;
  DEBUG0 (2, "DEBUG: Done Initializing hints\n");

  std::cerr << "DEBUG: Hostname is " << hostname << " and the service is "
	    << service << std::endl;
  
  if((n = getaddrinfo(hostname, service, &hints, &results_listen_p)) != 0)
   {
     string this_error = "Error Getting address info for host: ";
     this_error.append(hostname);
     this_error.append(" service: ");
     this_error.append(service);
     std::cerr << this_error << std::endl;
     perror("getaddrinfo");
     throw std::runtime_error::runtime_error(this_error);
   } /* end of if((n = getaddrinfo(hostname, service, hints,
	results_listen_p)) != 0) */
  DEBUG0 (2, "DEBUG: Got address info\n");
  struct addrinfo *results_index_p = results_listen_p;
  
  do 
   {
     DEBUG0 (2, "DEBUG: Trying to listen\n");
     listenfd = socket(results_index_p->ai_family, 
		       results_index_p->ai_socktype,
		       results_index_p->ai_protocol);
     if(listenfd < 0)
      {
	continue;		// error, try next one
      } /* end of if(listenfd < 0) */
     DEBUG0 (2, "DEBUG: Listen worked. Trying to set socket options\n");

     if((n = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, 
			sizeof(on))) < 0)
      {
	string this_error = "Error Setting socket options";
	this_error.append(hostname);
	this_error.append(" service: ");
	this_error.append(service);
	std::cerr << this_error << std::endl;
	perror("setsockopts");
	throw std::runtime_error::runtime_error(this_error);
      } /* end of if((n = setsockopt(listenfd, SOL_SOCKET,
	   SO_REUSEADDR,  &on, sizeof(on))) < 0) */
     
     DEBUG0 (2, "DEBUG: Trying to bind\n");
     if(bind(listenfd, results_index_p->ai_addr, 
	     results_index_p->ai_addrlen) == 0)
     {
       DEBUG0 (2, "DEBUG: Bound\n");
       break;			// Success!
     } /* end of if(connect(listenfd, results_index_p->ai_addr,
	  results_index_p->ai_addrlen) == 0) */
     perror("bind");
     n = close(listenfd);		// ignore this one
     if(n < 0)
      {
	perror("close");	
	std::cerr << "Error closing socket " << __FILE__ << ":" 
		  << __LINE__ << " for " << hostname 
		  << " port " << service << std::endl;
      } /* end of if(n < 0) */
   }
  while((results_index_p = results_index_p->ai_next) != 0);
  if(results_index_p == 0)
   {
     string this_error = "Could not create a working passive socket on host ";
     this_error.append(hostname);
     this_error.append(" service: ");
     this_error.append(service);
     std::cerr << this_error << std::endl;
     throw std::runtime_error::runtime_error(this_error);
   } /* end of if(results_index_p == 0) */


  if(listen(listenfd, 10) < 0)
   {
     string this_error = "Could not listen on socket on host ";
     this_error.append(hostname);
     this_error.append(" service: ");
     this_error.append(service);
     std::cerr << this_error << std::endl;
     perror("listen");
     throw std::runtime_error::runtime_error(this_error);
   } /* end of if(listen(listenfd, 10) < 0) */
  
  if(address_length_p)
   {
     DEBUG0 (2, "DEBUG: Setting address length");
     *address_length_p = results_index_p->ai_addrlen;
   } /* end of if(address_length_p) */
  
  DEBUG0 (2, "DEBUG: Freeing addressinfo");
  freeaddrinfo(results_listen_p);
  DEBUG0 (2, "DEBUG: Done getting passive socket");
  return (listenfd);
}


void *
handle_message(void* arg_p)
{
  QMS_Trace ("handle_message", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: handle_message\n");
  int ret = 0;
  char * new_message_p = (char *) arg_p;
  if((ret = pthread_detach(pthread_self())) != 0)
  {
    perror("Detaching Thread");
    return 0;
  } /* end of if((ret = pthread_detach(my_id) != 0) */
     
  gateway_p->handle_query(new_message_p);

  delete [] new_message_p;
  pthread_exit(0);
  return 0;
}



void 
client_listen(int listenfd, socklen_t addrlen)
{
  QMS_Trace ("listen_on_socket", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: listen_on_socket\n");
  socklen_t len = 0;
  int connfd;
  int port;
  char address[128];


  struct sockaddr_in *cliaddr;
  cliaddr = ( struct sockaddr_in *) malloc(addrlen);
  assert(cliaddr);
  
  for(; ;)
   {
     len = addrlen;     
     address[0] = 0;
     port = 0;
     
     if((connfd = accept(listenfd, (struct sockaddr *) cliaddr, &len)) < 0)
     {
       std::cerr << "Error on connection: Ignoring" << std::endl;
       perror("accept");
       if(errno == EINTR)
	{
	  continue;
	} /* end of if(errno == EINTR) */
       else
	{
	  std::cerr << "Error on connection: Could not ignore" << std::endl;
	  exit(EXIT_FAILURE);
	} /* end of else */
     }
     // IPV4 specific stuff
     if(inet_ntop(AF_INET, &cliaddr->sin_addr, address, sizeof(address)) == 0)
      {
	std::cerr << "Error determining address: Ignoring" << std::endl;
	perror("inet_ntop(");
      } /* end of if(inet_ntop(AF_INET, &cliaddr->sin_addr, address, 
	   sizeof(address)) == 0) */
     if((port = ntohs(cliaddr->sin_port)) == 0)
      {
	std::cerr << "Error determining address: Ignoring" << std::endl;
	perror("ntohs");
      } /* end of if((port = ntohs(cliaddr->sin_port)) == 0) */
     std::cout << "Got connection on port " << port 
	       << "From address " << address << std::endl;
     
     char buff[BUFSIZ + 8192];
     ssize_t n ;
     
     string message;
     string raw_data;
     DEBUG0 (4, "DEBUG: Reading");
     bool done = false;
     while( !done)
      {
	n = read(connfd, buff, BUFSIZ + 8192);
	if(n < 0)
	 {
	   if(errno == EINTR)
	    {
	      continue;
	    } /* end of if(errno == EINTR) */
	   else
	    {
	      perror("read");
	      break;
	    } /* end of else */
	 } /* end of if(n < 0) */
	if(n == 0)
	 {
	   break;
	 } /* end of if(n == 0) */
	
        buff[n] = 0;
        DEBUG2 (2, "DEBUG: Read %d bytes --> \n%s", n, buff);
        raw_data.append(buff);

        string::size_type index = raw_data.find(STDC::QMS::Citizen::delimiter);
        while(index != string::npos)
         {
           // we have at least one complete message in here
	   message.erase();
           message.assign(raw_data, 0, index);
	   char * message_p = new char[strlen(message.c_str()) + 2];
	   strncpy(message_p, message.c_str(), strlen(message.c_str()) + 1);
	   
	   DEBUG1(2,"DEBUG: Now the message is\n%s\n", message_p);
	   pthread_t thread_id;
	   if((n = pthread_create(&thread_id, 0, handle_message, 
				  (void *) message_p)) != 0)
// 	   if((n = ACE_Thread::spawn((ACE_THR_FUNC)handle_message,
//                               (void *)message_p,  // arg
//                               THR_JOINABLE, // flags
//                               0,  // t_id
//                               0,  // t_handle
//                               ACE_DEFAULT_THREAD_PRIORITY,
//                               0,  // stack
//                               0,  // stack_size
//                               0   // thread_adapter
//                               )) !=0) 
	    {
	      std::cerr << "Error spawning read thread" << std::endl;
	      perror("pthread_create");
	    } /* end of if((n = pthread_create(thread_id, 0, listen_on_socket, 
		 (void *)&sockfd)) != 0) */
	   
           raw_data.erase(0, index + strlen(STDC::QMS::Citizen::delimiter));
           index = raw_data.find(STDC::QMS::Citizen::delimiter);

         } /* end of while(message.find(delimiter) != string::npos) */
      } /* end of while((n = read(datapipe[0], buff, BUFSIZ + 8192) ) > 0)*/
     if(n == -1)
      {
        perror("read from child\n");
      } /* end of if(n == -1) */
     if((n = close(connfd)) < 0)
      {
	std::cerr << "Error closing connected socket" << std::endl;
	perror("Closing connected socket");
      } /* end of if((n = close(connfd)) < 0) */
     
     DEBUG0 (6, "DEBUG: Finished reading");
   } /* end of for(; ;) */
}

void *
create_server(void * arg_p)
{
  QMS_Trace ("create_server", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: create_server\n");

  char *port_p = (char *)arg_p;
  
  char hostname[ MAXNAMELEN ];
  ACE_OS::hostname( hostname, MAXNAMELEN );
  DEBUG1(2,"Our Hostname is %s", hostname);
  

  socklen_t addrlen;
  socklen_t my_addrlen;
  int                    localport= 0;
  int 			 listenfd = 0;
  struct sockaddr_in 	*my_addr  = 0;
  try
   {
     listenfd = tcp_listen(NULL, port_p, &addrlen);
   }
  catch (... )
   {
     std::cerr << "Caught an exception"  << std::endl;
     exit (EXIT_FAILURE);
   }

  my_addr  = (struct sockaddr_in *) malloc(addrlen);
  if(!my_addr)
   {
     std::cerr << "Error Allocating memory" << std::endl;
     exit (EXIT_FAILURE);
   } /* end of if(!my_addr) */
  my_addrlen = addrlen;
  ssize_t n;
  
  if((n = getsockname(listenfd, (struct sockaddr *)my_addr, 
		      &my_addrlen)) < 0)
   {
     std::cerr << "Error determining port " << std::endl;
     exit (EXIT_FAILURE);
   } /* end of if(getsockname(listenfd, &my_addr, addrlen) < 0) */
  if((localport = ntohs(my_addr->sin_port)) == 0)
   {
     std::cerr << "Error determining address: Ignoring" << std::endl;
     perror("ntohs");
   } /* end of if((port = ntohs(cliaddr->sin_port)) == 0) */
  else
   {
     std::cerr << "DEBUG: The local port is " << localport
	       << std::endl;
   } /* end of else */

  client_listen(listenfd, addrlen);
  return 0;
}

/**
 * @brief A concrete implementation for handling errors 
 *
 * This class is used to register a signal handler registered with the
 * reactor used by the TAO ORB. We over ride the handle_signal method
 * and use it to act on signals we register handlers for.
 */
class gateway_error_handler : public ACE_Event_Handler
{
public:
  /// The default constructor for the classgateway_error_handler
  gateway_error_handler(STDC::QMS::Gateway *gateway_p,
                       STDC::QMS::CORBA_Handles *handles_p):
    handles_p_(handles_p), gateway_p_(gateway_p) {};

  /// This method takes action on an   signal event.
  int handle_signal (int signum, siginfo_t *info_p, ucontext_t* context_p);

  
protected:
  
private:
  /// Private destructor so that the signal handler is always created
  /// dynamically and hence the heap doesnt get corrupted.
  /// the destructor
  ~gateway_error_handler(){};
  /// Without this g++ complains about the private destructor
  friend class Shut_Up_G_Plus_Plus;

  /// Stash away a pointer to the the CORBA Handles
  STDC::QMS::CORBA_Handles *handles_p_;
  
  /// Stash away the gateway object so we can exit gracefully
  STDC::QMS::Gateway *gateway_p_;
  
};      // end of class gateway_error_handler

/**
 * @brief The action to take when a registered signal is  handled. 
 *
 * Essentially, we just shut down the gateway object, which
 * causes the ORB to shutdown.
 */
int
gateway_error_handler::handle_signal (int signum, siginfo_t *info_p, 
                                     ucontext_t* context_p)
{
  std::cerr << "Received signal" << signum << std::endl;
  if(signum == SIGCHLD)
   {
     std::cerr << " Handling SIGCHLD" << std::endl;
#if !defined(_WIN32)
     pid_t pid;
     int stat;
     while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
      {
        std::cerr << " Child" << pid << " terminated" << std::endl;
      } /* end of while((pid = waitpid(-1, &stat, WNOHANG)) > 0) */
#endif
     return 0;
   } /* end of if(signum == SIGCHLD) */
  
  this->gateway_p_->cleanup();
  this->handles_p_->get_orb_handle()->shutdown ();
  return 0;
}

void
add_handler(gateway_error_handler *signal_handler_p, 
            STDC::QMS::CORBA_Handles *handles_p, int signal)
{
//       CORBA::ORB_var my_orb = handles_p->get_orb_handle();
//       TAO_ORB_Core *orb_core_p = my_orb->orb_core();
//       ACE_Reactor *reactor_p = orb_core_p->reactor();
//       int ret = reactor_p->register_handler(SIGINT, signal_handler_p);
  DEBUG1 (4, "DEBUG: Adding signal for signal number %d\n",
          signal);

  if(handles_p->get_orb_handle()->orb_core()->reactor()->register_handler(SIGINT
, signal_handler_p) == -1)
   {
     std::cerr << "Error:register_handler for " << signal
               << std::endl;
     if(handles_p)
      {
        delete handles_p;
        handles_p = 0;
      } /* end of if(handles_p) */
     exit (EXIT_FAILURE);
   }
}


/// The structure that the query is packed into in order to spawn a thread
struct pack_args 
{
  /// The query string of interest
  string query;
};
/**
 * @brief An function passed to a new thread to handle the incoming query
 * @param args_p A struct pack_args with the information required
 *
 * This function is needed since we need a global (or a static method)
 * to be passed to pthread_create. A non-method in this file was
 * deemed to be clearer rather than creating a static method that
 * would tend to get lost in all the other mehtods in the sensor
 * object. 
 */
void *
do_query (void * args_p)
{
  QMS_Trace ("do_query", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: do_query\n");  
  int ret = 0;

  if((ret = pthread_detach(pthread_self())) != 0)
  {
    perror("Detaching Thread");
    return 0;
  } /* end of if((ret = pthread_detach(my_id) != 0) */

  struct pack_args *packed_p = (struct pack_args *)args_p;
  if(packed_p)
   {
     DEBUG0(2, "DEBUG: testing output\n");  
     if(!packed_p->query.empty())
      {
	DEBUG0(2, "DEBUG: Calling handle_data\n");  
        gateway_p->handle_data(packed_p->query);
      } /* end of if(sensor_p) */
     else
      {
	std::cerr << "Error: nothing to write" << std::endl;
      } /* end of else */
     
     packed_p->query.erase();
     delete packed_p;
     packed_p = 0;
   } /* end of if(packed_p) */
  else
   {
     std::cerr << "Error: null argument passed in to thread" << std::endl;
   } /* end of else */  
  DEBUG0(6, "DEBUG: Finished Handling Query\n");  
  pthread_exit(0);
  return 0;
}
/**
 * @brief The callback function to handle incoming data
 * @param response The incoming message to handle
 * @param arg_p A pointer to a Client Object
 *
 */
void
callback(const string &response, void *arg_p)
{
  QMS_Trace("callback", __LINE__, __FILE__);
  DEBUG0(2, "DEBUG: callback\n");

  if(arg_p)
   {
     std::cerr << "Warning: Unknown argument " << __FILE__
	       << " " << __LINE__ << std::endl;
   } /* end of if(arg_p) */
  
  struct pack_args  *packed_p = new pack_args;
  packed_p->query    = response;

  pthread_t thread_id;
  DEBUG0(2, "DEBUG: Going to spawn thread\n");
  int ret = pthread_create(&thread_id, 0, do_query, 
			   (void *) packed_p);
  

//   int ret = ACE_Thread::spawn((ACE_THR_FUNC)do_query,
//                               (void *)packed_p,  // arg
//                               THR_JOINABLE, // flags
//                               0,  // t_id
//                               0,  // t_handle
//                               ACE_DEFAULT_THREAD_PRIORITY,
//                               0,  // stack
//                               0,  // stack_size
//                               0   // thread_adapter
//                              );
  if(ret != 0)
   {
     perror ("Thread Cretion failed\n");
   } /* end of if(ret == -1) */
  DEBUG0(4, "DEBUG: Created thread to handle query\n");
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
main (int argc, char *argv[])
{
  QMS_Trace ("main", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: Gateway starting\n");

  char *filename_p = 0;

  STDC::QMS::CORBA_Handles *handles_p = new STDC::QMS::CORBA_Handles();
  if(!handles_p)
   {
     std::cerr << "Error creating corba handles" <<std::endl;
     exit (EXIT_FAILURE);
   } /* end of if(!handles_p) */

  gateway_error_handler *signal_handler_p = 
    new gateway_error_handler(gateway_p, handles_p);

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
        std::cout << argv[0] << version << std::endl
                  << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
                  << std::endl
                  << "\t-h             : This help text"  << std::endl
                  << "\t-v             : Prints out the version"  << std::endl
                  << "\t-file Filename : Read XML data from here"  << std::endl
                  << "\t-f    Filename : Read XML data from here"  << std::endl
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        std::cout << argv[0] << ": Version "<< version << std::endl;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "file") || strchr((argv[i] + j), 'f'))
      {
        filename_p = (char *) malloc (strlen(argv[i + 1]) + 1);
        strcpy(filename_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (6, "unknown argument %s", argv[i] );
   }

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {      
      std::cout << "CORBA Handles" << std::endl;
      handles_p->init(argc, argv, "Generic_Sensor", ACE_TRY_ENV);
      ACE_TRY_CHECK;
      std::cerr << "DEBUG: initialized corba handles" << std::endl;
  
      DEBUG0 (4,"Activating POA Manager using the handles.\n ");
      handles_p->activate_poa_manager(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      std::cout << "Initializing Gateway" << std::endl;
      gateway_p->init(handles_p, ACE_TRY_ENV);
      pthread_t server_id;
      if((pthread_create(&server_id, 0, create_server, 
			     (void *) "8989")) != 0)
// 	int n ;
//         if((n = ACE_Thread::spawn((ACE_THR_FUNC)create_server,
//                               (void *) "8989",  // arg
//                               THR_JOINABLE, // flags
//                               0,  // t_id
//                               0,  // t_handle
//                               ACE_DEFAULT_THREAD_PRIORITY,
//                               0,  // stack
//                               0,  // stack_size
//                               0   // thread_adapter
//                               )) == -1) 

       {
	 std::cerr << "Error spawning server thread" << std::endl;
	 perror("pthread_create");
       }
      std::cerr << "DEBUG: Adding signal handlers" << std::endl;
      add_handler(signal_handler_p, handles_p, SIGINT);
      add_handler(signal_handler_p, handles_p, SIGHUP);
      add_handler(signal_handler_p, handles_p, SIGQUIT);
      add_handler(signal_handler_p, handles_p, SIGABRT);
      add_handler(signal_handler_p, handles_p, SIGUSR1);
      add_handler(signal_handler_p, handles_p, SIGSEGV);
      add_handler(signal_handler_p, handles_p, SIGUSR2);
      add_handler(signal_handler_p, handles_p, SIGPIPE);
      add_handler(signal_handler_p, handles_p, SIGTERM);
      add_handler(signal_handler_p, handles_p, SIGCHLD);
      std::cerr << "DEBUG: Starting the loop" << std::endl;
      handles_p->run(ACE_TRY_ENV);
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,"Caught exception:");
      std::cout << "Cleaning up" << std::endl;
      gateway_p->cleanup();
    }
  ACE_ENDTRY;

  delete handles_p;
  handles_p = 0;
  
  delete gateway_p;
  gateway_p = 0;

  std::cout << "Gateway Done" << std::endl;
  exit(EXIT_SUCCESS);
} /* end of main() */
