//                              -*- Mode: C++ -*- 
// QMS_Linked_List_Iterators.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Sun Apr 22 22:19:58 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Aug 14 10:24:32 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 84
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// $Id: QMS_Linked_List_Iterators.cpp,v 1.2 2001/10/21 08:54:12 srivasta Exp $
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
//static const char* version = "$Id: QMS_Linked_List_Iterators.cpp,v 1.2 2001/10/21 08:54:12 srivasta Exp $";


/** @file QMS_Linked_List_Iterators.cpp
 *  @ingroup MLD
 *  @brief Defines the iterator objects for the double linked list
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 *
 * This file is included by QMS_Linked_List_Iterators.h
 */

/**
 * @brief Constructor
 * @param List The double Linked List to Iterate over
 * 
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::QMS_Linked_List_Iterator_Base
(QMS_Linked_List <NodeType , KeyType, Lock> *list_p) : 
  current_p_(0),  list_p_(list_p)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Iterator_Base\n");
  
  // Do nothing
}

/**
 * @overload
 * @param iter The iterator to base this object on
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::QMS_Linked_List_Iterator_Base (QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock> &iter) :
  current_p_(iter.current_p_),  list_p_(iter.list_p_)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Iterator_Base\n");
  
  // Do nothing
}
/**
 * @brief The assignment operator
 * @param iter The iterator to base this object on
 */
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Iterator_Base <NodeType , KeyType, Lock> &
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::operator= 
(QMS_Linked_List_Iterator_Base <NodeType , KeyType, Lock> &rhs)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::operator= ",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::operator= \n");
  
  this->current_p_ = rhs.current_p_;
  this->list_p_    = rhs.list_p_;
  return *this;
}

/**
 * @brief retask the iterator to iterate over another list
 * @param List the new list to iterate over
 */
template <class NodeType, class KeyType, class Lock> void
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::reset(QMS_Linked_List <NodeType, KeyType, Lock> *list_p)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::reset",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::reset\n");
  
  this->current_p_ = 0;
  this->list_p_ = list_p;
}
/**
 * @brief return the data contained under the iterator
 * @return Pointer to the data contained 
 * This can also serve as an end of pass marker
 */
template <class NodeType, class KeyType, class Lock> NodeType *
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::not_done(void)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType,KeyType,Lock>::not_done",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::not_done\n");
  
  if(this->current_p_ != this->list_p_->head_p_)
   {
     return this->current_p_->get_data();
   } /* end of if(this->current_p_ != this->list_p_->head_p_) */
  else
   {
     DEBUG0(DEBUG_L_WARN, "We are pointing to the head");
     return 0;
   } /* end of else */
}
/**
 * @brief return a pointer to the node  under the iterator
 * @return pointer to the list node (not the data contained in the node)
 *
 */
template <class NodeType, class KeyType, class Lock> 
QMS_Node <NodeType , KeyType, Lock> *
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::get_node(void)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType,KeyType,Lock>::get_node",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::get_node\n");
  
  if(this->current_p_ != this->list_p_->head_p_)
   {
     return this->current_p_;
   } /* end of if(this->current_p_ != this->list_p_->head_p_) */
  else
   {
     return 0;
   } /* end of else */
}

/**
 * @brief return data under the iterator
 * @return Pointer to the data contained 
 */
template <class NodeType, class KeyType, class Lock> NodeType *
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::next(void) 
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::next",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::next\n");
  
  return this->not_done ();
}
/**
 * @brief return key to the element under the iterator
 * @return Pointer to the key to the element under the iterator 
 */
template <class NodeType, class KeyType, class Lock> KeyType *
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::key(void) 
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::key",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::key\n");
  
  if(this->current_p_ != this->list_p_->head_p_)
   {
     return this->current_p_->get_key();
   } /* end of if(this->current_p_ != this->list_p_->head_p_) */
  else
   {
     return 0;
   } /* end of else */
}


/**
 * @overload
 * @param ptr Where the ppointer to the data is returned
 */
