#include "myclient.h"
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
                string parameters;
                if(line.size() == command.size()){
                    parameters = "";
                }else{
                    parameters = line.substr(pos2+1);
                }
                if(command == ns.list && parameters.empty()) {
                    map<int,string> groups = cch.listGroups();
                    if(groups.size() == 0){
                        cout << "There are no newsgroups!"<<endl;
                    }
                    for(auto& g : groups) {
                        cout << g.first<< " " << g.second<<endl;
                    }
            } else if(command == ns.help && parameters.empty()) {
                for(string com : ns.list_commands()) {
                    cout << com <<endl;
                }
            } else if(command == ns.create_group && !parameters.empty()) {
                if(cch.createGroup(parameters)) {
                    cout << "Newsgroup created"<<endl;
                }else{
                    cout << "Newsgroup already exists!"<<endl;
                }
            } else if(command == ns.delete_group && !parameters.empty()) {
                int param = stoi(parameters);
                if(cch.deleteGroup(param)) {
                    cout<<"Newsgroup deleted"<<endl;
                }else{
                    cerr << "Newsgroup does not exist!" <<endl;
                }
            } else if(command == ns.list_articles && !parameters.empty()) {
                int param = stoi(parameters);
                map<int,string> arts = cch.listArts(param);
                if(arts.empty()){
                    cout << "There are no articles in newsgroup!"<<endl;
                }
                for(auto& a : arts) {
                    cout << a.first<<" "<<a.second<<endl;
                }
            } else if(command == ns.create_article && !parameters.empty()) {
                vector<string> v = ns.validate_input(parameters);
                if(v.size() < 4) {
                    cout << "Invalid input!"<<endl;
                }
                int id = stoi(v[0]);
                string text;
                for(size_t i = 3; i < v.size(); ++i){
                    text +=v[i];
                    text +=" ";
                }
                if(cch.createArt(id,v[1],v[2],text)) {
                    cout << "Article created"<<endl;
                }else{
                    cout<< "Newsgroup does not exist!"<<endl;
                }
            } else if(command == ns.delete_article && !parameters.empty()) {
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
                
            } else if(command == ns.get_article && !parameters.empty()) {
                vector<string> v = ns.validate_input(parameters);
                if(v.size() < 2) {
                    cerr<<"Invalid input!"<<endl;
                }
                int id = stoi(v[0]);
                int id2 = stoi(v[1]);
                vector<string> res = cch.getArt(id,id2);
                if(res.empty()){
                    cout<<"Article does not exist!"<<endl;
                }
                for(size_t i = 0; i < res.size(); ++i) {
                    cout<< res[i]<<" ";
                }
                cout<<endl;
            } else {
                cout << "Error, command does not exist!"<<endl;
                cout << "Please try again"<<endl;
                for(string com : ns.list_commands()) {
                    cout << com <<endl;
                }
            }
        }catch(ConnectionClosedException&) {
            cerr << "No reply from server. Quitting." << endl;
            exit(1);
        }
    }
}
}

