package com.stdc.Util;

// CORBA_Handles.java
//
// ============================================================================
// 
// = FILENAME
//    CORBAHandles.java
//
// = AUTHOR
//    Amit Haldankar (amit.haldankar@stdc.com)
//
// = DESCRIPTION
//   This is the administor/factory for a PushConsumer.
//
// ============================================================================

/**
 * @authors Amit Haldankar March 2002
 *
 * A start for QMS in java
 * This is where the bulk of the work gets done. The sequence of steps is
 *   - The orb is initialized, using the command line options, if any
 *   - The portable Object Adapter is next
 *   - Then we create a POA manager
 *   - The naming service handle is the next
 *   - After the naming context, we get a scheduler handle
 *   - Finally, we get hold of the event channel
 *
 */


public class CORBA_Handles {

  public static final int QMS_DEFAULT_RETRIES = 3;
  public static final int QMS_DEFAULT_RETRY_SLEEP_INTERVAL = 60;

  private org.omg.CORBA.ORB _orb = null;
  private org.omg.PortableServer.POA _rootPoa = null;
  private org.omg.PortableServer.POA _poa = null;
  private org.omg.CORBA.Object _poaManager = null;
  private org.omg.CosNaming.NamingContextExt _namingContext = null;
  private RtecScheduler.Scheduler _scheduler = null;
  private org.omg.CosTrading.Lookup _lookupHandle = null;

  private boolean _initialized = false;
  private boolean _poaActivated = false;

  public CORBA_Handles ()
  {
  }

  public void init (String[] args, String orbName)
  {
      System.out.println ("In CORBA_Handles.init");

      if (_initialized) {
          System.out.println ("CORBA_Handles already initialized");
          return;
      }

      try
      {
          _orb = org.omg.CORBA.ORB.init (args, null);
          if ( _orb == null ) {
              int count = 0;
              while ( _orb == null ) {
                  if ( count >= QMS_DEFAULT_RETRIES ) {
                      System.err.println ("Unable to initialize the orb exiting.");
                      System.exit(1);
                  }
                  try { Thread.sleep(QMS_DEFAULT_RETRY_SLEEP_INTERVAL); } catch (InterruptedException e) {}
                  System.out.println ("retrying getting the orb");
                  _orb = org.omg.CORBA.ORB.init (args, null);
                  count++;
              }
          } else {
              System.out.println ("Orb initilized(no external data yet)");
          }
    
          org.omg.CORBA.Object obj = _orb.resolve_initial_references ("RootPOA");
          _rootPoa = org.omg.PortableServer.POAHelper.narrow (obj);
          System.out.println ("Narrowed RootPOA");
          if ( _rootPoa == null ) {
              int count = 0;
              while ( _rootPoa == null ) {
                  if ( count >= QMS_DEFAULT_RETRIES ) {
                      System.err.println ("Unable to initialize the POA exiting.");
                      System.exit(1);
                  }
                  try { Thread.sleep(QMS_DEFAULT_RETRY_SLEEP_INTERVAL); } catch (InterruptedException e) {}
                  System.out.println ("retrying getting root poa");
                  obj = _orb.resolve_initial_references ("RootPOA");
                  _rootPoa = org.omg.PortableServer.POAHelper.narrow (obj);
                  count++;
              }
          } else {
              System.out.println ("Got the root POA(no external data yet)");
          }

          // Getting a reference to the Name Service
          org.omg.CORBA.Object nsobj = _orb.resolve_initial_references("NameService");
          _namingContext = org.omg.CosNaming.NamingContextExtHelper.narrow(nsobj);
          System.out.println("Narrowed the naming context(Connected)");
          if ( _namingContext == null ) {
              int count = 0;
              while ( _namingContext == null ) {
                  if ( count >= QMS_DEFAULT_RETRIES ) {
                      System.err.println ("Unable to get the naming context exiting.");
                      System.exit(1);
                  }
                  try { Thread.sleep(QMS_DEFAULT_RETRY_SLEEP_INTERVAL); } catch (InterruptedException e) {}
                  System.out.println ("retrying getting naming context");
                  nsobj = _orb.resolve_initial_references("NameService");
                  _namingContext = org.omg.CosNaming.NamingContextExtHelper.narrow(nsobj);
                  count++;
              }
          } else {
              System.out.println ("Got the naming context(Connected)");
          }


          // Getting a reference to the Scheduler Service
          _scheduler = 
              RtecScheduler.SchedulerHelper.narrow(
                  _namingContext.resolve(_namingContext.to_name("ScheduleService")));
          System.out.println("Narrowed  the scheduler handle");
          if ( _scheduler == null ) {
              int count = 0;
              while ( _scheduler == null ) {
                  if ( count >= QMS_DEFAULT_RETRIES ) {
                      System.err.println ("Unable to get the scheduler exiting.");
                      System.exit(1);
                  }
                  try { Thread.sleep(QMS_DEFAULT_RETRY_SLEEP_INTERVAL); } catch (InterruptedException e) {}
                  System.out.println ("retrying getting scheduler");
                  _scheduler = 
                      RtecScheduler.SchedulerHelper.narrow(
                          _namingContext.resolve(_namingContext.to_name("ScheduleService")));
                  count++;
              }
          } else {
              System.out.println ("Got the scheduler");
          }

      } catch (org.omg.CosNaming.NamingContextPackage.InvalidName e) {
          System.err.println ("CosNaming.NamingContextPackage.InvalidName");
          System.err.println (e);
      } catch (org.omg.CosNaming.NamingContextPackage.NotFound e) {
          System.err.println ("CosNaming.NamingContextPackage.NotFound");
          System.err.println (e);
      } catch (org.omg.CosNaming.NamingContextPackage.CannotProceed e) {
          System.err.println ("CosNaming.NamingContextPackage.CannotProceed");
          System.err.println (e);
      } catch (org.omg.CORBA.ORBPackage.InvalidName e) {
          System.err.println ("ORBPackage.InvalidName");
          System.err.println (e);
      } catch(org.omg.CORBA.SystemException e) {
          System.err.println ("CORBAHandles : ORB and Name Service initialization");
          System.err.println(e);
      }    

      this._initialized = true;
      System.out.println ("Return CORBA_Handles.init");
      return;
  }
  
