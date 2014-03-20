#include <string>
#include <iostream>
#include "clientcommandhandler.h"
#include "protocol.h"
#include <map>
#include <utility>

using namespace std;

void ClientCommandHandler::writeNumber(int nbr){
    mh.writeNumber(nbr);
}

string ClientCommandHandler::readString(){
    return mh.readString();
}

void ClientCommandHandler::writeCommand(unsigned char c){
    mh.writeCode(c);
}
map<int, string> ClientCommandHandler::listGroups() {
    
    mh.writeCode(Protocol::COM_LIST_NG);
    mh.writeCode(Protocol::COM_END);
    unsigned char start_code = mh.readCode();
    int size = mh.readNumber();
    cout << "Client received start_code: " << static_cast<unsigned>(start_code) << endl;
    cout << "with size: " << size << endl;
    //    checkCode("List groups", Protocol.ANS_LIST_NG, code);
    //    checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");
    map<int, string> groups;
    for (int i = 0; i < size; i++) {
        groups.insert(make_pair(mh.readNumber(), mh.readString()));
    }
    cout << "incoming map: " << endl;
    for(auto it = groups.cbegin(); it != groups.cend(); ++it){
        std::cout << it->first << " " << it->second << "\n";
    }
    unsigned char end_code = mh.readCode();
    cout << "And end_code: " << static_cast<unsigned>(end_code) <<endl;
    //    checkCode("List groups", Protocol.ANS_END, code);
    return groups;
}
