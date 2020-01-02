#include"Sweepline.h"


double Sweepline::y = 100000;
double Sweepline::tol = 1e-10;
AVLTree<Point> Sweepline::eventpoint;
AVLTree<pair<int, AVLTreeNode<Point>*>> Sweepline::eventpointmark;
AVLTree<Line> Sweepline::orderline, Sweepline::orderline2, Sweepline::orderline3;
AVLTree<pair<int, AVLTreeNode<Line>*>> Sweepline::orderlinemark, Sweepline::orderlinemark2, Sweepline::orderlinemark3;
vector<Point> Sweepline::points;
vector<Line> Sweepline::lines;
vector<Jordanline> Sweepline::jordanlines;
vector<Spajor> Sweepline::spajors;
AVLTree<int> Sweepline::existpoints;
AVLTree<int> Sweepline::existlines;
vector<int> Sweepline::existjordanlines;
AVLTreeNode<Line>* Sweepline::xx = NULL;
AVLTreeNode<Point>* Sweepline::xp = NULL;



void Sweepline::completeclean(){
    clean();
    points.clear();
    lines.clear();
    jordanlines.clear();
    spajors.clear();
}

void Sweepline::enter(const Spajor& s){
    int k = s.size();
    for(auto i = 0; i < k; i++){
        // existjordanlines.push_back(s[i]);
        Jordanline jl = jordanlines[s[i]];
        for(auto j = 0; j < jl.size(); j++){
            if(existpoints.find(lines[jl[j]][0]) == NULL)existpoints.add(lines[jl[j]][0]);
            if(existpoints.find(lines[jl[j]][1]) == NULL)existpoints.add(lines[jl[j]][1]);
            if(existlines.find(jl[j]) == NULL){
                existlines.add(jl[j]);
                points[lines[jl[j]][0]].addnearline(lines[jl[j]]);
                points[lines[jl[j]][1]].addnearline(lines[jl[j]]);
            }
        }
    }
}





void Sweepline::clean(){
    eventpoint.clean();
    eventpointmark.clean();
    orderline.clean();orderline2.clean();orderline3.clean();
    orderlinemark.clean();orderlinemark2.clean();orderlinemark3.clean();
    existpoints.clean();
    existlines.clean();
    existjordanlines.erase(existjordanlines.begin(), existjordanlines.end());
    for(auto i = 0; i < lines.size(); i++){
        // if(!points[lines[i][0]].nearline.empty())
        points[lines[i][0]].nearline.clean();
            // if(!points[lines[i][1]].nearline.empty())
        points[lines[i][1]].nearline.clean();
    }
}



const Spajor Sweepline::input(istream& is){
    clean();
    int jlnumb;
    if(!is) {
        cout << "istream is empty";
        exit(0);
    }
    is >> jlnumb;
    vector<int> jordanline;
    int kp = points.size();
    int kl = lines.size();
    // int kj = jordanlines.size();
    int ks = spajors.size();
    int linenumb;
    for(auto i = 0; i < jlnumb; i++){
        int mark = 0;
        double x = 0, y = 0;
        Point p1, p2, markp;
        Line l;
        vector<int> line;
        is >> linenumb;
        for(auto j = 0; j < linenumb; j++){
            is >> x;
            is >> y;
            p2 = Point(x, y, kp);
            points.push_back(p2);
            if(existpoints.find(kp) == NULL) existpoints.add(kp);
            kp++;
            if(mark == 0){
                markp = p2;
                mark = 1;
            }
            else {
                l = Line(p1.getidentity(), p2.getidentity(), kl, ks);
                points[p1.getidentity()].addnearline(l);
                points[p2.getidentity()].addnearline(l);
                lines.push_back(l);
                if(existlines.find(kl) == NULL) existlines.add(kl);
                line.push_back(kl);
                kl++;
            }
            p1 = p2;
        }
        p2 = markp;
        l = Line(p1.getidentity(), p2.getidentity(), kl, ks);
        points[p1.getidentity()].addnearline(l);
        points[p2.getidentity()].addnearline(l);
        lines.push_back(l);
        if(existlines.find(kl) == NULL) existlines.add(kl);
        line.push_back(kl);
        kl++;
        //Jordanline jl(line, kj);
        //        jordanlines.push_back(jl);
        //      existjordanlines.push_back(kj);
        //jordanline.push_back(kj);
        //kj++;
    }
    Sweepline::intersection();
    int spajor2 = Sweepline::spajors.size();
    Sweepline::update(spajor2, true);
    Line::generator();
    //int spajor2 = Sweepline::spajors.size();
    //Sweepline::update(spajor2, true);
    Spajor s = Jordanline::generator();
    Sweepline::clean();
    return s;
}


