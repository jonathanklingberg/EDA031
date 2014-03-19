#include "newsclient.h"
#include "protocol.h"

#include <string>
#include <iostream>

using namespace std;

Newsclient::Newsclient(string hostname,int portnumber) : host(hostname),port(portnumber) {}

Newsclient::bool validate_input(int& command,string& param) {
    switch (command) {
        case 1:
            if(param == )
            break;
            
        default:
            break;
    }
}

int main() {
    Newsclient ns("localhost",1000);
    while(true) {
        string line;
        while(getline(cin,line)) {
            auto pos = line.find(" ");
            auto pos2 = line.find(" ",pos+1);
            string command = line.substr(0,pos2);
            string parameters = line.substr(pos2+1);
            if(command == ns.help) {
                for(string com : ns.list_commands()) {
                    cout << com <<endl;
                }
            } else if(command == ns.list) {
                map<int,string> groups = cch.listGroups();
                for(auto& g : groups) {
                    cout << g.first<< " " << g.second<<endl;
                }
            } else if(command == ns.create_group) {
                if(cch.addGroup(parameters) == Protocol::ERR_NG_ALREADY_EXISTS) {
                    cerr << "newsgroup already exists!"<<endl;
                }
            } else if(command == ns.delete_group) {
                int param = stoi(parameters);
                if(cch.remGroup(param) == Protocol::ERR_NG_DOES_NOT_EXIST) {
                    cerr << "newsgroup does not exist!" <<endl;
                }
            } else if(command == ns.list_articles) {
                int param = stoi(parameters);
                map<int,string> arts = cch.listArt(param)
                
            } else if(command == ns.create_articles) {
                
            } else if(command == ns.delete_articles) {
                
            } else if(command == ns.get_article) {
                
            } else {
                cout << "error, command does not exist"<<endl;
                exit(1);
            }
        }
    }
}
