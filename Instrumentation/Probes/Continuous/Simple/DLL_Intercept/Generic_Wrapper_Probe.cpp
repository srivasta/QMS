// Generic_Wrapper_Probe.cpp
// Author      : Shivakumar C. Patil (shivakumar.patil@stdc.com)
// Description : 
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
 *  @ingroup DLLInterceptProbe
 *  @brief Contains implementation of DLL Interception Probe that delivers
 *  transparent instrumentation on Windows NT. 
 */


#include "Generic_Wrapper_Probe.h"
#include "Debug.h"
#include "Instrumentation.h"

// Adding the message delimiter to the end of this XML string so that
// the message can be written in one go
const char *dll_intercept_fmt = "\
   <?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
   <dllInterceptProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/dllInterceptProbe\"\n\
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
    xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/dllInterceptProbe\n\
    dllInterceptProbe.xsd\">\n\
     <interceptData>\n\
       <process_pid>%lu</process_pid>\n\
       <wrapper_name>%s</wrapper_name>\n\
       <contents>%s</contents>\n\
    </interceptData>\n\
   </dllInterceptProbe>\n\
%s\n";


void
worker(void *args)
{
	char buf[BUFSIZ], *pipe_name=0, *WrpFileName=0, 
		                      *pay_load = 0;
	char **args_pa = (char **) args;
	DWORD dwbytesread, dwdata, pid;
	dwdata = (DWORD) BUFSIZ;
	BOOL bstatus;
	HANDLE RMSENDPipe;
    SECURITY_ATTRIBUTES sa;

	ssize_t       ret      = 0;
    ssize_t       nleft    = 0;
    ssize_t       nwritten = 0;

	//parsing the command line options.
	for (int i=1; args_pa[i] != 0; i++)
	{
		if (ACE_OS::strcmp(args_pa[i],"-n") == 0)
		{
			pipe_name = (args_pa[++i]);
			DEBUG1 (2, "Probe Worker:Named Pipe ->%s", pipe_name);
			continue;
		}
		//Added this to get file name and process id.
		// These 2 are required to fill the response xml 
		if (ACE_OS::strcmp(args_pa[i],"-f") == 0)
		{
			WrpFileName = (args_pa[++i]);
			DEBUG1 (2, "Probe Worker:WrpFileName ->%s", WrpFileName);
			continue;
		}
		else if (ACE_OS::strcmp(args_pa[i],"-p") == 0)
		{
			pid = (atoi(args_pa[++i]));
			DEBUG1 (2, "Probe Worker:Pid ->%d", pid);
			continue;
		}
	}
		
	// set up overlapped structure fields 
	// to simplify this sample, we'll eschew an event handle 

    sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = NULL;

	//RM SEND Named pipe 
	RMSENDPipe = CreateNamedPipe(pipe_name, PIPE_ACCESS_INBOUND, 
		PIPE_READMODE_MESSAGE|PIPE_TYPE_MESSAGE|PIPE_WAIT, 1, 0, 0, NMPWAIT_WAIT_FOREVER, &sa);

	if (RMSENDPipe == INVALID_HANDLE_VALUE)
		 DEBUG1 (2,"Probe Worker:error in creating %s named pipe", pipe_name);
	else 
		 DEBUG1 (2,"Probe Worker:created the %s Named Pipe", pipe_name);

	for (;;)
	{
		if (status == stop_probe )
		{
			DEBUG0(2,"Probe Worker:Worker thread has been stopped\n");
			DisconnectNamedPipe(RMSENDPipe);
			CloseHandle(RMSENDPipe);
			break;
	    }
		else if ( status == start_probe )
		{
			bstatus = ReadFile(RMSENDPipe, buf, dwdata, &dwbytesread, NULL);
			if (bstatus)
			{
				char * ptr ;
				ptr = buf ;
					while (*ptr != '\0')
					{
						if (! isprint(*ptr))
							*ptr = ' ' ;
						ptr++ ;
					}
				pay_load = new char [ BUFSIZ + 4096 ];
				// Creating the pay_load XML.
				ret = _snprintf(pay_load, BUFSIZ+4096, dll_intercept_fmt, 
					                  pid, WrpFileName, buf, STDC::QMS::Citizen::delimiter); 
				
				ret = strlen (pay_load);
				nleft = ret;
				char *tmp = pay_load;

                while(nleft > 0)
				{
					if((nwritten = ACE_OS::write(ACE_STDOUT, pay_load, nleft)) <= 0)
					{
                        if(errno == EINTR)
						{
							nwritten = 0;
						} 
						else
						{
							ACE_OS::perror("Probe: Error in writing pay_load");
						} 
					} 
					nleft -= nwritten;
					pay_load += nwritten;
				} // end of while(nleft > 0) 

				delete tmp;

			} // end of if (bstatus)
			else 
				continue;
		} // end of if ( status == start_probe )

	} // end of for loop.

  DEBUG0 (2,"\n Worker Thread exiting ");

} // end of worker()




