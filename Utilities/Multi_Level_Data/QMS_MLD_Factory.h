/*                               -*- Mode: C -*- 
 * QMS_MLD_Factory.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Mon Apr 23 22:17:31 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu May  3 16:49:40 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 50
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * $Id: QMS_MLD_Factory.h,v 1.2 2001/10/21 08:54:12 srivasta Exp $
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


#ifndef _QMS_MLD_FACTORY_H_
#define _QMS_MLD_FACTORY_H_
/** @file QMS_MLD_Factory.h
 *  @ingroup MLD
 *  @brief Object factories used for creating multilevel data structures
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 */

#include "ace/Containers_T.h"

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

using namespace std;

// Forward declarations
template <class NodeType, class KeyType, class Lock> class Linked_List_Factory;
template <class NodeType, class KeyType, class Lock> class QMS_Linked_List;
template <class NodeType, class KeyType, class Lock> class QMS_Linked_List_Iterator;
template <class NodeType, class KeyType, class Lock> class QMS_Linked_List_Iterator_Base;
template <class NodeType, class KeyType, class Lock> class QMS_Linked_List_Reverse_Iterator;
template <class NodeType, class KeyType, class Lock> class QMS_MLD_Containers;
template <class NodeType, class KeyType, class Lock> class QMS_MLD_Factory;
template <class NodeType, class KeyType, class Lock> class QMS_Node;
template <class NodeType, class KeyType, class Lock> class QMS_Sub_Type_Element;


/** @class QMS_MLD_Factory
 *  @ingroup MLD
 *  @brief This class is an superclass for various concrete factories
 *
 * This class serves as a base for concrete factories. A template
 * factory, though attractive in that it would not require a concrete
 * factory class for every multilevel container class implemented, turned
 * out to be quite ugly, since factory objects are member objects of the
 * very container objects they create. 
 */
template <class NodeType, class KeyType, class Lock>
class QMS_MLD_Factory
{
 public:
  /// A virtual destructor
  virtual ~QMS_MLD_Factory(){};
  /// A pure virtual create object method, instantiated by concrete factories
  virtual QMS_MLD_Containers<NodeType, KeyType, Lock> *create_object 
    (ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> > *levels_p) = 0;
};	// end of class QMS_MLD_Factory


/** @class Linked_List_Factory
 *  @ingroup MLD
 *  @brief This class is a concrete factory that produces a linked list
 *
 * This class is an object factory that creates a doubly linked list
 * that is a component of a multilevel data structure. 
 */
template <class NodeType, class KeyType, class Lock>
class Linked_List_Factory : public QMS_MLD_Factory<NodeType, KeyType, Lock>
{
public:
  /// Empty virtual destructor function
  virtual ~Linked_List_Factory(){};
  /// The work horse function that creates the linked list object
  Dllexport  virtual QMS_MLD_Containers<NodeType, KeyType, Lock> 
    *create_object
    (ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> > 
     *levels_p)
    { 
      return new QMS_Linked_List<NodeType, KeyType, Lock>(levels_p);
    }
};	// end of class QMS_MLD_Factory

#endif /* _QMS_MLD_FACTORY_H_ */
