package com.stdc.Instrumentation.Clients.HelloWorld;

// HelloWorldCallback.java
//
// ============================================================================
//
// = FILENAME
//    HelloWorldCallback.java
//
// = AUTHOR
//    Amit Haldankar (amit.haldankar@stdc.com)
//
// = DESCRIPTION
//   This is the Message handler for HelloWorld messages.
//
// ============================================================================


/**
 * @authors Amit Haldankar April 2002
 *
 * A start for QMS in java
 *
 */

import java.io.StringReader;

import com.stdc.Util.CallBack;
import com.stdc.Util.QMSMessage.QMSMessage;

public class HelloWorldCallback implements CallBack
{
  private HelloWorldMessageParser _parser = null;

  public HelloWorldCallback()
  {
      _parser = new HelloWorldMessageParser();
  }

  public void callback (String data, Object args)
  {
        QMSMessage inMsg = null;

        inMsg = (QMSMessage)_parser.fromXML(new StringReader(data));
        System.out.println (inMsg.print());
  }
}
