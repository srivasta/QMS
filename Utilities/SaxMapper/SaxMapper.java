package com.stdc.Util.SaxMapper;

import java.io.*;
import java.util.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;


public abstract class SaxMapper extends DefaultHandler {


    //Defaults for Parser properties
    private static boolean setValidation    = false;
    private static boolean setNameSpaces    = true;
    private static boolean setSchemaSupport = true;
    private static boolean setSchemaFullSupport = false;

    public abstract Object getMappedObject();
    public abstract TagTracker createTagTrackerNetwork();


    // A stack for the tag trackers to coordinate on.
    private Stack tagStack = new Stack();

    // The SAX 2 parser...
    private XMLReader xr;

    // Buffer for collecting data from
    // the "characters" SAX event.
    private CharArrayWriter contents = new CharArrayWriter();


    public SaxMapper( ) {

        try {
            // Create the XML reader...
            xr = XMLReaderFactory.createXMLReader();


            if ( System.getProperty("stdc.qms.setValidation") != null)
                setValidation = Boolean.getBoolean("stdc.qms.setValidation");

            if ( System.getProperty("stdc.qms.setNameSpaces") != null)
                setNameSpaces = Boolean.getBoolean("stdc.qms.setNameSpaces");

            if ( System.getProperty("stdc.qms.setSchemaSupport") != null)
                setSchemaSupport = Boolean.getBoolean("stdc.qms.setSchemaSupport");

            if ( System.getProperty("stdc.qms.setSchemaFullSupport") != null)
                setSchemaFullSupport = Boolean.getBoolean("stdc.qms.setSchemaFullSupport");

            xr.setFeature( "http://xml.org/sax/features/validation",
                                               setValidation);

            xr.setFeature( "http://xml.org/sax/features/namespaces",
                                               setNameSpaces );

            xr.setFeature( "http://apache.org/xml/features/validation/schema",
                                               setSchemaSupport );

            xr.setFeature( "http://apache.org/xml/features/validation/schema-full-checking",
                                               setSchemaFullSupport );

        } catch (org.xml.sax.SAXException se) {
            if (se.getException() != null)
                se.getException().printStackTrace(System.err);
            else
                se.printStackTrace(System.err);
        } catch (Exception e) {
            e.printStackTrace(System.err);
        }

        // Create the tag tracker network 
        // and initialize the stack with 
        // it.
        //
        // This constructor anchors the tag
        // tracking network to the begining
        // of the XML document. ( before the
        // first tag name is located ).
        //
        // By placing it first on the stack
        // all future tag tracking will follow
        // the network anchored by this
        // root tag tracker.
        //
        // The createTagTrackerNetwork() method
        // is abstract.  All sub classes are 
        // responsible for reacting to this 
        // request with the creation of a 
        // tag tracking network that will 
        // perform the mapping for the sub class.
        //
        SaxMapperLog.trace( "Creating the tag tracker network." );
        tagStack.push( createTagTrackerNetwork() );
        SaxMapperLog.trace( "Tag tracker network created." );
        
    }    

    public Object fromXML( String url ) {

        try {
            return fromXML( new InputSource( url ) );

        } catch ( Exception e ) {
                     e.printStackTrace();
            return null;    
        }
    }

    public Object fromXML( InputStream in ) {
        try {
            return fromXML( new InputSource( in ) );

        } catch ( Exception e ) {
                     e.printStackTrace();
            return null;    
        }
    }

    public Object fromXML( Reader in ) {
        try {
            return fromXML( new InputSource( in ) );

        } catch ( Exception e ) {
                     e.printStackTrace();
            return null;    
        }
    }

    private synchronized Object fromXML( InputSource in ) throws Exception {

        // notes, 
        // 1.  The calling "fromXML" methods catch 
        //     any parsing exceptions.
        // 2.  The method is synchronized to keep 
        //     multiple threads from accessing the XML parser
        //     at once.  This is a limitation imposed by SAX.


        // Set the ContentHandler...
        xr.setContentHandler( this );

        
        // Parse the file...
        SaxMapperLog.trace( "About to parser XML document." );
                try {
            xr.parse( in );
                } catch (org.xml.sax.SAXParseException se) {
            System.out.println( "XML document parsing failed." );
                    se.printStackTrace();
                    return null;
                }
        SaxMapperLog.trace( "XML document parsing complete." );

            return getMappedObject();
    }


    // Implement the content hander methods that 
    // will delegate SAX events to the tag tracker network.

    public void startElement( String namespaceURI,
                   String localName,
                  String qName,
                  Attributes attr ) throws SAXException {

        // Resetting contents buffer.
        // Assuming that tags either tag content or children, not both.
        // This is usually the case with XML that is representing 
        // data strucutures in a programming language independant way.
        // This assumption is not typically valid where XML is being 
        // used in the classical text mark up style where tagging 
        // is used to style content and several styles may overlap 
        // at once.
        contents.reset();

        // delegate the event handling to the tag tracker
        // network.
        TagTracker activeTracker = (TagTracker) tagStack.peek();
        activeTracker.startElement( namespaceURI, localName, 
                        qName, attr, tagStack );


    }

    public void endElement( String namespaceURI,
                   String localName,
                  String qName ) throws SAXException {

        // delegate the event handling to the tag tracker
        // network.
        TagTracker activeTracker = (TagTracker) tagStack.peek();
        activeTracker.endElement( namespaceURI, localName, 
                      qName, contents, tagStack );

    }


    public void characters( char[] ch, int start, int length )
                        throws SAXException {
        // accumulate the contents into a buffer.
        contents.write( ch, start, length );

    }

}
