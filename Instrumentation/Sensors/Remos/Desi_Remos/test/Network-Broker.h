//Network-Broker.h
// Author Shivakumar C. Patil (shivakumar.patil@stdc.com)

#ifndef NETWORK_BROKER_H
#define NETWORK_BROKER_H

/*
** Microsoft workarounds
*/

#pragma warning( disable: 4786 )
#pragma warning( disable: 4788 )

#include <strstream>
#include <vector>
#include <set>

#include "remos-link-data.h"

typedef pair<string, string> host_pair;

class NetworkBroker {
public:
	NetworkBroker(void);
	NetworkBroker(char*, int, char*);
	~NetworkBroker();
	int  init(char*, int, char*);
	bool connect_network_analyzer();
	bool init_host_pairs(const char*);
	void init_host_pairs();
	bool submit_remos_query(void *arg_p);
	void process_remos_data(const string& data, void *arg_p);
private:
	char* _name_server_host;
	int _name_server_port;
	char* _network_analyzer;
	int _network_analyzer_socket;
	set<string> _hosts;
	vector<host_pair> _host_pairs;
	vector<RemosLinkData> _link_data_vector;
	char* _NB_data;
};

#endif

/*********** End of Code for network-broker.h ************/

/*****************************************************************************/
