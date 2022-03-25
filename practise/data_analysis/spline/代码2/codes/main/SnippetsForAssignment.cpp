#include <iostream>
#include <vector>
#include <cmath>
#include "Spline.H"

///---------------Necessary Function Information--------------
constexpr Real funB(const Real &_x)
{
    return 1.0 / (1 + 25.0 * _x * _x);
}

constexpr Real funBder(const Real &t)
{
    return -50.0 * t / (1 + 25.0 * t * t) / (1 + 25.0 * t * t);
}

constexpr Real funC(const Real &_x)
{
    return 1.0 / (1 + _x * _x);
}

constexpr Real funCder(const Real t)
{
    return -2.0 * t / (1 +  t * t) / (1 +  t * t);
}

Vec<Real, 2> heartCurve(Real t)
{
    return {sqrt(3) * cos(M_PI*t), 2.0 / 3 * (sqrt(3) * sin(M_PI*t) + sqrt(sqrt(3) * abs(cos(M_PI*t))))};
}

///----------------- Snippets For B ----------------------
void displayErrorConvergence(RealVect rv)
{
    int B_PossibleN[5] = {5, 10, 20, 40, 80};
    for (int i = 0; i < 4; i++)
        std::cout << "N = " << B_PossibleN[i] + 1 << ", error_max = " << rv[i] << ", convergence rate = " << (std::log2(rv[i] / rv[i + 1])) << std::endl;
    std::cout << "N = " << B_PossibleN[4] + 1 << ", error_max = " << rv[4] << std::endl;
};

void plotAgainstRunge_B(std::string str)
{
    using namespace std;
    ofstream outfile("../../output/B_"+str+"Plot.m"); 
    outfile<<"clear;figure(1);\n";
    for(int k=0;k<5;k++)
    {
        ifstream infile("../../output/B_"+str+"_" + std::to_string(k+1)+".m");
        char c;
        while(infile.get(c))
            outfile <<c; 
        infile.close();
        outfile<<"set(h,'linestyle',':','linewidth',1.5);hold on;\n";
    };
    outfile<<"t=-1:0.004:1;x=1./(1+25.0*t.*t);plot(t,x,'color','k','linestyle','--','LineWidth',2.5);hold on;\n";
    outfile<<"set(gca,'FontSize',20);legend = legend('{n=5}','{n=11}','{n=21}','{n=41}','{n=81}','{f(x)}');set(legend,'FontSize',20,'FontName', 'Times New Roman', 'Location','NorthEastOutside');";
    outfile<<"title('Runge."<<str<<"');saveas(1,'Assignment_B_"<<str<<".png');clf(1);";
    outfile.close();
}

///----------------- Snippets For C ----------------------
void plotAgainstRunge_C(std::string str)
{
    using namespace std;
    ofstream outfile("../../output/C_"+str+".m",ios::app); 
    outfile<<"set(h,'linestyle',':','linewidth',1.5);hold on;\n";
    outfile<<"t=-5:0.02:5;x=1./(1+t.*t);plot(t,x,'linestyle','--','LineWidth',2);hold on;\n";
    outfile<<"figure(1);\n";
    outfile<<"set(gca,'FontSize',20);";
    outfile<<"title('Corollary."<<str<<"');legend('BSpline','f(x)');saveas(1,'Assignment_C_"<<str<<".png');clf(1);";
    outfile.close();
}

///----------------- Snippets For E ----------------------
void plotCharacteristics_E(std::vector<Vec<Real, 2> > rvs,std::string str)
{
    using namespace std;
    ofstream outfile("../../output/E_heart_"+str+".m",ios::app);
    outfile<<"set(h,'linestyle',':','linewidth',1.5);hold on;\n";
    outfile<<"x1=[";
    for(int i=0;i<rvs.size();i++)
        outfile<<rvs[i][0]<<",";
    outfile<<"];\n";
    outfile<<"x2=[";   
    for(int i=0;i<rvs.size();i++)
        outfile<<rvs[i][1]<<",";
    outfile<<"];\n";
    outfile<<"plot(x1,x2,'color','k','marker','x','linestyle','none','linewidth',1.5);hold on;\n";
    outfile<<"figure(1);\n";
    outfile<<"set(gca,'FontSize',20);";
    outfile<<"title('HeartCurve."<<str<<"');saveas(1,'Assignment_E_"<<str<<".png');clf(1);";
    outfile.close();
}

