/*                               -*- Mode: C -*- 
 * QMS_Linked_List_Iterators.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Sun Apr 22 22:17:11 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu May  3 16:44:49 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 77
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 *  $Id: QMS_Linked_List_Iterators.h,v 1.3 2001/10/21 08:54:12 srivasta Exp $
 */
/** @file QMS_Linked_List_Iterators.h
 *  @ingroup MLD
 *  @brief Iterators for the doubly linked list
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 *
 * This file includes QMS_Linked_List_Iterators.cpp
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


#ifndef _QMS_LINKED_LIST_ITERATORS_H_
#define _QMS_LINKED_LIST_ITERATORS_H_

#include "Debug.h"
#include "QMS_Linked_List.h"

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

using namespace std;
/**
 *  @brief A common base class for iterators for a double linked list
 *  
 * Most of the algorithms and access methods do so using iterators.
 * This  class provides the common elements for forward and reverse
 * concrete classes derived from this one.
 */
template <class NodeType, class KeyType, class Lock>
class QMS_Linked_List_Iterator_Base
{
  friend class QMS_Linked_List<NodeType , KeyType, Lock>;
  friend class QMS_Linked_List_Iterator<NodeType , KeyType, Lock>;

 public:
  /// Retasks the iterator to iterate over a new Double_Linked_List.
  Dllexport void reset(QMS_Linked_List <NodeType , KeyType, Lock> *list_p);

  /// Passes back the <entry> under the iterator. Returns 0 if the
  /// iteration has completed, otherwise 1
  Dllexport int next(NodeType *&NodePtr);
  /// return a pointer to the data element under the iterator
  Dllexport NodeType *next(void);
  /// return a pointer to the key for the under the iterator
  Dllexport KeyType *key(void);

  /**
   * Return the address of next (current) unvisited item in the list.
   * 0 if there is no more element available.STL-like iterator
   * dereference operator: 
   */
  Dllexport NodeType & operator* (void);

  /// Return a pointer to the first data element in the list
  Dllexport NodeType * begin(void);
  /// Return a pointer to the last data element in the list
  Dllexport NodeType * end(void);
  /// Return true if the iterator is done
  Dllexport virtual bool done (void);
  /// return a pointer to the underlying element
  Dllexport QMS_Node <NodeType , KeyType, Lock> *get_node(void);
  
  /// Delete the current element, adance to the next element, and
  /// return the deleted element
  virtual NodeType *advance_and_remove (int dont_remove) = 0;
  /// A pure virtual function taking the iterator to the beginning
  virtual int first(void) = 0;
  /// A pure virtual function taking the iterator to the end
  virtual int last(void) = 0;
  /// advance to the next element in the list
  virtual QMS_Node <NodeType , KeyType, Lock> *advance(void) = 0;
  /// Advance to the next node
  virtual int advance(int) = 0;
   
 protected:
  /// The default constructor
  QMS_Linked_List_Iterator_Base(QMS_Linked_List <NodeType , KeyType, Lock> 
				*list_p);
  /// The copy constructor
  QMS_Linked_List_Iterator_Base(QMS_Linked_List_Iterator_Base<NodeType, KeyType, Lock> &iter);
  /// The destructor
  virtual ~QMS_Linked_List_Iterator_Base(){};
  
  /// The assignment operator
  QMS_Linked_List_Iterator_Base <NodeType , KeyType, Lock> &
    operator=(QMS_Linked_List_Iterator_Base <NodeType , KeyType, Lock> &rhs);

  /// Go to the head of the list
  int go_head(void);
  /// Go to the tail of the list
  int go_tail(void);


  /// Advance to the next element, returning the data contained
  NodeType *do_advance(void);
  /// Retreat to the previous element, returning the data contained
  NodeType *do_retreat(void);

  /// Return the element under the pointer, or 0, if done
  NodeType *not_done(void);

  /// The current state of the iterator  
  QMS_Node <NodeType , KeyType, Lock> *current_p_;
  /// pointger to the list we are iterating over
  QMS_Linked_List <NodeType , KeyType, Lock> *list_p_;
};

/**
 *  @brief An iterator for a double linked list
 *  
 * Iterate through the double-linked list.  This class provides
 * an interface that let users access the internal element
 * addresses directly.
 */
