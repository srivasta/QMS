
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


/*                               -*- Mode: C -*- 
 * QMS_Type_list.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Wed Apr 18 10:53:53 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu May  3 16:47:22 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 50
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 *  $Id: QMS_Type_list.h,v 1.2 2001/10/21 08:54:13 srivasta Exp $
 */
/** @file QMS_Type_list.h
 *  @ingroup MLD
 *  @brief List defining levels and comparison functions
 *
 * When compiling with the ``-fno-implicit-template'' directive, it is
 * necesary to explicitly instantiate the required concrete classes in
 * some compilation unit in the program. That particular compilation
 * unit needs to include the implementation of the abstract data type,
 * and hence it needs to include not just the interface, but the file
 * containing the implementation.
 */

#ifndef _QMS_TYPE_LIST_H_
#define _QMS_TYPE_LIST_H_

#include "ace/Synch.h"
#include "ace/Thread.h"

#include "QMS_MLD_Factory.h"

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

/**
 * This is the elemnt of a dovule linked list that is used to define
 * the structure of the nodes below the current level, if any, in the
 * multilevel data structure 
 */
template <class NodeType, class KeyType, class Lock>
class QMS_Sub_Type_Element
{
  friend class ACE_Double_Linked_List<QMS_Sub_Type_Element>;
  friend class ACE_Double_Linked_List_Iterator_Base<QMS_Sub_Type_Element>;
  friend class ACE_Double_Linked_List_Iterator<QMS_Sub_Type_Element>;
  friend class ACE_Double_Linked_List_Reverse_Iterator<QMS_Sub_Type_Element>;

public:
  /** 
   * @brief the default constructor
   * @param type_p A pointer to a concrete factory object 
   * @param cmp_func A pointer to the comparison function to use
   * 
   */
  Dllexport
    QMS_Sub_Type_Element (QMS_MLD_Factory<NodeType, KeyType, Lock>* type_p = 0,
			  int (*cmp_func)(const KeyType&, const KeyType&) = 0):
    prev_(0), next_(0), type_p_(type_p), cmp_(cmp_func)
    {
      // Do Nothing
    };
  /**
   * @brief The copy constructor
   * @param rhs The QMS_Sub_Type_Element to copy from
   *
   */
  Dllexport QMS_Sub_Type_Element
    (const QMS_Sub_Type_Element<NodeType, KeyType, Lock>& rhs) :
    prev_ (rhs.prev_), next_ (rhs.next_), type_p_ (rhs.type_p_),
    cmp_ (rhs.cmp_)
    {
      // Do Nothing
    }
  /**
   * @brief The assignment operator
   * @param copy The QMS_Sub_Type_Element to copy from
   *
   */
  Dllexport  QMS_Sub_Type_Element& 
    operator=(const QMS_Sub_Type_Element& copy)
    {
      this->next_ = copy.next_;
      this->prev_ = copy.prev_;
      this->type_p_ = copy.type_p_;
      this->cmp_    = copy.cmp_;
      return *this;
    }

  /**
   * @brief Set the data in this object
   * @param type_p Pointer to a factory object for this level
   * @param cmp_func A pointer to the comparison function to use
   *
   */
  Dllexport  void set(QMS_MLD_Factory<NodeType, KeyType, Lock> *type_p, 
	   int (*cmp_func)(const KeyType&, const KeyType&)) 
    {
      this->type_p_= type_p;
      this->cmp_   = cmp_func;
    }
  
  /// return the type of the level
  Dllexport  QMS_MLD_Factory<NodeType, KeyType, Lock> *
    get_type(void) { return this->type_p_; }
  /// return the compariton function to use
  Dllexport  
    int (*get_cmp(void))(const KeyType&, const KeyType&) { return this->cmp_; }
  
private:
    /// The pointer to the previous element
  QMS_Sub_Type_Element<NodeType, KeyType, Lock> *prev_;
  ///  The pointer to the next element
  QMS_Sub_Type_Element<NodeType, KeyType, Lock> *next_;

  /// The type of the data struct at this level
  QMS_MLD_Factory<NodeType, KeyType, Lock> *type_p_;
  /// The comparison function for the level
  int (*cmp_)(const KeyType&, const KeyType&);
};	// end of class QMS_Sub_Type_Element

#endif /* _QMS_TYPE_LIST_H_ */
