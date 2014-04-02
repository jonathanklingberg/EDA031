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
    cout<<"vi skriver maps nu för satan i sch"<<endl;
    writeAnswer(Protocol::PAR_NUM);
    writeNumber(groups.size());
    auto beg = groups.begin();
    while( beg != groups.end()){
        writeAnswer(Protocol::PAR_NUM);
        writeNumber( beg->first );
        cout<<beg->first<<"det där var första siffran"<<endl;
        writeAnswer(Protocol::PAR_STRING);
        writeNumber(beg->second.size());
        cout<<beg->second.size()<<"storleken på strängen"<<endl;
        writeString( beg->second );
        cout<<beg->second<<"gruppnamnet"<<endl;
        ++beg;
    }
}

void ServerCommandHandler::writeAnswer(unsigned char ch){
    mh.writeCode(ch);
}
void ServerCommandHandler::writeNumber(int nbr){
    mh.writeNumber(nbr);
}
