// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

#ifndef _TAO_IDL_GENERIC_SENSORS_CPP_
#define _TAO_IDL_GENERIC_SENSORS_CPP_

#include "Generic_SensorS.h"

#include "tao/PortableServer/Object_Adapter.h"
#include "tao/PortableServer/Operation_Table.h"
#include "tao/TAO_Server_Request.h"
#include "tao/ORB_Core.h"
#include "tao/Stub.h"
#include "tao/IFR_Client_Adapter.h"
#include "tao/PortableInterceptor.h"

#if TAO_HAS_INTERCEPTORS == 1
#include "tao/RequestInfo_Util.h"
#include "tao/PICurrent.h"
#include "tao/PortableServer/ServerRequestInfo.h"
#include "tao/PortableServer/ServerInterceptorAdapter.h"
#endif  /* TAO_HAS_INTERCEPTORS == 1 */

#include "ace/Dynamic_Service.h"
#if defined (__BORLANDC__)
#pragma option -w-rvl -w-rch -w-ccc -w-aus
#endif /* __BORLANDC__ */

#if !defined (__ACE_INLINE__)
#include "Generic_SensorS.i"
#endif /* !defined INLINE */

class TAO_STDC_QMS_Citizen_Generic_Sensor_Perfect_Hash_OpTable : public TAO_Perfect_Hash_OpTable
{
private:
  unsigned int hash (const char *str, unsigned int len);
public:
 const TAO_operation_db_entry * lookup (const char *str, unsigned int len);
};
/* starting time is 15:08:26 */
/* C++ code produced by gperf version 2.8 (ACE version) */
/* Command-line: /opt/ACE_wrappers/bin/gperf -m -M -J -c -C -D -E -T -f 0 -F 0 -a -o -t -p -K opname_ -L C++ -Z TAO_STDC_QMS_Citizen_Generic_Sensor_Perfect_Hash_OpTable -N lookup  */
unsigned int
TAO_STDC_QMS_Citizen_Generic_Sensor_Perfect_Hash_OpTable::hash (const char *str, unsigned int len)
{
  static const unsigned char asso_values[] =
    {
#if defined (ACE_MVS)
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21,  0,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21,  4,
     21, 21,  5,  5, 21, 10, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21,  0, 21, 21,
     21,  0, 21,  0, 21, 21, 21, 21, 21, 21,
     21, 21,  0,  0, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21,  0, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21,
#else
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21,  0, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 21, 21,  0, 21,  4, 21, 21,
      5,  5, 21, 10, 21, 21, 21, 21,  0, 21,
     21, 21,  0, 21,  0,  0,  0, 21, 21, 21,
     21, 21, 21, 21, 21, 21, 21, 21,
#endif /* ACE_MVS */
    };
  return len + asso_values[str[len - 1]] + asso_values[str[0]];
}

const class TAO_operation_db_entry *
TAO_STDC_QMS_Citizen_Generic_Sensor_Perfect_Hash_OpTable::lookup (const char *str, unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 12,
      MIN_WORD_LENGTH = 4,
      MAX_WORD_LENGTH = 20,
      MIN_HASH_VALUE = 4,
      MAX_HASH_VALUE = 20,
      HASH_VALUE_RANGE = 17,
      DUPLICATES = 0,
      WORDLIST_SIZE = 16
    };

  static const class TAO_operation_db_entry  wordlist[] =
    {
      {"",0},{"",0},{"",0},{"",0},
      {"stop", 	&POA_STDC::QMS::Citizen::Generic_Sensor::stop_skel},
      {"stats", 	&POA_STDC::QMS::Citizen::Generic_Sensor::stats_skel},
      {"",0},{"",0},{"",0},
      {"_is_a",  &POA_STDC::QMS::Citizen::Generic_Sensor::_is_a_skel},
      {"pause", 	&POA_STDC::QMS::Citizen::Generic_Sensor::pause_skel},
      {"resume", 	&POA_STDC::QMS::Citizen::Generic_Sensor::resume_skel},
      {"reconnect_EC", 	&POA_STDC::QMS::Citizen::Generic_Sensor::reconnect_EC_skel},
      {"_non_existent",  &POA_STDC::QMS::Citizen::Generic_Sensor::_non_existent_skel},
      {"ping", 	&POA_STDC::QMS::Citizen::Generic_Sensor::ping_skel},
      {"_interface",  &POA_STDC::QMS::Citizen::Generic_Sensor::_interface_skel},
      {"",0},{"",0},
      {"disconnect_EC", 	&POA_STDC::QMS::Citizen::Generic_Sensor::disconnect_EC_skel},
      {"set_operating_level", 	&POA_STDC::QMS::Citizen::Generic_Sensor::set_operating_level_skel},
      {"show_operating_level", 	&POA_STDC::QMS::Citizen::Generic_Sensor::show_operating_level_skel},
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          const char *s = wordlist[key].opname_;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1))
            return &wordlist[key];
        }
    }
  return 0;
}
/* ending time is 15:08:26 */
static TAO_STDC_QMS_Citizen_Generic_Sensor_Perfect_Hash_OpTable tao_STDC_QMS_Citizen_Generic_Sensor_optable;

