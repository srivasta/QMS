/// Using standard C++ namespace.

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


#include "ace/OS.h"
#include "ace/Thread.h"
#include "ace/Signal.h"
#include "ace/Pipe.h"
#include "ace/Process.h"

#include "QMS_Debug.h"
#include "QMS_Api.h"
//#include "QMS_Remos_Msg.h"
#include "Remos_Datastructs.h"


#include <stdio.h>
#include <string.h>

using namespace std;
#include <string>

using std::string;



#define DEFAULT_SLEEP 2.0
QMS_Api qms_api;
int gwritefd;
int start_set = 0;
//ACE_Thread_Mutex TD_asset_guard;

/// The host that the collector is running on
char *collhost_p = 0;
// The port number on the collector host
char *port_p = 0;


static const char* version = "$Id: FFD_Sensor.cpp,v 1.7 2001/10/21 08:54:07 srivasta Exp $";

//char *env_init[] = { "PATH=/home/spatil/Work/devel/quite/QMS/Instrumentation/Probes/Continuous/Named","LD_LIBRARY_PATH=/opt/ACE_wrappers/ace:/home/spatil/Work/devel/quite/QMS/API:/home/spatil/Work/devel/quite/QMS/Instrumentation/Sensors/Remos/utility", NULL };

//char *env_init[] = { "PATH=/home/quite/spatil/oldstuff/desiSensors:/home/quite/components/QMS-1.0/API/Remos_Sensor:/usr/local/share/jdk1.2.2/bin","LD_LIBRARY_PATH=/opt/ACE_wrappers/ace:/opt/Remos/modeler/lib/I386/LINUX:/opt/QMS/API:/opt/QMS/Instrumentation/Sensors/Remos/utility", "CLASSPATH=/opt/Remos/java",  NULL };

void Remos_CallBack(const string &query, void * arg_p = 0);
void  send_query( void *);
void extract_query(string &, int &, char *);

extern "C" void
sig_handler(int sig)
{
  QMS_Trace ("sig_handler", __LINE__, __FILE__);

  char kill_a[10]="kill\n";
  int len = ACE_OS::strlen(kill_a);

  ACE_OS::printf ("Caught Signal %d\n", sig);
  qms_api.disconnect();
  if ( start_set ) {
  if ( ACE_OS::write (gwritefd, kill_a, len) != len )
         ACE_OS::perror("write");
  else
        ACE_OS::printf ("Sent the Kill\\n command to the Probe\n");
  }
  sleep(2);
  ACE_OS::exit (sig);
}



