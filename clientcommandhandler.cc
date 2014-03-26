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

string ClientCommandHandler::readString(int n){
    return mh.readString(n);
}

void ClientCommandHandler::writeCommand(unsigned char c){
    mh.writeCode(c);
}
void ClientCommandHandler::writeString(string s){
    mh.writeString(s);
}

map<int, string> ClientCommandHandler::listGroups() {
    writeCommand(Protocol::COM_LIST_NG);
    writeCommand(Protocol::COM_END);
    unsigned char start_code = mh.readCode(); //ANS_LIST_NG
    mh.readCode(); //read PAR_NUM
    int size = mh.readNumber(); // N
    //    checkCode("List groups", Protocol.ANS_LIST_NG, code);
    //    checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");
    map<int, string> groups;
    for (int i = 0; i < size; i++) {
        mh.readCode(); //read PAR_NUM
        int num = mh.readNumber(); //N
        mh.readCode(); //read PAR_STRING
        int n = mh.readNumber(); //N
        groups.insert(make_pair(num, mh.readString(n)));
    }
    unsigned char end_code = mh.readCode();
    //    checkCode("List groups", Protocol.ANS_END, code);
    return groups;
}

bool ClientCommandHandler::createGroup(string title) {
	writeCommand(Protocol::COM_CREATE_NG);
	writeCommand(Protocol::PAR_STRING);
	writeNumber(title.size());
    writeString(title);
	writeCommand(Protocol::COM_END);
	unsigned char start_code = mh.readCode();  //ANS_CREATE_NG	
	unsigned char acknowledgement_code = mh.readCode();   //Antingen ANS_ACK eller ANS_NAK
	unsigned char end_code;
	unsigned char nak_answer_code;
	switch(acknowledgement_code) {
		case Protocol::ANS_ACK:
			end_code = mh.readCode();
			return true;
		case Protocol::ANS_NAK:
			nak_answer_code = mh.readCode();
			if(nak_answer_code == Protocol::ERR_NG_ALREADY_EXISTS) {
				cout << "Group already exists!" << endl;
			}
		        end_code = mh.readCode();
			return false;
        default :
            return false;
    }
}


bool ClientCommandHandler::deleteGroup(int group_nbr) {
	writeCommand(Protocol::COM_DELETE_NG);
	writeCommand(Protocol::PAR_NUM);
    writeNumber(group_nbr);
	writeCommand(Protocol::COM_END);
	unsigned char start_code = mh.readCode();  //ANS_CREATE_NG	
	unsigned char acknowledgement_code = mh.readCode();   //Antingen ANS_ACK eller ANS_NAK
    unsigned char end_code;
    unsigned char nak_answer_code;
	switch(acknowledgement_code) {
		case Protocol::ANS_ACK :
			end_code = mh.readCode();
			return true;
		case Protocol::ANS_NAK :
			nak_answer_code = mh.readCode();
            if(nak_answer_code == Protocol::ERR_NG_DOES_NOT_EXIST) {
				cout << "The group does not exist!" << endl;
			}
			end_code = mh.readCode();
			return false;
        default :
            return false;
    }
}

map<int, string> ClientCommandHandler::listArts(int group_nbr) {
    writeCommand(Protocol::COM_LIST_ART);
    writeCommand(Protocol::PAR_NUM);
    writeNumber(group_nbr);
    writeCommand(Protocol::COM_END);
    unsigned char start_code = mh.readCode(); //ANS_LIST_ART
    unsigned char acknowledgement_code = mh.readCode();   //Antingen ANS_ACK eller ANS_NAK
    unsigned char end_code;
    unsigned char nak_answer_code;
    switch(acknowledgement_code) {
		case Protocol::ANS_ACK :
            mh.readCode(); //PAR_NUM
            int size = mh.readNumber(); // size of map
            map<int,string> res;
            for(int i = 0; i != size; ++i) {
                mh.readCode(); //read PAR_NUM
                int num = mh.readNumber(); //N
                mh.readCode(); //read PAR_STRING
                int n = mh.readNumber(); //N
                res.insert(make_pair(num, mh.readString(n)));
            }
            end_code = mh.readCode();
            case Protocol::ANS_NAK :
			nak_answer_code = mh.readCode();
            if(nak_answer_code == Protocol::ERR_NG_DOES_NOT_EXIST) {
				cout << "The group does not exist!" << endl;
			}
			end_code = mh.readCode();
			return false;
        default :
            return false;
    }
    return res;
    
}


