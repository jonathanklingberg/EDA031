#include "myclient.h"
#include "protocol.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <map>

using namespace std;


vector<string> Myclient::validate_input(string& param) {
    vector<string> res;
    int position;
    for(auto i = param.begin(); i != param.end(); i += position) {
        auto pos = param.find(" ");
        position = pos;
        string s = param.substr(*i,pos);
        res.push_back(s);
    }
    return res;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Connection conn(argv[1], port);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
    MessageHandler mh(conn);
    ClientCommandHandler cch(mh);
    
	cout << "enter a command, type -h for help: ";
  
    Myclient ns; // creates a Myclient, used to check commands
    while(true) {
        string line;
        while(getline(cin,line)) {
            try {
            auto pos = line.find(" ");
            auto pos2 = line.find(" ",pos+1);
            string command = line.substr(0,pos2);
            string parameters = line.substr(pos2+1);
            if(command == ns.help) {
                for(string com : ns.list_commands()) {
                    cout << com <<endl;
                }
            } else if(command == ns.list) {
                cout << "HEJ FÖR FAN!"<<endl;
                map<int,string> groups = cch.listGroups();
                for(auto& g : groups) {
                    cout << g.first<< " " << g.second<<endl;
                }
            } else if(command == ns.create_group) {
                if(cch.createGroup(parameters) == false) {
                    cerr << "newsgroup already exists!"<<endl;
                }
            } else if(command == ns.delete_group) {
                int param = stoi(parameters);
                if(cch.deleteGroup(param) == false) {
                    cerr << "newsgroup does not exist!" <<endl;
                }
//            } else if(command == ns.list_articles) {
//                int param = stoi(parameters);
//                map<int,string> arts = cch.listArt(param);
//                for(auto& a : arts) {
//                    cout << a.first<<" "<<a.second<<endl;
//                }
//            } else if(command == ns.create_articles) {
//                vector<string> v = ns.validate_input(parameters);
//                if(v.size() != 4) {
//                    cerr << "invalid input"<<endl;
//                }
//                int id = stoi(v[0]);
//                if(cch.addArt(id,v[1],v[2],v[3]) == ERR_NG_DOES_NOT_EXIST) {
//                    cerr<< "newsgroup does not exist!"<<endl;
//                }
//                
//            } else if(command == ns.delete_articles) {
//                vector<string> v = ns.validate_input(parameters);
//                if(v.size() != 2) {
//                    cerr << "invalid input"<<endl;
//                }
//                int id = stoi(v[0]);
//                if(cch.remArt(id,v[1]) == ERR_ART_DOES_NOT_EXIST) {
//                    cerr<<"Article does not exist!"<<endl;
//                }
//                
//            } else if(command == ns.get_article) {
//                vector<string> v = ns.validate_input(parameters);
//                if(v.size() != 2) {
//                    cerr<<"Invalid input!"<<endl;
//                }
//                int id = stoi(v[0]);
//                int id2 = stoi(v[1]);
//                vector<string> res = cch.getArt(id,id2);
//                cout<< res[0]<<" "<<res[1]<<endl;
                
            } else {
                cout << "error, command does not exist"<<endl;
                exit(1);
            }
            }catch(ConnectionClosedException&) {
               cerr << " no reply from server. Quitting." << endl;
                exit(1);
            }
        }
    }
}

