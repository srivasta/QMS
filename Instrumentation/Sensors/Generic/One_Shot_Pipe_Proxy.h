/*                               -*- Mode: C++ -*- 
 * One_Shot_Pipe_Proxy.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Wed May  9 13:09:30 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu Nov 29 14:19:26 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 35
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * $Id: One_Shot_Pipe_Proxy.h,v 1.9 2001/12/09 02:11:58 nath Exp $
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
 * @brief A concrete abstraction object for simple probes using simple pipes
 *
 */

#ifndef _ONE_SHOT_PIPE_PROXY_H_
#define _ONE_SHOT_PIPE_PROXY_H_

#include <map>
#include <string>
#include "ace/Synch.h"
#include "Pipe_Proxy.h"


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
      
      /// The default refresh rate
#define DEFAULT_SLEEP 2
      /**
       * @ingroup GenericSensor
       * @brief A concrete abstraction object for probes using simple pipes
       *
       * This is a concrete class derived from the virtual class for
       * interacting with probes using simple pipes. The distinguishing
       * characteristic of the probes handled by this class is that they are
       * simple processes, with no concept of sessions. For each request,
       * the probe is deployed, it provides the data, and exits. Any
       * periodicity in the request, then, has to be handled in the proxy;
       * setting up loops and implementing pause/resume interation with that
       * loop. 
       */
      class One_Shot_Pipe_Proxy: public virtual STDC::QMS::Citizen::Pipe_Proxy
      {
      public:
	/// The default constructor for the class One_Shot_Pipe_Proxy
	One_Shot_Pipe_Proxy(const char *file_name_p, char *const argv[], 
			    Meta_Data &parent, 
			    string & key,
			    double refresh_rate = DEFAULT_SLEEP,
			    int iterations = 9999);
  
        /// A virtual start method
        Dllexport virtual int start(void);
        /// A virtual Pause method
        Dllexport virtual int pause(void);
        /// A virtual Resume method
        Dllexport virtual int resume(void);
        /// A virtual Kill method
        Dllexport virtual int kill(void);
	/// A virtual method to deploy the probe
	Dllexport virtual int deploy(void);
	/// A pure virtual method to destroy this object
	virtual void destroy (void);
        /// A pure virtual send_command method
        Dllexport virtual int send_command(const string command);

	/// the destructor
	Dllexport virtual ~One_Shot_Pipe_Proxy(){};

      protected:
	/// The refresh rate requested
	double refresh_rate_;
	/// The number of iterations asked for
	int iterations_;
      };	// end of class One_Shot_Pipe_Proxy
    };
  };
};



#endif /* _ONE_SHOT_PIPE_PROXY_H_ */
