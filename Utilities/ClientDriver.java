package com.stdc.Util;

// ClientDriver.java
//
// ============================================================================
//
// = FILENAME
//    ClientDriver.java
//
// = AUTHOR
//    Amit Haldankar (amit.haldankar@stdc.com)
//
// = DESCRIPTION
//   Driver interface for Client.
//
// ============================================================================


/**
 * @authors Amit Haldankar March 2002
 *
 * A start for QMS in java
 *
 */

public interface ClientDriver extends Runnable
{
    public void init(Client client);

    public void run();
}
