/*****************************************************************************
**
** $Id: testcom-lib.h,v 1.1 2001/12/10 06:26:21 spatil Exp $
**
******************************************************************************/

#ifndef TEST_COMM_LIB_H
#define TEST_COMM_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

#ifndef __AFXSOCK_H__
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include<memory.h>
#include<winbase.h>

/*
** CONSTANTS
*/

#define      APPNAMELEN         128
#define      HOSTNAMELEN        128
#define      DATALEN            1024
#define      SIZE_MSG_LEN       256

#define      FAILURE            -1
#define      SUCCESS             0

#define	     FALSE		 0
#define	     TRUE		 1

#define      NODATA             -2
#define	     DEAD		-3

#define      NON_BLOCKING        0
#define      BLOCKING            1


/*
**  MESSAGE TYPES
*/

#define   REG          1
#define   UNREG        2



/*
** STRUCTURE USED FOR INITIALIZING.
*/

struct message
{

  char type;
  char appname[APPNAMELEN];
  char hostname[HOSTNAMELEN];
  char data[DATALEN];

};

#define    MAXBUFLEN   sizeof(struct message)


/*
** STRUCTURE TO KEEP A LIST OF ALL THE REGISTERED CLIENTS.
*/

struct AppListElmt
{
  char appname[APPNAMELEN];
  char hostname[HOSTNAMELEN];
  int app_sock;

  struct AppListElmt * next;

};

typedef struct AppListElmt listelmt;

/*
** POINTER TO ALWAYS POINT AT THE TOP OF THE LIST.
*/



/*
** STANDARD FUNCTIONS USED BY CLIENTS AND SERVERS.
*/
#ifdef __cplusplus
extern "C" {
#endif

void ErrHandler ();
void PipeHandler( int temp );
void FlushBuff( char *buff, int size );
int  Send_Message( int sd, char *appname, char *msg, int size );
char *ReceiveMessage( int sd, char *appname, int * size_of_msg );

/*
** CLIENT FUNCTIONS
*/

int ClientInitialize( char *appname, char *server_host, int server_port );
int NewClientInitialize( char *appname, char *server_name, char *server_host, int server_port );
void AddAppSocket( char *appname, int socket );
void InitializeClientTable();
int WaitForApps(int blockopt, int time, void (*req_proc)(char *, int, char *, int) );

/*
** SERVER FUCNTIONS.
*/

int ServerInitialize(int port_no);
int NewServerInitialize( char *name, char *server_name, int server_port );
int WaitForClients( int blockopt, int time, void (*req_proc)(char *, int, char *, int ) );
int GetAppSocket( char *appname, int *socket );
void InitFdset();

/*
** REGISTERING AND UNGREGISTERING OF APPLICATION
*/


void RegisterApp( struct message * mesgrecvd, int app_fd );
void UnRegisterApp( int appsock );


/*
** FUNCTIONS TO HANDLE THE LIST THAT KEEPS TRACK OF REGISTERED APPLICATIONS.
*/

void InitializeList();
void AddtoList( char * appname, char * hostname, int app_sock );
int  RemoveFromList( int appsock );
int  SearchList( char *appname, struct AppListElmt *dest_info );

#ifdef __cplusplus
}
#endif

#endif

/*
** End of comm-lib.h code
*/