void Sweepline::intersection(){
    AVLTreeNode<int>* kk = existpoints.findfirstnode();
    AVLTreeNode<Point>* eventpointmarkp;
    while(kk != NULL){
        eventpointmarkp = eventpoint.add(points[kk->data]);
        eventpointmark.add(make_pair(kk->data, eventpointmarkp));
        kk = existpoints.findnextnode(kk);
    }
    AVLTreeNode<Line>* orderlinemarkp;
    AVLTreeNode<Line>* prev = NULL, *next = NULL;
    AVLTreeNode<Point>* atnp = eventpoint.findfirstnode();
    while(true){
        prev = NULL;
        next = NULL;
        Point p = points[(atnp->data).getidentity()];
        y = p[1];
        AVLTreeNode<Point>* m = eventpoint.findnextnode(atnp), *mt = NULL;
        while(m != NULL && m->data == p){
            Point q = m->data;
            AVLTreeNode<pair<double, vector<int>>>* z = q.nearline.findfirstnode();
            while(z != NULL){
                vector<int> vi = (z->data).second;
                for(auto k = 0; k < vi.size(); k++){
                    Line l1;
                    if(lines[vi[k]][0] == q.getidentity()){
                        //points[q.getidentity()].delnearline(lines[vi[k]]);
                        //lines[vi[k]][0] = p.getidentity();
                        int f = lines.size();
                        l1 = Line(p.getidentity(), lines[vi[k]][1], f);
                        l1.setinspajor(lines[vi[k]].getinspajor());
                        lines.push_back(l1);
                        points[lines[vi[k]][1]].delnearline(lines[vi[k]]);
                        points[lines[vi[k]][1]].addnearline(l1);
                        if(orderlinemark.find(make_pair(vi[k], xx)) != NULL){
                            orderlinemarkp = orderlinemark.find(make_pair(vi[k], xx))->data.second;
                            orderlinemarkp->data = l1;
                            orderlinemark.del(make_pair(vi[k], xx));
                            orderlinemark.add(make_pair(l1.getidentity(), orderlinemarkp));
                        }
                    }
                    else if(lines[vi[k]][1] == q.getidentity()){
                        //points[q.getidentity()].delnearline(lines[vi[k]]);
                        //lines[vi[k]][1] = p.getidentity();
                        int f = lines.size();
                        l1 = Line(lines[vi[k]][0], p.getidentity(), f);
                        l1.setinspajor(lines[vi[k]].getinspajor());
                        lines.push_back(l1);
                        points[lines[vi[k]][0]].delnearline(lines[vi[k]]);
                        points[lines[vi[k]][0]].addnearline(l1);
                        if(orderlinemark.find(make_pair(vi[k], xx)) != NULL){
                            orderlinemarkp = orderlinemark.find(make_pair(vi[k], xx))->data.second;
                            orderlinemarkp->data = l1;
                            orderlinemark.del(make_pair(vi[k], xx));
                            orderlinemark.add(make_pair(l1.getidentity(), orderlinemarkp));
                        }
                    }
                    else
                        cout << "m->data == p wrong";
                    existpoints.del(vi[k]);
                    existpoints.add(l1.getidentity());
                    points[p.getidentity()].addnearline(l1);
                    points[q.getidentity()].delnearline(lines[vi[k]]);
                }
                z = q.nearline.findnextnode(z);
            }
            //points[q.getidentity()].nearline.clean();
            mt = m;
            existpoints.del(q.getidentity());
            m = eventpoint.findnextnode(m);
            eventpoint.del(mt);
        }
        AVLTreeNode<pair<double, vector<int>>>* atndv = points[p.getidentity()].nearline.findfirstnode();
        while(true){
            if(atndv == NULL) break;
            if((atndv->data).first > PI - tol/100) break;
            vector<int> v = (atndv->data).second;
            for(auto i = 0; i < v.size(); i++){
                Line l = lines[v[i]];
                if(points[l[0]] < p || points[l[1]] < p){
                    // AVLTreeNode<Line>* xx = NULL;
                    if(orderlinemark.find(make_pair(l.getidentity(), xx)) == NULL) cout << "orderlinemark.find wrong";
                    orderlinemarkp = orderlinemark.find(make_pair(l.getidentity(), xx))->data.second;
                    prev = orderline.findprevnode(orderlinemarkp);
                    next = orderline.findnextnode(orderlinemarkp);
                    orderline.del(orderlinemarkp);
                    orderlinemark.del(make_pair(l.getidentity(), xx));
                }
            }
            atndv = points[p.getidentity()].nearline.findnextnode(atndv);
            if(atndv == NULL) break;
            if((atndv->data).first > PI - tol/100) break;
        }
        if(atndv != NULL){
            vector<int> v = (atndv->data).second;
            Line l = lines[v[0]];
            if(prev == NULL && next == NULL){
                orderlinemarkp = orderline.add(l);
                prev = orderline.findprevnode(orderlinemarkp);
                next = orderline.findnextnode(orderlinemarkp);
                orderline.del(orderlinemarkp);
            }
        }
        while(next != NULL && (next->data).ifintheline(p)){
            Line nextline = lines[(next->data).getidentity()];
            existlines.del(nextline.getidentity());
            next = orderline.findnextnode(next);
            orderline.del(orderlinemark.find(make_pair(nextline.getidentity(), xx))->data.second);
            orderlinemark.del(make_pair(nextline.getidentity(), xx));
            int k = lines.size();
            Line l1(nextline[0], p.getidentity(), k, nextline.getinspajor());
            lines.push_back(l1);
            k++;
            Line l2(p.getidentity(), nextline[1], k, nextline.getinspajor());
            lines.push_back(l2);
            points[p.getidentity()].addnearline(l1);
            points[p.getidentity()].addnearline(l2);
            points[nextline[0]].delnearline(nextline);
            points[nextline[0]].addnearline(l1);
            points[nextline[1]].delnearline(nextline);
            points[nextline[1]].addnearline(l2);
            // next = orderline.findnextnode(next);
            //if(next == NULL) break;
        }
        while(prev != NULL && (prev->data).ifintheline(p)){
            Line prevline = lines[(prev->data).getidentity()];
            existlines.del(prevline.getidentity());
            prev = orderline.findprevnode(prev);
            orderline.del(orderlinemark.find(make_pair(prevline.getidentity(), xx))->data.second);
            orderlinemark.del(make_pair(prevline.getidentity(), xx));
            int k = lines.size();
            Line l1(prevline[0], p.getidentity(), k, prevline.getinspajor());
            lines.push_back(l1);
            k++;
            Line l2(p.getidentity(), prevline[1], k, prevline.getinspajor());
            lines.push_back(l2);
            points[p.getidentity()].addnearline(l1);
            points[p.getidentity()].addnearline(l2);
            points[prevline[0]].delnearline(prevline);
            points[prevline[0]].addnearline(l1);
            points[prevline[1]].delnearline(prevline);
            points[prevline[1]].addnearline(l2);
            // prev = orderline.findprevnode(prev);
            // if(prev == NULL) break;
        }
        atndv = points[p.getidentity()].nearline.findfirstnode();
        Line leftl, rightl;
        int g = 0;
        Line l;
        while(true){
            if(atndv == NULL) break;
            vector<int> v = (atndv->data).second;
            AVLTreeNode<pair<double, vector<int>>>* atndvmark = atndv;
            for(auto i = 0; i < v.size(); i++){
                l = lines[v[i]];
                if(points[l[0]] > p || points[l[1]] > p){
                    if(g == 0){
                        leftl = l;
                        g = 1;
                    }
                    orderlinemarkp = orderline.add(l);
                    orderlinemark.add(make_pair(l.getidentity(), orderlinemarkp));
                }
            }
            vector<int> vk;
            atndvmark = points[p.getidentity()].nearline.find(make_pair(l.angle(p), vk));
            atndv = points[p.getidentity()].nearline.findnextnode(atndvmark);
            if(atndv == NULL){
                rightl = l;
                break;
            }
        }
        if(g == 1){
            if(prev != NULL)
                inter(prev->data, leftl, p);
            if(next != NULL)
                inter(rightl, next->data, p);
        }
        else {
            if(prev != NULL && next != NULL)
                inter(prev->data, next->data, p);
        }
        atnp = eventpoint.findnextnode(atnp);
        if(atnp == NULL) break;
    }
}








