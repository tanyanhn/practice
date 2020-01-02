#include <iostream>

#include "../require.h"
using namespace std;

class HasArray {
public:
    static const  int len = 5;
    int a[len];
    HasArray(){
        for (int i = 0; i < len; ++i)
            a[i] = i;
    }
    ~HasArray(){}
    void print(){}
};

int main(int argc, char *argv[])
{
    HasArray h;
    int (HasArray::* pa)[5] =&HasArray::a;
    for (int i = 0; i < HasArray::len; ++i)
        cout << (h.*pa)[i] << ' ';
    cout << endl;

    return 0;
}
