

#include "message_handler.h"

using namespace Protocol;

Message_handler::Message_handler(conn) {

}

Message_handler::void read() {
    char ch;
    ch = conn.read();
    switch (ch) {
        case COM_LIST_NG: // list newsgroups
            list_NGs();
            break;
        case COM_CREATE_NG: // create newsgroup
        
            break;
            
        case COM_LIST_ART: // list articles
            break;
            
            
        case COM_CREATE_ART: // create article
            break;
            
        case COM_DELETE_ART: // delete article
            
            break;
            
        case COM_GET_ART: //get article
            break;
            
        default:
            break;
    }
}

Message_handler::void list_NGs() {
    
    
}