int
setflags(string &cmdstr, void *args)
{
   static bool start_worker = false;
   char *WrpFileName=0;
   static char *WrpName=0;
   char **args_pa = (char **) args;
   BOOL Unwrapstat;
   static DWORD pid;

   
   if( (cmdstr.find("start\n") != string::npos) ||
               (cmdstr.find("start\r\n") != string::npos) )
      {
         DEBUG0 (2, "PROBE Listener: Setting status to START\n");
         if (!start_worker)
         {
            //parsing the command line arguments.
            for (int i=1; args_pa[i] != 0; i++)
            {
               if (ACE_OS::strcmp(args_pa[i],"-f") == 0)
               {
                   WrpFileName = (args_pa[++i]);
                   DEBUG1 (2, "Probe Listener :WrpFileName ->%s", WrpFileName);
                   continue;
                }
                else if (ACE_OS::strcmp(args_pa[i],"-p") == 0)
                {
                    pid = (atoi(args_pa[++i]));
                    DEBUG1 (2, "Probe Listener : Pid ->%d", pid);
                    continue;
                }
                else if (ACE_OS::strcmp (args_pa[i],"-w") == 0)
                {
                    WrpName = (args_pa[++i]);
                    DEBUG1 (2, "Probe Listener :WrpName ->%s", WrpName);
                    continue;
                }

             } // end of for loop for parsing the command line args.

              DEBUG0 (2, "PROBE Listener: Starting the Worker thread\n");
              int ret = ACE_Thread::spawn((ACE_THR_FUNC)worker,
                                      (void *) args,  // arg
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

             if ((WrapProcess(WrpFileName, pid, NULL, FALSE)) == TRUE)
                DEBUG2 (2,"PROBE Listener:Wrapped the %d with %s", pid, WrpName);
             else
              {
                 DEBUG2 (2,"PROBE Listener:Unable to wrap %d with %s", pid, WrpName);
                 exit(1);
              }

	      start_worker = true;
	      DEBUG0(2, "PROBE Listener: Created Worker thread\n");
			  
          } // end of if ( !start_worker)

        } 
        else if( (cmdstr.find("stop\n") != string::npos) ||
               (cmdstr.find("stop\r\n") != string::npos) )
        {
           DEBUG0 (2, "PROBE Listener: Setting status to STOP\n");
           status = stop_probe;
           DEBUG1(2,"PROBE Listener:down for->%d \n", pid);

           if ((Unwrapstat = UnwrapProcess( WrpName, pid ))== UNWRAPPED)
                 DEBUG2(2,"PROBE Listener:Removed %s Wrapper from %d", WrpName, pid);

           else if ( Unwrapstat == PROCESS_NOT_ACCESSIBLE )
                 DEBUG1(2,"PROBE Listener:s not accessible", pid);

           else if ( Unwrapstat == NO_SUCH_WRAPPER )
                 DEBUG2(2,"PROBE Listener:Unable to Unwrap %s from %d", WrpName, pid);

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