int
main (int argc, char *argv[])
{
  QMS_Trace ("main", __LINE__, __FILE__);

// commented on 4/30/01
/*
  sigset_t oldmask_set, newmask_set;
  ACE_Sig_Set newmask((sigset_t *) &newmask_set), oldmask((sigset_t *) &oldmask_set);
  newmask.fill_set();
  newmask.sig_del(SIGTERM);
  newmask.sig_del(SIGINT);
  newmask.sig_del(SIGABRT);
  newmask.sig_del(SIGHUP);


  if ( ACE_OS::sigprocmask (SIG_BLOCK, &(newmask.sigset()), &(oldmask.sigset()) ) < 0 )

       ACE_OS::perror (" sigprocmask failed ");


  DEBUG0 (DEBUG_L_ENTER, "DEBUG: starting\n");

*/
  signal(SIGTERM,sig_handler);
  signal(SIGINT,sig_handler);
  signal(SIGABRT,sig_handler);
  signal(SIGHUP,sig_handler);
  signal(SIGSEGV,sig_handler);


/*
  ACE_Sig_Action sa ((ACE_SignalHandler) (sig_handler),SIGINT);
  ACE_Sig_Action sa1 ((ACE_SignalHandler) (sig_handler),SIGTERM);
  ACE_Sig_Action sa2 ((ACE_SignalHandler) (sig_handler),SIGABRT);
  ACE_Sig_Action sa3 ((ACE_SignalHandler) (sig_handler),SIGHUP);
*/

  DEBUG0 (DEBUG_L_CALL, "DEBUG: added signal handling\n");
  DEBUG3(DEBUG_L_CALL, "DEBUG: starting the API With ID = %d "
         " Send event type = %d Recieve event type = %d\n",  Data_Supplier,
         //QMS_Remos_Data, << QMS_Remos_Query );
         QMS_Remos_Data,  QMS_Remos_Query );

  char * ecname_p = (char *) "QMS_Channel";

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
        cout << argv[0] << version << endl
             << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
             << endl
             << "\t-h              : This help text"  << endl
             << "\t-v              : Prints out the version"  << endl
             << "\t-ecname    NAME : The name of the event channel"  << endl
             << "\t-e         NAME : The name of the event channel"  << endl
             << "\t-collector NAME : The name of the Collector Host"  << endl
             << "\t-c         NAME : The name of the Collector Host"  << endl
             << "\t-p       NUMBER : The name of the Collector Port"  << endl
             << "\t-port    NUMBER : The name of the Collector Port"  << endl
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        cout << argv[0] << ": Version " << version << endl;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "ecname") || strchr((argv[i] + j), 'f'))
      {
        ecname_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
        strcpy(ecname_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (DEBUG_L_ERROR, "unknown argument", argv[i]);
   }



  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {

     qms_api.init(argc, argv,
                   Data_Supplier,   // My ID
                   QMS_Remos_Data,  //  The data I send
                   QMS_Remos_Query, // The data I get
                   ecname_p
                   );
      ACE_TRY_CHECK;
      qms_api.register_callback(Remos_CallBack, 0);
      ACE_TRY_CHECK;
      qms_api.connect_supplier();
      ACE_TRY_CHECK;
      qms_api.connect_consumer();
      ACE_TRY_CHECK;
      qms_api.listen();
      printf ("\n Leaving the Main\n");
      ACE_TRY_CHECK;
    }

  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      qms_api.connect_supplier();
      qms_api.connect_consumer();
      exit (1);
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      qms_api.connect_supplier();
      qms_api.connect_consumer();
      exit (2);
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      qms_api.connect_supplier();
      qms_api.connect_consumer();
      exit (3);
    }
  ACE_ENDTRY;

}

