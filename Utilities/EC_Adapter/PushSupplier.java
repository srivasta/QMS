package com.stdc.Util;

import RtecEventData;
import RtecEventDataHelper;
import RtecEventDataHolder;


// PushSupplier.java
//
// ============================================================================
//
//
// = FILENAME
//    PushSupplier.java
//
// = AUTHOR
//    Amit Haldankar (amit.haldankar@stdc.com)
//
// = DESCRIPTION
//    This is a Push Consumer which takes the data field of the
//    event and updates with it a Data Handler.
//
//
// ============================================================================



// The Consumer has to implement the Skeleton Consumer

public class PushSupplier extends RtecEventComm.PushSupplierPOA
{

  public static final int ACE_ES_EVENT_ANY = 0;
  public static final int ACE_ES_EVENT_SHUTDOWN = 1;
  public static final int ACE_ES_EVENT_ACT = 2;
  public static final int ACE_ES_EVENT_NOTIFICATION = 3;
  public static final int ACE_ES_EVENT_TIMEOUT = 4;
  public static final int ACE_ES_EVENT_INTERVAL_TIMEOUT = 5;
  public static final int ACE_ES_EVENT_DEADLINE_TIMEOUT = 6;
  public static final int ACE_ES_GLOBAL_DESIGNATOR = 7;
  public static final int ACE_ES_CONJUNCTION_DESIGNATOR = 8;
  public static final int ACE_ES_DISJUNCTION_DESIGNATOR = 9;
  public static final int ACE_ES_EVENT_UNDEFINED = 16;
  public static final int TOTAL_MESSAGES = 30;

  private CORBA_Handles _handles = null;
  private int _sendEventType = -1;
  private int _myId = -1;
  private String EventName = null;
  private String _ecName = null;
  private int _disconnect_event_type = PushConsumer.SUPPLIER_DISCONNECT;

  private org.omg.CORBA.ORB _orb;
  private org.omg.PortableServer.POA _poa;
  private RtecScheduler.Scheduler _scheduler;

  private int _rt_info;
  private RtecEventChannelAdmin.EventChannel _eventChannel;
  private RtecEventChannelAdmin.SupplierAdmin _supplier_admin;
  private RtecEventChannelAdmin.ProxyPushConsumer _consumer_proxy;
  private RtecEventChannelAdmin.SupplierQOS _qos;
  private boolean _isScheduled = false;
  private boolean _isSubscribed = false;
  private boolean _connectedToProxy = false;

  public PushSupplier ()
  {
  }

  public PushSupplier (CORBA_Handles CORBAHandles,
                       int sendEventType,
                       int myId,
                       String ecName)
  {
      this.init(CORBAHandles, sendEventType, myId, ecName);
  }

  public void init (CORBA_Handles CORBAHandles,
                    int sendEventType,
                    int myId,
                    String ecName)
  {
      this._handles = CORBAHandles;
      _orb = CORBAHandles.get_orb_handle();
      _poa = CORBAHandles.get_root_poa_handle();
      _scheduler = CORBAHandles.get_scheduler_handle();

      this._sendEventType = sendEventType;
      this._myId = myId;
      this.EventName = "Send QMS Message";
      this._ecName = ecName;
      try {

        // Define Real-time information
        System.out.println("Event Name = " + EventName);
        this._rt_info = _scheduler.create (EventName);

        default_schedule();

        // Register Publishing events

        byte payload[] = new byte[1];
        payload[0] = 0;
        RtecEventComm.Event notification_event_ = new RtecEventComm.Event ();
        notification_event_.header =
          new RtecEventComm.EventHeader (_sendEventType,     //type
                                         _myId,               //source
                                         1,                  //ttl
                                         0L,                 //creation_time
                                         0L,                 //ec_recv_time
                                         0L                  //ec_send_time
                                        );

        notification_event_.data =
          new RtecEventData (0, payload, _orb.create_any());

        RtecBase.Dependency_Info dependency_info = 
                     new RtecBase.Dependency_Info(
                         RtecBase.Dependency_Type_t.ONE_WAY_CALL,          //Dependency Type
                         1,                                                //No of calls
                         _rt_info                                          //rt_info
                         );
        RtecEventChannelAdmin.Publication publications_[] = new RtecEventChannelAdmin.Publication[1];
        publications_[0] = new RtecEventChannelAdmin.Publication (notification_event_, dependency_info);


        // Get SupplierQOS
        _qos = new RtecEventChannelAdmin.SupplierQOS (publications_, false);

      } catch (RtecScheduler.DUPLICATE_NAME e) {
          System.err.println ("PushSupplier.init: Duplicate names");
          System.err.println (e);
      } catch (RtecScheduler.INTERNAL e) {
          System.err.println ("PushSupplier.init: internal scheduler error");
          System.err.println (e);
      } catch (RtecScheduler.SYNCHRONIZATION_FAILURE e) {
          System.err.println ("PushSupplier.init: scheduler synchronization failure");
          System.err.println (e);
      } catch(org.omg.CORBA.SystemException e) {
          System.err.println(e);
      }
  }

