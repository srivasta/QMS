package com.stdc.Instrumentation.Clients.HelloWorld;

// HelloWorldClient.java
//
// ============================================================================
//
// = FILENAME
//    HelloWorldClient.java
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

import java.util.Calendar;

import com.stdc.Util.Client;
import com.stdc.Util.ClientDriver;
import com.stdc.Util.PushSupplier;

public class HelloWorldClient implements ClientDriver
{

  // The push consumer for reading the data
  private PushSupplier _supplier;

  private Client _client;

  private String _interval;
  private int _repeatitions;

  public HelloWorldClient()
  {
     _client = null;
     _supplier = null;
  }

  public HelloWorldClient(Client client)
  {
      init (client);
  }
 
  public void init (Client client)
  {
      _client = client;
      _supplier = _client.get_supplier();

      try { 
         String count = System.getProperty("stdc.qms.client.repeatitions");
         if ( count != null )
             _repeatitions = Integer.parseInt(count);
      } catch ( Exception ex ) {
          _repeatitions = 1;
      }
      _interval = System.getProperty("stdc.qms.client.interval");
  }

  public void run ()
  {

      try {
          Thread.sleep(10);
          System.out.println("Sending Messages\n");

          _supplier.send(create_message(0,null));
          System.out.println("**************Start Message sent**************");
          Thread.sleep(20000);

          _supplier.send(create_message(1,"pause"));
          System.out.println("**************Pause Message sent**************");
          Thread.sleep(5000);

          _supplier.send(create_message(2,"restart"));
          System.out.println("**************restart Message sent**************");
          Thread.sleep(5000);

          _supplier.send(create_message(3,"resume"));
          System.out.println("**************Resume Message sent**************");
          Thread.sleep(40000);

          _supplier.send(create_message(4,"kill"));
          System.out.println("**************Kill Message sent**************");
          Thread.sleep(10000);

          _supplier.send(create_message(5,"stop"));
          System.out.println("**************Stop Message sent**************");
          Thread.sleep(1000);

      } catch (InterruptedException e) {
          System.out.println("Client exiting");
      } finally {
          _client.cleanup();
      }
  }

  public String create_message(long version, String action)
  {
      long sequence_no = 1000;
      long request_id = 1;

      Calendar rightNow = Calendar.getInstance();
      String currentDate = rightNow.get(Calendar.YEAR) + "-" + 
                           rightNow.get(Calendar.MONTH) + "-" + 
                           rightNow.get(Calendar.DAY_OF_MONTH);

      String currentTime = rightNow.get(Calendar.HOUR_OF_DAY) + ":" + 
                           rightNow.get(Calendar.MINUTE) + ":" + 
                           rightNow.get(Calendar.SECOND);

      String payLoad = null;
      if ( action == null ) {
          payLoad = 
              "<helloWorld xmlns=\"http://www.stdc.com/2001/QMS/helloWorld\"\n" +
              " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n" +
              " xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/helloWorld " + _client.get_probe_schema_uri() + "\">\n" +
              " <Request>\n" +
              "   <firstname>John</firstname>\n" +
              "   <lastname>Doe</lastname>\n" +
              " </Request>\n" + 
              "</helloWorld>\n";
      } else {
          payLoad = 
              "<helloWorld xmlns=\"http://www.stdc.com/2001/QMS/helloWorld\"\n" +
              " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n" +
              " xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/helloWorld " + _client.get_probe_schema_uri() + "\">\n" +
              " <Request>\n" +
              "   <action>" + action + "</action>\n" +
              " </Request>\n" + 
              "</helloWorld>\n";
      }

      // Format string for the request
      String mesgBuf  = 
              "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
              "<qms:QMSMessage xmlns=\"http://www.stdc.com/2001/QMSSchema\"\n" +
              "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n" +
              "xmlns:qms=\"http://www.stdc.com/2001/QMSSchema\"\n" +
              "xsi:schemaLocation=\"http://www.stdc.com/2001/QMSSchema " + _client.get_qms_schema_uri() + "\">\n" +
              "<qms:msgSequenceNo>" + sequence_no + "</qms:msgSequenceNo>\n" +
              "<qms:msgDate>" + currentDate + "</qms:msgDate>\n" +
              "<qms:msgTime>" + currentTime + "-0:00</qms:msgTime>\n" +
              "<qms:originatingHost>" + _client.get_host_address() + "</qms:originatingHost>\n" +
              "<qms:msgSender>\n" +
              "  <id>" + _client.get_supplier_id() + "</id>\n" +
              "  <description>Test client for a QMS Probe</description>\n" +
              "</qms:msgSender>\n" +
              "<qms:QMSUniqueName>\n" +
              "  <category>" + _client.get_category_name() + "</category>\n" +
              "</qms:QMSUniqueName>\n" +
              "<qms:Session>\n" +
              "  <requestID>" + request_id + "</requestID>\n" +
              "  <version>" + version + "</version>\n" +
              "  <minRepetitions>\n" +
              "   <count>" + _repeatitions + "</count>\n" +
              "  </minRepetitions>\n" +
              "  <minRepeatInterval>" + _interval + "</minRepeatInterval>\n" +
              "</qms:Session>\n" +
              "<qms:payload>\n" +
                payLoad +
              "</qms:payload>\n" +
              "</qms:QMSMessage>\n";

      return mesgBuf;
  }

}
