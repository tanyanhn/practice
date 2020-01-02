#include <iostream>
using namespace std;

class ing {
    int i;

public:
    ing(int ii = 1)  : i(ii) {}
    ~ing(){}
    void set(int jj = 2) {
        i = jj;
    }
    void print(){
        cout << i << endl;
    }

};
