//                              -*- Mode: C++ -*- 
// One_Shot_Pipe_Proxy.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Wed May  9 14:01:06 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu Nov 29 14:19:57 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 72
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// $Id: One_Shot_Pipe_Proxy.cpp,v 1.11 2001/12/09 02:11:58 nath Exp $
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
 * @ingroup GenericSensor
 * @brief Implementation of a one-shot pipe proxy
 *
 */

#if !defined(_WIN32)
#include <unistd.h>
#endif

#include "Debug.h"
#include "One_Shot_Pipe_Proxy.h"

/// The default refresh rate
#define DEFAULT_SLEEP 2

/**
 * @brief The default constructor
 * @param file_name_p The full path name of the probe to be executed
 * @param argc Arguments to be fed to the child probe
 * @param envp Environment variables for the child probe
 * @param parent The metadata object for this probe abstracting the communications
 * @param refresh_rate The rate at which data is requested
 * @param iterations The number of iterations of the probe data required
 *
 * We initialize the parent Pipe_Proxy class object, as well as the
 * internal variables refresh_rate_ and iterations_
 */
STDC::QMS::Citizen::One_Shot_Pipe_Proxy::One_Shot_Pipe_Proxy
(const char *file_name_p, char *const argv[], Meta_Data &parent,
 string & key, double refresh_rate, int iterations):
  Probe_Proxy(parent, key), 
  Pipe_Proxy(file_name_p, argv, parent, key), 
  refresh_rate_(refresh_rate), iterations_(iterations)
{
  QMS_Trace("STDC::QMS::Citizen::One_Shot_Pipe_Proxy::One_Shot_Pipe_Proxy", 
	    __LINE__, __FILE__);
  DEBUG0 (2,
	 "DEBUG:STDC::QMS::Citizen::One_Shot_Pipe_Proxy::One_Shot_Pipe_Proxy");
  // do nothing
}

/**
 * @brief A virtual send command
 * @return -1 on error
 *
 * If we have not already been started, this is where we set the
 * internal status to active, and call on the deploy method to deploy
 * the probe 
 */
int 
STDC::QMS::Citizen::One_Shot_Pipe_Proxy::send_command(const string command)
{
  QMS_Trace("STDC::QMS::Citizen::One_Shot_Pipe_Proxy::send_command", __LINE__,
	    __FILE__);
  DEBUG0 (2,
	  "DEBUG:STDC::QMS::Citizen::One_Shot_Pipe_Proxy::send_command");
  if(command.compare("pause") == 0)
   {
     return this->pause();
   } /* end of if(command.compare("pause") == 0) */

  if(command.compare("resume") == 0)
   {
     return this->resume();
   } /* end of if(command.compare("resume") == 0) */

  if(command.compare("stop") == 0)
   {
     return this->kill();
   } /* end of if(command.compare("stop") == 0) */
	
  if(command.compare("star") == 0)
   {
     return this->start();
   } /* end of if(command.compare("stop") == 0) */
	
  
}

/**
 * @brief A virtual start method
 * @return -1 on error
 *
 * If we have not already been started, this is where we set the
 * internal status to active, and call on the deploy method to deploy
 * the probe 
 */
int 
STDC::QMS::Citizen::One_Shot_Pipe_Proxy::start(void)
{
  QMS_Trace("STDC::QMS::Citizen::One_Shot_Pipe_Proxy::start", __LINE__,
            __FILE__);
  DEBUG0 (2,
          "DEBUG:STDC::QMS::Citizen::One_Shot_Pipe_Proxy::start");
  {
    ACE_Read_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
    if(this->Am_I_Active)
     {
       // Already started
       return -1;
     } /* end of if(this->Am_I_Active) */
    this->status_ = ACTIVE;
  }
  return this->deploy();
}


/**
 * @brief A virtual Pause method
 * @return -1 on error
 *
 * Set the internal status to inactive
 *
 */
int
STDC::QMS::Citizen::One_Shot_Pipe_Proxy::pause(void)
{
  QMS_Trace("STDC::QMS::Citizen::One_Shot_Pipe_Proxy::pause", __LINE__,
	    __FILE__);
  DEBUG0 (2, 
	  "DEBUG:STDC::QMS::Citizen::One_Shot_Pipe_Proxy::pause");
  ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
  this->status_ = INACTIVE;
  return 0;
}

/**
 * @brief A virtual Resume method
 * @return -1 on error
 *
 * Identical to the start method
 *
 * If we have not already been started, this is where we set the
 * internal status to active, and call on the deploy method to deploy
 * the probe 
 *
 */
int 
STDC::QMS::Citizen::One_Shot_Pipe_Proxy::resume(void)
{
  QMS_Trace("STDC::QMS::Citizen::One_Shot_Pipe_Proxy::resume", __LINE__, 
	    __FILE__);
  DEBUG0 (2,
	  "DEBUG:STDC::QMS::Citizen::One_Shot_Pipe_Proxy::resume");
  {
    ACE_Read_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
    if(this->Am_I_Active)
     {
       // Already started
       return -1;
     } /* end of if(this->Am_I_Active) */
    this->status_ = ACTIVE;
  }
  return this->deploy();
}

/**
 * @brief A virtual Kill method
 * @return -1 on error
 *
 * Set the internal status to killed
 *
 */
int
STDC::QMS::Citizen::One_Shot_Pipe_Proxy::kill(void)
{
  QMS_Trace("STDC::QMS::Citizen::One_Shot_Pipe_Proxy::kill", __LINE__,
	    __FILE__);
  DEBUG0 (2, 
	  "DEBUG:STDC::QMS::Citizen::One_Shot_Pipe_Proxy::kill");
  ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
  this->status_ = KILLED;
  return 0;
}

