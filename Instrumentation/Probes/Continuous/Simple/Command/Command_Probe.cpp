//                              -*- Mode: C++ -*- 
// Command_Probe.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
// Created On       : Tue Jan 15 09:02:22 2002
// Created On Node  : glaurung.green-gryphon.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Jan 23 16:42:06 2002
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 61
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// 
// 

/*
 * Copyright (C) 2002 System/Technology Development Corporation
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
 *  @ingroup    CommandProbe
 *  @brief Contains implementation of a general purpose command probe
 *
 */

/// RCS version
static const char* version = 
"$Id: Command_Probe.cpp,v 1.28 2002/01/25 17:07:35 srivasta Exp $";

#include <fstream>
#include <iostream>
#include <strstream>
#include <sstream>
#include <cstdlib>

#include <cstring>
#include <ctype.h>
#include <cstdio>

#include <string>
using std::string;
using std::cout;

#include <exception>
#include <stdexcept>


#include "ace/OS.h"
#include "ace/Thread_Manager.h"
#include "Debug.h"
#include <signal.h>
#include "Instrumentation.h"
#include "Parse_Duration.cpp"

#if defined(_WIN32)
static HANDLE hProcess;
int hStdOut;
#define INACTIVE 100

#else
pid_t child_pid = 0;
#endif
bool worker_started = false;
ACE_thread_t worker_id;
ACE_hthread_t worker_handle;
static unsigned long dataid=0;

int cmd_pipe[2];

/// mutex to guard internal variables
ACE_Thread_Mutex asset_guard;

void
modify_data (string &src, const char *pattern, const char *replace)
{
  string::size_type x = src.find(pattern);
  while ( x < string::npos )
   {
     src.replace(x,1,replace);
     x = src.find(pattern, x + strlen(replace) + 1);
   }
}


