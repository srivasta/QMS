/*****************************************************************************
**
** $Id: testcom-lib.c,v 1.1 2001/12/10 06:26:20 spatil Exp $
**
******************************************************************************/

#include <stdlib.h>

#include "testcom-lib.h"


int server_fd;  /* SERVER'S SOCKET DESCRIPTOR           */
int maxfdpl1;   /* ARGUMENT TO SELECT CALL              */
fd_set fdvar;   /* TABLE TO KEEP ALL THE CLIENT SOCKETS */

struct AppListElmt *head;


/*************************************************************************
**
** Error Handler
**
**************************************************************************/
void ErrHandler()
{
  exit(1);
}


/*************************************************************************
**
** Pipe Signal Handler
**
**************************************************************************/
void PipeHandler( int temp )
{
  printf("\ncomm-lib.c:: PipeHandler(): Broken Pipe\n");
}



/***************************************************************************
**
** Function :Initializes a Character buffer
**
***************************************************************************/
void FlushBuff(char *buff, int n)
{
  int i;
  for(i=0;i<n; i++)
    buff[i]='\0';
}


/***************************************************************************
**
** Function : Sends message "msg" of any size "size"  to specified socket "sd"
**            from application "appname".
** Modified : Mar 08, 1998
**
***************************************************************************/
int Send_Message(int sd, char *appname, char *msg, int size)
{
  int value;
  char size_message[SIZE_MSG_LEN];

  /*
  ** THIS FUNCTION IS CALLED WHEN THERE IS A BROKEN PIPE.
  */
  //signal(SIGPIPE, PipeHandler );
  /*
  ** FIRST SEND THE SIZE OF THE MESSAGE AS GIVEN BY THE CALLING
  ** APPLICATION AND THE APPLICATION NAME.
  */

  sprintf( size_message,"%d %s", size, appname);

  /*
  **  SEND THE INITIAL MESSAGE TO INFORM OF THE SIZE.
  */

  if( (value = send( sd, size_message, SIZE_MSG_LEN, 0 ) ) < 0 ) {

    /*
    ** IF THERE IS A BROKEN PIPE INDICATE THAT THE APPLICATION ON
    ** THE OTHER SIDE IS DEAD.
    */

    if( errno == EPIPE ) {
	     return( DEAD );
    }

    perror("comm-lib.c: SendMessage() - Write failed when sending the size.");
    //printf("\n Erring process = %d \n", getpid());
    return( DEAD );
  }

  /*
  **  SEND THE ACTUAL MESSAGE.
  */

  if( (value = send(sd, msg, size, 0 )) < 0 )
    {

      /*
      ** IF THERE IS A BROKEN PIPE INDICATE THAT THE APPLICATION ON
      ** THE OTHER SIDE IS DEAD.
      */

      if( errno == EPIPE )
	  {
	   return( DEAD );
	  }

      perror("comm-lib.c:: SendMsg(): Write call failed when sending the acutal data.");
      //printf("\n Erring process = %d \n", getpid());
      return( DEAD );

    }

  return( SUCCESS );

}