#if (TAO_HAS_INTERCEPTORS == 1)
#endif /* TAO_HAS_INTERCEPTORS */

///////////////////////////////////////////////////////////////////////
//            Strategized Proxy Broker Implementation
//

// Factory function Implementation.
POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_Strategized_Proxy_Broker *POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_Strategized_Proxy_Broker::the_TAO_Generic_Sensor_Strategized_Proxy_Broker (void)
{
  static POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_Strategized_Proxy_Broker strategized_proxy_broker;
  return &strategized_proxy_broker;
}

POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_Strategized_Proxy_Broker::_TAO_Generic_Sensor_Strategized_Proxy_Broker (void)
{
  for (int i = 0; i < TAO_Collocation_Strategies::CS_LAST; ++i)
    this->proxy_cache_[i] = 0;
  
}

POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_Strategized_Proxy_Broker::~_TAO_Generic_Sensor_Strategized_Proxy_Broker (void)
{
  for (int i = 0; i < TAO_Collocation_Strategies::CS_LAST; ++i)
    delete this->proxy_cache_[i];
  
}

STDC::QMS::Citizen::_TAO_Generic_Sensor_Proxy_Impl&
POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_Strategized_Proxy_Broker::select_proxy (
    ::STDC::QMS::Citizen::Generic_Sensor *object,
    CORBA::Environment &ACE_TRY_ENV
  )
{
  int strategy =
    TAO_ORB_Core::collocation_strategy (object, ACE_TRY_ENV);
    ACE_CHECK_RETURN (*this->proxy_cache_[strategy]);
  
  if (this->proxy_cache_[strategy] != 0)
    return *this->proxy_cache_[strategy];
  
  this->create_proxy (strategy, ACE_TRY_ENV);
  ACE_CHECK_RETURN (*this->proxy_cache_[strategy]);
  
  return *this->proxy_cache_[strategy];
  
}

void 
POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_Strategized_Proxy_Broker::create_proxy (
    int strategy,
    CORBA::Environment &ACE_TRY_ENV
  )
{
  ACE_GUARD (TAO_SYNCH_MUTEX, guard, this->mutex_);
  
  if (this->proxy_cache_[strategy] == 0)
    {
      switch (strategy)
        {
        case TAO_Collocation_Strategies::CS_THRU_POA_STRATEGY:
          ACE_NEW_THROW_EX (
              this->proxy_cache_[strategy],
              POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_ThruPOA_Proxy_Impl,
              CORBA::NO_MEMORY ()
          );
          ACE_CHECK;
          break;
          
        case TAO_Collocation_Strategies::CS_REMOTE_STRATEGY:
        default:
          ACE_NEW_THROW_EX (
              this->proxy_cache_[strategy],
              ::STDC::QMS::Citizen::_TAO_Generic_Sensor_Remote_Proxy_Impl,
              CORBA::NO_MEMORY ()
          );
          ACE_CHECK;
          break;
        
      }
    
  }
}


//
//        End Strategized Proxy Broker Implementation
///////////////////////////////////////////////////////////////////////


STDC::QMS::Citizen::_TAO_Generic_Sensor_Proxy_Broker *
STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Factory_function (CORBA::Object_ptr obj)
{
  ACE_UNUSED_ARG (obj);
  return ::POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_Strategized_Proxy_Broker::the_TAO_Generic_Sensor_Strategized_Proxy_Broker();
}

