// QMS_Trader_ECInfo_Impl.h
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



#ifndef QMS_TRADER_ECINFO_IMPL_H
#define QMS_TRADER_ECINFO_IMPL_H

/** @file QMS_Trader_ECInfo_Impl.h
 * @ingroup Trader
 * @brief The interface definition of the QMS trader functionality
 * 
 */
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::ios;
using std::cerr;
using std::endl;
using std::string;

#include <fstream>

using std::ifstream;

#include <iomanip>

using std::setiosflags;
using std::resetiosflags;
using std::setw;
using std::setprecision;


#include "ECInfo.h"
#include "TraderS.h"

// Headers for the QMS_CORBA_HANDLES
#include "CORBA_Handles.h"
#include "Debug.h"

// The headers required for communicating with traders.
#include "orbsvcs/CosTradingC.h"
#include "orbsvcs/CosTradingReposC.h"

#include "orbsvcs/Trader/Trader.h"
#include "orbsvcs/Trader/Service_Type_Repository.h"

#define QMS_UNIQUE_CATEGORY_NAME        "QMS_TRADER"
#define	QT_SERVICE_TYPE	"STDC_QMS_CITIZEN_QMS_TRADER"
#define ECINFO_SERVICE_TYPE     "STDC_QMS_CITIZEN_QMS_TRADER_ECINFO"
#define SUPPLIER_SERVICE_TYPE   "STDC_QMS_CITIZEN_QMS_TRADER_SUPPLIERID"

// Default Event Channel Names for Announce, Data and Request.
#define DEFAULT_ANNOUNCE_CHANNEL	"QMS_D_ANN"
#define	DEFAULT_DATA_CHANNEL	"QMS_D_DAT"
#define DEFAULT_REQUEST_CHANNEL	"QMS_D_REQ"


using namespace CosTrading;
using namespace CosTradingRepos;


// STL headers.
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib> 

// using namespace std.
using namespace std;


/** @class QMS_Trader_ECInfo_Impl
 * @ingroup Trader
 * @brief servant class for handling different event channel information.
 *
 * This QMS_Trader_ECInfo_Impl class stores the information pertaining to a
 * QMSUniqueName category in a MAP data structure. The key to the MAP being 
 * the QMSUniqueName category and associated value is list of ECInfo classes 
 * that provide the event channel names and event ids of specific event
 * channel type (announce, data and request). Since each
 * QMSUniqueName category is associated with three different event channel
 * classes, there are three MAP data structures that store this
 * information against a QMSUniqueName category
 *
 */


namespace STDC
{
  namespace QMS
    {
      namespace Citizen
	{
	  class QMS_Trader_ECInfo_Impl : public POA_STDC::QMS::Citizen::QMS_Trader_ECInfo
	    {

	    public:

	      /**  default constructor **/
	      QMS_Trader_ECInfo_Impl();


	      /** destructor **/
	      ~QMS_Trader_ECInfo_Impl();


	      /** The init Method **/
	      void init (char *, STDC::QMS::CORBA_Handles *ptr = 0,
                         CORBA::Environment &ACE_TRY_ENV =
                         TAO_default_environment ())
		ACE_THROW_SPEC (( CORBA::SystemException));
	      
	      /// @brief Pause the QMS_Trader_ECInfo_Impl temporarily
	      /// @param credentials The credentials of the requestor
	      /// @param reason      The reason for pausing the QMS_Trader_ECInfo_Impl
	      /// @param ack         Acknowledgement
	      ///
	      /// Unless the QMS_Trader_ECInfo_Impl is running, this is a no op.  
	      virtual void pause ( const char * reason, 
				   const char * credentials,
				   CORBA::Short_out ack)
		ACE_THROW_SPEC (( CORBA::SystemException));