void Sweepline::inter(const Line& l1, const Line& l2, const Point& p1){
    AVLTreeNode<Line>* orderlinemarkp;
    Line prevl = lines[l1.getidentity()], l = lines[l2.getidentity()];
    Point lp0, lp1, prevlp0, prevlp1;
    if(points[l[0]] > points[l[1]]){
        lp0 = points[l[0]];
        lp1 = points[l[1]];
    }
    else if(points[l[0]] < points[l[1]]){
        lp0 = points[l[1]];
        lp1 = points[l[0]];
    }
    else
        cout << " two point in a line too close. in inter()";
    if(points[prevl[0]] > points[prevl[1]]){
        prevlp0 = points[prevl[0]];
        prevlp1 = points[prevl[1]];
    }
    else if(points[prevl[0]] < points[prevl[1]]){
        prevlp0 = points[prevl[1]];
        prevlp1 = points[prevl[0]];
    }
    else
        cout << "two points in a line too close. in inter() prevl";
    if((lp0 == prevlp0)){
        if(lp0.getidentity() == prevlp0.getidentity()) return;
        AVLTreeNode<pair<double, vector<int>>>* z = points[lp0.getidentity()].nearline.findfirstnode();
        while(z != NULL){
            vector<int> vi = (z->data).second;
            for(auto k = 0; k < vi.size(); k++){
                Line l1;
                if(lines[vi[k]][0] == lp0.getidentity()){
                    // points[lp0.getidentity()].delnearline(lines[vi[k]]);
                    //lines[vi[k]][0] = prevlp0.getidentity();
                    int f = lines.size();
                    l1 = Line(prevlp0.getidentity(), lines[vi[k]][1], f);
                    l1.setinspajor(lines[vi[k]].getinspajor());
                    lines.push_back(l1);
                    points[lines[vi[k]][1]].delnearline(lines[vi[k]]);
                    points[lines[vi[k]][1]].addnearline(l1);
                    if(orderlinemark.find(make_pair(vi[k], xx)) != NULL){
                        orderlinemarkp = orderlinemark.find(make_pair(vi[k], xx))->data.second;
                        orderlinemarkp->data = l1;
                        orderlinemark.del(make_pair(vi[k], xx));
                        orderlinemark.add(make_pair(l1.getidentity(), orderlinemarkp));
                    }
                }
                else if(lines[vi[k]][1] = lp0.getidentity()){
                    //points[lp0.getidentity()].delnearline(lines[vi[k]]);
                    // lines[vi[k]][1] = prevlp0.getidentity();
                    int f = lines.size();
                    l1 = Line(lines[vi[k]][0], prevlp0.getidentity(), f);
                    l1.setinspajor(lines[vi[k]].getinspajor());
                    lines.push_back(l1);
                    points[lines[vi[k]][0]].delnearline(lines[vi[k]]);
                    points[lines[vi[k]][0]].addnearline(l1);
                    if(orderlinemark.find(make_pair(vi[k], xx)) != NULL){
                        orderlinemarkp = orderlinemark.find(make_pair(vi[k], xx))->data.second;
                        orderlinemarkp->data = l1;
                        orderlinemark.del(make_pair(vi[k], xx));
                        orderlinemark.add(make_pair(l1.getidentity(), orderlinemarkp));
                    }
                }
                else
                    cout << "inter() lp0 == prevl wrong";
                existlines.del(vi[k]);
                existlines.add(l1.getidentity());
                points[prevlp0.getidentity()].addnearline(l1);
                points[lp0.getidentity()].delnearline(lines[vi[k]]);
            }
            z = points[lp0.getidentity()].nearline.findnextnode(z);
        }
        //points[lp0.getidentity()].nearline.clean();
        existpoints.del(lp0.getidentity());
        AVLTreeNode<Point>* mark = eventpointmark.find(make_pair(lp0.getidentity(), xp))->data.second;
        eventpoint.del(mark);
        eventpointmark.del(make_pair(lp0.getidentity(), xp));
        /*if(mark->data.getidentity() == lp0.getidentity())
          eventpoint.del(mark);
          else if(eventpoint.findprevnode(mark).getidentity() == lp0.getidentity())
          eventpoint.del(eventpoint.findprevnode(mark));
          else if(eventpoint.findnextnode(mark).getidentity() == lp0.getidentity())
          eventpoint.del(eventpoint.findnextnode(mark));
          else
          cout << "more than two point coincide";*/
    }
    else if(prevl.ifintheline(lp0)){
        int k = lines.size();
        Line l1(prevl[0], lp0.getidentity(), k, prevl.getinspajor());
        lines.push_back(l1);
        k++;
        Line l2(lp0.getidentity(), prevl[1], k, prevl.getinspajor());
        lines.push_back(l2);
        existlines.del(prevl.getidentity());
        existlines.add(l1.getidentity());
        existlines.add(l2.getidentity());
        orderlinemarkp = orderlinemark.find(make_pair(prevl.getidentity(), xx))->data.second;
        if(points[prevl[0]] < lp0) {
            orderlinemarkp->data = l1;
            orderlinemark.del(make_pair(prevl.getidentity(), xx));
            orderlinemark.add(make_pair(l1.getidentity(), orderlinemarkp));
        }
        else if(points[prevl[1]] < lp0){
            orderlinemarkp->data = l2;
            orderlinemark.del(make_pair(prevl.getidentity(), xx));
            orderlinemark.add(make_pair(l2.getidentity(), orderlinemarkp));
        }
        else
            cout << "inter() prevl[] lp0 wrong";
        points[lp0.getidentity()].addnearline(l1);
        points[lp0.getidentity()].addnearline(l2);
        points[prevl[0]].delnearline(prevl);
        points[prevl[0]].addnearline(l1);
        points[prevl[1]].delnearline(prevl);
        points[prevl[1]].addnearline(l2);
    }
    else if(l.ifintheline(prevlp0)){
        int k = lines.size();
        Line l1(l[0], prevlp0.getidentity(), k, l.getinspajor());
        lines.push_back(l1);
        k++;
        Line l2(prevlp0.getidentity(), l[1], k, l.getinspajor());
        lines.push_back(l2);
        existlines.del(l.getidentity());
        existlines.add(l1.getidentity());
        existlines.add(l2.getidentity());
        orderlinemarkp = orderlinemark.find(make_pair(l.getidentity(), xx))->data.second;
        if(points[l[0]] < prevlp0){
            orderlinemarkp->data = l1;
            orderlinemark.del(make_pair(l.getidentity(), xx));
            orderlinemark.add(make_pair(l1.getidentity(), orderlinemarkp));
        }
        else if(points[l[1]] < prevlp0){
            orderlinemarkp->data = l2;
            orderlinemark.del(make_pair(l.getidentity(), xx));
            orderlinemark.add(make_pair(l2.getidentity(), orderlinemarkp));
        }
        else
            cout << "inter() l[] prevlp0 wrong";
        points[prevlp0.getidentity()].addnearline(l1);
        points[prevlp0.getidentity()].addnearline(l2);
        points[l[0]].delnearline(l);
        points[l[0]].addnearline(l1);
        points[l[1]].delnearline(l);
        points[l[1]].addnearline(l2);
    }
    else {
        if(l.ifintersection(prevl)){
            Point p = prevl.intersection(l);
            if(p < p1) return;
            int k = points.size();
            p.setidentity(k);
            points.push_back(p);
            existpoints.add(k);
            k = lines.size();
            Line l1(p.getidentity(), prevl[1], k, prevl.getinspajor());
            k++;
            Line l2(prevl[0], p.getidentity(), k, prevl.getinspajor());
            k++;
            Line l3(l[0], p.getidentity(), k, l.getinspajor());
            k++;
            Line l4(p.getidentity(), l[1], k, l.getinspajor());
            lines.push_back(l1);
            lines.push_back(l2);
            lines.push_back(l3);
            lines.push_back(l4);
            existlines.del(prevl.getidentity());
            existlines.del(l.getidentity());
            existlines.add(l1.getidentity());
            existlines.add(l2.getidentity());
            existlines.add(l3.getidentity());
            existlines.add(l4.getidentity());
            points[p.getidentity()].addnearline(l1);
            points[p.getidentity()].addnearline(l2);
            points[p.getidentity()].addnearline(l3);
            points[p.getidentity()].addnearline(l4);
            points[l[0]].delnearline(l);
            points[l[0]].addnearline(l3);
            points[l[1]].delnearline(l);
            points[l[1]].addnearline(l4);
            points[prevl[0]].delnearline(prevl);
            points[prevl[0]].addnearline(l2);
            points[prevl[1]].delnearline(prevl);
            points[prevl[1]].addnearline(l1);
            eventpoint.add(points[p.getidentity()]);
            orderlinemarkp = orderlinemark.find(make_pair(prevl.getidentity(), xx))->data.second;
            orderlinemark.del(make_pair(prevl.getidentity(), xx));
            if(p > points[prevl[1]]){
                orderlinemarkp->data = l1;
                orderlinemark.add(make_pair(l1.getidentity(), orderlinemarkp));
            }
            else {
                orderlinemarkp->data = l2;
                orderlinemark.add(make_pair(l2.getidentity(), orderlinemarkp));
            }
            orderlinemarkp = orderlinemark.find(make_pair(l.getidentity(), xx))->data.second;
            orderlinemark.del(make_pair(l.getidentity(), xx));
            if(p > points[l[0]]){
                orderlinemarkp->data = l3;
                orderlinemark.add(make_pair(l3.getidentity(), orderlinemarkp));
            }
            else {
                orderlinemarkp->data = l4;
                orderlinemark.add(make_pair(l4.getidentity(), orderlinemarkp));
            }
        }
    }
}