int
STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Factory_Initializer (long)
{
  STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Factory_function_pointer = 
    STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Factory_function;
  
  return 0;
}

static int STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Stub_Factory_Initializer_Scarecrow = 
  STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Factory_Initializer (ACE_reinterpret_cast (long, STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Factory_Initializer));


///////////////////////////////////////////////////////////////////////
//                 ThruPOA Proxy  Implementation
//

POA_STDC::QMS::Citizen::_TAO_Generic_Sensor_ThruPOA_Proxy_Impl::_TAO_Generic_Sensor_ThruPOA_Proxy_Impl (void)
{}

// ThruPOA Implementation of the IDL interface methods

//
//           End ThruPOA Proxy Implementation
///////////////////////////////////////////////////////////////////////

// skeleton constructor
POA_STDC::QMS::Citizen::Generic_Sensor::Generic_Sensor (void)
{
  this->optable_ = &tao_STDC_QMS_Citizen_Generic_Sensor_optable;
}

// copy ctor
POA_STDC::QMS::Citizen::Generic_Sensor::Generic_Sensor (const Generic_Sensor& rhs)
  :   ACE_NESTED_CLASS (POA_STDC::QMS::Citizen,Command) (rhs),
    ACE_NESTED_CLASS (POA_STDC::QMS::Citizen,Control) (rhs),
    TAO_ServantBase (rhs)
{}

// skeleton destructor
POA_STDC::QMS::Citizen::Generic_Sensor::~Generic_Sensor (void)
{
}

void POA_STDC::QMS::Citizen::Generic_Sensor::_is_a_skel (
    TAO_ServerRequest &_tao_server_request, 
    void * _tao_object_reference,
    void * /* Servant_Upcall */,
    CORBA::Environment &ACE_TRY_ENV
  )
{
  TAO_InputCDR &_tao_in = _tao_server_request.incoming ();
  POA_STDC::QMS::Citizen::Generic_Sensor *_tao_impl = (POA_STDC::QMS::Citizen::Generic_Sensor *) _tao_object_reference;
  CORBA::Boolean _tao_retval = 0;
  CORBA::String_var value;
  if (!(_tao_in >> value.out ()))
    ACE_THROW (CORBA::MARSHAL ());
  
  _tao_retval = _tao_impl->_is_a (value.in (), ACE_TRY_ENV);
  ACE_CHECK;
  
  _tao_server_request.init_reply ();
  TAO_OutputCDR &_tao_out = _tao_server_request.outgoing ();
  if (!(_tao_out << CORBA::Any::from_boolean (_tao_retval)))
    ACE_THROW (CORBA::MARSHAL ());
}

void POA_STDC::QMS::Citizen::Generic_Sensor::_non_existent_skel (
    TAO_ServerRequest &_tao_server_request, 
    void * _tao_object_reference,
    void * /* Servant_Upcall */,
    CORBA::Environment &ACE_TRY_ENV
  )
{
  POA_STDC::QMS::Citizen::Generic_Sensor *_tao_impl = (POA_STDC::QMS::Citizen::Generic_Sensor *) _tao_object_reference;
  CORBA::Boolean _tao_retval = _tao_impl->_non_existent (ACE_TRY_ENV);
  ACE_CHECK;
  
  _tao_server_request.init_reply ();
  TAO_OutputCDR &_tao_out = _tao_server_request.outgoing ();
  if (!(_tao_out << CORBA::Any::from_boolean (_tao_retval)))
    ACE_THROW (CORBA::MARSHAL ());
}

