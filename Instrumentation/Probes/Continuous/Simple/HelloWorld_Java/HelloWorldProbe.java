package com.stdc.Instrumentation.Probes.HelloWorld;

// HelloWorldProbe.java
//
// ============================================================================
//
// = FILENAME
//    HelloWorldProbe.java
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

import com.stdc.Util.ParseXMLDuration;

/**
 * @authors Amit Haldankar April 2002
 *
 * A start for QMS in java
 *
 */

public class HelloWorldProbe implements Runnable
{

  public static int START_PROBE = 0;
  public static int PAUSE_PROBE = 1;
  public static int STOP_PROBE = 2;

  public static int default_count = 1;
  public static long default_interval = 1000;

  private BufferedReader _consoleIn;
  private Thread _listener;
  private String _args[] = null;
  private String _argStr = null;
  private int _repeatCount = -1;
  private long _repeatInterval = -1;

  private int _status = -1;
  private boolean _startWorker = false;

  public HelloWorldProbe(String args[])
  {
      _args = args;
      int count = -1;
      long interval = -1;
      StringBuffer sb = new StringBuffer();
      for (int i = 0; i < args.length ; i++ ) {
          if ( args[i].equals("-r") ) {
              try {
                  count = Integer.parseInt(args[i+1]);
                  i++;
              } catch ( NumberFormatException ex ) {
                  count = default_count;
                  i++;
              }
          } else if ( args[i].equals("-i") ) {
              try {
                  interval = ParseXMLDuration.getMilliSeconds(args[i+1]);
                  i++;
              } catch ( Exception ex ) {
                  interval = default_interval;
                  i++;
              }
          } else {
              sb.append( args[i].trim() + " " );
          }
      }

      _argStr = sb.toString().trim();

      if ( count > 0 )
          _repeatCount = count;
      else
          _repeatCount = default_count;

      if ( interval > 0 )
          _repeatInterval = interval;
      else
          _repeatInterval = default_interval;

      _consoleIn = new BufferedReader(new InputStreamReader(System.in));
      Thread _listener = new Thread (this);
      _listener.start();
  }

  public int getStatus () {
      return _status;
  }

  public void setStatus (int status) {
      if ( status == START_PROBE ||
           status == STOP_PROBE  ||
           status == PAUSE_PROBE    )
          _status = status;
  }

  public void run () {
      boolean allOK = true;
      String line;

      while(allOK) {
          try {
              line = getCommandLine();
              setFlags(line, _args);
              if ( _status == STOP_PROBE )  {
                  allOK = false;
              }
          }
          catch (IOException e) {
            e.printStackTrace();
            allOK = false;
          }
      }
      return;
  }

  private String getCommandLine() throws IOException {
    String commandLine = "";
    while (true) {
       commandLine = _consoleIn.readLine();
       if (commandLine != null && commandLine.length() !=0 )
            break;
    }
    return commandLine;
  }

  private synchronized void setFlags(String commandLine, String args[]) {
      if ( commandLine.indexOf("pause") != -1 ) {
          _status = HelloWorldProbe.PAUSE_PROBE;
      } else if ( commandLine.indexOf("start") != -1 ) {
          _status = HelloWorldProbe.START_PROBE;
          if ( !_startWorker ) {
              new HelloWorldProbeWorker ( this, _repeatCount, _repeatInterval, _argStr );
              _startWorker = true;
          }
      } else if ( commandLine.indexOf("stop") != -1 ) {
          _status = HelloWorldProbe.STOP_PROBE;
      } else if ( commandLine.indexOf("resume") != -1 ) {
          _status = HelloWorldProbe.START_PROBE;
      }
  }

  static public void main  (String args[])
  {
      HelloWorldProbe hwProbe = new HelloWorldProbe(args);  
  }
}
