#include <iostream>
#include "../require.h"
using namespace std;

class team{
    const int size ;
    enum{ s = 10};
    int i[s];
public:
    team(int sz) : size(sz){};
    void insert(int * A);
    void print(){
        cout << size <<endl;
        for(int j = 0; j < s ; j++)
            cout << i[j] <<"."; 
    }
};

void team::insert( int * A){
    for (int j=0 ; j< s ; j++)
        i[j] = A[j];
}

int main(int argc, char *argv[])
{
    int B[10] = {1,2,3,4,5,6,7,8,12};
    team T(100);
    T.insert(B);
    T.print();
    
    return 0;
}