void send_query(void *a)
{
  printf ("Start of Send_query \n");
  char *tmp_p = reinterpret_cast<char *>( a );
  string query(tmp_p);
  int event_type = 0;

/// default request_id
  int request_id = 0;

  extract_query(query, event_type, tmp_p);
  
//if ( query_data_ptr->request_id >= 100 )
if (event_type)
{
   printf ("Inside the Continuous Probe\n");

  pid_t childpid;
  int ctrlpipe[2], datapipe[2];

  //char stop_a[10]="stop\n";
  char stop_a[10]="pause\n";

  char start_a[10]="start\n";

  //char kill_a[10]="kill\n";
  char kill_a[10]="stop\n";
 
  char resume_a[10]="resume\n";
  int len;

// commented on 4/30/01
/*  sigset_t oldmask_set, newmask_set;
  ACE_Sig_Set newmask((sigset_t *) &newmask_set), oldmask((sigset_t *)&oldmask_set);
  newmask.fill_set();

  if ( pthread_sigmask (SIG_BLOCK, &newmask.sigset(), &oldmask.sigset() ) != 0)
        perror("pthread_sigmask error");
*/

  fprintf (stderr,"\n Send Query :- The Message  is ->%s\n", tmp_p);

  if (ACE_OS::strcmp(tmp_p,stop_a) == 0)
  {
      fprintf (stderr,"\n Received pause Message \n");
      len = strlen(stop_a);
        if ( write (gwritefd, stop_a, len) != len )
                perror("write");
        else {
              fprintf (stderr,"\n Sensor Stop Thread:- successful write to child\n");
              delete tmp_p;
              return ;
             }

  }

  else if (ACE_OS::strcmp(tmp_p,resume_a) == 0)
  {
      fprintf (stderr,"\n Received resume Message \n");
      len = strlen(resume_a);
        if ( write (gwritefd, resume_a, len) != len )
                perror("write");
        else {
              fprintf (stderr,"\n Sensor Stop Thread:- successful write to child\n");
              delete tmp_p;
              return ;
             }

  }

  else if (ACE_OS::strcmp(tmp_p,kill_a) == 0)
  {
      fprintf (stderr,"\n Received stop Message \n");
      len = strlen(kill_a);
        if ( write (gwritefd, kill_a, len) != len )
                perror("write");
        else {
              fprintf (stderr, "\n Sensor Kill Thread:- successful write to child\n");
              delete tmp_p;
              start_set = 0;
              return ;
             }

  }
  else if (ACE_OS::strcmp(tmp_p,start_a) == 0)

         {
            fprintf (stderr, "\n Received the start command \n");
            if ( start_set )
            {
                ACE_OS::fprintf (stderr, "Probe active already \n");
                len = ACE_OS::strlen(start_a);
                if ( ACE_OS::write (gwritefd, start_a, len) != len )
                         { ACE_OS::perror("write"); ACE_OS::exit(0); }
                else {
                        ACE_OS::fprintf (stderr, "\n Sensor start Thread:- successful write to child\n");
                        delete tmp_p;
                        return ;
                     }
            }
            else {
                   ACE_OS::fprintf (stderr, "Probe started First Time \n");
                   delete tmp_p;
                   start_set = 1;
                 }

         }
          else {
                 ACE_OS::fprintf (stderr,"Pl use ->start\\n, stop\\n ,pause\\n or resume\\n \n");
                 return ;
               }


  if (pipe(ctrlpipe) < 0)
        perror("pipe");

  if (pipe(datapipe) < 0)
        perror("pipe");

  if ( (childpid = fork() ) == 0) {

        fprintf (stderr, "\nInside the Child\n");

        if (close(ctrlpipe[1]) != 0)
        perror ("close");
        if (close(datapipe[0]) != 0)
        perror ("close");

        if (ctrlpipe[0] != STDIN_FILENO ) {

        fprintf (stderr, "\nSTDIN \n");
                if ( dup2 ( ctrlpipe[0], STDIN_FILENO ) != STDIN_FILENO ) {
                        fprintf(stderr, "Problem with STDIN dup2\n");
                        exit(3);
                }
                if (close ( ctrlpipe[0]) != 0)
                perror("close");
        }

        if (datapipe[1] != STDOUT_FILENO ) {

        fprintf (stderr, "\nSTDOUT \n");
                if ( dup2 ( datapipe[1], STDOUT_FILENO ) != STDOUT_FILENO ) {
                        fprintf(stderr, "Problem with STDOUT dup2\n");
                        exit(3);
                }
                if ( close (datapipe[1]) != 0)
                perror("close");
        }

        fprintf (stderr, "\nGoing to Execle\n");

        //if (execle ("/home/spatil/Work/devel/quite/QMS/Instrumentation/Probes/Continuous/Named/ffd_probe", "ffd_probe",(char *)0, env_init) < 0) 

        if (execlp ("ffd_probe", "ffd_probe", (char *)0 ) < 0) 

        {
                fprintf (stderr, "\nExeclp failed\n");
                perror ("execlp");
        }

        exit(0);

       }

  else {
           printf("\n Original Childpid ->%d\n", childpid);
           ssize_t n;
           char buff[BUFSIZ];

           gwritefd = ctrlpipe[1];

           printf ("\n The global write fd->%d\n", gwritefd);

           if (close(ctrlpipe[0]) != 0)
           perror ("close");
           if (close(datapipe[1]) != 0)
           perror ("close");

           while( (n = read(datapipe[0], buff, BUFSIZ) ) > 0 )
           {
                buff[n] = 0;
                //fprintf (stderr,"data from Child ------>%s\n", buff);
                printf ("\ndata from Child ------>%s\n", buff);
                qms_api.send(buff);

           }

           if (n == -1)
                perror("read from child\n");
           else
                printf ("\n Parent Read failed ->%d\n", n);

           int status = 0;
           pid_t pid_ret;

           while ( (pid_ret = waitpid(childpid, &status, 0) )  != childpid )
           printf("\n Exited Childpid ->%d\n", pid_ret);
           if (WIFEXITED(status))
                printf("\n Child exited normally\n");
           else
                printf ("\n Child exited abnormally\n");
           if (close(datapipe[0]) != 0)
           perror("close");
           if (close(ctrlpipe[1]) != 0)
           perror ("close");

      }

       //return;
 } // end of continuous Probe

else  {

   printf ("Inside the OneSHot Probe\n");

  if (tmp_p != NULL) 
	{ printf ("deleting the tmp_p\n"); delete tmp_p; }
  
 } // End of One shot Probe


} 


