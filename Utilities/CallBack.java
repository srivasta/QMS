package com.stdc.Util;

// CallBack.java
//
// ============================================================================
//
// = FILENAME
//    CallBack.java
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
 * A start for QMS in java
 *
 */

public interface CallBack
{
    public void callback (String data, Object args);
}
