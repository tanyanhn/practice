#include "CardinalBspline.H"
#include "Spline.H"
Real Rungefun(Real t)
{
    return 1.0 / (1 +  t * t);
}

Real RungefunDer(Real t)
{
    return -2.0 * t / (1 +  t * t) / (1 +  t * t);
}

int main(int argc, char const *argv[])
{
    using namespace std;

    const int N3 = 10;
    RealBox Box1;
    InterpConditions IntpCondsBox1;
    Box1.push_back({-5,Rungefun(-5)});
    for (int i = 1; i <= N3; i++)
    {
        Box1.push_back({i-5.5, Rungefun(i-5.5)});
    }
    Box1.push_back({5,Rungefun(5)});
    IntpCondsBox1.ResetIntpInfo(Box1);
    Spline<1,3,cardinalB> bspl1=interpolate<3>(IntpCondsBox1,middleSite,cardinalB);
    cout<<bspl1(5)<<'\n';
    RealVect Knots1 = bspl1.getKnots();
    for (int i=0;i<Knots1.size();i++)
        cout<<Knots1[i]<<" ";
    cout<<'\n';
    plotIn(bspl1,"bspl1.m");

    RealBox Box2;
    InterpConditions IntpCondsBox2;
    Box2.push_back({-5,Rungefun(-5),RungefunDer(-5)});
    for (int i = 2; i <= N3; i++)
    {
        Box2.push_back({-6.0+ i, Rungefun(i-6)});
    }
    Box2.push_back({5,Rungefun(5),RungefunDer(5)});
    IntpCondsBox2.ResetIntpInfo(Box2);
    Spline<1,4,cardinalB> bspl2=interpolate<4>(IntpCondsBox2,complete,cardinalB);
    cout<<bspl2(5)<<'\n';
    // RealVect Knots2 = bspl2.getKnots();
    // for (int i=0;i<Knots2.size();i++)
    //     cout<<Knots2[i]<<" ";
    // cout<<'\n';
    plotIn(bspl2,"bspl2.m");

    return 0;
}
