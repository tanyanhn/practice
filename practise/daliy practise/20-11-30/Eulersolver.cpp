#include"Real.h"
#include"Eulersolver.h"
#include<vector>
#include<algorithm>

using namespace std;


template<class func>
vector<Real> ForwardEulersolver<func>::solver(Real T, Real stepsize){
    Real Time = T;
    int step = Time/stepsize + 1;
    auto rightf = Eulersolver<func>::rightf;
    vector<Real> anwser = Eulersolver<func>::initial;
    vector<Real> init = anwser;
    for(int istep = 1; istep < step; ++istep){
        rightf.sett(Time/step*(istep-1));
        transform(init.begin(),init.end(),anwser.begin(),rightf);
    }
    return anwser;
}