/*                               -*- Mode: C++ -*- 
 * Pipe_Proxy_Remos.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Wed May  9 13:09:30 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu Nov 29 14:11:42 2001
 * Last Machine Used: glaurung.stdc.com
 * Update Count     : 32
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * $Id: Pipe_Proxy_Remos.h,v 1.9 2001/12/09 02:14:18 nath Exp $
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
 * @brief A pure virtual class to interact with probes using simple pipes
 *
 */
#ifndef __PIPE_PROXY_REMOS_H_
#define __PIPE_PROXY_REMOS_H_

#include "Debug.h"
#include "Probe_Proxy_Remos.h"
#include "EC_Adapter.h"

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
       * @brief A pure virtual class to interact with probes using simple pipes
       *
       * This is the root of a heirarchy of classes that provides a
       * polymorphic abstraction layer for interacting with probes using a
       * simple pipe (standard UNIX paradigm).
       *
       * This adds the knowledge of the pathname of the executable to run as
       * a child, the command line argument that one provides the child
       * process, and the environment that the child process runs in.
       */
      class Pipe_Proxy_Remos : public virtual  STDC::QMS::Citizen::Probe_Proxy_Remos
      {
      public:
	/// The default constructor for the class Pipe_Proxy_Remos
	Pipe_Proxy_Remos(const char *file_name_p, char *const argv[], 
		   Meta_Data_Remos &parent, string & key):
	  Probe_Proxy_Remos(parent, key), 
	  file_name_p_(const_cast<char *>(file_name_p)), 
	  argv_(const_cast<char * * >(argv))	{};
	      
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
	virtual ~Pipe_Proxy_Remos();
	      
      protected:
	/// Initialize the probe object, creating the pipes etc  
	virtual int init(const char *file_name_p, char *const argv[]);
	/// The file name of the probe to call
	char * file_name_p_;
	/// The command line arguments
	char **argv_;
	      
	/// The control pipe
	int ctrlpipe[2];
	/// The data pipe
	int datapipe[2];
      };	// end of class Pipe_Proxy_Remos  
    };
  };
};


#endif /* _PIPE_PROXY_REMOS_H_ */