template <class NodeType, class KeyType, class Lock> int
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::next (NodeType *&ptr) 
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::next ",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::next \n");
  
  ptr = this->not_done ();
  return ptr ? 1 : 0;
}

/**
 * @brief Go to the first data element in the list
 * @return Pointer to the data contained in the first element of the list
 */
template <class NodeType, class KeyType, class Lock> NodeType *
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::begin(void)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::begin",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::begin\n");
  
  this->first ();
  return this->next();
}


/**
 * @brief Go to the last data element in the list
 * @return Pointer to the data contained in the last element of the list
 */
template <class NodeType, class KeyType, class Lock> NodeType *
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::end(void)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::end",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::end\n");
  
  this->last ();
  return this->next();
}

/**
 * @brief Is the pass over the list done?
 * @return A boolean true or false value
 */
template <class NodeType, class KeyType, class Lock> bool
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::done (void)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::done ",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::done \n");
  if(this->current_p_ != this->list_p_->head_p_)
   {
     return false;
   } /* end of if(this->current_p_ != this->list_p_->head_p_) */
  else
   {
     return true;
   } /* end of else */
}

/**
 * @brief STL-like iterator dereference operator: 
 * @return Pointer to the data contained 
 *
 * Return the address of next (current) unvisited item in the list.
 */
template <class NodeType, class KeyType, class Lock> NodeType &
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::operator* (void)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType,KeyType,Lock>::operator*",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::operator* \n");
  
  return *(this->not_done());	// Error if we are on the head
}
/**
 * @brief  Go to the head of the list
 * @return Return 1 if the list contains data, 0 otherwise
 *
 */
template <class NodeType, class KeyType, class Lock> int
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::go_head(void)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::go_head",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::go_head\n");
  
  this->current_p_ = this->list_p_->head_p_->next_p_;
  if(this->list_p_->head_p_->next_p_ == this->list_p_->head_p_)
   { return 0; }
  else
   { return 1; } 
}


/**
 * @brief  Go to the tail of the list
 * @return Return 1 if the list contains data, 0 otherwise
 *
 */
template <class NodeType, class KeyType, class Lock> int
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::go_tail(void)
{
  QMS_Trace ("QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::go_tail",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::go_tail\n");
  
  this->current_p_ = this->list_p_->head_p_->prev_p_;
  if(this->list_p_->head_p_->prev_p_ == this->list_p_->head_p_)
   { return 0; }
  else
   { return 1; } 
}

/**
 * @brief  Advance to the next element
 * @return Pointer to the data contained 
 *
 */
template <class NodeType, class KeyType, class Lock> NodeType *
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::do_advance(void)
{
  QMS_Trace("QMS_Linked_List_Iterator_Base<NodeType,KeyType,Lock>::do_advance",
	    __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::do_advance\n");
  
  if(this->not_done())
   {
     this->current_p_ = this->current_p_->next_p_;
     return this->not_done();
   } /* end of if(this->not_done()) */
  else
   {
     return 0;
   } /* end of else */
}

/**
 * @brief  Retreat to the previous element
 * @return Pointer to the data contained 
 *
 */
template <class NodeType, class KeyType, class Lock> NodeType *
QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::do_retreat(void)
{
  QMS_Trace("QMS_Linked_List_Iterator_Base<NodeType,KeyType,Lock>::do_retreat",
	    __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::do_retreat\n");
  
  if(this->not_done())
   {
     this->current_p_ = this->current_p_->prev_p_;
     return this->not_done();
   } /* end of if(this->not_done()) */
  else
   {
     return 0;
   } /* end of else */
}


/*************************************************************************
 *************************************************************************
 *************************************************************************
 ************************************************************************/

/**
 * @brief Constructor
 * @param List The double Linked List to Iterate over
 * 
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Iterator
(QMS_Linked_List <NodeType , KeyType, Lock> *list_p) :
  QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock> (list_p)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Iterator",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Iterator\n");
  
  // Advance current_p_ out of the null area and onto the last item in
  // the list
  this->current_p_ = this->list_p_->head_p_->next_p_;
}
/**
 * @overload
 * @param iter The iterator to base this object on
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Iterator (QMS_Linked_List_Iterator<NodeType, KeyType, Lock> &iter) :
  QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock> (0)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Iterator",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Iterator\n");
  
  this->current_p_ = iter.current_p_;
  this->list_p_    = iter.list_p_;
}

/**
 * @brief The assignment operator
 * @param iter The iterator to base this object on
 */
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Iterator<NodeType, KeyType, Lock> &
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator=
(QMS_Linked_List_Iterator<NodeType, KeyType, Lock> &rhs)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator=",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator=\n");
  
  this->current_p_ = rhs.current_p_;
  this->list_p_    = rhs.list_p_;
  return *this;
}

/**
 * @brief retask the iterator to iterate over another list
 * @param List the new list to iterate over
 */
template <class NodeType, class KeyType, class Lock> void
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::reset(QMS_Linked_List<NodeType,KeyType,Lock> *list_p)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::reset",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::reset\n");
  
  this->QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::reset(list_p);
  // Advance current_p_ out of the null area and onto the last item in
  // the list
  this->current_p_ = this->list_p_->head_p_->next_p_;
}

