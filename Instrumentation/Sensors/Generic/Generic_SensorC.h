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

#ifndef _TAO_IDL_GENERIC_SENSORC_H_
#define _TAO_IDL_GENERIC_SENSORC_H_

#include "tao/corba.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "CommandC.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO 

#if defined (TAO_EXPORT_NESTED_CLASSES)
#  if defined (TAO_EXPORT_NESTED_MACRO)
#    undef TAO_EXPORT_NESTED_MACRO
#  endif /* defined (TAO_EXPORT_NESTED_MACRO) */
#  define TAO_EXPORT_NESTED_MACRO 
#endif /* TAO_EXPORT_NESTED_CLASSES */

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option push -w-rvl -w-rch -w-ccc -w-inl
#endif /* __BORLANDC__ */

TAO_NAMESPACE  STDC
{
    TAO_NAMESPACE  QMS
  {
        TAO_NAMESPACE  Citizen
    {
      
#if !defined (_STDC_QMS_CITIZEN_GENERIC_SENSOR___PTR_CH_)
#define _STDC_QMS_CITIZEN_GENERIC_SENSOR___PTR_CH_
      
      class Generic_Sensor;
      typedef Generic_Sensor *Generic_Sensor_ptr;
      
#endif /* end #if !defined */
      
      
#if !defined (_STDC_QMS_CITIZEN_GENERIC_SENSOR___VAR_CH_)
#define _STDC_QMS_CITIZEN_GENERIC_SENSOR___VAR_CH_
      
      class  Generic_Sensor_var : public TAO_Base_var
      {
      public:
        Generic_Sensor_var (void); // default constructor
        Generic_Sensor_var (Generic_Sensor_ptr p) : ptr_ (p) {} 
        Generic_Sensor_var (const Generic_Sensor_var &); // copy constructor
        ~Generic_Sensor_var (void); // destructor
        
        Generic_Sensor_var &operator= (Generic_Sensor_ptr);
        Generic_Sensor_var &operator= (const Generic_Sensor_var &);
        Generic_Sensor_ptr operator-> (void) const;
        
        operator const Generic_Sensor_ptr &() const;
        operator Generic_Sensor_ptr &();
        // in, inout, out, _retn 
        Generic_Sensor_ptr in (void) const;
        Generic_Sensor_ptr &inout (void);
        Generic_Sensor_ptr &out (void);
        Generic_Sensor_ptr _retn (void);
        Generic_Sensor_ptr ptr (void) const;
        
        // Hooks used by template sequence and object manager classes
        // for non-defined forward declared interfaces.
        static Generic_Sensor_ptr tao_duplicate (Generic_Sensor_ptr);
        static void tao_release (Generic_Sensor_ptr);
        static Generic_Sensor_ptr tao_nil (void);
        static Generic_Sensor_ptr tao_narrow (
            CORBA::Object *,
            CORBA::Environment &
          );
        static CORBA::Object * tao_upcast (void *);
      
      private:
        Generic_Sensor_ptr ptr_;
        // Unimplemented - prevents widening assignment.
        Generic_Sensor_var (const TAO_Base_var &rhs);
        Generic_Sensor_var &operator= (const TAO_Base_var &rhs);
      };


#endif /* end #if !defined */
      
      
#if !defined (_STDC_QMS_CITIZEN_GENERIC_SENSOR___OUT_CH_)
#define _STDC_QMS_CITIZEN_GENERIC_SENSOR___OUT_CH_
      
      class  Generic_Sensor_out
      {
      public:
        Generic_Sensor_out (Generic_Sensor_ptr &);
        Generic_Sensor_out (Generic_Sensor_var &);
        Generic_Sensor_out (const Generic_Sensor_out &);
        Generic_Sensor_out &operator= (const Generic_Sensor_out &);
        Generic_Sensor_out &operator= (const Generic_Sensor_var &);
        Generic_Sensor_out &operator= (Generic_Sensor_ptr);
        operator Generic_Sensor_ptr &();
        Generic_Sensor_ptr &ptr (void);
        Generic_Sensor_ptr operator-> (void);
      
      private:
        Generic_Sensor_ptr &ptr_;
      };
      
      
#endif /* end #if !defined */
      
      
#if !defined (_STDC_QMS_CITIZEN_GENERIC_SENSOR_CH_)
#define _STDC_QMS_CITIZEN_GENERIC_SENSOR_CH_
      
      // Forward Classes Declaration.
      class _TAO_Generic_Sensor_Proxy_Impl;
      class _TAO_Generic_Sensor_Remote_Proxy_Impl;
      class _TAO_Generic_Sensor_Proxy_Broker;
      class _TAO_Generic_Sensor_Remote_Proxy_Broker;
      
      class  Generic_Sensor
        : public virtual STDC::QMS::Citizen::Command
      {
      public:
      #if !defined(__GNUC__) || !defined (ACE_HAS_GNUG_PRE_2_8)
        typedef Generic_Sensor_ptr _ptr_type;
        typedef Generic_Sensor_var _var_type;
      #endif /* ! __GNUC__ || g++ >= 2.8 */

        static int _tao_class_id;
        
        // The static operations.
        static Generic_Sensor_ptr _duplicate (Generic_Sensor_ptr obj);
        
        static Generic_Sensor_ptr _narrow (
            CORBA::Object_ptr obj,
            CORBA::Environment &ACE_TRY_ENV = 
              TAO_default_environment ()
          );
        
        static Generic_Sensor_ptr _unchecked_narrow (
            CORBA::Object_ptr obj,
            CORBA::Environment &ACE_TRY_ENV = 
              TAO_default_environment ()
          );
        
        static Generic_Sensor_ptr _nil (void)
          {
            return (Generic_Sensor_ptr)0;
          }
        
        static void _tao_any_destructor (void*);
        
        virtual CORBA::Boolean _is_a (
            const CORBA::Char *type_id, 
            CORBA::Environment &ACE_TRY_ENV = 
              TAO_default_environment ()
          );
        
        virtual void *_tao_QueryInterface (ptr_arith_t type);
        
        virtual const char* _interface_repository_id (void) const;

      private:
        _TAO_Generic_Sensor_Proxy_Broker *the_TAO_Generic_Sensor_Proxy_Broker_;
        
      protected:
        Generic_Sensor (int collocated = 0);
        
        // These methods travese the inheritance tree and set the
        // parents piece of the given class in the right mode
        virtual void STDC_QMS_Citizen_Generic_Sensor_setup_collocation (int collocated);
        
        Generic_Sensor (
            TAO_Stub *objref, 
            CORBA::Boolean _tao_collocated = 0,
            TAO_Abstract_ServantBase *servant = 0
          );
        
        friend class _TAO_Generic_Sensor_Remote_Proxy_Impl;
        friend class _TAO_Generic_Sensor_ThruPOA_Proxy_Impl;
        friend class _TAO_Generic_Sensor_Direct_Proxy_Impl;
        
        virtual ~Generic_Sensor (void);
      
      private:
        Generic_Sensor (const Generic_Sensor &);
        void operator= (const Generic_Sensor &);
      };
      
      // The Proxy Implementations are used by each interface to
      // perform a call. Each different implementation encapsulate
      // an invocation logics.
      
      
      ///////////////////////////////////////////////////////////////////////
      //                    Base Proxy Impl. Declaration
      //
      
      class  _TAO_Generic_Sensor_Proxy_Impl
        : public virtual STDC::QMS::Citizen::_TAO_Command_Proxy_Impl
      {
      public:
        virtual ~_TAO_Generic_Sensor_Proxy_Impl (void) { }
        
      protected:
        _TAO_Generic_Sensor_Proxy_Impl (void);
      };
      
      //
      //               End Base Proxy Impl. Declaration
      ///////////////////////////////////////////////////////////////////////
      
      
      ///////////////////////////////////////////////////////////////////////
      //                Remote Proxy Impl. Declaration
      //
      
      class  _TAO_Generic_Sensor_Remote_Proxy_Impl
        : public virtual _TAO_Generic_Sensor_Proxy_Impl,
          public virtual TAO_Remote_Object_Proxy_Impl,
          public virtual STDC::QMS::Citizen::_TAO_Command_Remote_Proxy_Impl
      {
      public:
        _TAO_Generic_Sensor_Remote_Proxy_Impl (void);
        
        virtual ~_TAO_Generic_Sensor_Remote_Proxy_Impl (void) { }
        
      };
      
      //
      //             End Remote Proxy Impl. Declaration
      ///////////////////////////////////////////////////////////////////////
      
      // The Proxy Brokers are used by each interface to get
      // the right proxy for performing a call. In the new 
      // collocation scheme, the proxy to be used can vary on
      // a call by call basis.
      
      
      ///////////////////////////////////////////////////////////////////////
      //                 Base Proxy Broker Declaration 
      //
      
            class  _TAO_Generic_Sensor_Proxy_Broker
      {
      public:
        virtual ~_TAO_Generic_Sensor_Proxy_Broker (void);
        virtual _TAO_Generic_Sensor_Proxy_Impl &select_proxy (
            Generic_Sensor *object,
            CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ()
          ) = 0;
        
      protected:
        _TAO_Generic_Sensor_Proxy_Broker (void);
        
      };
      
      //
      //              End Base Proxy Broker Declaration 
      ///////////////////////////////////////////////////////////////////////
      
            
      ///////////////////////////////////////////////////////////////////////
      //                 Remote Proxy Broker Declaration 
      //
      
      class  _TAO_Generic_Sensor_Remote_Proxy_Broker
        : public virtual _TAO_Generic_Sensor_Proxy_Broker
      {
      public: 
        _TAO_Generic_Sensor_Remote_Proxy_Broker (void);
        
        virtual ~_TAO_Generic_Sensor_Remote_Proxy_Broker (void);
        
        virtual _TAO_Generic_Sensor_Proxy_Impl &select_proxy (
            Generic_Sensor *object,
            CORBA_Environment &ACE_TRY_ENV
          );
        
      private:
        _TAO_Generic_Sensor_Remote_Proxy_Impl remote_proxy_impl_;
      
      public:
        // This member function is used to get an handle to the unique instance
        // of the Remote Proxy Broker that is available for a given
        // interface.
        static _TAO_Generic_Sensor_Remote_Proxy_Broker *the_TAO_Generic_Sensor_Remote_Proxy_Broker (void);
      };
      
      //
      //              End Remote Proxy Broker Declaration 
      ///////////////////////////////////////////////////////////////////////
      
      
#endif /* end #if !defined */
      
      TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_Generic_Sensor;
      
      
    }
TAO_NAMESPACE_CLOSE // module STDC::QMS::Citizen


  }
TAO_NAMESPACE_CLOSE // module STDC::QMS


}
TAO_NAMESPACE_CLOSE // module STDC

// Proxy Broker Factory function pointer declarations.

extern 
STDC::QMS::Citizen::_TAO_Generic_Sensor_Proxy_Broker *
(*STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Factory_function_pointer) (
    CORBA::Object_ptr obj
  );

// Any operators for interface STDC::QMS::Citizen::Generic_Sensor
 void operator<<= (CORBA::Any &, STDC::QMS::Citizen::Generic_Sensor_ptr);
 CORBA::Boolean operator>>= (const CORBA::Any &, STDC::QMS::Citizen::Generic_Sensor *&);

#ifndef __ACE_INLINE__

 CORBA::Boolean operator<< (TAO_OutputCDR &, const STDC::QMS::Citizen::Generic_Sensor_ptr );
 CORBA::Boolean operator>> (TAO_InputCDR &, STDC::QMS::Citizen::Generic_Sensor_ptr &);

#endif /* __ACE_INLINE__ */


#if defined (__ACE_INLINE__)
#include "Generic_SensorC.i"
#endif /* defined INLINE */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option pop
#endif /* __BORLANDC__ */

#endif /* ifndef */
