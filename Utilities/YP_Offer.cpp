//                              -*- Mode: C++ -*- 
// YP_Offer.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Fri Sep 21 15:06:33 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Oct 24 17:33:08 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 19
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


/// RCS version string
static const char* version = 
    "$Id: YP_Offer.cpp,v 1.19 2001/12/02 03:30:27 srivasta Exp $";

/** @file 
 *  @ingroup Utilities
 *  @brief Convenience methods to create Service types used in CORBA
 *  Trading offers.
 *
 * $Id: YP_Offer.cpp,v 1.19 2001/12/02 03:30:27 srivasta Exp $
 */
#include  <exception>
#include <stdexcept>

#include "YP_Offer.h"
#include "Debug.h"

using std::invalid_argument;
/**
 * @brief This adds the derived service type used by specific QMS Citizens
 * @param handles_p A pointer to an initialized CORBA_Handles object
 * @param service_type_p The name of the derived service type
 * @param interface_repository_id ID of the IDL interface for the citizen
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * This function add a service type that inherits from the base service
 * type used by all QMS Citizens. 
 */
void
STDC::QMS::Add_YP_SubType(STDC::QMS::CORBA_Handles *handles_p,
			  const char * service_type_p,
                          const char * interface_repository_id,
			  CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Add_YP_SubType", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Add_YP_SubType\n");
  if(!service_type_p || !interface_repository_id)
   {
     cerr << "missing arguments" << endl;
     throw invalid_argument("Missing arguments");
   } /* end of if(!service_type_p || !interface_repository_id) */

  ACE_TRY
    {
      CosTrading::Lookup_var lookup = 
        handles_p->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      
      CORBA::Object_var obj = lookup->type_repos(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CosTradingRepos::ServiceTypeRepository_var repos = 
        CosTradingRepos::ServiceTypeRepository::_narrow(obj.in(),
                                                        ACE_TRY_ENV);
      if(CORBA::is_nil(repos.in()))
       {
         cerr << "Not a type repository reference" << endl;
         throw 0;
       } /* end of if(CORBA::in_nil(repos)) */
      
      CosTradingRepos::ServiceTypeRepository::PropStructSeq props;
      props.length(0);

      CosTradingRepos::ServiceTypeRepository::ServiceTypeNameSeq base_types;
      base_types.length(1);
      base_types[0] = CORBA::string_dup (YP_SERVICE_TYPE);
      
      repos->add_type (service_type_p, interface_repository_id, props,
		       base_types, ACE_TRY_ENV );
      ACE_CHECK;
   }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ServiceTypeExists, ste)
    {
      ACE_PRINT_EXCEPTION (ste, "STDC::QMS::Add_YP_ServiceType - exists");
      if (ste.name.in () != 0)
	cerr << "ServiceTypeExists: " <<  ste.name.in() <<endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::IllegalPropertyName, excp)
    {
      ACE_PRINT_EXCEPTION (excp, "Adding Generic Sensor sub type");
      
      if (excp.name.in () != 0)
        cerr << "IllegalPropertyName: " << excp.name.in () << endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,vtr)
    {
      ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType");
      cerr << "ValueTypeRedefinition" << endl;      
      if (vtr.type_1.in () != 0)
	cerr <<  "Type One:" <<  vtr.type_2.in ()  << endl;
      if (vtr.type_2.in () != 0)
	cerr << "Type Two: " << vtr.type_2.in () << endl;
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Error adding service type");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;      
}

/**
 * @brief This function adds the base service type that is used by all citizens
 * @param handles_p A pointer to an initialized CORBA_Handles object
 * @param ACE_TRY_ENV CORBA env for propogating exceptions
 *
 * This is the base service type for all QMS Citizen YP offers. As
 * such, it defines the preset property names and their types,
 * enabling these preset types to be searchable. Having this as a
 * common utility functiuon ensures that all Citizens shall be in
 * sync
 */
