/*                               -*- Mode: C -*- 
 * Continuous.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Fri Aug 17 14:52:08 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Sat Oct 20 03:28:21 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 2
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
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


#ifndef _CONTINUOUS_H_
#define _CONTINUOUS_H_

/** @file Continuous.h
 *  @ingroup Probes
 *  @brief Continuous probes
 *
 */

/** @defgroup Continuous Continuous Probes
 * @ingroup Probes
 *
 *
 * The Continuous Probe is capable of providing the Metrics in a 
 * continuous manner. 
 * 
 *  This consists of two threads -> 1) Worker thread and 2) Listener thread.
 *  
 *  Listener Thread:- The Listener thread listens for commands on the 
 *        standard input and passes that information to the 
 *        Worker thread using an enum structure.
 *
 *  Worker Thread:- The Worker thread calls the get_data function at the 
 *      specified intervals. This thread is resonsible for 
 *      actions like Starting,Pausing, Resuming and Stopping 
 *      the Probe. 
 *
 * Primary functions of Continuos Probe are 
 * 
 *   -# Supports QMS Comands like Start, Pause ,Resume and Stop.
 *   
 *   -# Continuously monitors the standard input for commands 
 *    mentioned above.
 * 
 *   -# Converts the Metrics information to XML format.
 * 
 *   -# Continuously prints the Metrics information in the form
 *    of XML document on the standard output at the given 
 *    interval.
 *
 *
 */



#endif /* _CONTINUOUS_H_ */
