#include "Spline.H"
#include <cmath>

Vec<Real, 2> circle(Real t)
{
    return {5.0 * cos(M_PI * t), 2.0 * sin(M_PI * t)};
};

Vec<Real, 2> rotateSin(Real t)
{
    return {sin(M_PI * t), t};
};

Vec<Real, 2> helix(Real t)
{
    return {t * cos(t), t * sin(t)};
};

Real Rungefun(Real t)
{
    return 1.0 / (1 + 25.0 * t * t);
}

Real RungefunDer(Real t)
{
    return -50.0 * t / (1 + 25.0 * t * t) / (1 + 25.0* t * t);
}

int main(int argc, char const *argv[])
{
    using rVec = Vec<Real, 2>;
    using T_Poly = Polynomial<2, rVec>;
    using namespace std;
    {
    T_Poly p1({{2, 4}, {1, 3}}), p2({{-1, -2}, {-3, -4}});
    Spline<2, 2, ppForm> spl1(p1, 5), spl2(p2, 3),spl3;
    cout << spl1.getStartPoint() << " " << spl1.getEndPoint() << " " << '\n';
    spl1.display();
    spl2.display();
    spl2.polycat(spl1);
    spl2.display();
    spl3 = spl2 * 2.0;
    spl3.display();
    return 0;
    cout << spl2.getKnots()[0] << " " << spl2.getKnots()[1] << " " << spl2.getKnots()[2] << '\n';
    plotIn(spl2, "spl2.m");
    }

    ///------------Dim=2--------------
    vector<Vec<Real, 2>> KnotsInfo = {{1, 1}, {2, 2}, {3, 1}, {4, 0}, {2, -1}, {1, 1}};
    Spline<2, 2, ppForm> spl3 = fitCurve<2>(KnotsInfo);
    spl3.display();
    plotIn(spl3, "spl3.m", 500);

    const int N1 = 20;
    
    std::vector<rVec> Box1(N1 + 1);
    for (int i = 0; i <= N1; i++)
        Box1[i] = circle(2.0 * i / N1);
    Spline<2, 4, ppForm> spl4 = fitCurve<4>(Box1, BCType::periodic);
    plotIn(spl4, "spl4.m", 500);

    std::vector<rVec> Box2(N1 + 1);
    for (int i = 0; i <= N1; i++)
        Box2[i] = rotateSin(2.0 * i / N1);
    Spline<2, 4, ppForm> spl5 = fitCurve<4>(Box2, BCType::notAknot);
    plotIn(spl5, "spl5.m", 500);

    const int N2 = 100;
    
    std::vector<rVec> Box3(N2 + 1 + 2);
    for (int i = 0; i <= N2; i++)
        Box3[i] = helix(5.0 * M_PI * i / N2);
    Box3[N2 + 1] = {1, 0};
    Box3[N2 + 2] = {-1, -5 * M_PI};
    Spline<2, 4, ppForm> spl6 = fitCurve<4>(Box3, BCType::complete);
    // plotIn(spl6, "spl6.m", 500);

    ///------------Dim=1--------------

    const int N3 = 20;
    RealBox Box4;
    InterpConditions IntpCondsBox4;
    for (int i = 0; i <= N3; i++)
    {
        Box4.push_back({-1 + 2.0 * i / N3, Rungefun(-1 + 2.0 * i / N3)});
    }
    IntpCondsBox4.ResetIntpInfo(Box4);
    Spline<1, 2, ppForm> spl7 = interpolate<2>(IntpCondsBox4);
    plotIn(spl7, "spl7.m", 500);

    Spline<1, 4, ppForm> spl8 = interpolate<4>(IntpCondsBox4, BCType::notAknot);
    plotIn(spl8, "spl8.m", 500);

    RealBox Box5;
    InterpConditions IntpCondsBox5;
    Box5.push_back({-1,Rungefun(-1),RungefunDer(-1)});
    for (int i = 1; i < N3; i++)
    {
        Box5.push_back({-1 + 2.0 * i / N3, Rungefun(-1 + 2.0 * i / N3)});
    }
    Box5.push_back({1,Rungefun(1),RungefunDer(1)});
    IntpCondsBox5.ResetIntpInfo(Box5);
    Spline<1, 4, ppForm> spl9 = interpolate<4>(IntpCondsBox5,BCType::complete);
    plotIn(spl9,"spl9.m",500);


    RealBox Box6;
    InterpConditions IntpCondsBox6;
    Box6.push_back({1, log(1.0), 1});
    Box6.push_back({2, log(2.0)});
    Box6.push_back({3, log(3.0)});
    Box6.push_back({4, log(4.0)});
    Box6.push_back({6, log(6.0),1.0/6.0});
    IntpCondsBox6.ResetIntpInfo(Box6);
    Spline<1,4,ppForm> spl10 = interpolate<4>(IntpCondsBox6,BCType::complete);
    plotIn(spl10,"spl10.m",500);
    cout<<spl10(5.0)<<'\n';
    ofstream os10("spl10.m",ios::app);
    os10<<"% hahahahaha";
    os10.close();
}
