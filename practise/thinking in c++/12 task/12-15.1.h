#ifndef BIRD_H
#define BIRD_H

#include <iostream>
#include <string>
using namespace std;

class Bird {
    static int birdNum;
    string id;
public:
    Bird(string a = "Bird");
    ~Bird();
    friend ostream& operator<<(ostream&, const Bird&);
    void print();
};
#endif