/***************************************************************************
**
** Function : Receives Messages on the socket "sd" from the application "appname"
**            and returns the buffer.
**
**   The block_flag sets the blocking option for the receive call.
**
**   0 - non blocking
**   1 - blocking (default)
**
*****************************************************************************/
char * ReceiveMessage(int sd, char *appname, int *size_of_msg )
{
  char *buffer, *message_in, temp_buff[SIZE_MSG_LEN], size_buff[SIZE_MSG_LEN];
  int value = 0, total_size = 0, total_value = 0;

  /*
  ** THIS FUNCTION IS CALLED WHEN THERE IS A BROKEN PIPE.
  */

  //signal(SIGPIPE, PipeHandler );

  /*
  ** RECEIVE THE FIRST MESSAGE TO DETERMINE THE SIZE
  */

  while( total_value < SIZE_MSG_LEN )
  {
	 value = 0;
     if((value = recv(sd, temp_buff, SIZE_MSG_LEN - total_value, 0)) < 0 )
	 {

       if( errno == EAGAIN ) // if exit was due to no data condition
	   {
	 	 *size_of_msg = NODATA;
	 	  return( NULL );
	   }

       /*perror("comm-lib.c:: ReceiveMessage(): Read call failed when getting the size ");*/
       //printf("\n Erring process = %d \n", getpid());
       /** *size_of_msg = FAILURE; **/ /*** #'d out by praveen **/
       *size_of_msg = DEAD;
       return (NULL);
	 }

    if (value == 0)
    {
        /*
        ** Case when The sender is dead.
        */

        *size_of_msg = DEAD;  /*** To indicate that Sender id DEAD ***/
        return(NULL);
    }

	memcpy(size_buff + total_value, temp_buff, value);
	total_value = total_value + value;
  }


  /*
  ** SCAN THE SIZE, THE NAME, AND PREPARE THE BUFFER TO READ IT IN.
  */

  sscanf( size_buff,"%d %s", size_of_msg, appname);
  buffer = (char *)malloc( *size_of_msg );
  message_in = (char *)malloc( *size_of_msg );
  total_size = *size_of_msg;

  if((buffer == NULL )||(message_in == NULL ))
    {
      perror("comm-lib.c:: ReceiveMessage(): Malloc error");
      *size_of_msg = FAILURE;
      return(NULL);
    }


  /*
  ** NOW READ THE ACTUAL MESSAGE
  ** WE ARE READING IN A LOOP BECAUSE IN SOME CASES THE WHOLE
  ** MESSAGE DOES NOT COME IN ONE JUNK. THIS IS A SYSTEM THING.
  */

  total_value = 0;
  while( total_value < total_size )
    {
	   value = 0;
	   if((value = recv(sd, message_in, total_size - total_value, 0) ) < 0 )
	   {
	 	 /*perror("comm-lib.c:: ReceiveMesssage(): Read failed when getting the actual data ");*/
		 //printf("\n Erring process = %d \n", getpid());
	 	 *size_of_msg = DEAD; /** Changed from FAILURE to DEAD bu praveen **/
	 	 return(NULL);
	   }

	   if (value == 0)
	   {
	     /*
	     ** Case when The sender is dead.
	     */

	     *size_of_msg = DEAD;  /*** To indicate that Sender id DEAD ***/
	     return(NULL);
	   }


	  memcpy(buffer + total_value, message_in, value);
	  total_value = total_value + value;

    } /* end while */

  free( message_in );
  return( buffer );

}


/***************************************************************************
**
** Function : A communication Initialization Routine that connects to a
**            server on specified host and port and returns a socket desc.
**
****************************************************************************/
int ClientInitialize(char *appname, char *server_host, int server_port)
{
    struct sockaddr_in sin;
    struct hostent *hp;
    char my_host_name[HOSTNAMELEN+1];
    int sd;  /* socket desc for Server */

    struct message out_messg;

    FlushBuff(out_messg.appname, APPNAMELEN);
    FlushBuff(out_messg.hostname, HOSTNAMELEN);
    FlushBuff(out_messg.data, DATALEN);

    /*
    ** GET MY HOST NAME
    */

    if (gethostname(my_host_name, sizeof(my_host_name))  < 0)
    {
	perror("client.c:: ClientInitialize(): unable to gethostname");
	return( FAILURE );
    }
    my_host_name[HOSTNAMELEN-1] = '\0';


    /*
    ** GET DATA FOR THE REMOTE HOST.
    */

    if( (hp=gethostbyname(server_host)) == 0 )
      {
	perror("comm-lib.c:: ClientInitialize(): gethostbyname:");
	return( FAILURE );
      }


    /*
    ** INITIALIZE THE STRUCTURE DESCRIBING WHAT TYPE OF CONNECTION IS NEEDED.
    */

    memset((char *)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    memcpy((char *)&sin.sin_addr, (char *)hp->h_addr,  hp->h_length);
    sin.sin_port = htons((unsigned short)server_port);

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
	perror("comm-lib.c:: ClientInitialize: socket call failure:");
	return( FAILURE );
      }


    /*
    ** CONNECT TO THE SERVER
    */


    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
      {
	perror("comm-lib.c:: ClientInitialize() :: Connect failure");
        closesocket( sd );
	return( FAILURE );
      }
    else
      {
	/*
	** SEND THE INITIAL INFORMATION TO THE SERVER.
	*/

	out_messg.type = REG;
	memcpy(out_messg.appname, appname, APPNAMELEN);
	memcpy(out_messg.hostname, my_host_name, HOSTNAMELEN);

	if( send(sd, (char *)&out_messg, sizeof(out_messg), 0) < 0 )
	  {
	    perror("comm-lib.c:: ClientInitialize(): reg'ing write failed");
	    closesocket( sd );
            return( FAILURE );
	  }

      }

    /*
    ** RETURNE THE SOCKET DESCRIPTOR.
    */

    return(sd);
}



