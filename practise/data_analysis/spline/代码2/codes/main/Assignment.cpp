#include <iostream>
#include <vector>
#include <cmath>
#include "Spline.H"
#include "SnippetsForAssignment.cpp"

int main(int argc, const char **argv)
{
    using namespace std;
    using rVec = Vec<Real, 2>;
    using T_Poly = Polynomial<2, rVec>;
    std::cout << "------------------------Assignment B--------------------------" << endl;
    int B_PossibleN[5] = {5, 10, 20, 40, 80};
    RealVect B_ErrorComplete(5), B_ErrorNotAKnot(5);
    for (int k = 0; k < 5; k++)
    {
        int N = B_PossibleN[k];
        RealBox Box_complete, Box_notAknot;
        Box_complete.push_back({-1, funB(-1), funBder(-1)});
        Box_notAknot.push_back({-1, funB(-1)});
        for (int i = 1; i < N; i++)
        {
            Box_complete.push_back({-1 + 2.0 * i / N, funB(-1 + 2.0 * i / N)});
            Box_notAknot.push_back({-1 + 2.0 * i / N, funB(-1 + 2.0 * i / N)});
        }
        Box_complete.push_back({1, funB(1), funBder(1)});
        Box_notAknot.push_back({1, funB(1)});
        InterpConditions IC_c(Box_complete), IC_n(Box_notAknot);
        Spline<1, 4, ppForm> spl1 = interpolate<4>(IC_c, BCType::complete);
        Spline<1, 4, ppForm> spl2 = interpolate<4>(IC_n, BCType::notAknot);
        ///compute the error
        B_ErrorComplete[k] = 0, B_ErrorNotAKnot[k] = 0;
        for (int i = 0; i < N; i++)
        {
            B_ErrorComplete[k] = std::max(B_ErrorComplete[k], funB(-1 + (2.0 * i + 1) / N) - spl1(-1 + (2.0 * i + 1) / N)[0]);
            B_ErrorNotAKnot[k] = std::max(B_ErrorNotAKnot[k], funB(-1 + (2.0 * i + 1) / N) - spl2(-1 + (2.0 * i + 1) / N)[0]);
        };
        ///plot
        plotIn(spl1, "../../output/B_complete_" + std::to_string(k + 1) + ".m");
        plotIn(spl2, "../../output/B_notAknot_" + std::to_string(k + 1) + ".m");
    };
    ///generate the result
    std::cout << "For Complete situation, " << endl;
    displayErrorConvergence(B_ErrorComplete);
    std::cout << "For Not_a_knot situation, " << endl;
    displayErrorConvergence(B_ErrorNotAKnot);
    plotAgainstRunge_B("complete");
    plotAgainstRunge_B("notAknot");
    std::cout << "Plots have been generated as '/output/B_[XX]Plot.m'.\n";

    std::cout << "------------------------Assignment C--------------------------" << endl;
    RealBox Box1;
    InterpConditions IntpCondsBox1;
    Box1.push_back({-5, funC(-5)});
    for (int i = 1; i <= 10; i++)
        Box1.push_back({i - 5.5, funC(i - 5.5)});
    Box1.push_back({5, funC(5)});
    IntpCondsBox1.ResetIntpInfo(Box1);
    Spline<1, 3, cardinalB> bspl1 = interpolate<3>(IntpCondsBox1, middleSite, cardinalB);
    plotIn(bspl1, "../../output/C_459.m");
    RealBox Box2;
    InterpConditions IntpCondsBox2;
    Box2.push_back({-5, funC(-5), funCder(-5)});
    for (int i = 2; i <= 10; i++)
        Box2.push_back({-6.0 + i, funC(i - 6)});
    Box2.push_back({5, funC(5), funCder(5)});
    IntpCondsBox2.ResetIntpInfo(Box2);
    Spline<1, 4, cardinalB> bspl2 = interpolate<4>(IntpCondsBox2, complete, cardinalB);
    plotIn(bspl2, "../../output/C_458.m");
    ///plot
    plotAgainstRunge_C("458");
    plotAgainstRunge_C("459");
    std::cout << "Plots have been generated as '/output/C_[XX].m'.\n";

    std::cout << "------------------------Assignment D--------------------------" << endl;
    Real C_Sites[7] = {-3.5, -3, -0.5, 0, 0.5, 3, 3.5};
    ///compute the error
    for (int i = 0; i < 7; i++)
        std::cout << "x = " << C_Sites[i]
                  << ": E_458 = " << std::abs(bspl2(C_Sites[i]) - funC(C_Sites[i]))
                  << ", E_459 = " << std::abs(bspl1(C_Sites[i]) - funC(C_Sites[i])) << '\n';


    std::cout << "------------------------Assignment E--------------------------" << endl;
    int E_PossibleN[3] = {10, 40, 160};
    for (int k = 0; k < 3; k++)
    {
        vector<rVec> Box(E_PossibleN[k] + 1);
        for (int i = 0; i <= E_PossibleN[k]; i++)
            Box[i] = heartCurve(2.0 * i / E_PossibleN[k]);
        Spline<2, 4, ppForm> spl = fitCurve<4>(Box, BCType::periodic);
        plotIn(spl, "../../output/E_heart_" + std::to_string(E_PossibleN[k]) + ".m");
        plotCharacteristics_E(Box, std::to_string(E_PossibleN[k]));
    }
    std::cout << "Plots have been generated as '/output/E_[XX].m'.\n";

    std::cout << "------------------------Assignment F--------------------------" << endl;
    {
        RealBox Box3, Box4, Box5;
        Box3 = {{1, 3.0, 1.0}, {2, 3.7}, {5, 3.9}, {6, 4.2}, {7, 5.7}, {8, 6.6}, {10, 7.1}, {13, 6.7}, {17, 4.5, -0.67}};
        Box4 = {{17, 4.5, 3.0}, {20, 7.0}, {23, 6.1}, {24, 5.6}, {25, 5.8}, {27, 5.2}, {27.7, 4.1, -4.0}};
        Box5 = {{27.7, 4.1, 0.33}, {28, 4.3}, {29, 4.1}, {30, 3.0, -1.5}};
        InterpConditions IC3(Box3), IC4(Box4), IC5(Box5);
        Spline<1, 4, ppForm> spl3 = interpolate<4>(IC3, BCType::complete);
        Spline<1, 4, ppForm> spl4 = interpolate<4>(IC4, BCType::complete);
        Spline<1, 4, ppForm> spl5 = interpolate<4>(IC5, BCType::complete);
        plotIn(spl3, "../../output/F_beast_" + std::to_string(1) + ".m");
        plotIn(spl4, "../../output/F_beast_" + std::to_string(2) + ".m");
        plotIn(spl5, "../../output/F_beast_" + std::to_string(3) + ".m");
        plotBeast_F();
    }
    std::cout << "Plots have been generated as '/output/F_beastPlot.m'.\n";


    std::cout << "------------------------Assignment G--------------------------" << endl;
    {
        ///
        /**
         * t1 's front and back are Startpoint/Endpoint of the canvas，
         * the remain are interpolation knots, which is indeed t1_knot.
         * The same with t2 and t2_knot.
         */ 
        RealVect t1({0.0,2.1,3.2,5.4,8.0}),t1_knot({2.1,3.2,5.4});
        plot_G_TriTable<1>(t1);
        add_G_BSpline<1>(t1_knot,"../../output/G_N1.m",0.0,8.0);
        RealVect t2({0,2,6,9,10,12}),t2_knot({2,6,9,10});
        plot_G_TriTable<2>(t2);
        add_G_BSpline<2>(t2_knot,"../../output/G_N2.m",0,12);
    }
    std::cout << "Plots have been generated as '/output/G_N[X].m'.\n";

    std::cout<<"\n------------------------All Assignments Completed------------------------"<<endl;
    return 0;
}
