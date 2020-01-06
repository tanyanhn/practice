#ifndef DATA_BOOLEAN
#define DATA_BOOLEAN

#include"Point.h"
#include"Segment.h"
#include"Planar.h"
#include"Face.h"
#include"Yinset.h"
#include"HassNode.h"
#include<map>
#include<vector>

class Point;
class Segment;
class Planar;
class Face;
class Yinset;
class HassNode;

struct Data {
    static Point farpoint;
    static std::vector<int> existpoints;
    static std::vector<int> existsegments;
    static std::vector<int> existplanars;
    static std::vector<int> existfaces;
    static std::map<int, Point> points;
    static int pointsnum;
    static std::map<int, Segment> segments;
    static int segmentsnum;
    static std::map<int, Planar> planars;
    static int planarsnum;
    static std::map<int, Face> faces;
    static int facesnum;
    static std::map<int, Yinset> yinsets;
    static int yinsetsnum;
    static void load(Yinset&) ;
    static void clean();
    static Yinset& meet(Yinset&, Yinset&);
    static Yinset& join(Yinset&, Yinset&);
    static Yinset& complement(Yinset& );
    static std::vector<Planar> intersection();
    static std::vector<Planar> triangulation();
    static std::vector<Planar> meetFace();
    static std::vector<Face> past();
    static std::vector<HassNode> generatehassmap();
};

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

#endif