void
write_data(string in_data)
{
  QMS_Trace ("write_data", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: Writing data\n");
  string data = in_data;
  
  modify_data(data, "&", "&amp;");
  modify_data(data, "<", "&lt;");
  modify_data(data, ">", "&gt;");
  std::ostringstream out_ack;
  out_ack << std::endl << "<commandProbe" << std::endl 
	  << "    xmlns=\"http://www.stdc.com/2001/QMS/Probes/Continuous/CommandProbe\"" 
	  << std::endl 
	  << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" 
	  << std::endl 
	  << "    xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/Continuous/CommandProbe" 
	  << std::endl 
	  << "    commandProbe.xsd\">"        << std::endl 
	  << "      <probeData>"              << std::endl 
	  << "         <dataid>" << ++dataid  << "</dataid>" << std::endl 
	  << "         <response>"            << std::endl 
	  << "            <textData>"         << std::endl 
	  << "               <message>"       << std::endl 
	  << data                             << std::endl 
	  << "               </message>"      << std::endl 
	  << "            </textData>"        << std::endl 
	  << "        </response>"            << std::endl 
	  << "      </probeData>"             << std::endl 
	  << "</commandProbe>"                << std::endl 
	  << STDC::QMS::Citizen::delimiter    << std::endl 
    ;
     
  char * cmd_data = strdup(const_cast<char *>(out_ack.str().c_str()));
  int ret = strlen (cmd_data);
  int nleft = ret;
  int error_count = 0;
  int nwritten = 0;
     
  while(nleft > 0)
   {
     if((nwritten = ACE_OS::write(ACE_STDOUT, cmd_data, nleft)) <= 0)
      {
	if(errno == EINTR) { nwritten = 0; } 
	else               
	 {
	   ACE_OS::perror("Probe: Error in writing cmd_data");
	   if ( error_count++ > 5 )
	    {
	      ACE_OS::fprintf(stderr, "Aborting from Probe\n");
	      exit(2);
	    }
	 } // end of else .
      } // end of if((nwritten ...)
     nleft -= nwritten;
     cmd_data += nwritten;
   } // end of while(nleft > 0)
#ifndef _WIN32
  if(cmd_data)
   {
     //free(cmd_data);
     cmd_data = 0;
   } /* end of if(cmd_data) */
#endif
}


/**
 *  @brief  This is where the work of the probe is done
 *  @param  args_p List of command line arguments.
 *  @return None
 *
 */
void
worker(void *args_p)
{
  QMS_Trace ("worker", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: worker thread starting\n");
  char ** argv_ = (char **) args_p;
  
#if defined(_WIN32)
  // Create the pipe
  if(_pipe(cmd_pipe, BUFSIZ + 8192, O_BINARY | O_NOINHERIT) == -1)
   {
     perror ("_pipe");
     exit (3);
   }
#else
  if(pipe(cmd_pipe) < 0)
   {
     perror("Error while creating the ctrlpipe");
     return;
   } /* end of if(pipe(this->ctrlpipe)) */
  
#endif
  
#if defined(_WIN32)
  // Duplicate stdout handle (next line will close original)
  hStdOut = _dup(_fileno(stdout));
  // Duplicate write end of pipe to stdout handle
      DEBUG0 (4, "DEBUG:  Setting STDOUT for everyone to write end of control pipe\n");
  if(_dup2(cmd_pipe[1], _fileno(stdout)) != 0)
   {
     perror ("_dup2");
     exit (3);
   }
  
  // Close original write end of pipe
  close(cmd_pipe[1]);
#else
  child_pid = fork();
  if(child_pid < 0)
   {
     perror("Fork Failed");
     return;
   } /* end of if(child_pid < 0) */
  if(child_pid == 0)
   {				// in the child
     DEBUG1 (4, "DEBUG:  Handling pipe in the child(close cmd_pipe[0]=%d)\n",
	     cmd_pipe[0]);
     if (close(cmd_pipe[0]) != 0)
      {
	perror ("close");
	exit (EXIT_FAILURE);
      }
     
     DEBUG0 (2, "DEBUG:  Handling stdout in the child");
     if (cmd_pipe[1] != STDOUT_FILENO ) 
      {
	DEBUG1 (2, "DEBUG:  Duplicating stdout in child cmd_pipe[1]=%d",
		cmd_pipe[1]);
	if ( dup2 ( cmd_pipe[1], STDOUT_FILENO ) != STDOUT_FILENO ) 
	 {
	   fprintf(stderr, "Problem with STDOUT dup2\n");
	   return;
	 }
      }	
#endif //  _WIN32
     
     
     DEBUG1 (2, "DEBUG: deploy exec %s", argv_[0]);
     // DEBUG!!!
     if(!argv_)
      {
	fprintf(stderr, "No arguments!!!\n");
	return;
      } /* end of if(!this->argv_) */
#ifndef SILENT_MODE
     else
      {
	int i = 0;
	std::cerr << "\tCommand: '";
	while(argv_[i])
	 {
	   std::cerr << "\"" << argv_[i++] << "\" ";
	 } /* end of while(this->argv_[i]) */
	std::cerr << "'" << std::endl;
      } /* end of else */
#endif //  SILENT_MODE
     
     
     // Shift the command line arguments down
     int j = 0, i = 0;
     while ( argv_[++i] != 0)
      {
	argv_[j++] = argv_[i];
      }
     argv_[j] = NULL;
     char *filename_p = argv_[0];
     
     
#if defined(_WIN32)
     // Spawn process
     hProcess = (HANDLE)spawnvp(P_NOWAIT, filename_p, argv_);
     
     // Duplicate copy of original stdout back into stdout
    DEBUG0 (4, "DEBUG:  Handling pipe in the parent, restoring STDOUT\n");
     if(_dup2(hStdOut, _fileno(stdout)) != 0)
      {
	perror ("_dup2");
	exit (3);
      }
     
     // Close duplicate copy of original stdout
	 DEBUG0 (4, "DEBUG:  Closing local copy of stdout\n");
     close(hStdOut);
#else //  !_WIN32
     DEBUG1(2, "Going to exec %s\n", filename_p);
     int ret = execvp(filename_p, argv_);
     perror("Failed execve");
     DEBUG1 (8, "DEBUG: Failed execve %d", ret);
   } /* end of if(int child_pid = fork()) */
  else
   {				// in the parent
     DEBUG1 (4, "DEBUG:  Handling pipe in the parent(close cmd_pipe[1]=%d)\n",
	     cmd_pipe[1]);
     if (close(cmd_pipe[1]) != 0)
      {
	perror ("close");
	exit (EXIT_FAILURE);
      }
#endif //  _WIN32

     string data;
     data.assign( "\t\t\tReceived request to execute command -> ");;
     for ( int k = 0; argv_[k] != NULL ; k++ )
      {
	data.append(argv_[k]);
	data.append(" ");
      }
     write_data(data);
     // Done sending the Ack.


     DEBUG1 (4, "DEBUG:  Reading in the parent(cmd_pipe[0]=%d)\n",
	     cmd_pipe[0]);

     char probe_data[BUFSIZ + 8192];
     string modified;
     modified.erase();
     bool done = false;
     bool seen_data = false;
     int err_count = 0;
     
     while (!done)
      {
	DEBUG0(2,"Reading from pipe");
	int n = read (cmd_pipe[0], probe_data, BUFSIZ + 8192 );
	if(n < 0)
	 {
	   if(errno == EINTR) { continue; } 
	   else               { 
	     DEBUG1 (4, "DEBUG: Done: n = %d\n", n);
	     perror("Error reading from child");
	     done = true; 
	     if(!modified.empty())
	      {
		write_data(modified);
	      } /* end of if(!modified.empty()) */
	     break;
	   }
	 } // end of if(n < 0)
	
	if(n == 0 && seen_data) 
	 { 
	   DEBUG0(4, "DEBUG: Done:0 Bytes read  and we have seen some data\n");
	   if(!modified.empty())
	    {
	      write_data(modified);
	    } /* end of if(!modified.empty()) */
	   break; 
	 }
	if(n == 0) 
	 {
#if defined(_WIN32)
	   Sleep(1000);
#else
	   sleep(1);
#endif
	   if(++err_count > 5)
	    {
	      string tmp_data = "";
	      write_data(tmp_data);
	      break;
	    } /* end of if(++err_count > 5) */
	   else
	    {
	      continue;
	    } /* end of else */
	 }
	seen_data = true;
	probe_data[n] = 0;
	DEBUG1 (2, "Read %d bytes --> \n", n);
	DEBUG1 (2, "Worker Read the cmd_data ->%s\n", probe_data);
	modified.append(probe_data);
      } // end of while (!done)
#ifndef _WIN32
   }
#endif
  DEBUG0 (2, "PROBE Worker: Leaving the Worker method\n"); 
  DEBUG0(2, "PROBE Worker: Exiting from the Probe\n");
  
  exit(0);
}

/**
 * @brief This function handles the commands received
 * @param command The command received
 * @param args_p The command line arguments for the probe
 */
int
handle_command(string command, void * args_p)
{
  QMS_Trace ("handle_command", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG: Handling a command\n");
  ACE_Write_Guard<ACE_Thread_Mutex> guard(asset_guard);

  int ret = 0;
  
  if((command.find("start\n") != string::npos) ||
     (command.find("start\r\n") != string::npos))
   {
     DEBUG0 (2, "PROBE Listener: Starting the Worker thread\n");
     ret = ACE_Thread::spawn((ACE_THR_FUNC)worker,
			     args_p,  // arg
			     THR_JOINABLE, // flags
			     &worker_id,  // t_id
			     &worker_handle,  // t_handle
			     ACE_DEFAULT_THREAD_PRIORITY,
			     0,  // stack
			     0,  // stack_size
			     0   // thread_adapter
			     );
     if(ret == -1)
      {    
	ACE_OS::perror ("Worker Thread Creation failed\n");
	DEBUG0 (2, "PROBE Listener: Error creating the Worker thread\n"); 
	exit(1);
      } // end of if(ret == -1)
     return ret;
   } /* end of if(command.find("start\n") != string::npos) */


  if((command.find("stop\n") != string::npos) ||
     (command.find("stop\r\n") != string::npos))
   {
     DEBUG0 (2, "PROBE Listener: The Probe has been Stopped\n");

#if defined(WIN32)
     if (!TerminateProcess(hProcess, INACTIVE))
      {
	perror ("TerminateProcess");
	exit(1);
      }
#else
     	DEBUG1 (2, "DEBUG: child pid is %d\n", child_pid);
     if(child_pid)
      {
	DEBUG1 (2, "DEBUG: Sending signal 15 to the child %d\n",
		child_pid);
	ret = kill(child_pid, 15);
	if(ret < 0)
	 {
	   if(errno != ESRCH)
	    {
	      DEBUG1 (2, "DEBUG: Sending signal 9 to the child %d\n",
		      child_pid);
	      ret = kill(child_pid, 9);
	    } /* end of if(errno != ESRCH) */
	 } /* end of if(ret < 0) */
	child_pid = 0;
	int timeleft = 2;
	while(timeleft)
	 {
	   timeleft = ACE_OS::sleep(timeleft);
	 } /* end of while(timeleft) */
      } /* end of if(child_pid) */
#endif
     
     DEBUG0(2, "PROBE Listener: Exiting from the Probe\n");
     exit(EXIT_SUCCESS);
   } /* end of if((command.find("start\n") != string::npos) ||
	(command.find("start\r\n") != string::npos)) */
  
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
  DEBUG0 (2, "DEBUG: starting\n");

  bool done = false;
  char buffer[BUFSIZ];
  int n = 0;
  string raw_data;
  string command;
  
  // Handle command line arguments.  We need to strip off the
  // duplicated argv[0]; and we should handle the -i and -r arguments
  // ourselves. 

  while(!done)
   {
     n = ACE_OS::read(ACE_STDIN, buffer, BUFSIZ + 8192);
     if(n < 0)
      {
	if(errno == EINTR)
	 {
	   continue;
	 } /* end of if(errno == EINTR) */
	else
	 {
	   done = true;
	   break;
	 } /* end of else */
      } /* end of if(n < 0) */
     if(n == 0)
      {
	done = true;
	break;
      } /* end of if(n == 0) */
        
     buffer[n] = 0;
     DEBUG2 (2, "DEBUG: Read %d bytes --> \n%s", n, buffer);
     raw_data.append(buffer);
     string::size_type index = raw_data.find("\n");
     while ( index != string::npos )
      {
	command.assign(raw_data, 0, 
		       index + strlen("\n"));
	raw_data.erase(0, index + strlen("\n"));
	index = raw_data.find("\n");
	handle_command(command, argv);
      }     
   } /* end of while(!done) */
  DEBUG0 (2, "DEBUG:  Listener: done\n");
  exit(EXIT_SUCCESS);
}
