#include <iostream>
#include "../require.h"
using namespace std;

enum Hue { red = 0, blue, yellow };

class color {
    Hue a;
public:
    color(Hue i = red) {
        if(i > 2 || i < 0) {printf("failed"); }
        a = i;
    }
    void print() const {
        switch (a){
            case red: cout << "red"; break;
            case blue: cout << "blue"; break;
            defaut : cout << "yellow"; break;
        }
        cout << endl;
    }
    void set(Hue b){
        a = static_cast<Hue> (b);
    }
};

int main(int argc, char *argv[])
{
    color r(red);
    r.print();
    r.set(blue);
    r.print();
    return 0;
}
