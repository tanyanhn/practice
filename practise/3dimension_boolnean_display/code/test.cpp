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
    Segment seg = Data::segments[15];
    Point p0 = Data::points[seg[0]],
        p1 = Data::points[seg[1]],
        p;
    p = p0 + (p1 - p0)/2;
    //cout << seg.ifcontainPoint(p) << endl;
    //p += Direction(Tol::t/2, 0, 0);
    //cout << seg.ifcontainPoint(p + Direction(Tol::t / 2, 0, 0)) << endl;
    //cout << seg.ifcontainPoint(p + Direction(Tol::t / 2, 0, Tol::t / 2)) << endl;
    //cout << seg.ifcontainPoint(p + Direction(Tol::t / 2, Tol::t, Tol::t / 2)) << endl;
    //cout << seg.ifcontainPoint(p0 + (p1 - p0) * 3) << endl;
    //cout << seg.ifcontainPoint(p0 + (p1 - p0) * -3) << endl;
    //cout << seg.ifcontainPoint(p0) << endl;
    //cout << seg.ifcontainPoint(p1) << endl;
    Line l1(p + Direction(Tol::t / 2, 0, Tol::t / 2), Direction(1 + Tol::t / 2, 0, 0));
    Line l2(p + Direction(Tol::t / 2, 0, Tol::t / 2), Direction(0, Tol::t / 2, 1 + Tol::t / 2));
    Line l3(p + Direction(Tol::t / 2, 0, Tol::t / 2), Direction(0, Tol::t * 2, 1));
    cout << l1.ifintersectionLine(seg) << endl;
    cout << l2.ifintersectionLine(seg) << endl;
    cout << l3.ifintersectionLine(seg) << endl;
    cout << l1.ifoverlapLine(seg) << endl;
    cout << l2.ifoverlapLine(seg) << endl;
    cout << l3.ifoverlapLine(seg) << endl;
    Point pp1 = l1.intersectionLine(seg),
        pp3 = l3.intersectionLine(seg);
    
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