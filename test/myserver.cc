/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){

	if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}
	
	while (true) {
		auto conn = server.waitForActivity();

		if (conn != nullptr) { // incoming message
            MessageHandler mh(conn);
            CommandHandler ch(mh);
			try {
				char c = mh.readByte();
                switch (c) {
                    case COM_LIST_NG: // list newsgroups
                        map<int, sting> groups = db.listNgs();
                        ch.sendMap(groups);
                        break;
                    case COM_CREATE_NG: // create newsgroup
                        int groupId = mh.readByte();
                        int res = db.addGroup(groupId);
                        ch.sendAns(res);
                        break;
                    case COM_DELETE_NG : // deletes a specified newsgroup
                        int groupId = mh.readByte();
                        int res = db.getRem(groupId);
                        ch.sendMap(res);
                        break;
                    case COM_LIST_ART: // list articles
                        break;
                        
                    case COM_CREATE_ART: // create article
                        
                        break;
                        
                    case COM_DELETE_ART: // delete article
                        int artId = mh.readByte();
                        int error = db.remArt(artId);
                        ch.sendRem(error);
                        break;
                        
                    case COM_GET_ART: //get article
                        break;
                    default:
                        break;
                }
                
//
//                int addGroup(string name); // create a new newsgroup
//                vector<string> listArt(int groupId); // list all articles to specific group
//                int remArt(int groupIndex, int articleIndex); // remove a secific article
//                vector<string> getArt(int groupId, int artId); // get a specific article
//                int addArt(int groupIndex, string name, string author,
//                           string text); // create new article
                
                
                
                conn.read();
                
//				string result;
//				if (nbr > 0) {
//					result = "positive";
//				} else if (nbr == 0) {
//					result = "zero";
//				} else {
//					result = "negative";
//				}
				writeString(conn, result);
			} catch (ConnectionClosedException&) {
				server.deregisterConnection(conn);
				cout << "Client closed connection" << endl;
			}
		} else {
			conn = make_shared<Connection>();
			server.registerConnection(conn);
			cout << "New client connects" << endl;
		}
	}
}
