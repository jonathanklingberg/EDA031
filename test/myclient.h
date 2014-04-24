#ifndef MYCLIENT_H
#define MYCLIENT_H

#include "connection.h"
#include "connectionclosedexception.h"
#include "clientcommandhandler.h"
#include "protocol.h"

#include <string>
#include <iostream>
#include <vector>

class Myclient {
    
public:
    
    
    std::vector<std::string> list_commands(){ return commandlist;}
    
    std::vector<std::string> validate_input(std::string& param);
    
    const std::string list = "list newsgroups";
    const std::string create_group = "create newsgroup";
    const std::string delete_group = "delete newsgroup";
    const std::string list_articles = "list articles";
    const std::string create_article = "create article";
    const std::string delete_article = "delete article";
    const std::string get_article = "read article";
    const std::string help = "-h";
    
    const std::string instr = "please see the commands below: write the command followed by any paramaters, end with carriage return";
    const std::string ls_grps = "list newsgroups";
    const std::string new_grp = "create newsgroup [newsgroup title]";
    const std::string del_grp = "delete newsgroup [newsgroup id]";
    const std::string ls_arts = "list articles [newsgroup id]";
    const std::string new_art = "create article [newsgroup id] [title] [author] [text]";
    const std::string del_art = "delete article [newsgroup id] [article id]";
    const std::string get_art = "read article [newsgroup id] [article id]";

    
    std::vector<std::string> commandlist = {instr,ls_grps,new_grp,del_grp,ls_arts,new_art,del_art,get_art};
    
};


#endif