#include"Line.h"
using namespace std;

const double Line::angle(const Point& pp) const {
    Line l = *this;
    if(pp.getidentity() != lp[0] && pp.getidentity() != lp[1]){
        cout << "angle p not in line wrong";
        exit(0);
    }
    Point p0, p1;
    if(l.lp[0] == pp.getidentity()){
        p0 = Sweepline::points[lp[0]];
        p1 = Sweepline::points[lp[1]];
    }
    else{
        p0 = Sweepline::points[lp[1]];
        p1 = Sweepline::points[lp[0]];
    }
    Point p = p1 - p0;
    double d;
    if(p[0] > 0){
        d = atan(p[1] / p[0]);
        if(p1 > p0)
            d = d + 2 * PI;
    }
    else if(p[0] < 0){
        d = atan(-p[1] / p[0]);
        d = PI - d;
    }
    else {
        if(p[1] > 0) d = PI / 2;
        else if(p[1] < 0) d = PI * 3 / 2;
        else cout << "angle() two point coincide wrong";
    }
    return d;
}



const int Line::ifintheline(const Point& p) const {
    Line l = *this;
    Point lp1 = Sweepline::points[l[0]], lp2 = Sweepline::points[l[1]];
    if(p == lp1 || p == lp2) return 1;
    if((p[0] < min(lp1[0], lp2[0]) - Sweepline::tol) ||
       (p[0] > max(lp1[0], lp2[0]) + Sweepline::tol) ||
       (p[1] < min(lp1[1], lp2[1]) - Sweepline::tol) ||
       (p[1] > max(lp1[1], lp2[1]) + Sweepline::tol))
        return 0;
    Point p1 = Point(p[0] - Sweepline::tol, p[1] - Sweepline::tol);
    Point p2 = Point(p[0] + Sweepline::tol, p[1] - Sweepline::tol);
    Point p3 = Point(p[0] - Sweepline::tol, p[1] + Sweepline::tol);
    Point p4 = Point(p[0] + Sweepline::tol, p[1] + Sweepline::tol);
    if(((p1 - lp1).cross(lp1 - lp2) * (p - lp1).cross(lp1 - lp2) > 0) &&
       ((p2 - lp1).cross(lp1 - lp2) * (p - lp1).cross(lp1 - lp2) > 0) &&
       ((p3 - lp1).cross(lp1 - lp2) * (p - lp1).cross(lp1 - lp2) > 0) &&
       ((p4 - lp1).cross(lp1 - lp2) * (p - lp1).cross(lp1 - lp2) > 0))
        return 0;
    return 1;
}




const bool Line::ifintersection(const Line& l) const {
    vector<Point>& points = Sweepline::points;
    Line l1 = *this, l2 = l;
    Point p10 = points[l1[0]], p11 = points[l1[1]], p20 = points[l2[0]], p21 = points[l2[1]];
    if(((p10 - p20).cross(p20 - p21)) * ((p11 - p20).cross(p20 - p21)) <0 &&
       ((p20 - p10).cross(p10 - p11)) * ((p21 - p10).cross(p10 - p11)) <0)
        return true;
    return false;
}




const Point Line::intersection(const Line& l2) const {
    const Line l1 = *this;
    vector<Point>& points = Sweepline::points;
    Point p1 = points[l1[0]], p2 = points[l1[1]], p3 = points[l2[0]], p4 = points[l2[1]];
    double s1 = fabs((p1 - p2).cross(p2 - p3)), s2 = fabs((p1 - p2).cross(p2 - p4));
    return Point((p4[0] * s1 + p3[0] * s2) / (s1 + s2), (p4[1] * s1 + p3[1] * s2) / (s1 + s2));
}




