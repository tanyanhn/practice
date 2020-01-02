#include"Point.h"
//#include"BalanceTree.h"
using namespace std;


bool Point::operator==(const Point& p) const {
    if(fabs(coord[0] - p[0]) < Sweepline::tol && fabs(coord[1] - p[1]) < Sweepline::tol) return true;
    else return false;
}
bool Point::operator<(const Point& p) const {
    if(coord[1] > p[1] + Sweepline::tol){
        return true;
    }
    else if(coord[1] > p[1] - Sweepline::tol && coord[0] > p[0] + Sweepline::tol) {
        return true;
    }
    return false;
}









Line Point::nextline(const Line& l2){
    bool t = false, t1 = false;
    Line l1;
    vector<int> l2v;
    l2v.push_back(l2.getidentity());
    AVLTreeNode<pair<double, vector<int>>>* k = nearline.find(make_pair(l2.angle(*this), l2v));
    if(k == NULL) cout << "nextline() k out of range";
    k = nearline.findnextnode(k);
    if(k == NULL) k = nearline.findfirstnode();
    if(k != NULL){
        for(auto i = 0; i < k->data.second.size(); i++){
            if(t == true && t1 == false){
                if(Sweepline::lines[k->data.second[i]][0] == identity){
                    t1 = true;
                    l1 = Sweepline::lines[k->data.second[i]];
                }
            }
            if(k->data.second[i] == l2.getidentity()){
                t = true;
            }
        }
    }
    if(t1 != true){
        k = nearline.find(make_pair(l2.angle(*this), l2v));
        if(k != NULL){
            for(auto i = 0; i < k->data.second.size(); i++){
                if(t == true && t1 == false){
                    if(Sweepline::lines[k->data.second[i]][0] == identity){
                        t1 = true;
                        l1 = Sweepline::lines[k->data.second[i]];
                    }
                }
                if(t == false && k->data.second[i] == l2.getidentity()){
                    t = true;
                }
            }
        }
    }
    int test = 0;
    while(t1 != true){
        k = nearline.findprevnode(k);
        if(k == NULL){
            k = nearline.findlastnode();
            if(test < 2)
                test++;
            else {
                cout << "nextnearline() wrong test";
                 exit(0);
                //Sweepline::points[999999999999];
            }
        }
        if(k != NULL){
            for(auto i = 0; i < k->data.second.size(); i++){
                if(t == true && t1 == false){
                    if(Sweepline::lines[k->data.second[i]][0] == identity){
                        t1 = true;
                        l1 = Sweepline::lines[k->data.second[i]];
                    }
                }
                if(t == false && k->data.second[i] == l2.getidentity()){
                    t = true;
                }
            }
        }
        if(t1 == true) break;
    }
    return l1;
}





void Point::addnearline(const Line& l){
    vector<int> lv;
    lv.push_back(l.getidentity());
    pair<double, vector<int>> pa = make_pair(l.angle(*this), lv);
    AVLTreeNode<pair<double, vector<int>>>* k = NULL;
    if(nearline.find(pa) != NULL) k = nearline.find(pa);
    if(k == NULL)
        nearline.add(pa);
    else
        k->data.second.push_back(l.getidentity());
}





void Point::delnearline(const Line& l2){
    bool t = false;
    vector<int> l2v;
    l2v.push_back(l2.getidentity());
    AVLTreeNode<pair<double, vector<int>>>* k = nearline.find(make_pair(l2.angle(*this), l2v));
    if(k == NULL) {
        // cout << "nextline() k out of range";
        return;
    }
    k = nearline.findprevnode(k);
    if(k == NULL) k = nearline.findlastnode();
    if(k != NULL){
        auto i = k->data.second.begin();
        while(i != k->data.second.end()){
            if(t == false && (*i) == l2.getidentity()){
                t = true;
                if (k->data.second.size() == 1){
                    nearline.del(k);
                    break;
                }
                else{
                    k->data.second.erase(i);
                    break;
                }
            }
            i++;
        }
    }
    else cout << "delnearline() wrong";
    if(t != true){
        k = nearline.find(make_pair(l2.angle(*this), l2v));
        if(k != NULL){
            auto i = k->data.second.begin();
            while(i != k->data.second.end()){
                if(t == false && (*i) == l2.getidentity()){
                    t = true;
                    if(k->data.second.size() == 1){
                        nearline.del(k);
                        break;
                    }
                    else{
                        k->data.second.erase(i);
                        break;
                    }
                }
                i++;
            }
        }
    }
    bool test = false;
    while(t != true){
        k = nearline.findnextnode(k);
        if(k == NULL){
            k = nearline.findfirstnode();
            if(test == false)
                test = true;
            else {
                cout << "nextnearline() wrong test";
                exit(0);
            }
        }
        if(k != NULL){
            auto i = k->data.second.begin();
            while(i != k->data.second.end()){
                if(t == false && (*i) == l2.getidentity()){
                    t = true;
                    if(k->data.second.size() == 1){
                        nearline.del(k);
                        break;
                    }
                    else{
                        k->data.second.erase(i);
                        break;
                    }
                }
                i++;
            }
        }
        // if(t == true) break;
    }
}


/*

void Point::delnearline(const Line& l2){
    bool t = false;
    vector<int> l2v;
    l2v.push_back(l2.getidentity());
    AVLTreeNode<pair<double, vector<int>>* k = nearline.find(make_pair(l2.angle(*this), l2v));
    if(k == NULL) cout << "nextline() k out of range";
    k = nearline.findprevnode(k);
    if(k == NULL) k = nearline.findlastnode();
    if(k != NULL){
        auto i = k->data.second.begin();
        while(i != k->data.second.end()){
            if(t == false && (*i) == l2.getidentity()){
                t = true;
                if (k->data.second.size() == 1){
                    nearline.del(k);
                    break;
                }
                else{
                    k->data.second.erase(i);
                    break;
                }
            }
            i++;
        }
    }
    else cout << "delnearline() wrong";
    if(t != true){
        k = nearline.find(make_pair(l2.angle(*this), l2v));
        if(k != NULL){
            auto i = k->data.second.begin();
            while(i != k->data.second.end()){
                if(t == false && (*i) == l2.getidentity()){
                    t = true;
                    if(k->data.second.size() == 1){
                        nearline.del(k);
                        break;
                    }
                    else{
                        k->data.second.erase(i);
                        break;
                    }
                }
                i++;
            }
        }
    }
    bool test = false;
    while(t != true){
        k = nearline.findnextnode(k);
        if(k == NULL){
            k = nearline.findfirstnode();
            if(test == false)
                test = true;
            else {
                cout << "nextnearline() wrong test";
                exit(0);
            }
        }
        if(k != NULL){
            auto i = k->data.second.begin();
            while(i != k->data.second.end()){
                if(t == false && (*i) == l2.getidentity()){
                    t = true;
                    if(k->data.second.size() == 1){
                        nearline.del(k);
                        break;
                    }
                    else{
                        k->data.second.erase(i);
                        break;
                    }
                }
                i++;
            }
        }
        if(t1 == true) break;
    }
}*/