void
Remos_CallBack(const string &query, void *arg_p)
{
  QMS_Trace ("Remos_CallBack", __LINE__, __FILE__);
  fprintf(stderr,"\n In Remos_CallBack\n");
  fprintf(stderr,"\n Query ->%s\n",query.c_str());

  if (arg_p)
   {
     cout << "With a non null argument"  << endl;
   }


  string x;
  x.assign(query.data());
  int len = x.length();
  char *temp_p = new char[len + 1];
  x.copy(temp_p, len, 0);
  temp_p[len] = 0;
  cout << "The received Message -> " << temp_p << "length -> " << strlen (temp_p)  << endl;

  if (ACE_Thread::spawn((ACE_THR_FUNC)send_query,
                            (void *)temp_p,  // arg
                            THR_JOINABLE, // flags
                            0,  // t_id
                            0,  // t_handle
                            ACE_DEFAULT_THREAD_PRIORITY,
                            0,  // stack
                            0,  // stack_size
                            0   // thread_adapter
                            )==-1)
 
        ACE_OS::perror (" Creation of Send Thread failed\n");

  else
        ACE_OS::printf ("Send Query thread created \n");


}




void extract_query(string &data, int &event_type, char *command)
{
  ACE_Thread_Mutex asset_guard;
  ACE_Read_Guard<ACE_Thread_Mutex> guard(asset_guard);
  {
     ACE_DECLARE_NEW_CORBA_ENV;
     
     size_t location = 0;
     size_t start = 0;
     size_t stop = 0;

     location = start;

     // the EventType stuff now

     location = data.find("<EventType>", location);
     if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
     location += strlen("<EventType>");
     start = location;

     location = data.find("</EventType>", location);
     if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
     stop = location;

     // stuff added to make sure we are getting this data on NT side
     string x;
     x.assign( (data.substr(start, stop - start)).data() );
     int len = stop - start;
     char *temp_p = new char[len +1];
     x.copy(temp_p, len, 0);
     temp_p[len] = 0;

     event_type = atoi(temp_p);
     delete temp_p;

     cout << "The EventType is -> " << event_type << endl;

     // The request id stuff now.
   
     location = data.find("<requestid>", location);
     if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
     location += strlen("<requestid>");
     start = location;

     location = data.find("</requestid>", location);
     if (location == string::npos)
     {
       ACE_THROW_RETURN (CORBA::BAD_PARAM (), 0);
     }
     stop = location;

     // stuff added to make sure we are getting this data on NT side
     
     x.assign( (data.substr(start, stop - start)).data() );
     len = stop - start;
     x.copy(command, len, 0);
     command[len] = 0;

     cout << "The command is -> " << command << endl;


     }

}

