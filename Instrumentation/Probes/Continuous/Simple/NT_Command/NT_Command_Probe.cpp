// NT_Command_Probe.cpp
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



/** @file	NT_Command_Probe.cpp
 *  @ingroup	GenericProbe
 *  @brief Contains implementation of a Generic Continuos Probe.
 *
 * This file provides implementation of a Generic Continuous Probe that 
 * delivers QMS Metrics at the specified intervals.
 *
 */

// standard headers
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using std::string;
using std::cout;


// ACE specific headers
#include "ace/OS.h"
#include "ace/Thread_Manager.h"
#include "Debug.h"
#include "Instrumentation.h"

// local headers
#include "NT_Command_Probe.h"
//#include "get_data_GCP.h"
//#include "Parse_Duration.cpp"


const char *payload_fmt="\
<commandProbe\n\
    xmlns=\"http://www.stdc.com/2001/QMS/Probes/Continuous/CommandProbe\"\n\
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
    xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/Continuous/CommandProbe\n\
    commandProbe.xsd\">\n\
      <probeData>\n\
        <dataid>%ld</dataid>\n\
        <response>\n\
	 <textData>\n\
	  <message>\n\
	%s\n\
	  </message>\n\
	 </textData>\n\
        </response>\n\
      </probeData>\n\
</commandProbe>\n\
";


#define	INACTIVE	100

int output[2];
/** @ingroup GenericProbe */

/// RCS version
static const char* version = 
"$Id: NT_Command_Probe.cpp,v 1.1 2002/03/13 22:31:15 nath Exp $";



void
modify_data (string &src, const char *pattern, const char *replace)
{
  int x = src.find(pattern);
  while ( x < string::npos )
   {
     src.replace(x,1,replace);
     x = src.find(pattern, x + 1);
   }
}

/**
 *  @brief  Function handled by the Worker thread.
 *  @param  args List of command line arguments.
 *  @return None
 *
 * This function is used by the Worker thread to deliver the QMS Metrics
 * at the specified intervals.
 *
 */
void 
worker(void *args)
{
  
  // local variables.
  
  char *cmd_data = new char [ BUFSIZ + 8192 ], data[BUFSIZ + 8192];
  char *tmp = cmd_data;
  char **args_pa = (char **) args;
  string modified;
  modified.erase();
  
  ssize_t n;
  ssize_t       ret      = 0;
  ssize_t       nleft    = 0;
  ssize_t       nwritten = 0;
  
  bool done = false;
  static unsigned long dataid=0;
  
  strcpy (data, "Received request to execute command -> ");
  for ( int i = 0; args_pa[i] != NULL ; i++ )
   {
     strcat(data, args_pa[i]);
     strcat(data, " ");
   }
  
  ret = _snprintf(cmd_data, BUFSIZ + 8192, payload_fmt, dataid++, 
		  data);
  
  if(ret == -1 || ret > (BUFSIZ + 8192 ) )
   {
     std::cerr << "Buffer overflow in processing cmd_data, ignoring"
	       << std::endl;
   }
  
  strcat(cmd_data, STDC::QMS::Citizen::delimiter);
  strcat(cmd_data, "\n");
  
  ret = strlen (cmd_data);
  nleft = ret;
  int error_count = 0;
  
  while(nleft > 0)
   {
     if((nwritten = ACE_OS::write(ACE_STDOUT, cmd_data, nleft)) <= 0)
      {
	if(errno == EINTR)
	 {
	   nwritten = 0;
	 } 
	else
	 {
	   ACE_OS::perror("Probe: Error in writing cmd_data");
	   if ( error_count++ > 5 )
	    {
	      ACE_OS::fprintf(stderr, "Aborting from Probe\n");
	      exit(2);
	    }
	   
	 } // end of else .
	
      } // end of if((nwritten = ACE_OS::write(ACE_STDOUT, cmd_data, nleft)) <= 0)
     
     nleft -= nwritten;
     cmd_data += nwritten;
     
   } // end of while(nleft > 0) 
  
  // Done sending the Ack.
  
  cmd_data = tmp;
  
  while (!done)
   {
     n = read (output[0], data, BUFSIZ + 8192 );
     
     if(n < 0)
      {
	if(errno == EINTR)
	 {
	   continue;
	 } 
	else
	 {
	   break;
	 } 
	
      } // end of if(n < 0)
     
     if(n == 0)
      {
	break;
      } /* end of if(n == 0) */
     
     data[n] = 0;
     DEBUG1 (2, "Read %d bytes --> \n", n);
     DEBUG1 (2, "Worker Read the cmd_data ->%s\n", data);
     
     modified.append(data);
     
   } // end of while (!done)
  
  modify_data(modified, "&", "&amp;");
  modify_data(modified, "<", "&lt;");
  modify_data(modified, ">", "&gt;");
  
  ret = _snprintf(cmd_data, BUFSIZ + 8192, payload_fmt, dataid++, 
		  modified.c_str());
  
  if(ret == -1 || ret > (BUFSIZ + 8192 ) )
   {
     std::cerr << "Buffer overflow in processing cmd_data, ignoring"
	       << std::endl;
   }
  
  strcat(cmd_data, STDC::QMS::Citizen::delimiter);
  strcat(cmd_data, "\n");
  
  ret = strlen (cmd_data);
  nleft = ret;
  error_count = 0;
  
  while(nleft > 0)
   {
     if((nwritten = ACE_OS::write(ACE_STDOUT, cmd_data, nleft)) <= 0)
      {
	if(errno == EINTR)
	 {
	   nwritten = 0;
	 } 
	else
	 {
	   ACE_OS::perror("Probe: Error in writing cmd_data");
	   if ( error_count++ > 5 )
	    {
	      ACE_OS::fprintf(stderr, "Aborting from Probe\n");
	      exit(2);
	    }
	   
	 } // end of else .
	
      } // end of if((nwritten = ACE_OS::write(ACE_STDOUT, cmd_data, nleft)) <= 0)
     
     nleft -= nwritten;
     cmd_data += nwritten;
     
   } // end of while(nleft > 0) 
  
  cmd_data = tmp;
  delete [] cmd_data;
  
  DEBUG0 (2, "PROBE Worker: Leaving the Worker method\n"); 
  DEBUG0(2, "PROBE Worker: Exiting from the Probe\n");
  
  exit(0);
  
}



