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
 *** Modified at:   Mon Nov  5 12:54:24 2001
 *** Status:        Experimental, do not distribute.
 *** Update count:  24
 ***************************************************************** -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:qms="http://www.stdc.com/2001/QMSSchema"
  version="$Id: QMSMessage.xsl,v 1.3 2001/11/05 18:32:09 nath Exp $">

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
  <xsl:template  match="/qms:QMSMessage">
    
    <!-- Verify that param msgType has a valid value -->
    <xsl:choose>
      <xsl:when test="($msgType='new') or ($msgType='modify')">
        <xsl:choose>
	  <xsl:when test="$input='getAction'">
	    <xsl:call-template name="buildAction">
	      <xsl:with-param name="msgType" select="$msgType"/>
	    </xsl:call-template>
	  </xsl:when>
	  <xsl:when test="$input='getIsTerminate'">
	    <xsl:call-template name="isTerminate">
	    </xsl:call-template>
	  </xsl:when>
	  <xsl:when test="$input='getExecString'">
	    <xsl:call-template name="buildExecString">
	    </xsl:call-template>
	  </xsl:when>
	  <xsl:when test="$input='getProbeString'">
	    <xsl:call-template name="buildProbeString">
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
  
</xsl:stylesheet>
