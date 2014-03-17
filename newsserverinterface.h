#ifndef NEWSSERVERINTERFACE_H
#define NEWSSERVERINTERFACE_H

#include "server.h"

/* An interface for the in-memory and database newsservers */
class NewsserverInterface {

    public:
    virtual NewsserverInterface(int port):
    virtual NewsserverInterface();
    virtual ~NewsserverInterface();
    
    


    private:
    Server server;
    MessageHandler msgh;
    
};
    
#endif
