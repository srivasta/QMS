// QMS_Trader_ECInfo_Impl.cpp
// Author           : Shivakumar C. Patil (shivakumar.patil@stdc.com)
// Description      : Component of the QMS Trader - Provides EC Information
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



/** @file QMS_Trader_ECInfo_Impl.cpp
 * @ingroup Trader
 * @brief Implementation of ECInfo class and it's methods.
 * 
 *
 */

// local headers.
#include "QMS_Trader_ECInfo_Impl.h"
#include "orbsvcs/Trader/Trader_Utils.h"
#include "YP_Offer.h"

/** 
 * @brief STDC::QMS::Citizen::QMS_Trader_ECInfo constructor
 * @param None.
 * @return None.
 *
 * 1:- This constructor calls the storeUniqueNames method to get a list 
 * of unique QMSUniqueName category strings.
 *
 * 2:- Calls the fillMaps() method to store MAP data structures with 
 *     QMSUniqueName categories as a key against list of ECInfo classes.
 */
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::QMS_Trader_ECInfo_Impl():yp_service_type(0),r_service_type(0),supplier_service_type(0),config_file(0),supplierid_num(20000),handles_p(0),handles_flag(0),lookup_p(0),lookup_v(0),eventid_num(10000)
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::QMS_Trader_ECInfo_Impl", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::QMS_Trader_ECInfo_Impl\n");
  r_service_type = new char[100];
  yp_service_type = new char[100];
  config_file = new char[100];
  supplier_service_type = new char[100];

  this->announce_values.clear();
  this->data_values.clear();
  this->request_values.clear();
}


/**
 * @brief QMS_Trader_ECInfo_Impl destructor
 * @param None.
 * @return None.
 */
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::~QMS_Trader_ECInfo_Impl()
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::~QMS_Trader_ECInfo_Impl()", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::~QMS_Trader_ECInfo_Impl()\n");

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY 
  {
      vector<CosTrading::OfferId_var>::iterator offerid_iter;
      for ( offerid_iter = offerid_list.begin(); 
                offerid_iter != offerid_list.end(); ++offerid_iter)
      {
          this->register_->withdraw (*offerid_iter, ACE_TRY_ENV);
          ACE_TRY_CHECK;
       }

  }
  ACE_CATCHANY
  {
    ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                    "QMS_Trader_ECInfo_Impl::~QMS_Trader_ECInfo_Impl");
    ACE_RE_THROW;
  }

  ACE_ENDTRY;
  ACE_CHECK;

  ACE_TRY 
  {
      this->repos_->remove_type (yp_service_type, ACE_TRY_ENV);
      ACE_TRY_CHECK;
      this->repos_->remove_type (r_service_type, ACE_TRY_ENV);
      ACE_TRY_CHECK;
      this->repos_->remove_type (supplier_service_type, ACE_TRY_ENV);
      ACE_TRY_CHECK;


  }
  ACE_CATCH (CosTrading::UnknownServiceType, excp)
  {
  if (excp.type.in () != 0)
      ACE_DEBUG ((LM_DEBUG, "Service type not yet registered: %s\n", excp.type.in ()));    
  }
  ACE_CATCHANY
  {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                      "QMS_Trader_ECInfo_Impl::~QMS_Trader_ECInfo_Impl");
      ACE_RE_THROW;
  }

  ACE_ENDTRY;
  ACE_CHECK;

  if ( this->handles_flag )
      delete this->handles_p;
  if (this->r_service_type != NULL)
      delete this->r_service_type;
  if (this->yp_service_type != NULL)
      delete this->yp_service_type;
  if (this->supplier_service_type != NULL)
      delete this->supplier_service_type;
  if (this->config_file != NULL)
      delete this->config_file;

}


/**
 * @brief The servant initialization method.
 * @param file The config file from which to read event channel information.
 * @param yp_type The yellow page service type.
 * @param r_type The service type for event channel information.
 * @param s_type The service type for supplier id information.
 * @param ptr Pointer to QMS_CORBA_HANDLES
 * @param ACE_TRY_ENV CORBA::Environment variable
 * @return None.
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::init(char *file, STDC::QMS::CORBA_Handles *ptr ,
                                  CORBA::Environment &ACE_TRY_ENV)
                                 ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::init", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::init\n");
  ACE_TRY
  {
      ACE_OS::strcpy(this->config_file, file);
      ACE_OS::strcpy(this->yp_service_type, QT_SERVICE_TYPE);
      ACE_OS::strcpy(this->r_service_type, ECINFO_SERVICE_TYPE);
      ACE_OS::strcpy(this->supplier_service_type, SUPPLIER_SERVICE_TYPE);

      DEBUG4(DEBUG_L_ENTER, "DEBUG: config file: %s yp type: %s register_type: %s  supplier type: %s\n", this->config_file, this->yp_service_type, this->r_service_type, this->supplier_service_type);

      if ( ptr != NULL) 
      {
          this->handles_p = ptr;
      }
      else 
      {
          DEBUG0(DEBUG_L_ENTER, "Creating new corba handles \n");
          this->handles_p = new STDC::QMS::CORBA_Handles();
          this->handles_flag = 1;
      }

      DEBUG0(DEBUG_L_ENTER, "Trying to get pointer to lookup handle\n");
      this->lookup_v = this->handles_p->get_lookup_handle(ACE_TRY_ENV);
      this->lookup_p = this->lookup_v.in();
      ACE_TRY_CHECK;

      assert(!CORBA::is_nil(this->lookup_p));

      DEBUG0(DEBUG_L_ENTER, "Got pointer to lookup handle\n");
      CORBA::Object_var obj = this->lookup_p->type_repos(ACE_TRY_ENV);
      ACE_TRY_CHECK;

      DEBUG0(DEBUG_L_ENTER, "Reading the type_repos attribute on lookup interface\n");

      this->repos_ = CosTradingRepos::ServiceTypeRepository::_narrow(obj.in(),ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0(DEBUG_L_ENTER, "init : Got the repository reference\n");
      this->register_ = this->lookup_p->register_if (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0(DEBUG_L_ENTER, "init :Adding yp Service type\n");
      this->add_yp_serviceType (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0(DEBUG_L_ENTER, "init :Querying the Trader for Supplier Id\n");
      this->supplier_importer (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DEBUG0(DEBUG_L_ENTER, "init :Exporting the offers for register Service type\n");
      this->offer_exporter (ACE_TRY_ENV);
 
      ACE_TRY_CHECK;
  }

  ACE_CATCHANY
  {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                      "QMS_Trader_ECInfo_Impl::init");
      ACE_RE_THROW;
  }

  ACE_ENDTRY;
  ACE_CHECK;

}

/** @brief Pause the QMS_Trader_ECInfo temporarily
 *  @param credentials The credentials of the entity making the request
 *  @param reason      The reason for pausing the QMS_Trader_ECInfo
 * 
 *  Unless the QMS_Trader_ECInfo is running, this is a no op.
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::pause(const char * reason, 
					   const char * credentials,
					   short &ack)

  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo::pause", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo::pause\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n", credentials,
	 reason );
  ack = 0;
  if(reason)
   {
     cerr << reason << endl;
   } /* end of if(reason) */
  if(credentials)
   {
     cerr << credentials << endl;
   } /* end of if(credentials) */
}

  
/** @brief Resume a previously paused QMS_Trader_ECInfo
 *  @param credentials The credentials of the entity making the request
 *  @param reason      The reason for resuming the QMS_Trader_ECInfo
 *   
 *  The QMS_Trader_ECInfo has to be in a paused state
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::resume(const char * reason,
					    const char * credentials,
					    short &ack)

  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo::resume", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo::resume\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n", credentials,
	 reason );
  if(reason)
   {
     cerr << reason << endl;
   } /* end of if(reason) */
  if(credentials)
   {
     cerr << credentials << endl;
   } /* end of if(credentials) */
  
  ack = 0;
}