  private void default_schedule ()
  {
      try {
          System.out.println("Setting Scheduler Parameters");
          _scheduler.set (_rt_info,
                          RtecScheduler.Criticality_t.VERY_LOW_CRITICALITY,
                          0L,
                          0L,
                          0L,
                          2500000,  // period
                          RtecScheduler.Importance_t.VERY_LOW_IMPORTANCE,
                          0L,
                          1,
                          RtecScheduler.Info_Type_t.OPERATION);
          System.out.println("Scheduler Parameters set");
          _isScheduled = true;
      } catch(org.omg.CORBA.SystemException e) {
          System.err.println("SYS_EX Setting schedule");
          System.err.println(e);
      } catch (RtecScheduler.UNKNOWN_TASK e) {
          System.err.println ("PushSupplier.init: Unknown task");
          System.err.println (e);
      } catch (RtecScheduler.SYNCHRONIZATION_FAILURE e) {
          System.err.println ("PushSupplier.init: scheduler synchronization failure");
          System.err.println (e);
      } catch (RtecScheduler.INTERNAL e) {
          System.err.println ("PushSupplier.default_schedule: internal scheduler error");
          System.err.println (e);
      }
  }

  public void connect ()
  {
      try {
          if ( _isScheduled == false )
              default_schedule();

          // Connect as a supplier
          if ( _supplier_admin == null ) {
              System.out.println("Connecting to EC " + _ecName);
              if ( _eventChannel == null )
                  _eventChannel =
                      _handles.get_event_channel(_ecName);

              System.out.println("Getting Supplier Admin");
              _supplier_admin = _eventChannel.for_suppliers ();
              int count = 0;
              while ( _supplier_admin == null ) {
                  if ( count >= CORBA_Handles.QMS_DEFAULT_RETRIES ) {
                      System.err.println ("Unable to get supplier admin object exiting.");
                      System.exit(1);
                  }
                  try { Thread.sleep(CORBA_Handles.QMS_DEFAULT_RETRY_SLEEP_INTERVAL); 
                  } catch (InterruptedException e) {}
                  System.out.println ("retrying getting consumer admin object");
                  _supplier_admin = _eventChannel.for_suppliers ();
                  count++;
              }
              System.out.println("Got Supplier Admin");
          }

          // Obtain a reference to the proxy push consumer

          if ( _consumer_proxy == null ) {
              System.out.println("Getting Proxy Push Consumer");
              _consumer_proxy = _supplier_admin.obtain_push_consumer ();
              int count = 0;
              while ( _consumer_proxy == null ) {
                  if ( count >= CORBA_Handles.QMS_DEFAULT_RETRIES ) {
                      System.err.println ("Unable to get proxy push consumer exiting.");
                      System.exit(1);
                  }
                  try { Thread.sleep(CORBA_Handles.QMS_DEFAULT_RETRY_SLEEP_INTERVAL); 
                  } catch (InterruptedException e) {}
                  System.out.println ("retrying getting proxy push consumer");
                  _consumer_proxy = _supplier_admin.obtain_push_consumer ();
                  count++;
              }
              System.out.println("Got Proxy Push Consumer");
          }

          if ( !_connectedToProxy ) {
              org.omg.CORBA.Object objref = _poa.servant_to_reference (this);

              RtecEventComm.PushSupplier supplier_ref = 
                RtecEventComm.PushSupplierHelper.narrow (objref);

              _consumer_proxy.connect_push_supplier (supplier_ref, _qos);

              _connectedToProxy = true;
          }

          System.out.println ("Registered the supplier successfully.");

      } catch(org.omg.CORBA.SystemException e) {
          System.err.println("SYS_EX Setting schedule");
          System.err.println(e);
      } catch (org.omg.PortableServer.POAPackage.WrongPolicy e) {
          System.err.println ("PushSupplier.connect: org.omg.PortableServer.POAPackage.WrongPolicy");
          System.err.println (e);
      } catch (org.omg.PortableServer.POAPackage.ServantNotActive e) {
          System.err.println ("PushConsumer.connect: org.omg.PortableServer.POAPackage.ServantNotActive");
          System.err.println (e);
//      } catch (RtecEventChannelAdmin.TypeError e) {
//          System.err.println ("PushConsumer.connect: RtecEventChannelAdmin.TypeError");
//          System.err.println (e);
      } catch (RtecEventChannelAdmin.AlreadyConnected e) {
          System.err.println ("Demo_Consumer.open_consumer: RtecEventChannelAdmin.AlreadyConnected");
          System.err.println (e);
      }
  }