template <class NodeType, class KeyType, class Lock>
class QMS_Linked_List_Iterator : public QMS_Linked_List_Iterator_Base<NodeType , KeyType, Lock>
{
  friend class QMS_Linked_List<NodeType , KeyType, Lock>;
 public:
  /// The default constructor
  QMS_Linked_List_Iterator(QMS_Linked_List <NodeType , KeyType, Lock> *list_p);
  /// The copy constructor
  QMS_Linked_List_Iterator(QMS_Linked_List_Iterator <NodeType , KeyType, Lock> &iter);

  
  /// The assignment operator
  Dllexport QMS_Linked_List_Iterator<NodeType , KeyType, Lock> & 
    operator= (QMS_Linked_List_Iterator<NodeType , KeyType, Lock> &rhs);
  
  /// retask the iterator to point to a new list
  Dllexport void reset(QMS_Linked_List <NodeType , KeyType, Lock> *list_p);


  /// Delete the current element, adance to the next element, and
  /// return the deleted element
  virtual NodeType *advance_and_remove (int dont_remove);
  /// A pure virtual function taking the iterator to the beginning
  virtual int first(void);
  /// A pure virtual function taking the iterator to the end
  virtual int last(void);
  /// advance to the next element in the list
  virtual QMS_Node <NodeType , KeyType, Lock> *advance(void);
  /// Advance to the next node
  virtual int advance(int);

  
  /// Prefix advance.
  Dllexport QMS_Linked_List_Iterator <NodeType, KeyType, Lock> & operator++ (void);  
  /// Postfix advance.
  Dllexport QMS_Linked_List_Iterator <NodeType, KeyType, Lock>   operator++ (int);
  
  /// Prefix reverse.
  Dllexport QMS_Linked_List_Iterator <NodeType, KeyType, Lock> & operator-- (void);
  /// Postfix reverse.
  Dllexport QMS_Linked_List_Iterator <NodeType, KeyType, Lock>   operator-- (int);
};


/**
 *  @brief A reverse iterator for a double linked list
 *  
 * Iterate backwards through the double-linked list.  This class provides
 * an interface that let users access the internal element
 * addresses directly.
 */
template <class NodeType, class KeyType, class Lock>
class QMS_Linked_List_Reverse_Iterator : public QMS_Linked_List_Iterator_Base<NodeType , KeyType, Lock>
{
  friend class QMS_Linked_List<NodeType , KeyType, Lock>;
 public:
  /// The default constructor
  QMS_Linked_List_Reverse_Iterator(QMS_Linked_List <NodeType , KeyType, Lock> 
				   *list_p);
  /// The copy constructor
  QMS_Linked_List_Reverse_Iterator(QMS_Linked_List_Reverse_Iterator <NodeType , KeyType, Lock> &iter);
  
  /// The assignment operator
  Dllexport QMS_Linked_List_Reverse_Iterator<NodeType , KeyType, Lock> &
    operator= (QMS_Linked_List_Reverse_Iterator<NodeType, KeyType, Lock> &rhs);
  
  /// retask the iterator to point to a new list
  Dllexport void reset(QMS_Linked_List <NodeType , KeyType, Lock> *list_p);

  /// Delete the current element, adance to the next element, and
  /// return the deleted element
  virtual NodeType *advance_and_remove (int dont_remove);
  /// A pure virtual function taking the iterator to the beginning
  virtual int first(void);
  /// A pure virtual function taking the iterator to the end
  virtual int last(void);
  /// advance to the next element in the list
  virtual QMS_Node <NodeType , KeyType, Lock> *advance(void);
  /// Advance to the next node
  virtual int advance(int);

  /// Prefix advance.
  Dllexport QMS_Linked_List_Reverse_Iterator <NodeType, KeyType, Lock> & operator++ (void);
  
  /// Postfix advance.
  Dllexport QMS_Linked_List_Reverse_Iterator <NodeType, KeyType, Lock>   operator++ (int);
  
  
  /// Prefix reverse.
  Dllexport QMS_Linked_List_Reverse_Iterator <NodeType, KeyType, Lock> & operator-- (void);
  
  /// Postfix reverse.
  Dllexport QMS_Linked_List_Reverse_Iterator <NodeType, KeyType, Lock>   operator-- (int);
};

// include the implementation
#include "QMS_Linked_List_Iterators.cpp"

#endif /* _QMS_LINKED_LIST_ITERATORS_H_ */
