//                              -*- Mode: C++ -*- 
// QMS_Linked_List.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Sat Apr 21 14:20:10 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Aug 14 10:24:24 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 66
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
//  $Id: QMS_Linked_List.cpp,v 1.2 2001/10/21 08:54:12 srivasta Exp $
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
//static const char* version = "$Id: QMS_Linked_List.cpp,v 1.2 2001/10/21 08:54:12 srivasta Exp $";


/** @file QMS_Linked_List.cpp
 *  @ingroup MLD
 *  @brief Implementation of a double linked list structure
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 *
 * This file is included by the file QMS_Linked_List.h
 */


/**
 * @brief The default constructor
 * @param levels_p Description of the lower levels of the data struct
 *
 * The constructor creates a dummy node called head for use as a guard
 * in iterations and passes over the list. 
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List<NodeType, KeyType, Lock>::QMS_Linked_List(ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> > *levels_p) :
  QMS_MLD_Containers< NodeType, KeyType, Lock>::QMS_MLD_Containers(levels_p)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::QMS_Linked_List",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::QMS_Linked_List\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  this->head_p_ = new QMS_Node<NodeType, KeyType, Lock>();
  this->head_p_->parent_p_ = this->head_p_->next_p_ 
			   = this->head_p_->prev_p_
			   = this->head_p_;
  this->head_p_->root_p_   = this;
}

/**
 * @brief the explicit level constructor
 * @param type_p The object factory to use for creating sub levels
 * @param cmp_p  A pointer to the comparison function to use to compare keys
 *
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List<NodeType, KeyType, Lock>::QMS_Linked_List
(QMS_MLD_Factory<NodeType, KeyType, Lock> *type_p, int (*cmp_p)(const KeyType&, const KeyType&)) :
  QMS_MLD_Containers< NodeType, KeyType, Lock>::QMS_MLD_Containers(type_p, cmp_p)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::QMS_Linked_List", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::QMS_Linked_List\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  this->head_p_ = new QMS_Node<NodeType, KeyType, Lock>();
  this->head_p_->parent_p_ = this->head_p_->next_p_ 
			   = this->head_p_->prev_p_
			   = this->head_p_;
  this->head_p_->root_p_   = this;
}


/**  
 * @brief The copy constructor
 * @param copy the object to copy from
 *
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List<NodeType, KeyType, Lock>::QMS_Linked_List(QMS_Linked_List<NodeType, KeyType, Lock> &copy) :
  QMS_MLD_Containers<NodeType, KeyType, Lock>()
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::QMS_Linked_List", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::QMS_Linked_List\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  this->size_ 	    = copy.size_;
  this->type_p_	    = copy.type_p_;
  this->cmp_ 	    = copy.cmp_;
  this->sub_levels_ = copy.sub_levels_;
  
  this->copy_nodes(copy);
}

/**  
 * @brief The assignment operator
 * @param rhs the object to copy from
 *
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List<NodeType, KeyType, Lock> &
QMS_Linked_List<NodeType, KeyType, Lock>::operator= (QMS_Linked_List<NodeType, KeyType, Lock> &rhs)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::operator=", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::operator=\n");
  
  if(this != &rhs)
   {
     this->delete_nodes();
     this->copy_nodes(rhs);
   } /* end of if(this != copy) */
  return *this;
}

/**  
 * @brief The destructor
 *
 * We make sure all nodes in this level are deleted, and we delete the
 * dummy head node as well.
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List<NodeType, KeyType, Lock>::~QMS_Linked_List()
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::~QMS_Linked_List", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::~QMS_Linked_List\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  this->delete_nodes();
  delete this->head_p_;
  this->head_p_ = 0;
}


/**  
 * @brief Insert a new element at the head of the list
 * @param new_item_p A Pointer to the the new data to be inserted
 * @param key_p      A pointer to a key associated with the data
 * @return The data element just inserted
 *
 * Inserts the new data element at the head of the list
 */
template <class NodeType, class KeyType, class Lock> NodeType* 
QMS_Linked_List<NodeType, KeyType, Lock>::insert_head (NodeType *new_item_p,
							KeyType *key_p)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::insert_head ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::insert_head \n");
  
  if(new_item_p == 0)
   {
     return new_item_p;
   } /* end of if(new_item_p == 0) */
  return this->insert_element(new_item_p, key_p, this->head_p_->next_p_);
}

/**  
 * @brief Insert a new element at the tail of the list
 * @param new_item_p A Pointer to the the new data to be inserted
 * @param key_p      A pointer to a key associated with the data
 * @return The data element just inserted
 *
 * Inserts the new data element at the tail of the list
 */
template <class NodeType, class KeyType, class Lock> NodeType* 
QMS_Linked_List<NodeType, KeyType, Lock>::insert_tail (NodeType *new_item_p,
							KeyType *key_p)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::insert_tail ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::insert_tail \n");
  
  if(new_item_p == 0)
   {
     return new_item_p;
   } /* end of if(new_item_p == 0) */
  return this->insert_element(new_item_p, key_p, this->head_p_);
}
/**  
 * @brief delete a new element at the head of the list
 * @return The data element just deleted
 *
 * Deletes the element at the head of the list
 */
