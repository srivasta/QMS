package com.stdc.Util;

// Client.java
//
// ============================================================================
//
// = FILENAME
//    Client.java
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
 *
 */

import java.util.*;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileInputStream;

import org.omg.CORBA.Any;
import org.omg.CosNaming.*;
import org.omg.CosTrading.*;
import org.omg.CosTrading.LookupPackage.*;
import org.omg.CosTradingRepos.*;
import org.omg.CosTradingRepos.ServiceTypeRepositoryPackage.*;
import RtecEventData;
import RtecEventDataHelper;
import RtecEventDataHolder;

import STDC.QMS.Citizen.*;

public class Client implements CallBack
{

  private String _identityString = "QMS Probe test client";

  private CORBA_Handles _CORBAHandles = null;

  // The QMS unique name category for the probe we are testing
  private String _categoryName = null;

  // The host IP of the machine we are running on
  private String _hostAddress = null;

  private QMS_Trader_ECInfo _ecRegistry = null;

  // The EC supplier ID in order to be able to send events
  private int _supplierId = -1;

  // The URI of the probe schema used in requests
  private String _probe_schema_uri = null;

  // The URI of the schema file used in QMS Messages
  private String _qms_schema_uri = null;

  // The event channel used to send requests on
  private String _request_channel = null;

  // The event type for the requests we send out
  private int _request_event_type;

  // The event channel used by the sensor to reply with data
  private String _data_channel = null;

  // The event type for the data reply
  private int _data_event_type;

  // The push consumer for reading the data
  private PushConsumer _consumer = new PushConsumer();

  // The push supplier for sending requests
  private PushSupplier _supplier = new PushSupplier();

  // Callback object which will be passed to register_callback.
  private CallBack _callbackObj = null;



  public Client(CORBA_Handles handles, String category)
  {
      this(handles, category, null);
  }
 
  public Client(CORBA_Handles handles, String category, CallBack msgHandler)
  {
      this._categoryName = category;
      this._CORBAHandles = handles;
      this._callbackObj = msgHandler;

      try {
          java.net.InetAddress addr = java.net.InetAddress.getLocalHost();
          _hostAddress = addr.getHostAddress();
      } catch (java.net.UnknownHostException e) {
          System.err.println ("UnknownHostException");
          System.err.println (e);
      }
  }
 
  public void init ()
  {
      get_supplier_id();

      get_offers();

  }

  public String get_probe_schema_uri ()
  {
      return _probe_schema_uri;
  }

  public String get_qms_schema_uri ()
  {
      return _qms_schema_uri;
  }

  public String get_host_address ()
  {
      return _hostAddress;
  }

  public String get_category_name ()
  {
      return _categoryName;
  }

  public PushConsumer get_consumer ()
  {
      return _consumer;
  }

  public PushSupplier get_supplier ()
  {
      return _supplier;
  }

  public void run ()
  {
      _CORBAHandles.run();

      System.out.println ("Client Done");
  }

  public int get_supplier_id ()
  {
//      System.out.println("In get_supplier_id ()");
      if ( _ecRegistry == null ) {
          get_ec_registry ();
      }

      if ( _supplierId == -1 ) {
          String identity = "Client Looking for " + _categoryName + ":" + _hostAddress;
          System.out.println("Identity String " + identity);

          _supplierId = _ecRegistry.getSupplierID(identity);

          System.out.println("Supplier Id = " + _supplierId);
      }
      return _supplierId;
  }