void
STDC::QMS::Add_YP_ServiceType(STDC::QMS::CORBA_Handles *handles_p,
			      CORBA::Environment &ACE_TRY_ENV)
{
  QMS_Trace("STDC::QMS::Add_YP_ServiceType", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: STDC::QMS::Add_YP_ServiceType\n");

  ACE_TRY
    {
      CosTrading::Lookup_var lookup = 
	handles_p->get_lookup_handle(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::Object_var obj = lookup->type_repos(ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CosTradingRepos::ServiceTypeRepository_var repos = 
	CosTradingRepos::ServiceTypeRepository::_narrow(obj.in(),
							ACE_TRY_ENV);
      if(CORBA::is_nil(repos.in()))
       {
	 cerr << "Not a type repository reference" << endl;
	 throw 0;
       } /* end of if(CORBA::in_nil(repos)) */
      CosTradingRepos::ServiceTypeRepository::PropStructSeq props;
      props.length(18);
      
      props[0].name  = CORBA::string_dup ("QMS_UNIQ_NAME_CATEGORY");
      props[1].name  = CORBA::string_dup ("QMS_UNIQ_NAME_HOST_NAME");
      props[2].name  = CORBA::string_dup ("QMS_UNIQ_NAME_UUID");
      props[3].name  = CORBA::string_dup ("VERSION");
      props[4].name  = CORBA::string_dup ("SUPPLIER_ID");
      props[5].name  = CORBA::string_dup ("DESCRIPTION");
      props[6].name  = CORBA::string_dup ("PROBE_SCHEMA_URI");
      props[7].name  = CORBA::string_dup ("QMS_SCHEMA_URI");
      props[8].name  = CORBA::string_dup ("QMS_YP_PROP_1");
      props[9].name  = CORBA::string_dup ("QMS_YP_PROP_2");
      props[10].name  = CORBA::string_dup ("QMS_YP_PROP_3");
      props[11].name  = CORBA::string_dup ("QMS_YP_PROP_4");
      props[12].name = CORBA::string_dup ("QMS_YP_PROP_5");
      props[13].name = CORBA::string_dup ("QMS_YP_PROP_6");
      props[14].name = CORBA::string_dup ("QMS_YP_PROP_7");
      props[15].name = CORBA::string_dup ("QMS_YP_PROP_8");
      props[16].name = CORBA::string_dup ("QMS_YP_PROP_9");
      props[17].name = CORBA::string_dup ("QMS_YP_PROP_10");


      int i; 
      for(i = 0; i < 4; i++)
       {
	 props[i].value_type = CORBA::TypeCode::_duplicate(CORBA::_tc_string);
	 props[i].mode = 
	   CosTradingRepos::ServiceTypeRepository::PROP_MANDATORY_READONLY;
       } /* end of for(int i = 0; i < 4; i++) */

      props[4].value_type = CORBA::TypeCode::_duplicate(CORBA::_tc_ulong);
      props[4].mode = CosTradingRepos::ServiceTypeRepository::PROP_READONLY;

      for(i = 5; i < 18; i++)
       {
	 props[i].value_type = CORBA::TypeCode::_duplicate(CORBA::_tc_string);
	 props[i].mode = 
	   CosTradingRepos::ServiceTypeRepository::PROP_NORMAL;
       } /* end of for(int i = 0; i < 18; i++) */
      
      CosTradingRepos::ServiceTypeRepository::ServiceTypeNameSeq base_types;
      //repos->add_type ("STDC::QMS::Citizen::citizen", 
      repos->add_type (YP_SERVICE_TYPE, 
		       "IDL:STDC/QMS/Citizen:1.0", props, base_types,
		       ACE_TRY_ENV );
      ACE_CHECK;

      
      
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ServiceTypeExists, ste)
    {
      ACE_PRINT_EXCEPTION (ste, "Adding YP_ServiceType");
      
      if (ste.name.in () != 0)
	cerr <<  "ServiceTypeExists: \n" << ste.name.in () << endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::IllegalPropertyName, excp)
    {
      ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType");
      
      if (excp.name.in () != 0)
	cerr <<  "IllegalPropertyName: " << excp.name.in () << endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,vtr)
    {
      ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType");
      cerr << "ValueTypeRedefinition" << endl;
      if (vtr.type_1.in () != 0)
	cerr <<  "Type One:" << vtr.type_2.in () << endl;
      if (vtr.type_2.in () != 0)
	cerr <<  "Type Two:" << vtr.type_2.in ()<< endl;
      ACE_RE_THROW;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
			   "Error adding service type");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
}
