//                              -*- Mode: C++ -*- 
// Continuous_Pipe_Proxy_Remos.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Wed May  9 14:01:06 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu Dec  6 15:14:31 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 79
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// $Id: Continuous_Pipe_Proxy_Remos.cpp,v 1.34 2001/12/10 21:03:19 srivasta Exp $
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


/**
 * @file 
 * @ingroup RemosSensor
 * @brief Implementation of a proxy for a continuous, pipe based probe
 *
 */
#include <unistd.h>
#include "ace/Synch.h"

#include "Debug.h"
#include "Continuous_Pipe_Proxy_Remos.h"

/**
 * @brief The default constructor
 * @param file_name_p The full path name of the probe to be executed
 * @param argc Arguments to be fed to the child probe
 * @param envp Environment variables for the child probe
 * @param parent The metadata object for this probe abstracting the communications
 *
 * We initialize the parent Pipe_Proxy_Remos class object.  Unlike the
 * One_Shot_Pipe_Proxy_Remos we do not have to record the refresh rate and
 * iterations, since the probes we deal with are intelligent enough to
 * handle looping internally 
 */
STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::Continuous_Pipe_Proxy_Remos
(const char *file_name_p, char *const argv[], Meta_Data_Remos & parent, 
 string & key) : 
  Probe_Proxy_Remos(parent, key),
  Pipe_Proxy_Remos(file_name_p, argv, parent, key)
{
  QMS_Trace("STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::Continuous_Pipe_Proxy_Remos",
	    __LINE__, __FILE__);
  DEBUG0 (2,
     "DEBUG:STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::Continuous_Pipe_Proxy_Remos");
  // do nothing
}

/**
 * @brief Write a command on to the control pipes connected to the probe
 * @param data_p The command to be written on to the control pipe
 *
 * We write the command to the control pipe, handling partial writes
 * to the poipe as well.
 */
int 
STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::send_command(const string command)
{
  QMS_Trace("STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::send_command",
	    __LINE__, __FILE__);
  DEBUG0 (2,
	  "DEBUG:STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::send_command");
  // Assume locking already done
  ssize_t 	ret 	 = strlen(command.c_str());
  ssize_t 	nleft 	 = ret;
  ssize_t 	nwritten = 0;
  
  char *ptr = const_cast< char * >(command.c_str());
  
  while(nleft > 0)
   {
     if((nwritten = write(this->ctrlpipe[1], ptr, nleft)) <= 0)
      {
        if(errno == EINTR)
         {
           nwritten = 0;
         } /* end of if(errno == EINTR) */
        else
         {
           perror("Failed to send message");
           return -1;
         } /* end of else */
      } /* end of if((nwritten = write(sockfd, ptr, nleft)) <= 0) */
     nleft -= nwritten;
     ptr += nwritten;
   } /* end of while(nleft > 0) */
  return 0;
}


