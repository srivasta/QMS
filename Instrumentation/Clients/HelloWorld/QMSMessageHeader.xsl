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
  version="$Id: QMSMessageHeader.xsl,v 1.1 2002/04/10 21:58:06 amit Exp $">

  <xsl:output method="text"/>
  
  <!-- Defining some easy access tags. These variables provide ready
  access to essential parameters in all the probe XSL files -->
  <xsl:variable name="originatingHost" select="/qms:QMSMessage/qms:originatingHost"/>
  <xsl:variable name="uniqueName" select="/qms:QMSMessage/qms:QMSUniqueName"/>
  <xsl:variable name="session" select="/qms:QMSMessage/qms:Session"/>
  <xsl:variable name="repetitions"
    select="$session/qms:minRepetitions/qms:count"/>
  <xsl:variable name="currentCount"
    select="$session/qms:minRepetitions/qms:current"/>
  <xsl:variable name="interval"
    select="$session/qms:minRepeatInterval"/>


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

  <xsl:template name="header" match="/qms:QMSMessage">
    QMS Header Info:
      Date: <xsl:value-of select="/qms:QMSMessage/qms:msgDate" /> Time: <xsl:value-of select="/qms:QMSMessage/qms:msgTime" />
      QMS Unique name:
        Category: <xsl:value-of select="$uniqueName/qms:category" />
        Host:     <xsl:value-of select="$uniqueName/qms:host" />
        Uuid:     <xsl:value-of select="$uniqueName/qms:uuid" />
      Count: <xsl:value-of select="$repetitions" /> Current: <xsl:value-of select="$currentCount" />
      Repeat Interval: <xsl:value-of select="$interval" />
      <xsl:call-template name="payload" />
  </xsl:template>

  <!-- Primary entry point for the transforms. First we check if this
  is a valid payload and then we perform the appropriate action -->
  <xsl:template match="/">

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
	<xsl:apply-templates />
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
