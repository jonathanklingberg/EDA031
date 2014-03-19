#ifndef NEWSSERVERINTERFACE_H
#define NEWSSERVERINTERFACE_H

#include "server.h"
#include <string>
#include <vector>

using namespace std;

/* An interface for the in-memory and database newsservers */
class NewsserverInterface {

    public:
    virtual NewsserverInterface(int p): port(p),server(port); //creates a new newsserver interface with port p
    virtual NewsserverInterface(); //creates a new newsserver interface
    virtual ~NewsserverInterface();
    
    virtual vector<> get_newsgroups(int group_id) const; //list all newsgroups
    virtual void create_newsgroup(string& name);
    virtual void delete_newsgroup(int group_id);
    virtual vector<> list_articles(int group_id) const;
    virtual vector<> get_article(int group_id,int article_id) const;
    virtual void create_article(int group_id,string& title,string& author,string& text);
    virtual void delete_article(int group_id,int article_id);

    private:
    Server server;
    MessageHandler msgh;
    int port;
    
};
    
#endif
