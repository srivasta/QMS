// get_data_O.cpp
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



/** @file get_data_O.cpp
 *  @ingroup Probes
 *  @brief Contains implementation of the guts of a Remos Probe
 *
 * The external interface for the QMS probe system is the get_data
 * function. This gets the Metrics information and prints it in XML  
 * format to the standard out. 
 * 
 */

#include <cstdio>
#include "ace/OS.h"
#include "get_data_O.h"

/** @ingroup Probes */

/**
 * @brief prints the XML Metrics information to the standard out.
 * @param  request_id Any user defined parameter.
 * @param  data_id Any user defined parameter.
 * @param sleep_interval Any user defined parameter.
 * @return NONE.
 *
 *
 */

void
get_data(char *src, char *dest)
{
  ssize_t n;
  char message[BUFSIZ];
  static long data_id = 0;

  sprintf(message, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n <remosProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/RemosProbe\"\n   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n   xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"\n   xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema qmsEvent.xsd\n   http://www.stdc.com/2001/QMS/Probes/RemosProbe remosProbe.xsd\">\n  <bandwidthData>\n\t<flowData>\n\t  <dataID>%ld</dataID>\n\t  <source>%s</source>\n\t  <destination>%s</destination>\n\t  <latency>0.000000</latency>\n\t  <available>9999268.800000</available>\n\t</flowData>\n  </bandwidthData>\n", data_id++, src, dest );

  n = strlen(message);

  if ( ACE_OS::write (ACE_STDOUT, message, n) != n)
    ACE_OS::perror ("Probe: error in writing to STDOUT");

}
