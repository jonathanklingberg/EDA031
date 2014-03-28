/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "servercommandhandler.h"
#include "protocol.h"
#include "in_memory.h"
#include "newsgroup.h"
#include "database_interface.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <vector>

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
        DatabaseInterface db();  // CREATE A DB HERE : Database db();
		if (conn != nullptr) {
			try {
                unsigned char command = sch.readCommand();
                unsigned char end_command;
                vector<NewsGroup> newsgoups = db.listNGs();
                map<size_t, string> groups;
                switch (command) {
                    case Protocol::COM_LIST_NG: // list newsgroups
                        end_command = sch.readCommand();
                        // check endcommand...
                        //sch.writeAnswer(Protocol::PAR_NUM);
                        //sch.writeNumber(newsgroups.size());    // Antal newsgroups
                        for(size_t i; i < newsgroups.size(); ++i) {                        	
                        	groups.insert(make_pair(newsgroups[i].getId(), newsgroups[i].getTitle()));
                        }
                        sch.writeAnswer(Protocol::ANS_LIST_NG);
                        sch.writeMap(groups);
                        break;
                    case Protocol::COM_CREATE_NG: // create newsgroup
                    	sch.readCommand(); //PAR_STRING
                    	int namesize = sch.readNumber();
                    	string groupName = smh.readString(namesize);
                    	//int res = db.addGroup(groupId);
                    	end_command = sch.readCommand();                  
                    	db.createNG(groupName);
                        //                    	cout << "db atm: " << endl;
                        //    			for(auto it = db.cbegin(); it != db.cend(); ++it){
                        //        		std::cout << it->first << " " << it->second << "\n";
                        //    			}
                        sch.writeAnswer(Protocol::ANS_CREATE_NG);
                        if (find_if(newsgroups.begin(), newsgroups.end(), [string groupName](NewsGroup ng){ return ng.getTitle() != groupName}) {  //lambda
                            Newsgroup ng(groupName);
                            db.createNG(ng);
                            sch.writeAnswer(Protocol::ANS_ACK);
                        }else{
                        sch.writeAnswer(Protocol::ANS_NAK);
                        sch.writeAnswer(Protocol::ERR_NG_ALREADY_EXISTS);
                        }
                        break;
                        
                    case Protocol::COM_DELETE_NG : // deletes a specified newsgroup
                        sch.readCommand();
                        int groupId = sch.readNumber();
                        sch.readCommand();
                        
                        sch.writeAnswer(Protocol::ANS_DELETE_NG);
                        //NewsGroup romove_group;
                        /*
                     	for(size_t i = 0; i < newsgroups.size(); ++i) {
                     		if(newsgroups[i].getId() == groupId) {
                     			remove_group = newsgroups[i];
                     		}
                        }
               		*/
                        if(db.removeNG(groupId)){               // Anropa databas metod
                            sch.writeAnswer(Protocol::ANS_ACK);
                        }else{
                            sch.writeAnswer(Protocol::ANS_NAK);
                            sch.writeAnswer(Protocol::ERR_NG_DOES_NOT_EXIST);
                        }
                        break;
                    case Protocol::COM_LIST_ART: // list articles
                        sch.readCommand(); //PAR_NUM
                        int groupId = sch.readNumber();   //dvs newsgroup ID
                        sch.readCommand(); //COM_END
                        
                        sch.writeAnswer(Protocol::ANS_LIST_ART);
                         if(find_if(newsgroups.begin(), newsgroups.end(), [string groupName](NewsGroup ng){ return ng.getId() == groupId}) {
                            sch.writeAnswer(Protocol::ANS_ACK);	
                            vector<Article> articles = db.listArticles(groupId);
                            sch.writeAnswer(Protocol::PAR_NUM);
                            sch.writeNumber(articles.size());                 //Antal artiklar
                            for(size_t i = 0; i < articles.size(); ++i) {
                            	sch.writeAnswer(Protocol::PAR_NUM);
                            	sch.writeNumber(i);
                            	sch.writeAnswer(Protocol::PAR_STRING);
                            	sch.writeNumber(articles[i].getTitle().size());
                            	sch.writeString(articles[i].getTitle());
                            }         
                        }else{
                            sch.writeAnswer(Protocol::ANS_NAK);
                            sch.writeAnswer(Protocol::ERR_NG_DOES_NOT_EXIST);
                        }
                        break;
                        
                    case Protocol::COM_CREATE_ART: // create article
                        	sch.readCommand();   // PAR_NUM
                        	int groupId = sch.readNumber();   // N 
                        	sch.readCommand(); // PAR_STRING
                        	
                        	
                        break;
                        
                    case Protocol::COM_DELETE_ART: // delete article
                        int artId = mh.readByte();
                        int error = db.remArt(artId);
                        sch.sendRem(error);
                        break;
                        
                    case COM_GET_ART: //get article
                        break;
                    default:
                        break;
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
