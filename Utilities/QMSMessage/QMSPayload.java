package com.stdc.Util.QMSMessage;

// QMSPayload.java
//
// ============================================================================
//
// = FILENAME
//    QMSPayload.java
//
// = AUTHOR
//    Amit Haldankar (amit.haldankar@stdc.com)
//
// = DESCRIPTION
//   Call back interface for PushConsumer.
//
// ============================================================================


/**
 * @authors Amit Haldankar March 2002
 *
 * This is a marker interface for Payload in QMS Message
 *
 */

public interface QMSPayload
{
    public String getCategory ();
    public void setCategory (String category);
    public String print ();
}
