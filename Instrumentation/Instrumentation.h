//                              -*- Mode: C++ -*- 
// Instrumentation.h --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Mon Feb  5 01:30:06 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Nov 27 16:11:50 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 4
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// 
// $Id: Instrumentation.h,v 1.9 2001/12/04 00:44:32 spatil Exp $

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


#ifndef INSTRUMENTATION_H
#define INSTRUMENTATION_H

/** @file Instrumentation.h
 *  @ingroup QMS
 *  @brief Instrumentation - QoS intrumentation that uses QMS
 *
 */


/** @defgroup Instrumentation Instrumentation - QoS intrumentation that uses QMS
 *  @ingroup  QMS
 *
 *  By definition, Instrumentation is an integral part of QMS. QMS
 *  provides a mechanism for data providers to publish their presence
 *  on the grid, and provides data consumers to subscribe to, and even
 *  request tailored data from, such consumers.
 *
 *  QMS Instrumentation is implemented as a Sensor/Probe design
 *  pattern. 
 *
 *  QMS provides a standard, flexible interface for both the
 *  interactions between the data providers and consumers, as well as
 *  a set of standard XML formats for encapsulation of the data
 *  generated.
 *
 *  By crafting standard QMS sensors that deploy or interface with the
 *  underlying probes, QMS provides standard sets of capabilities
 *  often not present in the underlying probes themselves.
 */
namespace STDC
{
  namespace QMS
  {
    namespace Citizen
    {
      /// The delimiter used by probes to separate messages sent to sensors
      static const char *delimiter = 
            "<!-- ******_PROBE_MESSAGE_DELIMITER_****** -->";
    };
  };
};  


#endif // INSTRUMENTATION_H
