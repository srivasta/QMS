/*                               -*- Mode: C -*- 
 * Message_Format_HW.h --- 
 * Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
 * Created On       : Fri Oct 12 17:32:08 2001
 * Created On Node  : ember.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Wed Oct 24 09:07:22 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 3
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


/** @file 
 *  @ingroup HelloWorld 
 *  @brief C++ representation of the payload data for the hello world probe
 *
 * $Id: Message_Format_HW.h,v 1.2 2001/12/02 03:30:24 srivasta Exp $
 */

#ifndef _MESSAGE_FORMAT_HW_H_
#define _MESSAGE_FORMAT_HW_H_


/// The guts of the message payload
struct Hello_World_Request 
{
  /// The first name of the requestor
  string firstname;
  // The last name of the requestor
  string lastname;
  /// Potential modifying action to be taken
  string action;
};

/// intermediate level of the heirarchy of the payload
struct helloWorld
{
  /// The guts of the message payload
  struct Hello_World_Request request;
};
  
/// The contents of the payload
struct hw_payload_data 
{
  /// Data contained in the message
  struct helloWorld data;
};

#endif /* _MESSAGE_FORMAT_HW_H_ */