/**
 * @brief Go to the first element in the list
 * @return 0 if the list is empty
 */
template <class NodeType, class KeyType, class Lock> int
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::first(void)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::first",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::first\n");
  
    return this->go_head ();
}

/**
 * @brief Go to the last element in the list
 * @return 0 if the list is empty
 */
template <class NodeType, class KeyType, class Lock> int
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::last(void)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::last", 
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::last\n");
  
    return this->go_tail ();
}

/**
 * @brief Advance one step
 * @return 0 if the list is empty
 */
template <class NodeType, class KeyType, class Lock> int
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::advance(int)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::advance",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::advance\n");
  
  return this->do_advance () ? 1 : 0;
}

/**
 * @brief Advance one step
 * @return A pointer to the list element (not the underlying data)
 */
template <class NodeType, class KeyType, class Lock> 
QMS_Node <NodeType , KeyType, Lock> *
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::advance(void)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::advance",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::advance\n");
  
  this->do_advance ();
  return this->current_p_;
}

/**
 * @brief Advance one step, delete the data contained therein, 
 * @return A pointer to the data from the lement that was removed
 */
template <class NodeType, class KeyType, class Lock> NodeType *
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::advance_and_remove (int dont_remove)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType,KeyType,Lock>::advance_and_remove ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::advance_and_remove \n");
  
  NodeType* item_p = 0;
  if (dont_remove)
   {
     this->do_advance ();
   }
  else
    {
      QMS_Node <NodeType , KeyType, Lock> *delete_p = this->current_p_;
      item_p = this->next ();
      this->do_advance ();
      this->list_p_->delete_element (delete_p);
    }
  return item_p;
}

/// Prefix advance.
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Iterator<NodeType, KeyType, Lock> 
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator++ (int)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator++ ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator++ \n");
  
  QMS_Linked_List_Iterator<NodeType, KeyType, Lock> ret_val = *this;
  
  this->do_advance ();
  return ret_val;
}
/// Postfix advance.
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Iterator<NodeType, KeyType, Lock> &
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator++ (void)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator++ ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator++ \n");
  
  this->do_advance ();
  return *this;
}

/// Prefix reverse.
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Iterator<NodeType, KeyType, Lock> 
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator-- (int)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator-- ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator-- \n");
  
  QMS_Linked_List_Iterator<NodeType, KeyType, Lock> ret_val = *this;
  this->do_retreat ();
  return ret_val;
}
/// Postfix reverse.
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Iterator<NodeType, KeyType, Lock> &
QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator-- (void)
{
  QMS_Trace ("QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator-- ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Iterator<NodeType, KeyType, Lock>::operator-- \n");
  
  this->do_retreat ();
  return *this;
}


/*************************************************************************
 *************************************************************************
 *************************************************************************
 ************************************************************************/

