/*****************************************************************************
** Programmers:  Jim Carroll, Mustafizur Rahman
** File: remos-link-data.h
** Date: November 6, 2000
** Purpose:  This is the header file for remos-link-data.cpp
**
** $Id: remos-link-data.h,v 1.1 2001/12/10 06:26:20 spatil Exp $
**
******************************************************************************/

#ifndef REMOS_LINK_DATA_H
#define REMOS_LINK_DATA_H

#include <string>


using namespace std;


enum remos_link_type {remos_link, remos_flow};


class RemosLinkData {

public:

	RemosLinkData();

	RemosLinkData(remos_link_type, string, string, double, double, double);

	~RemosLinkData();

	remos_link_type link_type() { return _link_type; }

	void set_link_type(remos_link_type link_type) { _link_type = link_type; }

	string source_node() { return _source_node; }

	string destination_node() { return _destination_node; }

	double latency() { return _latency; }

	void set_latency(double latency) { _latency = latency; }

	double available_bandwidth() { return _available_bandwidth; }

	void set_available_bandwidth(double available_bandwidth) { _available_bandwidth = available_bandwidth; }

	double static_bandwidth() { return _static_bandwidth; }

	void set_static_bandwidth(double static_bandwidth) { _static_bandwidth = static_bandwidth; }

private:
	remos_link_type _link_type;

	string _source_node;

	string _destination_node;

	double _latency;

	double _available_bandwidth;

	double _static_bandwidth;

};

#endif

/*********** End of Code for network-broker.h ************/
