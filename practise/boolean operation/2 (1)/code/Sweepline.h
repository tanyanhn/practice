#ifndef SWEEPLINE
#define SWEEPLINE

#include"Point.h"
#include"Line.h"
#include"Jordanline.h"
#include"Spajor.h"
#include"BalanceTree.h"
#include<vector>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;

const double PI = 3.1415926535897;
class Point;
class Line;
class Jordanline;
class Spajor;

class Sweepline  {
public:
    static double y;
    static double tol;
    static AVLTree<Point> eventpoint;
    static AVLTree<pair<int, AVLTreeNode<Point>*>> eventpointmark;
    static AVLTree<Line> orderline, orderline2, orderline3;
    static AVLTree<pair<int, AVLTreeNode<Line>*>> orderlinemark, orderlinemark2, orderlinemark3;
    static vector<Point> points;
    static AVLTree<int> existpoints;
    static vector<Line> lines;
    static AVLTree<int> existlines;
    static vector<Jordanline> jordanlines;
    static vector<int> existjordanlines;
    static vector<Spajor> spajors;
    static AVLTreeNode<Line>* xx;
    static AVLTreeNode<Point>* xp;
    Sweepline(){}
    Sweepline(const Sweepline&){}
    Sweepline& operator=(const Sweepline&){}
    ~Sweepline(){}
    static void intersection();
    static void inter(const Line&, const Line&, const Point&);
    static void update(int spajor2 = -1, bool spajortype2 = true, int spajor3 = -1, bool spajortype3 = true);
    static void settol(double t){
        Sweepline::tol = t;
    }
    static void clean();
    static void completeclean();
    static const Spajor input(istream&);
    static void enter(const Spajor&);
};

template<>
inline bool std::operator<(const pair<double, vector<int>>& left, const pair<double, vector<int>>& right){
    return left.first < right.first - Sweepline::tol / 100;
}

template<>
inline bool std::operator>(const pair<double, vector<int>>& left, const pair<double, vector<int>>& right){
    return left.first > right.first + Sweepline::tol / 100;
}


template<>
inline bool std::operator<(const pair<int, AVLTreeNode<Line>*>& left, const pair<int, AVLTreeNode<Line>*>& right){
    return left.first < right.first;
}

template<>
inline bool std::operator>(const pair<int, AVLTreeNode<Line>*>& left, const pair<int, AVLTreeNode<Line>*>& right){
    return left.first > right.first;
}


template<>
inline bool std::operator<(const pair<int, AVLTreeNode<Point>*>& left, const pair<int, AVLTreeNode<Point>*>& right){
    return left.first < right.first;
}

template<>
inline bool std::operator>(const pair<int, AVLTreeNode<Point>*>& left, const pair<int, AVLTreeNode<Point>*>& right){
    return left.first > right.first;
}


template<>
inline bool std::operator<(const pair<double, int>& left, const pair<double, int>& right){
    return left.first < right.first;
}

template<>
inline bool std::operator>(const pair<double, int>& left, const pair<double, int>& right){
    return left.first > right.first;
}

template<>
inline bool std::operator<(const pair<int, int>& left, const pair<int, int>& right){
    return left.first < right.first;
}

template<>
inline bool std::operator>(const pair<int, int>& left, const pair<int, int>& right){
    return left.first > right.first;
}


#endif