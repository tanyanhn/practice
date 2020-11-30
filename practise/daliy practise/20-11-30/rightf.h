#ifndef RIGHTF
#define RIGHTF

#include"Real.h"
#include<cmath>


class rightf  {
  private:
    Real Time;
    Real lambda;
  public:
    rightf(){};
    explicit rightf(Real l): lambda(l){}
    void sett(Real T){
        Time = T;
    }
    Real operator()(Real Un);
    //rightf(const rightf&){}
    //rightf& operator=(const rightf&){}
    ~rightf(){}
};

Real rightf::operator()(Real Un){
    return lambda*(Un - cos(Time)) - sin(Time);
}

#endif