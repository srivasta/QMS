#!/bin/sh
######################################################################
## Copyright (c) 2001, System/Technology Development Corporation
##                
## Filename:      CommandProbe.sh
## Version:       1.0
## Description:   Command Execution Probe with Unix Shell
##                
## Author:        Amarendranath Vadlamudi <nath@vedam>
## Created at:    Fri Dec 14 01:05:23 2001
## Modified by:   Amarendranath Vadlamudi <nath@vedam>
## Modified at:   Thu Dec 27 19:11:21 2001
## Status:        Experimental, do not distribute.
## Update count:  17
######################################################################

PATH=/bin:/usr/bin
export PATH

# Defining some binaries we need upfront
ECHO=/bin/echo
SED=/bin/sed
PS=/bin/ps

# Wait for the start
while [ 1 ] ; do
    read input
    
    case $input in 
	start)
	    
# Putting the XML header for a Command Probe schema
	    
	    HEADER='<?xml version="1.0" encoding="UTF-8"?>
<commandProbe
   xmlns="http://www.stdc.com/2001/QMS/Probes/Continuous/CommandProbe"
   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
   xsi:schemaLocation=
   "http://www.stdc.com/2001/QMS/Probes/Continuous/CommandProbe
    commandProbe.xsd">
   <probeData>'
	    
	    export HEADER
	    
# Creating the XML Footer for the Command Probe schema
	    FOOTER='
     </response>
   </probeData>
</commandProbe>
<!-- ******_PROBE_MESSAGE_DELIMITER_****** -->'
	    export FOOTER

	    # Sanitize the received arguments. Ignoring the '>' for now
	    cleanCommand=`$ECHO $@ | $SED 's/</\&lt;/'`
	    
	    # Create the received request message
	    echo $HEADER ;
	    $ECHO "<dataid>1</dataid><response>"
	    $ECHO "<textData><message>"
	    $ECHO "Received request to execute '$cleanCommand'"
	    $ECHO "</message></textData>"
	    $ECHO $FOOTER 


	    # Create the message with the data content
	    $ECHO $HEADER ;
	    $ECHO "<dataid>2</dataid><response>"
	    $ECHO "<textData><message>"
	    $ECHO "Request to execute '$cleanCommand'"
	    $ECHO "Output:"
	    $ECHO ""
	    
	    ($@ | /bin/sed 's/</\&lt;/') &
#	    ($@  | /bin/sed 's/</\&lt;/') &
	    # Grab the PID for use in the stop
	    SED_PID=$!

	    # If the command exited normally, why should we hang around
	    if [ -z "`$PS --no-headers -p $SED_PID`" ] ; then
		$ECHO "</message></textData>"
		$ECHO $FOOTER ;
		exit 0
	    fi
	    ;;
	stop)
	    $ECHO "Process exiting on stop command"
	    $ECHO "<!-- "
	    
	    # Find the parent PID, since the actual command is SED_PID's 
	    # sibling
	    SED_PARENT=`$PS -p $SED_PID --no-headers -o ppid`

	    # Find all the processes that have my command name
	    for i in `$PS -c $1 --no-headers -o pid`
	    do
	      echo $i
	    done

	    kill -TERM $PID 
	    sleep 1
	    if [ -n "`$PS --no-headers -p $PID`" ] ; then
		kill -KILL $PID 
	    fi
	    $ECHO " -->"
	    # If the process hung around till now, then this needs to go
	    # around the killed messages that come back.
	    $ECHO ""
	    $ECHO $FOOTER ;
	    exit 0
	    ;;
    esac
done
