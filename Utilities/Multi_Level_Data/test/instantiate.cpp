//                              -*- Mode: C++ -*- 
// instantiate.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
// Created On       : Fri Apr 27 16:56:45 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Aug 14 10:24:15 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 6
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// $Id: instantiate.cpp,v 1.2 2001/10/21 08:54:13 srivasta Exp $
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
//static const char* version = "$Id: instantiate.cpp,v 1.2 2001/10/21 08:54:13 srivasta Exp $";

/** @file instantiate.cpp
 *  @ingroup  Utilities Testing
 *  @brief Template instantiation for templates used in the test code
 *
 */

#include <string>
#include "QMS_MLD.h"

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class  QMS_Sub_Type_Element<string,string,ACE_RW_Mutex>;
template class  ACE_Double_Linked_List<QMS_Sub_Type_Element<string,string,ACE_RW_Mutex> >;
template class  ACE_Double_Linked_List_Iterator_Base<QMS_Sub_Type_Element<string,string,ACE_RW_Mutex> >;
template class  ACE_Double_Linked_List_Iterator<QMS_Sub_Type_Element<string,string,ACE_RW_Mutex> >;
template class  ACE_Double_Linked_List_Reverse_Iterator<QMS_Sub_Type_Element<string,string,ACE_RW_Mutex> >;
template class  QMS_MLD_Containers<string,string,ACE_RW_Mutex>;
template class  QMS_Linked_List_Iterator_Base<string,string,ACE_RW_Mutex>;
template class  QMS_Linked_List_Iterator<string,string,ACE_RW_Mutex>;
template class  QMS_Linked_List_Reverse_Iterator<string,string,ACE_RW_Mutex>;
template class  QMS_Linked_List<string,string,ACE_RW_Mutex>;
template class  QMS_Node<string,string,ACE_RW_Mutex>;
template class  QMS_MLD_Factory<string,string,ACE_RW_Mutex>;
template class  Linked_List_Factory<string,string,ACE_RW_Mutex>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate QMS_Sub_Type_Element<string,string,ACE_RW_Mutex>
#pragma instantiate ACE_Double_Linked_List<QMS_Sub_Type_Element<string,string,ACE_RW_Mutex> >
#pragma instantiate ACE_Double_Linked_List_Iterator_Base<QMS_Sub_Type_Element<string,string,ACE_RW_Mutex> >
#pragma instantiate ACE_Double_Linked_List_Iterator<QMS_Sub_Type_Element<string,string,ACE_RW_Mutex> >
#pragma instantiate ACE_Double_Linked_List_Reverse_Iterator<QMS_Sub_Type_Element<string,string,ACE_RW_Mutex> >
#pragma instantiate QMS_MLD_Containers<string,string,ACE_RW_Mutex>
#pragma instantiate QMS_Linked_List_Iterator_Base<string,string,ACE_RW_Mutex>
#pragma instantiate QMS_Linked_List_Iterator<string,string,ACE_RW_Mutex>
#pragma instantiate QMS_Linked_List_Reverse_Iterator<string,string,ACE_RW_Mutex>
#pragma instantiate QMS_Linked_List<string,string,ACE_RW_Mutex>
#pragma instantiate QMS_Node<string,string,ACE_RW_Mutex>
#pragma instantiate QMS_MLD_Factory<string,string,ACE_RW_Mutex>
#pragma instantiate Linked_List_Factory<string,string,ACE_RW_Mutex>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
