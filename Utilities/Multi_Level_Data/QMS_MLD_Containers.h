/*                               -*- Mode: C -*- 
 * QMS_MLD_Containers.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Fri Apr 20 11:44:01 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu May  3 16:45:08 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 78
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 *  $Id: QMS_MLD_Containers.h,v 1.3 2001/10/21 08:54:12 srivasta Exp $
 */
/** @file QMS_MLD_Containers.h
 *  @ingroup MLD
 *  @brief The abstract container for the multilevel datastructures
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 *
 * This file includes QMS_MLD_Containers.cpp
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



#ifndef _QMS_MLD_CONTAINERS_H_
#define _QMS_MLD_CONTAINERS_H_

#include "Debug.h"
#include "QMS_Type_list.h"
#include "QMS_Nodes.h"

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

using namespace std;
/**
 *  @brief This is the abstract superclass of Multi level containers
 *
 *  This class provides the common API for most of the containers in
 *  the multilevel data structure framework.  A multilevel data
 *  structure is, for example, can be like this:
 *    * The top level is a double linked list, 
 *    * each node of the doubly linked list is the rot of a red black tree
 *    * each node of the red black tree is the contains a stack
 * and so on. The implementation is provided by the concrete
 * containers, and the iterators are also only provided by the
 * concrete classes. 
 */
template <class NodeType, class KeyType, class Lock>
class QMS_MLD_Containers
{
  friend class QMS_Node<NodeType, KeyType, Lock>;
  friend class QMS_MLD_Factory<NodeType, KeyType, Lock>;
  friend class Linked_List_Factory<NodeType, KeyType, Lock>;
  friend class QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>;
  friend class QMS_Linked_List_Iterator<NodeType, KeyType, Lock>;
  friend class QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>;

public:
  ///the default constructor
  Dllexport QMS_MLD_Containers(ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> > *levels_p = 0);
  /// explicit constructor
  Dllexport QMS_MLD_Containers(QMS_MLD_Factory<NodeType, KeyType, Lock> *type_p, 
		     int (*cmp_p)(const KeyType&, const KeyType&)); 

  /// The destructor
  Dllexport  virtual ~QMS_MLD_Containers(){};  // the destructor

  /// Set the comparison function to compare keys at this level
  Dllexport void set_cmp(int (*cmp_ptr)(const KeyType&, const KeyType&));
  /// Set the object factory to use in the member nodes
  Dllexport void set_type(QMS_MLD_Factory<NodeType, KeyType, Lock> *type_p);
  /// set the linked list describing the levels below this one
  Dllexport void set_sublevel
    (ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> >  
     *levels_p);
  /// Initialize the object
  Dllexport void set
    (ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> > 
     *levels_p);
  
  // = Additional utility methods.
  /// Is the container empty?
  Dllexport virtual const bool is_empty (void) const;
  /// Is the container full? Usually no, since most containers are open-ended
  Dllexport virtual const bool is_full (void)  const;
  /// The number of items in the container.
  Dllexport virtual const size_t size (void)   const;
  /// Copy all the nodes from another list; deleting all local nodes
  Dllexport  virtual void copy_nodes(QMS_MLD_Containers<NodeType, KeyType, Lock> &copy) = 0;

  /// Lock the node for reading
  Dllexport  int get_read_lock(void);   
  /// Lock the node for writing
  Dllexport  int get_write_lock(void);   
  /// release the ock
  Dllexport  int release_lock(void); 

protected:
  /// A lock to protect the data members of the object
  mutable Lock lock_;
  /// A pointer to the (dummy) root/head of the container
  QMS_Node<NodeType, KeyType, Lock> *head_p_;

  /// Pure virtual method used to delete all nodes in the container
  virtual void delete_nodes(void) = 0;


  /// A linked list cointaining details of levels deeper in the data structure
  ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> > sub_levels_;
  /// An object factory to produce the levels deeper in the structure.
  QMS_MLD_Factory<NodeType, KeyType, Lock> *type_p_;
  /// The comparison function used to compare the keys
  int (*cmp_)(const KeyType&, const KeyType&);

  /// Size of this list.
  size_t size_;
 };	// end of class QMS_MLD_Containers

// include the implementation
#include "QMS_MLD_Containers.cpp"

#endif /* _QMS_MLD_CONTAINERS_H_ */