///----------------- Snippets For F ----------------------
void plotBeast_F()
{
    using namespace std;
    ofstream outfile("../../output/F_beastPlot.m"); 
    outfile<<"clear;figure(1);\n";
    for(int k=0;k<3;k++)
    {
        ifstream infile("../../output/F_beast_"+ std::to_string(k+1)+".m");
        char c;
        while(infile.get(c))
            outfile <<c; 
        infile.close();
        outfile<<"set(h,'color','k','linestyle','-','linewidth',1.5);hold on;\n";
    };  
    outfile<<"set(gca,'FontSize',20);set(gca,'xtick',0:5:30);set(gca,'ytick',0:2:8);axis equal;axis([0,30,0,8]);title('SleepingBeast');saveas(1,'Assignment_F_beastPlot.png');clf(1);";
}


///----------------- Snippets For G ----------------------
template<int N>
void plot_G_TriTable(const RealVect t)
{   const int _num=500;
    const Real dx = (t.back()-t[0])/_num;
    using namespace std;
    using rVec = Vec<Real, 1>;
    using T_Poly = Polynomial<N+1, rVec>;
    std::vector<rVec> zerobox;
    for(int i=0;i<N+1;i++)
        zerobox.push_back({0});
    T_Poly zeroP(zerobox);
    vector<Spline<1,N+1,ppForm> > TruncFuns;
    for(int i=0;i<N+2;i++)
    {
        T_Poly p;
        p[0]={t[i+1]},p[1]={-1};
        for(int k=0;k<N-1;k++)
            p = multiply_overflow(p,p);
        vector<T_Poly> ps({p,zeroP});
        RealVect knts({t[0],t[i+1],t.back()});
        Spline<1,N+1,ppForm> Trunfun(t[0]);
        Trunfun.polycat(p,t[i+1]-t[0]);
        Trunfun.polycat(zeroP,t.back()-t[i+1]);
        TruncFuns.push_back(Trunfun);
    }   
    RealVect rowname(N+2);
    for(int i=0;i<N+2;i++)
        rowname[i]=t[i+1];
    RealBox TriCol1(N+2);
    for(int k=0;k < N+2;k++)
        for(int i=0;i<= _num;i++)
            TriCol1[k].push_back(((TruncFuns[k])(t[0]+dx*i))[0]);
    std::vector<RealBox> TriT;
    TriT.push_back(TriCol1);   
    for(int colnum=1;colnum < N+2;colnum++)
    {   
        RealBox b;
        for(int rownum=0;rownum+colnum<N+2;rownum++)
        {
            RealVect a(_num+1);
            for(int i=0;i<= _num;i++)
            {
                Real up = TriT[colnum-1][rownum][i]-TriT[colnum-1][rownum+1][i];
                Real down = rowname[rownum]-rowname[rownum+colnum];
                a[i] = up/down;
            }
            b.push_back(a);
        }
        TriT.push_back(b);
    }
    ofstream outfile("../../output/G_N"+std::to_string(N)+".m"); 
    outfile<<"clear;figure(1);\n";
    outfile<<"t="<<t[0]<<":"<<dx<<":"<<t.back()<<";\n";
    for(int colnum=0;colnum<N+2;colnum++)
    {
        for(int rownum=0;rownum+colnum<N+2;rownum++)
        {
            outfile<<"x=[";
            for(int i=0;i<=_num;i++)
                outfile<<TriT[colnum][rownum][i]<<",";
            outfile<<"];\nh=plot(t,x);set(gca,'FontSize',20);set(h,'linewidth',1.5);\nsaveas(1,'Assignment_G_N"<<N<<"_"<<colnum<<"_"<<rownum<<".png');\n";
        }
    }
}

template<int N>
void add_G_BSpline(RealVect rv,std::string str,Real _startplot,Real _endplot)
{
    const int _num=500;
    const Real dx = (_endplot-_startplot)/_num;
    const Real width = _endplot-_startplot;
    using namespace std;
    ofstream outfile(str,ios::app); 
    outfile<<"hold on;\n";
    outfile<<"x=[";
    for(int i=0;i<=_num;i++)
        outfile<<OrdinaryBSpline<N>(rv,_startplot+dx*i)/(rv.back()-rv[0])<<",";
    outfile<<"];\n h=plot(t,x);\n set(h,'linestyle',':','linewidth',2);\n";
    outfile<<"set(gca,'FontSize',20);";
    outfile<<"legend = legend('{divided difference}','{BSpline(Retracted)}');set(legend,'FontSize',20,'FontName', 'Times New Roman', 'Location','NorthEastOutside');";
    outfile<<"title('Bspline"<<N<<"');saveas(1,'Assignment_G_"<<N<<"_Compare.png');clf(1);";
    outfile.close();
}