/**
 * @brief Destroy this object
 *
 */
void
STDC::QMS::Citizen::One_Shot_Pipe_Proxy::destroy(void)
{
  QMS_Trace("STDC::QMS::Citizen::One_Shot_Pipe_Proxy::destroy", __LINE__,
	    __FILE__);
  DEBUG0 (2, 
	  "DEBUG:STDC::QMS::Citizen::One_Shot_Pipe_Proxy::destroy");

  this->~One_Shot_Pipe_Proxy();
}

/**
 * @brief Deploy the probe
 *
 * This is where all the work is done. After performing some sanity
 * checking, we go into a loop for the desired number of
 * iterations. For each iteration, we create two pipes, one for
 * control, and another for data. Closing the appropriate ends of the
 * pipes, we fork off the child probe, and, in the parent, read data
 * from the pipe, and send it off through the event channel
 * adapter. Finally, we wait for the child probe to finish, clean up
 * the pipes, sleep for the refresh rate period, and we are off to the
 * next iteration.
 *
 * At the top of the loop, we check to see if we have been paused or
 * killed. If we have been paused or killed, we exit the loop and
 * allow the appropriate actions to be taken.
 */
int 
STDC::QMS::Citizen::One_Shot_Pipe_Proxy::deploy(void)
{
  QMS_Trace("STDC::QMS::Citizen::One_Shot_Pipe_Proxy::deploy", __LINE__, 
	    __FILE__); 
  DEBUG0 (2,
	  "DEBUG:STDC::QMS::Citizen::One_Shot_Pipe_Proxy::deploy");
 
  #if !defined(_WIN32)
  if(!this->file_name_p_)
   {
     std::cerr << "Error: Failed to deploy probe: missing path" << std::endl;
     return -1; 
   } /* end of if(!this->file_name_p_) */
  

  for(int i =0; i < this->iterations_; i++)
   {
     {
       ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
       if(this->status_ != ACTIVE)
	{
	  break;
	} /* end of if(this->status_ != ACTIVE) */ 
       if(pipe(this->ctrlpipe) < 0)
	{
	  perror("ctrlpipe");
	  return -1;
	} /* end of if(pipe(this->ctrlpipe)) */
       if(pipe(this->datapipe) < 0)
	{
	  perror("datapipe");
	  return -1;
	} /* end of if(pipe(this->datapipe) < 0) */
       
       this->Am_I_Active = true;
     }
     int childpid = fork();
     if(!childpid)
      {				// in the child
	if (close(this->ctrlpipe[1]) != 0)
	  perror ("close");
	if (close(this->datapipe[0]) != 0)
	  perror ("close");
	
	if (ctrlpipe[0] != STDIN_FILENO ) {
	  if ( dup2 ( ctrlpipe[0], STDIN_FILENO ) != STDIN_FILENO ) {
	    fprintf(stderr, "Problem with STDIN dup2\n");
	    return (-1);
	  }
	  if (close ( ctrlpipe[0]) != 0)
	    perror("close");
	}	
	
	if ( datapipe[1] != STDOUT_FILENO ) { 
	  if ( dup2 ( datapipe[1], STDOUT_FILENO ) != STDOUT_FILENO ) {
	    // Problems
	    fprintf(stderr, "Problem with STDOUT dup2\n");
	    return (-1);
	  }
	  if (close ( datapipe[1]) != 0)
	    perror("close datapipe[0]");
	}
	
	DEBUG0 (4, 
		"DEBUG:STDC::QMS::Citizen::One_Shot_Pipe_Proxy::deploy exec");
	execvp(this->file_name_p_, this->argv_);
	perror("Failed execve");
      } /* end of if(int childpid = fork()) */
     else
      {				// in the parent
	if (close(this->ctrlpipe[0]) != 0)
	  perror ("close");
	if (close(this->datapipe[1]) != 0)
	  perror ("close");
	char buff[BUFSIZ + 8192 ];
	ssize_t n ;
	while((n = read(datapipe[0], buff, BUFSIZ + 8192 ) ) > 0)
	 {
	   buff[n] = 0;
	   this->_metadata.handle_data(this->_key, buff);
	 } /* end of while((n = read(datapipe[0], buff, BUFSIZ + 8192 ) ) > 0)*/
	if(n == -1)
	 {
	   perror("read from child\n");
	 } /* end of if(n == -1) */
	int status = 0;
	pid_t pid_ret;
	while((pid_ret = waitpid(childpid, &status, 0) )  != childpid)
	 {
	   DEBUG1(4, "Exited Childpid ->%d", pid_ret);
	 } /* end of while(pid_ret = waitpid(childpid, &status, 0)) */
	if(WIFEXITED(status))
	 {
	   DEBUG0(4, "Child Exited Normally");
	 } /* end of if(WIFEXITED(status)) */
	else
	 {
	   DEBUG0(6, "Child Exited Abnormally");
	 } /* end of else if(WIFEXITED(status)) */
	
	if (close(this->ctrlpipe[1]) != 0)
	  perror ("close");
	if (close(this->datapipe[0]) != 0)
	  perror ("close");	

	ACE_Time_Value sleep_time(this->refresh_rate_, 0);
	ACE_OS::sleep (sleep_time);
      } /* end of else (int childpid = fork())*/
   } /* end of for(int i =0; i < this->interations_; i++) */
  {
    ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
    this->Am_I_Active = false;
    return (0);
  }
  #else
  
  return (0);

  #endif

}

