// Generic_Continuous_Probe.cpp
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



/** @file	Generic_Continuous_Probe.cpp
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
using std::cout;


// ACE specific headers
#include "ace/OS.h"
#include "ace/Thread_Manager.h"
#include "Debug.h"


// local headers
#include "Generic_Continuous_Probe.h"
#include "get_data_GCP.h"
#include "Parse_Duration.cpp"


#if defined(_WIN32)
//#define read	_read
#endif

/** @ingroup GenericProbe */

/// RCS version
static const char* version = "$Id: Generic_Continuous_Probe.cpp,v 1.11 2001/12/17 18:31:25 spatil Exp $";



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
  char *data = 0, duration[1024]; 
  char **args_pa = (char **) args;

  ssize_t       ret      = 0;
  ssize_t       nleft    = 0;
  ssize_t       nwritten = 0;

  int count,i; 
  struct timespec repeat_intrval; 
  repeat_intrval.tv_sec = 1;
  repeat_intrval.tv_nsec = 0;


  // parsing the command line options.
  for ( i = 0; args_pa[i] != 0 ; i++)
   {
     if (ACE_OS::strcmp(args_pa[i],"-r") == 0)
      { 
         count = abs ( atoi(args_pa[++i]) ); 
         continue; 
      }
     else if (ACE_OS::strcmp(args_pa[i],"-i") == 0)
      { 
        //refresh_rate = atof(args_pa[++i]); 
        strcpy(duration,args_pa[++i]);
        refresh_rate = STDC::QMS::duration_to_tv(duration);
        continue; 
      }
   }

  // validating the values of count and refresh_rate.
  if ( count > 1 )
    {
       if ( refresh_rate.tv_nsec > 0  || refresh_rate.tv_sec > 0 )
                { }
       else 
           {
              refresh_rate.tv_sec = repeat_intrval.tv_sec;
              refresh_rate.tv_nsec = repeat_intrval.tv_nsec;
              DEBUG2 (2, "USING DEFAULT Secs -> %d\t NanoSecs-> %d\n", 
                                  refresh_rate.tv_sec, refresh_rate.tv_nsec);
           }
    }
  else if ( count < 1 )
    {
       count = repeat_count;
       DEBUG1 (2, "USING DEFAULT REPETITIONS ->%d\n", count);

       if ( refresh_rate.tv_nsec > 0  || refresh_rate.tv_sec > 0 )
                { }
       else 
           {
              refresh_rate.tv_sec = repeat_intrval.tv_sec;
              refresh_rate.tv_nsec = repeat_intrval.tv_nsec;
              DEBUG2 (2, "USING DEFAULT Secs -> %d\t NanoSecs-> %d\n", 
                                  refresh_rate.tv_sec, refresh_rate.tv_nsec);
           }

    }
  else if (count == 1 ) 
       {
          if ( refresh_rate.tv_nsec > 0  || refresh_rate.tv_sec > 0 )
                { }
       else 
           {
              refresh_rate.tv_sec = repeat_intrval.tv_sec;
              refresh_rate.tv_nsec = repeat_intrval.tv_nsec;
              DEBUG2 (2, "USING DEFAULT Secs -> %d\t NanoSecs-> %d\n", 
                                  refresh_rate.tv_sec, refresh_rate.tv_nsec);
           }
       }


  DEBUG3 (2,"PROBE Worker: count ->%d\t Secs -> %d \t NanoSecs -> %d\n",
                           count, refresh_rate.tv_sec, refresh_rate.tv_nsec);

  // The loop that prints the data on the stdout.
  i=0;
  while (i < count )
   {
     DEBUG1 (2, "PROBE Worker: (i) value is ->%d\n", i);
     if ( status == stop_probe)
      {
	DEBUG0 (2, "PROBE Worker: The Probe has been Stopped\n");
	break;

      }
     else if (status == pause_probe )
      {
        DEBUG0 (2, "PROBE Worker: The Probe has been paused\n");
	ACE_OS::nanosleep ( (&refresh_rate));
        DEBUG0 (2, "Exiting from status = pause_probe ");
        continue;
      }
     else if (status == start_probe )
      {
        DEBUG0 (2, " status = start_probe ");
	data = get_data(args);
        char *tmp = data;
        ret = strlen (data);
        nleft = ret;
        int error_count = 0;

        while(nleft > 0)
        {
           if((nwritten = ACE_OS::write(ACE_STDOUT, data, nleft)) <= 0)
           {
             if(errno == EINTR)
             {
                nwritten = 0;
             } 
             else
             {
                ACE_OS::perror("Probe: Error in writing data");
                if ( error_count++ > 5 )
                   {
                     ACE_OS::fprintf(stderr, "Aborting from Probe\n");
                     exit(2);
                   }
             } 
           } 
           nleft -= nwritten;
           data += nwritten;
        } // end of while(nleft > 0) 

	delete tmp;
	ACE_OS::nanosleep  (&refresh_rate);
        DEBUG0 (2, "Exiting from status = start_probe ");
	i++ ; 
        continue;
      }
      else if (status == read_repetitions )
      {
        DEBUG0 (2, "PROBE Worker: The Probe is reading repetitions\n");
        {
          ACE_Write_Guard<ACE_Thread_Mutex> guard(TD_asset_guard);
          count = repeat_count;
          if ( count == 0)
          {
              DEBUG1 (2, "USING DEFAULT REPETITIONS ->%d\n", 1);
              count += 1;
          }
          i = 0;
          status = start_probe;
        }
        DEBUG0 (2, "Exiting from status = read_repetitions ");
        continue;

      }
      else if (status == read_repeatInterval )
      {
        DEBUG0 (2, "PROBE Worker: The Probe is reading repeat_intrval\n");
        {
          ACE_Write_Guard<ACE_Thread_Mutex> guard(TD_asset_guard);
          if ( refresh_rate.tv_sec > 0 || refresh_rate.tv_nsec > 0 )
          { }
          else
           {
              refresh_rate.tv_sec = repeat_intrval.tv_sec;
              refresh_rate.tv_nsec = repeat_intrval.tv_nsec;
              DEBUG2 (2, "USING DEFAULT Secs -> %d\t NanoSecs-> %d\n",
                                  refresh_rate.tv_sec, refresh_rate.tv_nsec);
           }

          status = start_probe;
        }
        DEBUG0 (2, "Exiting from status = read_repeatInterval ");
        continue;
      }
  
   } //end of while(i < count)
  
   DEBUG2 (2, "PROBE Worker: count ->%d\t(i) is ->%d\n", count,i);
   DEBUG0 (2, "PROBE Worker: Leaving the Worker method\n"); 
   DEBUG0(2, "PROBE Worker: Exiting from the Probe\n");

   exit(0);

}



