/*                               -*- Mode: C++ -*- 
 * List_Data_Remos.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Mon Jul 16 15:29:24 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Tue Oct 30 13:21:50 2001
 * Last Machine Used: ember.stdc.com
 * Update Count     : 21
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
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



/** @file 
 *  @ingroup RemosSensor
 *  @brief Contains a simple class that encapsulates event chanel information
 * 
 * $Id: List_Data_Remos.h,v 1.9 2001/12/09 02:14:17 nath Exp $
 */


#ifndef _LIST_DATA_REMOS_H_
#define _LIST_DATA_REMOS_H_

#include <string>

#include "ace/Synch.h"
#include "ace/Thread.h"
#include "ace/Containers_T.h"
 
#include "orbsvcs/CosNamingC.h"
#include "orbsvcs/Event_Utilities.h"

#include "Debug.h"
namespace STDC
{
  namespace QMS
  {
    namespace Citizen
    {
      /**
       * @brief A simple encapsulation of event channel information
       *
       * Essentially this is a class that is a awrapper around a name,
       * which is a string, and a value, that may be either another
       * string, or an integer.
       */
      class Sensor_Data_Element_Remos
      {
      public:
	/**
	 * @brief  The default constructor for the class Sensor_Data_Element_Remos 
	 * @param name The associated name of this element
	 * @param value The associated numerical value
	 */
	Sensor_Data_Element_Remos (string name = "", int value = 0) :
	  _name(name), _valInt(value),_valString("")
	{
	  QMS_Trace ("Sensor_Data_Element_Remos", __LINE__, __FILE__);
	};
	    
	/**
	 * @overload
	 * @brief  The default constructor for the class Sensor_Data_Element_Remos 
	 * @param name The associated name of this element
	 * @param value The associated stringvalue
	 */
	Sensor_Data_Element_Remos(string name, string value) :
	  _name(name), _valInt(0), _valString(value)
	{
	  QMS_Trace ("Sensor_Data_Element_Remos", __LINE__, __FILE__);
	};
	    
	///the copy constructor
	Sensor_Data_Element_Remos(const Sensor_Data_Element_Remos& rhs) :
	  _name(rhs._name), _valInt(rhs._valInt), 
	  _valString(rhs._valString)
	{
	  QMS_Trace ("Sensor_Data_Element_Remos", __LINE__, __FILE__);
	};
	/// the assignment operator
	Sensor_Data_Element_Remos& 
	operator=(const Sensor_Data_Element_Remos& rhs)
	{
	  QMS_Trace ("Sensor_Data_Element_Remos::operator=", __LINE__, __FILE__);
	  if(&rhs != this)
	   {
	     ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
		 
	     this->_name = rhs._name;
	     this->_valInt = rhs._valInt;
	     this->_valString = rhs._valString;
	   }
	  return *this;
	}
	    
	    
	/// the default address-of operators
	// Sensor_Data_Element_Remos* operator&()             { return this; };
	// const Sensor_Data_Element_Remos* operator&() const { return this; };
	/**
	 * @brief Set the name of this element
	 * @param name The name of this element
	 */
	void set_name(string& name)
	{
	  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
	  this->_name = name;
	};
	    
	/**
	 * @brief Get the name of this element
	 * @return The name of this element
	 */
	string get_name(void)
	{
	  ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
	  return this->_name;
	};
	    
	/**
	 * @brief Set the string value of this element
	 * @param value The value of this element
	 */
	void set_string_val(string& value)
	{
	  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
	  this->_valString = value;
	};
	    
	/**
	 * @brief Get the string value of this element
	 * @return The string value of this element
	 */
	string get_string_val(void)
	{
	  ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
	  return this->_valString;
	};
	    
	/**
	 * @brief Set the numerical value of this element
	 * @param value The value of this element
	 */
	void set_int_val(int value)
	{
	  ACE_Write_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
	  this->_valInt = value;
	};
	    
	/**
	 * @brief Get the numerical value of this element
	 * @return The numerical value of this element
	 */
	int get_int_val(void)
	{
	  ACE_Read_Guard<ACE_Thread_Mutex> guard(this->asset_guard);
	  return this->_valInt;
	};
      protected:
	/// The name of this element
	string _name;
	/// The numerical value of this element
	int _valInt;
	/// The string value of this element
	string _valString;
      private:
	/// A mutex used for protecting the values
	ACE_Thread_Mutex asset_guard;
      };	// end of class Sensor_Data_Element_Remos
    };
  };
};


#endif /* _LIST_DATA_REMOS_H_ */
