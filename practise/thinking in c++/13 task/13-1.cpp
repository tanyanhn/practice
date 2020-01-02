#include <iostream>
#include <vector>
#include "../require.h"
using namespace std;

class Counted {
    int id;
    static int count;
public:
    Counted() : id(count++) {
        cout << "id: " << id << " it's being created\n";
    }
    ~Counted(){
        cout << "id: " << id << " it's being destroyed\n";
    }
    void print(){
        cout << "id: " << id << "\n";
    }
};

int Counted::count = 1;
int main(int argc, char *argv[])
{
    Counted c[10];
    Counted* p;
    p = new Counted;
    vector<Counted*> v(10);
    for(int i = 0; i < 10; i++) v[i] = new Counted;
    for(int i = 0; i < 10; i++) v[i]->print(); 
    for(int j = 0; j < 10; j++) delete v[j];
    delete p;
    Counted* const a = new Counted[3];
    delete []a;
    return 0;
}