template <class NodeType, class KeyType, class Lock> NodeType* 
QMS_Linked_List<NodeType, KeyType, Lock>::delete_head (void)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::delete_head ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::delete_head \n");
  
  if(this->is_empty ())
   {
     return 0;
   } /* end of if(new_item_p == 0) */
  return this->delete_element(this->head_p_->next_p_);
}

/**  
 * @brief delete a new element at the tail of the list
 * @return The data element just deleted
 *
 * Deletes the element at the tail of the list
 */
template <class NodeType, class KeyType, class Lock> NodeType* 
QMS_Linked_List<NodeType, KeyType, Lock>::delete_tail (void)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::delete_tail ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::delete_tail \n");
  
  if(this->is_empty ())
   {
     return 0;
   } /* end of if(new_item_p == 0) */
  return this->delete_element(this->head_p_->prev_p_);
}

/**
 * @brief The work horse function for deleting elements
 * @param delete_p A pointer to the data contained in the deleted element
 * @return A pointer to the data deleted
 *
 * This is the function used by the delete_head() and delete_tail()
 * member functions to actually perform the deletions. It 
 * the key value inserted, and returns apointer to the data deleted.
 */
template <class NodeType, class KeyType, class Lock> NodeType* 
QMS_Linked_List<NodeType, KeyType, Lock>::delete_element(QMS_Node<NodeType, KeyType, Lock> *delete_p)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::delete_element", 
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::delete_element\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  // refuse to delete the head node
  if(delete_p == this->head_p_)
   {
     return 0;
   } /* end of if(before == this->head_p_) */

  // Save the data
  NodeType* data_p = delete_p->get_data();
  KeyType* key_p = delete_p->get_key();
  delete key_p;
  
  delete_p->prev_p_->next_p_ = delete_p->next_p_;
  delete_p->next_p_->prev_p_ = delete_p->prev_p_;
  delete_p->next_p_          = delete_p->prev_p_ 
			     = 0;
  delete delete_p;
  delete_p = 0;
  
  this->size_--;
  return data_p;
}

/**
 * @brief The work horse function for inserting elements
 * @param new_item_p A pointer to the data to be inserted
 * @param key_p A pointer to the key value associated with the data
 * @param before A pointer to the element before which the new element should be inserted
 * @return A pointer to the data inserted
 *
 * This is the function used by the insert_head() and insert_tail()
 * member functions to actually perform the deletions. It  returns a
   pointer to the data inserted. 
 */
template <class NodeType, class KeyType, class Lock> NodeType* 
QMS_Linked_List<NodeType, KeyType, Lock>::insert_element(NodeType *new_item_p, 
							 KeyType *key_p, 
							 QMS_Node<NodeType, KeyType, Lock> *before)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::insert_element", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::insert_element\n");
  
  if(new_item_p == 0)
   {
     return new_item_p;
   } /* end of if(new_item_p == 0) */

  ACE_Write_Guard<Lock> guard(lock_);
  QMS_Node<NodeType, KeyType, Lock> *temp_p = 
    new QMS_Node<NodeType, KeyType, Lock>(new_item_p, key_p, this, 0);
  temp_p->prev_p_          = before->prev_p_;
  temp_p->next_p_          = before;
  before->prev_p_->next_p_ = temp_p;
  before->prev_p_          = temp_p;

  this->size_++;
  DEBUG1(DEBUG_L_INFO, "DEBUG: insert_element: the size is %d",
	 this->size_);
  if(this->head_p_->next_p_ == this->head_p_)
   {
     DEBUG0(DEBUG_L_CRIT, "Failed while entering element");
     return 0;
   } /* end of if(this->head_p_->nexp_p_ == this->head_p_) */
  
  return new_item_p;
}

//forward declaration
template <class NodeType, class KeyType, class Lock> 
class QMS_Linked_List_Iterator ;

/**
 * @brief Iteratively copy all the nodes from another list
 * @param copy The linked list to copy
 *
 * This does a deep copy of the list to copy from.  Please note that
 * this member function does not destroy ny data already present, so
 * this is truly a deep append function.
 */ 
template <class NodeType, class KeyType, class Lock> void
QMS_Linked_List<NodeType, KeyType, Lock>::copy_nodes(QMS_MLD_Containers<NodeType, KeyType, Lock> &copy)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::copy_nodes",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::copy_nodes\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  for(QMS_Linked_List_Iterator<NodeType, KeyType, Lock> iter(static_cast<QMS_Linked_List *>(&copy)); 
      !iter.done(); iter.advance())
   {
     this->insert_tail(iter.next(), iter.key());
   }
}

/**
 * @brief Iteratively delete all node
 * @param copy The linked list to copy
 *
 * This destroys both key and data values while walking through the
 * list. 
 */ 

template <class NodeType, class KeyType, class Lock> void
QMS_Linked_List<NodeType, KeyType, Lock>::delete_nodes(void)
{
  QMS_Trace ("QMS_Linked_List<NodeType, KeyType, Lock>::delete_nodes", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List<NodeType, KeyType, Lock>::delete_nodes\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  while(!this->is_empty())
   {
     KeyType*  key_p  = this->head_p_->next_p_->get_key();
     NodeType* data_p = this->delete_element(this->head_p_->next_p_);
     delete key_p;
     delete data_p;
   } /* end of while(!this->is_empty()) */
}





