//
//  firewallRules.cpp
//  Firewall-Classification-Engine
//
//  Created by Ezzat Qupty on 06/03/2021.
//

#include "firewallRules.hpp"
#include <iostream>

PacketRules::PacketRules(string ip, bool allowed){
    this->ip = ip;
    this->allowed = allowed;
}

string PacketRules::getIP() const {
    return ip;
}

bool PacketRules::isAllowed() const{
    return allowed;
}

bool PacketRules::operator<(const PacketRules& p) const {
    return this->ip < p.ip;
}

bool PacketRules::operator>(const PacketRules& p) const {
    return this->ip > p.ip;
}

bool PacketRules::operator==(const PacketRules& p) const {
    return this->ip == p.ip;
}


void FirewallRules::insert(string username, string ip, bool allowed){
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

bool FirewallRules::isAllowed(string username, string ip){
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
