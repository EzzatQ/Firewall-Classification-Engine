//
//  firewallRules.hpp
//  Firewall-Classification-Engine
//
//  Created by Ezzat Qupty on 05/03/2021.
//

#ifndef firewallRules_hpp
#define firewallRules_hpp


#include <set>
#include <map>
#include <string>
#include "firewallRules.hpp"
using namespace std;


class PacketRules {
	string ip;
	bool allowed;
public:
    PacketRules(string ip, bool allowed);
    string getIP() const;
    bool isAllowed() const;
	bool operator<(const PacketRules& p) const;
    bool operator>(const PacketRules& p) const;
    bool operator==(const PacketRules& p) const;
};

typedef map<string, set<PacketRules>> FirewallMap;
typedef pair<string, set<PacketRules>> MapPair;

class FirewallRules {
	FirewallMap rules;
public:
	
    void insert(string username, string ip, bool allowed);
    bool isAllowed(string username, string ip);
};


#endif /* firewallRules_hpp */