/** @brief Stop the QMS_Trader_ECInfo
 *  @param credentials The credentials of the entity making the request
 *  @param reason      The reason for stopping the QMS_Trader_ECInfo
 *   
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::stop(const char * reason, 
					  const char * credentials, short &ack)

  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo::stop_QMS", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo::stop\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n", credentials, 
	 reason );
  if(reason)
   {
     cerr << reason << endl;
   } /* end of if(reason) */
  if(credentials)
   {
     cerr << credentials << endl;
   } /* end of if(credentials) */
  ack = 0;
  //delete this;
}

/** @brief Disconnect from the event channel
 *  @param reason The reason given for the command
 *  @param credentials The security credentials 
 *  @param ACE_TRY_ENV The CORBA exception environment
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::disconnect_EC (const char * reason, 
						    const char * credentials)

  ACE_THROW_SPEC ((
   CORBA::SystemException
   //QMS_Citizen::QMS_Citizen_Error
   ))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::disconnect_EC", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::disconnect_EC\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n", credentials, 
	 reason );
  if(reason)
   {
     cerr << reason << endl;
   } /* end of if(reason) */
  if(credentials)
   {
     cerr << credentials << endl;
   } /* end of if(credentials) */
}

  
/** @brief Reconnect to the event channel
 *  @param reason The reason given for the command
 *  @param EC_Name The event Channel name to use
 *  @param credentials The security credentials 
 *  @param ACE_TRY_ENV The CORBA exception environment
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::reconnect_EC (const char * reason,
						   const char * EC_Name,
						   const char * credentials)

  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::reconnect_EC", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::reconnect_EC\n");
  DEBUG2(DEBUG_L_ENTER, "DEBUG: Credentials %s; reason: %s\n", credentials,
	 reason );
  if(reason)
   {
     cerr << reason << endl;
   } /* end of if(reason) */
  if(credentials)
   {
     cerr << credentials << endl;
   } /* end of if(credentials) */
  if(EC_Name)
   {
     cerr << EC_Name << endl;
   } /* end of if(reason) */
  
}

/** @brief Show the current operating level
 *  @param level result
 *  @param ACE_TRY_ENV The CORBA exception environment
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::show_operating_level (CORBA::Short_out
							   level)

  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::show_operating_level", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::show_operating_level\n");
  level = this->level_;
}

  
/** @brief Set the current operating level
 *  @param level The desired operating level
 *  @param credentials The security credentials of the requesting entity
 *  @param ACE_TRY_ENV The CORBA exception environment
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::set_operating_level (CORBA::Short level, 
							  const char * credentials)

  ACE_THROW_SPEC ((CORBA::SystemException))

{
  QMS_Trace("QMS_Trader_ECInfo_Impl::set_operating_level", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::set_operating_level\n");
  DEBUG1(DEBUG_L_ENTER, "DEBUG: Credentials %s\n", credentials);
  if(level > 0)
   {
     this->level_ = level;
   } /* end of if(level > 0) */
  if(credentials)
   {
     cerr << credentials << endl;
   } /* end of if(credentials) */

}

 
/** @brief Dump the statistics of the program
 *  @param ACE_TRY_ENV The CORBA exception environment
 *  @param credentials The security credentials of the requesting entity
 *  @param stats The requested statistics
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::stats (const char * credentials, 
					    CORBA::String_out stats)

  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::stats", __LINE__, __FILE__);
  DEBUG1(DEBUG_L_ENTER, "DEBUG: Credentials %s\n", credentials);
  if(credentials)
   {
     cerr << credentials << endl;
   } /* end of if(credentials) */
  stats = "OK";
}


void 
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::ping ( CORBA::Short_out ack)

          ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::ping", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::ping\n");

  ack = 0;
}



/**
 * @brief Corba method returning sequence of announce channels
 * @param qms_unique_name A const char * containing QMSUniqueName category.
 * @param ACE_TRY_ENV Reference to CORBA::Environment variable.
 * @return Pointer to a sequence containing announce event channels information.
 *
 */
STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq *
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::getAnnounceChannels(const char * 
							 qms_unique_name )
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::getAnnounceChannels", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::getAnnounceChannels\n");

  ACE_TRY
  {
    CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ();
    this->index = qms_unique_name;
    string ectype("announce");
    announceECSeq = new STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq;
 
      this->offer_importer(this->index, ectype, this->announce_values, ACE_TRY_ENV);
      DEBUG1(DEBUG_L_ENTER, "DEBUG: getAnnounceChannels %d\n", announce_values.size());
      announceECSeq->length(announce_values.size());
      if ( this->announce_values.size() )
      { 
          ECList::iterator eclistiter;
          CORBA::ULong i = 0;

          for (eclistiter = this->announce_values.begin();
                (eclistiter != this->announce_values.end()) 
                          && ( i < announceECSeq->length());
                      ++eclistiter, ++i)
          {
              this->Info = *eclistiter;
              (*announceECSeq)[i].EventChannelName = 
              CORBA::string_dup((this->Info.getName()).c_str());
              (*announceECSeq)[i].EventId = this->Info.getId();
          }

          // clear the contents of the ECList.
          this->announce_values.clear();
      }
      else 
      {
        announceECSeq->length(1);
        (*announceECSeq)[0].EventChannelName = CORBA::string_dup (DEFAULT_ANNOUNCE_CHANNEL);
        (*announceECSeq)[0].EventId = (this->eventid_num);

        this->eprops.length(4);
        CosTrading::OfferId_var offer_id;
        CORBA::Object_ptr offer_obj = this->_this(ACE_TRY_ENV);
        CosTrading::Register_ptr reg = this->register_.in();
        ACE_TRY_CHECK;

        this->eprops[0].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
        this->eprops[0].value <<= (this->index.c_str());

        this->eprops[1].name = CORBA::string_dup("EC_NAME");
        this->eprops[1].value <<= DEFAULT_ANNOUNCE_CHANNEL;

        this->eprops[2].name = CORBA::string_dup("EC_ID");
        this->eprops[2].value <<= (this->eventid_num);

        this->eprops[3].name = CORBA::string_dup("EC_TYPE");
        this->eprops[3].value <<= ectype.c_str();

        offer_id = reg->_cxx_export(offer_obj, this->r_service_type, this->eprops,
                                            ACE_TRY_ENV);
        ACE_TRY_CHECK;
        this->offerid_list.push_back(offer_id);
	ACE_DEBUG ((LM_DEBUG, \
		    "New QMSUniqueName: \"%s\". Assigned [%s,%d,%s]\n", \
		    this->index.c_str(), DEFAULT_ANNOUNCE_CHANNEL, \
		    eventid_num, ectype.c_str() ));

        ACE_Read_Guard<ACE_Thread_Mutex>  guard(this->asset_guard);
        {
          this->eventid_num++;
        }
         
      } // end of else. Add the default announce channel for the existing 
        // QMSUniqueName category, since it is not there in the file.

  }

  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      ACE_RE_THROW;
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return announceECSeq;

}


/**
 * @brief Corba method returning sequence of data channels
 * @param qms_unique_name A const char * containing QMSUniqueName category
 * @param ACE_TRY_ENV Reference to CORBA::Environment variable.
 * @return Pointer to a sequence containing data event channels information.
 *
 */
STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq *
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::getDataChannels ( const char * qms_unique_name )

      ACE_THROW_SPEC ((
        CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::getDataChannels ", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::getDataChannels \n");

  ACE_TRY
  {
    CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ();
    this->index = qms_unique_name;
    string ectype("data");
    dataECSeq = new STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq;

      this->offer_importer(this->index, ectype, this->data_values, 
                                            ACE_TRY_ENV);
      //ACE_DEBUG ((LM_DEBUG, "%d\n", data_values.size()));
      DEBUG1(DEBUG_L_ENTER, "DEBUG: getDataChannels %d\n", data_values.size());
      dataECSeq->length(data_values.size());

      if ( this->data_values.size() )
      {
          ECList::iterator eclistiter;
          CORBA::ULong i = 0;


          for (eclistiter = this->data_values.begin();
                (eclistiter != this->data_values.end()) 
                && ( i < dataECSeq->length());
              ++eclistiter, ++i)
          {
              this->Info = *eclistiter;
              (*dataECSeq)[i].EventChannelName = 
              CORBA::string_dup((this->Info.getName()).c_str());
              (*dataECSeq)[i].EventId = this->Info.getId();
          }

          // clear the contents of the ECList.
          this->data_values.clear();
    
      }
      else
      {
        dataECSeq->length(1);
        (*dataECSeq)[0].EventChannelName = CORBA::string_dup (DEFAULT_DATA_CHANNEL);
        (*dataECSeq)[0].EventId = (this->eventid_num);

        this->eprops.length(4);
        CosTrading::OfferId_var offer_id;
        CORBA::Object_ptr offer_obj = this->_this(ACE_TRY_ENV);
        CosTrading::Register_ptr reg = this->register_.in();
        ACE_TRY_CHECK;

        this->eprops[0].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
        this->eprops[0].value <<= (this->index.c_str());

        this->eprops[1].name = CORBA::string_dup("EC_NAME");
        this->eprops[1].value <<= DEFAULT_DATA_CHANNEL;

        this->eprops[2].name = CORBA::string_dup("EC_ID");
        this->eprops[2].value <<= (this->eventid_num);

        this->eprops[3].name = CORBA::string_dup("EC_TYPE");
        this->eprops[3].value <<= ectype.c_str();

        offer_id = reg->_cxx_export(offer_obj, this->r_service_type, this->eprops,
                                            ACE_TRY_ENV);
        ACE_TRY_CHECK;
        this->offerid_list.push_back(offer_id);
	ACE_DEBUG ((LM_DEBUG, \
		    "New QMSUniqueName: \"%s\". Assigned [%s,%d,%s]\n", \
		    this->index.c_str(), DEFAULT_DATA_CHANNEL, \
		    eventid_num, ectype.c_str() ));

        ACE_Read_Guard<ACE_Thread_Mutex>  guard(this->asset_guard);
        {
          this->eventid_num++;
        }

      } // end of else. Add the default data channel for the existing 
        // QMSUniqueName category, since it is not there in the file.

  }

  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      ACE_RE_THROW;
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return dataECSeq;

}



/**
 * @brief Corba method returning sequence of request channels
 * @param qms_unique_name A const char * containing QMSUniqueName category
 * @param ACE_TRY_ENV Reference to CORBA::Environment variable.
 * @return Pointer to a sequence containing request event channels information.
 * 
 */
STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq *
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::getRequestChannels ( const char * qms_unique_name )
      ACE_THROW_SPEC ((
        CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::getRequestChannels ", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::getRequestChannels \n");
  ACE_TRY
  {
    CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ();
    this->index = qms_unique_name;
    string ectype("request");
    requestECSeq = new STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq;

       this->offer_importer(this->index, ectype, this->request_values, 
                                               ACE_TRY_ENV);
       //ACE_DEBUG ((LM_DEBUG, "%d\n", request_values.size()));
       DEBUG1(DEBUG_L_ENTER, "DEBUG: getRequestChannels %d\n", request_values.size());
       requestECSeq->length(request_values.size());
    
       if ( request_values.size() )
       {
  
           ECList::iterator eclistiter;
           CORBA::ULong i = 0;

           for (eclistiter = this->request_values.begin();
             (eclistiter != this->request_values.end()) 
             && ( i < requestECSeq->length());
             ++eclistiter, ++i)
           {
              this->Info = *eclistiter;
              (*requestECSeq)[i].EventChannelName = 
              CORBA::string_dup((this->Info.getName()).c_str());
              (*requestECSeq)[i].EventId = this->Info.getId();
           }

           // clear the contents of the ECList.
           this->request_values.clear();
       }
      else
      {

        requestECSeq->length(1);
        (*requestECSeq)[0].EventChannelName = CORBA::string_dup 
                                                   (DEFAULT_REQUEST_CHANNEL);
        (*requestECSeq)[0].EventId = (this->eventid_num);

        this->eprops.length(4);
        CosTrading::OfferId_var offer_id;
        CORBA::Object_ptr offer_obj = this->_this(ACE_TRY_ENV);
        CosTrading::Register_ptr reg = this->register_.in();
        ACE_TRY_CHECK;

        this->eprops[0].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
        this->eprops[0].value <<= (this->index.c_str());

        this->eprops[1].name = CORBA::string_dup("EC_NAME");
        this->eprops[1].value <<= DEFAULT_REQUEST_CHANNEL;

        this->eprops[2].name = CORBA::string_dup("EC_ID");
        this->eprops[2].value <<= (this->eventid_num);

        this->eprops[3].name = CORBA::string_dup("EC_TYPE");
        this->eprops[3].value <<= ectype.c_str();

        offer_id = reg->_cxx_export(offer_obj, this->r_service_type, this->eprops,
                                            ACE_TRY_ENV);
        ACE_TRY_CHECK;
        this->offerid_list.push_back(offer_id);
	ACE_DEBUG ((LM_DEBUG, \
		    "New QMSUniqueName: \"%s\". Assigned [%s,%d,%s]\n", \
		    this->index.c_str(), DEFAULT_REQUEST_CHANNEL, \
		    eventid_num, ectype.c_str() ));

        ACE_Read_Guard<ACE_Thread_Mutex>  guard(this->asset_guard);
        {
          this->eventid_num++;
        }

      } // end of else. Add the default request  channel for the existing 
        // QMSUniqueName category, since it is not there in the file.

  }

  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception :");
      ACE_RE_THROW;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception :");
      ACE_RE_THROW;
    }

  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return requestECSeq;

}


/**
 * @brief The function that retuns the supplier id to a QMS citizen
 * @param description description of the supplier
 * @param ACE_TRY_ENV Reference to CORBA::Environment variable.
 */
CORBA::ULong
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::getSupplierID (const char * description)

ACE_THROW_SPEC ((CORBA::SystemException))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::getSupplierID ", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::getSupplierID \n");
  CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ();

  ACE_TRY
  {
      this->desc.assign(description);
      this->supplier_exporter(this->desc, ACE_TRY_ENV);
  }

  ACE_CATCHANY
  {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                          "STDC::QMS::Citizen::QMS_Trader_ECInfo::getSupplierID");
      ACE_RE_THROW;
  }

  ACE_ENDTRY;
  ACE_CHECK;

  return this->supplierid_num++;

}


/**
 * @brief Adds the Yellow Pages service type
 * @param ACE_TRY_ENV Reference to CORBA::Environment variable.
 * @return None.
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::add_yp_serviceType(CORBA::Environment &ACE_TRY_ENV)

   ACE_THROW_SPEC ((CORBA::SystemException,
                    CosTrading::IllegalServiceType,
                    CosTradingRepos::ServiceTypeRepository::ServiceTypeExists,
                    CosTradingRepos::ServiceTypeRepository::InterfaceTypeMismatch,
                    CosTrading::IllegalPropertyName,
                    CosTrading::DuplicatePropertyName,
                    CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
                    CosTrading::UnknownServiceType,
                    CosTradingRepos::ServiceTypeRepository::DuplicateServiceTypeName))
{
    QMS_Trace("QMS_Trader_ECInfo_Impl::add_yp_serviceType", __LINE__, __FILE__);
    DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::add_yp_serviceType\n");
 
    bool retry = true;
    bool no_yp_service = false;

    ACE_TRY
    {
       this->make_offer(ACE_TRY_ENV);
       ACE_TRY_CHECK;
  
       retry = false ;
    }
    ACE_CATCH (CosTrading::UnknownServiceType, excp)
     {
       cerr << "DEBUG: No service type (ignored -- need to add service type)"
            << endl;
       no_yp_service = true;
       ACE_TRY_ENV.clear ();
     }
    ACE_CATCH (CosTrading::PropertyTypeMismatch, excp)
     {
        cerr << "DEBUG: Property type mismatch\n";
         if (excp.type.in () != 0)
          cerr << "Invalid type: " << excp.type.in () << endl;
        if(excp.prop.name.in())
         {
           cerr << "Invalid property name : " << excp.prop.name.in () << endl;
         } /* end of if(excp.something.name.in()) */
         ACE_RE_THROW;
     }
    ACE_CATCH (CosTrading::IllegalPropertyName, excp)
     {
        cerr << "DEBUG: IllegalPropertyName\n";
        ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType-IllegalPropertyName");

        if (excp.name.in () != 0)
           cerr << "Illegal Property  name: " << excp.name.in () << endl;
        ACE_RE_THROW;
     }
    ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition, vtr)
     {
        cerr << "DEBUG: ValueTypeRedefinition\n";
        ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType -ValueTypeRedefinition");

        if (vtr.type_1.in () != 0)
          cerr << "Type One: " << vtr.type_2.in () << endl;
        if (vtr.type_2.in () != 0)
          cerr << "Type Two: " << vtr.type_2.in () << endl;
        ACE_RE_THROW;
     }
    ACE_CATCHANY
     {
        cerr << "DEBUG: Yikes. Another unexpected exception\n";
        ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
        ACE_RE_THROW;
     }
    ACE_ENDTRY;
     
    if(no_yp_service)
   {
     ACE_TRY
       {
         // Adding the YP SERVICE TYPE using STDC::QMS::Add_YP_ServiceType method.
         STDC::QMS::Add_YP_ServiceType(this->handles_p, ACE_TRY_ENV);
         ACE_TRY_CHECK;
         cerr << "YP Service Type created -> " << YP_SERVICE_TYPE << endl;
       }
     ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ServiceTypeExists, ste)
       {
         ACE_PRINT_EXCEPTION (ste, "Adding YP_ServiceType");

         if (ste.name.in () != 0)
           cerr << "Service Type Exists: (ignored)" << ste.name.in () << endl;
         ACE_TRY_ENV.clear ();
       }
     ACE_CATCH (CosTrading::IllegalPropertyName, excp)
       {
         ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType");

         if (excp.name.in () != 0)
           cerr << "IllegalPropertyName,: " << excp.name.in () << endl;
         ACE_RE_THROW;
       }
     ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
                vtr)
       {
         ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType");

         if (vtr.type_1.in () != 0)
           cerr << "Type One: " << vtr.type_2.in () << endl;
         if (vtr.type_2.in () != 0)
           cerr << "Type Two: " << vtr.type_2.in () << endl;
         ACE_RE_THROW;
       }
     ACE_CATCHANY
       {
         ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
         ACE_RE_THROW;
       }
     ACE_ENDTRY;

     ACE_TRY
       {
         //Adding the YP_SubType using STDC::QMS::Add_YP_SubType method.
         STDC::QMS::Add_YP_SubType(this->handles_p,
                                   QT_SERVICE_TYPE,
                                   this->_interface_repository_id(),
                                   ACE_TRY_ENV);
         ACE_TRY_CHECK;
         cerr << "QMS Trader Service subtype added -> " << QT_SERVICE_TYPE << endl;
       }
     ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ServiceTypeExists, ste)
       {
         ACE_PRINT_EXCEPTION (ste, "Adding QMS_Trader_ECInfo ServiceType");

         if (ste.name.in () != 0)
           cerr << "ServiceTypeExists: " << ste.name.in () << endl;
         ACE_RE_THROW;
       }
     ACE_CATCH (CosTrading::IllegalPropertyName, excp)
       {
         ACE_PRINT_EXCEPTION (excp, "Adding QMS_Trader_ECInfo ServiceType");

         if (excp.name.in () != 0)
           cerr << "Illegal Property name: " << excp.name.in () << endl;
         ACE_RE_THROW;
       }
     ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
                vtr)
       {
         ACE_PRINT_EXCEPTION (vtr, "Adding QMS_Trader_ECInfo ServiceType");

         if (vtr.type_1.in () != 0)
           cerr << "Type One: " << vtr.type_2.in () << endl;
         if (vtr.type_2.in () != 0)
           cerr << "Type Two: " << vtr.type_2.in () << endl;
         ACE_RE_THROW;
       }
     ACE_CATCHANY
       {
         ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
         ACE_RE_THROW;
       }
     ACE_ENDTRY;

    } /* end of if(no_yp_service) */

 
    ACE_TRY
    {
      if(retry)
       {
         this->make_offer(ACE_TRY_ENV);
         ACE_TRY_CHECK;
       } /* end of if(retry) */
    }
   ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
      ACE_RE_THROW;
    }
   ACE_ENDTRY;

}