	      /// @param credentials The credentials of the requestor
	      /// @param reason      The reason for pausing the QMS_Trader_ECInfo_Impl
	      /// @brief Resume a previously paused QMS_Trader_ECInfo_Impl
	      ///  
	      /// The QMS_Trader_ECInfo_Impl has to be in a paused state
	      virtual void resume ( const char * reason, 
				    const char * credentials,
				    CORBA::Short_out ack)
		ACE_THROW_SPEC ((CORBA::SystemException));
    

	      /// @param credentials The credentials of the requestor
	      /// @param reason      The reason for pausing the QMS_Trader_ECInfo_Impl
	      /// @brief Stop the QMS_Trader_ECInfo_Impl
	      ///  
	      virtual void stop ( const char * reason, 
				  const char * credentials,
				  CORBA::Short_out ack)
		ACE_THROW_SPEC ((CORBA::SystemException));

	      /// @brief Disconnect from the event channel
	      /// @param reason The reason given for the command
	      /// @param credentials The security credentials 
	      /// @param ACE_TRY_ENV The CORBA exception environment

	      virtual void disconnect_EC (const char * reason, 
					  const char * credentials)
    
		ACE_THROW_SPEC ((CORBA::SystemException));

	      /// @brief Reconnect to the event channel
	      /// @param reason The reason given for the command
	      /// @param EC_Name The event Channel name to use
	      /// @param credentials The security credentials 
	      /// @param ACE_TRY_ENV The CORBA exception environment

	      virtual void reconnect_EC (const char * reason,
					 const char * EC_Name,
					 const char * credentials)
    
		ACE_THROW_SPEC ((CORBA::SystemException));

	      /// @brief Show the current operating level
	      /// @param level result
	      /// @param ACE_TRY_ENV The CORBA exception environment

	      virtual void show_operating_level ( CORBA::Short_out level)
    
		ACE_THROW_SPEC ((CORBA::SystemException));
  
	      /// @brief Set the current operating level
	      /// @param level The desired operating level
	      /// @param credentials The security credentials of the requestor
	      /// @param ACE_TRY_ENV The CORBA exception environment

	      virtual void set_operating_level ( CORBA::Short level, 
						 const char * credentials)
    
		ACE_THROW_SPEC ((CORBA::SystemException));
 
	      /// @brief Dump the statistics of the program
	      /// @param ACE_TRY_ENV The CORBA exception environment
	      /// @param credentials The security credentials of the requestor
	      /// @param stats The requested statistics

	      virtual void  stats ( const char * credentials, 
				    CORBA::String_out stats)
		ACE_THROW_SPEC ((CORBA::SystemException));

	      virtual void ping ( CORBA::Short_out ack)
		ACE_THROW_SPEC ((CORBA::SystemException));
  

	      /** method for returning list of announce channels **/
	      virtual STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq *
	      getAnnounceChannels (const char * qms_unique_name)
		ACE_THROW_SPEC ((CORBA::SystemException));

	      /**  method for returning list of data channels **/

	      virtual STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq *
	      getDataChannels (const char * qms_unique_name)
		ACE_THROW_SPEC ((CORBA::SystemException));


	      /**  method for returning list of request channels **/

	      virtual STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq *
	      getRequestChannels (const char * qms_unique_name)
		ACE_THROW_SPEC ((CORBA::SystemException));


	      /** method for providing the supplier Id. **/
 
	      virtual CORBA::ULong getSupplierID ( const char * description)
		ACE_THROW_SPEC ((CORBA::SystemException));

	    private:

	      /** The method for adding yp service type **/

	      void add_yp_serviceType(CORBA::Environment &ACE_TRY_ENV =
				      TAO_default_environment ())
		ACE_THROW_SPEC ((CORBA::SystemException,
		 CosTrading::IllegalServiceType,
		 CosTradingRepos::ServiceTypeRepository::ServiceTypeExists,
		 CosTradingRepos::ServiceTypeRepository::InterfaceTypeMismatch,
		 CosTrading::IllegalPropertyName,
		 CosTrading::DuplicatePropertyName,
		 CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
		 CosTrading::UnknownServiceType,
		 CosTradingRepos::ServiceTypeRepository::DuplicateServiceTypeName));
	      
