#include<math.h>
#include<iostream>
#include"Direction.h"
using namespace std;

Direction Direction::operator/(const double i) const {
    if(fabs(i) < Tol::t * Tol::t) {
        cout << "Direction / i too small" <<endl;
        char a;
        cin >> a;
    }
    return Direction(coord[0] / i, coord[1] / i, coord[2] / i);
}


double Direction::angle(const Direction& d2, const Direction& di) const {
    Direction d1 = *this;
    if(d1.cross(d2).dot(di) < -Tol::t)
        return 2 * M_PI - acos(d2.dot(d1));
    else if(d1.cross(d2).dot(di) > Tol::t)
        return acos(d2.dot(d1));
    else if(d1.dot(d2) > 0)
        return 0;
    else if(d1.dot(d2) < 0)
        return M_PI;
}