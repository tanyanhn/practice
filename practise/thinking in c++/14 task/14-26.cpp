#include <iostream>
#include <vector>
using namespace std;

class Rock  {
public:
    Rock(){
        cout << "Rock()\n";
    }
    Rock(const Rock&) {
        cout << "Rock(const Rock&)\n";
    }
    Rock& operator=(const Rock&) {
        cout << "Rock=()\n";
        return *this;
    }
    ~Rock(){cout << "~Rock()\n";}
    void print(){}
};

int main() {
    vector<Rock> byValue;
    Rock r1, r2, r3;
    byValue.push_back(r1);
    byValue.push_back(r2);
    byValue.push_back(r3);
    cout << "byValue populated\n\n";

    vector<Rock*> byPtr;
    byPtr.push_back(&r1);
    byPtr.push_back(&r2);
    byPtr.push_back(&r3);
    cout << "byPtr populated\n\n";
}
