/*****************************************************************************
** Programmers:  Jim Carroll, Mustafizur Rahman
** File: remos-link-data.cpp
** Date: October 19, 2000
** Purpose:  This file contains class definitions for
**           RemosLinkData
**
** $Id: remos-link-data.cpp,v 1.1 2001/12/10 06:26:20 spatil Exp $
**
******************************************************************************/

/*
** System Includes
*/


/*
** User includes
*/

#include "remos-link-data.h"

/*
** Global Variables
*/


/*********************************************************************
** Class definitions for RemosLinkData.
*********************************************************************/

RemosLinkData::RemosLinkData() {
	_link_type = remos_link,
	_source_node = "",
	_destination_node = "",
	_latency = 0.0,
	_available_bandwidth = 0.0,
	_static_bandwidth = 0.0;
}

RemosLinkData::RemosLinkData(remos_link_type link_type,
	string source_node,
	string destination_node,
	double latency,
	double available_bandwidth,
	double static_bandwidth) {
	_link_type = link_type,
	_source_node = source_node,
	_destination_node = destination_node,
	_latency = latency,
	_available_bandwidth = available_bandwidth,
	_static_bandwidth = static_bandwidth;
}

RemosLinkData::~RemosLinkData() {
}

/*****************************************************************************/