	      /** Method for adding the register service type **/
	      
	      void add_registry_serviceType(CORBA::Environment &ACE_TRY_ENV =
					    TAO_default_environment ())
		ACE_THROW_SPEC ((CORBA::SystemException,
		 CosTrading::IllegalServiceType,
		 CosTradingRepos::ServiceTypeRepository::ServiceTypeExists,
		 CosTradingRepos::ServiceTypeRepository::InterfaceTypeMismatch,
		 CosTrading::IllegalPropertyName,
		 CosTrading::DuplicatePropertyName,
		 CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
		 CosTrading::UnknownServiceType,
		 CosTradingRepos::ServiceTypeRepository::DuplicateServiceTypeName));
	      
	      /** Method for adding the Supplier service type **/
	      
	      void add_supplier_serviceType(CORBA::Environment &ACE_TRY_ENV =
					    TAO_default_environment ())
		ACE_THROW_SPEC ((CORBA::SystemException,
		 CosTrading::IllegalServiceType,
		 CosTradingRepos::ServiceTypeRepository::ServiceTypeExists,
		 CosTradingRepos::ServiceTypeRepository::InterfaceTypeMismatch,
		 CosTrading::IllegalPropertyName,
		 CosTrading::DuplicatePropertyName,
		 CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
		 CosTrading::UnknownServiceType,
		 CosTradingRepos::ServiceTypeRepository::DuplicateServiceTypeName));
	      
	      

	      /** method for exporting the offers to the trader **/

	      void offer_exporter (CORBA::Environment &ACE_TRY_ENV = 
				   TAO_default_environment ()) 
		ACE_THROW_SPEC ((CORBA::SystemException,
				 CosTrading::Register::InvalidObjectRef,
				 CosTrading::IllegalServiceType,
				 CosTrading::UnknownServiceType,
				 CosTrading::Register::InterfaceTypeMismatch,
				 CosTrading::IllegalPropertyName,
				 CosTrading::PropertyTypeMismatch,
				 CosTrading::ReadonlyDynamicProperty,
				 CosTrading::MissingMandatoryProperty,
				 CosTrading::DuplicatePropertyName));

	      /** method for importing the offers from the trader. **/
	      void offer_importer (string&, string&, list< ECInfo >&, 
				   CORBA::Environment &ACE_TRY_ENV = 
				   TAO_default_environment ()) 
		ACE_THROW_SPEC ((CORBA::SystemException,
				 CosTrading::IllegalServiceType,
				 CosTrading::UnknownServiceType,
				 CosTrading::IllegalConstraint,
				 CosTrading::Lookup::IllegalPreference,
				 CosTrading::Lookup::IllegalPolicyName,
				 CosTrading::Lookup::PolicyTypeMismatch,
				 CosTrading::Lookup::InvalidPolicyValue,
				 CosTrading::IllegalPropertyName,
				 CosTrading::DuplicatePropertyName,
				 CosTrading::DuplicatePolicyName));

	      /** method for importing supplierd id offers from the trader **/
	      void supplier_importer (CORBA::Environment &ACE_TRY_ENV = 
				      TAO_default_environment ()) 
		ACE_THROW_SPEC ((CORBA::SystemException,
				 CosTrading::IllegalServiceType,
				 CosTrading::UnknownServiceType,
				 CosTrading::IllegalConstraint,
				 CosTrading::Lookup::IllegalPreference,
				 CosTrading::Lookup::IllegalPolicyName,
				 CosTrading::Lookup::PolicyTypeMismatch,
				 CosTrading::Lookup::InvalidPolicyValue,
				 CosTrading::IllegalPropertyName,
				 CosTrading::DuplicatePropertyName,
				 CosTrading::DuplicatePolicyName));

	      /** method for exporting supplier id offers to the trader **/

