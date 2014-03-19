#ifndef NEWSCLIENT_H
#define NEWSCLIENT_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Newsclient {
    
    public:
    
    Newsclient(string host,int port);
    
    vector<string> list_commands(){ return commandlist;}
    
    const string instructions = "please see the commands below: write the command followed by white space and any paramaters on one line, end with carriage return";
    const string list = "list newsgroups";
    const string create_group = "create newsgroup";
    const string delete_group = "delete newsgroup";
    const string list_articles = "list articles";
    const string create_articles = "create article";
    const string delete_articles = "delete article";
    const string get_article = "read article";
    const string help = "-h";
    
    vector<string> commandlist = {instructions,list,create_group,delete_group,list_articles,create_articles,delete_articles,get_article};
    
private:
    
    //Message_handler msghandler;
    string host;
    int port;
    
};


#endif