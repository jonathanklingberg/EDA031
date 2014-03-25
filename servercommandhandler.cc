#include <string>
#include <map>
#include "protocol.h"

#include "servercommandhandler.h"

using namespace std;

int ServerCommandHandler::readNumber(){     //ska vi använda denna?
    return mh.readNumber();
}
unsigned char ServerCommandHandler::readCommand(){     //ska vi använda denna?
    return mh.readCode();
}
void ServerCommandHandler::writeString(const string& s){      //ska vi använda denna?
    mh.writeString(s);
}
void ServerCommandHandler::writeMap(map<int, string> map){
    mh.writeCode(Protocol::PAR_NUM);
    mh.writeNumber(map.size());
    auto beg = map.begin();
    while( beg != map.end()){
        mh.writeCode(Protocol::PAR_NUM);
        mh.writeNumber( beg->first );
        mh.writeCode(Protocol::PAR_STRING);
        mh.writeNumber(beg->second.size());
        mh.writeString( beg->second );
        ++beg;
    }
}

void ServerCommandHandler::writeAnswer(unsigned char ch){       //ska vi använda denna?
    mh.writeCode(ch);
}
void ServerCommandHandler::writeNumber(int nbr){         ///ska vi använda denna?
    mh.writeNumber(nbr);
}
