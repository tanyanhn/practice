#include"DatastructureHead.h"
#include"STLHead.h"
#include"FunctorHead.h"

using namespace std;


int main(int argc, char* argv[]){
    ifstream fis0("data/cube.obj");
    ifstream fis1("data/tetrahedron.obj");
    Yinset y1, y2;
    fis0 >> y1;
    fis1 >> y2;
    /*
    Segment seg = Data::segments[23];
    Point p0 = Data::points[seg[0]],
        p1 = Data::points[seg[1]],
        p;
    p = p0 + (p1 - p0)/2;
    */
    Planar f = Data::planars[14],
        pl0 = Data::planars[15],
        pl1 = Data::planars[7];
    vector<int> ps = f.getpoints();
    vector<int> segs = f.getsegments();
    Segment seg0 = Data::segments[segs[0]];
    Point p0 = Data::points[ps[0]],
        p1 = Data::points[ps[1]],
        p2 = Data::points[ps[2]];
    Direction d1 = Data::points[9] - Data::points[12],
        d2 = Data::points[10] - Data::points[9];
    Direction normaldirect = f.getnormaldirect();
    Flat f1(p0, normaldirect),
        f2(p0, normaldirect + Direction(Tol::t / 3, Tol::t / 3, Tol::t / 3)),
        f3(p0, normaldirect + Direction(0.5, 0.5, 0.5));
    Line l1(seg0.getfixpoint(), seg0.getdirect() +  Direction(Tol::t / 3, Tol::t / 3, Tol::t / 3)),
        l2(seg0.getfixpoint(), seg0.getdirect() +  Direction(0.1, 0.1, 0.1));
    Point pp0 = p0 + (p1 - p0) / 3,
        pp1 = p0 + (p1 - p0) * 3,
        pp2 = p0 + (p0 - p1) * 3
    /*
    cout << f.ifintersectionLine(seg0) << endl
         << f.ifintersectionLine(l1) << endl
         << f.ifintersectionLine(l2) << endl
         << f.ifintersectionFlat(f1) << endl
         << f.ifintersectionFlat(f2) << endl
         << f.ifintersectionFlat(f3) << endl
         << f.ifcontainPoint(p0) << endl
         << f.ifcontainPoint(p0 + Direction(Tol::t / 3, Tol::t / 3, Tol::t / 3)) << endl
         << f.ifcontainPoint(p0 + Direction(Tol::t, Tol::t, Tol::t)) << endl;
    cout << l1.ifoverlapLine(l2)  << endl
         << l1.ifoverlapLine(seg0) << endl;
    Line l3 = f.intersectionFlat(f3),
        l4 = f.intersectionFlat(pl1),
        l5 = pl1.intersectionFlat(f3);
    //d1 = Direction() - d1;
    //d2 = Direction() - d2;
    cout << f.angleBetweenFlats(pl0, d1) << endl
         << f.angleBetweenFlats(pl1, d2) << endl;
    //d1 = Direction() - d1;
    //d2 = Direction() - d2;
    cout << pl0.angleBetweenFlats(f, d1) << endl
         << pl1.angleBetweenFlats(f, d2) << endl;
    */
    //cout << seg.ifcontainPoint(p) << endl;
    //p += Direction(Tol::t/2, 0, 0);
    //cout << seg.ifcontainPoint(p + Direction(Tol::t / 2, 0, 0)) << endl;
    //cout << seg.ifcontainPoint(p + Direction(Tol::t / 2, 0, Tol::t / 2)) << endl;
    //cout << seg.ifcontainPoint(p + Direction(Tol::t / 2, Tol::t, Tol::t / 2)) << endl;
    //cout << seg.ifcontainPoint(p0 + (p1 - p0) * 3) << endl;
    //cout << seg.ifcontainPoint(p0 + (p1 - p0) * -3) << endl;
    //cout << seg.ifcontainPoint(p0) << endl;
    //cout << seg.ifcontainPoint(p1) << endl;
    /*
    Line l1(p + Direction(Tol::t / 2, 0, Tol::t / 2), seg.getdirect() + Direction(Tol::t, 0, 0));
    Line l2(p + Direction(Tol::t / 2, 0, Tol::t / 2), seg.getdirect() + Direction(0, Tol::t, Tol::t / 2));
    Line l3(p + Direction(Tol::t / 2, 0, Tol::t / 2), seg.getdirect() + Direction(0, 0, Tol::t * 2));
    cout << l1.ifintersectionLine(seg) << endl;
    cout << l2.ifintersectionLine(seg) << endl;
    cout << l3.ifintersectionLine(seg) << endl;
    cout << l1.ifoverlapLine(seg) << endl;
    cout << l2.ifoverlapLine(seg) << endl;
    cout << l3.ifoverlapLine(seg) << endl;
    Point pp2 = l2.intersectionLine(seg),
        pp3 = l3.intersectionLine(seg);
    cout << pp3;
    */
    //Data::f();
    //char* a = 0;
    //cout << *a;
    /*
    ofstream fos("answer/test.obj");
    fos << y1;
    fos << endl;
    fos << y2;
    */
}