/**
 * @brief The function that exports the config file information to trader.
 * @param ACE_TRY_ENV Reference to CORBA::Environment variable.
 * @return None.
 * 
 */
void 
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::offer_exporter (CORBA::Environment &ACE_TRY_ENV)

           ACE_THROW_SPEC ((CORBA::SystemException,
                            CosTrading::Register::InvalidObjectRef,
                            CosTrading::IllegalServiceType,
                            CosTrading::UnknownServiceType,
                            CosTrading::Register::InterfaceTypeMismatch,
                            CosTrading::IllegalPropertyName,
                            CosTrading::PropertyTypeMismatch,
                            CosTrading::ReadonlyDynamicProperty,
                            CosTrading::MissingMandatoryProperty,
                            CosTrading::DuplicatePropertyName))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::offer_exporter", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::offer_exporter\n");

  ACE_TRY
  {
      string qms_name, ecname, ectype;
      long eventid;

      this->eprops.length(4);
      CosTrading::OfferId_var offer_id;
      CORBA::Object_ptr offer_obj = this->_this(ACE_TRY_ENV);
      CosTrading::Register_ptr reg = this->register_.in(); 
      ACE_TRY_CHECK;

      ifstream inClientFile( this->config_file, ios::in );
      while ( inClientFile >> qms_name >> ecname >> eventid >> ectype )
      {
            this->eprops[0].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
            this->eprops[0].value <<= qms_name.c_str();

            this->eprops[1].name = CORBA::string_dup("EC_NAME");
            this->eprops[1].value <<= ecname.c_str();

            this->eprops[2].name = CORBA::string_dup("EC_ID");
            this->eprops[2].value <<= (CORBA::ULong)(eventid);

            this->eprops[3].name = CORBA::string_dup("EC_TYPE");
            this->eprops[3].value <<= ectype.c_str();

            offer_id = reg->_cxx_export(offer_obj, this->r_service_type, this->eprops,
                                            ACE_TRY_ENV);
            ACE_TRY_CHECK;
            this->offerid_list.push_back(offer_id);
            ACE_DEBUG ((LM_DEBUG, "Registered offer id is: %s.\n", offer_id.in ()));

      }
  
  }

  ACE_CATCH (CosTrading::UnknownServiceType, excp)    
  {
    this->type_struct_.props.length(4);
    // for QMS_UNIQ_NAME_CATEGORY
    this->type_struct_.props[0].name = CORBA::string_dup ("QMS_UNIQ_NAME_CATEGORY");
    this->type_struct_.props[0].value_type = 
                              CORBA::TypeCode::_duplicate(CORBA::_tc_string);
    this->type_struct_.props[0].mode = 
              CosTradingRepos::ServiceTypeRepository::PROP_MANDATORY_READONLY;
    // Event Channel Name
    this->type_struct_.props[1].name = CORBA::string_dup ("EC_NAME");
    this->type_struct_.props[1].value_type = 
                             CORBA::TypeCode::_duplicate(CORBA::_tc_string);
    this->type_struct_.props[1].mode = 
            CosTradingRepos::ServiceTypeRepository::PROP_MANDATORY_READONLY;
    // Event Id
    this->type_struct_.props[2].name = CORBA::string_dup ("EC_ID");
    this->type_struct_.props[2].value_type = 
                            CORBA::TypeCode::_duplicate(CORBA::_tc_ulong);
    this->type_struct_.props[2].mode = 
             CosTradingRepos::ServiceTypeRepository::PROP_MANDATORY_READONLY;
    // Event Channel Type
    this->type_struct_.props[3].name = CORBA::string_dup ("EC_TYPE");
    this->type_struct_.props[3].value_type = 
                             CORBA::TypeCode::_duplicate(CORBA::_tc_string);
    this->type_struct_.props[3].mode = 
             CosTradingRepos::ServiceTypeRepository::PROP_MANDATORY_READONLY;
    // Repository id of the servant.
    this->type_struct_.if_name = this->_interface_repository_id ();

    // Create register Service Type
    this->repos_->add_type (this->r_service_type,
                  this->type_struct_.if_name,
                  this->type_struct_.props,
                  this->type_struct_.super_types,
                  ACE_TRY_ENV);
    ACE_CHECK;
    ACE_DEBUG ((LM_DEBUG, "Adding the ECInfo Service Type -> %s\n",
                                             r_service_type ));

    string qms_name, ecname, ectype;
    long eventid;

    this->eprops.length(4);
    CosTrading::OfferId_var offer_id;
    CORBA::Object_ptr offer_obj = this->_this(ACE_TRY_ENV);
    CosTrading::Register_ptr reg = this->register_.in(); 
    ACE_CHECK;

    ifstream inClientFile( this->config_file, ios::in );
    while ( inClientFile >> qms_name >> ecname >> eventid >> ectype )
    {
        this->eprops[0].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
        this->eprops[0].value <<= qms_name.c_str();

        this->eprops[1].name = CORBA::string_dup("EC_NAME");
        this->eprops[1].value <<= ecname.c_str();

        this->eprops[2].name = CORBA::string_dup("EC_ID");
        this->eprops[2].value <<= (CORBA::ULong)(eventid);

        this->eprops[3].name = CORBA::string_dup("EC_TYPE");
        this->eprops[3].value <<= ectype.c_str();

        offer_id = reg->_cxx_export(offer_obj,
                         this->r_service_type,
         this->eprops,
         ACE_TRY_ENV);
        ACE_CHECK;
        this->offerid_list.push_back(offer_id);
        ACE_DEBUG ((LM_DEBUG, "Loading configuration file: %s\t%s\t%d\t%s.\n", \
		    qms_name.c_str(), ecname.c_str(), \
		    eventid,ectype.c_str() ));
    }

  }

  ACE_CATCHANY
  {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                          "QMS_Trader_ECInfo_Impl::offer_exporter ");
      ACE_RE_THROW;
  }

  ACE_ENDTRY;
  ACE_CHECK;

}


