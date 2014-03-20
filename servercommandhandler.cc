#include <string>
#include <map>

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
void ServerCommandHandler::writeMap(map<int, string> map){
    mh.writeNumber(map.size());
    auto beg = map.begin();
    while( beg != map.end()){
        mh.writeNumber( beg->first );
        mh.writeString( beg->second );
        ++beg;
    }
}

void ServerCommandHandler::writeAnswer(unsigned char ch){
    mh.writeCode(ch);
}
void ServerCommandHandler::writeNumber(int nbr){
    mh.writeNumber(nbr);
}
