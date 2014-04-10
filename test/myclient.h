#ifndef MYCLIENT_H
#define MYCLIENT_H

#include "connection.h"
#include "connectionclosedexception.h"
#include "clientcommandhandler.h"
#include "protocol.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Myclient {
    
public:
    
    
    vector<string> list_commands(){ return commandlist;}
    
    vector<string> validate_input(string& param);
    
    const string instructions = "please see the commands below: write the command followed by white space and any paramaters on one line, end with carriage return";
    const string list = "list newsgroups";
    const string create_group = "create newsgroup";
    const string delete_group = "delete newsgroup";
    const string list_articles = "list articles";
    const string create_article = "create article";
    const string delete_article = "delete article";
    const string get_article = "read article";
    const string help = "-h";
    
    vector<string> commandlist = {instructions,list,create_group,delete_group,list_articles,create_article,delete_article,get_article};
    
};


#endif