//                              -*- Mode: C++ -*-
// QMS.h ---
// Author           : Manoj Srivastava ( srivasta@ember )
// Created On       : Thu Jan 11 13:27:41 2001
// Created On Node  : ember
// Last Modified By : Amar Vadlamudi (amar.vadlamudi@stdc.com)
// Last Modified On : Thu Jan 03 16:32:01 2002
// Last Machine Used: vedam.stdc.com
// Update Count     : 51
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
//  $Id: QMS.h,v 1.19 2002/01/03 22:42:53 nath Exp $
//

/*
 * Copyright (C) 2001 System/Technology Development Corporation
 * This file is part of QoS Metrics Services (QMS)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA
 *
 * You may contact System/Technology Development Corporation at
 *
 *     System/Technology Development Corporation
 *     Suite 500, Center for Innovative Technology,
 *     2214 Rock Hill Road,
 *     Herndon, VA 20170    
 *     (703) 476-0687
 */


#ifndef QMS_H_
#define QMS_H_
/** @file QMS.h
 *  @brief The Top level documentation driver.
 *
 * $Id: QMS.h,v 1.19 2002/01/03 22:42:53 nath Exp $
 */

/** @mainpage  QMS Documentation
 *
 *  @section QMSOverview Overview
 *  QMS provides a message oriented transport mechanism and a set of
 *  services that facilitates communication between data consumers and
 *  data producers. QMS contains a cross platform, robust, data
 *  agnostic publish/subscribe framework for this communication.
 *  <em>Thus QMS delivers the ability to negotiate QoS in multiple 
 *  dimensions by enabling dynamic insight into changing system resources, 
 *  conditions and mission needs (QoS metrics)</em>.
 *
 *
 *  @subsection Capabilities Major Capabilities
 *   
 *     - Provide the ability to distribute QoS metrics data to a dynamic
 *       set of consumers from a dynamic set of suppliers in the
 *       environment
 *     - Support the use of publish/subscribe and request/response
 *       mechanisms for the distribution of QoS metrics data.
 *     - Provides the ability to readily add new data streams into the 
 *       environment with minimal effort using XML and XSL transforms.
 *     - Provide the ability to determine the number and nature of the 
 *       various data suppliers in the environment dynamically
 *     - Provide comprehensive logging of all instrumented event data for
 *       analysis and for use in tracking historical performance of
 *       instrumented applications
 *     - Provide transparent instrumentation mechanisms to instrument
 *       applications for QoS related metrics
 *     - Provide visualization mechanisms for the visualization of event
 *       data as text logs and as graphs.
 *
 *  A design goal of QMS citizens has been that they should themselves
 *  be well behaved, QoS aware, adaptive applications designed to fit
 *  well into a distributed QoS sensitive environemnt. Rapid failure
 *  detection and inbuilt security are other high priority design
 *  considerations.
 *
 *  QMS uses XML for data representation, as well as configuration and
 *  reports. QMS also uses XSL to provide the close coupling needed between
 *  Sensors and Probes that were designed independent of each other. Along 
 *  with the code for the components are testing
 *  programs, and benchmarks for some of the components.
 *
 *  @htmlonly
 *
 *  The following <a href="../images/QMS-1.swf" alt="QMS Flash
 *  Animation">animation</a> provides an overview of the capabilities
 *  of QMS.  You will need a means of viewing <a
 *  href="http://www.macromedia.com/">Shockwave flash</a> in order to
 *  view this animation.
 *
 *  @endhtmlonly
 *
 *  @subsection SubIndex1 Getting Started 
 *
 *  -# @ref README.background
 *     - @ref QMSTerminology
 *     - @ref QMSSensors
 *     - @ref QMSProbes
 *     - @ref QMSClients
 *     - @ref QMSTraderOverview
 *  -# @ref README.install
 *     - @ref SystemRequirements
 *  -# @ref README.run
 *  -# @ref README.FAQ
 *
 *  @subsection SubIndex2 An Example Sensor/Probe
 *  
 *  To demonstrate the concepts in QMS, we present an example implementation
 *  of a trivial Sensor with a builtin probe. Please see the documentation 
 *  for the HelloWorld Sensor in the modules for additional information and
 *  the source code.
 *
 *  - @ref HelloWorldOverview
 *  - @ref BuildSensor
 *  - @ref BuildClient
 *  
 *  See the Modules section for details on more advanced Sensors and Probes.
 *
 *  @subsection Acknowledgements Acknowledgements
 *
 *  This work was performed under the aegis of the 
 *  <a href="http://quite.teknowledge.com/">QUITE project</a>,
 *  which is a <a href="http://www.darpa.mil">DARPA</a>
 *  project geared towards integrating the
 *  technologies developed under the 
 *  <a href="http://www.darpa.mil/ito/research/quorum/projects.html">QUORUM
 *  </a> program.
 */