/***************************************************************************
**
** Function : Asks the name server about where the server_name is running.
**            and then connect to that server using this information.
**
****************************************************************************/
int NewClientInitialize(char *appname, char *server_name, char * server_host, int server_port)
{
    char my_host_name[HOSTNAMELEN+1];
    char buff[256], *msg, app[APPNAMELEN], host[APPNAMELEN];
    int sd, sys_db_sd, size, port;

    // Initialize winsock
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD( 2, 0 );

	if ( WSAStartup(wVersionRequested, &wsaData) != 0 ) {
		perror("WinSock DLL Startup initialize fail\n");
		return FAILURE;
	}

    /*
    ** GET MY HOST NAME
    */

    if (gethostname(my_host_name, sizeof(my_host_name))  < 0)
    {
	perror("comm-lib.c:: NewClientInitialize(): First gethostname");
	return( FAILURE );
    }
    my_host_name[HOSTNAMELEN-1] = '\0';


    /*
    ** CONNECT TO THE NAME DATA SERVER AND GET THE HOST INFORMATION OF
    ** THE SERVER APPLICATION.
    */

    if( ( sys_db_sd = ClientInitialize( "other", server_host, server_port ) ) < 0 )
      {
	perror("comm-lib.c:: NewClientInitialize(): Unable to connect to Name Server.");
	return( FAILURE );
      }


    /*
    ** FORMAT THE BUFFER TO REQUEST DATA FROM THE NAME SERVER
    ** AND SEND IT.
    */

    sprintf( buff,"R %s", server_name );
    if( ( Send_Message( sys_db_sd, "other", buff, sizeof( buff ) ) ) < 0 )
      {
	perror("comm-lib.c:: NewClientInitialize(): Write to Name Server failed");
        closesocket( sys_db_sd );
        return( FAILURE );
      }

    msg = ReceiveMessage( sys_db_sd, app, &size );
    if( msg != NULL )
      {
	FlushBuff( host, sizeof( host ) );
	sscanf( msg,"%s %d", host, &port );

	if( port == 0 )
	  {
	    printf("comm-lib.c:: NewClientInitialize(): %s not registered\n",server_name );
	    closesocket( sys_db_sd );
            return( FAILURE );
	  }

	printf("%s Host = %s\n%s Port =  %d\n",server_name, host, server_name, port);
      }
    if( size == DEAD )
      {
	closesocket( sys_db_sd);
	return( FAILURE );
      }

    free( msg );
    closesocket( sys_db_sd );


    /*
    ** CALL INITIALIZE TO CONNECT TO THE SERVER.
    */

    if( ( sd = ClientInitialize( appname, host, port ) ) < 0 )
      {
	perror("comm-lib.c:: NewClientInitialize(): Unable to connect to the server.");
	return( FAILURE );
      }

    /*
    ** RETURN THE SOCKET DESCRIPTOR.
    */

    return(sd);
}


