#include <iostream>
#include "../require.h"
using namespace std;

class S {
    static const int max = 5;
    const int i;
    static int j;
    int k[max];
public:
    S(int* a, int ii = 10) : i(ii) {for(int d = 0; d< max; ++d)
            k[d]=*(a+d);}
    void print(int d) {
        cout << k[d] << endl << i-j << "\"\n";
        f();
    }
    static void f() { j++;}
};

int S::j = 0;

int main(int argc, char *argv[])
{
    int A[] = {1,2,3,4,5,6,7,8,9};
    S s(A);
    for(int i = 0; i < 5;++i ) s.print(i);
    return 0;
}
