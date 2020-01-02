#include "OStack.h"
#include "../require.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Use multple inheritance. We want both a string and an Object:
class MyString : public string, public Object {
public:
    MyString(string s) : string(s) {}
    ~MyString(){
        cout << "deleting string: " << *this << "\n";
    }
    void print(){}
};

int main (int argc, char* argv[]) {
    requireArgs(argc, 1); // File name is argument
    ifstream in(argv[1]);
    assure(in, argv[1]);
    Stack textlines;
    string line;
    // Read file and store lines in the stack:
    while(getline(in, line))
        textlines.push(new MyString(line));
    // Pop some lines from the Stack:
    MyString* s;
    for (int i = 0; i < 10; i++){
        if((s = (MyString*)textlines.pop()) == 0) break;
        cout << *s << endl;
        delete s;
    }
    cout << "Letting the destructor do the rest:\n";
}

