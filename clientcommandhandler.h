#include <string>
#include "messagehandler.h"
#include <map>

using namespace std;

class ClientCommandHandler{
public:
    ClientCommandHandler(MessageHandler m) : mh(m){}
    void writeNumber(int nbr);
    void writeCommand(unsigned char c);
    string readString();
    map<int, string> listGroups();
    bool createGroup(string title);
    //bool deleteGroup(string title);
private:
    MessageHandler mh;
};
