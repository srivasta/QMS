/*                               -*- Mode: C -*- 
 * QMS_Nodes.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Thu Apr 19 15:04:56 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu May  3 16:46:00 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 48
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 *   $Id: QMS_Nodes.h,v 1.3 2001/10/21 08:54:13 srivasta Exp $
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



#ifndef _QMS_NODES_H_
#define _QMS_NODES_H_

/** @file QMS_Nodes.h
 *  @ingroup MLD
 *  @brief Defines the nodes used in the multilevel datastructures
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 *
 * This file includes QMS_Nodes.cpp
 */

#include "Debug.h"
#include "QMS_Type_list.h"

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

using namespace std;

// forward references
template <class NodeType, class KeyType, class Lock> class QMS_MLD_Containers;

/// node colours, needed for Red-Black trees
enum NODE_COLOUR  { BLACK, RED };

/**
 *  @brief The default node for the container classes
 *
 * This node is a container that provides the support needed by the
 * multilevel data structures and the algorithms that act on them (for
 * example, pointers to siblings, and parents, node colour, etc).
 * Objects of this class, in turn, act as containers for the the user
 * data and keys to be stored in the data structure. 
 *
 * Objects of this class are elements in a multilevel data structure,
 * so are prepared to be the root of the next level of the data
 * structure. 
 */
template <class NodeType, class KeyType, class Lock>
class QMS_Node
{
  friend class QMS_MLD_Containers<NodeType , KeyType, Lock>;
  friend class QMS_Linked_List<NodeType, KeyType, Lock>;
  friend class QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>;
  friend class QMS_Linked_List_Iterator<NodeType, KeyType, Lock>;
  friend class QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>;
  
public:
  ///the default constructor
  Dllexport  QMS_Node();   
  /// The explicit constructor            
  Dllexport  QMS_Node(NodeType *node_p, KeyType *key_p, 
	   QMS_MLD_Containers<NodeType, KeyType, Lock> *root_p, 
	   QMS_Node<NodeType, KeyType, Lock> *parent_p = 0);
  ///the copy constructor
  Dllexport  QMS_Node(const QMS_Node<NodeType, KeyType, Lock>& rhs);

  /// the assignment operator
  Dllexport  QMS_Node<NodeType, KeyType, Lock>& 
    operator=(QMS_Node<NodeType, KeyType, Lock>& rhs);             
  
  /// Return the pointer to contained data
  Dllexport  NodeType *get_data(void);
  /// Return the pointer to contained key
  Dllexport  KeyType *get_key(void);
  /// Return a pointer to the next level of data structure
  Dllexport  QMS_MLD_Containers<NodeType, KeyType, Lock> *get_container(void);
  
  /// the destructor
  Dllexport  ~QMS_Node();                  

  /// Lock the node for reading
  Dllexport  int get_read_lock(void);   
  /// Lock the node for writing
  Dllexport  int get_write_lock(void);   
  /// release the lock
  Dllexport  int release_lock(void); 

protected:
  /// A lock to prevent corruption of internal data
  mutable Lock lock_;
  /// Pointer to the data contained
  NodeType *node_p_;
  /// The key used to access the data
  KeyType *key_p_;
  /// Pointer to the container object to which this node belongs
  QMS_MLD_Containers<NodeType, KeyType, Lock> *root_p_;
  /// Pointer to deeper levels of the data structure
  QMS_MLD_Containers<NodeType, KeyType, Lock> *data_container_p_;
  /// pointer to the previous element
  QMS_Node <NodeType, KeyType, Lock> *prev_p_;
  /// pointer to the next element
  QMS_Node <NodeType, KeyType, Lock> *next_p_;
  /// pointer to the parent element, if relevant
  QMS_Node <NodeType, KeyType, Lock> *parent_p_;
  /// Colour of this node, needed for Red-Black trees
  enum NODE_COLOUR colour_;
};	// end of class QMS_Node

// include implementation
#include "QMS_Nodes.cpp"
#endif /* _QMS_NODES_H_ */
