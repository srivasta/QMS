//                              -*- Mode: C++ -*- 
// QMS_Linked_List.h --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Sat Apr 21 14:20:42 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu May  3 14:55:49 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 47
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// $Id: QMS_Linked_List.h,v 1.3 2001/10/21 08:54:12 srivasta Exp $
//
/** @file QMS_Linked_List.h
 *  @ingroup MLD
 *  @brief The concrete implementation of a doubly linked list
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 *
 * This file includes QMS_Linked_List.cpp
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


#ifndef _QMS_LINKED_LIST_H_
#define _QMS_LINKED_LIST_H_

#include "Debug.h"
#include "QMS_MLD_Containers.h"

/// Used by visual C++ to export the member function
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

using namespace std;
/**
 *  @brief This class implements a double linked list
 *
 * This is one of the concrete container classes in the
 * multilevel data structure framework.  This implements most of the
 * common stl like members.
 */
template <class NodeType, class KeyType, class Lock>
class QMS_Linked_List : public QMS_MLD_Containers <NodeType , KeyType, Lock>
{
  friend class QMS_MLD_Factory<NodeType, KeyType, Lock>;
  friend class Linked_List_Factory<NodeType, KeyType, Lock>;
  
public:
  ///the default constructor
  Dllexport QMS_Linked_List(ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> > *levels_p = 0);
  /// Explicit constructor
  Dllexport QMS_Linked_List(QMS_MLD_Factory<NodeType, KeyType, Lock> *type_p, 
		  int (*cmp_p)(const KeyType&, const KeyType&));
  ///the copy constructor
  Dllexport QMS_Linked_List(QMS_Linked_List<NodeType, KeyType, Lock> &rhs);  
  /// the assignment operator
  Dllexport QMS_Linked_List<NodeType, KeyType, Lock> & 
  operator=(QMS_Linked_List<NodeType, KeyType, Lock> &rhs);

  /// The destructor
  Dllexport  virtual ~QMS_Linked_List();

  /// Adds <new_item> to the head of the list. Returns the new item
  /// that was inserted.
  Dllexport  virtual NodeType *insert_head (NodeType *new_item_p, KeyType *key_p);

  /// Adds <new_item> to the head of the list. Returns the new item
  /// that was inserted.
  Dllexport  virtual NodeType *insert_tail (NodeType *new_item_p, KeyType *key_p);

  /**
   * Removes and returns the first <item> in the list.  Returns
   * internal node's address on success, 0 if the queue was empty.
   * This method will *not* free the internal node.
   */
  Dllexport  virtual NodeType* delete_head (void);

  /**
   * Removes and returns the last <item> in the list.  Returns
   * internal nodes's address on success, 0 if the queue was
   * empty. This method will *not* free the internal node.
   */
  Dllexport  virtual NodeType *delete_tail (void);

  /// Delete the elment pointed to by delete_p
  Dllexport  virtual NodeType* delete_element(QMS_Node<NodeType, KeyType, Lock> *delete_p);
  /// Insert a new element at the position indicated
  Dllexport  virtual NodeType* insert_element(NodeType *new_item_p, KeyType *key_p,
					     QMS_Node<NodeType, KeyType, Lock> *before_p);

  /// Copy all the nodes from another list; deleting all local nodes
  Dllexport  virtual void copy_nodes(QMS_MLD_Containers<NodeType, KeyType, Lock> &copy);

protected:
  /// Delete all nodes, destroying the data  
  Dllexport  virtual void delete_nodes (void);
};	// end of class QMS_Linked_List

// Include the implementation
#include "QMS_Linked_List.cpp"

#endif /* _QMS_LINKED_LIST_H_ */
