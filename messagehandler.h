#include "connection.h"
#include <string>
#include <memory>

using namespace std;

//template <typename T>
class MessageHandler {
    
public:
//    MessageHandler(T& c) : conn(c) {};
    MessageHandler(Connection& c) : conn(c) {};
//    MessageHandler(shared_ptr<Connection>& c) : conn(c) {};
    void writeNumber(int value);
    string readString();
    void writeString(const string& s);
    int readNumber();
    void writeByte(unsigned char ch);
    void writeCode(unsigned char c);
    unsigned char readCode();
    unsigned char readByte();
private:
//    T& conn;
    Connection& conn;
//    shared_ptr<Connection>& conn;
};
