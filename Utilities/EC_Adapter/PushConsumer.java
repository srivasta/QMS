package com.stdc.Util;

import RtecEventData;
import RtecEventDataHelper;
import RtecEventDataHolder;


// PushConsumer.java
//
// ============================================================================
//
//
// = FILENAME
//    PushConsumer.java
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

public class PushConsumer extends RtecEventComm.PushConsumerPOA
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

  public static final int QMS_DISCONNECT = 10000;
  public static final int SUPPLIER_DISCONNECT = 20000;

  private CORBA_Handles _handles = null;
  private int _getEventType = -1;
  private String EventName = null;
  private String _ecName = null;
  private CallBack _callbackObj = null;
  private Object _argObj = null;

  private org.omg.CORBA.ORB _orb;
  private org.omg.PortableServer.POA _poa;
  private RtecScheduler.Scheduler _scheduler;

  private int _total_received = 0;
  private int _totalEvents = 0;
  private int _rt_info;
  private RtecEventChannelAdmin.EventChannel _eventChannel;
  private RtecEventChannelAdmin.ConsumerAdmin _consumer_admin;
  private RtecEventChannelAdmin.ProxyPushSupplier _supplier_proxy;
  private RtecEventChannelAdmin.ConsumerQOS _qos;
  private boolean _isScheduled = false;
  private boolean _isSubscribed = false;
  private boolean _connectedToProxy = false;

  public PushConsumer ()
  {
  }


  public PushConsumer (CORBA_Handles CORBAHandles,
                       int eventType,
                       String ecName)

  {
      this.init(CORBAHandles, eventType, ecName);
  }

  public void init (CORBA_Handles CORBAHandles,
                    int eventType,
                    String ecName)

  {
      System.out.println ("In PushConsumer.init");

      this._handles = CORBAHandles;
      _orb = CORBAHandles.get_orb_handle();
      _poa = CORBAHandles.get_root_poa_handle();
      _scheduler = CORBAHandles.get_scheduler_handle();

      this._getEventType = eventType;
      this.EventName = "Consume QMS Message";
      this._ecName = ecName;

      try
      {
        // Define Real-time information

        this._rt_info = _scheduler.create (EventName);

        default_schedule();

        // Register for Notification and Shutdown events
        byte payload[] = new byte[1];
        payload[0] = 0;

        RtecEventComm.Event start_disjunction_group = new RtecEventComm.Event ();
        start_disjunction_group.header =
          new RtecEventComm.EventHeader (ACE_ES_DISJUNCTION_DESIGNATOR,
                                         0, 1, 0, 0, 0);
        start_disjunction_group.data =
          new RtecEventData (0, payload, _orb.create_any());


        RtecEventComm.Event notification_event_ = new RtecEventComm.Event ();

        notification_event_.header =
          new RtecEventComm.EventHeader (_getEventType,   //type
                                         0,               //source
                                         1,               //ttl
                                         0L,              //creation_time
                                         0L,              //ec_recv_time
                                         0L               //ec_send_time
                                        );

        notification_event_.data =
          new RtecEventData (0,                           // pad
                             payload,                     // payload
                             _orb.create_any()            // any_value
                            );

        RtecEventComm.Event qms_disconnect_event = new RtecEventComm.Event ();
        qms_disconnect_event.header =
          new RtecEventComm.EventHeader (QMS_DISCONNECT,
                                         0, 1, 0, 0, 0);
        qms_disconnect_event.data =
          new RtecEventData (0, payload, _orb.create_any());

        RtecEventComm.Event supplier_disconnect_event = new RtecEventComm.Event ();
        supplier_disconnect_event.header =
          new RtecEventComm.EventHeader (SUPPLIER_DISCONNECT,
                                         0, 1, 0, 0, 0);
        supplier_disconnect_event.data =
          new RtecEventData (0, payload, _orb.create_any());


        RtecEventChannelAdmin.Dependency dependencies_[] = new RtecEventChannelAdmin.Dependency[4];
        dependencies_[0] = new RtecEventChannelAdmin.Dependency (start_disjunction_group, 0);
        dependencies_[1] = new RtecEventChannelAdmin.Dependency (notification_event_, _rt_info);
        dependencies_[2] = new RtecEventChannelAdmin.Dependency (qms_disconnect_event, _rt_info);
        dependencies_[3] = new RtecEventChannelAdmin.Dependency (supplier_disconnect_event, _rt_info);


        // get ConsumerQOS
        this._qos = new RtecEventChannelAdmin.ConsumerQOS (dependencies_, false);

        _isSubscribed = true;

      } catch (RtecScheduler.DUPLICATE_NAME e) {
          System.err.println ("Demo_Consumer.open_consumer: Duplicate names");
          System.err.println (e);
      } catch (RtecScheduler.INTERNAL e) {
          System.err.println ("Demo_Consumer.open_consumer: internal scheduler error");
          System.err.println (e);
      } catch (RtecScheduler.SYNCHRONIZATION_FAILURE e) {
          System.err.println ("Demo_Consumer.open_consumer: scheduler synchronization failure");
          System.err.println (e);
      } catch(org.omg.CORBA.SystemException e) {
          System.err.println(e);
      }

      System.out.println ("Return PushConsumer.init");
  }

  public void push (RtecEventComm.Event[] events)
  {
      System.out.println ("In PushConsumer.push");

      if (events.length == 0) {
          System.err.println ("No events");
          return;
      }

      String eventData = null;
      // looping over the set of events
      for (int i = 0; i < events.length; ++i){
//          System.out.println ("event number = " + i + " Type = " +  events[i].header.type);
          eventData = new String (events[i].data.payload);

          if (_callbackObj != null)
           {
             System.out.println ("Before Consumer callback\n");
             _callbackObj.callback(eventData, _argObj);
             System.out.println ("Consumer done callback\n");
           }
          else
           {
             System.out.println ("Consumer no callback registered\n");
//             throw new Exception("Bad Parameters");
           }
           _totalEvents++;
      }
      _total_received++;
      System.out.println ("Push Consumer: Received an event set! ->Number: "
                            + _total_received
                            + " Total events = " + _totalEvents);

      System.out.println ("Return PushConsumer.push");
  }

  public void connect ()
  {
      System.out.println ("In PushConsumer.connect");
      try {
          if ( _isScheduled == false )
              default_schedule();

          // Connect as a consumer
          if ( _consumer_admin == null ) {
              System.out.println("Connecting to EC " + _ecName);
              if ( _eventChannel == null )
                  _eventChannel =
                      _handles.get_event_channel(_ecName);

              System.out.println("Getting Consumer Admin");
              _consumer_admin = _eventChannel.for_consumers ();
              int count = 0;
              while ( _consumer_admin == null ) {
                  if ( count >= CORBA_Handles.QMS_DEFAULT_RETRIES ) {
                      System.err.println ("Unable to get consumer admin object exiting.");
                      System.exit(1);
                  }
                  try { Thread.sleep(CORBA_Handles.QMS_DEFAULT_RETRY_SLEEP_INTERVAL); 
                  } catch (InterruptedException e) {}
                  System.out.println ("retrying getting consumer admin object");
                  _consumer_admin = _eventChannel.for_consumers ();
                  count++;
              }
              System.out.println("Got Consumer Admin");
          }

          // Obtain a reference to the proxy push supplier

          if ( _supplier_proxy == null ) {
              System.out.println("Getting Proxy Push Supplier");
              _supplier_proxy = _consumer_admin.obtain_push_supplier ();
              int count = 0;
              while ( _supplier_proxy == null ) {
                  if ( count >= CORBA_Handles.QMS_DEFAULT_RETRIES ) {
                      System.err.println ("Unable to get proxy push supplier exiting.");
                      System.exit(1);
                  }
                  try { Thread.sleep(CORBA_Handles.QMS_DEFAULT_RETRY_SLEEP_INTERVAL); 
                  } catch (InterruptedException e) {}
                  System.out.println ("retrying getting proxy push supplier");
                  _supplier_proxy = _consumer_admin.obtain_push_supplier ();
                  count++;
              }
              System.out.println("Got Proxy Push Supplier");
          }

          if ( !_connectedToProxy ) {
              org.omg.CORBA.Object objref = _poa.servant_to_reference (this);
              RtecEventComm.PushConsumer consumer_ref = 
                            RtecEventComm.PushConsumerHelper.narrow (objref);
              _supplier_proxy.connect_push_consumer (consumer_ref, _qos);
              _connectedToProxy = true;
          }

          System.out.println ("Registered the consumer successfully.");

      } catch(org.omg.CORBA.SystemException e) {
          System.err.println("System Exception connecting Push Consumer");
          System.err.println(e);
      } catch (org.omg.PortableServer.POAPackage.WrongPolicy e) {
          System.err.println ("PushConsumer.connect: org.omg.PortableServer.POAPackage.WrongPolicy");
          System.err.println (e);
      } catch (org.omg.PortableServer.POAPackage.ServantNotActive e) {
          System.err.println ("PushConsumer.connect: org.omg.PortableServer.POAPackage.ServantNotActive");
          System.err.println (e);
      } catch (RtecEventChannelAdmin.TypeError e) {
          System.err.println ("PushConsumer.connect: RtecEventChannelAdmin.TypeError");
          System.err.println (e);
      } catch (RtecEventChannelAdmin.AlreadyConnected e) {
          System.err.println ("PushConsumer.connect: RtecEventChannelAdmin.AlreadyConnected");
          System.err.println (e);
      }
      System.out.println ("Return PushConsumer.connect");
  }

  public void register_callback( CallBack callbackObj, Object argObj)
  {
      this._callbackObj = callbackObj;
      this._argObj = argObj;
  }

  public void disconnect_push_consumer()
  {
      System.out.println ("PushConsumer: Have to disconnect!");
      disconnect();
  }

  public void disconnect()
  {
      if ( _supplier_proxy == null || _consumer_admin == null )
          return;

      if (this._connectedToProxy){
          _supplier_proxy.disconnect_push_supplier();
          _connectedToProxy = false;
      }

      if ( _supplier_proxy != null )
          _supplier_proxy = null;

      if ( _consumer_admin != null )
          _consumer_admin = null;
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
          System.err.println("System Exception Setting schedule");
          System.err.println(e);
      } catch (RtecScheduler.UNKNOWN_TASK e) {
          System.err.println ("PushConsumer.default_schedule: Unknown task");
          System.err.println (e);
      } catch (RtecScheduler.SYNCHRONIZATION_FAILURE e) {
          System.err.println ("PushConsumer.default_schedule: scheduler synchronization failure");
          System.err.println (e);
      } catch (RtecScheduler.INTERNAL e) {
          System.err.println ("PushConsumer.default_schedule: internal scheduler error");
          System.err.println (e);
      }
  }

}
