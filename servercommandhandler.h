#include <vector>
#include <string>
#include "MessageHandler.h"

class ServerCommandHandler(MessageHandler mh) : mh(mh){}
public:
    void sendMap(map<int, string>);
    void sendAns(res);
    void sendArticle(
private:
    MessageHandler mh;
}