/***************************************************************************************
**
** This functions initializes the server on the user specified port.  If the port is zero
** then the systmem picks one on random and passes it back to the calling function.
**
*****************************************************************************************/
int ServerInitialize(int port_no)
{
  struct sockaddr_in sin0, sin1;
  int port_info_size;
  WORD wVersionRequested;
  WSADATA wsaData;



  // INITIALIZING SOCKET AND BINDING ADDRESS


   // Initialize the winsock

	wVersionRequested = MAKEWORD( 2, 0 );

	if ( WSAStartup(wVersionRequested, &wsaData) != 0 ) {
		perror("WinSock DLL Startup initialize fail\n");
		return FAILURE;
	}


  /*
  ** INITIALIZE ALL DATA STRUCTURES
  */

  InitializeList();


  if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("comm-lib.c:: ServerInitialize(): socket create error");
      closesocket( server_fd );
      return( FAILURE );
    }

  memset((char *)&sin0, 0, sizeof(sin0));
  sin0.sin_family = AF_INET;
  sin0.sin_port   = htons((unsigned short )port_no);
  sin0.sin_addr.s_addr = htonl(INADDR_ANY);


  /*
  ** NOW BIND TO THE SOCKET
  */

  if( bind(server_fd, (struct sockaddr *)&sin0, sizeof(sin0)) < 0 )
    {
      perror("comm-lib.c:: ServerInitialize(): bind error");
      closesocket( server_fd );
      return ( FAILURE );
    }


  /*
  ** FIND OUT WHICH PORT WAS SELECTED BY THE SYSTEM
  */

  port_info_size = sizeof(struct sockaddr);
  getsockname( server_fd, (struct sockaddr *)&sin1, &port_info_size);
  printf("\nServer Port = %d\n", htons(sin1.sin_port) );

  listen(server_fd,20);
  printf("\nWaiting for Clients to Connect\n");

  FD_ZERO(&fdvar);
  FD_SET((unsigned)server_fd, &fdvar);
  maxfdpl1 = server_fd + 1;
  fflush(stdout);


  return( sin1.sin_port );

}


/**************************************************************************
**
** This functions initializes the server on random port.
** It returns the port.  It takes the application name as an argument.
** It also takes the hostname and the port number
** of the Name Server.
**
** The Name  Server is sent the port number and the application name of the
**
*****************************************************************************************/

