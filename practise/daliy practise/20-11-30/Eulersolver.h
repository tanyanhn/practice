#ifndef EULERSOLVER
#define EULERSOLVER


#include"Real.h"
#include<vector>
#include<algorithm>

template<class func>
class Eulersolver  {
  protected:
    std::vector<Real> initial;
    Real anwserT;
    func rightf;
    Real stepsize;
  public:
    Eulersolver(){};
    Eulersolver(std::vector<Real>& init, func right) : initial(init), rightf(right), anwserT(0){}
    virtual std::vector<Real> solver(Real T,Real step) = 0;
    void setinitial(std::vector<Real>& init) { initial = init;}
    void setrightf(func f) { rightf = f;}
    // Eulersolver(const Eulersolver&){}
    // Eulersolver& operator=(const Eulersolver&){}
    virtual ~Eulersolver() = 0;
};
template<class func>
Eulersolver<func>::~Eulersolver(){};


template<class func>
class ForwardEulersolver : public Eulersolver<func> {
  public:
    ForwardEulersolver(){}
    ForwardEulersolver(std::vector<Real>& init, func right) : Eulersolver<func>(init,right) {}
        //ForwardEulersolver(const ForwardEulersoler& tmp) {}
        //ForwardEulersolver& operator=(const ForwardEulersoler&){}
    virtual std::vector<Real> solver(Real T,Real step);
    virtual ~ForwardEulersolver(){}
};

template<class func>
std::vector<Real> ForwardEulersolver<func>::solver(Real T, Real stepsize){
    Real Time = T;
    int step = Time/stepsize + 1;
    auto rightf = Eulersolver<func>::rightf;
    std::vector<Real> anwser = Eulersolver<func>::initial;
    std::vector<Real> init = anwser;
    for(int istep = 1; istep < step; ++istep){
        rightf.sett(stepsize*(istep-1));
        std::transform(init.begin(),init.end(),anwser.begin(),[&](Real Un){
            return Un + stepsize*rightf(Un);}
            );
        init = anwser;
    }
    return anwser;
}

#endif