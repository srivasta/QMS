// get_data_GCP.cpp
/*********************************************************************
 * Copyright (c) 2001, System/Technology Development Corporation .
 *                
 * Filename:      get_data_GCP.cpp
 * Version:       
 * Description:   The data function of the Generic Continuous Probe
 *                
 * Author:        Shivakumar C. Patil (shivakumar.patil@stdc.com)
 * Created at:    Sat Dec  1 14:18:52 2001
 * Modified by:   Amarendranath Vadlamudi <nath@vedam>
 * Modified at:   Sat Dec  1 14:31:34 2001
 * Status:        Experimental, do not distribute.
 * Update count:  2
 ********************************************************************/

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



/** @file get_data_GCP.cpp
 *  @ingroup GenericProbe
 *  @brief Contains implementation of get_data and xml_insert functions.
 *
 * The external interface for the QMS probe system is the get_data
 * function. This gets the Metrics information and prints it in XML  
 * format to the standard out. 
 *
 */

#include <cstdio>
#include <cstring>
#include "get_data_GCP.h"


#if defined(_WIN32)
#define snprintf _snprintf
#endif


const char *graph_payload_fmt = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
  <genericCProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/Continuous/GenericProbe\"\n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/Continuous/GenericProbe\n\
      genericCProbe.xsd\">\n\
      <probeData>\n\
        <dataid>%ld</dataid>\n\
        <response>%s</response>\n\
      </probeData>\n\
    </genericCProbe>\n\
";

const char *graph_payload_data = "Generic Continuous Probe is successfully executing";


/** @ingroup GenericProbe */


/**
 * @brief Gets Metrics information and returns it in XML format.
 * @param args List of command line arguments.
 * @return returns a pointer to XML document.

 *
 */
char *
get_data(void *args)
{
 
  char *message = new char[BUFSIZ+8192];
  static long data_id = 0;
/*
  sprintf(message, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n <remosProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/RemosProbe\"\n   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n   xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"\n   xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema qmsEvent.xsd\n   http://www.stdc.com/2001/QMS/Probes/RemosProbe remosProbe.xsd\">\n  <bandwidthData>\n\t<flowData>\n\t  <dataID>%ld</dataID>\n\t  <source>HostOne</source>\n\t  <destination>HostTwo</destination>\n\t  <latency>0.000000</latency>\n\t  <available>9999268.800000</available>\n\t</flowData>\n  </bandwidthData>\n", data_id++ );
*/

  snprintf (message, BUFSIZ+8192, graph_payload_fmt, data_id++, graph_payload_data);
  strcat(message,STDC::QMS::Citizen::delimiter);
  strcat(message, "\n");

  return message; 

}
