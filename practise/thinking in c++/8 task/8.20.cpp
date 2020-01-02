#include <iostream>
#include <string.h>
#include "../require.h"
using namespace std;

class Mystring {
    string s;
public:
    Mystring(const char* c = " ");
    Mystring(const string* c) : s(*c) {}
    Mystring operator= (const string* c) {
        s = *c;
        return *this;
    }
    void print(){
        cout << s <<endl;
    };
    ~Mystring(){};
};
Mystring::Mystring(const char* c) : s(c){}

class StringStack {
    static const int size = 100;
    Mystring* stack[size];
    int index;
public:
    bool empty;
    StringStack();
    void push(const string* s);
    Mystring pop ();
    ~StringStack(){};
};

StringStack::StringStack() : index(0) ,empty(1) {
    memset (stack, 0 ,size * sizeof(Mystring*));
}

void StringStack::push(const string* s){
    if(index < size){
        Mystring* m = new Mystring(s);
        stack[index++] = m;
        empty = 0;}
}

Mystring StringStack::pop() {
    if(index > 0){
        Mystring rv = *stack[--index];
        delete stack[index];
        stack[index] = 0;
        return rv;
    }
    empty = 1;
    Mystring rt;
    return rt;
}

string iceCream[] = {
    "pralines & cream",
    "fudge ripple",
    "jamocha almond fudge",
    "wild mountain blackberry",
    "raspberry sorbet",
    "lemon swirl",
    "rocky road",
    "deep chocolate fudge"
};

const int iCsz =
    sizeof iceCream / sizeof *iceCream;

int main(int argc, char *argv[])
{
    Mystring S("Hello World!");
    S.print();


    StringStack ss;
    for (int i = 0; i < iCsz; i++)
        ss.push(&iceCream[i]);
    Mystring cp;
    do{
        cp = ss.pop();
        cp.print();
    }
    while(ss.empty == 0);
    
          return 0;
}
