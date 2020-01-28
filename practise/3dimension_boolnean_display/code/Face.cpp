#include"Face.h"
#include"Planar.h"
#include"Point.h"
#include"Planar.h"
#include"STLHead.h"
using namespace std;

class PlanarCompare{
public:
    bool operator()(const Planar&, const Planar&);
};

bool PlanarCompare::operator()(const Planar& pl0, const Planar& pl1){
    vector<int> vp1 = pl1.getpoints(),
        vp0 = pl0.getpoints();
    Point p00 = Data::points[vp0[0]],
        p01 = Data::points[vp0[1]],
        p02 = Data::points[vp0[2]],
        p10 = Data::points[vp1[0]],
        p11 = Data::points[vp1[1]],
        p12 = Data::points[vp1[2]],
        p0, p1;
    int k0, k1;
    if(p00 < p01){
        if(p01 < p02){
            p0 = p02;
            k0 = 2;
        }
        else{
            p0 = p01;
            k0 = 1;
        }
    }
    else{
        if(p00 < p02){
            p0 = p02;
            k0 = 2;
        }
        else{
            p0 = p00;
            k0 = 0;
        }
    }
    if(p10 < p11){
        if(p11 < p12){
            p1 = p12;
            k1 = 2;
        }
        else{
            p1 = p11;
            k1 = 1;
        }
    }
    else{
        if(p10 < p12){
            p1 = p12;
            k1 = 2;
        }
        else{
            p1 = p10;
            k1 = 0;
        }
    }
    if(p0.getid() != p1.getid()){
        return p0 < p1;
    }
    else{
        vector<int> vseg0 = pl0.getsegments(),
            vseg1 = pl1.getsegments();
        Segment seg00 = Data::segments[vseg0[(k0 + 2) % 3]],
            seg01 = Data::segments[vseg0[k0]],
            seg10 = Data::segments[vseg1[(k1 + 2) % 3]],
            seg11 = Data::segments[vseg1[k1]];
        Direction zaix = Direction(0, 0, 1);
        double direct00 = fabs(seg00.getdirect().dot(zaix)),
            direct01 = fabs(seg01.getdirect().dot(zaix)),
            direct10 = fabs(seg10.getdirect().dot(zaix)),
            direct11 = fabs(seg11.getdirect().dot(zaix));
        if(direct00 > direct01){
            swap(direct00, direct01);
        }
        if(direct10 > direct11){
            swap(direct10, direct11);
        }
        if(direct00 > direct10 + Tol::t){
            return true;
        }
        else if(direct00 < direct10 - Tol::t){
            return false;
        }
        else {
            if(direct01 > direct11 + Tol::t){
                return true;
            }
            else {
                return false;
            }
        }
    }
}


void Face::generatortype(){
    Planar biggestpl = Data::planars[planars[0]];
    PlanarCompare functor;
    for(auto i = ++planars.begin(); i != planars.end(); i++){
        Planar pl = Data::planars[*i];
        if(functor(biggestpl, pl) == true){
            biggestpl = pl;
        }
    }
    if(biggestpl.getnormaldirect().dot(Direction(0, 0, 1)) > 0){
        type = 1;
    }
    else {
        type = 0;
    }
}