  public org.omg.CORBA.ORB get_orb_handle ()
  {
      return this._orb;
  }

  public org.omg.PortableServer.POA get_root_poa_handle ()
  {
      return this._rootPoa;
  }

  public org.omg.CosNaming.NamingContextExt get_naming_handle ()
  {
      return this._namingContext;
  }

  public RtecScheduler.Scheduler get_scheduler_handle ()
  {
      return this._scheduler;
  }

  public RtecEventChannelAdmin.EventChannel get_event_channel (String eventChannelName)
  {

      RtecEventChannelAdmin.EventChannel eventChannel = null;

      System.out.println ("In CORBA_Handles.get_event_channel");
      // Getting a reference to the Event Service
      try {
          eventChannel = 
              RtecEventChannelAdmin.EventChannelHelper.narrow(
                  _namingContext.resolve(_namingContext.to_name(eventChannelName)));
          System.out.println("Narrowed the Event Channel");
          if ( eventChannel == null ) {
              int count = 0;
              while ( eventChannel == null ) {
                  if ( count >= QMS_DEFAULT_RETRIES ) {
                      System.err.println ("Unable to get the Event Channel exiting.");
                      System.exit(1);
                  }
                  try { Thread.sleep(QMS_DEFAULT_RETRY_SLEEP_INTERVAL); } catch (InterruptedException e) {}
                  System.out.println ("retrying getting Event Channel");
                  eventChannel = 
                      RtecEventChannelAdmin.EventChannelHelper.narrow(
                          _namingContext.resolve(_namingContext.to_name(eventChannelName)));
                  count++;
              }
          } else {
              System.out.println ("Got the Event Channel");
          }
      } catch (org.omg.CosNaming.NamingContextPackage.InvalidName e) {
          System.err.println ("CosNaming.NamingContextPackage.InvalidName");
          System.err.println (e);
      } catch (org.omg.CosNaming.NamingContextPackage.NotFound e) {
          System.err.println ("CosNaming.NamingContextPackage.NotFound");
          System.err.println (e);
      } catch (org.omg.CosNaming.NamingContextPackage.CannotProceed e) {
          System.err.println ("CosNaming.NamingContextPackage.CannotProceed");
          System.err.println (e);
      }

      System.out.println ("Return CORBA_Handles.get_event_channel");
      return eventChannel;

  }

  public void activate_poa_manager ()
  {
      try {
          if(!_poaActivated) {
              if ( _rootPoa != null ) {
                  _rootPoa.the_POAManager().activate();
                  _poaActivated = true;
                  System.out.println ("POA Activated"); 
              }
          }
      } catch (org.omg.PortableServer.POAManagerPackage.AdapterInactive e) {
          System.err.println ("PortableServer.POAManagerPackage.AdapterInactive");
          System.err.println (e);
      }
  }

  public org.omg.CosTrading.Lookup get_lookup_handle ()
  {
      try
      {
          if ( _lookupHandle == null ) {
              org.omg.CORBA.Object tradingObj = _orb.resolve_initial_references("TradingService");
              _lookupHandle = org.omg.CosTrading.LookupHelper.narrow(tradingObj);
              if ( _lookupHandle == null ) {
                  int count = 0;
                  while ( _lookupHandle == null ) {
                      if ( count >= QMS_DEFAULT_RETRIES ) {
                          System.err.println ("Unable to locate trading service exiting.");
                          System.exit(1);
                      }
                      try { Thread.sleep(QMS_DEFAULT_RETRY_SLEEP_INTERVAL); } catch (InterruptedException e) {}
                      System.out.println ("retrying getting trading service");
                      tradingObj = _orb.resolve_initial_references("TradingService");
                      _lookupHandle = org.omg.CosTrading.LookupHelper.narrow(tradingObj);
                      count++;
                  }
              } else {
                  System.out.println ("Got the trading service handle");
              }
          }
      } catch (org.omg.CORBA.ORBPackage.InvalidName e) {
          System.err.println ("ORBPackage.InvalidName");
          System.err.println (e);
      }
      return this._lookupHandle;
  }

  public void run ()
  {
      _orb.run();
  }
    
  public void fini ()
  {
      _rootPoa.destroy(true, true);
      _rootPoa = null;

      _orb.destroy();
      _orb = null;
  }
    
  public void disconnect ()
  {
      this._scheduler = null;
      this._namingContext = null;

      fini();
  }

//  public class Object_is_null_exception extends Exception 
//  {
//      Object_is_null_exception (String s) {
//          super (s);
//      }
//  }
  
} // CORBA_Handles
