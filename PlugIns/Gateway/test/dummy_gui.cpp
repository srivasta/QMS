//                              -*- Mode: C++ -*- 
// dummy_gui.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
// Created On       : Fri Dec  7 15:12:18 2001
// Created On Node  : glaurung.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Dec 12 21:41:30 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 79
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
version = "$Id: dummy_gui.cpp,v 1.5 2001/12/16 01:51:44 srivasta Exp $";

/** @file 
 *  @ingroup Facilities
 *  @brief A Dummy Basic Validation GUI replacement for testing
 *
 * $Id: dummy_gui.cpp,v 1.5 2001/12/16 01:51:44 srivasta Exp $
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


#include "Debug.h"
#include "Instrumentation.h"

/**
 * @brief Perform the normal steps fpr a client
 * @param hostname The hostname to connect to
 * @param service The service name or port number to connect
 */
int
tcp_connect(const char * hostname, const char *service)
{
  QMS_Trace ("tcp_connect", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: tcp_connect\n");
  int n = 0;
  int sockfd;
  struct addrinfo *results_talk_p = 0;

  struct addrinfo hints;
  memset ((void *) &hints, 0, sizeof(struct addrinfo));

  hints.ai_flags    			  = AI_CANONNAME;
  hints.ai_family   			  = AF_INET;
  hints.ai_socktype 			  = SOCK_STREAM;  
  

  
  if((n = getaddrinfo(hostname, service, &hints, &results_talk_p)) != 0)
   {
     string this_error = "Error Getting address info for host: ";
     this_error.append(hostname);
     this_error.append(" service: ");
     this_error.append(service);
     throw std::runtime_error::runtime_error(this_error);
   } /* end of if((n = getaddrinfo(hostname, service, hints,
	results_talk_p)) != 0) */

  DEBUG0 (2, "DEBUG: Got address info\n");

  struct addrinfo *results_index_p = results_talk_p;
  
  do 
   {
     sockfd = socket(results_index_p->ai_family, 
		     results_index_p->ai_socktype,
		     results_index_p->ai_protocol);
     if(sockfd < 0)
      {
	continue;
      } /* end of if(sockfd < 0) */

     if(connect(sockfd, results_index_p->ai_addr, 
		results_index_p->ai_addrlen) == 0)
     {
       break;
     } /* end of if(connect(sockfd, results_index_p->ai_addr,
	  results_index_p->ai_addrlen) == 0) */
     n = close(sockfd);		// ignore this one
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
     string this_error = "Could not find a working connection for host: ";
     this_error.append(hostname);
     this_error.append(" service: ");
     this_error.append(service);
     throw std::runtime_error::runtime_error(this_error);
   } /* end of if(results_index_p == 0) */
  freeaddrinfo(results_talk_p);
  return (sockfd);
}

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
	perror("setsockopt");
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
     perror("close");
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

/**
 * Package information to pass to listening thread
 */
struct listen_info
{
  /// The file  descriptor to lsiten on
  int listenfd;
  /// The length of the sockkaddr variable
  socklen_t addrlen;
};

void *
listen_on_socket(void * arg_p)
{
  QMS_Trace ("listen_on_socket", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: listen_on_socket\n");
  socklen_t len = 0;
  int connfd;
  int port;
  char address[128];

  struct listen_info *socket_info_p = (struct listen_info *)arg_p;
  struct sockaddr_in *cliaddr;
  cliaddr = ( struct sockaddr_in *) malloc(socket_info_p->addrlen);
  assert(cliaddr);
  
  for(; ;)
   {
     len = socket_info_p->addrlen;     
     address[0] = 0;
     port = 0;
     
     if((connfd = accept(socket_info_p->listenfd, 
			 (struct sockaddr *) cliaddr, &len)) < 0)
     {
       std::cerr << "Error on connection to " << socket_info_p->listenfd
		 << "Struct length " << len  <<" Ignoring. " << std::endl;
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

        string::size_type index = raw_data.find("\n");
        while(index != string::npos)
         {
           // we have at least one complete message in here
           message.assign(raw_data, 0, index);
           raw_data.erase(0, index + strlen("\n"));
           index = raw_data.find("\n");
	   std::cout << message << std::endl;
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
  return 0;
}

string request = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>                                 \n\
<!-- *****************************************************************     \n\
 *** Copyright (c) 2001, System/Technology Development Corporation .       \n\
 ***                						           \n\
 *** Filename:      BVdiscover.xml				           \n\
 *** Version:       1.0						           \n\
 *** Description:   BVT to BVGateway Discover request		           \n\
 ***                						           \n\
 *** Author:        Amarendranath Vadlamudi <nath@vedam>	           \n\
 *** Created at:    Sun Dec  9 17:48:18 2001			           \n\
 *** Modified by:   Amarendranath Vadlamudi <nath@vedam>	           \n\
 *** Modified at:   Sun Dec  9 23:36:53 2001			           \n\
 *** Status:        Experimental, do not distribute.		           \n\
 *** Update count:  24						           \n\
 ***************************************************************** -->     \n\
<discover xmlns=\"http://www.stdc.com/2001/QMS/Plugins/BVGateway\"         \n\
  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"	           \n\
  xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"		           \n\
  xsi:schemaLocation=						           \n\
  \"http://www.stdc.com/2001/QMS/Plugins/BVGateway BVGateway.xsd\">        \n\
  <request>							           \n\
    <BVTlistenAddress>						           \n\
      <host>127.0.0.1</host>				                   \n\
      <port>DELETEME            </port>          			   \n\
    </BVTlistenAddress>						           \n\
    <resource>							           \n\
      <QMSUniqueName>						           \n\
        <qms:category>QMS_CPU_Utilization</qms:category>		   \n\
      </QMSUniqueName>						           \n\
      <QMSUniqueName>						           \n\
        <qms:category>HelloWorldProbe</qms:category>		           \n\
      </QMSUniqueName>						           \n\
    </resource>							           \n\
  </request>   							           \n\
</discover>    							           \n\
";

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
  DEBUG0 (2, "DEBUG: GUI starting\n");

  DEBUG0 (4, "DEBUG: parsing arguments\n");
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
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        std::cout << argv[0] << ": Version "<< version << std::endl;
        exit (0);
      }

     DEBUG1 (6, "unknown argument %s", argv[i] );
   }

  char hostname[ MAXNAMELEN ];
  ACE_OS::hostname( hostname, MAXNAMELEN );
  DEBUG1(2,"Our Hostname is %s", hostname);


  socklen_t addrlen;
  socklen_t my_addrlen;
  int                    localport = 0;
  int 			 listenfd  = 0;
  int 			 sockfd    = 0;
  struct sockaddr_in 	*my_addr   = 0;

  try
   {
     listenfd = tcp_listen(NULL, "", &addrlen);
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
  char address[128];
  address[0] = 0;
     
  if(inet_ntop(AF_INET, &my_addr->sin_addr, address, sizeof(address)) == 0)
   {
     std::cerr << "Error determining address: Ignoring" << std::endl;
     perror("inet_ntop(");
   } /* end of if(inet_ntop(AF_INET, &cliaddr->sin_addr, address, 
	sizeof(address)) == 0) */
  DEBUG0 (4, "DEBUG: Trying to connect to port 8989\n");
  try 
   {
     sockfd = tcp_connect("127.0.0.1", "8989");
   }
  catch (... )
   {
     std::cerr << "Caught an exception"  << std::endl;
     exit (EXIT_FAILURE);
   }
  DEBUG0 (4, "DEBUG: Connected to port 8989\n");

  pthread_t  thread_id;
  struct listen_info information;
  information.listenfd = listenfd;
  information.addrlen = addrlen;

  
  if((n = pthread_create(&thread_id, 0, listen_on_socket, 
			 (void *) &information)) != 0)
   {
     std::cerr << "Error spawning read thread" << std::endl;
     exit (EXIT_FAILURE);
   } /* end of if((n = pthread_create(thread_id, 0, listen_on_socket, 
	(void *)&sockfd)) != 0) */
  
  char portstr[7];
  n = snprintf(portstr, 7, "%d", localport);
  if(n < 0 || n > 7)
   {
     std::cerr << "Error creating message" << std::endl;
   } /* end of if(n < 0 || n > 7) */
  
  unsigned int pos = request.find("DELETEME");
  if(pos != string::npos)
   {
     request.replace(pos, strlen("DELETEME"), portstr);
   } /* end of if(pos != string::npos) */

  request.append(STDC::QMS::Citizen::delimiter);
  
  ssize_t nleft;
  ssize_t nwritten;
  std::cerr << "DEBUG: sending message: " << std::endl
	    << request;
  
  nleft = strlen(request.c_str());
  n = nleft;
  char *ptr = const_cast< char * >(request.c_str());
  
  while(nleft > 0)
   {
     if((nwritten = write(sockfd, ptr, nleft)) <= 0)
      {
	if(errno == EINTR)
	 {
	   nwritten = 0;
	 } /* end of if(errno == EINTR) */
	else
	 {
	   std::cerr << "Error writing to pipe" << std::endl;
	   perror("write");
	   exit (EXIT_FAILURE);
	 } /* end of else */
      } /* end of if((nwritten = write(sockfd, ptr, nleft)) <= 0) */
     nleft -= nwritten;
     ptr += nwritten;
   } /* end of while(nleft > 0) */

  n = pthread_join(thread_id, 0);
  
  std::cout << "GUI Done" << std::endl;
  exit (EXIT_SUCCESS);
} /* end of main() */
