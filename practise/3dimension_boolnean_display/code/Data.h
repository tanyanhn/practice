#ifndef DATA_BOOLEAN
#define DATA_BOOLEAN

#include"Point.h"
#include"Segment.h"
//#include"Planar.h"
//#include"Face.h"
//#include"Spajor.h"
#include<map>
#include<vector>

class Point;
class Segment;

struct Data {
    static std::vector<int> existpoints;
    static std::vector<int> existsegments;
    static std::vector<int> existplanars;
    static std::vector<int> existfaces;
    static std::map<int, Point> points;
    static std::map<int, Segment> segments;
};

std::vector<int> Data::existpoints;
std::vector<int> Data::existsegments;
std::vector<int> Data::existplanars;
std::vector<int> Data::existfaces;
std::map<int, Point> Data::points;
std::map<int, Segment> Data::segments;

#endif