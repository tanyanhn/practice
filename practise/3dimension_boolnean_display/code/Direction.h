#ifndef DIRECTION_BOOLEAN
#define DIRECTION_BOOLEAN

#include<math.h>
#include<iostream>
#include"Tol.h"
using namespace std;

class Direction{
    double coord[3];
public:
    Direction() : coord{1, 1, 1} {}
    Direction(const double x, const double y, const double z) : coord{x, y, z} {
         if(fabs(x) < Tol::t && fabs(y) < Tol::t && fabs(z) < Tol::t){
            cout << "Direction too close to 0\n";
            char a;
            cin >> a;
            }
    }
    Direction(const Direction& d2) : coord{d2.coord[0], d2.coord[1], d2.coord[2]} {}
    Direction& operator=(const Direction& d2) {
        coord[0] = d2.coord[0];
        coord[1] = d2.coord[1];
        coord[2] = d2.coord[2];
    }
    ~Direction(){}
    const double operator[](const int i) const {
        if(i < 0 || i > 2){
            cout << "Direction" << " : " << i << " out of range";
            char a;
            cin >> a;
        }
        return coord[i];
    }
    double& operator[](const int i){
        if(i < 0 || i > 2){
            cout << "Direction" << " : " << i << " out of range";
            char a;
            cin >> a;
        }
        return coord[i];
    }
    Direction operator-(const Direction& d2) const {
        return Direction(coord[0] - d2.coord[0],
                         coord[1] - d2.coord[1],
                         coord[2] - d2.coord[2]);
    }
    Direction operator+(const Direction& d2) const {
        return Direction(coord[0] + d2.coord[0],
                         coord[1] + d2.coord[1],
                         coord[2] + d2.coord[2]);
    }
    Direction operator/(const double i) const; /*{
        if(fabs(i) < Tol::t * Tol::t) {
            cout << " i too small" <<endl;
            cin >> i;
        }
        return Direction(coord[0] / i, coord[1] / i, coord[2] / i);
    }*/
    Direction operator*(const double i) const {
        return Direction(coord[0] * i, coord[1] * i, coord[2] * i);
    }
    Direction unit() const {
        // double m = coord[0] * coord[0] + coord[1] * coord[1] + coord[2] * coord[2];
        return *this / this->norm();
    }
    double norm() const {
        return coord[0] * coord[0] + coord[1] * coord[1] + coord[2] * coord[2];
    }
    double dot(const Direction& d2) const {
        return coord[0] * d2.coord[0] + coord[1] * d2.coord[1] + coord[2] * d2.coord[2];
    }
    Direction cross(const Direction& d2) const {
        return Direction(coord[1] * d2.coord[2] - coord[2] * d2.coord[1],
                         coord[2] * d2.coord[0] - coord[0] * d2.coord[2],
                         coord[0] * d2.coord[1] - coord[1] * d2.coord[0]);
    }
};


class Direction2D {
public:
    double d[2];
    Direction2D(double d1, double d2) : d{d1, d2} {}
    ~Direction2D() {}
    double dot(const Direction2D& p) const {
        return (d[0] * p[0] + d[1] * p[1]);
    }
    double cross(const Direction2D& p) const {
        return(d[0] * p[1] - d[1] * p[0]);
    }
    double& operator[](const int index){
        if(index < 0 || index > 1) cout << "operator[] wrong";
        return d[index];
    }
    const double& operator[](const int index) const {
        if(index < 0 || index > 1) cout << "opearotr[] const wrong";
        return d[index];
    }
    Direction2D operator-(const Direction2D& p) const {
        return Direction2D(d[0] - p[0], d[1] - p[1]);
    }
    Direction2D operator+(const Direction2D& p) const {
        return Direction2D(d[0] + p[0], d[1] + p[1]);
    }
};

#endif