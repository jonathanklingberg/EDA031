#ifndef CLIENT_COMMANDHANDLER_H
#define CLIENT_COMMANDHANDLER_H
#include "messagehandler.h"
#include <string>
#include <map>
#include <vector>

class ClientCommandHandler{
public:
    ClientCommandHandler(MessageHandler m) : mh(m){}
    void writeNumber(int nbr);
    void writeCommand(unsigned char c);
    void writeString(std::string s);
    std::string readString(int n);
    std::map<int, std::string> listGroups();
    bool createGroup(std::string title);
    bool deleteGroup(int group_nbr);
    std::map<int, std::string> listArts(int group_nbr);
    bool createArt(int group_nbr,std::string title,std::string auth, std::string text);
    bool deleteArt(int group_nbr, int art_nbr);
    std::vector<std::string> getArt(int group_nbr,int art_nbr);
private:
    MessageHandler mh;
};
#endif