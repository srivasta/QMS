/*                               -*- Mode: C -*- 
 * QMS_MLD.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Tue May  1 10:55:34 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu May  3 15:17:01 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 5
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


/** @file QMS_MLD.h
 *  @ingroup MLD
 *  @brief The top level file that includes all the individual elemens
 *  of the MLD framework
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 *
 * This file includes all hte header files required for the
 * intantiation of any multilevel data structure.
 */

/**
 * @defgroup MLD Multi level data structures
 * @ingroup Utilities
 *
 * In several situations, one needs to store data whose innate model
 * has layers, or is deeply nested. The framework created by this
 * Multi level data structure module allows for an infinitely deep
 * nested set of data structures.  One can have a linked list of
 * elelments, each elemnt contiaining an rbtree of elelmets, each of
 * which has a linked list ....
 *
 * The framework also provides parametrerized locking, allowing the
 * client to either use strict locking, or, for performance, use
 * ACE_Null_Mutex to do away with any overhead created by the locking
 * mechanism. 
 *
 * The test files testLinked_list.cpp and instantiate.cpp illustrate
 * how one can use this module.
 */

#ifndef _QMS_MLD_H_
#define _QMS_MLD_H_

#include "QMS_Type_list.h"
#include "QMS_Nodes.h"
#include "QMS_MLD_Factory.h"
#include "QMS_MLD_Containers.h"
#include "QMS_Linked_List_Iterators.h"
#include "QMS_Linked_List.h"


#endif /* _QMS_MLD_H_ */
