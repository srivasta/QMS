//                              -*- Mode: C++ -*- 
// .h --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Sun Feb  4 17:58:43 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Mar  6 12:40:55 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 6
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// 
// $Id: Backend.h,v 1.2 2001/10/21 08:54:12 srivasta Exp $

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


#ifndef BACKEND_H
#define BACKEND_H

/** @file Backend.h
 *  @ingroup Backend
 *  @brief A generic interface to persistent local storage
 *
 */

/** @defgroup Backend QMS BE - A generic interface to persistent local storage
 *  @ingroup Utilities
 * 
 *  These sets of modules provide a consistent and polymorphic set of
 *  interfaces to a wide variety of persistent storage objects, and is
 *  designed to be useful for any QMS citizen or client. 
 *
 *  Broadly, these modules shall be divided into two groups, one
 *  related to storage into back ends, with the relevant use cases,
 *  and a second set related to querying and retrieval of data from
 *  these back ends. 
 *
 *  There are a number of classes of back end storage entities
 *  envisaged as being hooked into these modules, starting with simple
 *  files, relational databases, and LDAP servers. Indeed, any storage
 *  method able to deal with the storage and retrieval of chunks of
 *  text can be seen as a candidate for plugging into these modules.
 *
 */


/** @defgroup BE_Retrieve QMS BE Retrieve - Modules related to querying and retrieving data from local storage
 *  @ingroup Backend 
 *
 *  These modules implement interfaces to querying and retrieving data
 *  from the back end objects that the @ref BE_Store modules stored
 *  them in. 
 */


/** @defgroup BE_Store QMS BE Store - Modules related to storing data to local storage
 *  @ingroup Backend 
 *
 *  These modules implement interfaces to storing data to persistent
 *  storage. All these modules have to implement the following use
 *  cases (See http://images/BackendStorageUseCase.png)
 *     - Create  Create a new back end object, like a new file or table
 *     - Save    Save a message into the back end object
 *     - Erase   Truncate or erase the back end object
 *     - Close   Close the back end object.
 *     - Copy    Copy the current back end object into another, saving
 *               the contents
 *     - Destroy Destroy the beck end object, for example by deleting
 *     - Exit    The destructor. Return any resources allocated
 *     - Get BE Attributes 
 *     - Set BE Attribute  
 */

#endif // BACKEND_H
