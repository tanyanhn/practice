#ifndef BIRDHOUSE_H
#define BIRDHOUSE_H
#include "12-15.1.h"
#include <iostream>
using namespace std;

class BirdHouse {
    Bird val;
    Bird* ptr;
    Bird& ref;

    BirdHouse(const BirdHouse&);
    BirdHouse& operator=(const BirdHouse&){}
public:
    BirdHouse(const Bird& v, Bird* p, Bird& r) : val(v), ref(r) {
        ptr = p;
    }
    ~BirdHouse(){}
    friend ostream& operator<<(ostream&, const BirdHouse&);
    void print(){}
    
};
#endif