int NewServerInitialize( char *app_name, char *server_host, int server_port )
{

  struct sockaddr_in sin0, sin1;
  int port_info_size, sys_sd;
  char host_name[HOSTNAMELEN];
  char buffer[SIZE_MSG_LEN];

   // Initialize the winsock
      WORD wVersionRequested;
      WSADATA wsaData;
  printf("%s NewServerInitialize programname: ", app_name);

	wVersionRequested = MAKEWORD( 2, 0 );

	if ( WSAStartup(wVersionRequested, &wsaData) != 0 ) {
		perror("WinSock DLL Startup initialize fail\n");
		return FAILURE;
	}

  /*
  ** INITIALIZE ALL DATA STRUCTURES
  */

  InitializeList();

  /*
  ** INITIALIZING SOCKET AND BINDING ADDRESS
  */

  if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("comm-lib.c:: NewServerInitialize(): socket create error");
      return( FAILURE );
    }

  memset((char *)&sin0, 0, sizeof(sin0));
  memset((char *)&sin1, 0, sizeof(sin1));
  sin0.sin_family = AF_INET;
  sin0.sin_port   = htons(0);
  sin0.sin_addr.s_addr = htonl(INADDR_ANY);

  if( bind(server_fd, (struct sockaddr *)&sin0, sizeof(sin0)) < 0 )
    {
      perror("comm-lib.c:: NewServerInitialize(): bind error");
      closesocket( server_fd );
      return ( FAILURE );
    }

  /*
  ** FIND OUT WHICH PORT WAS SELECTED BY THE SYSTEM
  */

  port_info_size = sizeof(struct sockaddr_in);
  getsockname( server_fd, (struct sockaddr *)&sin1, &port_info_size);
  printf("\nApp = %s\nport = %d\n", app_name, htons( sin1.sin_port ) );


  /*
  ** GET THS HOST NAME OF THIS SERVER TO REGISTER WITH NAME SERVER.
  */

  if (gethostname( host_name, sizeof(host_name))  < 0)
    {
	perror("comm-lib.c:: NewServerInitialize(): unable to gethostname");
        closesocket( server_fd );
        return( FAILURE );
    }

  /*
  ** CONNECT TO THE NAME DATA SERVER AND SEND THE DATA.
  */

  if( ( sys_sd = ClientInitialize( "other", server_host, server_port ) ) < 0 )
    {
      perror("comm-lib.c:: NewServerInitailize(): Unable to connect to Name Server.");
      return( FAILURE );
    }

  /*
  ** SEND THE REGISTER INFORMATION TO NAME SERVER
  */

  FlushBuff(buffer, sizeof(buffer));
  sprintf(buffer, "D %s %s %d ", app_name, host_name, htons(sin1.sin_port) );

  if( ( Send_Message( sys_sd, "other", buffer, sizeof( buffer ) ) ) < 0 )
    {
      perror("comm-lib.c:: NewServerInitialize(): Write to Name Server failed");
      closesocket( sys_sd );
      closesocket( server_fd );
      return( FAILURE );
    }

  closesocket( sys_sd );

  /*
  ** CLOSE THE SOCKET WITH NAME SERVER.
  */

  listen(server_fd,20);
  printf("\nWaiting for Clients to Connect\n");

  FD_ZERO(&fdvar);
  FD_SET((unsigned)server_fd, &fdvar);
  maxfdpl1 = server_fd + 1;
  fflush(stdout);


  return( sin1.sin_port );

}


