#include "newsclient.h"
#include "protocol.h"

#include <string>
#include <iostream>

using namespace std;

Newsclient::Newsclient(string hostname,int portnumber) : host(hostname),port(portnumber) {}

Newsclient::vector<string> validate_input(string& param) {
    vector<string> res;
    for(auto i = param.begin(), i != param.end(); i = pos+1) {
        auto pos = param.find(" ");
        string s = param.substr(i,pos);
        res.push_back(s);
    }
    return res;
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
                map<int,string> arts = cch.listArt(param);
                for(auto& a : arts) {
                    cout << a.first<<" "<<a.second<<endl;
                }
            } else if(command == ns.create_articles) {
                vector<string> v = ns.validate_input(parameters);
                if(v.size() != 4) {
                    cerr << "invalid input"<<endl;
                }
                int id = stoi(v[0]);
                if(cch.addArt(id,v[1],v[2],v[3]) == ERR_NG_DOES_NOT_EXIST) {
                    cerr<< "newsgroup does not exist!"<<endl;
                }
                
            } else if(command == ns.delete_articles) {
                vector<string> v = ns.validate_input(parameters);
                if(v.size() != 2) {
                    cerr << "invalid input"<<endl;
                }
                int id = stoi(v[0]);
                if(cch.remArt(id,v[1]) == ERR_ART_DOES_NOT_EXIST) {
                    cerr<<"Article does not exist!"<<endl;
                }
                
            } else if(command == ns.get_article) {
                vector<string> v = ns.validate_input(parameters);
                if(v.size() != 2) {
                    cerr<<"Invalid input!"<<endl;
                }
                int id = stoi(v[0]);
                int id2 = stoi(v[1]);
                vector<string> res = cch.getArt(id,id2);
                cout<< res[0]<<" "<<res[1]<<endl;
                
            } else {
                cout << "error, command does not exist"<<endl;
                exit(1);
            }
        }
    }
}
