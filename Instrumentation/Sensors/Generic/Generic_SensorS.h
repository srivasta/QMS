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

#ifndef _TAO_IDL_GENERIC_SENSORS_H_
#define _TAO_IDL_GENERIC_SENSORS_H_

#include "CommandS.h"
#include "Generic_SensorC.h"


#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/PortableServer/PortableServer.h"
#include "tao/PortableServer/Servant_Base.h"
#include "tao/PortableServer/Collocated_Object.h"
#include "tao/PortableServer/ThruPOA_Object_Proxy_Impl.h"
#include "tao/PortableServer/Direct_Object_Proxy_Impl.h"
#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option push -w-rvl -w-rch -w-ccc -w-inl
#endif /* __BORLANDC__ */

TAO_NAMESPACE  POA_STDC
{
  TAO_NAMESPACE  QMS
  {
    TAO_NAMESPACE  Citizen
    {
      class Generic_Sensor;
      typedef Generic_Sensor *Generic_Sensor_ptr;
      // Forward Classes Declaration
      class _TAO_Generic_Sensor_ThruPOA_Proxy_Impl;
      class _TAO_Generic_Sensor_Strategized_Proxy_Broker;
      
      class  Generic_Sensor
        : public virtual POA_STDC::QMS::Citizen::Command
      {
      protected:
        Generic_Sensor (void);

      public:
        Generic_Sensor (const Generic_Sensor& rhs);
        virtual ~Generic_Sensor (void);


        virtual CORBA::Boolean _is_a (
            const char* logical_type_id,
            CORBA::Environment &ACE_TRY_ENV = 
              TAO_default_environment ()
          );

        virtual void* _downcast (
            const char* logical_type_id
          );

        static void _is_a_skel (
            TAO_ServerRequest &req,
            void *obj,
            void *servant_upcall,
            CORBA::Environment &ACE_TRY_ENV
          );

        static void _non_existent_skel (
            TAO_ServerRequest &req,
            void *obj,
            void *servant_upcall,
            CORBA::Environment &ACE_TRY_ENV
          );

        static void _interface_skel (
            TAO_ServerRequest &req,
            void *obj,
            void *servant_upcall,
            CORBA::Environment &ACE_TRY_ENV
          );

        virtual void _dispatch (
            TAO_ServerRequest &req,
            void *_servant_upcall,
            CORBA::Environment &ACE_TRY_ENV
          );

        ::STDC::QMS::Citizen::Generic_Sensor *_this (
            CORBA::Environment &ACE_TRY_ENV = 
              TAO_default_environment ()
          );

        virtual const char* _interface_repository_id (void) const;

        static void disconnect_EC_skel (
            TAO_ServerRequest &req, 
            void *obj,
            void *context,
            CORBA::Environment &ACE_TRY_ENV =
              TAO_default_environment ()
          );

        static void reconnect_EC_skel (
            TAO_ServerRequest &req, 
            void *obj,
            void *context,
            CORBA::Environment &ACE_TRY_ENV =
              TAO_default_environment ()
          );

        static void show_operating_level_skel (
            TAO_ServerRequest &req, 
            void *obj,
            void *context,
            CORBA::Environment &ACE_TRY_ENV =
              TAO_default_environment ()
          );

        static void set_operating_level_skel (
            TAO_ServerRequest &req, 
            void *obj,
            void *context,
            CORBA::Environment &ACE_TRY_ENV =
              TAO_default_environment ()
          );

        static void stats_skel (
            TAO_ServerRequest &req, 
            void *obj,
            void *context,
            CORBA::Environment &ACE_TRY_ENV =
              TAO_default_environment ()
          );

        static void ping_skel (
            TAO_ServerRequest &req, 
            void *obj,
            void *context,
            CORBA::Environment &ACE_TRY_ENV =
              TAO_default_environment ()
          );

        static void pause_skel (
            TAO_ServerRequest &req, 
            void *obj,
            void *context,
            CORBA::Environment &ACE_TRY_ENV =
              TAO_default_environment ()
          );

        static void resume_skel (
            TAO_ServerRequest &req, 
            void *obj,
            void *context,
            CORBA::Environment &ACE_TRY_ENV =
              TAO_default_environment ()
          );

        static void stop_skel (
            TAO_ServerRequest &req, 
            void *obj,
            void *context,
            CORBA::Environment &ACE_TRY_ENV =
              TAO_default_environment ()
          );


      };

      
      ///////////////////////////////////////////////////////////////////////
      //               Strategized Proxy Broker Declaration 
      //
      
      class  _TAO_Generic_Sensor_Strategized_Proxy_Broker : public virtual ::STDC::QMS::Citizen::_TAO_Generic_Sensor_Proxy_Broker
      {
      public: 
        _TAO_Generic_Sensor_Strategized_Proxy_Broker (void);
        
        virtual ~_TAO_Generic_Sensor_Strategized_Proxy_Broker (void);
        
        virtual ::STDC::QMS::Citizen::_TAO_Generic_Sensor_Proxy_Impl &select_proxy (
          ::STDC::QMS::Citizen::Generic_Sensor *object,
          CORBA_Environment &ACE_TRY_ENV
        );
      
      private:
        // Helper methods that takes care to create the proxy
        // as soon as their use is necessary.
        void create_proxy (
          int collocation_strategy,
          CORBA::Environment &ACE_TRY_ENV
        );
        
        // Caches the proxy implementations. The proxy implementation
        // are totally stateless, and those can be shared by all the
        // instances of a given IDL interface type.
        ::STDC::QMS::Citizen::_TAO_Generic_Sensor_Proxy_Impl
        *proxy_cache_[TAO_Collocation_Strategies::CS_LAST];
        
        TAO_SYNCH_MUTEX mutex_;
        // This funxtion is used to get an handle to the unique instance
        // of the Strategized Proxy Broker that is available for a given
        // interface.
      
      public:
        static _TAO_Generic_Sensor_Strategized_Proxy_Broker *the_TAO_Generic_Sensor_Strategized_Proxy_Broker (void);
      };
      
      
      //
      //            End Strategized Proxy Broker Declaration 
      ///////////////////////////////////////////////////////////////////////
      
      
      ///////////////////////////////////////////////////////////////////////
      //                    ThruPOA  Impl. Declaration
      //
      
      class  _TAO_Generic_Sensor_ThruPOA_Proxy_Impl : 
        public virtual ::STDC::QMS::Citizen::_TAO_Generic_Sensor_Proxy_Impl,
        public virtual TAO_ThruPOA_Object_Proxy_Impl,
        public virtual ::POA_STDC::QMS::Citizen::_TAO_Command_ThruPOA_Proxy_Impl
        
      {
      public:
        _TAO_Generic_Sensor_ThruPOA_Proxy_Impl (void);
        
        virtual ~_TAO_Generic_Sensor_ThruPOA_Proxy_Impl (void) { }
        
        
      };
      
      //
      //                ThruPOA  Proxy Impl. Declaration
      ///////////////////////////////////////////////////////////////////////
      
      
    }
    TAO_NAMESPACE_CLOSE // module STDC::QMS::Citizen

  }
  TAO_NAMESPACE_CLOSE // module STDC::QMS

}
TAO_NAMESPACE_CLOSE // module STDC

#include "Generic_SensorS_T.h"

#if defined (__ACE_INLINE__)
#include "Generic_SensorS.i"
#endif /* defined INLINE */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option pop
#endif /* __BORLANDC__ */

#endif /* ifndef */