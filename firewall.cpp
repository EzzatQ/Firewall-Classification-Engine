
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include "firewallRules.hpp"
#include <filesystem> // C++17 standard header file name

namespace fs = std::__fs::filesystem;
using namespace std;

#define ARG_NUM 3
#define RULE_PARTS_NUM 3
#define INCOMING_PARTS_NUM 2
#define IP_PARTS_NUM 4
#define IP_PART_MAX 255
#define IP_PART_MIN 0

vector<string> explode(const string& s, char c){
	string buff{""};
	vector<string> v;
	
	for(auto n : s){
		if(n != c) {
			buff += n;
		} else {
			if(n == c && buff != ""){
				v.push_back(buff);
				buff = "";
				
			}
		}
	}
	if(buff != "") v.push_back(buff);
	return v;
}

bool checkIP(string& ip){
	vector<string> ipv4 = explode(ip, '.');
	if(ipv4.size() < IP_PARTS_NUM) return false;
	for(int i = 0; i < IP_PARTS_NUM; i++){
		int num = stoi(ipv4[i]);
		if(num < IP_PART_MIN || num > IP_PART_MAX)
			return false;
	}
	return true;
}

bool checkRule(vector<string>& parts){
	if(parts.size() != RULE_PARTS_NUM) return false;
	if(parts[2] != "allow" && parts[2] != "deny") return false;
	if(!checkIP(parts[1])) return false;
	return true;
}

bool checkIncoming(vector<string>& parts){
	if(parts.size() != INCOMING_PARTS_NUM) return false;
	if(!checkIP(parts[1])) return false;
	return true;
}

void processRules(FirewallRules& rules, ifstream& file){
	vector<string> parts;
	string line;
	int  lineNum = 1;
	while(getline(file, line)){
		parts = explode(line, '|');
		if(!checkRule(parts)){
			cerr << "Rule Format Error: rule in line " << lineNum << " is not in the expected format" << endl;
			cerr << "Expected format is: <source-username>|<destination-ip-address>|<allow/deny>" << endl;
			continue;
		}
		bool allowed = parts[2] == "allow" ? true : false;
		rules.insert(parts[0], parts[1], allowed);
		lineNum++;
	}
}

void processPackets(FirewallRules& rules, vector<string>& packets){
	for(const string& packetFileName : packets){
		ifstream packetFile(packetFileName);
		if(packetFile.fail()){
			cerr << "File Error: could not open " << packetFileName << endl;
			continue;
		}
		vector<string> parts;
		int  lineNum = 1;
		string line;
		while(getline(packetFile, line)){
			parts = explode(line, '|');
			if(!checkIncoming(parts)){
				cerr << "Rule Format Error: rule in file " << packetFileName << ", line " << lineNum << " is not in the expected format" << endl;
				cerr << "Expected format is: <source-username>|<destination-ip-address>" << endl;
				lineNum++;
				continue;
			}
			string allowed = rules.isAllowed(parts[0], parts[1]) ? "allowed" : "denied";
			string host = explode(packetFileName, '/').back();
			cout << host << ": " << parts[0] << " access to " << parts[1] << " was " << allowed << endl;
			lineNum++;
		}
		packetFile.close();
	}
}

int main(int argc, char* argv[]){
    if(argc < ARG_NUM || argc > ARG_NUM){
        cerr << "Invalid Input: Expected " << ARG_NUM - 1 << " arguments, got " << argc - 1 << endl;
        exit(-1);
    }

	ifstream rulesFile(argv[1]);
    if(rulesFile.fail()){
        cerr << "FileError: could not open " << argv[1] << endl;
        exit(-1);
    }
    vector<string> packets;
	try{
		for (const auto& entry : fs::directory_iterator(argv[2])){
			packets.push_back(entry.path());
			//cout << entry.path() << endl;
		}
	} catch(fs::filesystem_error& e){
		cerr << "Invalid Input: " << argv[2] << " does not exist or is not a directory" << endl;
	}
        
    if(packets.size() == 0){
        cout << "There are no packet files to process" << endl;
        exit(-1);
    }
	FirewallRules rules;
	processRules(rules, rulesFile);
	processPackets(rules, packets);
	
	
	
	
	rulesFile.close();
	return 1;
}
