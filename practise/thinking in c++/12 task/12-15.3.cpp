#include "12-15.2.h"
#include "12-15.1.h"
#include <iostream>

int main() {
    using namespace std;
    Bird a, b ,c;
    BirdHouse bh(a, &b , c);
    cout << bh << endl;
    
}
