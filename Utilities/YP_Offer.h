//                              -*- Mode: C++ -*- 
// YP_Offer.h --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Fri Sep 21 15:03:09 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Oct 24 09:27:16 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 10
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// 
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


/** @file 
 *  @ingroup Utilities
 *  @brief Convenience methods to create Service types used in CORBA
 *  Trading offers.
 *
 * $Id: YP_Offer.h,v 1.8 2001/12/02 03:30:27 srivasta Exp $
 */

#ifndef _YP_OFFER_H_
#define _YP_OFFER_H_

#include "ace/OS.h"
#include "tao/ORB.h"
#include "CORBA_Handles.h"
#include "orbsvcs/Trader/Trader_Utils.h"
/// The YP Service Type name used by all QMS Citizens
#define YP_SERVICE_TYPE "STDC_QMS_CITIZEN_YPOFFER"

namespace STDC
{
  namespace QMS 
  {
    /// This adds the derived service type used by specific QMS Citizens
    void
    Add_YP_ServiceType(STDC::QMS::CORBA_Handles *handles_p,
		       CORBA::Environment &ACE_TRY_ENV = 
		       TAO_default_environment());
    ///  This function adds the base service type that is used by all citizens
    void
    Add_YP_SubType(STDC::QMS::CORBA_Handles *handles_p,
		   const char * service_type,
		   const char * interface_repository_id,
		   CORBA::Environment &ACE_TRY_ENV = 
		   TAO_default_environment());
  };
};



#endif /* _YP_OFFER_H_ */
