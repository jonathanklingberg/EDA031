#include <string>
#include "messagehandler.h"
#include <map>
#include <vector>

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
    map<int, string> listArts(int group_nbr);
    bool createArt(int group_nbr,string title,string auth, string text);
    bool deleteArt(int group_nbr, int art_nbr);
    vector<string> getArt(int group_nbr,int art_nbr);
private:
    MessageHandler mh;
};
