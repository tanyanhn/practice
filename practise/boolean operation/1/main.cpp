#include"Point.h"
#include"Line.h"
#include"BalanceTree.h"
#include<string>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include"intersection.h"
using namespace std;

double sweepLine::y = 10000000;
sweepLine::ATP sweepLine::eventpoint;
map<int, GraphLine> sweepLine::everyline;
sweepLine::ATL sweepLine::orderline;
intersection sl;

/*bool operator<( const GraphLine l1, const GraphLine l2){
    double y = sweepLine::y;
    double x1 = min(min((*(l1.ep[0]))[0], (*(l1.ep[1]))[0]), min((*(l2.ep[0]))[0], (*(l2.ep[1]))[0]));
    double x2 = max(max((*(l1.ep[0]))[0], (*(l1.ep[1]))[0]), max((*(l2.ep[0]))[0], (*(l2.ep[1]))[0]));
    GraphPoint a1(x1, y), a2(x2, y);
    GraphLine l3(a1, a2);
    GraphPoint* p1, *p2;
    if(sl.Meet(l1, l3) == 1) {GraphPoint tp1 = sl.inter(l1, l3); p1 = &tp1;}
    else if(sl.Meet(l1, l3) == 0){double p11 = min((*(l1.ep[0]))[0], (*(l1.ep[1]))[0]);
        GraphPoint tp1(p11, y);  p1 = &tp1;}
    else {cout << "operator< in sweepLine wrong "; exit(0);}
    if(sl.Meet(l2, l3) == 1) {GraphPoint tp2 = sl.inter(l2, l3); p2 = &tp2;}
    else if(sl.Meet(l2, l3) == 0){double p21 = min((*(l2.ep[0]))[0], (*(l2.ep[1]))[0]);
        GraphPoint tp2(p21, y);  p2 = &tp2;}
    else {cout << "operator< in sweepLine wrong "; exit(0);}
    return (*p1 < *p2);
}
*/
int main(){
    cout << "main()\n";
    ifstream input("test.input");
    int num;
    string sdata;
    double d1, d2;
      vector<GraphPoint> gp;
    while(input){
        input >> num;
        if(input){
            cout << num << endl;
            long double d[2];
            for(int i = 0; i < num; i++){
                /*input >> sdata;
                d[0] = stold(sdata);
                input >> sdata;
                d[1] = stold(sdata);*/
                input >> d1;
                input >> d2;
                d[0] = d1;
                d[1] = d2;
                gp.push_back(GraphPoint(d[0], d[1]));
                cout << setprecision(15) << d[0] << ", " << d[1] << endl;
                sweepLine::eventpoint.add(GraphPoint(d[0], d[1]));
            }
        }
    }
    sweepLine::eventpoint.transform();
    AVLTreeNode<GraphPoint>* p = sweepLine::eventpoint.findfirstnode();
    cout << endl;
    cout << p << endl;
    p = sweepLine::eventpoint.findlastnode();
    cout << p << endl;
    sweepLine::eventpoint.transform();
    if(gp[1] > gp[2]) cout << gp[1] << " > " << gp[2]  << "\n";
    else if(gp[1] < gp[2])  cout << gp[1] << " < " << gp[2]  << "\n";
    else  cout << gp[1] << " = " << gp[2]  << "\n";
    GraphPoint p1 = gp[5], p2 = gp[6], p3 = gp[7], p4 = gp[8];
    GraphLine l1(p1, p2), l2(p3, p4);
    cout << p1 << p2 << p3 << p4 << endl;
    for(int i = 0; i < 3; i++){
        sweepLine::y = i;
        l1 < l2;
        if(l1.operator<(l2) == true) cout << "l1 < l2" << endl;
    else cout << "l2 >= l1" << "\n";
    }
    GraphPoint* q1, *q2;
    q1 = NULL;
    q2 = 0;
    if(q1 == q2) cout << "q1 == q2\n";
    else cout << "q1 != q2\n";
}
