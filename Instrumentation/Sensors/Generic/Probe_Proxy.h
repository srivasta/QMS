/*                               -*- Mode: C++ -*- 
 * Probe_Proxy.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Wed May  9 13:01:21 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Sat Dec  1 00:22:22 2001
 * Last Machine Used: ember.stdc.com
 * Update Count     : 43
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * $Id: Probe_Proxy.h,v 1.11 2001/12/09 02:11:58 nath Exp $
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


/**
 * @file 
 * @ingroup GenericSensor
 * @brief A pure virtual superclass for proxies to probes
 *
 */
#ifndef _PROBE_PROXY_H_
#define _PROBE_PROXY_H_



#include "ace/Synch.h"
#include "Instrumentation.h"
#include "Meta_Data.h"

/// Windows needs this to export the member functions.
#if defined (_WIN32) /* Only Win32 needs special treatment. */
#   define Dllexport  __declspec( dllexport )
#else
#   define Dllexport
#endif

namespace STDC
{
  namespace QMS
  {
    namespace Citizen
    {
      
      // forward definition
      class Probe_Proxy;
      class Meta_Data;

      /**
       * @ingroup GenericSensor
       * @brief A pure virtual superclass for proxies to probes
       *
       * This is the root of a heirarchy of classes that provides a
       * polymorphic abstraction layer for interacting with probes. For each
       * distinct Sensor-Probe interaction protocol there shall be an
       * derived class to encapsulate the unique interaction.  This class
       * sets up the (few) utility methods common to all proebes 
       *
       */
      class Probe_Proxy
      {
      public:
	/// The default constructor for the class Probe_Proxy
	Probe_Proxy(Meta_Data& parent, string &key):
	  Am_I_Active(false), _metadata(parent), _key(key) 
	{
	  // Do Nothing
	};

        /// A pure virtual start method
        virtual int start(void) = 0;
        /// A pure virtual Pause method
        virtual int pause(void) = 0;
        /// A pure virtual Resume method
        virtual int resume(void) = 0;
        /// A pure virtual Kill method
        virtual int kill(void) = 0;
        /// A pure virtual method to deploy the probe
        virtual int deploy(void) = 0;
	/// A pure virtual method to destroy this object
	virtual void destroy (void) = 0;
	/// A pure virtual send_command method
	virtual int send_command(const string command) = 0;

	/// the destructor
	virtual ~Probe_Proxy()
	{
	  QMS_Trace("STDC::QMS::Citizen::Probe_Proxy::~Probe_Proxy",__LINE__,
		    __FILE__);
	  DEBUG0 (4, "DEBUG: STDC::QMS::Citizen::~Probe_Proxy");
	  this->_key.erase(); 
	  DEBUG0 (4, "DEBUG: ~Probe_Proxy -- done");
	};
	
      protected:
        /// The status of the probe (current or desired)
        enum Status { INACTIVE, ACTIVE, KILLED } status_;
        /// WHether the probe is actively sending us data
        bool Am_I_Active;
	/// Lock
	mutable ACE_RW_Thread_Mutex lock_;
	/// A pointer to the send method to send the data back
	Meta_Data & _metadata;
	/// The unique key that identifies a request to the sensor
	string _key;

      private:
	
      };	// end of class Probe_Proxy    
    };
  };
};
  

#endif /* _PROBE_PROXY_H_ */
