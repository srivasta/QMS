// Simple_Logger.h
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

/** @file Simple_Logger.h
 *  @ingroup Logger
 *  @brief A Simple Logger that logs information on all the Event Channels.
 *
 */

#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H

#include "ace/OS.h"
#include "ace/Synch.h"

#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"
#include "orbsvcs/CosTradingDynamicC.h"

#include "orbsvcs/Trader/Trader.h"
#include "orbsvcs/Trader/Trader_Utils.h"

#include "TraderC.h"
#include "Debug.h"
#include "Push_Consumer.h"
#include "YP_Offer.h"

#include <csignal>
#include <string>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <list>

using namespace CosTradingRepos;
using namespace CosTrading;
using namespace std;


namespace STDC
{
  namespace QMS
  {
    namespace Citizen
    {
       struct Consumer_Info
       {
          FILE *file_handle_p;
          ACE_Thread_Mutex asset_guard;
          string ec_name;
          int event_id;
       };

       struct Query
       { 
          string qun_category;
          string supplier_id;
          string ec_name;
       };
    };
  };
};


vector<STDC::QMS::Citizen::Query *> Query_List;
list<string> EC_Info;
list<string> query_strings;

vector<STDC::QMS::Push_Consumer *> consumer_list;
vector<STDC::QMS::Citizen::Consumer_Info *> consumer_info_list;

void 
get_offers( CosTrading::Lookup_ptr lookup_if,
                       STDC::QMS::Citizen::Query *query_info,
                       CORBA::Environment& ACE_TRY_ENV);

void
iterate_thru_offers(CosTrading::OfferIterator_ptr offer_iterator,
    CORBA::Environment& ACE_TRY_ENV)
             ACE_THROW_SPEC ((CORBA::SystemException));


void
get_name_id ( string &, CORBA::Long  &, string &);


void
fill_query_struct(list<string> & , vector<STDC::QMS::Citizen::Query *> & );

void
get_qms_trader_ref ( CosTrading::Lookup_ptr , 
                     STDC::QMS::Citizen::QMS_Trader_ECInfo_var & ,
                     CORBA::Environment&);

void
my_callback(const string &, void *);


void
disconnect_consumers (CORBA::Environment &);

void
clean_consumers (void);

void
clean_consumer_info_list(void);

#endif /* SIMPLE_LOGGER_H */
