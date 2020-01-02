// Deleting void pointers can cause memory leaks
#include<iostream>
using namespace std;

class Object {
    void* data; // Some storage
    const int size;
    const char id;
public:
    Object(int sz, char c) : size(sz) , id(c) {
        data = new char[size];
        cout << "Consructing object " << id << ", size = " << size <<"\n";
    }
    ~Object(){
        cout << "Destructing object " << id << "\n";
        delete []data; // OK, just releases storage,
        // no destructor calls are necessary
    }
    void print(){}
};

int main() {
    Object* a = new Object(40 , 'a');
    delete a;
    void* b = new Object(40, 'b');
    delete b;
}
