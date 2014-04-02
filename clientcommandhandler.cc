#include <string>
#include <iostream>
#include "clientcommandhandler.h"
#include "protocol.h"
#include <map>
#include <utility>
#include <vector>
#include <iostream>

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
    cout<<"jaha lista grupper var begärt"<<endl;
    writeCommand(Protocol::COM_LIST_NG);
    writeCommand(Protocol::COM_END);
    unsigned char start_code = mh.readCode(); //ANS_LIST_NG
    mh.readCode(); //read PAR_NUM
    int size = mh.readNumber(); // N
    //    checkCode("List groups", Protocol.ANS_LIST_NG, code);
    //    checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");
    map<int, string> groups;
    cout<<"jag skapade en grupp som ska returneras"<<endl;
    for (int i = 0; i < size; ++i) {
        mh.readCode(); //read PAR_NUM
        int num = mh.readNumber(); //N
        mh.readCode(); //read PAR_STRING
        int n = mh.readNumber(); //N
        groups.insert(make_pair(num, mh.readString(n)));
        cout<<"jag lade in en grupp i res"<<endl;
    }
    unsigned char end_code = mh.readCode();
    //    checkCode("List groups", Protocol.ANS_END, code);
    return groups;
}

bool ClientCommandHandler::createGroup(string title) {
    cout<<"då var create group begärt för satan"<<endl;
	writeCommand(Protocol::COM_CREATE_NG);
	writeCommand(Protocol::PAR_STRING);
	writeNumber(title.size());
    writeString(title);
	writeCommand(Protocol::COM_END);
	unsigned char start_code = mh.readCode();  //ANS_CREATE_NG
	cout<<start_code<<endl;
	unsigned char acknowledgement_code = mh.readCode();   //Antingen ANS_ACK eller ANS_NAK
	unsigned char end_code;
    cout<<"jag har nu fått lite svar från servern"<<endl;
	switch(acknowledgement_code) {
		case Protocol::ANS_ACK:
            cout<<"ACK FÖR SATANS"<<endl;
			end_code = mh.readCode();
			return true;
		case Protocol::ANS_NAK:
            cout<<"NAK FÖR SATANS"<<endl;
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
    map<int,string> res;
    switch(acknowledgement_code) {
		case Protocol::ANS_ACK :{
            mh.readCode(); //PAR_NUM
            int size = mh.readNumber(); // size of map
            for(int i = 0; i != size; ++i) {
                mh.readCode(); //read PAR_NUM
                int num = mh.readNumber(); //N
                mh.readCode(); //read PAR_STRING
                int n = mh.readNumber(); //N
                res.insert(make_pair(num, mh.readString(n)));
            }
            end_code = mh.readCode();
            return res;
        }
            break;
        case Protocol::ANS_NAK :{
            end_code = mh.readCode();
            return res;
        }
            break;
    }
}

bool ClientCommandHandler::createArt(int group_nbr, string title, string auth, string text) {
    writeCommand(Protocol::COM_CREATE_ART);
    writeCommand(Protocol::PAR_NUM);
    writeNumber(group_nbr);
    writeCommand(Protocol::PAR_STRING);
    writeString(title);
    writeCommand(Protocol::PAR_STRING);
    writeString(auth);
    writeCommand(Protocol::PAR_STRING);
    writeString(text);
    writeCommand(Protocol::COM_END);
    unsigned char start_code = mh.readCode(); //ANS_CREATE_ART
    unsigned char acknowledgement_code = mh.readCode();   //Antingen ANS_ACK eller ANS_NAK
    unsigned char end_code;
    switch(acknowledgement_code) {
		case Protocol::ANS_ACK:
			end_code = mh.readCode();
			return true;
		case Protocol::ANS_NAK:
            end_code = mh.readCode();
			return false;
        default :
            return false;
    }
}

bool ClientCommandHandler::deleteArt(int group_nbr,int art_nbr) {
    writeCommand(Protocol::COM_DELETE_ART);
    writeCommand(Protocol::PAR_NUM);
    writeNumber(group_nbr);
    writeCommand(Protocol::PAR_NUM);
    writeNumber(art_nbr);
    unsigned char start_code = mh.readCode(); //ANS_DELETE_ART
    unsigned char acknowledgement_code = mh.readCode();   //Antingen ANS_ACK eller ANS_NAK
    unsigned char end_code;
    switch(acknowledgement_code) {
		case Protocol::ANS_ACK:
			end_code = mh.readCode();
			return true;
		case Protocol::ANS_NAK:
            end_code = mh.readCode();
			return false;
        default :
            return false;
    }
}

vector<string> ClientCommandHandler::getArt(int group_nbr,int art_nbr) {
    writeCommand(Protocol::COM_GET_ART);
    writeCommand(Protocol::PAR_NUM);
    writeNumber(group_nbr);
    writeCommand(Protocol::PAR_NUM);
    writeNumber(art_nbr);
    unsigned char start_code = mh.readCode(); //ANS_GET_ART
    unsigned char acknowledgement_code = mh.readCode();   //Antingen ANS_ACK eller ANS_NAK
    unsigned char end_code;
    vector<string> res;
    switch(acknowledgement_code) {
		case Protocol::ANS_ACK:
            for (int i = 0; i != 3; ++i) {
                mh.readCode(); //read PAR_STRING
                int n = mh.readNumber(); //N
                res.push_back(mh.readString(n));
            }
			end_code = mh.readCode();
			return res;
		case Protocol::ANS_NAK:
            end_code = mh.readCode();
			return res;
    }
}






