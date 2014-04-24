#ifndef SERVER_COMMANDHANDLER_H
#define SERVER_COMMANDHANDLER_H
#include <string>
#include <map>
#include "messagehandler.h"

class ServerCommandHandler {
public:
    ServerCommandHandler(MessageHandler m) : mh(m){}
    int readNumber();
    unsigned char readCommand();
    void writeString(const std::string& s);
    void writeMap(std::map<int, std::string> map);
    void writeAnswer(unsigned char ch);
    void writeNumber(int nbr);
private:
    MessageHandler mh;
};
#endif