// ECInfo.h
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


#ifndef ECINFO_H
#define ECINFO_H

/** @file ECInfo.h
 * @ingroup Trader
 * @brief ECInfo class definition and declaration of it's methods.
 *
 * This class is used to store the EventChannel name and event id
 * associated with a specific QMSUniqueName category. Each QMSUniqueName
 * category is associated with three classes of event channels based on the
 * class of the event being published or consumed. The event channel classes 
 * are Announce, Data or Request.
 *
 * This class has accessor and mutator methods for accessing and
 * mutating the values of EventChannel name and event id.
 *
 * This class has a friend member function which is used for overloading
 * << operator , so that "cout" object can be used to print the contents 
 * of this class.
 *
 */

#include <iostream>
#include <string>

/** @namespace std
 * @brief Using namespace std for cout, endl, string and ostream.
 *
 */
using std::cout;
using std::endl;
using std::string;
using std::ostream;

/** @class ECInfo
 * @brief class for storing Event Channel name and event id information.
 *
 *  1:- Mutator method to change the Event Channel name and event id.
 *
 *  2:- Accessor method to access the these values.
 *
 *  3:- friend function to print the contents of class to ostream using 
 *      cout.
 *
 */
class ECInfo 
{

public:

        ///  default constructor 
	ECInfo(void);

        /// default destructor
	~ECInfo(void);
    
        /// Copy Constructor
        ECInfo(const ECInfo & );

        /// The = operator
        ECInfo & operator=(const ECInfo &);

        /// The == operator for comparison
        bool operator==(const ECInfo &);

        /// The == operator for comparison
        bool operator==(ECInfo &);

        /// The < operator for comparison
        bool operator< (ECInfo &);

        /// mutator method for setting the event channel name 
	void setName(string );

        /// accessor method for getting event channel name 
	string getName(void);

        /// mutator method for setting the event id 
	void setId(long );

        /// accessor method for getting the event id 
	long getId(void);

        /// Friend function to print class content on ostream using cout.
	friend ostream &operator<<( ostream&, const ECInfo &);

private :

        /** @var name
         * brief Variable to hold name of the Event Channel.
         */
	string name;

        /** @var id
         * brief Variable to hold event id associated with the Event Channel.
         */
	long id;

};

#endif /* ECINFO_H */
