//
//  firewallRules.hpp
//  Firewall-Classification-Engine
//
//  Created by Ezzat Qupty on 05/03/2021.
//

#ifndef firewallRules_hpp
#define firewallRules_hpp

#include <iostream>
#include <set>
#include <map>
#include <string>
#include "firewallRules.hpp"
using namespace std;


class PacketRules {
	string ip;
	bool allowed;
public:
	PacketRules(string ip, bool allowed): ip(ip), allowed(allowed){}
	
	string getIP() const {
		return ip;
	}
	
	bool isAllowed() const{
		return allowed;
	}
	
	bool operator<(const PacketRules& p) const {
		return this->ip < p.ip;
	}
	
	bool operator>(const PacketRules& p) const {
		return this->ip > p.ip;
	}
	
	bool operator==(const PacketRules& p) const {
		return this->ip == p.ip;
	}
	
};

typedef map<string, set<PacketRules>> FirewallMap;
typedef pair<string, set<PacketRules>> MapPair;

class FirewallRules {
	FirewallMap rules;
public:
	
	void insert(string username, string ip, bool allowed){
		PacketRules ipRule(ip, allowed);
		FirewallMap::iterator user = rules.find(username);
		if(user == rules.end()){ //username does not exist
			set<PacketRules> userRule;
			userRule.insert(ipRule);
			rules.insert(MapPair(username, userRule));
		} else {//username exists
			set<PacketRules>::iterator packetRule = user->second.find(ipRule);
			if(packetRule != user->second.end()){ // rule for ip has already been defined
				cout << "Rule Redefinition: rule for user: " << username << " and ip: " << ip << " has already been defined" << endl;
			} else { //rule wasn't definned
				user->second.insert(ipRule);
			}
		}
	}
	
	bool isAllowed(string username, string ip){
		PacketRules ipRule(ip, false);
		FirewallMap::iterator user = rules.find(username);
		if(user == rules.end()){
			return true;//if no rules for user, allow
		} else {
			set<PacketRules>::iterator packetRule = user->second.find(ipRule);
			if(packetRule == user->second.end()){
				return true; // no rule for specified ip
			} else {
				return packetRule->isAllowed();
			}
		}
		
	}
};


#endif /* firewallRules_hpp */
