
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


#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define WRITE_FIFO	"/tmp/FFD_FIFO"
#define FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void FIFO_write (int);

int
main(int argc, char **argv)
{
   int writefd;
	
   if ( (mkfifo ( WRITE_FIFO, FILE_MODE) < 0) && (errno != EEXIST) )
	printf ("can't create %s\n", WRITE_FIFO);

   writefd = open (WRITE_FIFO, O_WRONLY, 0);
   FIFO_write( writefd );
   
   close(writefd);
   unlink(WRITE_FIFO);
   exit(0);

}

void
FIFO_write(int wfd)
{

   ssize_t n;
   char buff[BUFSIZ];
 
   for (int i=0; i < 1000 ; i++ )
   {
      sprintf(buff, "The value of i->%d\n", i);
      n = strlen(buff);
      if ( write (wfd, buff, n) != n)
         perror ("dummyFFD write failed ");
      printf("buff->%s", buff);
      sleep(1);
   }

}