void Sweepline::update(int spajor2, bool spajortype2, int spajor3, bool spajortype3){
    AVLTreeNode<int>* kk = existpoints.findfirstnode();
    //vector<Point> points = Sweepline::points;
    eventpoint.clean();
    while(kk != NULL){
        eventpoint.add(points[kk->data]);
        kk = existpoints.findnextnode(kk);
    }
    int m = 0;
    if(spajor3 != -1) m = 1;
    AVLTreeNode<Line>* orderlinemarkp;
    AVLTreeNode<Line>* prev = NULL;
    AVLTreeNode<Point>* atnp = eventpoint.findfirstnode();
    while(true){
        if(atnp == NULL) break;
        Point p = points[atnp->data.getidentity()];
        y = p[1];
        AVLTreeNode<pair<double, vector<int>>>* atndv = points[p.getidentity()].nearline.findfirstnode();
        while(true){
            if(atndv == NULL) break;
            vector<int> v = (atndv->data).second;
            for(auto i = 0; i < v.size(); i++){
                Line l = lines[v[i]];
                if(points[l[0]] < p || points[l[1]] < p){
                    if(m == 0){
                        if(orderlinemark.find(make_pair(l.getidentity(), xx)) == NULL) cout << "update() points[l[]] < p wrong";
                        orderlinemarkp = orderlinemark.find(make_pair(l.getidentity(), xx))->data.second;
                        prev = orderline.findprevnode(orderlinemarkp);
                        if(prev != NULL)
                            lines[l.getidentity()].setleftline(prev->data.getidentity());
                        else
                            lines[l.getidentity()].setleftline(-1);
                        orderline.del(orderlinemarkp);
                        orderlinemark.del(make_pair(l.getidentity(), xx));
                    }
                    if(m == 1){
                        if(l.getinspajor() != spajor2){
                            if(orderlinemark3.find(make_pair(l.getidentity(), xx)) == NULL) cout << "update() orderlinemark3.find wrong";
                            orderline3.del(orderlinemark3.find(make_pair(l.getidentity(), xx))->data.second);
                            orderlinemark3.del(make_pair(l.getidentity(), xx));
                            //  if(fabs(points[l[1]][1] - points[l[0]][1]) > tol ){
                                orderlinemarkp = orderline2.add(l);
                                /*}
                            else {
                                if(points[l[1]] > points[l[0]]){
                                    int k = points.size();
                                    Point p(points[l[0]][0] - tol, points[l[0]][1], k);
                                    points.push_back(p);
                                    int f = l[0];
                                    lines[l.getidentity()][0] = k;
                                    orderlinemarkp = orderline2.add(l);
                                    lines[l.getidentity()][0] = f;
                                    points.pop_back();
                                }
                                else {
                                    int k = points.size();
                                    Point p(points[l[1]][0] - tol, points[l[1]][1], k);
                                    points.push_back(p);
                                    int f = l[1];
                                    lines[l.getidentity()][1] = k;
                                    orderlinemarkp = orderline2.add(l);
                                    lines[l.getidentity()][1] = f;
                                    points.pop_back();
                                }
                                }*/
                            prev = orderline2.findprevnode(orderlinemarkp);
                            /*}
                              else{
                              orderlinemarkp = orderline2.add(l);
                              prev = orderline2.findprevnode(orderlinemarkp);
                              while(!(*prev > l))
                              }*/
                            if(prev == NULL){
                                lines[l.getidentity()].setIfInOtherYinset(spajortype2);
                            }
                            else {
                                Point p0 = points[(prev->data)[0]], p1 = points[(prev->data)[1]];
                                if(p0 < p1)
                                    lines[l.getidentity()].setIfInOtherYinset(true);
                                else
                                    lines[l.getidentity()].setIfInOtherYinset(false);
                            }
                            orderline2.del(orderlinemarkp);
                        }
                        else if(l.getinspajor() == spajor2){
                            if(orderlinemark2.find(make_pair(l.getidentity(), xx)) == NULL) cout << "update() orderlinemark2.find wrong";
                            orderline2.del(orderlinemark2.find(make_pair(l.getidentity(), xx))->data.second);
                            orderlinemark2.del(make_pair(l.getidentity(), xx));
                            //orderlinemarkp = orderline3.add(l);
                            //   if(fabs(points[l[1]][1] - points[l[0]][1]) > tol ){
                                orderlinemarkp = orderline3.add(l);
                                /*    }
                            else {
                                if(points[l[1]] > points[l[0]]){
                                    int k = points.size();
                                    Point p(points[l[0]][0] - tol, points[l[0]][1], k);
                                    points.push_back(p);
                                    int f = l[0];
                                    l[0] = k;
                                    orderlinemarkp = orderline3.add(l);
                                    l[0] = f;
                                    points.pop_back();
                                }
                                else {
                                    int k = points.size();
                                    Point p(points[l[1]][0] - tol, points[l[1]][1], k);
                                    points.push_back(p);
                                    int f = l[1];
                                    lines[l.getidentity()][1] = k;
                                    orderlinemarkp = orderline3.add(l);
                                    lines[l.getidentity()][1] = f;
                                    points.pop_back();
                                }
                                }*/
                            prev = orderline3.findprevnode(orderlinemarkp);
                            if(prev == NULL){
                                lines[l.getidentity()].setIfInOtherYinset(spajortype3);
                            }
                            else {
                                Point p0 = points[(prev->data)[0]], p1 = points[(prev->data)[1]];
                                if(p0 < p1)
                                    lines[l.getidentity()].setIfInOtherYinset(true);
                                else
                                    lines[l.getidentity()].setIfInOtherYinset(false);
                            }
                            orderline3.del(orderlinemarkp);
                        }
                        else
                            cout << "update() l.getinspajor == spajor wrong";
                    }
                }
                if(points[l[0]] > p || points[l[1]] > p){
                    if(m == 0){
                        if(orderlinemark.find(make_pair(l.getidentity(), xx)) != NULL) cout << "update() points[l[]] > p orderlinemark wrong";
                        orderlinemarkp = orderline.add(l);
                        orderlinemark.add(make_pair(l.getidentity(), orderlinemarkp));
                    }
                    if(m == 1){
                        if(l.getinspajor() == spajor2){
                            orderlinemarkp = orderline2.add(l);
                            orderlinemark2.add(make_pair(l.getidentity(), orderlinemarkp));
                        }
                        else {
                            orderlinemarkp = orderline3.add(l);
                            orderlinemark3.add(make_pair(l.getidentity(), orderlinemarkp));
                        }
                    }
                }
            }
            atndv = points[p.getidentity()].nearline.findnextnode(atndv);
            //if(atndv == NULL) break;
        }
        atnp = eventpoint.findnextnode(atnp);
        //if(atnp == NULL) break;
    }
    if(m == 1){
        AVLTreeNode<int>* pt = existlines.findfirstnode();
        while(true){
            if(pt == NULL) break;
            int t = pt->data;
            Line l = lines[t];
            AVLTreeNode<int>* markpt = existlines.findnextnode(pt);
            if(l.getIfInOtherYinset() == false){
                existlines.del(t);
                Point p0 = points[l[0]], p1 = points[l[1]];
                points[p0.getidentity()].delnearline(l);
                points[p1.getidentity()].delnearline(l);
            }
            pt = markpt;
            if(pt == NULL) break;
        }
    }
}