const bool Line::operator<(const Line& l2) const {
    vector<Point>& points = Sweepline::points;
    vector<Line>& lines = Sweepline::lines;
    Line l1 = lines[this->identity];
    double y = Sweepline::y;
    double x1 = min(min(points[l1[0]][0], points[l1[1]][0]),
                    min(points[l2[0]][0], points[l2[1]][0]));
    double x2 = max(max(points[l1[0]][0], points[l1[1]][0]),
                    max(points[l2[0]][0], points[l2[1]][0]));
    int k = points.size();
    Point a1(x1, y, k);
    Point a2(x2, y, k + 1);
    Sweepline::points.push_back(a1);
    Sweepline::points.push_back(a2);
    int k1 = lines.size();
    Line l3(a1.getidentity(), a2.getidentity(), k1);
    lines.push_back(l3);
    Point p1, p2;
    Point l1p0 = points[l1[0]], l1p1 = points[l1[1]], l2p0 = points[l2[0]], l2p1 = points[l2[1]];
    if(l1p0 > l1p1) {
        l1p0 = points[l1[1]];
        l1p1 = points[l1[0]];
    }
    if(l2p0 > l2p1) {
        l2p0 = points[l2[1]];
        l2p1 = points[l2[0]];
    }
    if(l3.ifintheline(l1p1))
        p1 = l1p1;
    if(l3.ifintheline(l1p0))
        p1 = l1p0;
    if(l3.ifintheline(l2p1))
        p2 = l2p1;
    if(l3.ifintheline(l2p0))
        p2 = l2p0;
    if(l3.ifintheline(l2p0) == false && l3.ifintheline(l2p1) == false)
        p2 = l2.intersection(l3);
    if(l3.ifintheline(l1p0) == false && l3.ifintheline(l1p1) == false)
        p1 = l1.intersection(l3);
    Sweepline::points.pop_back();
    Sweepline::points.pop_back();
    Sweepline::lines.pop_back();
    if(p1 == p2) {
        //&& (fabs(l1p0[1] - l1p0[1]) < Sweepline::tol || fabs(l2p0[1] - l2p1[1] < Sweepline::tol))){
        if((l1p0[1] > (y + Sweepline::tol)) && (l2p0[1] > (y + Sweepline::tol)))
            return l1.angle(l1p1) > l2.angle(l2p1);
        else if((l1p0[1] > (y + Sweepline::tol)))
            return l1.angle(l1p1) > l2.angle(l2p0);
        else if((l2p0[1] > (y + Sweepline::tol)))
            return l1.angle(l1p0) > l2.angle(l2p1);
        else
            return l1.angle(l1p0) < l2.angle(l2p0);
    }
    return p1[0] < p2[0];
}


const bool Line::operator>(const Line& l2)const {
    return l2 < *this;
}



void Line::generator() {
    vector<Point> points = Sweepline::points;
    vector<Line>& lines = Sweepline::lines;
    AVLTree<int> existl = Sweepline::existlines;
    vector<Jordanline>& jordanlines = Sweepline::jordanlines;
    vector<int>& existjordanlines = Sweepline::existjordanlines;
    vector<int> jordanline;
    int l, p, k;
    k = Sweepline::jordanlines.size();
    AVLTree<pair<int, int>> jvl;
    while(true){
        if(existl.findfirstnode() == NULL) break;
        l = (existl.findfirstnode())->data;
        p = lines[l][0];
        jvl.add(make_pair(p, l));
        while(true){
            int l1 = l;
            int p2 = lines[l1][1];
            int l2 = (points[p2].nextline(lines[l1]).getidentity());
            p = p2;
            l = l2;
            while(jvl.find(make_pair(p, l)) != NULL){
                int pp1 = (jvl.find(make_pair(p, l))->data).first;
                int ll1 = (jvl.find(make_pair(p, l))->data).second;
                int pp2 = lines[ll1][1];
                p = pp2;
                if(p == p2){
                    points[pp1].delnearline(lines[ll1]);
                    points[pp2].delnearline(lines[ll1]);
                    // if(l2 = ll1) l2 = (points[p2].nextline(lines[prevl]).getidentity());
                    jvl.del(make_pair(pp1, ll1));
                    existl.del(ll1);
                    lines[ll1].setinjordanline(k);
                    jordanline.push_back(ll1);
                    Jordanline jordan(jordanline, k);
                    jordanlines.push_back(jordan);
                    jordanline.erase(jordanline.begin(), jordanline.end());
                    existjordanlines.push_back(k);
                    k++;
                    break;
                }
                int ll2 = (points[pp2].nextline(lines[ll1])).getidentity();
                points[pp1].delnearline(lines[ll1]);
                if(pp1 == p2 && ll1 == l2 && points[p2].nearline.getsize() > 1) l2 = (points[p2].nextline(lines[l1]).getidentity());
                points[pp2].delnearline(lines[ll1]);
                jvl.del(make_pair(pp1, ll1));
                existl.del(ll1);
                lines[ll1].setinjordanline(k);
                jordanline.push_back(ll1);
                l = ll2;
            }
            if(jvl.empty()) break;
            // int l2 = (points[p2].nextline(lines[l1]).getidentity());
            p = p2;
            l = l2;
            jvl.add(make_pair(p, l));
        }
    }
}