//get_data_ffd.cpp
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

/** @file get_data_ffd.cpp
 *  @ingroup GenericProbe
 *  @brief Contains implementation of get_data and xml_insert functions.
 * The external interface for the QMS probe system is the get_data
 * function. This gets the Metrics information and prints it in XML
 * format to the standard out.
 *
 */


#include "get_data_ffd.h"
#include "Instrumentation.h"
#include "Debug.h"
#include <cstring>



char *
get_data_ffd (void *)
{

   ssize_t n;
   char buff[BUFSIZ];
   char *tmp_p = new char[BUFSIZ];
   int readfd;

   if ( (mkfifo ( READ_FIFO, FILE_MODE) < 0) && (errno == EEXIST) )
        DEBUG1 (2, "The fifo ->%s already exists\n", READ_FIFO);
   else
        perror ("mkfifo");

   if ( (readfd = open (READ_FIFO, O_RDONLY, 0)) < 0 )
        perror ("open");

   if ( (n = read ( readfd, buff, BUFSIZ)) > 0 )
   {
        if (close (readfd) < 0 )
                perror ("close");
        buff[n] = 0;
        strcpy(tmp_p, buff);
        strcat(tmp_p, STDC::QMS::Citizen::delimiter);
        strcat(tmp_p, "\n");

        return (tmp_p);
   }
   else {
            //fprintf (stdin, "stop\n");
            exit(1);
        }

}
