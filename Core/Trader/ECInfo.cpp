// ECInfo.cpp
// Author           : Shivakumar C. Patil (shivakumar.patil@stdc.com)
// Description      :
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


/** @file ECInfo.cpp
 * @ingroup Trader
 * @brief Contains the implementation of methods for ECInfo class.
 *
 */

//local headers.

#include "ECInfo.h"


/** @fn ECInfo::ECInfo(void)
 * @brief ECInfo constructor
 * @param None.
 * @return None.
 */
ECInfo::ECInfo(void)
{


}

/** @fn ECInfo::~ECInfo(void)
 * @brief ECInfo destructor
 * @param None.
 * @return None.
 */
ECInfo::~ECInfo(void)
{


}

/** @fn ECInfo::ECInfo(const ECInfo &rhs)
 * @brief ECInfo Copy Constructor
 * @param rhs a const reference to ECInfo
 * return None
 */
ECInfo::ECInfo(const ECInfo &rhs)
{
  this->name = rhs.name;
  this->id = rhs.id;
}

/** @fn ECInfo::operator=(const ECInfo &rhs)
 * @brief The operator =
 * @param rhs the ECInfo to copy from
 * return ECInfo A reference to ECInfo
 */
ECInfo & ECInfo::operator=(const ECInfo &rhs)
{
  this->name = rhs.name;
  this->id = rhs.id;
  return *this;
}

bool ECInfo::operator==(const ECInfo &rhs)
{
  return (this->name == rhs.name) && (this->id == rhs.id);
}


bool ECInfo::operator==(ECInfo &rhs)
{
  return (this->name == rhs.name) && (this->id == rhs.id);
}

bool ECInfo::operator< (ECInfo &rhs)
{
 return this->name < rhs.name;
}


/** @fn void ECInfo::setName (string a)
 * @brief Method to change the event channel name.
 * @param a string that needs to be set as event channel name.
 * @return None.
 */
void
ECInfo::setName (string a)
{
	this->name = a;

}

/** @fn void ECInfo::setId(long b) 
 * @brief Method to change the event id.
 * @param b long value that needs to be set as event id.
 * @return None.
 */
void
ECInfo::setId(long b)
{
	this->id = b;

}

/** @fn string ECInfo::getName(void)
 * @brief Method to access event channel name.
 * @param None.
 * @return string
 */
string
ECInfo::getName (void)
{
	return this->name;

}

/** @fn long ECInfo::getId (void)
 * @brief Method to acces event id.
 * @param None.
 * @return long
 */
long
ECInfo::getId (void)
{
	return this->id;

}

/** @fn ostream &operator<<( ostream &out, const ECInfo &info)
 * @brief Friend function to print class content on ostream using cout.
 * @param out A reference to the ostream.
 * @param info A reference to ECInfo class for printing.
 * @return A reference to the ostream.
 */
ostream &operator<<( ostream &out, const ECInfo &info)
{
	out << info.name << '\t' << info.id << endl;
	return out;

}

