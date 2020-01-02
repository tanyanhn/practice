#include"Point.h"
#include"Line.h"
#include"Spajor.h"
#include"Sweepline.h"
#include<iostream>
#include<fstream>
using namespace std;
#include<ctime>
void settol(double d){
    Sweepline::settol(d);
    return;
}

Spajor input(istream& is){
    return Sweepline::input(is);
}

void completeclean(){
    Sweepline::completeclean();
}

int main(int argc, char* argv[]){
    settol(1e-12);
    time_t t1 = clock();
    //if(argc == 0) return 0;
    ifstream is1(argv[1]);
    ifstream is2(argv[2]);
    ofstream os1(argv[3]);
    ofstream os2(argv[4]);
    ofstream os3(argv[5]);
    ofstream os4(argv[6]);
    Spajor s1 = input(is1);
    Spajor complements1 = s1.complement();
    Spajor s2 = input(is2);
    Spajor s3 = s1.meet(s2);
    os1 << s3;
    // completeclean();
    //ifstream is3(argv[1]);
    //ifstream is4(argv[2]);
    //Spajor s7 = input(is3);
    //Spajor s8 = input(is4);
    Spajor s4 = s1.join(s2);
    Spajor s5 = s1.complement();
    Spajor s6 = s2.complement();
    os2 << s4;
    os3 << s5;
    os4 << s6;
    //Point p(5.5, 3);
    // cout << s3.IfInSpajor(p) << endl;
    //cout << complements1;
    //cout << s2;
    //double d;
    //is1 >> d;
    //cout << d;
    /*
    double d[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Point p1(1, 2, 1), p2(2, 3, 2), p3(3, 4, 3), p4(5, 9, 4);
    Sweepline::points.push_back(p1);
    Sweepline::points.push_back(p2);
    Sweepline::points.push_back(p3);
    Sweepline::points.push_back(p4);
    Line l1(1, 3, 1), l2(1, 4, 2);
    p1.addnearline(l1);
    p1.addnearline(l2);
    Point p5 ;3
    Point p6 = p1;
    p5 = p1;
    p5.delnearline(l1);
    p5.delnearline(l2);*/

    std::cout << "\n TIME: " << (double)(clock() - t1)/CLOCKS_PER_SEC << std::endl;
}