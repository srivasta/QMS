<?xml version="1.0" encoding="UTF-8"?>
<!-- *****************************************************************
 *** Copyright (c) 2001, System/Technology Development Corporation .
 ***                
 *** Filename:      dllInterceptProbe.xsl
 *** Version:       1.0
 *** Description:   Transforms used by the probe to start and stop it
 ***                
 *** Author:        Amarendranath Vadlamudi <amar.vadlamudi@stdc.com>
 *** Created at:    Mon Nov 19 12:18:45 2001
 *** Modified by:   Amarendranath Vadlamudi <nath@vedam>
 *** Modified at:   Mon Nov 26 17:32:58 2001
 *** Status:        Experimental, do not distribute.
 *** Update count:  2
 ***************************************************************** -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:qms="http://www.stdc.com/2001/QMSSchema"
  xmlns:probe="http://www.stdc.com/2001/QMS/Probes/dllInterceptProbe"
  version="$Id: dllInterceptProbe.xsl,v 1.2 2001/11/26 22:34:18 nath Exp $">

  <!-- This variable is a mandatory definition for every probe. This
  is used initially to verify that the namespace used by the payload
  is actually the namespace we are expecting, i.e. probe: -->
  <xsl:variable name="payloadRoot"
    select="name(/qms:QMSMessage/qms:payload/probe:*[1])"/>
  
  <!-- Include the primary XSL definitions that will be used by all
  Sensors in QMS where the template names and variables are defined. -->
  <xsl:include href="QMSMessage.xsl"/>
    
  <!-- The additional parameters that this probe needs. These are -->
  <!-- obtained from the capability file by the sensor and provided to
  the XSLT engine -->
  <xsl:param name="NamedPipePrefix" select="'\\.\pipes\probe'"/>

  <xsl:template name="buildAction">
    <xsl:param name="msgType"/>
    <!-- Set isRequest variable -->
    <xsl:variable name="isRequest">
      <xsl:for-each select="qms:payload/probe:dllInterceptProbe/*[1]">
	<xsl:value-of select="name(.)='interceptRequest'"/>
      </xsl:for-each>
    </xsl:variable>
    <xsl:text>Message Type = </xsl:text>
    <xsl:value-of select="$msgType"/>
    <xsl:text>&#xA;</xsl:text>
    <xsl:text>Request Message = </xsl:text>
    <xsl:value-of select="$isRequest"/>
    <xsl:text>&#xA;</xsl:text>
    <xsl:choose>
      <xsl:when test="$isRequest='true'">
	<!-- Message is request -->
	<xsl:choose>
	  <xsl:when
	    test="qms:payload/probe:dllInterceptProbe/probe:interceptRequest/probe:action='activate'">
	    <!-- Request is an activate -->
	    <xsl:choose>
	      <xsl:when test="$msgType='new'">	      
		<!-- Activating a new request -->
		<xsl:text>Decision=exec</xsl:text>
	      </xsl:when>
	      <xsl:otherwise>
		<!-- Deactivating a new request is illegal -->
		<xsl:text>Decision=noaction</xsl:text>
	      </xsl:otherwise>
	    </xsl:choose>
	  </xsl:when>
	  <xsl:otherwise>
	    <!-- This is a deactivate -->
	    <xsl:choose>
	      <xsl:when test="$msgType='new'">
		<!-- Deactivating a new request is illegal -->
		<xsl:text>Decision=noaction</xsl:text>
	      </xsl:when>
	      <xsl:otherwise>
		<!-- Deactivating a modify request -->
		<xsl:text>Decision=write-to-pipe</xsl:text>
	      </xsl:otherwise>
	    </xsl:choose>
	  </xsl:otherwise>
	</xsl:choose>
      </xsl:when>
      <xsl:otherwise>
	<!-- Message is not a request, so take no action -->
	<xsl:text>Decision=noaction</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- This builds the Executable String -->

  <xsl:template name="buildExecString">
    <xsl:text>Command Line=</xsl:text>
    <xsl:text> -n </xsl:text><xsl:value-of select="$NamedPipePrefix"/>
    <xsl:variable name="request"
      select="qms:payload/probe:dllInterceptProbe/probe:interceptRequest"/>
    <xsl:text> -p </xsl:text>
    <xsl:value-of select="$request/probe:process_pid"/>
    <xsl:text> -w </xsl:text>
    <xsl:value-of select="$request/probe:wrapper_name"/>
    <xsl:text> -f </xsl:text>
    <xsl:value-of select="$request/probe:wrapper_file"/>
  </xsl:template>

  
  <!-- Get the message to Write to the Pipe -->
  <xsl:template name="buildProbeString">
    <xsl:choose>
      <xsl:when
	test="qms:payload/probe:dllInterceptProbe/probe:interceptRequest/probe:action='activate'">
	<xsl:text>start</xsl:text>
      </xsl:when>
	<xsl:when
	test="qms:payload/probe:dllInterceptProbe/probe:interceptRequest/probe:action='deactivate'">
	<xsl:text>stop</xsl:text>
      </xsl:when>
    </xsl:choose>
  </xsl:template>
  
  <!-- If this request is a terminate request, tell the sensor so. -->
  <xsl:template name="isTerminate">
    <xsl:choose>
      <xsl:when test="qms:payload/probe:dllInterceptProbe/probe:interceptRequest/probe:action='deactivate'">
	<xsl:text>isTerminate=true</xsl:text>
      </xsl:when>
      <xsl:otherwise>
	<xsl:text>isTerminate=false</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

</xsl:stylesheet>