/**
 * @brief This function returns information pertaining to a QMSUniqueName category.
 * @param ACE_TRY_ENV Reference to CORBA::Environment variable.
 * @return None.
 * 
 */
void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::offer_importer (string& QUN, string& ectype, 
 list< ECInfo >& offer_values, CORBA::Environment& ACE_TRY_ENV)

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
                             CosTrading::DuplicatePolicyName))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::offer_importer", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::offer_importer\n");

  ACE_TRY
  {

    // Now doing an import operation
    PolicySeq policies; //empty sequence
    Lookup::SpecifiedProps desired_props;
    desired_props._d(Lookup::all);
    //PolicyNameSeq_var policies_applied; // out param
  
    CosTrading::OfferSeq *offer_seq_ptr = 0;
    CosTrading::OfferIterator_ptr offer_iterator_ptr = 0;
    CosTrading::PolicyNameSeq *limits_applied_ptr = 0;

    CosTrading::OfferSeq_out offer_seq_out (offer_seq_ptr);
    CosTrading::OfferIterator_out offer_iterator_out (offer_iterator_ptr);
    CosTrading::PolicyNameSeq_out limits_applied_out (limits_applied_ptr);
    //OfferIterator_var iterator;     // out param

    string query ("QMS_UNIQ_NAME_CATEGORY");
    query += " == \'";
    query.append(QUN);
    query += "\' and EC_TYPE == \'";
    query.append(ectype);
    query += "\'";

    //cout << query.c_str() << endl;

    // Make sure that all the parameters are proper. 
    // specify the struct that says the required properties. min EC_ID
    this->lookup_p->query(this->r_service_type, query.c_str(), "", policies,
                  desired_props, 0, offer_seq_out, offer_iterator_out, 
                  limits_applied_out, ACE_TRY_ENV);
  ACE_TRY_CHECK;

  CosTrading::OfferIterator_ptr offer_iterator = offer_iterator_ptr;


  if (!CORBA::is_nil(offer_iterator)) 
  {
        DEBUG0(DEBUG_L_ENTER, "DEBUG: offer_iterator is not null\n");
        CORBA::Boolean more = 0;

      do 
      {
          DEBUG0(DEBUG_L_ENTER, "DEBUG: Inside the do while loop\n");
          CosTrading::OfferSeq *iter_offers_ptr;
          CosTrading::OfferSeq_out iter_offers_out (iter_offers_ptr);

          more = offer_iterator->next_n(1, iter_offers_out,ACE_TRY_ENV);
          ACE_TRY_CHECK;

          CosTrading::OfferSeq_var iter_offers (iter_offers_ptr);
          CORBA::Any* value = 0;
          DEBUG1(DEBUG_L_ENTER, "DEBUG: iter_offers->length()->%d\n",
                                   iter_offers->length());


          for (CORBA::ULong i = 0; i < iter_offers->length(); i++)
          {
              DEBUG0(DEBUG_L_ENTER, "DEBUG: Inside the for loop\n");
              //this->eprops = iter_offers[i].properties;
              //TAO_Property_Evaluator prop_eval (this->eprops);
              TAO_Property_Evaluator prop_eval (iter_offers[i].properties);
              //for (int length = this->eprops.length(), k=0; k < length ; k++)
              for (int length = (iter_offers[i].properties).length(), k=0; k < length ; k++)
              {
                  //if ( ACE_OS::strcmp ("QMS_UNIQ_NAME_CATEGORY", (this->eprops[k].name.in())) == 0 || ACE_OS::strcmp("EC_TYPE", (this->eprops[k].name.in())) == 0 )
                  if ( ACE_OS::strcmp ("QMS_UNIQ_NAME_CATEGORY", (iter_offers[i].properties[k].name.in())) == 0 || ACE_OS::strcmp("EC_TYPE", (iter_offers[i].properties[k].name.in())) == 0 )
                  {
                     DEBUG0(DEBUG_L_ENTER, "DEBUG: Got a QMS_UNIQ_NAME_CATEGORY or EC_TYPE \n");
                     continue;
                  }
                  value = prop_eval.property_value(k, ACE_TRY_ENV);
                  ACE_TRY_CHECK;
                  //cout << this->eprops[k].name.in() << endl;
                  //DEBUG1(DEBUG_L_ENTER, "DEBUG: %s\n", this->eprops[k].name.in());
                  DEBUG1(DEBUG_L_ENTER, "DEBUG: %s\n", iter_offers[i].properties[k].name.in());
                  CORBA::ULong       long_val;
                  const char *    string_val;
                  if ((*value) >>= long_val)
                  {
                      DEBUG1(DEBUG_L_ENTER, "DEBUG: offer_importer->%d\n", long_val);
                      this->Info.setId(long_val);
                  }
                  else if ((*value) >>= string_val)
                  {
                       DEBUG1(DEBUG_L_ENTER, "DEBUG: offer_importer->%s\n", string_val);
                        this->Info.setName(string_val);
                  }
             } // end of second for 

              DEBUG0(DEBUG_L_ENTER, "DEBUG: Pushing the values into offer_values \n");
              offer_values.push_front(this->Info);

         } // end of first for 

     } while (more);

    DEBUG0(DEBUG_L_ENTER, "DEBUG: Destroying the iterator\n");
    offer_iterator->destroy();
    ACE_TRY_CHECK;

  } // end of if 

}

  ACE_CATCHANY
  {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                      "QMS_Trader_ECInfo_Impl::offer_importer ");
      ACE_RE_THROW;
  }

  ACE_ENDTRY;
  ACE_CHECK;

}


