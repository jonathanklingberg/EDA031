#include <string>
#include <map>

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
    mh.writeNumber(map.size());
    auto beg = map.begin();
    while( beg != map.end()){
        mh.writeNumber( beg->first );
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
