#ifndef DATA_BOOLEAN
#define DATA_BOOLEAN

//#include"Point.h"
//#include"Segment.h"
//#include"Planar.h"
//#include"Face.h"
//#include"Yinset.h"
//#include"HassNode.h"
#include<map>
#include<set>
#include<vector>
#include"STLHead.h"

class Point;
class Segment;
class Planar;
class Face;
class Yinset;
class HassNode;

class Data {
public:
    static Point farpoint;
    static std::set<int> existpoints;
    static std::set<int> existsegments;
    static std::set<int> existplanars;
    static std::set<int> existfaces;
    static std::vector<Point> points;
    static int pointsnum;
    static std::vector<Segment> segments;
    static int segmentsnum;
    static std::vector<Planar> planars;
    static int planarsnum;
    static std::vector<Face> faces;
    static int facesnum;
    static std::vector<Yinset> yinsets;
    static int yinsetsnum;
    static std::map<Point, std::set<int>> pastpoints;
    static void load(const Yinset&) ;
    static void clear();
    static void structcopy();
    static void print(std::ostream&, const Yinset&);
    static int import(std::istream&);
    static Yinset meet(const Yinset&, const Yinset&);
    static Yinset join(const Yinset&, const Yinset&);
    static Yinset complement(const Yinset& );
    static void intersection();
    static void triangulation();
    static void selecttriangles(const Yinset&, const Yinset&);
    static void past();
    static void f(){
        int* pi = 0;
        std::cout << *pi;
    }
    //static std::vector<HassNode> generatehassmap();
};
/*
Point Data::farpoint;
std::vector<int> Data::existpoints;
std::vector<int> Data::existsegments;
std::vector<int> Data::existplanars;
std::vector<int> Data::existfaces;
std::map<int, Point> Data::points;
std::map<int, Segment> Data::segments;
std::map<int, Planar> Data::planars;
std::map<int, Face> Data::faces;
std::map<int, Yinset> Data::yinsets;
int Data::pointsnum = 0;
int Data::segmentsnum = 0;
int Data::planarsnum = 0;
int Data::facesnum = 0;
int Data::yinsetsnum = 0;
*/

#endif