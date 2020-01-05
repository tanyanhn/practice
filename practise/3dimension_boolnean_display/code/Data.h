#ifndef DATA_BOOLEAN
#define DATA_BOOLEAN

#include"Point.h"
#include"Segment.h"
#include"Planar.h"
#include"Face.h"
#include"Yinset.h"
#include<map>
#include<vector>

class Point;
class Segment;
class Planar;
class Face;
class Yinset;

struct Data {
    static Point farpoint;
    static std::vector<int> existpoints;
    static std::vector<int> existsegments;
    static std::vector<int> existplanars;
    static std::vector<int> existfaces;
    static std::map<int, Point> points;
    static std::map<int, Segment> segments;
    static std::map<int, Planar> planars;
    static std::map<int, Face> faces;
    static std::map<int, Yinset> yinsets;
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

#endif