/**
 * @brief Constructor
 * @param List The double Linked List to Iterate over
 * 
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Reverse_Iterator
(QMS_Linked_List <NodeType , KeyType, Lock> *list_p) :
  QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock> (list_p)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Reverse_Iterator", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Reverse_Iterator\n");
  
  // Advance current_p_ out of the null area and onto the last item in
  // the list
  this->current_p_ = this->list_p_->head_p_->prev_p_;
}

/**
 * @overload
 * @param iter The iterator to base this object on
 */
template <class NodeType, class KeyType, class Lock>
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Reverse_Iterator
(QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> &iter) :
  QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock> (0)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Reverse_Iterator", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::QMS_Linked_List_Reverse_Iterator\n");
  
  this->current_p_ = iter.current_p_;
  this->list_p_    = iter.list_p_;
}
/**
 * @brief The assignment operator
 * @param iter The iterator to base this object on
 */
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> &
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator=
(QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> &rhs)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator=", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator=\n");
  
  this->current_p_ = rhs.current_p_;
  this->list_p_    = rhs.list_p_;
  return *this;
}


/**
 * @brief retask the iterator to iterate over another list
 * @param List the new list to iterate over
 */
template <class NodeType, class KeyType, class Lock> void
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::reset(QMS_Linked_List<NodeType,KeyType,Lock> *list_p)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::reset", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::reset\n");
  
  this->QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock>::reset(list_p);
  // Advance current_p_ out of the null area and onto the last item in
  // the list
  this->current_p_ = this->list_p_->head_p_->prev_p_;
}

/**
 * @brief Go to the first element in the list
 * @return 0 if the list is empty
 */
template <class NodeType, class KeyType, class Lock> int
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::first(void)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::first", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::first\n");
  
    return this->go_tail ();
}

/**
 * @brief Go to the last element in the list
 * @return 0 if the list is empty
 */
template <class NodeType, class KeyType, class Lock> int
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::last(void)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::last", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::last\n");
  
    return this->go_head ();
}

/**
 * @brief Advance one step
 * @return 0 if the list is empty
 */
template <class NodeType, class KeyType, class Lock> int
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::advance(int)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::advance", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::advance\n");
  
  return this->do_retreat () ? 1 : 0;
}

/**
 * @brief Advance one step
 * @return A pointer to the list element (not the underlying data)
 */
template <class NodeType, class KeyType, class Lock>
QMS_Node<NodeType, KeyType, Lock> *
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::advance(void)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::advance", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::advance\n");
  
  this->do_retreat();
  return this->current_p_;
}

/**
 * @brief Advance one step, delete the data contained therein, 
 * @return A pointer to the data from the lement that was removed
 */
template <class NodeType, class KeyType, class Lock> NodeType *
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::advance_and_remove (int dont_remove)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::advance_and_remove ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::advance_and_remove \n");
  
  NodeType* item_p = 0;
  if (dont_remove)
   {
     this->do_retreat ();
   }
  else
    {
      QMS_Node<NodeType, KeyType, Lock> *delete_p = this->current_p_;
      item_p = this->next ();
      this->do_retreat ();
      this->list_p_->delete_element (delete_p);
    }
  return item_p;
}

/// Prefix advance.
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> 
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator++ (int)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator++ ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator++ \n");
  
  QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> ret_val = *this;
  
  this->do_retreat ();
  return ret_val;
}

/// Postfix advance.
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> &
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator++ ()
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator++ ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator++ \n");
  
  this->do_retreat ();
  return *this;
}


/// Prefix reverse.
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> 
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator-- (int)
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator-- ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator-- \n");
  
  QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> ret_val = *this;
  this->do_advance ();
  return ret_val;
}

/// Postfix reverse.
template <class NodeType, class KeyType, class Lock> 
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> &
QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator-- ()
{
  QMS_Trace ("QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator-- ", __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, "DEBUG: Entering QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock>::operator-- \n");
  
  this->do_advance ();
  return *this;
}

