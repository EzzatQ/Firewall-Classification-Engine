
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem> // C++17 standard header file name
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace std;

int main(int argc, char* argv[]){
    if(argc < 3 || argc > 3){
        cout << "Invalid input: Expected 2 arguments, got " << argc - 1 << endl;
        exit(-1);
    }  
    ifstream rules(argv[1]);
    if(!rules.is_open()){
        cout << "File Error: could not open " << argv[1] << endl;
        exit(-1);
    }
    vector<string> packets;
    for (const string& entry : fs::directory_iterator(argv[2])){
        packets.push_back(entry.path());
        cout << entry.path() << endl;
    }
        
    if(packets.size() == 0){
        cout << "There are no packets to process" << endl;
        exit(-1);
    }
    return 1;
}