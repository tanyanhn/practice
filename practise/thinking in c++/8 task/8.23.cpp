#include <iostream>
#include "../require.h"
using namespace std;

class you{
    const int ci;
    int m;
public:
    you(int i,int j) : ci(j) , m(i){};
    ~you(){}
    void print() const {
        cout << ci << " "<<  m;
    }
    void insert (int i){
        m=i;
    }
};

int main(int argc, char *argv[])
{
    you Y(3,4);
    const you O(5,6);
    Y.insert(6);
    Y.print();
    //O.insert(1);
    O.print();
    
    return 0;
}