  public int send (String mesg)
  {
        RtecEventComm.Event events[] = new RtecEventComm.Event[1];

        events[0] = new RtecEventComm.Event ();
        events[0].header =
          new RtecEventComm.EventHeader (_sendEventType,     //type
                                         _myId,               //source
                                         1,                  //ttl
                                         0L,                 //creation_time
                                         0L,                 //ec_recv_time
                                         0L                  //ec_send_time
                                        );

        byte payload[] = mesg.getBytes();

        events[0].data =
          new RtecEventData (0, payload, _orb.create_any());

        _consumer_proxy.push (events);

        return 0;
  }

  public void disconnect_push_supplier()
  {
      System.out.println ("Demo Supplier: Have to disconnect!");
      send_disconnect_event();
  }

  public void send_disconnect_event()
  {
        RtecEventComm.Event events[] = new RtecEventComm.Event[1];

        events[0] = new RtecEventComm.Event ();
        events[0].header =
          new RtecEventComm.EventHeader (_disconnect_event_type,     //type
                                         _myId,                      //source
                                         1,                         //ttl
                                         0L,                        //creation_time
                                         0L,                        //ec_recv_time
                                         0L                         //ec_send_time
                                        );

        byte payload[] = new byte[1];
        payload[0] = 0;

        events[0].data =
          new RtecEventData (0, payload, _orb.create_any());

        _consumer_proxy.push (events);

        return;
  }

  public void disconnect()
  {
      if ( _consumer_proxy == null )
          return;

      if (this._connectedToProxy){
          _consumer_proxy.disconnect_push_consumer();
          _connectedToProxy = false;
      }

      if ( _consumer_proxy != null )
          _consumer_proxy = null;

      if ( _supplier_admin != null )
          _supplier_admin = null;

      try {
          _poa.deactivate_object (_poa.servant_to_id (this));
      } catch ( org.omg.PortableServer.POAPackage.ServantNotActive e ) {
          System.err.println ("PushSupplier.disconnect: ServantNotActive");
          System.err.println (e);
      } catch (org.omg.PortableServer.POAPackage.WrongPolicy e) {
          System.err.println ("PushSupplier.disconnect: WrongPolicy");
          System.err.println (e);
      } catch (org.omg.PortableServer.POAPackage.ObjectNotActive e) {
          System.err.println ("PushSupplier.disconnect: ObjectNotActive");
          System.err.println (e);
      }
  }

}
