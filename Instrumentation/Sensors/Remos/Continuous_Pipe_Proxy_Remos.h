/*                               -*- Mode: C++ -*- 
 * Continuous_Pipe_Proxy_Remos.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Wed May  9 13:09:30 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Sat Dec  1 01:07:38 2001
 * Last Machine Used: ember.stdc.com
 * Update Count     : 23
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * $Id: Continuous_Pipe_Proxy_Remos.h,v 1.9 2001/12/09 02:14:17 nath Exp $
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
 * @ingroup RemosSensor
 * @brief A concrete abstraction object for sophisticated probes using pipes
 *
 */

#ifndef _CONTINUOUS_PIPE_PROXY_REMOS_REMOS_H_
#define _CONTINUOUS_PIPE_PROXY_REMOS_REMOS_H_

#include "Pipe_Proxy_Remos.h"

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
	
      /**
       * @ingroup RemosSensor
       * @brief A concrete abstraction object for probes using simple pipes
       *
       * This is a concrete class derived from the virtual class for
       * interacting with probes using simple pipes. The distinguishing
       * characteristic of the probes handled by this class is that they are
       * complex; and implement their own session management. They can be
       * started, paused, and resumed, and, finally, killed. They can, then,
       * handle periodicity requirements on their own. These status change
       * commands are communicated from the Sensor to the probe through the
       * probes STDIN.
       */
      class Continuous_Pipe_Proxy_Remos : 
	public virtual STDC::QMS::Citizen::Pipe_Proxy_Remos
      {
      public:
	/// The default constructor for the class Continuous_Pipe_Proxy_Remos
	Continuous_Pipe_Proxy_Remos(const char *file_name_p,
			      char *const argv[],
			      Meta_Data_Remos & parent,
			      string & key
			      );
	  
        /// A pure virtual start method
        Dllexport virtual int start(void);
        /// A pure virtual Pause method
        Dllexport virtual int pause(void);
        /// A pure virtual Resume method
        Dllexport virtual int resume(void);
        /// A pure virtual Kill method
        Dllexport virtual int kill(void);
	/// A virtual method to deploy the probe
	Dllexport virtual int deploy(void);
	/// A pure virtual method to destroy this object
	virtual void destroy (void);
	/// A pure virtual send_command method
	Dllexport virtual int send_command(const string command);
	  
	/// the destructor
	virtual ~Continuous_Pipe_Proxy_Remos(){};
	  
      protected:
      };	// end of class Continuous_Pipe_Proxy_Remos
    };
  };
};



#endif /* _CONTINUOUS_PIPE_PROXY_REMOS_REMOS_H_ */
