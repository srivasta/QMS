package com.stdc.Instrumentation.Clients.HelloWorld;

// TransformCallback.java
//
// ============================================================================
//
// = FILENAME
//    TransformCallback.java
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

import javax.xml.transform.*;
import javax.xml.transform.sax.*;
import javax.xml.transform.dom.*;
import javax.xml.transform.stream.*;

public class TransformCallback implements  com.stdc.Util.CallBack
{
  private TransformerFactory _tfactory = null;
  private String _xslId = null;
  private Transformer _transformer = null;

  public TransformCallback() throws Exception
  {
      _xslId = System.getProperty("stdc.qms.client.transform");
      if ( _xslId == null ) {
          throw new Exception("Name of transform file not specified " + 
                              "(property stdc.qms.client.transform)" );
      }

      // Create a transform factory instance.
      _tfactory = TransformerFactory.newInstance();

      try {
          // Create a transformer for the stylesheet.
          _transformer
            = _tfactory.newTransformer(new StreamSource(_xslId));
      } catch (TransformerConfigurationException ex) {
          System.err.println ("TransformerConfigurationException in TransformCallback");
          ex.printStackTrace();
          throw new Exception (ex.getMessage());
      }
  }

  public synchronized void callback (String data, Object args)
  {
      // Transform the source XML to System.out.
      StreamSource xmlSource = new StreamSource(new StringReader(data));
      try {
          _transformer.transform( xmlSource,
                                  new StreamResult(System.out));
      } catch (TransformerException ex) {
          System.err.println ("TransformerException in callback");
      }
  }
}
