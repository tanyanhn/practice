#include <iostream>
#include <string>
//#include <sstream>
#include "../require.h"
using namespace std;

class Bird {
    static int birdNum;
    string id;
public:
    Bird(string a = "Bird") : id(a + "# "){
        birdNum++;
        /* ostringstream oss;
        oss << id << birdNum;
        id = oss.str();*/
        id = id + to_string(birdNum);
    }
    ~Bird(){}
    friend ostream& operator<<(ostream& os, const Bird& a) {
        os << a.id;
    }
    void print(){}
};

int Bird::birdNum = 0;

int main(int argc, char *argv[])
{
    Bird a, b, c("Tom"), d("Jerry");
    cout << a << b << c << d ;
    return 0;
}
