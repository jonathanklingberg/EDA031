/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "servercommandhandler.h"
#include "protocol.h"
#include "in_memory.h"
#include "newsgroup.h"
#include "database_interface.h"
#include "article.h"
#include "on_disk.h"

#include <algorithm>
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
	//InMemory db;  // CREATE A DB HERE : Database db();
    OnDisk db;
	while (true) {
        auto conn = server.waitForActivity();
        MessageHandler smh(*conn.get());
        ServerCommandHandler sch(smh);
		if (conn != nullptr) {
			try {
                unsigned char command = sch.readCommand();
                unsigned char end_command;
                bool check = false;   // Används i COM_LIST_ART
                int groupId;
                int namesize;
                int titlesize;
                int authorsize;
                int textsize;
                int artId;
                string groupName;
                vector<NewsGroup> newsgroups;
                vector<Article> artlist;
                map<int, string> groups;
                switch (command) {
                    case Protocol::COM_LIST_NG: // list newsgroup
                        end_command = sch.readCommand();
                        newsgroups = db.listNGs();
                        for(size_t i = 0; i < newsgroups.size(); ++i) {
                        	groups.insert(make_pair(newsgroups[i].getId(), newsgroups[i].getTitle()));
                        }
                        sch.writeAnswer(Protocol::ANS_LIST_NG);
                        sch.writeMap(groups);
                        break;
                        
                    case Protocol::COM_CREATE_NG:{ // create newsgroup
                    	sch.readCommand(); //PAR_STRING
                    	namesize = sch.readNumber();
                    	groupName = smh.readString(namesize);
                    	end_command = sch.readCommand();
                        sch.writeAnswer(Protocol::ANS_CREATE_NG);
                        if(db.createNG(groupName)) {
                            sch.writeAnswer(Protocol::ANS_ACK);
                        }else{
                            sch.writeAnswer(Protocol::ANS_NAK);
                            sch.writeAnswer(Protocol::ERR_NG_ALREADY_EXISTS);
                        }
                    }
                        break;
                    
                        
                    case Protocol::COM_DELETE_NG :{ // deletes a specified newsgroup
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
                    }
                        break;
                        
                    case Protocol::COM_LIST_ART:{ // list articles
                        sch.readCommand(); //PAR_NUM
                        groupId = sch.readNumber();   //dvs newsgroup ID
                        sch.readCommand(); //COM_END
                        
                        sch.writeAnswer(Protocol::ANS_LIST_ART);
                        newsgroups = db.listNGs();  //existing groups
                        for(NewsGroup ng : newsgroups) { 
                        	if(ng.getId() == groupId) {
                        		check = true;
                        	}
                        }
                        if(check) {
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
                    }
                        break;
                        
                    case Protocol::COM_CREATE_ART:{ // create article
                        sch.readCommand();   // PAR_NUM
                        groupId = sch.readNumber();   // N
                        sch.readCommand(); // PAR_STRING
                        titlesize = sch.readNumber();
                        string title = smh.readString(titlesize);
                        sch.readCommand(); // PAR_STRING
                        authorsize = sch.readNumber(); // N
                        string author = smh.readString(authorsize);
                        sch.readCommand(); // PAR_STRING
                        textsize = sch.readNumber(); //N
                        string text = smh.readString(textsize);
                        sch.readCommand(); // COM_END
                        sch.writeAnswer(Protocol::ANS_CREATE_ART);
                        if(db.addArticle(groupId,title,author,text)){               // Anropa databas metod
                            sch.writeAnswer(Protocol::ANS_ACK);
                        }else{
                            sch.writeAnswer(Protocol::ANS_NAK);
                            sch.writeAnswer(Protocol::ERR_NG_DOES_NOT_EXIST);
                        }
                    }
                           break;
                           
                    case Protocol::COM_DELETE_ART: // delete article
                           sch.readCommand(); // PAR_NUM
                           groupId = sch.readNumber();
                           sch.readCommand(); // PAR_NUM
                           artId = sch.readNumber();
                           sch.readCommand(); // COM_END
                           sch.writeAnswer(Protocol::ANS_DELETE_ART);
                           if(db.removeArticle(groupId, artId)) {
                               sch.writeAnswer(Protocol::ANS_ACK);
                           }else{
                               sch.writeAnswer(Protocol::ANS_NAK);
                               sch.writeAnswer(Protocol::ERR_NG_DOES_NOT_EXIST);
                           }
                           break;
                           
                    case Protocol::COM_GET_ART:{ //get article
                           sch.readCommand(); // PAR_NUM
                           groupId = sch.readNumber();
                           sch.readCommand(); // PAR_NUM
                           artId = sch.readNumber();
                           sch.readCommand(); // COM_END
                           sch.writeAnswer(Protocol::ANS_GET_ART);
                           artlist = db.listArticles(groupId);
                           string t, ath, text;                      
                           for(Article a : artlist) {
                           	if(a.getId() == artId) {
                           		check = true;
                           		t = a.getTitle();
                           		ath = a.getAuthor();
                           		text = a.getText();
                           	}
                           }
                           if(check){
                            sch.writeAnswer(Protocol::ANS_ACK);
                            sch.writeAnswer(Protocol::PAR_STRING); // PAR_STRING
                            sch.writeNumber(t.size());
                            smh.writeString(t);
                            sch.writeAnswer(Protocol::PAR_STRING); // PAR_STRING
                            sch.writeNumber(ath.size());
                            smh.writeString(ath);
                            sch.writeAnswer(Protocol::PAR_STRING); // PAR_STRING
                            sch.writeNumber(text.size());
                            smh.writeString(text);
                        }else{
                            sch.writeAnswer(Protocol::ANS_NAK);
                            sch.writeAnswer(Protocol::ERR_NG_DOES_NOT_EXIST);
                        }
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
