/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "clientcommandhandler.h"
#include "protocol.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <map>

using namespace std;

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
	cout << "Type a number: ";
	int nbr;
    // Test for listgroup
    // IMPLEMENT YOUR OWN CLI HERE!!
	while (cin >> nbr) {
		try {
			cout << nbr << " is ...";
            map<int, string> groups = cch.listGroups();
			cout << "Type another number: ";
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}

