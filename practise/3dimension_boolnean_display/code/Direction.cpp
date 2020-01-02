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