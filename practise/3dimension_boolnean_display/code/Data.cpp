#include"Point.h"
#include"Segment.h"
#include"Planar.h"
#include"Face.h"
#include"Yinset.h"
#include"HassNode.h"
#include<map>
#include<vector>


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
