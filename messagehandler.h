#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include "connection.h"
#include <string>
#include <memory>

class MessageHandler {
    
public:
    MessageHandler(Connection& c) : conn(c) {};
    void writeNumber(int value);
    std::string readString(int n);
    void writeString(const std::string& s);
    int readNumber();
    void writeByte(unsigned char ch);
    void writeCode(unsigned char c);
    unsigned char readCode();
    unsigned char readByte();
    
private:
    Connection& conn;
};
#endif