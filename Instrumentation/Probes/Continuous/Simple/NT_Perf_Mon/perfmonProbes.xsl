<?xml version="1.0" encoding="UTF-8"?>
<!-- *****************************************************************
 *** Copyright (c) 2001, System/Technology Development Corporation .
 ***                
 *** Filename:      perfmonProbes.xsl
 *** Version:       1.0
 *** Description:   XSL Transforms to generate Perfmon Probe command parameters
 ***                
 *** Author:        Amarendranath Vadlamudi <amar.vadlamudi@stdc.com>
 *** Created at:    Mon Nov  26 11:30:03 2001
 *** Modified by:   Amarendranath Vadlamudi <nath@vedam>
 *** Modified at:   Fri Dec  7 13:04:54 2001
 *** Status:        Experimental, do not distribute.
 *** Update count:  15
 ***************************************************************** -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:qms="http://www.stdc.com/2001/QMSSchema"
  xmlns:probe="http://www.stdc.com/2001/QMS/Probes/perfmonProbes"
  version="$Id: perfmonProbes.xsl,v 1.3 2001/12/07 18:47:17 nath Exp $ ">

  <!-- This variable is a mandatory definition for every probe. This
  is used initially to verify that the namespace used by the payload
  is actually the namespace we are expecting, i.e. probe: -->
  <xsl:variable name="payloadRoot"
    select="name(/qms:QMSMessage/qms:payload/probe:*[1])"/>
  
  <!-- Include the primary XSL definitions that will be used by all
  Sensors in QMS where the template names and variables are defined. -->
  <xsl:include href="QMSMessage.xsl"/>

  <!-- The additional parameters that this probe needs. These
  parameters are also defined in the Capability Fragments and hence
  are available to the Sensor at runtime.-->
  <xsl:param name="resource" select="''"/>

  <!-- Defining some easy access tags The Performance Monitor Probe
  Schema defines the action element that controls the execution of the
  probes. This is the element we're accessing here.--> 

  <xsl:variable
    name="payloadElement"
    select="/qms:QMSMessage/qms:payload/probe:perfmonProbe"/>
  <xsl:variable
    name="action"
    select="$payloadElement/probe:perfmonRequest/probe:probeControl/probe:action"/>

  <!-- Template: buildAction
  This template serves as the mechanism used by the Sensor to
  determine what to do with the request. The result indicates to the
  Sensor if the probe is to be exec'ed (Decision=exec), a command is
  to sent to the probe (Decision=write-to-pipe) or nothing is to be
  done (Decision=noaction). The Sensor also passes the msgType
  parameter to the template after determining if the message is a
  "new" message or a "modify" message -->
  
  <xsl:template name="buildAction">

    <!-- This parameter is received as an input parameter from the
    calling entity -->
  
    <xsl:param name="msgType"/>

    <!-- This parameter is received as an input parameter from the
    calling entity. This is generally not used in the regular
    operation of the Sensor. Can be useful as a debugging tool.Default
    value is false. --> 
    
    <xsl:param name="verbose"/>

    <!-- Set isRequest variable once we determine if the message is a
    legitimate request for this probe -->
    <xsl:variable name="isRequest">
      <xsl:for-each select="$payloadElement/*[1]">
	<xsl:value-of select="name(.)='perfmonRequest'"/>
      </xsl:for-each>
    </xsl:variable>

    <!-- Debug messages -->
    <xsl:if test="($verbose='true')">
      <xsl:text>Message Type = </xsl:text>
      <xsl:value-of select="$msgType"/>
      <xsl:text>&#xA;</xsl:text>
      <xsl:text>Request Message = </xsl:text>
      <xsl:value-of select="$isRequest"/>
      <xsl:text>&#xA;</xsl:text>
      <xsl:text>Decision = </xsl:text>
    </xsl:if>

    <!-- A new request needs to be exec'ed, while a modify request
    needs to send a command to an existing probe. A catchall
    "noaction" at the end for all other cases -->
    <xsl:choose>
      <xsl:when test="($isRequest='true') and ($msgType='modify')">
	<xsl:text>write-to-pipe</xsl:text>
      </xsl:when>
      <xsl:when test="($isRequest='true') and ($msgType='new')">
	<xsl:text>exec</xsl:text>
      </xsl:when>
      <xsl:otherwise>
	<xsl:text>noaction</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- Template: buildExecString
  This template provides the Executable String which the Sensor
  will use to Exec the probe instance -->
  <xsl:template name="buildExecString">

    <!-- This parameter is received as an input parameter from the
    calling entity. Default value is false. -->
    <xsl:param name="verbose"/>

    <!-- Verbose output is on -->
    <xsl:if test="($verbose='true')">
      <xsl:text>Resource Name = </xsl:text>
      <xsl:value-of select="$resource"/>
      <xsl:text>&#xA;</xsl:text>
      <xsl:text>Repetitions = </xsl:text>
      <xsl:value-of select="$repetitions"/>
      <xsl:text>&#xA;</xsl:text>
      <xsl:text>Interval = </xsl:text>
      <xsl:value-of select="$interval"/>
      <xsl:text>&#xA;</xsl:text>
      <xsl:text>Command Line = </xsl:text>
    </xsl:if>

    <xsl:text>-r&#xA;</xsl:text><xsl:value-of select="$repetitions"/>
    <xsl:text>&#xA;-i&#xA;</xsl:text><xsl:value-of select="$interval"/>
    <xsl:text>&#xA;-n&#xA;</xsl:text>
    <xsl:value-of select="$resource"/>
  </xsl:template>

  
  <!-- Template: buildProbeString
  Get the message to Write to the Pipe 
  There are two kinds of messages that we can write to the pipe.
  1. A message that indicates the parameters to change the behaviour
  of the data collection
  2. A message that controls the execution of the pipe -->
  <xsl:template name="buildProbeString">

    <!-- This parameter is received as an input parameter from the
    calling entity. Default value is false. -->
    <xsl:param name="verbose"/>
    
    <!-- According to the perfmonProbes.xsd schema, the control messages
    are specified in a probeControl element. So if the probeControl
    element exists, then this is a control message -->
    <xsl:variable name="isControlMessage">
      <xsl:for-each select="$payloadElement/probe:perfmonRequest/*[1]">
	<xsl:value-of select="name(.)='probeControl'"/>
      </xsl:for-each>
    </xsl:variable>

    <!-- Verbose output is on -->
    <xsl:if test="($verbose='true')">
      <xsl:text>Is this a Control Message = </xsl:text>
      <xsl:value-of select="$isControlMessage"/>
      <xsl:text>&#xA;</xsl:text>
      <xsl:text>Probe String for Pipe = </xsl:text>
    </xsl:if>

    <xsl:choose>
      <xsl:when test="$isControlMessage='true'">
        <!-- This is a control message -->
        <xsl:value-of select="concat($action, '&#xA;')"/>
      </xsl:when>
      <xsl:otherwise>
        <!-- This is a perfmonRequest for a specific resource -->
	<xsl:value-of select="concat('count,', $repetitions, '&#xA;')"/>
	<xsl:value-of select="concat('intrval,', $interval)"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <!-- Template: isTerminate
  If this request is a terminate request, tell the sensor so.
  Note that the Sensor has already determined that this is a valid 
  modify message for a valid request, so there is no need to redo the
  check here.-->
  <xsl:template name="isTerminate">

    <!-- This parameter is received as an input parameter from the
    calling entity. Default value is false. -->
    <xsl:param name="verbose"/>

    <!-- Verbose output is on -->
    <xsl:if test="($verbose='true')">
      <xsl:text>isTerminate = </xsl:text>
    </xsl:if>

    <xsl:choose>
      <xsl:when test="$action='stop'">
	<xsl:text>true</xsl:text>
      </xsl:when>
      <xsl:otherwise>
	<xsl:text>false</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

</xsl:stylesheet>