/***************************************************************************
**  This function waits on 'server-init'ed socket for apps to
**  to connect and calls 'process_request' to take care of
**  the message.
**  args :: blockopt -> value 1: means blocking enabled.
**                               Will wait till message recd.
**                      value 0: blocking diabled. timeout value must be
**                               specified.
**          time -> the time in secs for select
*****************************************************************************/
int WaitForClients(int blockopt, int time, void (*req_proc)(char *, int, char *, int) )
{


  struct sockaddr sender_add;
  struct AppListElmt *run;
  struct timeval timeout_val, *timeout;
  struct message *recv_msg;
  int app_fd, fromlen,  value, size_of_data, temp_app_sock;
  char messg_buf[MAXBUFLEN],
       *gillian, source_appname[APPNAMELEN], buffer[SIZE_MSG_LEN];


  if(blockopt == NON_BLOCKING)
    {
      /*
      ** blocking disabled for select; setting time values
      */

      timeout_val.tv_sec = 0;
      timeout_val.tv_usec = time;
      timeout = &timeout_val;
    }
  else if(blockopt == BLOCKING)
    {
      /*
      ** blocking enabled:: select does not return till message arrives
      */

      timeout = NULL;
    }
  else
    {
      printf("\ncomm-lib.c:: WaitForClients(): incorrect usage of blocking flag (use 1 or 0)\n");
      return( FAILURE );
    }

  fromlen = sizeof(struct sockaddr);
  FlushBuff(messg_buf, MAXBUFLEN);

  if( select(maxfdpl1, &fdvar, NULL, NULL, timeout) < 0)
    {
      perror("comm-lib.c:: WaitForClients(): select error");
      return( FAILURE );
    }

  /*
  **  Check the Server's LISTEN port to see if there are
  **  any new apps waiting to be registered.
  */

  if(FD_ISSET(server_fd, &fdvar))
    {
      if((app_fd =  accept(server_fd, &sender_add, &fromlen)) < 0 )
	{
	  perror("comm-lib.c:: WaitForClients(): unable to 'accept':");
	  return( FAILURE );
	}

      recv_msg = (struct message *)messg_buf;

      if( ( value =  recv(app_fd, messg_buf, sizeof(messg_buf), 0) ) < 0)
	{
	  perror("comm-lib.c:: WaitForClients(): read failed");
	  return( FAILURE );
	}
      if (value == 0)
	{
	  /*
	  ** Case when The sender is dead.
	  */

	  return( FAILURE );
	}

      switch(recv_msg->type)
	{
	default:

	  RegisterApp(recv_msg, app_fd);
	  printf("\n %s connected \n", recv_msg->appname);
	  FlushBuff(buffer, sizeof( buffer ) );
	  sprintf( buffer,"E START %s",recv_msg->appname );
	  req_proc("SERVER", app_fd, buffer, sizeof(buffer) );
	  fflush(stdout);
	  break;

	  /*
	  **The Server's LISTEN port will accept only messages
	  ** with type = REG. All other messages are passed to the
	  ** server from the apps thru their dedicated channels that
	  ** are opened up when they register.
	  ** However if at a later time, the server needs to respond to
	  ** additional types, more case statements can be added
	  ** here.
	  */

	}  /** end of switch **/

    }     /** matched if( ..) part **/
  else
    {

      /*
      ** THe input might be on one of the socket FDs of the apps
      ** (i.e direct messages from Apps)
      */

      /*
      ** Search list of reg'd apps for whose FD has messgs
      */

      run = head;

      while( run != NULL )
	{

	  /*
	  ** check the sockets in the list for data.
	  ** The list is completely checked.
	  */

	  if( FD_ISSET(run->app_sock, &fdvar) )
	    {
	      gillian = ReceiveMessage(run->app_sock, source_appname, &size_of_data );
	      if( (gillian == NULL) && (size_of_data == FAILURE) )
		{
		  printf("\ncomm-lib.c:: WaitForClients():NULL and 0 condition - read failed \n");
		  return( FAILURE );
		}

	      /*
	      ** Consider the case when the sending app is dead
	      */

	      if( (gillian == NULL) && (size_of_data == DEAD) )
		{
		  printf("\n %s DISCONNECTED", run->appname);
		  FlushBuff(buffer, sizeof( buffer ) );
		  sprintf( buffer,"E DEAD %s",run->appname );
		  temp_app_sock = run->app_sock;
		  run = run->next;
		  UnRegisterApp(temp_app_sock);
		  req_proc("SERVER", temp_app_sock, buffer, sizeof(buffer) );
		  break;

		}
	      else
		if( (gillian == NULL) && (size_of_data == NODATA) )
		  {
		    printf("\n NODATA received from client\n");

		  }
		else
		  if( gillian != NULL )
		    {
		      /*
		      ** call the user defined function to process
		      ** the  recd messages.
		      */

		      req_proc(source_appname, run->app_sock, gillian, size_of_data);
		      free(gillian);
			  gillian = NULL;
		    }
		  else
		    printf("\ncomm-lib.c::  WaitForClients() :: receivemessg() returned NULL \n");
	    } /** End of 'if FD_ISSET' **/

	  run = run->next; /** Check the next socket in the list. **/

	} /** end of while( run != null ) **/

    } /** end of the else ....Now check select again ..**/

  /*
  ** Once the app has been registered, we put the fd for the app
  ** in the set of FDs to be monitored by the select().
  ** (For the else part this is still done to remove all
  **  unregistered sockets from the set )
  */

  InitFdset();
  FD_SET( (unsigned)server_fd, &fdvar );
  if( server_fd > maxfdpl1 )
     maxfdpl1 = server_fd +1;
  return( SUCCESS );

}/** end of the server_wait() **/



