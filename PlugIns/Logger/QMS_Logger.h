//                              -*- Mode: C++ -*- 
// QMS_Logger.h --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Mon Feb  5 12:19:49 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Mon Feb  5 14:09:53 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 2
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// 
// $Id: QMS_Logger.h,v 1.3 2001/10/21 08:54:10 srivasta Exp $

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


#ifndef QMS_LOGGER_H
#define QMS_LOGGER_H

/** @file QMS_Logger.h
 *  @ingroup Logger 
 *  @brief The QMS flexible event logging service
 *
 */

/** @defgroup Logger QMS Logger -- flexible data recorder and logger
 *  @ingroup Facilities
 *
 * Goals and Requirements:
 *  - The Logger should listen for service requests
 *  - The Logger should be able to log QMS events pushed on to to the
 *    CORBA event channel
 *  - One should be able to create multiple independent logs using the
 *    logger, each log being associated with a separate storage
 *    back-end, and an ability to filter the recorded events by event
 *    type and supplier id
 *  - One should be able to modify attributes for each log, including
 *    security policies, back-ends, and filters 
 *  - The Logger must be a well behaved citizen in the QMS toolkit 
 *  - The logger must be able to report performance metrics and other
 *    statistics 
 *  - The logger should be a managed QMS component, and present a management   
 *    interface that allows, at a minimum, start, stop, pause, and resume      
 *    commands, in addition to providing the QMS Control and Command
 *    interfaces common to all citizens
 *
 */

#endif // QMS_LOGGER_H
