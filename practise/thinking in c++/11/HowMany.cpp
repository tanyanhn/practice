#include <iostream>
#include <fstream>
#include <string>
#include "../require.h"
using namespace std;

ofstream out("HowMany.out");

class HowMany {
    static int objectCount;

public:
    HowMany(){ objectCount++; }
    ~HowMany(){
        objectCount--;
        print("~Howmany()");
    }
    static void print(const string& msg = ""){
        if(msg.size() != 0 ) out << msg << ": ";
        out << "objectCount = "
            << objectCount << endl;
    }

};

int HowMany:: objectCount = 0;

HowMany f(HowMany x) {
    x.print("x argument inside f()");
    return x;
}

int main(int argc, char *argv[])
{
    HowMany h;
    HowMany::print("after construction of h");
    HowMany h2 = f(h);
    HowMany::print("after call to f()");
    return 0;
}
