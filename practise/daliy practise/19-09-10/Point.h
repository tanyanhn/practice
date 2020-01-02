#ifndef __CRAZYFISH__IntCell__
#define __CRAZYFISH__IntCell__

#include <iostream>
#include <vector>

class Point
{
private:
    double coordinate[2];
public:
    // A default constructor.
    Point(){};
    Point(double x, double y);
    const double *read() const;
    double &operator[](int i);
     const double &operator[](int i) const ; // Without this, then the return of can not be a rvalue.
    Point &operator+=(const Point &_pnt);
    // A friend means has the authority to modify the private values.
    friend std::ostream &operator<<(std::ostream&, const Point&);
    friend Point operator+(const Point &_p1, const Point & _p2);
};

std:: ostream & operator<< (std::ostream&, const Point&);
// Reload the  << operator for output. Should a friend of Point.

Point operator+(const Point & _p1, const Point &_p2);

Point::Point(double x, double y)
{
    coordinate[0] = x;
    coordinate[1] = y;
};

const double *Point:: read() const
{
    return (coordinate);
}

double &Point:: operator[] (int i)
{
    return coordinate[i];
};

// A read-only version for [] operator.
 const double &Point::operator[](int i) const
 {
     return coordinate[i];
 };

Point &Point::operator+=(const Point &_pnt)
{
    for (int i = 0; i < 2; i++)
        coordinate[i] += _pnt.coordinate[i];
    // Return itself.
    return * this;
};

std::ostream &operator<<(std::ostream& os, const Point& _pnt)
{
    for (int i = 0; i < 2; i++)
        os << _pnt.coordinate[i] << "\t";
    return os;
};

// A binary operator has to happen memory replication,
// since it produces new entity.
Point operator+(const Point & _p1, const Point & _p2)
{
    // Here we want a default constructor.
    Point result;
    for (int i = 0; i < 2; i++)
        result.coordinate[i] = _p1[i] + _p2[i];
    return result;
};

#else
// Do nothing.

#endif
