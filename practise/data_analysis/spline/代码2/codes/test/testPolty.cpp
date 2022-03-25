#include "Polynomial.H"
#include "Vec.h"
int main(int argc, char const *argv[])
{   
    using namespace std;
    using RV = Vec<Real,2>;
    Polynomial<3,RV> p1,p3;
    vector<RV> vrv1={{1,2},{3,4},{5,6}};
    Polynomial<2,RV> p2({{-1,2},{-3,4}});
    p1.setCoefs(vrv1);
    p3 = p2 - p1;
    cout<<p3<<'\n';
    cout<<p3.eval(0)<<'\n';
    cout<<p3.derivate()<<'\n';
    cout<<p2<<'\n';
    cout<<p2*(p3.derivate())<<'\n';
    Polynomial<4,RV> p4=p2.integral().integral();
    cout<<p4<<'\n';
    p4[0]=p4.eval(1.0);
    cout<<p4<<'\n';

    return 0;
}
