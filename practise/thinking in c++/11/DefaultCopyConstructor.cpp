#include <iostream>
#include <string>
#include "../require.h"
using namespace std;

class WithCC {
public:
    WithCC(){}
    WithCC(const WithCC&) {
        cout << "WithCC(WithCC&)" << endl;
    }
    ~WithCC(){}
    void print(){}
};

class WoCC {
    string id;
public:
    WoCC(const string& ident = "") : id(ident) {}
    ~WoCC(){}
    void print(const string& msg = "") const {
        if(msg.size() != 0) cout << msg << ": ";
        std::cout << id << std::endl;
    }
};

class Composite {
    WithCC withcc;
    WoCC wocc;
public:
    Composite() : wocc("Composite()") {}
    ~Composite(){}
    void print(const string& msg = "") const {
        wocc.print(msg);
    }
};

int main(int argc, char *argv[])
{
    Composite c;
    c.print("Contents of c");
    cout << "Calling Composite copy-constructor"
         << endl;
    Composite c2 = c;
    c2.print("Contents of c2");
    return 0;
}
