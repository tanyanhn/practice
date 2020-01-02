#include"Spajor.h"


const int Spajor::IfInSpajor(const Point& ip) const{
    vector<Point>& points = Sweepline::points;
    vector<Line>& lines = Sweepline::lines;
    AVLTree<int>& existlines = Sweepline::existlines;
    AVLTree<Line>& orderline = Sweepline::orderline;
    Sweepline::clean();
    Sweepline::y = ip[1];
    Sweepline::enter(*this);
    int k = points.size();
    Point p(ip[0], ip[1], k);
    Point q(ip[0], (ip[1] + 1), k + 1);
    points.push_back(p);
    points.push_back(q);
    k = lines.size();
    Line l(p.getidentity(), q.getidentity(), k);
    lines.push_back(l);
    /* for(auto i = 0; i < existlines.getsize(); i++){
        if(lines[existlines[i]].ifintheline(p) == 1){
            Sweepline::clean();
            return 0;
        }
        }*/
    double d1, d2;
    AVLTreeNode<int>* kk = existlines.findfirstnode();
    while(kk != NULL){
        if(lines[kk->data].ifintheline(p) == 1){
            Sweepline::clean();
            return 0;
        }
        d1 = points[lines[kk->data][0]][1];
        d2 = points[lines[kk->data][1]][1];
        if(((d1 > (p[1] - Sweepline::tol)) || (d2 > (p[1] - Sweepline::tol))) && ((d1 < (p[1] + Sweepline::tol)) || (d2 < (p[1] + Sweepline::tol))))
            orderline.add(lines[kk->data]);
        kk = existlines.findnextnode(kk);
    }
    /*
    double d1, d2;
    for(auto i = 0; i < existlines.getsize(); i++){
        d1 = points[lines[existlines[i]][0]][1];
        d2 = points[lines[existlines[i]][1]][1];
        if(((d1 > (p[1] - Sweepline::tol)) || (d2 > (p[1] - Sweepline::tol))) && ((d1 < (p[1] + Sweepline::tol)) || (d2 < (p[1] + Sweepline::tol))))
            orderline.add(lines[existlines[i]]);
            }*/
    AVLTreeNode<Line>* markl = orderline.add(l);
    markl = orderline.findprevnode(markl);
    points.pop_back();
    points.pop_back();
    lines.pop_back();
    if(markl == NULL) {
        if(type == true){
            Sweepline::clean();
            return 1;
        }
        else{
            Sweepline::clean();
            return -1;
        }
    }
    Line l1 = markl->data;
    if((fabs(points[l1[0]][1] - ip[1]) < Sweepline::tol) && (fabs(points[l1[1]][1] - ip[1]) < Sweepline::tol)){
        if(points[l1[0]] > points[l1[1]]){
            Sweepline::clean();
            return 1;
        }
        else{
            Sweepline::clean();
            return -1;
        }
    }
    else{
        if(points[l1[0]] > points[l1[1]]){
            Sweepline::clean();
            return -1;
        }
        else{
            Sweepline::clean();
            return 1;
        }
    }
}



const Spajor Spajor::complement() const {
    Sweepline::enter(*this);
    vector<int> markjordanline;
    vector<int> jordanl;
    for(int i = 0; i < jordanline.size(); i++){
        Jordanline jl = Sweepline::jordanlines[jordanline[i]];
        int k1 = Sweepline::jordanlines.size();
        for(int j = jl.size() - 1; j > -1; j--){
            /*     int m = Sweepline::lines[jl[j]][0];
            Sweepline::lines[jl[j]][0] = Sweepline::lines[jl[j]][1];
            Sweepline::lines[jl[j]][1] = m;*/
            int k = Sweepline::lines.size();
            Line l(Sweepline::lines[jl[j]][1], Sweepline::lines[jl[j]][0], k);
            l.setinjordanline(k1);
            Sweepline::lines.push_back(l);
            markjordanline.push_back(k);
        }
        Jordanline jordan(markjordanline, k1);
        int k = Sweepline::spajors.size();
        jordan.setinspajor(k);
        Sweepline::jordanlines.push_back(jordan);
        jordanl.push_back(k1);
        //       Sweepline::jordanlines[k].setline(markjordanline);
        markjordanline.erase(markjordanline.begin(), markjordanline.end());
    }
    //  type = !type;
    int k = Sweepline::spajors.size();
    Spajor s = *this;
    s.setjordanline(jordanl);
    s.settype(!type);
    s.setidentity(k);
    Sweepline::spajors.push_back(s);
    Sweepline::clean();
    return s;
}


const Spajor Spajor::meet(const Spajor& s) const {
    Sweepline::clean();
    Sweepline::enter(*this);
    Sweepline::enter(s);
    Sweepline::intersection();
    Sweepline::update(identity, type, s.identity, s.type);
    Sweepline::update();
    Line::generator();
    Spajor ss = Jordanline::generator();
    Sweepline::clean();
    return ss;
}


const Spajor Spajor::join(const Spajor& s) const{
    Spajor s1 = this->complement();
    Spajor s2 = s.complement();
    Spajor s3 = s1.meet(s2);
    Spajor s4 = s3.complement();
    return s4;
}

ostream& operator<<(ostream& os, const Spajor& s){
    os << s.size() << endl;
    for(auto i = 0; i < s.size(); i++)
        os << Sweepline::jordanlines[s[i]] << endl;
    return os;
}


