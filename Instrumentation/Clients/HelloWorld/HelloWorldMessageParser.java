package com.stdc.Instrumentation.Clients.HelloWorld;

import org.xml.sax.*;
import java.util.*;
import java.io.*;

import com.stdc.Util.SaxMapper.*;
import com.stdc.Util.QMSMessage.*;

public class HelloWorldMessageParser extends SaxMapper {

    private QMSMessage _target;
    private QMSMessageSender _qmsMsgSender;
    private QMSUniqueName _qmsUniqueName;
    private QMSSession _qmsSession;
    private QMSPayload _msgPayload;


    public Object getMappedObject() {

        return (Object)_target;
    }


    public TagTracker createTagTrackerNetwork() {

//        SaxMapperLog.trace( "creating tag track network" );

        // -- create root: /
        TagTracker root = new TagTracker() {
            public void onDeactivate() {
                // The root will be deactivated when parsing a new document begins.

                _target = new QMSMessage();
            }
        };

        // -- create action for /QMSMessage/msgSequenceNo
        TagTracker msgSequenceNo = new TagTracker(){
            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found :[/QMSMessage/msgSequenceNo]" );
                _target.setMsgSequenceNo (contents.toString());
            }
        };
        root.track( "/QMSMessage/msgSequenceNo", msgSequenceNo );

        // -- create action for /QMSMessage/msgDate
        TagTracker msgDate = new TagTracker(){
            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found :[/QMSMessage/msgDate]" );
                _target.setMsgDate (contents.toString());
            }
        };
        root.track( "/QMSMessage/msgDate", msgDate );

        // -- create action for /QMSMessage/msgTime
        TagTracker msgTime = new TagTracker(){
            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found :[/QMSMessage/msgTime]" );
                _target.setMsgTime (contents.toString());
            }
        };
        root.track( "/QMSMessage/msgTime", msgTime );

        // -- create action for /QMSMessage/originatingHost
        TagTracker originatingHost = new TagTracker(){
            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found :[/QMSMessage/originatingHost]" );
                _target.setOriginatingHost (contents.toString());
            }
        };
        root.track( "/QMSMessage/originatingHost", originatingHost );

        // -- create action for /QMSMessage/msgSender
        TagTracker msgSender = new TagTracker(){
            public void onStart( String namespaceURI, String localName,
                                 String qName, Attributes attr ) {
                SaxMapperLog.trace( "Found Start :[/QMSMessage/msgSender]" );
                _qmsMsgSender = new QMSMessageSender();
            }

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/msgSender]" );
                _target.setMessageSender(_qmsMsgSender);
            }
        };
        root.track( "/QMSMessage/msgSender", msgSender );

        // -- create action for /QMSMessage/msgSender/id
        TagTracker msgSenderId = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/msgSender/id]" );
                _qmsMsgSender.setId(contents.toString());
            }
        };
        root.track( "/QMSMessage/msgSender/id",  msgSenderId );

        // -- create action for /QMSMessage/msgSender/description
        TagTracker msgSenderDesc = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/msgSender/description]" );
                _qmsMsgSender.setDescription(contents.toString());
            }
        };
        root.track( "/QMSMessage/msgSender/description",  msgSenderDesc );

        // -- create action for /QMSMessage/QMSUniqueName
        TagTracker RSUniqueName = new TagTracker(){
            public void onStart( String namespaceURI, String localName,
                                 String qName, Attributes attr ) {
                SaxMapperLog.trace( "Found Start :[/QMSMessage/QMSUniqueName]" );
                _qmsUniqueName = new QMSUniqueName();
            }

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/QMSUniqueName]" );
                _target.setQMSUniqueName(_qmsUniqueName);
            }
        };
        root.track( "/QMSMessage/QMSUniqueName", RSUniqueName );

        // -- create action for /QMSMessage/QMSUniqueName/category
        TagTracker RScategory = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/QMSUniqueName/category]" );
                _qmsUniqueName.setCategory(contents.toString());
            }
        };
        root.track( "/QMSMessage/QMSUniqueName/category", RScategory );

        // -- create action for /QMSMessage/QMSUniqueName/host
        TagTracker RShost = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/QMSUniqueName/host" );
                _qmsUniqueName.setHost(contents.toString());
            }
        };
        root.track( "/QMSMessage/QMSUniqueName/host", RShost );

        // -- create action for /QMSMessage/QMSUniqueName/uuid
        TagTracker RSuuid = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/QMSUniqueName/uuid]" );
                _qmsUniqueName.setUuid(contents.toString());
            }
        };
        root.track( "/QMSMessage/QMSUniqueName/uuid", RSuuid );

        // -- create action for /QMSMessage/Session
        TagTracker session = new TagTracker(){
            public void onStart( String namespaceURI, String localName,
                                 String qName, Attributes attr ) {
                SaxMapperLog.trace( "Found Start :[/QMSMessage/Session]" );
                _qmsSession = new QMSSession();
            }

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/Session]" );
                _target.setQMSSession(_qmsSession);
            }
        };
        root.track( "/QMSMessage/Session", session );

        // -- create action for /QMSMessage/Session/requestID
        TagTracker RSRequestId = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/Session/requestID]" );
                _qmsSession.setRequestId(contents.toString());
            }
        };
        root.track( "/QMSMessage/Session/requestID", RSRequestId );

        // -- create action for /QMSMessage/Session/version
        TagTracker RSVersion = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/Session/version]" );
                _qmsSession.setVersion(contents.toString());
            }
        };
        root.track( "/QMSMessage/Session/version", RSVersion );

        // -- create action for /QMSMessage/Session/dataID
