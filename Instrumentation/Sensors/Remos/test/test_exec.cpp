//                              -*- Mode: C++ -*- 
// test_exec.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Mon Nov 26 16:08:15 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Nov 27 14:56:30 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 20
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

/** @file 
 *  @ingroup RemosSensor 
 *  @brief implementation of the client program
 *
 * $Id: test_exec.cpp,v 1.7 2001/12/09 02:14:18 nath Exp $
 */
/// RCS version string
static const char* version = 
"$Id: test_exec.cpp,v 1.7 2001/12/09 02:14:18 nath Exp $";



#include "Debug.h"

bool Am_I_Active = false;
/// The control pipe
int ctrlpipe[2];
/// The data pipe
int datapipe[2];
/// The file name of the probe to call
char * file_name_p_ = const_cast< char *>("./Generic_Continuous_Probe");

char * argv_[] = 
  { const_cast< char *>("Generic_Continuous_Probe"), 
    const_cast< char *>("-r"), 
    const_cast< char *>("5"),
    const_cast< char *>("-i"), 
    const_cast< char *>("0.1"),
    0 };
static const char *
      delimiter =  "<!-- ******_PROBE_MESSAGE_DELIMITER_****** -->";


int 
deploy(void)
{

  QMS_Trace("STDC::QMS::Citizen::Continuous_Pipe_Proxy::deploy", __LINE__,
            __FILE__);
  DEBUG0 (2, 
          "DEBUG:STDC::QMS::Citizen::Continuous_Pipe_Proxy::deploy");
  if(!file_name_p_)
   {
     std::cerr << "Error: Failed to feploy probe: missing path" << std::endl;
     return -1;
   } /* end of if(!this->file_name_p_) */
  

  DEBUG0 (2, "Creating the Pipes");

  if(pipe(ctrlpipe) < 0)
   {
     perror("ctrlpipe");
     return -1;
   } /* end of if(pipe(this->ctrlpipe)) */
  if(pipe(datapipe) < 0)
   {
     perror("datapipe");
     return -1;
   } /* end of if(pipe(this->datapipe) < 0) */
  Am_I_Active = true;       

  DEBUG0 (2, "Forking a child");
  int childpid = fork();
  if(childpid == 0)
   {                            // in the child
     DEBUG0 (2, "DEBUG:  Handling descriptors in the child");
     if (close(ctrlpipe[1]) != 0)
       perror ("close");
     if (close(datapipe[0]) != 0)
       perror ("close");
     
     DEBUG0 (2, "Continuous_Pipe_Proxy:: Handling stdin in the child");
     if (ctrlpipe[0] != STDIN_FILENO ) {
       if ( dup2 ( ctrlpipe[0], STDIN_FILENO ) != STDIN_FILENO ) {
         fprintf(stderr, "Problem with STDIN dup2\n");
         return (-1);
       }
       if (close ( ctrlpipe[0]) != 0)
         perror("close");
     }  
     
     DEBUG0 (2, "Handling stdout in the child");
     if ( datapipe[1] != STDOUT_FILENO ) { 
       if ( dup2 ( datapipe[1], STDOUT_FILENO ) != STDOUT_FILENO ) {
         // Problems
         fprintf(stderr, "Problem with STDOUT dup2\n");
         return (-1);
       }
       if (close ( datapipe[1]) != 0)
         perror("close datapipe[0]");
     }
     
     DEBUG1 (2, "DEBUG: deploy exec %s", file_name_p_);
     // DEBUG!!!
     if(!argv_)
      {
        fprintf(stderr, "No arguments!!!\n");
        return (-1);
      } /* end of if(!this->argv_) */
     else
      {
        int i = 0;
        std::cerr << "DEBUG: Command line arguments: ";
        while(argv_[i])
         {
           std::cerr << argv_[i++] << " ";
         } /* end of while(this->argv_[i]) */
        std::cerr << std::endl;
      } /* end of else */
     int ret = execvp(file_name_p_, argv_);
     perror("Failed execve");
     DEBUG1 (2, "DEBUG: Failed execve %d", ret);
   } /* end of if(int childpid = fork()) */
  else
   {                            // in the parent
     DEBUG0 (2, "DEBUG:  Handling descriptors in parent");
     if (close(ctrlpipe[0]) != 0)
       perror ("close");
     if (close(datapipe[1]) != 0)
       perror ("close");
     char buff[BUFSIZ];
     ssize_t n ;

     DEBUG0 (2, "DEBUG: In parent: writing start");

     strcpy (buff, "start\n");
     n = strlen(buff);
     if ( (n = write (ctrlpipe[1], buff, BUFSIZ)) < 0 )
          perror ("write");

     //int ret = start();
     string message;
     string raw_data;
     
     DEBUG0 (2, "DEBUG: In parent: reading");
     while((n = read(datapipe[0], buff, BUFSIZ) ) > 0)
      {
        buff[n] = 0;
        DEBUG2 (2, "DEBUG: Read %d bytes --> \n%s", n, buff);
	raw_data.append(buff);

	string::size_type index = raw_data.find(delimiter);
	while(index != string::npos)
	 {
	   // we have at least one complete message in here
	   message.assign(raw_data, 0, index);
	   raw_data.erase(0, index + strlen(delimiter));
	   index = raw_data.find(delimiter);
	   std::cout << "XML Message(" << message << ")" << std::endl;
	 } /* end of while(message.find(delimiter) != string::npos) */
      } /* end of while((n = read(datapipe[0], buff, BUFSIZ) ) > 0)*/
     if(n == -1)
      {
        perror("read from child\n");
      } /* end of if(n == -1) */
     DEBUG0 (2, "DEBUG: In parent: finished reading");

     int status = 0;
     pid_t pid_ret;
     while((pid_ret = waitpid(childpid, &status, 0) )  != childpid)
      {
        DEBUG1(4, "DEBUG: Exited Childpid ->%d", pid_ret);
      } /* end of while(pid_ret = waitpid(childpid, &status, 0)) */
     if(WIFEXITED(status))
      {
        DEBUG0(4, "DEBUG: Child Exited Normally");
      } /* end of if(WIFEXITED(status)) */
     else
      {
        DEBUG1(6, "DEBUG: Child Exited Abnormally with status %d",
	       WEXITSTATUS(status));
	if(WIFSIGNALED(status))
	 {
	   DEBUG1(6, "DEBUG: Child got signal %d",
		  WTERMSIG(status));
	 } /* end of if(WIFSIGNALED(status)) */	
      } /* end of else if(WIFEXITED(status)) */
     DEBUG0 (2, "DEBUG: Parent closing file descriptors");
     if (close(ctrlpipe[1]) != 0)
       perror ("close");
     if (close(datapipe[0]) != 0)
       perror ("close");
   } /* end of else */
  Am_I_Active = false;
  return (0);
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
main (void)
{
  QMS_Trace ("main", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: starting\n");
  DEBUG0 (2, "Creating the Pipes");
  std::cout << "Test program version " << version << " started" << std::endl;
  int ret = deploy();
  exit (ret);
}
