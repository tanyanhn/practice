#include"DatastructureHead.h"
#include"STLHead.h"
#include"FunctorHead.h"

using namespace std;

template<class T>
void print(T i){
    cout << i << endl;
}
class PlanarCompare;

int main(int argc, char* argv[]){
    //int* a = 0;
    // *a = 1;
    ifstream fis0("data/cube2.obj");
    ifstream fis1("data/tetrahedron.obj");
    ifstream fis2("data/tetrahedron2.obj");
    Yinset y1, y2, y3;
    fis0 >> y1;
    fis1 >> y2;
    //fis2 >> y3;
    y1.meet(y2);
    /*
    Segment seg = Data::segments[23];
    Point p0 = Data::points[seg[0]],
        p1 = Data::points[seg[1]],
        p;
    p = p0 + (p1 - p0)/2;
    */
    /*
    Yinset y3 = y2.complement();
    set<Planar, PlanarCompare> planars;
    for(auto i = Data::planars.begin(); i != Data::planars.end(); i++){
        planars.insert(i->second);
    }
    for(auto i = planars.begin(); i != planars.end(); i++){
        print(i->getid());
    }
    Planar pl = Data::planars[15];
    Planar pl0 = pl.overturn(),
        pl1 = Data::planars[5].overturn();
    vector<int> points = pl0.getpoints();
    Point p0 = Data::points[points[0]],
        p1 = Data::points[points[1]],
        p2 = Data::points[points[2]];
    Direction d1 = p1 - p0,
        d2 = p2 - p0,
        d3 = pl.getnormaldirect()*(Tol::t - 1e-5 * Tol::t),
        d4(Tol::t/2, Tol::t/2, Tol::t/2);
    Point p3 = p0 + d1 * 0.5 + d2 * 0.2,
        p4 = p0 + d1 * -4 + d2 * 0.7,
        p5 = p0 + d1 * 0 + d2 * 0.3;
    */
    /*
    print(pl.ifcontainPoint(p0));
    print(pl.ifcontainPoint(p3));
    print(pl.ifcontainPoint(p4));
    print(pl.ifcontainPoint(p5));
    print(pl.ifcontainPoint(p5 + d3));
    print(pl.ifcontainPoint(p5 + d4));
    print(pl.ifcontainPoint(p5));
    print(pl0.ifcontainPoint(p0));
    print(pl0.ifcontainPoint(p3));
    print(pl0.ifcontainPoint(p3 + d3));
    print(pl0.ifcontainPoint(p3 + d4));
    print(pl0.ifcontainPoint(p4));
    print(pl0.ifcontainPoint(p5));
    print(pl1.ifcontainPoint(p3));
    Point pk(2, 1, -1, Data::pointsnum++);
    Segment seg0(2, 6),
        seg1(2, 5),
        seg2(2, 8),
        seg3(pk.getid(), 2);
    print(pl.ifintersectionSegment(seg0));
    print(pl.ifintersectionSegment(seg1));
    print(pl.ifintersectionSegment(seg2));
    print(pl.ifintersectionSegment(seg3));
    print(pl0.ifintersectionSegment(seg2));
    print(pl0.ifintersectionSegment(seg3));
    print(pl0.intersectionSegment(seg2));
    print(pl0.intersectionSegment(seg1));
    print(pl0.intersectionSegment(seg0));
    */
    /*
    Line l(Point(0, 0, 2), Direction(0, 1, 0));
    (*Tol::l) = l;
    (*Tol::outside) = l.getdirect().cross(Direction(0, 0, 1)).unit();
    Point p1(0, 0, 4, 1),
        p2(0, 6, 4, 2),
        p3(0, 7, 4, 3),
        p4(0, 9, 4, 4),
        p5(0, 2, 2, 5),
        p6(0, 5, 2, 6),
        p7(0, 8, 2, 7),
        p8(0, 2, 0, 8),
        p9(0, 3, 0, 9),
        p10(0, 5, 0, 10),
        p11(0, 7, 0, 11),
        p12(0, 10, 0, 12);
    Segment seg1(3, 6, 1),
        seg2(7, 11, 2),
        seg3(9, 6, 3),
        seg4(6, 7, 4),
        seg5(8, 1, 5),
        seg6(7, 12, 6),
        seg7(4, 7, 7),
        seg8(5, 6, 8),
        seg9(6, 10, 9),
        seg10(2, 6, 10),
        seg11(3, 9, 11),
        seg12(7, 5, 12);
    cout << seg11.ifcontainPoint(p11) << endl
         << seg11.ifcontainPoint(p6) << endl
         << seg12.ifcontainPoint(p6) << endl
         << seg12.ifcontainPoint(p5) << endl
         << seg11.ifintersectionSegment(seg5) << endl
         << seg11.ifintersectionSegment(seg12) << endl
         << seg11.ifoverlapSegment(seg12) << endl
         << seg11.ifoverlapSegment(seg1) << endl
         << seg11.intersectionSegment(seg12) << endl;
    Segment overlap = seg11.overlapSegment(seg3);
    set<Segment> sweep;
    for(auto i = 1; i < 11; i++){
        sweep.insert(Data::segments[i]);
    }
    for(auto i = sweep.begin(); i != sweep.end(); i++){
        cout << i->getid() << endl;
    }
    */
    /*
    double x = M_PI,
        y = M_PI;
    x /= 17;
    x *= 17;
    cout << (y >= M_PI) << endl
         << (y > M_PI) << endl
         << (y == M_PI) << endl
         << (y < x) << endl;
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
        pp2 = p0 + (p0 - p1) * 3;
    */
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
    //cout << pl0.angleBetweenFlats(f, d1) << endl
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