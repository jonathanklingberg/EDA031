#include "newsclient.h"

#include <string>
#include <iostream>

using namespace std;

Newsclient::Newsclient(string hostname,int port) : host(hostname),port(port) {}


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
                cout << "lista lite grupper va"<<endl;
                cout << "parametrar: " << parameters<<endl;
            } else if(command == ns.create_group) {
                
            } else if(command == ns.delete_group) {
                
            } else if(command == ns.list_articles) {
                
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
