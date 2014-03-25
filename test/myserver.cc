/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "servercommandhandler.h"
#include "protocol.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
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
        MessageHandler smh(*conn.get());
        ServerCommandHandler sch(smh);
        // CREATE A DB HERE : Database db();
		if (conn != nullptr) {
			try {
                unsigned char command = sch.readCommand();
                unsigned char end_command;
                map<int, string> groups;
                cout << "Server received command: " << static_cast<unsigned>(command) << endl;
                // DONT FORGET TO READ END COMMAND INSIDE SWITH_CASE
                switch (command) {
                    case Protocol::COM_LIST_NG: // list newsgroups
                        cout << "inside the correct case" << endl;
                        end_command = sch.readCommand();
                        cout << "And end_command: " << static_cast<unsigned>(end_command) << endl;
                        // check endcommand...
//                      map<int, sting> groups = db.listNgs();               
                        groups.insert(make_pair(0,"C++ gruppen"));
                        groups.insert(make_pair(1,"Java gruppen"));
                        sch.writeAnswer(Protocol::ANS_LIST_NG);
                       // sch.writeAnswer(Protocol::PAR_NUM);
                        //sch.writeNumber(groups.size());
                        sch.writeMap(groups);
                    break;
//                    case Protocol::COM_CREATE_NG: // create newsgroup
//                    	string groupName = smh.readString();
//                    	//int res = db.addGroup(groupId);
//                    	end_command = sch.readCommand();
//                    	map<int, string> db;                      // fake db
//                    	db.insert(make_pair(0, groupName));
//                    	cout << "db atm: " << endl;
//    			for(auto it = db.cbegin(); it != db.cend(); ++it){
//        		std::cout << it->first << " " << it->second << "\n";
//    			}	
//                    	sch.writeAnswer(Protocol::ANS_CREATE_NG);
//                    	sch.writeAnswer(Protocol::ANS_ACK);		   // om namnet finns ska nak returneras
//                    break;
//                            case Protocol::COM_DELETE_NG : // deletes a specified newsgroup
//                                int groupId = mh.readByte();
//                                int res = db.getRem(groupId);
//                                sch.sendMap(res);
//                                break;
//                            case Protocol::COM_LIST_ART: // list articles
//                                break;
//                                
//                            case Protocol::COM_CREATE_ART: // create article
//                                
//                                break;
//                                
//                            case Protocol::COM_DELETE_ART: // delete article
//                                int artId = mh.readByte();
//                                int error = db.remArt(artId);
//                                sch.sendRem(error);
//                                break;
//                                
//                            case COM_GET_ART: //get article
//                                break;
//                            default:
//                                break;
                }
                sch.writeAnswer(Protocol::ANS_END);

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