/**
 * @brief method for getting the highest supplier id from trader. 
 * @param ACE_TRY_ENV Reference to CORBA::Environment variable.
 * @return None.
 */
void 
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::supplier_importer (CORBA::Environment &ACE_TRY_ENV) 

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
                       CosTrading::DuplicatePolicyName))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::supplier_importer", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::supplier_importer\n");

  ACE_TRY
  {
    PolicySeq policies; //empty sequence
    Lookup::SpecifiedProps desired_props;
        desired_props._d(Lookup::all);

    CosTrading::OfferSeq *offer_seq_ptr = 0;
    CosTrading::OfferIterator_ptr offer_iterator_ptr = 0;
    CosTrading::PolicyNameSeq *limits_applied_ptr = 0;

    CosTrading::OfferSeq_out offer_seq_out (offer_seq_ptr);
    CosTrading::OfferIterator_out offer_iterator_out (offer_iterator_ptr);
    CosTrading::PolicyNameSeq_out limits_applied_out (limits_applied_ptr);

    // Make sure that all the parameters are proper. 
    // specify the struct that says the required properties. max Supplier_Id
    this->lookup_p->query(this->supplier_service_type, "", "max Supplier_Id", policies,
                  desired_props, 1, offer_seq_out, offer_iterator_out, 
                                     limits_applied_out, ACE_TRY_ENV);
    ACE_TRY_CHECK;

    // looks like var variables take care of destruction.
    //CosTrading::OfferSeq_var offer_seq (offer_seq_ptr);
    CosTrading::OfferIterator_var offer_iterator (offer_iterator_ptr);
    CosTrading::PolicyNameSeq_var limits_applied (limits_applied_ptr);

    //Look like CosTrading::OfferSeq_var can't be defined before this
    CosTrading::OfferSeq& offer_seq = *offer_seq_ptr;
    //CosTrading::OfferIterator_ptr offer_iterator = offer_iterator_ptr;

    if (offer_seq.length() != 0 )
    {
        //this->eprops = offer_seq[0].properties;
        DEBUG0(DEBUG_L_ENTER, "DEBUG: Got the Property seq\n");
        //TAO_Property_Evaluator prop_eval (this->eprops);
        TAO_Property_Evaluator prop_eval (offer_seq[0].properties);
        CORBA::Any* value = 0;

        //DEBUG1(DEBUG_L_ENTER, "DEBUG: %s\n", this->eprops[0].name.in());
        DEBUG1(DEBUG_L_ENTER, "DEBUG: %s\n", (offer_seq[0].properties[0].name.in()));
        value = prop_eval.property_value(0, ACE_TRY_ENV);
        ACE_TRY_CHECK;

        if ((*value) >>= this->supplierid_num)
        {
          DEBUG1(DEBUG_L_ENTER, 
          "DEBUG: The supplierid_num value form Trader->%d\n",
          this->supplierid_num);
        }
        else
        {
            DEBUG0(DEBUG_L_ENTER, "*****SHOULDNOT BE HERE************\n");                                       
        }
    }
    else
    {
        this->supplierid_num = (CORBA::ULong) 20000;
        ACE_DEBUG ((LM_DEBUG, "Set supplierid_num value->%d\n", this->supplierid_num));
        DEBUG1(DEBUG_L_ENTER, "DEBUG: Set supplierid_num value->%d\n",
        this->supplierid_num);
    }


    // Clean up the iterator.
    if (!CORBA::is_nil(offer_iterator))
    {
        offer_iterator->destroy();
        ACE_TRY_CHECK;
    }

  }

  ACE_CATCH (CosTrading::UnknownServiceType, excp)    
  {
      this->type_struct_.props.length(2);
      // for the supplier id
      this->type_struct_.props[0].name = CORBA::string_dup ("Supplier_Id");
      this->type_struct_.props[0].value_type = 
                             CORBA::TypeCode::_duplicate(CORBA::_tc_ulong);
      this->type_struct_.props[0].mode = 
            CosTradingRepos::ServiceTypeRepository::PROP_MANDATORY_READONLY;
      // for supplier name
      this->type_struct_.props[1].name = CORBA::string_dup ("Supplier_Name");
      this->type_struct_.props[1].value_type = 
                             CORBA::TypeCode::_duplicate(CORBA::_tc_string);
      this->type_struct_.props[1].mode = 
              CosTradingRepos::ServiceTypeRepository::PROP_MANDATORY_READONLY;
      this->type_struct_.if_name = this->_interface_repository_id ();

      // Create Service Type
      this->repos_->add_type (this->supplier_service_type, this->type_struct_.if_name,
               this->type_struct_.props, this->type_struct_.super_types, ACE_TRY_ENV);
      ACE_CHECK;
      ACE_DEBUG ((LM_ERROR, "Adding the SupplierID Service Type -> %s\n",
                               supplier_service_type ));
  }

  ACE_CATCHANY
  {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                      "QMS_Trader_ECInfo_Impl::supplier_importer ");
      ACE_RE_THROW;
  }

  ACE_ENDTRY;
  ACE_CHECK;

}

/**
 * @brief method that exports the new supplied id information to trader.
 * @param ACE_TRY_ENV Reference to CORBA::Environment variable.
 * @return None.
 */
void 
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::supplier_exporter (string &supplier_name,
                               CORBA::Environment &ACE_TRY_ENV) 
         ACE_THROW_SPEC ((CORBA::SystemException,
                CosTrading::Register::InvalidObjectRef,
                CosTrading::IllegalServiceType,
                CosTrading::UnknownServiceType,
                CosTrading::Register::InterfaceTypeMismatch,
                CosTrading::IllegalPropertyName,
                CosTrading::PropertyTypeMismatch,
                CosTrading::ReadonlyDynamicProperty,
                CosTrading::MissingMandatoryProperty,
                CosTrading::DuplicatePropertyName))
{
  QMS_Trace("QMS_Trader_ECInfo_Impl::supplier_exporter", __LINE__, __FILE__);
  DEBUG0(DEBUG_L_ENTER, "DEBUG: QMS_Trader_ECInfo_Impl::supplier_exporter\n");

  ACE_TRY
  {
      this->eprops.length(2);
      CosTrading::OfferId_var offer_id;
      CORBA::Object_ptr offer_obj = this->_this(ACE_TRY_ENV);
      CosTrading::Register_ptr reg = this->register_.in(); 
      ACE_TRY_CHECK;

      this->eprops[0].name = CORBA::string_dup("Supplier_Id");
      this->eprops[0].value <<= (CORBA::ULong) this->supplierid_num;

      this->eprops[1].name = CORBA::string_dup("Supplier_Name");
      this->eprops[1].value <<= supplier_name.c_str();

       offer_id = reg->_cxx_export(offer_obj, this->supplier_service_type, \
				   this->eprops, ACE_TRY_ENV);
      ACE_TRY_CHECK;
      this->offerid_list.push_back(offer_id);
      ACE_DEBUG ((LM_DEBUG, "Assigned new SupplierID\t\"%s\" : %d\n", \
		  supplier_name.c_str(), this->supplierid_num));

  }

  ACE_CATCHANY
  {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                        "QMS_Trader_ECInfo_Impl::supplier_exporter ");
      ACE_RE_THROW;
  }

  ACE_ENDTRY;
  ACE_CHECK;

}