/** @defgroup QMS  QoS Metric Services
 *
 *  QMS provides a message oriented transport mechanism that facilitates
 *  communication between data consumers and data producers. QMS also
 *  provides a cross platform, robust, data agnostic publish/subscribe
 *  framework for this communication.
 *
 *  A design goal of QMS citizens has been that they should themselves
 *  be well behaved, QoS aware, adaptive applications designed to fit
 *  well into a distributed QoS sensitive environemnt. Rapid failure
 *  detection and inbuilt security are other high priority design
 *  considerations.
 *
 *  Major Capabilities:
 *
 *     - Provide the ability to distribute QoS metrics data to a
 *       dynamic set of consumers from a dynamic set of suppliers in
 *       the environment
 *     - Support the use of publish/subscribe and request/response
 *       mechanisms for the distribution of QoS metrics data. 
 *     - Provide comprehensive logging of all instrumented event data
 *       for analysis and for use in tracking historical performance
 *       of instrumented applications  
 *     - Provide transparent instrumentation mechanisms to instrument
 *       applications for QoS related metrics   
 *     - Provide visualization mechanisms for the visualization of
 *       event data as text logs and as graphs.
 */


/** @defgroup Services The Core services provided by QMS
 *  @ingroup  QMS
 *
 *  These adapters and interfaces represent core services
 *  ofered by QMS. Currently on the drawing board is a sophisticated
 *  trading/resource discovery module, which shall allow data
 *  providers to publish their presence in the enviroenment, and allow
 *  data consumers to discover such data providers, and perhaps
 *  request tailored data reports from such providers.
 */

/** @defgroup COMMAND The QMS Command and control Interface and adapter
 *  @ingroup  Services 
 *  
 * This interface is the mandatory interface that has to be
 * implemented by all QMS citizens.  These are standard CORBA object
 * interfaces. Examples of the methods implemented are:
 *
 *    -  Pause, Resume, Stop
 *    -  Connect and Disconnect from Event Channel
 *    -  Get and Set Attributes
 *    -  Ping
 *    -  Dump statistics
 *
 * The adapter classes provide a convenient standard C++ class that
 * encapsulates the client and server interactions to the QMS
 * Citizen's madatory command and control interfaces.
 */

/** @defgroup Facilities Plug ins and add-on facilities provided with QMS
 *  @ingroup  QMS
 *
 *  This group of modules represent added facilities tied in to the
 *  QMS infrastructure that perform useful tasks in the
 *  environment. Unlike the core services, these are not necesarily
 *  services provided to modules built on top of QMS and incorporated
 *  into the functionality of the add on modules, instead these are
 *  stand alone facilities that may be useful in their own right.
 *
 *  One such facility is the QMS logger, which listens for and logs
 *  QMS events. A redesigned logger shall offer flexibility of
 *  backends, and full control of logging activity.
 *
 *  Another facility planned is a flexible event and activity
 *  visualizer.
 */

/** @defgroup Visualizer The QMS Data visualization plugin
 *  @ingroup Facilities
 *
 *  The data visualizer listens for service request on the event
 *  channel, and plots the requested data 
 */


/** @defgroup Utilities Utilities - Miscellaneous software utilities
 *  @ingroup  QMS
 *
 *  These are modules that provide software ustilities and reuseable
 *  objects that can be used in other QMS components, or can be used
 *  by client software.  A number of template libraries and reference
 *  implementations of various patterns are planned.
 *   - Debugging Tools
 *   - Benchmarking Tools
 *   - Test Harnesses
 *   - Utility Libraries
 *      - XML Parsing
 *      - File Backend (read/write)
 *      - Data Structures and other patterns
 */

/** @defgroup TAOEC The TAO Event Channel Interface and Adapter
 *  @ingroup  Utilities
 *  
 * QMS uses the TAO event channel to transport requests and
 * responses. 
 *
 * The adapter classes provide a convenient standard C++ class that
 * encapsulates the CORBA event channel object classes, covering both
 * consumers and suppliers of events on the channel. It also incudes a
 * convenience class for capturing CORBA related handles.
 */


/** @defgroup Contrib Third party software integrated with QMS
 *  @ingroup  QMS
 *
 *  These are a collection of third party modules and software that
 *  have incorporated the QMS API and have been contributed for
 *  inclusion here. These third party modules may be instrumentation
 *  (either as sensors or probes), or can be data consumers (for
 *  example, resource managers) fitted with a QMS interface.
 */

/** @defgroup Testing Testing - Non production code used for testing
 *  @ingroup Utilities
 *
 * These are non production programs and files used to test interfaces
 * and parts of QMS during development. All new classes must have a
 * corresponding set of test programs to exercise the interface.
 */


/** @defgroup Benchmarks Benchmarks - Non production code for performance measurement
 *  @ingroup Utilities
 *
 * These are non production programs use to generate performance
 * metrics for the QMS system. Based on the class ACE_High_Res_Timer,
 * A high resolution timer class wrapper that encapsulates
 * OS-specific high-resolution timers, such as those found on
 * Solaris, AIX, Win32/Pentium, and VxWorks.
 */



#endif // QMS_H_
