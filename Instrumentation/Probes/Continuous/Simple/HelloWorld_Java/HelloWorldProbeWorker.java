package com.stdc.Instrumentation.Probes.HelloWorld;

// HelloWorldProbeWorker.java
//
// ============================================================================
//
// = FILENAME
//    HelloWorldProbeWorker.java
//
// = AUTHOR
//    Amit Haldankar (amit.haldankar@stdc.com)
//
// = DESCRIPTION
//   This is the first qms probe written in java.
//
// ============================================================================


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
import javax.swing.JFrame;

/**
 * @authors Amit Haldankar April 2002
 *
 * A start for QMS in java
 *
 */

public class HelloWorldProbeWorker implements Runnable
{

  HelloWorldProbe _probe = null;
  // Repeat count
  int _count = 1;
  // Repeat Interval in milli seconds
  long _repeatInterval = 1000;
  String _argStr = null;

  private Thread workerThread = null;

  public HelloWorldProbeWorker(HelloWorldProbe probe)
  {
      this(probe, 1, 1000, "");
  }

  public HelloWorldProbeWorker(HelloWorldProbe probe, int repeatCount, long repeatInterval, String arg)
  {
      _probe = probe;
      _count = repeatCount;
      _repeatInterval = repeatInterval;
      _argStr = arg;

      workerThread = new Thread(this);
      workerThread.start();
  }

  public void setRepeatCount(int count) {
      if ( count > 0 )
          _count = count;
  }

  public void setRepeatInterval(long interval) {
      if ( interval > 1000 )
          _repeatInterval = interval;
  }

  public void run ()
  {
      int i = 0;
      int status = -1;
      String msg = null;

      HelloWorldProbeConsole hwConsole = new HelloWorldProbeConsole(_count, _argStr);
      hwConsole.pack();
      hwConsole.setVisible(true);

      while ( i < _count ) {
          status = _probe.getStatus();
          if ( status == HelloWorldProbe.STOP_PROBE ) {
              break;
          } else if ( status == HelloWorldProbe.PAUSE_PROBE ) {
               try { Thread.sleep(_repeatInterval); } catch (InterruptedException e) { }
               continue;
          } else if ( status == HelloWorldProbe.START_PROBE ) {
               i++;
               msg = create_message(i);
               System.out.print(msg);
               System.out.flush();
               hwConsole.setSelected(i);
               try { Thread.sleep(_repeatInterval); } catch (InterruptedException e) { }
               continue;
          } else {
              break;
          }
      }
      System.exit(0);

  }

  public String create_message(int id)
  {
      String payLoad = 
              "<helloWorld xmlns=\"http://www.stdc.com/2001/QMS/helloWorld\"\n" +
              " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n" +
              " xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/helloWorld " + "helloWorld.xsd" + "\">\n" +
              " <Data>\n" +
              "   <dataid>" + id + "</dataid>\n" +
              "   <salutation>Hello " + _argStr + " !!</salutation>\n" +
              " </Data>\n" + 
              "</helloWorld>\n" +
              "<!-- ******_PROBE_MESSAGE_DELIMITER_****** -->";

      return payLoad;
  }

}
