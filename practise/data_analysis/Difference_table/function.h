#include<iostream>
#include<vector>

//using namespace std;


class F{
public:
    typedef double (*Fun)(const std::vector<double>& parameter);
    explicit F(Fun m): fun(m) {}
    double operator()(const std::vector<double>& parameter) const {
        return (*fun)(parameter);
    }
    double operator()(const double& d) const {
        std::vector<double> parameter;
        parameter.push_back(d);
        return (*fun)(parameter);
    }
private:
    Fun fun;
};

class function{
    std::vector<std::vector<double>> difference;
    F f;
    double a,b;
public:
    function();
    explicit function(F ff) : f(ff), a(0), b(0) {}
    //explicit function(const vector<double>& c) : coefficient(c) {}
    function(const function& temp) : difference(temp.difference), f(temp.f), a(temp.a), b(temp.b) {
        if(a > b){
            std::swap(a,b);
        }
    }
    function& operator=(const function& temp){
        difference = temp.difference;
        f = temp.f;
        a = temp.a;
        b = temp.b;
        return *this;
    }
    std::vector<std::pair<double,double>> getcoefficient() const {
        int k = difference.size();
        std::vector<std::pair<double,double>> anwser;
        for(int i = 0; i < k; i++){
            anwser.push_back(std::make_pair(difference[i][i+1], difference[i][0]));
        }
        return anwser;
    }
    void newtoninterpolation(const int n);
    void chebyshevinterpolation(const int n);
    int cal(std::pair<double, double> newnum);
    void clear(){
        difference = std::vector<std::vector<double>>();
    }
    void setab(double aa, double bb){
        a = aa;
        b = bb;
    }
};