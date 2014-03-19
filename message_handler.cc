#include "message_handler.h"

MessageHandler::void sendByte(int nbr){
    try{
        conn.write((char) nbr);
    }catch( exception e){
        throw e;
    }
}


MessageHandler::unsigned char readByte(){
    unsigned char code = conn.read();
    if (code == Connection.CONNECTION_CLOSED) {
        throw new ConnectionClosedException();
    }
    return code;
}