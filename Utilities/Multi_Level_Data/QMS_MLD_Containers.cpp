//                              -*- Mode: C++ -*- 
// QMS_MLD_Containers.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Mon Apr 23 16:05:00 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Aug 14 10:24:18 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 40
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// $Id: QMS_MLD_Containers.cpp,v 1.2 2001/10/21 08:54:12 srivasta Exp $
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
//static const char* version = "$Id: QMS_MLD_Containers.cpp,v 1.2 2001/10/21 08:54:12 srivasta Exp $";


/** @file QMS_MLD_Containers.cpp
 *  @ingroup MLD
 *  @brief Defines the generic datastructure (list, tree, etc) in the framework
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 *
 * This file is included by QMS_MLD_Containers.h
 */

/**
 * @brief The default constructor
 * @param levels_p The description of this and deeper levels of the structure
 */
template <class NodeType, class KeyType, class Lock>
QMS_MLD_Containers<NodeType, KeyType, Lock>::QMS_MLD_Containers(ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> > *levels_p) :
  head_p_(0), size_(0)
{
  QMS_Trace ("QMS_MLD_Containers<NodeType,KeyType,Lock>::QMS_MLD_Containers",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_MLD_Containers<NodeType, KeyType, Lock>::QMS_MLD_Containers\n");
  
  if(levels_p)
   {
     set(levels_p);
   } /* end of if(levels_p) */
}

/**
 * @brief The copy constructor
 *
 *
 */
template <class NodeType, class KeyType, class Lock>
QMS_MLD_Containers<NodeType, KeyType, Lock>::QMS_MLD_Containers
(QMS_MLD_Factory<NodeType, KeyType, Lock> *type_p,
 int (*cmp_p)(const KeyType&, const KeyType&)) :
  head_p_(0), type_p_(type_p), cmp_(cmp_p), size_(0)
{
  QMS_Trace ("QMS_MLD_Containers<NodeType,KeyType,Lock>::QMS_MLD_Containers",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_MLD_Containers<NodeType, KeyType, Lock>::QMS_MLD_Containers\n");
  
  // Do Nothing
}
               
/**
 * @brief Initialize the object 
 * @param levels_p A linked tlist describing this and the deeper
 * levels of the structure
 *
 * Please note that the linked list of type elements pointed to by
 * levels_p contains information about this level as well, and this is
 * the distinguishing factor from the member function set_sublevel
 * below. Using the linked list, we remove the first element, and use
   it to initialize this object. 
 *
 */
template <class NodeType, class KeyType, class Lock> void 
QMS_MLD_Containers<NodeType, KeyType, Lock>::set
(ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> >
 *levels_p)
{
  QMS_Trace ("QMS_MLD_Containers<NodeType, KeyType, Lock>::set",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_MLD_Containers<NodeType, KeyType, Lock>::set\n");
  
  if(levels_p)
   {
     ACE_Write_Guard<Lock> guard(lock_);
     if(!levels_p)
      {
	return;
      } /* end of if(!levels_p) */
     
     this->sub_levels_ = *(levels_p);
     
     QMS_Sub_Type_Element<NodeType, KeyType, Lock> *my_type_p = 
       sub_levels_.delete_head();
     this->type_p_ = my_type_p->get_type();
     this->cmp_  = my_type_p->get_cmp();
     delete my_type_p;
   } /* end of if(levels_p) */
}        
       
/**
 * @brief Set the comparison function used at this level
 * @param cmp_p A pointer to a comparison function to use
 *
 * The comparison function is used by some container classes
 * (for example, the red black tree container) to determine node
 * ordering, and also for information retrieval
 */
template <class NodeType, class KeyType, class Lock> void 
QMS_MLD_Containers<NodeType, KeyType, Lock>::set_cmp(int (*cmp_p)(const KeyType&, const KeyType&))
{
  QMS_Trace ("QMS_MLD_Containers<NodeType, KeyType, Lock>::set_cmp", 
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_MLD_Containers<NodeType, KeyType, Lock>::set_cmp\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  this->cmp_  = cmp_p;
}

/**
 * @brief set the type of this level
 * @param type_p A pointer to the object factory to use at this level
 *
 * The object factory is used for creating the container objects
 * (linked list, red black tree, stack, etc)
 */
template <class NodeType, class KeyType, class Lock> void 
QMS_MLD_Containers<NodeType, KeyType, Lock>::set_type
(QMS_MLD_Factory<NodeType, KeyType, Lock> *type_p)
{
  QMS_Trace ("QMS_MLD_Containers<NodeType, KeyType, Lock>::set_type",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_MLD_Containers<NodeType, KeyType, Lock>::set_type\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  this->type_p_ = type_p;
}
  
/**
 * @brief Set the types of data structures deeper down
 * @param ;eve;s_p The description of deeper levels of the structure
 *
 * Unlike the constructor and the set member function above, this
 * memeber does not affect the type or comparison function at this
 * level, it only affects the levels deeper in the tree.
 */
template <class NodeType, class KeyType, class Lock> void 
QMS_MLD_Containers<NodeType, KeyType, Lock>::set_sublevel
(ACE_Double_Linked_List<QMS_Sub_Type_Element<NodeType, KeyType, Lock> >
 *levels_p)
{
  QMS_Trace ("QMS_MLD_Containers<NodeType, KeyType, Lock>::set_sublevel",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_MLD_Containers<NodeType, KeyType, Lock>::set_sublevel\n");
  
  ACE_Write_Guard<Lock> guard(lock_);
  this->sub_levels_ = *(levels_p);
}
  
/**
 * @brief Is the container full?
 * @return true if the container is full
 *
 */
template <class NodeType, class KeyType, class Lock> const bool 
QMS_MLD_Containers<NodeType, KeyType, Lock>::is_full (void)  const 
{
  QMS_Trace ("QMS_MLD_Containers<NodeType, KeyType, Lock>::is_full ",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_MLD_Containers<NodeType, KeyType, Lock>::is_full \n");
  
  return false; 
}
  
/**
 * @brief Is the container empty?
 * @return true if the container is empty
 *
 */
template <class NodeType, class KeyType, class Lock> const bool 
QMS_MLD_Containers<NodeType, KeyType, Lock>::is_empty (void) const
{
  QMS_Trace ("QMS_MLD_Containers<NodeType, KeyType, Lock>::is_empty ",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER,
	  "DEBUG: Entering QMS_MLD_Containers<NodeType, KeyType, Lock>::is_empty \n");
  
  return this->size_ ? true : false; 
}


/**
 * @brief The size of the list/tree
 * @return return the number of elements at this level in the container
 *
 */
template <class NodeType, class KeyType, class Lock> const size_t 
QMS_MLD_Containers<NodeType, KeyType, Lock>::size (void) const
{
  QMS_Trace ("QMS_MLD_Containers<NodeType, KeyType, Lock>::size ", 
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_MLD_Containers<NodeType, KeyType, Lock>::size \n");
  
  return this->size_; 
}

/**
 * @brief Get a read lock on the internal mutex
 * @return -1 on error
 */
template <class NodeType, class KeyType, class Lock>  int
QMS_MLD_Containers <NodeType, KeyType, Lock>::get_read_lock(void)
{
  QMS_Trace ("QMS_MLD_Containers <NodeType, KeyType, Lock>::get_read_lock",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_MLD_Containers<NodeType,KeyType,Lock>::get_read_lock\n");
  return this->lock_.acquire_read();
}
/**
 * @brief Get a write lock on the internal mutex
 * @return -1 on error
 */
template <class NodeType, class KeyType, class Lock>  int
QMS_MLD_Containers <NodeType, KeyType, Lock>::get_write_lock(void)
{
  QMS_Trace ("QMS_MLD_Containers <NodeType, KeyType, Lock>::get_write_lock",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_MLD_Containers<NodeType,KeyType,Lock>::get_read_lock\n");
  return this->lock_.acquire_write();
}
/**
 * @brief Release the lock on the internal mutex
 * @return -1 on error
 */
template <class NodeType, class KeyType, class Lock>  int
QMS_MLD_Containers <NodeType, KeyType, Lock>::release_lock(void)
{
  QMS_Trace ("QMS_MLD_Containers <NodeType, KeyType, Lock>::get_write_lock",
	     __LINE__, __FILE__);
  DEBUG0 (DEBUG_L_ENTER, 
	  "DEBUG: Entering QMS_MLD_Containers<NodeType,KeyType,Lock>::get_read_lock\n");
  return this->lock_.release();
}
