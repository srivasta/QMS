/*                               -*- Mode: C -*-
 * Remos_Instrumentation.h ---
 * Author           : Manoj Srivastava ( srivasta@ember )
 * Created On       : Fri Oct 27 11:26:02 2000
 * Created On Node  : ember
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Tue Mar  6 12:22:04 2001
 * Last Machine Used: ember.stdc.com
 * Update Count     : 28
 * Status           : Unknown, Use with caution!
 * HISTORY          :
 * Description      :
 * $Id: Remos_Instrumentation.h,v 1.11 2001/10/21 08:54:09 srivasta Exp $
 */

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



#ifndef REMOS_INSTRUMENTATION_H
# define REMOS_INSTRUMENTATION_H

/** @defgroup       Remos A QMS Sensor that delivers Remos data
 *  @ingroup        Sensors
 *
 *  The Remos interface is a uniform way for applications to monitor a
 *  network and the hosts connected to it.  The Remos papers are
 *  available from the Remulac web page:
 *  http://www.cs.cmu.edu/~cmcl/remulac/index.html.
 *  Another reference of interest is the Remos Technical Report with a
 *  description of it's API at the following URL:
 *  http://www.cs.cmu.edu/~cmcl/remulac/remos-tr-2.ps
 *
 *  This sensor inserts a probe into the Remos system with the query
 *  parameters as requested. Additionally, this sensor provides a
 *  facility to periodically monitor the network (and replay the
 *  original query as requested).
 *
 * Primary functions of Remos are
 *
 *     -# Status - Provide information on host network characteristics
 *        and simple node-to-node path characteristics
 *     -# Flow Information - Given a set of desired network bandwidth
 *        flows for an application, Remos will return which of them can be
 *        supported by the network.
 *     -# Topology - In order to accomplish the above two, Remos builds
 *        a virtual (logical) topology of the network as is visible to it.
 *
 * Strengths:
 *
 *   -  Currently based on SNMP - The software is deployed as
 * 	sets of SNMP data collectors deployed on local subnets.
 * 	This enables rapid data collection. Other data
 * 	collectors are in the works but none are available right now.
 *   -  Enables Wide-area info - WAN collectors use
 * 	benchmarking techniques using tools like "traceroute"
 * 	and "NetTest" to get the wide area connectivity info. So
 * 	it can still be used when SNMP access to ISP routers
 * 	etc.. is not available.
 *   -  Scalable - Multiple SNMP/WAN data collectors feed
 * 	one or more master collector per administrative domain
 * 	that collects, analyzes and serves as contact point for
 * 	access to the data.
 *   -  Topology Maps - Generates useful topology maps using
 * 	SNMP queries on the intermediate devices.
 *   -  Portable - The collectors are implemented using Java and
 * 	hence are portable. The modeler which is what we'll
 * 	interface with is in C. It should not be an integration
 * 	problem.
 *
 * Weaknesses:
 *
 *   -  Based on SNMP - Requires that all hosts/switches/routers
 * 	in the environment support SNMP and have community
 * 	"public" access enabled.
 *   -  Wide Area Info - Since the wide area collectors do not
 * 	have access to the SNMP counters, the data is actually
 * 	user-level benchmarking and is not as accurate.
 *   -  Wide Area data collection - Since it's benchmarking with
 * 	tools, this generates high loads on routers and is
 * 	resource expensive.
 */

/** @file Remos_Instrumentation.h
 *  @ingroup        Remos
 *  @brief Contains implementation of a QMS Sensor that delivers Remos data
 */

/** @def	MAX_NODES
 *  @brief	Defines the maximum number of nodes that we can have.
 */
#define MAX_NODES 20

/** @def	DEFAULT_SLEEP
 *  @brief	The default amount of sleep time in miliseconds.
 */
#define DEFAULT_SLEEP 2


/** @def	MAXNAMELEN
 *  @brief	Defines the maximum length of a node name in characters.
 */
#ifndef MAXNAMELEN
# define MAXNAMELEN 4095
#endif


/** Probe for network topology  */
int getGraphInfo(char *node_names[], int num_nodes, int request_id);

/** Probe for network flow information  */
int getFlowInfo(char *node_names[], int num_nodes, int request_id);

/**  This is the call back function used when data is recieved */
void Remos_CallBack(const string &query, void * arg_p = 0);

/** convert from a string to char pointer */
int StringToCharHosts(string hostnames, char *node_name[]);

/** Write a variable argument formatted error message */
void errMsg(const char *format,...);


#endif /* REMOS_INSTRUMENTATION_H */
