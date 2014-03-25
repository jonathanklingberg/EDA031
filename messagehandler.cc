#include "connection.h"
#include "messagehandler.h"

#include <string>

using namespace std;

void MessageHandler::writeNumber(int value){
    conn.write((value >> 24) & 0xFF);
    conn.write((value >> 16) & 0xFF);
    conn.write((value >> 8)	 & 0xFF);
    conn.write(value & 0xFF);
}
string MessageHandler::readString(int n){
    string s;
    char ch = 0;
    for(int i = 0; i < n; ++i) {
    //while ((ch = conn.read()) != '$') {
        s += ch;
    }
    return s;
}

void MessageHandler::writeString(const string& s) {
	for (unsigned char c : s) {
		conn.write(c);
	}
	//conn.write('$');
}

int MessageHandler::readNumber() {
	unsigned char byte1 = conn.read();
	unsigned char byte2 = conn.read();
	unsigned char byte3 = conn.read();
	unsigned char byte4 = conn.read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

void MessageHandler::writeByte(unsigned char nbr){
//    try{
        conn.write(nbr);
//    }catch( exception e){
//        throw e;
//    }
}

unsigned char MessageHandler::readCode(){
    return readByte();
}

unsigned char MessageHandler::readByte(){
    unsigned char code = conn.read();
//    if (code == Connection.CONNECTION_CLOSED) {
//        throw new ConnectionClosedException();
//    }
    return code;
}

void MessageHandler::writeCode(const unsigned char c) {
		writeByte(c);
}
