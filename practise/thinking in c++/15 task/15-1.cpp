#include <iostream>

#include "../require.h"
using namespace std;

class Shape {
    char c;
public:
    char& C() {return this->c;}
    virtual void draw() = 0;//{ C() = 's';}
    friend ostream& operator<<(ostream& os, const Shape& s){
        return os << "c = "<< s.c << endl;
    }
};
inline void Shape::draw() { C() = 's';} 

class Circle : public Shape{
public:
    void draw() { C() = 'C'; }
};

class Square : public Shape {
public:
   void draw() { C() = 'S';}
};

class Triangle : public Shape {
public:
    void draw() { C() = 'T';}
};

//void f(Shape) {}

int main(int argc, char *argv[])
{
    Circle s1;Square s2; Triangle s3;
    Shape* a[] = {&s1, &s2, &s3};
    cout << *a[0] << *a[1] << *a[2] ;
    a[1]->draw();
    a[2]->draw(); a[0]->draw();
    cout << *a[0] << *a[1] << *a[2];
    //Shape s;
    //f(s1);
    return 0;
}
