



#include "protocol.h"
#include <iostream>
#include <string>

using namespace std;


void handleString(){
    int temp;
    int n;
    char ch;
    cin >> temp;
    n = temp;
    cout << n << endl;
    string command;
    cout << command <<endl;
    switch (ch) {
        case Protocol::COM_LIST_NG:
            cout << "List groups!"<<endl;
            break;
            
        default:
            cout << "något gick jäääävligt snett, back to the drawing board"<<endl;
            break;
    }
}

void handleNbr(){
    int temp;
    char ch;
    cin >> temp;
    ch = temp;
    switch (ch) {
        case Protocol::COM_LIST_NG:
            cout << "list groups"<<endl;
            break;
            
        default:
            cout << "något gick jäääävligt snett, back to the drawing board"<<endl;
            break;
    }
}

int main() {
    char ch;
    int i;
    cin >> i;
    ch = i;
    switch (ch) {
        case Protocol::PAR_STRING:
            cout << "String command"<<endl;
            handleString();
            break;
            
        case Protocol::PAR_NUM:
            cout << "Number command" <<endl;
            handleNbr();
            break;
            
        default:
            cout << "Invalid entry" <<endl;
            break;
    }
}