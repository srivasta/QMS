//                              -*- Mode: C++ -*- 
// QMS_Nodes.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Mon Apr 23 15:15:24 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Aug 14 10:24:11 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 45
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// $Id: QMS_Nodes.cpp,v 1.2 2001/10/21 08:54:12 srivasta Exp $
// 

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


/// RCS version string
//static const char* version = "$Id: QMS_Nodes.cpp,v 1.2 2001/10/21 08:54:12 srivasta Exp $";


/** @file QMS_Nodes.cpp 
 *  @ingroup  MLD
 *  @brief Implmentation of the generic node for the multilevel data structure 
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 *
 * This file is included by QMS_Nodes.h
 */


/**
 * @brief The default constructor
 *
 * This is generally used to make the dummyhead of the queue or the
 * red black tree, and sets the data and key pointers to null. It also
   does not set the pointer to the root, and makes the previous, next,
   and parent pointers point back to this node itself.
 */
template <class NodeType, class KeyType, class Lock>
QMS_Node<NodeType, KeyType, Lock>::QMS_Node() :
  node_p_(0), key_p_(0), root_p_(0), data_container_p_(0), colour_(BLACK) 
{
  QMS_Trace ("QMS_Node<NodeType, KeyType, Lock>::QMS_Node", __LINE__, 
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Node<NodeType, KeyType, Lock>::QMS_Node\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  this->next_p_ = this->prev_p_ = this->parent_p_ = this;
}

/**
 * @brief The destructor.
 *
 * If there is a contained data class like a linked list or a red
 * black tree, we make sure that all the nodes in that deeper data
 * structure are also delelted, and then delete the deeper level
 * itself. 
 */
template <class NodeType, class KeyType, class Lock>
QMS_Node <NodeType, KeyType, Lock>::~QMS_Node()
{
  QMS_Trace ("QMS_Node <NodeType, KeyType, Lock>::~QMS_Node", __LINE__, 
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Node <NodeType, KeyType, Lock>::~QMS_Node\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  if(this->data_container_p_)
   {
     this->data_container_p_->delete_nodes();     
     delete this->data_container_p_;
   } /* end of if(this->data_container_p_) */
  this->data_container_p_ = 0;
}

/**
 * @brief Explicit constructor
 * @param node_p   Pointer to the contained data
 * @param key_P    Pointer to the key associated with the data
 * @param root_p   Pointer to the containing data structure (list/tree)
 * @param parent_p Pointer to the parent node
 *
 * This method creates the node, sets the pointers to the correct
 *  values, and, if there are deeper levels to the data structure, it
 *  creates the lower level by calling on the embedded factory object
 *  to create the next level.
 */
template <class NodeType, class KeyType, class Lock>
QMS_Node <NodeType, KeyType, Lock>::QMS_Node
(NodeType *node_p, KeyType *key_p, 
 QMS_MLD_Containers<NodeType, KeyType, Lock> *root_p, 
 QMS_Node<NodeType, KeyType, Lock> *parent_p) :
  node_p_(node_p), key_p_(key_p),  root_p_(root_p), data_container_p_(0),
  parent_p_(parent_p), colour_(BLACK)
{
  QMS_Trace ("QMS_Node <NodeType, KeyType, Lock>::QMS_Node", __LINE__,
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Node <NodeType, KeyType, Lock>::QMS_Node\n");
  
  this->next_p_ = this->prev_p_ = this;
  if(root_p)
   {
     ACE_Double_Linked_List_Iterator<QMS_Sub_Type_Element<NodeType, KeyType, Lock> > iter(root_p->sub_levels_);
     QMS_Sub_Type_Element<NodeType, KeyType, Lock> *type_element_p = 0;
     int ret = iter.next(type_element_p);
     if(! ret)
      {
	return;
      } /* end of if(! ret) */
     
     QMS_MLD_Factory<NodeType, KeyType, Lock> * my_factory_p = 
       type_element_p->get_type();
     this->data_container_p_ = my_factory_p->create_object(&root_p->sub_levels_);
   } /* end of if(root_p) */
  
}
/**
 * @brief The operator =
 * @param rhs The node to copy from
 *
 * This does a deep copy of the contained lower levels of the
 * structure. It also handles any Mutexes correctly (by not copying
 * them or their states)
 */
template <class NodeType, class KeyType, class Lock> 
QMS_Node<NodeType, KeyType, Lock> &
QMS_Node<NodeType, KeyType, Lock>::operator= (QMS_Node<NodeType, KeyType, Lock> &rhs) 
{
  QMS_Trace ("QMS_Node<NodeType, KeyType, Lock>::operator= ", __LINE__, 
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: QMS_Node<NodeType, KeyType, Lock>::operator= \n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  ACE_Read_Guard<Lock> guard_other(rhs.lock_);

  this->data_container_p_->delete_nodes();

  this->node_p_    	     = rhs.node_p_  ;
  this->key_p_ 	   	     = rhs.key_p_   ;
  this->root_p_    	     = rhs.root_p_  ;
  this->parent_p_  	     = rhs.parent_p_;
  this->next_p_    	     = rhs.next_p_  ;
  this->prev_p_    	     = rhs.prev_p_  ;
  this->colour_    	     = rhs.colour_  ;
  this->data_container_p_->copy_nodes(*(rhs.data_container_p_));
  return *this;
}

/**
 * @brief Return a pointer to the data contained in this node
 * @return Pointer to the contained data
 */
template <class NodeType, class KeyType, class Lock> NodeType *
QMS_Node <NodeType, KeyType, Lock>::get_data(void)
{
  QMS_Trace ("QMS_Node <NodeType, KeyType, Lock>::get_data", __LINE__,
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Node <NodeType, KeyType, Lock>::get_data\n");
  
  ACE_Read_Guard<Lock> guard(lock_);
  return this->node_p_;
}

/**
 * @brief Return a pointer to the data contained in this node
 * @return Pointer to the contained key
 */
template <class NodeType, class KeyType, class Lock> KeyType *
QMS_Node <NodeType, KeyType, Lock>::get_key(void)
{
  QMS_Trace ("QMS_Node <NodeType, KeyType, Lock>::get_key", __LINE__, 
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Node <NodeType, KeyType, Lock>::get_key\n");
  
  ACE_Read_Guard<Lock> guard(lock_);
  return this->key_p_;
}

/**
 * @brief Return a pointer to the next deeper level of the data structure
 * @return Pointer to a data structure (tr5ee/list. etc)
 */
template <class NodeType, class KeyType, class Lock> 
QMS_MLD_Containers<NodeType, KeyType, Lock> *
QMS_Node <NodeType, KeyType, Lock>::get_container(void)
{
  QMS_Trace ("QMS_Node <NodeType, KeyType, Lock>::get_container", __LINE__,
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Node<NodeType,KeyType,Lock>::get_container\n");
  
  ACE_Read_Guard<Lock> guard(lock_);
  return this->data_container_p_;
}

/**
 * @brief Get a read lock on the internal mutex
 * @return -1 on error
 */
template <class NodeType, class KeyType, class Lock>  int
QMS_Node <NodeType, KeyType, Lock>::get_read_lock(void)
{
  QMS_Trace ("QMS_Node <NodeType, KeyType, Lock>::get_read_lock", __LINE__,
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Node<NodeType,KeyType,Lock>::get_read_lock\n");
  return this->lock_.acquire_read();
}
/**
 * @brief Get a write lock on the internal mutex
 * @return -1 on error
 */
template <class NodeType, class KeyType, class Lock>  int
QMS_Node <NodeType, KeyType, Lock>::get_write_lock(void)
{
  QMS_Trace ("QMS_Node <NodeType, KeyType, Lock>::get_write_lock", __LINE__,
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Node<NodeType,KeyType,Lock>::get_read_lock\n");
  return this->lock_.acquire_write();
}
/**
 * @brief Release the lock on the internal mutex
 * @return -1 on error
 */
template <class NodeType, class KeyType, class Lock>  int
QMS_Node <NodeType, KeyType, Lock>::release_lock(void)
{
  QMS_Trace ("QMS_Node <NodeType, KeyType, Lock>::get_write_lock", __LINE__,
	     __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Node<NodeType,KeyType,Lock>::get_read_lock\n");
  return this->lock_.release();
}
