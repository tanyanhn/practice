#include <iostream>

#include "../require.h"
using namespace std;

class C {
    char c;
public:
    C(char b) : c(b) {}
    ~C(){}
    void print(){}
    friend ostream& operator<<(ostream& os, const C& a){
        os << a.c;
    }
    friend istream& operator>> (istream& is, C& a) {
        is >> a.c;
    }
};

int main(int argc, char *argv[])
{
    C c('g');
    cout << c << endl;
    cin >> c;
    cout << c << endl;
    return 0;
}
