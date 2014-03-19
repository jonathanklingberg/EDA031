#include "Connection.h"

class MessageHandler {

public:
	MessageHandler(Connection conn) : conn(conn) {};
	void readByte();
    void sendByte();
    
private:
	Connection conn;
};