/***************************************************************************
**  This function waits on app sockets and calls function "req_proc".
**  These sockets desicriptors have to be added to the FD table by
**  calling Appropriate functions.
*****************************************************************************/
int WaitForApps(int blockopt, int time, void (*req_proc)(char *, int, char *, int) )
{

  struct timeval timeout_val, *timeout;

  struct AppListElmt *run;
  int size_of_data, temp_app_sock;
  char *gillian,
       source_appname[APPNAMELEN], buffer[SIZE_MSG_LEN];


  if(blockopt == NON_BLOCKING)
    {
      /*
      ** blocking disabled for select; setting time values
      */

      timeout_val.tv_sec = 0;
      timeout_val.tv_usec = time;
      timeout = &timeout_val;
    }
  else if(blockopt == BLOCKING)
    {
      /*
      ** blocking enabled:: select does not return till message arrives
      */

      timeout = NULL;
    }
  else
    {
      printf("\ncomm-lib.c:: WaitForApps(): incorrect usage of blocking flag (use 1 or 0)\n");
      return( FAILURE );
    }

  if( select(maxfdpl1, &fdvar, NULL, NULL, timeout) < 0)
    {
      perror("comm-lib.c:: WaitForApps(): select error");
      return( FAILURE );
    }


  /*
  ** THe input might be on one of the socket FDs of the apps
  ** (i.e direct messages from Apps)
  */

  /*
  ** Search list of reg'd apps for whose FD has messgs
  */

  run = head;
  while( run != NULL )
    {
      if(FD_ISSET(run->app_sock, &fdvar))
	{

	  /*
	  ** The second check is redundant but ITs there
	  ** Now we've located the app that's sent the message
	  */

	  gillian = ReceiveMessage(run->app_sock, source_appname, &size_of_data );
	  if( (gillian == NULL) && (size_of_data == FAILURE) )
	    {
	      printf("\nserve.c:: WaitForApps():NULL and 0 condition - read failed \n");
	      return( FAILURE );
	    }

	  /*
	  ** Consider the case when the sending app is dead
	  */

	  if( (gillian == NULL) && (size_of_data == DEAD) )
	    {
	      printf("\n %s DISCONNECTED", run->appname);
	      FlushBuff(buffer, sizeof( buffer ) );
	      sprintf( buffer,"E DEAD %s",run->appname );
	      temp_app_sock = run->app_sock;
	      run = run->next;
	      UnRegisterApp(temp_app_sock);
	      req_proc("SELECT-TABLE", temp_app_sock, buffer, sizeof(buffer) );
	      break;

	    }
	  else
	    if( (gillian == NULL) && (size_of_data == NODATA) )
	      {
		printf("\n No message received from client\n");

	      }
	    else
	      if( gillian != NULL )
		{
		  /*
		  ** call the user defined function to process
		  ** the  recd messages.
		  */

		  req_proc(source_appname, run->app_sock, gillian, size_of_data);
		  free(gillian);
		}
	      else
		printf("\ncomm-lib.c::  WaitForApps() :: receivemessg() returned NULL \n");
	} /* end if ISSET */

      run = run->next;
    } /** end while**/

/*
** Once the app has been registered, we put the fd for the app
** in the set of FDs to be monitored by the select().
** (For the else part this is still done to remove all
**  unregistered sockets from the set )
*/

InitFdset();
return( SUCCESS );

}/** end of the server_wait() **/


/****************************************************************************
** This Initializes a table so you could add application sd's to be monitored
** by select call. WaitForApps().
************************************************************************ ***/
void InitializeClientTable()
{
   FD_ZERO(&fdvar);
   InitializeList();
}



/************************************************************************
** This function re-initializes the 'fdset' that select call uses.
** All the sock desc in the app_list are re-entered into the list.
** This is done in each select cycle.
**************************************************************************/
void InitFdset()
{
  struct AppListElmt  *runner;

  FD_ZERO(&fdvar);

  runner = head->next;
  while(runner != NULL)
    {
      FD_SET((unsigned)runner->app_sock, &fdvar);
      if ( runner->app_sock >= maxfdpl1 )
	maxfdpl1 = runner->app_sock + 1;
      runner = runner->next;
    }

}



