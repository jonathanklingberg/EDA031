#include "myclient.h"
#include "protocol.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;


vector<string> Myclient::validate_input(string& param) {
    istringstream iss(param);
    vector<string> res{istream_iterator<string>{iss},
         istream_iterator<string>{}};
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
    
	cout << "Enter a command, type -h for help: ";
  
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
                map<int,string> groups = cch.listGroups();
                if(groups.size() == 0){
                    cout << "There are no newsgroups!"<<endl;
                }
                for(auto& g : groups) {
                    cout << g.first<< " " << g.second<<endl;
                }
            } else if(command == ns.create_group) {
                if(cch.createGroup(parameters) == true) {
                    cout << "Newsgroup created"<<endl;
                }else{
                    cout << "Newsgroup already exists!"<<endl;
                }
            } else if(command == ns.delete_group) {
                int param = stoi(parameters);
                if(cch.deleteGroup(param) == false) {
                    cerr << "Newsgroup does not exist!" <<endl;
                }
            } else if(command == ns.list_articles) {
                int param = stoi(parameters);
                map<int,string> arts = cch.listArts(param);
                if(arts.empty()){
                    cout << "There are no articles in newsgroup!"<<endl;
                }
                for(auto& a : arts) {
                    cout << a.first<<" "<<a.second<<endl;
                }
            } else if(command == ns.create_article) {
                vector<string> v = ns.validate_input(parameters);
                if(v.size() != 4) {
                    cout << "Invalid input!"<<endl;
                }
                int id = stoi(v[0]);
                if(cch.createArt(id,v[1],v[2],v[3])) {
                    cout << "Article created"<<endl;
                }else{
                cout<< "Newsgroup does not exist!"<<endl;
                }
            } else if(command == ns.delete_article) {
                vector<string> v = ns.validate_input(parameters);
                if(v.size() != 2) {
                    cerr << "Invalid input"<<endl;
                }
                int id = stoi(v[0]);
                int art_nbr = stoi(v[1]);
                if(cch.deleteArt(id,art_nbr)) {
                    cout << "Article was deleted"<<endl;
                }else{
                    cout<<"Article does not exist!"<<endl;
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
                cout << "Error, command does not exist!"<<endl;
                exit(1);
            }
            }catch(ConnectionClosedException&) {
               cerr << "No reply from server. Quitting." << endl;
                exit(1);
            }
        }
    }
}