void
STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl::make_offer(CORBA::Environment &ACE_TRY_ENV)
{

   ACE_TRY
   {
      char hostname[MAXNAMELEN], hostip[MAXNAMELEN],pid[MAXNAMELEN];
      in_addr address;

      ACE_OS::hostname( hostname, MAXNAMELEN );
      struct hostent *hostinfo = ACE_OS::gethostbyname (hostname);
      address.s_addr = (ACE_reinterpret_cast (in_addr * , 
                                    hostinfo->h_addr_list[0])->s_addr);

      ACE_OS::strcpy(hostip, inet_ntoa(address));
      
      this->eprops.length(5);
      CosTrading::OfferId_var offer_id;
      CORBA::Object_ptr offer_obj = this->_this(ACE_TRY_ENV);
      CosTrading::Register_ptr reg = this->register_.in();
      ACE_TRY_CHECK;

      // Exporting the offer for my sub type.

      this->eprops[0].name = CORBA::string_dup("QMS_UNIQ_NAME_CATEGORY");
      this->eprops[0].value <<= CORBA::string_dup(QMS_UNIQUE_CATEGORY_NAME);

      this->eprops[1].name = CORBA::string_dup("QMS_UNIQ_NAME_HOST_NAME");
      this->eprops[1].value <<= CORBA::string_dup(hostip);

      sprintf(pid,"%d",ACE_OS::getpid ());
      this->eprops[2].name = CORBA::string_dup("QMS_UNIQ_NAME_UUID");
      this->eprops[2].value <<= CORBA::string_dup(pid);

      this->eprops[3].name = CORBA::string_dup("VERSION");
      this->eprops[3].value <<= "1.0";

      this->eprops[4].name = CORBA::string_dup("DESCRIPTION");
      this->eprops[4].value <<= "QMS_Trader_ECInfo";


      offer_id = reg->_cxx_export(offer_obj,
                 QT_SERVICE_TYPE, this->eprops, ACE_TRY_ENV);
      ACE_TRY_CHECK;
      //this->offerid_list.push_front(offer_id);
      this->offerid_list.push_back(offer_id);
      ACE_DEBUG ((LM_DEBUG, "QMS Trader YP Offer Registered.\n"));

   }
   ACE_CATCH (CosTrading::UnknownServiceType, excp)
    {
      cerr <<  "DEBUG: No service type While trying to make an offer for "
           <<  "QMS_Trader_ECInfo" <<endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTrading::IllegalPropertyName, excp)
    {
      cerr << "DEBUG: IllegalPropertyName" <<endl;
      ACE_PRINT_EXCEPTION (excp, "Add_YP_ServiceType-IllegalPropertyName");

      if (excp.name.in () != 0)
        cerr << "IllegalPropertyName : " << excp.name.in () <<endl;
      ACE_RE_THROW;
    }
  ACE_CATCH (CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition, vtr)
    {
      cerr <<  "DEBUG: ValueTypeRedefinition\n" << endl;
      ACE_PRINT_EXCEPTION (vtr, "Add_YP_ServiceType -ValueTypeRedefinition");

      if (vtr.type_1.in () != 0)
        cerr << "Type One: " << vtr.type_2.in () << endl;
      if (vtr.type_2.in () != 0)
        cerr << "Type Two: " << vtr.type_2.in () << endl;
      ACE_RE_THROW;
    }
  ACE_CATCHANY
  {
    cerr <<  "DEBUG: Error making yp offer\n";
    ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Error making yp offer");
    ACE_RE_THROW;
  }
  ACE_ENDTRY;

}



#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class  list<string>;
template class list<ECInfo>;
template class vector<CosTrading::OfferId_var>;
template class vector<CORBA_String_var, __default_alloc_template<true, 0> >;

template CORBA_String_var * __uninitialized_copy_aux<CORBA_String_var *, CORBA_String_var *>(CORBA_String_var *, CORBA_String_var *, CORBA_String_var *, __false_type);
template CORBA_String_var * __uninitialized_copy_aux<CORBA_String_var const *, CORBA_String_var *>(CORBA_String_var const *, CORBA_String_var const *, CORBA_String_var *, __false_type);

template CORBA_String_var * __uninitialized_fill_n_aux<CORBA_String_var *, unsigned int, CORBA_String_var>(CORBA_String_var *, unsigned int, CORBA_String_var const &, __false_type);

template CORBA_String_var * fill_n<CORBA_String_var *, unsigned int, CORBA_String_var>(CORBA_String_var *, unsigned int, CORBA_String_var const &);
template void fill<CORBA_String_var *, CORBA_String_var>(CORBA_String_var *, CORBA_String_var *, CORBA_String_var const &);

#if defined(__GNUC_MINOR__) && __GNUC_MINOR__ > 92
template class _List_base<ECInfo, allocator<ECInfo> >;
template class _List_base<string, allocator<string > >;

template void list<string>::_M_insert_dispatch<_List_iterator<string, string const &, string const *> >(_List_iterator<string, string &, string *>, _List_iterator<string, string const &, string const *>, _List_iterator<string, string const &, string const *>, __false_type);
template void list<ECInfo >::_M_insert_dispatch<_List_iterator<ECInfo, ECInfo const &, ECInfo const *> >(_List_iterator<ECInfo, ECInfo &, ECInfo *>, _List_iterator<ECInfo, ECInfo const &, ECInfo const *>, _List_iterator<ECInfo, ECInfo const &, ECInfo const *>, __false_type);

#else

template void list<ECInfo, __default_alloc_template<true, 0> >::insert<__list_iterator<ECInfo, ECInfo const &, ECInfo const *> >(__list_iterator<ECInfo, ECInfo &, ECInfo *>, __list_iterator<ECInfo, ECInfo const &, ECInfo const *>, __list_iterator<ECInfo, ECInfo const &, ECInfo const *>);
template void list<string, __default_alloc_template<true, 0> >::insert<__list_iterator<string, string const &, string const *> >(__list_iterator<string, string &, string *>, __list_iterator<string, string const &, string const *>, __list_iterator<string, string const &, string const *>);

#endif

#endif // ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION
