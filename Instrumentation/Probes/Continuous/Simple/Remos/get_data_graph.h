// get_data_graph.h
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


#ifndef GET_DATA_GRAPH_H
#define GET_DATA_GRAPH_H

/** @file get_data_graph.h
 * @ingroup RemosProbes
 * @brief Contains implementation of Remos Continuous Graph Probe.
 * 
 *  The Remos interface is a uniform way for applications to monitor a
 *  network and the hosts connected to it.  The Remos papers are
 *  available from the Remulac web page:
 *  http://www.cs.cmu.edu/~cmcl/remulac/index.html.
 *
 *  This sensor inserts a probe into the Remos system with the query
 *  parameters as requested. Additionally, this sensor provides a
 *  facility to periodically monitor the network (and replay the
 *  original query as requested).
 */

extern "C" {
#include "remos.h"
}


/// Using standard C++ namespace.
#include <iostream>
using std::cout;
#include <string>
using std::string;

/** @def        MAXNAMELEN
 *  @brief      Defines the maximum length of a node name in characters.
 */
#ifndef MAXNAMELEN
# define MAXNAMELEN 4095
#endif

/** @def        MAX_NODES
 *  @brief      Defines the maximum number of nodes that we can have.
 */
#define MAX_NODES 20

/** Probe for network graph topology  */
char * get_data (void *);

/** convert from a string to array of char pointers to hostnames */
int StringToCharHosts (string, char *[]);

#endif /* GET_DATA_GRAPH_H */
