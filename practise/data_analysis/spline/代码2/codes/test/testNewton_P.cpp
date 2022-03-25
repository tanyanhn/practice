#include "NewtonInterp_Portable.H"
#include "InterpConditions.H"
#include "TriangleTable.H"
int main(int argc, char const *argv[])
{
    std::cout<<"---------------TestModifiedNewton----------------"<<std::endl;
    std::cout<<"Chapter4 Example 4.9:"<<std::endl;
    InterpConditions IC1({{1,0,1},{2,0.6931},{3,1.0986},{4,1.3863},{6,1.7918,0.1667}});
    NewtonInterp NI1(IC1);
    NI1.QuickInterp(3);
    NI1.Display();
    std::vector<Real> a = NI1.getTableOfDividedDiffs().getNthCol(3);
    std::cout<<a[0]<<a[1]<<a[2]<<a.back();
    return 0;
}
