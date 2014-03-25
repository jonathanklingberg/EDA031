#include <string>
#include <iostream>
#include "clientcommandhandler.h"
#include "protocol.h"
#include <map>
#include <utility>

using namespace std;

void ClientCommandHandler::writeNumber(int nbr){      //Behövs förmodligen inte
    mh.writeNumber(nbr);
}

string ClientCommandHandler::readString(int n){      //Behövs förmodligen inte
    return mh.readString(n);
}

void ClientCommandHandler::writeCommand(unsigned char c){     //Behövs förmodligen inte
    mh.writeCode(c);
}

map<int, string> ClientCommandHandler::listGroups() {
    mh.writeCode(Protocol::COM_LIST_NG);
    mh.writeCode(Protocol::COM_END);
    unsigned char start_code = mh.readCode();
    mh.readCode();
    int size = mh.readNumber();
    cout << "Client received start_code: " << static_cast<unsigned>(start_code) << endl;
    cout << "with size: " << size << endl;
    //    checkCode("List groups", Protocol.ANS_LIST_NG, code);
    //    checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");
    map<int, string> groups;
    for (int i = 0; i < size; i++) {
        mh.readCode();
        int num = mh.readNumber();
        mh.readCode();
        int n = mh.readNumber();
        groups.insert(make_pair(num, mh.readString(n)));
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

bool ClientCommandHandler::createGroup(string title) {
	mh.writeCode(Protocol::COM_CREATE_NG);
	mh.writeString(title);
	mh.writeNumber(Protocol::COM_END);
	unsigned char start_code = mh.readCode();  //ANS_CREATE_NG	
	unsigned char acknowlagement_code = mh.readCode();   //Antingen ANS_ACK eller ANS_NAK
	unsigned char end_code;
	unsigned char nak_answer_code;
	switch(acknowlagement_code) {
		case Protocol::ANS_ACK:
			end_code = mh.readCode();
			return true;
		case Protocol::ANS_NAK:
			nak_answer_code = mh.readCode();
		        end_code = mh.readCode();
			return false;
		default :
			return false;
		}
}

/*
bool ClientCommandHandler::deleteGroup(string title) {   // ej klar
	mh.writeCode(Protocol::COM:DELETE_NG);
	mh.writeString(title);
	mh.writeNumber(Protocol::COM_END);
	unsigned char start_code = mh.readCode();  //ANS_CREATE_NG	
	unsigned char acknowlagement_code = mh.readCode();   //Antingen ANS_ACK eller ANS_NAK
	switch(acknowlagement_code) {
		case (Protocol::ANS_ACK) :
			unsigned char end_code = mh.readCode();
			return true;
		case (Protocol::ANS_NAK) :
			unsigned char nak_answer_code = mh.readCode();
			unsigned char end_code = mh.readCode();
			return false;
		}
}
*/