int
setflags(string &cmdstr, void *args)
{

   string::size_type index = 0, index_nline = 0;
   static bool start_worker = false;

   {
      ACE_Write_Guard<ACE_Thread_Mutex> guard(TD_asset_guard);

      if( (cmdstr.find("pause\n") != string::npos) || 
          (cmdstr.find("pause\r\n") != string::npos))
      {
        DEBUG0 (2, "PROBE Listener: Setting status to PAUSE\n");
        status = pause_probe;
      }
      else if( (cmdstr.find("start\n") != string::npos) || 
               (cmdstr.find("start\r\n") != string::npos) )
      {
        DEBUG0 (2, "PROBE Listener: Setting status to START\n");
        status = start_probe;
       
        if (!start_worker)
        {
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
 
            start_worker = true;
            DEBUG0(2, "PROBE Listener: Created Worker thread\n");
        } //end of (!start_worker)

      }
      else if( (cmdstr.find("stop\n") != string::npos) ||
               (cmdstr.find("stop\r\n") != string::npos) )
      {
        DEBUG0 (2, "PROBE Listener: Setting status to STOP\n");
        status = stop_probe;
        DEBUG0(2, "PROBE Listener: Exiting from the Probe\n");
        exit(0);
      }
      else if( (cmdstr.find("resume\n") != string::npos) ||
               (cmdstr.find("resume\r\n") != string::npos) )
      {
        DEBUG0 (2, "PROBE Listener: Setting status to RESUME\n");
        status = start_probe;
      }
      else if ( (index = cmdstr.find("count,")) != string::npos) 
      {
         if ( cmdstr.find("\r") != string::npos && cmdstr.find("\n") != string::npos )
         {
           DEBUG0 (2, "Executing the NT specific code\n");
           DEBUG0 (2, "Setting the flags to repetitions\n");
           index_nline = cmdstr.find("\r\n");
           index += strlen("count,");
           DEBUG1 (2,"Repetitions->%s\n", 
                   cmdstr.substr(index,(index_nline - index)).c_str() );
           repeat_count = abs(atoi(cmdstr.substr(index,index_nline - index).c_str()));
           status = read_repetitions;
         }
         else if ( (index_nline = cmdstr.find("\n")) != string::npos)
         {
           DEBUG0 (2, "Setting the flags to repetitions\n");
           index += strlen("count,");
           std::cerr << "count value-> " << index << "\t" << index_nline << endl;
           DEBUG1 (2,"Repetitions->%s\n",
                   cmdstr.substr(index,(index_nline - index)).c_str() );
           std::cerr << cmdstr.substr(index,(index_nline - index)) << endl;
           repeat_count = abs(atoi(cmdstr.substr(index,(index_nline - index)).c_str()));
           status = read_repetitions;
         }

      }
      else if ( (index = cmdstr.find("intrval,")) != string::npos)
      {
         if ( cmdstr.find("\r") != string::npos && cmdstr.find("\n") != string::npos )
         {
           DEBUG0 (2, "Executing the NT specific code\n");
           DEBUG0 (2, "Setting the flags to repeatInterval\n");
           index_nline = cmdstr.find("\r\n");
           index += strlen("intrval,");
           DEBUG1 (2,"RepeatIntrval->%s\n", 
                  cmdstr.substr(index,(index_nline - index)).c_str() );
           refresh_rate = STDC::QMS::duration_to_tv(cmdstr.substr(index,(index_nline - index)).c_str() );
           status = read_repeatInterval;
         }
         else if ( (index_nline = cmdstr.find("\n")) != string::npos)
         {
           DEBUG0 (2, "Setting the flags to repeatInterval\n");
           index += strlen("intrval,");
           std::cerr << "intrval value-> " << index << "\t" << index_nline << endl;
           DEBUG1 (2,"RepeatIntrval->%s\n", 
                  cmdstr.substr(index,(index_nline - index)).c_str() );
           std::cerr << cmdstr.substr(index,(index_nline - index)) << endl;
           refresh_rate = STDC::QMS::duration_to_tv(cmdstr.substr(index,(index_nline - index)).c_str() );
           status = read_repeatInterval;
         }
      }
      else if (!start_worker)
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
