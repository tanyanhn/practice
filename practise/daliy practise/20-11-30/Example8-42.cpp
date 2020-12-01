#include"Eulersolver.h"
#include"Real.h"
#include"rightf.h"
#include<cmath>
#include<iostream>
#include<memory>

using namespace std;


int main(int argc, char *argv[])
{
    shared_ptr<Eulersolver<rightf>> fsolver = make_shared<ForwardEulersolver<rightf>>();
    vector<Real> init;
    init.push_back(1);
    Real lambda = -2100;
    fsolver->setinitial(init);
    fsolver->setrightf(rightf(lambda));
    Real stepsize[] = {0.001, 0.000976, 0.000950, 0.0008};
    cout.setf(ios::scientific);
    for(int itest = 0; itest < int(sizeof(stepsize)/sizeof(Real)); ++itest){
        vector<Real> anwser = fsolver->solver(2,stepsize[itest]);
        cout << "k = " << stepsize[itest] << ", E(T) = " << anwser[0] - cos(2) << endl;
    }
    return 0;
}
        