int
setflags(string &cmdstr, void *args)
{
  static bool start_worker = false;
  static HANDLE hProcess;
  int hStdOut;
  char **args_pa = (char **) args;
  
  if( (cmdstr.find("start\n") != string::npos) || 
      (cmdstr.find("start\r\n") != string::npos) )
   {
     
     DEBUG0 (2, "PROBE Listener: Setting status to START\n");
     if (!start_worker)
      {
	// Create the pipe
	if(_pipe(output, BUFSIZ + 8192, O_BINARY | O_NOINHERIT) == -1)
	  perror ("_pipe");
	
	// Duplicate stdout handle (next line will close original)
	hStdOut = _dup(_fileno(stdout));
	
	// Duplicate write end of pipe to stdout handle
	if(_dup2(output[1], _fileno(stdout)) != 0)
	  perror ("_dup2");
	
	// Close original write end of pipe
	close(output[1]);
	
	//Changing the command line arguments.
	int j = 0, i = 0;
	
	while ( args_pa[++i] != 0)
	  args_pa[j++] = args_pa[i];
	
	args_pa[j] = NULL;
	
	// Spawn process
	hProcess = (HANDLE)spawnvp(P_NOWAIT, args_pa[0], args_pa);
	
	// Duplicate copy of original stdout back into stdout
	if(_dup2(hStdOut, _fileno(stdout)) != 0)
	  perror ("_dup2");
	
	// Close duplicate copy of original stdout
	close(hStdOut);
	
	if ( hProcess )
	 {
           
	   DEBUG0 (2, "PROBE Listener: Starting the Worker thread\n");
	   int ret = ACE_Thread::spawn((ACE_THR_FUNC)worker,
				       args,  // arg
				       THR_JOINABLE, // flags
				       0,  // t_id
				       0,  // t_handle
				       ACE_DEFAULT_THREAD_PRIORITY,
				       0,  // stack
				       0,  // stack_size
				       0   // thread_adapter
				       );
	   if(ret == -1)
	    {    
	      ACE_OS::perror ("Worker Thread Cretion failed\n");
	      DEBUG0 (2, "PROBE Listener: Error creating the Worker thread\n"); 
	      exit(1);
	    } // end of if(ret == -1)
	   
	   DEBUG0(2, "PROBE Listener: Created Worker thread\n");
	   start_worker = true;
	   
	 } // end of if ( hProcess)
	else 
	 {
	   DEBUG0 (2, "PROBE Worker:Error in Spawning the child process");
	   cerr << "PROBE Listener:Error in Spawning the child process\n";
	 }
	
	
      } //end of (!start_worker)
     
   } // end of if( (cmdstr.find("start\n") != string::npos)
  else if( (cmdstr.find("stop\n") != string::npos) ||
	   (cmdstr.find("stop\r\n") != string::npos) )
   {
     DEBUG0 (2, "PROBE Listener: The Probe has been Stopped\n");
     if (!TerminateProcess(hProcess, INACTIVE))
       perror ("TerminateProcess");
     
     DEBUG0(2, "PROBE Listener: Exiting from the Probe\n");
     exit(0);
   }
  else if (!start_worker)
   {
     DEBUG0(2, "PROBE Listener: ****ERROR**** Pl Enter start\\n to start Probe\n");
   }
  
  return 0;
  
}



/**
 *  @brief The function used by the listener thread.
 *  @param  None
 *  @return None
 *
 * The Listener thread continuously monitors the standard input for 
 * commands like Start, Pause, Resume and Stop. Once it receives a command,
 * it changes the state of the probe, so that Worker thread can behave 
 * according to the command.
 *
 */
int 
listener (void *args)
{
  char buff[LENGTH];
  ssize_t n;
  string command,raw_data;
  raw_data.erase();
  command.erase();
  bool done = false;
  
  for (;;)
   {
     while (!done)
      {
	n = ACE_OS::read (ACE_STDIN, buff, LENGTH);
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
	DEBUG1 (2, "Read %d bytes --> \n", n);
	raw_data.append(buff);
        
	string::size_type index = raw_data.find("\n");
	while ( index != string::npos )
         {
           command.assign(raw_data, 0, 
			  index + strlen("\n"));
           raw_data.erase(0, index + strlen("\n"));
           index = raw_data.find("\n");
           setflags(command, args);
         }
      }
   } // end of for loop.

  DEBUG0 (2, "PROBE Listener: Leaving the Listener thread\n");
  return 0;

}




/**
 * @brief Initializes the Probe and creates Worker and Listener threads.
 * @param argc Count of command line arguments.
 * @param  argv List  of command line arguments.
 * @return returns the exit status of the program.
 *
 * This function performs the following tasks.
 *  - Starts the Worker and Listener threads.
 *  - Makes sure that Command syntax is correct.
 *  - Waits for the above threads before exiting.
 */
int 
main (int argc, char *argv[])
{

  DEBUG0(2, "PROBE Main: Calling Listener Method\n"); 
  listener((void *)argv);
  DEBUG0(2, "PROBE Main: Exiting from the Probe\n");

  exit(0);

}
