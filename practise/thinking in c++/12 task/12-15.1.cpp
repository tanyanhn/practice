#include <iostream>
#include <string>
//#include <sstream>
#include "../require.h"
#include "12-15.1.h"
using namespace std;

Bird::Bird(string a ) : id(a + "# ") {
        birdNum++;
        /* ostringstream oss;
           oss << id << birdNum;
           id = oss.str();*/
        id = id + to_string(birdNum);
    }
Bird::~Bird(){}
ostream& operator<<(ostream& os, const Bird& a) {
    os << a.id << endl;
}
void print(){}


int Bird::birdNum = 0;
