//                              -*- Mode: C++ -*- 
// QMS_Sensor.h --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Thu Feb 22 22:14:18 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed May 16 09:36:22 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 8
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// 
// $Id: QMS_Sensor.h,v 1.4 2001/10/21 08:54:06 srivasta Exp $

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


#ifndef QMS_SENSOR_H
#define QMS_SENSOR_H

#include <string>

/** @file QMS_Sensor.h
 *  @ingroup Sensors 
 *  @brief Interface definition for the QMS Sensors
 *
 *  This file details the use cases that a QMS sensor presents to the
 *  rest of the system, apart from the Command and control interfaces
 *  all QMS citizens must implement.
 */

/** @class QMS_Sensor
 *  @ingroup Sensors 
 *  @brief Interface definition for the QMS Sensors
 *
 * This is a pure virtual interface superclass put in here to
 * solidify the interface. Additionally, this is a place holder for
 * implementing class functions that implement common utilities and
 * design patterns to be used by all sensors. 
 *
 * For example, the interface below (and the underlying use case)
 * assumes that the clients of the sensors would be able to modify a
 * previous request, perhaps adjusting parameters like trigger
 * threshold of the periodicity of reporting, or, even, canceling a
 * request prematurely. In order for this to happen, the simplistic
 * model of a thread per request, with all the information about the
 * request being maintained in the memory space of the thread acting
 * on the request, has to go. 
 *
 * So queries to the sensor have to be accessible from a later thread
 * handling the modification request, different from the thread
 * handling the data gathering for the request itself. 
 *
 * So, when a request comes in, the thread that is spawned by CORBA to
 * handle the request queues it up in a doubly linked list ( a general
 * purpose pattern that can be reused elsewhere in QMS). This would
 * require acquiring and release read and write locks on the linked
 * list, patterns that has been implemented elsewhere. 
 *
 * At this point, the initial job is scheduled for execution, and
 * inserted at the head of a time-and-priority based scheduling queue,
 * which is probably going to be implemented as a red-black tree indexed
 * on execution time, each node of which may be another red-black tree
 * indexed on priority. After insertion at the head of the queue
 * (acquiring the requisite write locks), the scheduler thread is
 * signaled. 
 * 
 * The scheduler thread checks the head of the queue, pulls the top
 * jobs off the queue, and adds them to a execution queue. After
 * taking care of all the jobs currently scheduled to be executed, the
 * scheduler arranges to be woken up when the4 next job is going to be
 * active, and goes back to sleep. (Timers and condition variable
 * design patterns are already available)
 *
 * The execution queue is tended to by a thread pool (yet another
 * pattern already available for use). After execution of a job on the
 * execution queue, the thread from the pool that perfomed this task
 * shall reschedule the job for the next iteration if applicable. 
 * 
 * It should be noted that the scheduling and execution queues do not
 * duplicate the data for each job, they merely manipulate pointers
 * to the data that is stored in the original input doubly linked
 * list. 
 */

class QMS_Sensor
{
public:
  /// the default constructor
  QMS_Sensor(){};
  
  /// the destructor
  virtual ~QMS_Sensor(){};	

  /// @param credentials The credentials of the entity making the request
  /// @brief Start the sensor
  virtual void start(string credentials,
		     CORBA::Environment &ACE_TRY_ENV) = 0;
  
  /// @param credentials The credentials of the entity making the request
  /// @param reason      The reason for pausing the sensor
  /// @brief Pause the sensor temporarily
  ///
  /// Unless the sensor is running, this is a no op.
  virtual void pause(string reason, string credentials, short &ack,
		     CORBA::Environment &ACE_TRY_ENV) = 0;
  
  /// @param credentials The credentials of the entity making the request
  /// @param reason      The reason for pausing the sensor
  /// @brief Resume a previously paused sensor
  ///  
  /// The sensor has to be in a paused state
  virtual void resume(string reason, string credentials, short &ack,
		     CORBA::Environment &ACE_TRY_ENV) = 0;

  /// @param credentials The credentials of the entity making the request
  /// @param reason      The reason for pausing the sensor
  /// @brief Stop the sensor
  ///  
  virtual void stop(string reason, string credentials, short &ack,
		     CORBA::Environment &ACE_TRY_ENV) = 0;

  /// @param credentials The credentials of the entity making the request
  /// @param reason      The reason for pausing the sensor
  /// @brief Update the Sensors registration with the trading and
  /// fault detection services
  virtual void update_registration(string reason, string credentials,
				   CORBA::Environment &ACE_TRY_ENV) = 0;

  /// @param credentials The credentials of the entity making the request
  /// @param reason      The reason for pausing the sensor
  /// @brief Reread the configuration files
  ///  
  /// Often used after and administrator has changed values, or after
  /// a probe has been installed or removed from the machine, causing
  /// the capabilities file to be changed. 
  virtual void reload_configuration(string reason, string credentials,
				    CORBA::Environment &ACE_TRY_ENV) = 0;

  /// @param credentials The credentials of the entity making the request
  /// @brief Get the current sensor security policy
  virtual void get_security_policy(string credentials, string &policy,
				   CORBA::Environment &ACE_TRY_ENV) = 0;

  /// @param credentials The credentials of the entity making the request
  /// @param policy The new security policy to be implemented by the sensor
  /// @brief Set a new security policy
  virtual void set_security_policy(string policy, string credentials,
				   CORBA::Environment &ACE_TRY_ENV) = 0;

  /// @param credentials The credentials of the entity making the request
  /// @brief Get the current sensor attributes
  virtual void get_attributes(string credentials, string &attributes,
			      CORBA::Environment &ACE_TRY_ENV) = 0;

  /// @param credentials The credentials of the entity making the request
  /// @param attributes The new set of attributes for the sensor
  /// @brief Set a new set of attributes 
  virtual void set_attributes(string attributes, string credentials,
			      CORBA::Environment &ACE_TRY_ENV) = 0;
  
protected:
  
private:
  
};	// end of class QMS_Sensor


#endif // QMS_SENSOR_H