	      void supplier_exporter (string &supplier_name,
				      CORBA::Environment &ACE_TRY_ENV = 
				      TAO_default_environment ()) 
		ACE_THROW_SPEC ((CORBA::SystemException,
				 CosTrading::Register::InvalidObjectRef,
				 CosTrading::IllegalServiceType,
				 CosTrading::UnknownServiceType,
				 CosTrading::Register::InterfaceTypeMismatch,
				 CosTrading::IllegalPropertyName,
				 CosTrading::PropertyTypeMismatch,
				 CosTrading::ReadonlyDynamicProperty,
				 CosTrading::MissingMandatoryProperty,
				 CosTrading::DuplicatePropertyName));

            /** method for adding offer for the YP_SubType **/

             void make_offer(CORBA::Environment &);

	      /** @var yp_service_type
	       * brief Variable to hold name of the yp service type 
	       */
	      char *yp_service_type;

	      /** @var r_service_type
	       * brief Variable to hold name of the register service type 
	       */
	      char *r_service_type;

	      /** @var supplier_service_type
	       * brief Variable to hold name of the register service type 
	       */
	      char *supplier_service_type;

	      /** @var config_file
	       * @brief variable to hold the name of the config file to read.
	       */
	      char *config_file;

	      /** @var supplierid_num
	       * @brief storage for supplierid number 
	       */
	      CORBA::ULong supplierid_num;

	      /** @var handles_p
	       * @brief Pointer to QMS_CORBA_HANDLES.
	       */
	      STDC::QMS::CORBA_Handles *handles_p;

	      /** @var handles_flag
	       * @brief flag indicating whether memory has been allocated.
	       */
	      int handles_flag;

	      /** @var lookup_p
	       * @brief Variable for holding the pointer to the lookup interface 
	       */
	      CosTrading::Lookup_ptr lookup_p;

	      /** @var lookup_v
	       * @brief A var variable for holding the lookup interface.
	       */
	      CosTrading::Lookup_var lookup_v;

	      /** @var eventid_num
	       * @brief storage for eventid number
	       */
	      CORBA::ULong eventid_num;

	      /** @var asset_guard
	       * @brief ACE Read Gaurd.
	       */

	      ACE_Thread_Mutex asset_guard;

	      /** @var repos_
	       * @brief A reference to a service type repository instance.
	       */
	      CosTradingRepos::ServiceTypeRepository_var repos_;
  
	      /** @var type_structs_
	       * @brief
	       */
	      CosTradingRepos::ServiceTypeRepository::TypeStruct type_struct_;

	      /** @var register_
	       * @brief 
	       */
	      CosTrading::Register_var register_;

	      /** @var eprops
	       * @brief Propery sequence which contains the properties.
	       *
	       */
	      CosTrading::PropertySeq eprops;

	      /** @var desc
	       * @brief description of supplier 
	       */
	      string desc;

	      /** @var level_
	       * @brief variable for holding the operating levels.
	       */
	      CORBA::Short level_;

	      /** @var offerid_list
	       * @brief a list for holding the offer ids.
	       */
	      vector<CosTrading::OfferId_var> offerid_list;

	      /** @typedef std::list<string> stringList;
	       * @brief list of strings for storing QMS_UNIQ_NAME_CATEGORY
	       */
	      typedef list<string> stringList;

	      /** @typedef std::list< ECInfo > ECList;
	       * @brief list of Event channel information data.
	       */
	      typedef list< ECInfo > ECList;

	      /** @var announce_values, data_values, request_values
	       * @brief Variables containing std::list of ECInfo classes.
	       */
	      ECList announce_values, data_values, request_values;

	      /** @var Info
	       * @brief Instance of ECInfo class.
	       */
	      ECInfo Info;

	      /** @var index
	       * @brief A std::string variable.
	       */
	      string index;

	      /** Corba method returning sequence of announce channels **/
	      STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq *announceECSeq;

	      /** Corba method returning sequence of data channels **/
	      STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq * dataECSeq;

	      /** Corba method returning sequence of request channels **/
	      STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq * requestECSeq;

	    };
	};
    };
};

#endif /* QMS_TRADER_ECINFO_IMPL_H */