//        TagTracker RSDataId = new TagTracker(){
//
//            public void onEnd(   String namespaceURI, String localName,
//                          String qName, CharArrayWriter contents ){
//                SaxMapperLog.trace( "Found End :[/QMSMessage/Session/dataID]" );
//                resourceResp.setDataId(contents.toString());
//            }
//        };
//        root.track( "/QMSMessage/Session/dataID", RSDataId );

        // -- create action for /QMSMessage/Session/minRepetitions/count
        TagTracker RSMaxCount = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/Session/minRepetitions/count]" );
                _qmsSession.setRepeatCount(contents.toString());
            }
        };
        root.track( "/QMSMessage/Session/minRepetitions/count", RSMaxCount );

        // -- create action for /QMSMessage/Session/minRepetitions/current
        TagTracker RSCurrentCount = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/Session/minRepetitions/current]" );
                _qmsSession.setCurrentCount(contents.toString());
            }
        };
        root.track( "/QMSMessage/Session/minRepetitions/current", RSCurrentCount );

        // -- create action for /QMSMessage/Session/minRepeatInterval
        TagTracker RSMinRepeatInterval = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/Session/minRepeatInterval]" );
                _qmsSession.setRepeatInterval(contents.toString());
            }
        };
        root.track( "/QMSMessage/Session/minRepeatInterval", RSMinRepeatInterval );


//Parsing of HelloWorld PayLoad

        // -- create action for /QMSMessage/payload/helloWorld
        TagTracker hwPayLoad = new TagTracker(){
            public void onStart( String namespaceURI, String localName,
                                 String qName, Attributes attr ) {
                SaxMapperLog.trace( "Found Start :[/QMSMessage/payload/helloWorld]" );
                _msgPayload = new HelloWorldMsgPayload();
            }

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/payload/helloWorld]" );
                _target.setPayload(_msgPayload);
            }
        };
        root.track( "/QMSMessage/payload/helloWorld", hwPayLoad );

        // -- create action for /QMSMessage/payload/helloWorld/Data/dataid
        TagTracker hwDataId = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/payload/helloWorld/Data/dataid]" );
                ((HelloWorldMsgPayload)_msgPayload).setDataId(contents.toString().trim());
            }
        };
        root.track( "/QMSMessage/payload/helloWorld/Data/dataid", hwDataId );

        // -- create action for /QMSMessage/payload/helloWorld/Data/salutation
        TagTracker hwSalutation = new TagTracker(){

            public void onEnd(   String namespaceURI, String localName,
                          String qName, CharArrayWriter contents ){
                SaxMapperLog.trace( "Found End :[/QMSMessage/payload/helloWorld/Data/salutation]" );
                ((HelloWorldMsgPayload)_msgPayload).setSalutation(contents.toString().trim());
            }
        };
        root.track( "/QMSMessage/payload/helloWorld/Data/salutation", hwSalutation );


        return root;
    }


    public static void main( String[] argv ){

        try {

            System.out.println( "HelloWorldMessageParser:");

            HelloWorldMessageParser inp = new HelloWorldMessageParser();
            QMSMessage to  = (QMSMessage) inp.fromXML(argv[0]);

            System.out.print(to.print());

        } catch ( Exception e ) {
                     e.printStackTrace();
        }
    }

}