  private void get_ec_registry ()
  {
//      System.out.println("In get_ec_registry ()");
      if ( _ecRegistry != null ) {
          return;
      }
      try
      {
          org.omg.CORBA.ORB orbHandle = _CORBAHandles.get_orb_handle();
          Lookup lookupHandle = _CORBAHandles.get_lookup_handle();
          Policy[] policies = new Policy[3];
          policies[0] = new Policy();
          policies[0].name = "exact_type_match";
          policies[0].value = orbHandle.create_any();
          policies[0].value.insert_boolean(false);
          policies[1] = new Policy();
          policies[1].name = "use_dynamic_properties";
          policies[1].value = orbHandle.create_any();
          policies[1].value.insert_boolean(false);
          policies[2] = new Policy();
          policies[2].name = "use_proxy_offers";
          policies[2].value = orbHandle.create_any();
          policies[2].value.insert_boolean(false);
   
          SpecifiedProps desiredProps = new SpecifiedProps();
          desiredProps.all_dummy((short)0);
   
          OfferSeqHolder offers = new OfferSeqHolder();
          OfferIteratorHolder iterator = new OfferIteratorHolder();
          PolicyNameSeqHolder policies_applied = new PolicyNameSeqHolder();
   
   
          lookupHandle.query("STDC_QMS_CITIZEN_QMS_TRADER",            // IN string
                             "QMS_UNIQ_NAME_CATEGORY == 'QMS_TRADER' ",// IN contraint
                             "",                                       // IN preferences
                             policies,                                 // IN policies
                             desiredProps,                             // IN desired properties
                             1,                                        // IN how many
                             offers,                                   // OUT Offers
                             iterator,                                 // OUT Iterator
                             policies_applied                          // OUT policies applied
                            );
   
          if ( offers.value.length == 0 ) {
              System.out.println("No Trader Offers found");
          } else {
              _ecRegistry = QMS_Trader_ECInfoHelper.narrow(offers.value[0].reference);
              if ( _ecRegistry == null )
                  System.out.println("Service provider is not an ec registry");
              else
                  System.out.println("Got EC Registry");
          }
          if ( iterator.value != null )
              iterator.value.destroy();
      } catch (Exception e) {
          e.printStackTrace();
          System.exit(1);
      }
  }

  private void get_offers ()
  {
      try
      {
          org.omg.CORBA.ORB orbHandle = _CORBAHandles.get_orb_handle();;

          Lookup lookupHandle = _CORBAHandles.get_lookup_handle();

          Policy[] policies = new Policy[3];
          policies[0] = new Policy();
          policies[0].name = "exact_type_match";
          policies[0].value = orbHandle.create_any();
          policies[0].value.insert_boolean(false);
          policies[1] = new Policy();
          policies[1].name = "use_dynamic_properties";
          policies[1].value = orbHandle.create_any();
          policies[1].value.insert_boolean(false);
          policies[2] = new Policy();
          policies[2].name = "use_proxy_offers";
          policies[2].value = orbHandle.create_any();
          policies[2].value.insert_boolean(false);
   
          SpecifiedProps desiredProps = new SpecifiedProps();
          desiredProps.all_dummy((short)0);
   
          OfferSeqHolder offers = new OfferSeqHolder();
          OfferIteratorHolder iterator = new OfferIteratorHolder();
          PolicyNameSeqHolder policies_applied = new PolicyNameSeqHolder();
   
          String constraint = "QMS_UNIQ_NAME_CATEGORY == '" + _categoryName + "' "; 

          lookupHandle.query("STDC_QMS_CITIZEN_YPOFFER",               // IN string
                             constraint,                               // IN constraint
                             "",                                       // IN preferences
                             policies,                                 // IN policies
                             desiredProps,                             // IN desired properties
                             1,                                        // IN how many
                             offers,                                   // OUT Offers
                             iterator,                                 // OUT Iterator
                             policies_applied                          // OUT policies applied
                            );
   
          if ( offers.value.length == 0 ) {
              System.out.println("No Sensor Offers found");
          } else {
//               System.out.println("  Reference:");
//               String ref = orbHandle.object_to_string(offers.value[0].reference);
//               System.out.println("    " + ref);

              handle_offers(offers.value, iterator.value);
          }
          if ( iterator.value != null )
              iterator.value.destroy();
      } catch (Exception e) {
          e.printStackTrace();
          System.exit(1);
      }
  }

  private void handle_offers (Offer[] offers, OfferIterator iter)
  {
      choose_offer(offers, iter);
      connect_EC();
  }

