// ListOffers.h
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

#ifndef LISTOFFERS_H
#define LISTOFFERS_H

/** @file ListOffers.h
 * @ingroup Trader
 * @brief Lists the offers pertaining to a service type.
 */

#include "ace/OS.h"
#include "CORBA_Handles.h"
#include "Debug.h"
#include "YP_Offer.h"
#include "orbsvcs/Trader/Trader_Utils.h"

#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"

using namespace CosTradingRepos;
using namespace CosTrading;

#include <string>
#include <iostream>
#include <iomanip>

#include <cstring>
#include <csignal>
#include <cstdio>


#if defined (_WIN32)
#define setw	std::setw
#define setiosflags	std::setiosflags
#endif

/// using the std name space.
using namespace std;

/// Method that prints the offers pertaining to a service type.
void
print_offers (CosTrading::Lookup_ptr , char *, char * , CORBA_Environment &);

/// Lists all the Service Types in the Repository.
void
list_all_types (CosTrading::Lookup_ptr , CORBA::Environment& ) 
               ACE_THROW_SPEC ((CORBA::SystemException));

#endif /* LISTOFFERS_H */
