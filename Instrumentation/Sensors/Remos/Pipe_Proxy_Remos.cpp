//                              -*- Mode: C++ -*- 
// Pipe_Proxy_Remos.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Wed May  9 18:03:03 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Thu Dec  6 12:35:21 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 13
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// $Id: Pipe_Proxy_Remos.cpp,v 1.9 2001/12/09 02:14:18 nath Exp $
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


/**
 * @file 
 * @ingroup RemosSensor
 * @brief An implementation for the functions for a probe using pipes
 *
 */

#include "Debug.h"
#include "Pipe_Proxy_Remos.h"
#include "ace/Synch.h"

/**
 *  @brief Initialized the Probe Proxy
 *  @param file_name_p The full path name of the probe to be executed
 *  @param argv        Optional command line arguments
 *  @param envp        Optional environmental variables
 *  @return            1 on error, 0 otherwise
 */
int
STDC::QMS::Citizen::Pipe_Proxy_Remos::init(const char *file_name_p,
				     char *const argv[])
{
  QMS_Trace("STDC::QMS::Citizen::Pipe_Proxy_Remos::init", __LINE__, __FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::Citizen::Pipe_Proxy_Remos::init"); 
  ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->lock_);
  
  this->file_name_p_ = const_cast<char *>  (file_name_p);
  this->argv_ 	     = const_cast<char **> (argv);
  return 0;
}

/**
 * @brief The destrictor
 *
 */
STDC::QMS::Citizen::Pipe_Proxy_Remos::~Pipe_Proxy_Remos()
{
  QMS_Trace("STDC::QMS::Citizen::Pipe_Proxy_Remos::~Pipe_Proxy_Remos",
	    __LINE__,__FILE__);
  DEBUG0 (2, "DEBUG:STDC::QMS::Citizen::Pipe_Proxy_Remos::~Pipe_Proxy_Remos"); 
  DEBUG0 (4, "DEBUG: Deleting  arguments");
  if(this->argv_)
   {
     int i = 0;
     while(this->argv_[i])
      {
	DEBUG1 (4, "DEBUG: Deleting argument %d", i);
	delete [] this->argv_[i];
	this->argv_[i++] = 0;
      } /* end of while(this->argv_[i]) */
   } /* end of if(this->argv_) */
  DEBUG0 (4, "DEBUG: Done with ~Pipe_Proxy_Remos");
}
