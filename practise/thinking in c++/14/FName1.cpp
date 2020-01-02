// An fstream with a file name
#include <iostream>
#include <fstream>
#include <string>
#include "../require.h"
using namespace std;

class FName1 {
    ifstream file;
    string fileName;
    bool named;
public:
    FName1() : named(false) {}
    FName1(const string& fname) : fileName(fname), file(fname.c_str()) {
        assure(file, fileName);
        named = true;
    }
    string name() const { return fileName ;}
    void name(const string& newName) {
        if(named) return; // Don't overwrite
        fileName = newName;
        named = true;
    }
    operator ifstream&() {return file;}
    ~FName1(){}
    void print(){}
};

int main(int argc, char *argv[])
{
    FName1 file("FName1.cpp");
    cout << file.name() << endl;
    // Error: close() not a member:
    //! file.close();
    return 0;
}
