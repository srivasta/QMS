/*                               -*- Mode: C -*- 
 * Generic_Sensor.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
 * Created On       : Fri Oct 19 14:47:16 2001
 * Created On Node  : glaurung.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Tue Oct 30 13:29:23 2001
 * Last Machine Used: ember.stdc.com
 * Update Count     : 10
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
 */

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


#ifndef _GENERIC_SENSOR_H_
#define _GENERIC_SENSOR_H_

/** @file Generic_Sensor.idl
 *  @ingroup GenericSensor
 *  @brief The implementation of a Sensor interface
 *
 *  $Id: Generic_Sensor.h,v 1.9 2001/12/09 18:05:35 nath Exp $
 */

/** @defgroup GenericSensor Generic sensor - an example sensor implementation with external probes
 * @ingroup Sensors
 *
 * This is a concrete implementation of a QMS Sensor. Conceivably this
 * implementation is all you need in your system if all the data streams
 * that you use can be provided by external probes (programs).
 *
 * This implementation includes Local resource discovery, publishing
 * capabilities to enable global resource discovery, and full XML
 * parsing and validation capabilities and complete XSL transformation
 * capabilities.
 *
 * When the Sensor is instantiated, it is configured using an XML
 * configuration file - sensorConfiguration.xml that specify the
 * various parameters that the Sensor needs for its operation. This
 * file additionally specifies the capability file that this sensor
 * needs to read - sensorCapability.xml. The specified capability file
 * indicates to the Sensor what kind of data streams it is going to
 * publish into the QMS environment. Conceptually, each data stream is
 * generated by a probe.
 *
 * In addition, the capability file also specifies the exact kind and
 * nature of the XML transforms that the Sensor will need to execute
 * on each request that it receives. The file also specifies the exact
 * executable that will be exec'ed to instantiate the Probe.
 *
 * Note that the Sensor registers all its probe capabilities as offers
 * in the QMS Trader. Additionally, it also creates appropriate naming
 * contexts in the CORBA Name Service.
 */

#endif /* _GENERIC_SENSOR_H_ */