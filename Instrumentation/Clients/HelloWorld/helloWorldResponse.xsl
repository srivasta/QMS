<?xml version="1.0" encoding="UTF-8"?>
<!-- *****************************************************************
 *** Copyright (c) 2001, System/Technology Development Corporation .
 ***                
 *** Filename:      helloWorldResponse.xsl
 *** Version:       1.0
 *** Description:   XSL Transforms to build Generic Continuous Probe commands
 ***                
 *** Author:        Amit Haldankar <amit.haldankar@stdc.com>
 *** Created at:    Tue Apr  09 11:30:03 2002
 *** Modified by:   Amit Haldankar <amit@cougar>
 *** Modified at:   Tue Apr 09 20:01:24 2002
 *** Status:        Experimental, do not distribute.
 *** Update count:  6
 ***************************************************************** -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:qms="http://www.stdc.com/2001/QMSSchema"
  xmlns:probe="http://www.stdc.com/2001/QMS/helloWorld"
  version="$Id: helloWorldResponse.xsl,v 1.1 2002/04/10 21:58:06 amit Exp $">

  <!-- This variable is a mandatory definition for every probe. This
  is used initially to verify that the namespace used by the payload
  is actually the namespace we are expecting, i.e. probe: -->
  <xsl:variable name="payloadRoot"
    select="name(/qms:QMSMessage/qms:payload/probe:helloWorld)"/>
  
  <!-- Include the primary XSL definitions that will be used by all
  Sensors in QMS where the template names and variables are defined. -->
  <xsl:include href="QMSMessageHeader.xsl"/>
    
  <!-- Defining some easy access tags. The Generic Probe
  Schema defines the action element that controls the execution of the
  probes. This is the element we're accessing here.--> 

  <xsl:variable
    name="payloadElement"
    select="/qms:QMSMessage/qms:payload/probe:helloWorld"/>


  <xsl:template name="payload">
    Payload:
       Data Id:    <xsl:value-of select="$payloadElement/probe:Data/probe:dataid" />
       Salutation: <xsl:value-of select="$payloadElement/probe:Data/probe:salutation" />
  </xsl:template>

</xsl:stylesheet>
