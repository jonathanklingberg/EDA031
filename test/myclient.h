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
    
    const string list = "list newsgroups";
    const string create_group = "create newsgroup";
    const string delete_group = "delete newsgroup";
    const string list_articles = "list articles";
    const string create_article = "create article";
    const string delete_article = "delete article";
    const string get_article = "read article";
    const string help = "-h";
    
    const string instr = "please see the commands below: write the command followed by any paramaters, end with carriage return";
    const string ls_grps = "list newsgroups";
    const string new_grp = "create newsgroup [newsgroup title]";
    const string del_grp = "delete newsgroup [newsgroup id]";
    const string ls_arts = "list articles [newsgroup id]";
    const string new_art = "create article [newsgroup id] [title] [author] [text]";
    const string del_art = "delete article [newsgroup id] [article id]";
    const string get_art = "read article [newsgroup id] [article id]";

    
    vector<string> commandlist = {instr,ls_grps,new_grp,del_grp,ls_arts,new_art,del_art,get_art};
    
};


#endif