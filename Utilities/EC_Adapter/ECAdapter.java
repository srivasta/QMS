package com.stdc.Util;

import java.util.Vector;

// ECAdapter.java
//
// ============================================================================
//
//
// = FILENAME
//    ECAdapter.java
//
// = AUTHOR
//    Amit Haldankar (amit.haldankar@stdc.com)
//
// = DESCRIPTION
//
//
// ============================================================================


public class ECAdapter 
{
  private static final int DEFAULT_ID = 7000;
  private static final int DEFAULT_SEND_TYPE = 9000;
  private static final int DEFAULT_GET_TYPE = 8100;

  private String[] _args = null;
  private int _myId = -1;
  private int _sendEventType = -1;
  private int _getEventType = -1;
  private String _eventChannelName = null;
  private CORBA_Handles _handles = null;

  private boolean _simpleMode;
  private Vector _consumers = null;
  private Vector _suppliers = null;

  public ECAdapter ()
  {
  }

  public void init (String[] args)
  {
      this._args = args;
      this._simpleMode = false;

      this._handles  = new CORBA_Handles();
      this._handles.init(args, "QMS_API");
  }

  public void init (String[] args,
                    int mySupplierId,
                    int sendEvent,
                    int getEvent,
                    String eventChannelName,
                    CORBA_Handles CORBAHandles)
  {
      this._args = args;
      this._simpleMode = true;

      if (mySupplierId <= 0) { this._myId = ECAdapter.DEFAULT_ID; }
      else                   { this._myId = mySupplierId;         }
 
      if (sendEvent <= 0) { this._sendEventType = ECAdapter.DEFAULT_SEND_TYPE; }
      else                { this._sendEventType = sendEvent;                    }
    
      if (getEvent <= 0) {  this._getEventType  = ECAdapter.DEFAULT_GET_TYPE; }
      else               {  this._getEventType  = getEvent;                    }
  
      if (CORBAHandles != null) {  this._handles  = CORBAHandles;        }
      else                      {  this._handles  = new CORBA_Handles(); }
  
      this._handles.init(args, "QMS_API");
      this._handles.activate_poa_manager();

      add_supplier(eventChannelName, this._myId, this._sendEventType);

      add_consumer(eventChannelName, this._getEventType);
  }

  public int send (String data, int whichSupplier)
  {
      return ((PushSupplier)this._suppliers.get(whichSupplier)).send(data);
  }

  public int register_callback (CallBack callbackObj, Object argObject, int whichConsumer)
  {
      ((PushConsumer)this._consumers.get(whichConsumer)).register_callback (callbackObj, argObject);
      return  0;
  }

  public int add_supplier ()
  {
      _suppliers.add( new PushSupplier() );
      return (_suppliers.size() - 1);
  }

  public int add_supplier (String eventChannelName,
                           int myId,
                           int sendEvent)
  {
      _suppliers.add( new PushSupplier(_handles, sendEvent, myId, eventChannelName) );
      return (_suppliers.size() - 1);
  }

  public int add_consumer ()
  {
      _consumers.add( new PushConsumer() );
      return (_consumers.size() - 1);
  }

  public int add_consumer (String eventChannelName,
                           int getEvent)
  {
      _consumers.add( new PushConsumer(_handles, getEvent, eventChannelName) );
      return (_consumers.size() - 1);
  }

  public void disconnect ()
  {
      // Disconnect consumer first, since that involves sending a
      // disconnect event
      this.disconnect_consumer(0);
      this.disconnect_supplier(0);

      {
        this._handles.disconnect();
      }

  }

  public int disconnect_supplier(int whichSupplier)
  {
      PushSupplier supplier = (PushSupplier)this._suppliers.get(whichSupplier);
      supplier.disconnect();
      return 0;
  }

  public int disconnect_consumer(int whichConsumer)
  {
      PushConsumer consumer = (PushConsumer)this._consumers.get(whichConsumer);
      consumer.disconnect();
      return 0;
  }

  public int connect_supplier(int whichSupplier)
  {
      PushSupplier supplier = (PushSupplier)this._suppliers.get(whichSupplier);
      supplier.connect();
      return 0;
  }

  public int connect_consumer(int whichConsumer)
  {
      PushConsumer consumer = (PushConsumer)this._consumers.get(whichConsumer);
      consumer.connect();
      return 0;
  }

  public int listen()
  {
      this._handles.run();
      return 0;
  }

  public PushConsumer get_consumer(int whichConsumer)
  {
      return (PushConsumer)this._consumers.get(whichConsumer);
  }

  public PushSupplier get_supplier(int whichSupplier)
  {
      return (PushSupplier)this._suppliers.get(whichSupplier);
  }

  public Vector get_consumer_list()
  {
      return this._consumers;
  }

  public Vector get_supplier_list()
  {
      return this._suppliers;
  }

  public CORBA_Handles get_handles()
  {
      return this._handles;
  }

}
