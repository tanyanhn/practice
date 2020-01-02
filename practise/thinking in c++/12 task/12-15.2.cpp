#include "12-15.2.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const BirdHouse& bh) {
    os << '{' << bh.val << ", " << *bh.ptr <<", " << bh.ref  << '}';
    return os;
}
