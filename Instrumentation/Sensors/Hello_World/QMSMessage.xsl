<?xml version="1.0" encoding="UTF-8"?>
<!-- *****************************************************************
 *** Copyright (c) 2001, System/Technology Development Corporation
 ***                
 *** Filename:      QMSMessage.xsl
 *** Version:       1.0
 *** Description:   QMS Message Transform that defines the needed templates
 ***                
 *** Author:        Amarendranath Vadlamudi <amar.vadlamudi@stdc.com>
 *** Created at:    Fri Nov  2 18:02:45 2001
 *** Modified by:   Amarendranath Vadlamudi <nath@vedam>
 *** Modified at:   Wed Nov 21 15:38:09 2001
 *** Status:        Experimental, do not distribute.
 *** Update count:  44
 ***************************************************************** -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:qms="http://www.stdc.com/2001/QMSSchema"
  version="$Id: QMSMessage.xsl,v 1.5 2001/11/21 20:40:47 nath Exp $">

  <xsl:output method="text"/>
  
  <!-- Defining some easy access tags. These variables provide ready
  access to essential parameters in all the probe XSL files -->
  <xsl:variable name="session" select="/qms:QMSMessage/qms:Session"/>
  <xsl:variable name="repetitions"
    select="$session/qms:minRepetitions/qms:count"/>
  <xsl:variable name="interval"
    select="$session/qms:minRepeatInterval"/>

  <!-- This input parameter identifies whether the message is a new
  request or a modify on an existing request. The sensor determines
  this using the requestid and the version number in the QMS Message 
  header. It then performs a transform to determine what action it
  should take for this message. Allowed values for "msgType" are "new"
  and "modify". 
  Default value: "new" -->
  <xsl:param name="msgType" select="'new'"/>

  <!-- The input parameter that will define what action the Sensor is 
  taking and which template should be called. The values for input are
  getAction - this will return "noaction" "exec" "write-to-pipe" 
  getExecString - this will return the commandline to exec
  getProbeString - this will return the line to write to the pipe
  getIsTerminate - this will return true if the request is to terminate
                the probe
  Default value: "getAction" -->
  <xsl:param name="input" select="'getAction'"/>

  <!-- This input parameter identifies whether the output from the
  XSL transform should include verbose information that aids in human
  readability of the generated transform data. Default value is false
  for this parameter -->
  <xsl:param name="verbose" select="'false'"/>

  <!-- To prevent any text nodes from printing -->
  <xsl:template match="text()">
  </xsl:template>

  <!-- Defining a common error template for a fixed error format. Call
  this template as shown below with the error message passed in a
  parameter -->
  <xsl:template name="printError">
    <!-- The passed Error message -->
    <xsl:param name="error"/>

    <!-- Print the message correctly -->
    <xsl:text>Error=</xsl:text>
    <xsl:value-of select="$error"/>
    <xsl:text>&#xA;</xsl:text>
  </xsl:template>


  <!-- Check on the input parameters and call appropriate
  template. The contents of these templates will be defined by the
  Probe schema developers. The templates are expected to perform the
  following function:
  buildAction      - indicate whether a new probe needs to be exec'ed or a
                     command needs to be written to a pipe
  IsTerminate      - is this message a stop request. Aids in sensor
                     cleanup
  buildExecString  - The command line to exec
  buildProbeString - The command to write to the pipe input
 -->
  <xsl:template  name="processPayload">

    <!-- Verify that param msgType has a valid value -->
    <xsl:choose>
      <xsl:when test="($msgType='new') or ($msgType='modify')">
        <xsl:choose>
	  <xsl:when test="$input='getAction'">
	    <xsl:call-template name="buildAction">
	      <xsl:with-param name="msgType" select="$msgType"/>
	      <xsl:with-param name="verbose" select="$verbose"/>
	    </xsl:call-template>
	  </xsl:when>
	  <xsl:when test="$input='getIsTerminate'">
	    <xsl:call-template name="isTerminate">
	      <xsl:with-param name="verbose" select="$verbose"/>
	    </xsl:call-template>
	  </xsl:when>
	  <xsl:when test="$input='getExecString'">
	    <xsl:call-template name="buildExecString">
	      <xsl:with-param name="verbose" select="$verbose"/>
	    </xsl:call-template>
	  </xsl:when>
	  <xsl:when test="$input='getProbeString'">
	    <xsl:call-template name="buildProbeString">
	      <xsl:with-param name="verbose" select="$verbose"/>
	    </xsl:call-template>
	  </xsl:when>
	  <xsl:otherwise>
	    <!-- param input has an invalid value -->
	    <xsl:call-template name="printError">
	      <xsl:with-param name="error" 
		select="concat('Invalid Parameters. Param input=', $input)"/>
	    </xsl:call-template>
	  </xsl:otherwise>
	</xsl:choose>
      </xsl:when>
      <xsl:otherwise>
	<!-- msgType has an invalid value -->
	<xsl:call-template name="printError">
	  <xsl:with-param name="error" 
	    select="concat('Invalid Parameters. Param msgType=', $msgType)"/>
	</xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>



  <!-- Primary entry point for the transforms. First we check if this
  is a valid payload and then we perform the appropriate action -->
  <xsl:template match="/qms:QMSMessage">

    <!-- This is designed to catch any erroneous delivery of valid QMS
    Messages (messages that have passed the schema check) that contain
    payloads intended for a different probe. At the very least, when
    the namespace the payload has and the namespace defined by the
    probe's XSLT file in probe: do not match this should return an
    error. This requires that the probes XSLT file have a valid probe:
    namespace defined and a valid definition of the variable
    $payloadRoot. We look for a node with the right namespace. If the
    namespaces of the payload and the probe: definition in the XSLT
    file match, this node name should not be null.  -->

    <xsl:choose>
      <!-- The root element of payload is not null so it is valid -->
      <xsl:when test="$payloadRoot!=''">
	<xsl:call-template name="processPayload"/>
      </xsl:when>
      
      <!-- If payloadRoot is null, then this is an error -->    
      <xsl:otherwise>
	
	<!-- Get the Namespace URI for the payload in the message -->
	<xsl:variable name="payloadNS">
	  <xsl:for-each select="qms:payload/*[1]">
	    <xsl:value-of select="namespace-uri(.)"/>
	  </xsl:for-each>
	</xsl:variable>
	
	<xsl:call-template name="printError">
	  <xsl:with-param name="error" 
	    select="concat('Incorrect payload namespace in message - ', 
	    $payloadNS)"/>
	</xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
</xsl:stylesheet>