int 
internal_deploy(char * file_name_p_, int ctrlpipe[2], int datapipe[2], 
		char *argv_[], STDC::QMS::Citizen::Meta_Data_Remos & _metadata, 
		string _key)
{
  QMS_Trace("internal_deploy", __LINE__,__FILE__);
  DEBUG0 (2, "DEBUG: internal_deploy");

  DEBUG0 (4, "Continuous_Pipe_Proxy_Remos:: Forking a child");
  int childpid = fork();
  if(childpid < 0)
   {
     perror("Fork Failed");
     return childpid;
   } /* end of if(childpid < 0) */
  
  if(childpid == 0)
   {				// in the child

     DEBUG0 (4, "DEBUG:  Handling descriptors in the child");
     if (close(ctrlpipe[1]) != 0)
       perror ("close");
     if (close(datapipe[0]) != 0)
       perror ("close");
     
      DEBUG0 (2, "Continuous_Pipe_Proxy_Remos:: Handling stdin in the child");
     if (ctrlpipe[0] != STDIN_FILENO ) {
       if ( dup2 ( ctrlpipe[0], STDIN_FILENO ) != STDIN_FILENO ) {
	 fprintf(stderr, "Problem with STDIN dup2\n");
	 return (-1);
       }
       if (close ( ctrlpipe[0]) != 0)
	 perror("close");
     }	
     
      DEBUG0 (2, "Continuous_Pipe_Proxy_Remos:: Handling stdout in the child");
     if ( datapipe[1] != STDOUT_FILENO ) { 
       if ( dup2 ( datapipe[1], STDOUT_FILENO ) != STDOUT_FILENO ) {
	 // Problems
	 fprintf(stderr, "Problem with STDOUT dup2\n");
	 return (-1);
       }
       if (close ( datapipe[1]) != 0)
	 perror("close datapipe[0]");
     }
     
     DEBUG1 (2, "DEBUG: Continuous_Pipe_Proxy_Remos::deploy exec %s",
	     file_name_p_);
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
     DEBUG1 (8, "DEBUG: Failed execve %d", ret);
   } /* end of if(int childpid = fork()) */
  else
   {				// in the parent
     DEBUG0 (4, "DEBUG:  Handling descriptors in parent");
     if (close(ctrlpipe[0]) != 0)
       perror ("close");
     if (close(datapipe[1]) != 0)
       perror ("close");

     char buff[BUFSIZ];
     ssize_t length ;
     ssize_t n ;

     DEBUG0 (6, "DEBUG: In parent: writing start");

     strcpy (buff, "start\n");
     length = strlen(buff);

     ssize_t nleft    = length;
     ssize_t nwritten = 0;
     char *ptr = buff;
  
     while(nleft > 0)
      {
        if((nwritten = write(ctrlpipe[1], ptr, nleft)) <= 0)
         {
           if(errno == EINTR)
            {
              nwritten = 0;
            } /* end of if(errno == EINTR) */
           else
            {
              perror ("Error while writing start on to pipe");
            } /* end of else */
         } /* end of if((nwritten = write(sockfd, ptr, nleft)) <= 0) */
        nleft -= nwritten;
        ptr += nwritten;
      } /* end of while(nleft > 0) */

     string message;
     string raw_data;
     bool done = false;
     
     DEBUG0 (4, "DEBUG: In parent: reading");
     while(!done)
      {
	n = read(datapipe[0], buff, BUFSIZ);
	if(n < 0)
	 {
	   if(errno == EINTR)
	    {
	      continue;
	    } /* end of if(errno == EINTR) */
	   else
	    {
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

	string::size_type index = 
	  raw_data.find(STDC::QMS::Citizen::delimiter);
	while(index != string::npos)
	 {
	   // we have at least one complete message in here
	   message.assign(raw_data, 0, index);
	   raw_data.erase(0, index + strlen(STDC::QMS::Citizen::delimiter));
	   index = raw_data.find(STDC::QMS::Citizen::delimiter);
	   _metadata.handle_data(_key, message.c_str());
	 } /* end of while(message.find(delimiter) != string::npos) */
      } /* end of while((n = read(datapipe[0], buff, BUFSIZ) ) > 0)*/
     if(n == -1)
      {
	perror("read from child\n");
      } /* end of if(n == -1) */

     DEBUG0 (6, "DEBUG: In parent: finished reading");

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
     DEBUG0 (4, "DEBUG: Parent closing file descriptors");
     if (close(ctrlpipe[1]) != 0)
       perror ("close");
     if (close(datapipe[0]) != 0)
       perror ("close");	
     
   } /* end of else */
  return (0);
}



/**
 * @brief Deploy the probe
 * @return -1 on error
 *
 * This is where all the work is done. Different from the one shot
 * proxy, since we do not have to explicitly enter into a loop for
 * repeated data (the probe handles it all internally). We do all the
 * tasks that the one shot probe does per loop:  we create two pipes, 
 * one for control, and another for data. Closing the appropriate ends
 * of the pipes, we fork off the child probe, and, in the parent, read
 * data from the pipe, and send it off through the event channel 
 * adapter. Finally, we wait for the child probe to finish, clean up
 * the pipes, sleep for the refresh rate period, and we are done.
 */
int 
STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::deploy(void)
{
  QMS_Trace("STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::deploy", __LINE__,
	    __FILE__);
  DEBUG0 (2, 
	  "DEBUG:STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::deploy");
  if(!this->file_name_p_)
   {
     std::cerr << "Error: Failed to feploy probe: missing path" << std::endl;
     return -1;
   } /* end of if(!this->file_name_p_) */
  

  DEBUG0 (4, "Continuous_Pipe_Proxy_Remos:: Creating the Pipes");
  {
    ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
#if defined(_WIN32)
    if ( _pipe( this->datapipe, BUFSIZ+8192, O_BINARY | O_NOINHERIT ) < 0)
     {
       perror ("Error while creating the datapipe");
       return -1;
     }
    
    if ( _pipe( this->ctrlpipe, BUFSIZ+8192, O_BINARY | O_NOINHERIT ) < 0 )
     {
       perror ("Error while creating the ctrlpipe");
       return -1;
     }
#else    
    if(pipe(this->ctrlpipe) < 0)
     {
       perror("Error while creating the ctrlpipe");
       return -1;
     } /* end of if(pipe(this->ctrlpipe)) */
    if(pipe(this->datapipe) < 0)
     {
       perror("Error while creating the datapipe");
       return -1;
     } /* end of if(pipe(this->datapipe) < 0) */
#endif
    this->Am_I_Active = true;       
  }
  int ret = 0;
  
  try
   {
     ret = internal_deploy(this->file_name_p_, this->ctrlpipe, 
			   this->datapipe, this->argv_, this->_metadata, 
			   this->_key);
     
     {
       ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
       this->Am_I_Active = false;
       return (ret);
     }
   }
  catch (...)
   {
     std::cerr << "caught an exception while deploying"
	       << std::endl;
     return -1;
   }
  return ret;
}



/**
 * @brief A start method
 * @return -1 on error
 *
 * If the probe has been deployed, instruct it to start pumping data.
 */
int 
STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::start(void)
{
  QMS_Trace("STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::start", __LINE__,
            __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::start");
  ACE_Read_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
  if(this->Am_I_Active)
   {
     // Already started
     return -1;
   } /* end of if(this->Am_I_Active) */
  return this->send_command("start\n");
}
/**
 * @brief A pause method
 * @return -1 on error
 *
 * If the probe is active, send it a pause request
 */
int 
STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::pause(void)
{
  QMS_Trace("STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::pause", __LINE__,
            __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::pause");
  ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
  if(this->Am_I_Active == true)
   {
     this->status_ = INACTIVE;
     return this->send_command("pause\n");
   } /* end of if(this->Am_I_Active == true) */
  return -1;
}

/**
 * @brief A resume method
 * @return -1 on error
 *
 * If the probe is inactive, send it a resume request. Note: this even
 * works if the probe had been ``killed''
 */
int 
STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::resume(void)
{
  QMS_Trace("STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::resume", __LINE__,
            __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::resume");
  ACE_Read_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
  if(this->Am_I_Active)
   {
     // Already started
     return -1;
   } /* end of if(this->Am_I_Active) */
  this->status_ = ACTIVE;
  return this->send_command("resume\n");
}

/**
 * @brief A virtual kill method
 * @return -1 on error
 *
 * If the probe status is not killed, we set the status to killed, and
 * send the request to the probe
 */
int 
STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::kill(void)
{
  QMS_Trace("STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::kill", __LINE__,
            __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::kill");
  ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
  if(!this->status_ != KILLED)
   {
     this->status_ = KILLED;
     return this->send_command("stop\n");
   } /* end of if(this->Am_I_Active) */
}
/**
 * @brief destroy this object
 */
void
STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::destroy(void)
{
  QMS_Trace("STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::destroy", __LINE__,
            __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos::destroy");
  this->~Continuous_Pipe_Proxy_Remos();
}

