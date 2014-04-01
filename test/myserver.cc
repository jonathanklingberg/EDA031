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
                int groupId;
                int namesize;
                int titlesize;
                int authorsize;
                int textsize;
                vector<NewsGroup> newsgoups = db.listNGs();
                vector<Articles> artlist;
                map<size_t, string> groups;
                switch (command) {
                    case Protocol::COM_LIST_NG: // list newsgroups
                        end_command = sch.readCommand();
                        for(size_t i; i < newsgroups.size(); ++i) {                        	
                        	groups.insert(make_pair(newsgroups[i].getId(), newsgroups[i].getTitle()));
                        }
                        sch.writeAnswer(Protocol::ANS_LIST_NG);
                        sch.writeMap(groups);
                        break;
                        
                    case Protocol::COM_CREATE_NG: // create newsgroup
                    	sch.readCommand(); //PAR_STRING
                    	namesize = sch.readNumber();
                    	string groupName = smh.readString(namesize);
                    	//int res = db.addGroup(groupId);
                    	end_command = sch.readCommand();                  
                    	db.createNG(groupName);
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
                        groupId = sch.readNumber();
                        sch.readCommand();
                        
                        sch.writeAnswer(Protocol::ANS_DELETE_NG);
                        if(db.removeNG(groupId)){               // Anropa databas metod
                            sch.writeAnswer(Protocol::ANS_ACK);
                        }else{
                            sch.writeAnswer(Protocol::ANS_NAK);
                            sch.writeAnswer(Protocol::ERR_NG_DOES_NOT_EXIST);
                        }
                        break;
                        
                    case Protocol::COM_LIST_ART: // list articles
                        sch.readCommand(); //PAR_NUM
                        groupId = sch.readNumber();   //dvs newsgroup ID
                        sch.readCommand(); //COM_END
                        
                        sch.writeAnswer(Protocol::ANS_LIST_ART);
                         if(find_if(newsgroups.begin(), newsgroups.end(), [string groupName](NewsGroup ng){ return ng.getId() == groupId}) {
                            sch.writeAnswer(Protocol::ANS_ACK);	
                            vector<Article> articles = db.listArticles(groupId);
                            sch.writeAnswer(Protocol::PAR_NUM);
                            sch.writeNumber(articles.size());                 //Antal artiklar
                            for(size_t i = 0; i < articles.size(); ++i) {
                            	sch.writeAnswer(Protocol::PAR_NUM);
                            	sch.writeNumber(articles[i].getId());
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
                        	groupId = sch.readNumber();   // N 
                        	sch.readCommand(); // PAR_STRING
                        	titlesize = sch.readNumber();  
                        	string title = smh.readString(titlesize);   // läser in titel
                        	sch.readCommand();
                        	authorsize = sch.readNumber();
                        	string author = smh.readString(authorsize);
                        	sch.readCommand();
                        	textsize = sch.readNumber();
                        	string text = smh.readString();
                        	Article art(title, author, text);
                        	sch.readCommand(); // COM_END
                        	sch.writeAnswer(Protocol::ANS_CREATE_ART);
                        	if(db.addArticle(groupId, art){               // Anropa databas metod
                            		sch.writeAnswer(Protocol::ANS_ACK);
                       	 	}else{
                            		sch.writeAnswer(Protocol::ANS_NAK);
                            		sch.writeAnswer(Protocol::ERR_NG_DOES_NOT_EXIST);
                        	}                        	                       	                       	
                        break;
                        
                    case Protocol::COM_DELETE_ART: // delete article
                        	sch.readCommand(); // PAR_NUM
                        	groupId = sch.readNumber();
                        	sch.readCommand() // PAR_NUM
                        	int artId = sch.readNumber();
                        	sch.readCommand(); // COM_END
                        	sch.writeAnswer(Protocol::ANS_DELETE_ART);
                        	if(removeArticle(groupId, artId)) {
                        		sch.writeAnwer(Protocol::ANS_ACK);
                        	}else{
                        		sch.writeAnswer(Protocol::ANS_NAK);
                        		sch.writeAnswer(Protocol::ERR_NG_DOES_NOT_EXIST);
                        	}			
                        break;
                        
                    case COM_GET_ART: //get article
                    	sch.readCommand(); // PAR_NUM
                        groupId = sch.readNumber();
                        sch.readCommand() // PAR_NUM
                        int artId = sch.readNumber();
                        sch.readCommand(); // COM_END
                        sch.writeCommand(Protocol::ANS_GET_ART);
                        artlist = db.listArticles(groupId);
                        if(find_if(artlist.begin(), artlist.end(), [int artId](Article art){ return art.getId() == artId}) {
                        	sch.writeAnswer(Protocol::ANS_ACK);
                        	sch.writeAnswer(Protocol::PAR_STRING); // PAR_STRING
                        	sch.writeNumber(art.getTitle().size());
                        	smh.writeString(art.getTitle());
                        	sch.writeAnswer(Protocol::PAR_STRING); // PAR_STRING
                        	sch.writeNumber(art.getAuthor().size());
                        	smh.writeString(art.getAuthor());
                        	sch.writeAnswer(Protocol::PAR_STRING); // PAR_STRING
                        	sch.writeNumber(art.getText().size());
                        	smh.writeString(art.getText());
                        }else{
                        	sch.writeAnswer(Protocol::ANS_NAK);
                        	sch.writeAnswer(Protocol::ERR_NG_DOES_NOT_EXIST);
                        }
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