  private void choose_offer (Offer[] offers, OfferIterator iter)
  {
      int offersCount = offers.length;
      STDC.QMS.Citizen.Command sensor = null;
      try
      {
          for ( int i=0; i < offersCount; i++ ) {
              sensor = 
                  STDC.QMS.Citizen.CommandHelper.narrow(offers[i].reference);
              if ( sensor == null ) {
                  System.out.println("The reference is not a QMS Citizen For offer in sequence " + i);
                  continue;
              }
              org.omg.CORBA.ShortHolder acknowledgement = new org.omg.CORBA.ShortHolder();
              sensor.ping(acknowledgement);
              if ( acknowledgement.value == 0 )
                  continue;
              handle_selected_properties(offers[i].properties);
              System.out.println("Successfully pinged the Sensor");
              return;
          }
          if (iter != null) {
              int iterOfferCount = 0;
              int count = 0;
              OfferSeqHolder seq = new OfferSeqHolder();
              boolean more;
              do {
                  more = iter.next_n(10, seq);
                  iterOfferCount = seq.value.length;
                  count += seq.value.length;
                  System.out.println("Received " + count + " offers in iterator...");
                  for ( int i=0; i < iterOfferCount; i++ ) {
                      sensor = 
                          STDC.QMS.Citizen.CommandHelper.narrow(seq.value[i].reference);
                      if ( sensor == null ) {
                          System.out.println("The reference is not a QMS Citizen " + 
                                             "For offer in iterator " + i+count);
                          continue;
                      }
                      org.omg.CORBA.ShortHolder acknowledgement = new org.omg.CORBA.ShortHolder();
                      sensor.ping(acknowledgement);
                      if ( acknowledgement.value == 0 )
                          continue;
                      handle_selected_properties(seq.value[i].properties);
                      System.out.println("Successfully pinged the Sensor");
                      return;
                  }
              }
              while (more);
   
          } else {
              System.out.println("Iterator is null");
          }
      } catch ( STDC.QMS.Citizen.QMS_Citizen_Error e) {
          System.out.println( "handle_offers: STDC.QMS.Citizen.QMS_Citizen_Error" );
          System.exit(1);
      }

  }

  private void handle_selected_properties (Property[] properties)
  {
      HashMap prop = new HashMap(5);
      java.io.StringWriter sw = null;
      java.io.PrintWriter pw = null;
      for (int p = 0; p < properties.length; p++) {
          sw = new java.io.StringWriter();
          pw = new java.io.PrintWriter(sw);
          org.jacorb.trading.client.util.AnyUtil.print(_CORBAHandles.get_orb_handle(), pw, properties[p].value);
          pw.flush();
          String propStr = sw.toString();
          prop.put(properties[p].name, propStr.substring(1,propStr.length()-1) );
      }
      this._probe_schema_uri = (String)prop.get("PROBE_SCHEMA_URI");
      System.out.println ( "Property: PROBE_SCHEMA_URI = " + this._probe_schema_uri );

      this._qms_schema_uri = (String)prop.get("QMS_SCHEMA_URI");
      System.out.println ( "Property: QMS_SCHEMA_URI = " + this._qms_schema_uri );

      String requestProp = (String)prop.get("Request_0");
      this._request_channel = extract_EC_name(requestProp);
      this._request_event_type = extract_EC_id(requestProp);
      System.out.println ( "Property: Request Channel Name = " + this._request_channel ); 
      System.out.println ( "Property: Request Event Type = "  + this._request_event_type );

      String dataProp = (String)prop.get("Data_0");
      this._data_channel = extract_EC_name(dataProp);
      this._data_event_type = extract_EC_id(dataProp);
      System.out.println ( "Property: Data Channel Name = " + this._data_channel ); 
      System.out.println ( "Property: Data Event Type = "  + this._data_event_type );
      
  }

  private String extract_EC_name (String data)
  {
      String name = null;
      int location = 0;
      int start = 0;
      int stop = 0;
      String nameStrStart = "<Event_Channel_Name>";
      String nameStrEnd = "</Event_Channel_Name>";

      location = data.indexOf(nameStrStart);
      if ( location != -1 ) {
          location += nameStrStart.length();
          start = location;
          location = data.indexOf(nameStrEnd, location);
          if ( location != -1 ) {
              stop = location;
              name = data.substring(start,stop);
          } else {
              System.err.print("End of string encountered while finding EventChannel Name.");
          }
      } else {
          System.err.print("End of string encountered while finding EventChannel Name.");
      }
      return name;
  }