/****************************************************************************
** This function initializes the linked list which stores 'registered' app
** info .
************************************************************************ ***/
void InitializeList()
{
  head = (listelmt *)malloc(sizeof(listelmt));
  head->next = NULL;
  FlushBuff(head->appname, APPNAMELEN);
  FlushBuff(head->hostname, HOSTNAMELEN);
  head->app_sock=0;

}




/*********************************************************************
**  This function will be added to the end of the linked list. The
**  variables used here, 'end' is global.
**********************************************************************/
void AddToList(char * appname, char * hostname, int app_sock)
{
  struct AppListElmt * temp, * runner;

  /*
  ** Chanaged the way nodes are added to the list. Instead
  ** of attaching at the end now we are attaching after the first
  ** node. In some cases the data from last socket was never
  ** fetched because the first sockets were continuously busy.
  */

  if( head->next == NULL )
    runner = head;
  else
    runner = head->next;

  temp = (struct AppListElmt *)malloc(sizeof(struct AppListElmt));

  FlushBuff(temp->appname, APPNAMELEN);
  FlushBuff(temp->hostname, HOSTNAMELEN);

  memcpy(temp->appname, appname, APPNAMELEN);
  memcpy(temp->hostname, hostname, HOSTNAMELEN);
  temp->app_sock = app_sock;
  temp->next = NULL;

  temp->next = runner->next;
  runner->next = temp;

}




/*************************************************************
** Function to the search the global list pointed by head.
** (the appname is the search key )
***************************************************************/
int SearchList(char * appname, struct AppListElmt * dest_info)
{
  struct AppListElmt * runner;
  runner = head;

  while( strcmp(runner->appname, appname) != 0 )
    {
      runner = runner->next;
      if (runner == NULL) /** app not on list **/
	return( FAILURE );
    }

  memcpy((char *)dest_info, (char *)runner, sizeof(listelmt));


  return(SUCCESS);
}




/***************************************************************
**  Function to return the socket descriptor given the appname.
***************************************************************/
int GetAppSocket(char * appname, int *socket)
{
 struct AppListElmt  dest_info;
 int result;

 if( ( result = SearchList(appname, &dest_info) ) < 0 )
    {
      /*
      ** SearchList failed and the app is not registered
      */
      return(FAILURE);
    }

 *socket = dest_info.app_sock;

 return( SUCCESS );
}


/***************************************************************
**  Function Adds the socket in the server list to be monitored.
***************************************************************/
void AddAppSocket(char *appname, int socket)
{

  /*
  ** We are not using host information right now so I
  ** am just passing the word HOST.
  */

 AddToList( appname, "HOST", socket);
 InitFdset();

}

/*******************************************************
**  To remove a particular element from the list.
*******************************************************/
int RemoveFromList(int die_sock)
{
  struct AppListElmt * runner, * pre_runner;
  runner = head;
  pre_runner = runner;

  while( runner->app_sock != die_sock )
    {
      pre_runner = runner;

      runner = runner->next;
      if (runner == NULL) /** app not on list **/
	return(FAILURE);
    }

  pre_runner->next = runner->next;
  closesocket(runner->app_sock);

  free(runner);   /* annhilate element in the list */
  return( SUCCESS);
}



/****************************************************************************
** function that puts an application on the 'registered' list
*****************************************************************************/
void RegisterApp(struct message *recdmesg, int app_fd)
{
  AddToList(recdmesg->appname, recdmesg->hostname, app_fd);

}




/****************************************************************
** function to remove an appl for the 'registered' list
** ... IT scans the list using the appname as the identifier
** ... (..Check SearchList() )
*****************************************************************/
void UnRegisterApp(int appsock)
{
  /*
  ** This Fn. was changed to search with the appsock
  *
  */
  RemoveFromList( appsock );
}










