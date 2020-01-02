#ifndef SELFCOUNTER_H
#define SELFCOUNTER_H
#include "ValueStack.h"
#include <iostream>
using namespace std;

class SelfCounter {
    static int counter;
    int id;
public:
    SelfCounter() : id(counter++) {
        cout << "Created: " << id << "\n";
    }
    SelfCounter(const SelfCounter& rv) : id(rv.id) {
        cout << "Copied: " << id << "\n";
    }
    SelfCounter operator=(const SelfCounter& rv) {
        cout << "Assigned " << rv.id << "to " << id << "\n";
        id = rv.id;
        return *this;
    }
    ~SelfCounter() {
        cout << "Destroyed: " << id << "\n";
    }
    friend ostream& operator<<(ostream& os, const SelfCounter& sc){
        return os << "SelfCounter: " << sc.id;
    }
};

#endif