  private int extract_EC_id (String data)
  {
      int type = -1;
      int location = 0;
      int start = 0;
      int stop = 0;
      String typeStrStart = "<Event_Type>";
      String typeStrEnd = "</Event_Type>";

      location = data.indexOf(typeStrStart);
      if ( location != -1 ) {
          location += typeStrStart.length();
          start = location;
          location = data.indexOf(typeStrEnd, location);
          if ( location != -1 ) {
              stop = location;
              type = Integer.parseInt(data.substring(start,stop));
          } else {
              System.err.print("End of string encountered while finding EventChannel Name.");
          }
      } else {
          System.err.print("End of string encountered while finding EventChannel Name.");
      }
      return type;
  }

  private void connect_EC ()
  {
      _supplier.init(_CORBAHandles, _request_event_type, _supplierId, _request_channel);
      _consumer.init(_CORBAHandles, _data_event_type, _data_channel);

      if ( _callbackObj != null ) {
          _consumer.register_callback(_callbackObj,    // Callback object
                                      _callbackObj);   // Arguments Object
      } else {
          _consumer.register_callback(this,    // Callback object
                                      null);   // Arguments Object
      }

      _supplier.connect();

      _consumer.connect();
  }

  public void cleanup ()
  {
      _consumer.disconnect();

      _supplier.disconnect();

      // DO Parser cleanup here.

      _CORBAHandles.get_orb_handle().shutdown(true);
  }

  public void callback (String data, Object args)
  {
      // For now just print the received String.
      System.out.println (data);
  }

  public static void get_properties() throws Exception {
      String propFilePath = null;

      String configDir = System.getProperty("stdc.qms.configdir");
      String propFileName = System.getProperty("stdc.qms.propertyFile");

      if ( propFileName == null ) {
          System.err.println ("Property stdc.qms.propertyFile not specified");
          throw new Exception ( "Property stdc.qms.propertyFile not specified" );
      }

      if ( configDir != null ) {
          propFilePath = configDir + "/" + propFileName;
      } else {
          propFilePath = propFileName;
      }

      FileInputStream propFile = new FileInputStream(propFilePath);
      Properties p = new Properties(System.getProperties());
      p.load(propFile);

      // set the system properties
      System.setProperties(p);
  }

  static public void main  (String args[])
  {
     
       // Load the properties from properties file.
       try {
           get_properties();
       } catch (FileNotFoundException ex) {
           System.err.println ("Error in loading client properties.");
           System.out.println(ex.getMessage());
       } catch (IOException ex) {
           System.err.println ("Error in loading client properties.");
           System.out.println(ex.getMessage());
       } catch (Exception ex) {
           System.err.println ("Error in loading client properties.");
       }

       //Parse Command line arguments here.

       String category = System.getProperty("stdc.qms.probe.category");
       if ( category == null ) {
           System.err.println ("Error: No Category specified");
           System.exit(1);
       }

       String messageHandler = System.getProperty("stdc.qms.client.callback");
       CallBack callbackObj = null;
       if ( messageHandler != null ) {
           try {
               callbackObj = (CallBack)Class.forName(messageHandler).newInstance();
           } catch ( ClassNotFoundException e) {
               System.err.println("Class not fount exception " + messageHandler );
           } catch (Exception e) {
               System.err.println("Exception while creating instance of " + messageHandler );
           }
       }

       String clientDriver = System.getProperty("stdc.qms.client.driver");
       ClientDriver driverObj = null;
       if ( clientDriver != null ) {
           try {
               driverObj = (ClientDriver)Class.forName(clientDriver).newInstance();
           } catch ( ClassNotFoundException e) {
               System.err.println("Class not fount exception " + clientDriver );
           } catch (Exception e) {
               System.err.println("Exception while creating instance of " + clientDriver );
               System.err.println(e.getMessage());
               e.printStackTrace();
           } finally {
               if ( driverObj == null ) {
                   System.exit(1);
               }
           }
       } else {
           System.err.println("Client Driver class not specified");
           System.exit(1);
       }

       CORBA_Handles handles = new CORBA_Handles();
       handles.init ( args, "QMS_Client");
       handles.activate_poa_manager();

       Client client = new Client(handles, category, callbackObj);

       client.init();

       driverObj.init(client);
       Thread driverThread = new Thread( driverObj );

       driverThread.start();

       client.run();
  }
}
