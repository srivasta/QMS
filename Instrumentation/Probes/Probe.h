//                              -*- Mode: C++ -*-
// Probe.h ---
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
// Created On       : Mon Feb  5 01:35:59 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Oct 24 12:26:27 2001
// Last Machine Used: glaurung.stdc.com
// Update Count     : 3
// Status           : Unknown, Use with caution!
// HISTORY          :
// Description      :
//
// $Id: Probe.h,v 1.5 2001/12/02 03:30:21 srivasta Exp $

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


#ifndef PROBE_H
#define PROBE_H

/** @file Probe.h
 *  @ingroup Probes
 *  @brief QMS Probes - Simple QoS metric probes deployed by the sensors
 *
 */


/** @defgroup Probes QMS Probes - Simple QoS metric probes deployed by the sensors
 *  @ingroup  Instrumentation
 *
 * Probes are the lowest level entity in the QMS infrastructure. If
 * there is a data stream that is being generated, then there is a
 * probe.  Conceptually, a probe is the portion of the entity that is
 * generating the data stream. Ofcourse, the probe could be a separate
 * entity that allows itself to be controlled by the Sensor (this is
 * how the Generic Sensor interacts with its probes) or it could be a
 * probe that is built into the Sensor and has no existence of its own
 * (the HelloWorld Probe).
 *
 *  Probes are defined to be simple data sources, inserted either in
 *  application software on in the operating system itself. Most
 *  probes are designed to have minimal impact on the system being
 *  instrumented, and thus not perturb the operating points of the
 *  process being monitored.
 *
 *   The Sensor/Probe communication is designed to be simplistic; no
 *   complex hand shake protocols are envisaged. Indeed, in abstract,
 *   probes are extremely polymorphic: in theory, probes only need
 *   support two commands;
 *      -# provide data (with some optional parameters, perhaps)
 *      -# terminate
 *
 *  Where more sophisticated pre-processing of the datum being
 *  generated is desirable, it is performed by the sensor that
 *  inserted the probe.
 *
 * @em Resource @em Discovery
 *
 *   A simple way for handling capability file updates can be added to
 *   the packaging of the probes:
 *     - Part of the of the installation of a probe would be an XML
 *       snippet that contains the stanza describing things like
 *       location, family of probe/sensor communication methods,
 *       class of data provided, etc
 *     - In the post install hook, add a call to a standard utility to
 *       regenerate the capability file using a header, a footer, and the
 *       snippets provided by all the probes
 *     - Signal all local sensors to re-read the capabilities file
 *  A similar process occurs whenever the probe is removed from the
 *  system:
 *     - The XML snippet that detaild the probes capabilities is
 *       removed.
 *     - In the post removal hook, a call is made to the standard utility
 *       to regenerate the capabilities file
 *     - Signal all local sensors to re-read the capabilities file
 *
 * @em Classification @em of @em Probes
 *
 *
 *   Probes are classified based loosely on the means of communication
 *   with the sensor. (Use of XML as a data encoding scheme is not
 *   mandated for probes, since the presence4 of a XML parser maybe
 *   overly onerous for a lightweight probe). Some of the common methods
 *   under consideration are:
 *     - IPC using named pipes
 *     - Child process communicating over stdin/stdout
 *     - dynamically loaded libraries loaded into the sensor process
 *     - compiled directly into the sensor code
 *
 * @em Understanding @em Probes
 *
 *
 * When you've identified a unique data stream you have a case for a probe.
 * The first step is to define a format for the data that the probe
 * generates. It is important for this format to be something that the
 * clients receiving the data understand as well, so as to be able to make
 * sense of the data they are receiving. So this is accomplished by defining
 * an XML Schema for the probe - ProbeSchema.xsd that clearly defines the
 * format in which the probe publishes its data.
 *
 * Now we would like to have the probe also support some additional features
 * such as stopping the data stream, starting the data stream etc. These
 * would be instructions sent to the probe in a request from the client. To
 * make sure that the client understands the instructions, these are also
 * described in the ProbeSchema.xsd. This ensures that the clients also know
 * what instructions are supported by the Probe and how to activate them.
 *
 */

#endif // PROBE_H
