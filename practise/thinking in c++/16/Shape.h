#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <string>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual ~Shape() {};
};

class Circle : public Shape {
public:
    Circle() {}
    ~Circle() { cout << "Circle::~Circle\n"; }
    void draw() { cout << "Circle::draw\n"; }
    void erase() { cout << "Circle::erase\n"; }
};

class Square : public Shape {
public:
    Square() {}
    ~Square() { cout << "Square::~Square\n"; }
    void draw() { cout << "Square::draw\n"; }
    void erase() { cout << "Square::erase\n"; }
};

class Line : public Shape {
public:
    Line() {}
    ~Line() { cout << "Line::~Line\n"; }
    void draw() { cout << "Line::draw\n"; }
    void erase() { cout << "Line::erase\n"; }
};

#endif
