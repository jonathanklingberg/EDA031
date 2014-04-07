#include <string>
#include <map>
#include "protocol.h"
#include <iostream>

#include "servercommandhandler.h"

using namespace std;

int ServerCommandHandler::readNumber(){
    return mh.readNumber();
}
unsigned char ServerCommandHandler::readCommand(){
    return mh.readCode();
}
void ServerCommandHandler::writeString(const string& s){
    mh.writeString(s);
}
void ServerCommandHandler::writeMap(map<int, string> groups){
    writeAnswer(Protocol::PAR_NUM);
    writeNumber(groups.size());
    auto beg = groups.begin();
    while( beg != groups.end()){
        writeAnswer(Protocol::PAR_NUM);
        writeNumber( beg->first );
        writeAnswer(Protocol::PAR_STRING);
        writeNumber(beg->second.size());
        writeString( beg->second );
        ++beg;
    }
}

void ServerCommandHandler::writeAnswer(unsigned char ch){
    mh.writeCode(ch);
}
void ServerCommandHandler::writeNumber(int nbr){
    mh.writeNumber(nbr);
}
