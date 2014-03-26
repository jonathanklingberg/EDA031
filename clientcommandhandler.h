#include <string>
#include "messagehandler.h"
#include <map>

using namespace std;

class ClientCommandHandler{
public:
    ClientCommandHandler(MessageHandler m) : mh(m){}
    void writeNumber(int nbr);
    void writeCommand(unsigned char c);
    void writeString(string s);
    string readString(int n);
    map<int, string> listGroups();
    bool createGroup(string title);
    bool deleteGroup(int group_nbr);
private:
    MessageHandler mh;
};