void POA_STDC::QMS::Citizen::Generic_Sensor::_interface_skel (
    TAO_ServerRequest &_tao_server_request, 
    void * _tao_object_reference,
    void * /* Servant_Upcall */,
    CORBA::Environment &ACE_TRY_ENV
  )
{
  POA_STDC::QMS::Citizen::Generic_Sensor *_tao_impl = (POA_STDC::QMS::Citizen::Generic_Sensor *) _tao_object_reference;
  CORBA_InterfaceDef_ptr _tao_retval = 0;
  CORBA::Boolean _tao_result = 0;
  
  TAO_IFR_Client_Adapter *_tao_adapter =
    ACE_Dynamic_Service<TAO_IFR_Client_Adapter>::instance (
        TAO_ORB_Core::ifr_client_adapter_name ()
      );
    
  if (_tao_adapter == 0)
    {
      ACE_THROW (CORBA::INTF_REPOS ());
    }
  
  ACE_TRY
    {
      _tao_retval = _tao_impl->_get_interface (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      
      _tao_server_request.init_reply ();
      
      TAO_OutputCDR &_tao_out = _tao_server_request.outgoing ();
      
      _tao_result =
        _tao_adapter->interfacedef_cdr_insert (
            _tao_out,
            _tao_retval
          );
    }
  ACE_CATCHALL
    {
      _tao_adapter->dispose (_tao_retval);
    }
  ACE_ENDTRY;
  
  if (_tao_result == 0)
    {
      ACE_THROW (CORBA::MARSHAL ());
    }
}

CORBA::Boolean POA_STDC::QMS::Citizen::Generic_Sensor::_is_a (
    const char* value,
    CORBA::Environment &ACE_TRY_ENV
  )
{
  const char *base_id = CORBA::_tc_Object->id (ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);
  
  if (
    (!ACE_OS::strcmp ((char *)value, "IDL:STDC/QMS/Citizen/Generic_Sensor:1.0")) ||
    (!ACE_OS::strcmp ((char *)value, "IDL:STDC/QMS/Citizen/Command:1.0")) ||
    (!ACE_OS::strcmp ((char *)value, "IDL:STDC/QMS/Citizen/Control:1.0")) ||
    (!ACE_OS::strcmp ((char *)value, base_id)))
      return 1;
    else
      return 0;
}

void* POA_STDC::QMS::Citizen::Generic_Sensor::_downcast (
    const char* logical_type_id
  )
{
  if (ACE_OS::strcmp (logical_type_id, "IDL:STDC/QMS/Citizen/Generic_Sensor:1.0") == 0)
    return ACE_static_cast (POA_STDC::QMS::Citizen::Generic_Sensor_ptr, this);
  if (ACE_OS::strcmp (logical_type_id, "IDL:STDC/QMS/Citizen/Command:1.0") == 0)
    return ACE_static_cast (POA_STDC::QMS::Citizen::Command_ptr, this);
  if (ACE_OS::strcmp (logical_type_id, "IDL:STDC/QMS/Citizen/Control:1.0") == 0)
    return ACE_static_cast (POA_STDC::QMS::Citizen::Control_ptr, this);
  if (ACE_OS::strcmp (logical_type_id, "IDL:omg.org/CORBA/Object:1.0") == 0)
    return ACE_static_cast(PortableServer::Servant, this);
  return 0;
}

void POA_STDC::QMS::Citizen::Generic_Sensor::_dispatch (TAO_ServerRequest &req, void *servant_upcall, CORBA::Environment &ACE_TRY_ENV)
{
  this->synchronous_upcall_dispatch (req,
                                     servant_upcall,
                                     this,
                                     ACE_TRY_ENV);
}


const char* POA_STDC::QMS::Citizen::Generic_Sensor::_interface_repository_id (void) const
{
  return "IDL:STDC/QMS/Citizen/Generic_Sensor:1.0";
}

STDC::QMS::Citizen::Generic_Sensor*
POA_STDC::QMS::Citizen::Generic_Sensor::_this (CORBA_Environment &ACE_TRY_ENV)
{
  TAO_Stub *stub = this->_create_stub (ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);
  
  TAO_Stub_Auto_Ptr safe_stub (stub);
  
  CORBA::Object_ptr tmp = CORBA::Object::_nil ();
  
  if (stub->servant_orb_var ()->orb_core ()->optimize_collocation_objects ())
    ACE_NEW_RETURN (tmp, CORBA::Object (stub, 1, this), 0);
  else
    ACE_NEW_RETURN (tmp, CORBA::Object (stub, 0, this), 0);
  
  CORBA::Object_var obj = tmp;
  
  (void) safe_stub.release ();
  
  return ::STDC::QMS::Citizen::Generic_Sensor::_unchecked_narrow (obj.in ());
}



#endif /* ifndef */