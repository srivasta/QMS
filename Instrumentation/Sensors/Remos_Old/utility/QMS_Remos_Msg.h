//                              -*- Mode: C++ -*-
// QMS_Remos_Msg.h ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Wed Oct 18 16:38:44 2000
// Created On Node  : ember
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu May  3 16:46:36 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 41
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
// $Id: QMS_Remos_Msg.h,v 1.11 2001/10/21 08:54:10 srivasta Exp $
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


#ifndef QMS_MSG_H
# define QMS_MSG_H
/** @file QMS_Remos_Msg.h
 *  @ingroup Remos
 *  @brief Interface definition for the Remos message class.
 */

#include <string>

#include "ace/Synch.h"
#include "ace/Thread.h"

#include "Remos_Datastructs.h"

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

using namespace std;

/** @class QMS_Remos_Msg QMS_Remos_Msg.h "QMS/QMS_Remos_Msg.h"
 *  @ingroup Remos
 *  @brief This is a utility class providing XML conversion routines
 *
 * This class is an utility class provided to facilitate conversions
 * back and from XML. At some pint a validating SAX2 parser shall be
 * used to parse and validate the XML. The test_msg.cpp file shows
 * example usage for this class. Performance metrics for this class
   can be determined using the file bench_xml.cpp
 *
 * The most common use for this class is as follows:
 *  - On the initiator end of the transaction, a previously created
 *    Data_struct or a Query_struct structure is inserted into a
 *    QMS_Remos_Msg object. This causes conversion into an internal
 *    representation, which is an XML document.
 *  - Next, the message is extracted as a string. This is an XML
 *    document, and this document is sent over the wire.
 *  - On the recieving end, the XML document in a string is inserted
 *    into another QMS_Remos_Msg object
 *  - This message can now be extracted into a corresponding struct,
 *    and the XML document is parsed on the fly during the
 *    extraction.
 */
class QMS_Remos_Msg
{
public:
  /// The default constructor
  Dllexport QMS_Remos_Msg();

  /** Various ways of inserting data into this message.
   */
  /// Insert a struct Query_struct into the message
  Dllexport void insert(const struct Query_struct &data);
  /// Insert a struct Data_struct into the message
  Dllexport void insert(const struct Data_struct &data);
  /// Insert a string into the message
  Dllexport void insert(const string &data);

  /// Of course, one can construct a message piece by piece.
  Dllexport void append(const char *data_p);

  /// Erase the message, discarding the data contained
  Dllexport void erase(void);

  /// The size of the data when expressed as a string
  Dllexport size_t size(void);
  /** Return the data in the form of a string. If the data had been
   * inserted as a struct, the XML representation is generated.
   */
  Dllexport const char *as_string(void);

  /* One can extract the data as a struct, even if it had been
   * inserted as an XML string.
   */
  /// Extract contents into a struct Query_struct
  Dllexport struct Query_struct *extract_query(void);
  /// Extract contents into a struct Data_struct
  Dllexport struct Data_struct  *extract_data(void);

private:
  /// Set a mutex to guard the data
  ACE_Thread_Mutex asset_guard;

  /// Internal variables
  static long sequence_no;
  string data;
};



# endif// QMS_MSG_H
