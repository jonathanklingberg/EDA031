#include <string>
#include <map>

#include "messagehandler.h"

using namespace std;

class ServerCommandHandler {
public:
    ServerCommandHandler(MessageHandler m) : mh(m){}
    int readNumber();
    unsigned char readCommand();
    void writeString(const string& s);
    void writeMap(map<int, string> map);
    void writeAnswer(unsigned char ch);
    void writeNumber(int nbr);
private:
    MessageHandler mh;
};