#include "newsclient.h"

#include <string>
#include <iostream>

using namespace std;

Newsclient::Newsclient(string hostname,int port) : host(hostname),port(port) {}


int main() {
    Newsclient ns("localhost",1000);
    while(true) {
        string s;
        while(getline(cin,s)) {
            if(s == ns.help) {
                for(string com: ns.list_commands()) {
                    cout << com<<endl;
                }
            }
        }
    }
}