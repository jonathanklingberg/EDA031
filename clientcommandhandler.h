#include <map>
#include <vector>
#include <string>
#include "MessageHandler.h"

class ClientCommandHandler(MessageHandler mh) : mh(mh){}
public:
	map<int,string> listGroups(); // list all groups
    int remGroup(int groupId); // deletes a specified newsgroup
    int addGroup(string name); // create a new newsgroup
    map<int,string> listArt(int groupId); // list all articles to specific group
    int remArt(int groupIndex, int articleIndex); // remove a secific article
    vector<string> getArt(int groupId, int artId); // get a specific article
    int addArt(int groupIndex, string name, string author,
                         string text); // create new article
private:
    MessageHandler mh;
}