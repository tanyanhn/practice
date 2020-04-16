#include"DiscreteSpline.h"
#include<iostream>
#include<fstream>
#include<memory>

using namespace std;

const double epsilon = 1e-5;

double f1(double x){
    assert(x >=0 - epsilon && x <= sqrt(3) + epsilon && "x out of domain.");
    if(abs(x) < epsilon)
        return 2/sqrt(3);
    return 2.0/3 * (sqrt(x) + sqrt(3 - x*x));
}

double f2(double x){
    assert(x >=0 - epsilon && x <= sqrt(3) + epsilon && "x out of domain.");
    if(abs(x) < epsilon)
        return -2/sqrt(3);
    return 2.0/3 * (sqrt(x) - sqrt(3 - x*x));
}

typedef double (*Fun)(double);

template<class T>
vector<vector<double>> generateNodeImplicit(const vector<T>& f,const vector<double>& character, const int N){
    double s = 0;
    int m = f.size();
    assert(m == character.size() - 1 && "n character points should divided to n-1 function,");
    int k = (N - 1) / m;
    vector<vector<double>> interpolation;
    vector<double> prevsxy({0, character[0], f[0](character[0])});
    interpolation.push_back(prevsxy);
    if(m > 1){
        for(auto i = 0; i < m-1; i++){
            double interval = (character[i+1] - character[i])/(k);
            for(int j = 0; j < k; j++){
                vector<double> sxy(3);
                sxy[1] = prevsxy[1] + interval;
                sxy[2] = f[i](sxy[1]);
                s = s + sqrt((sxy[1] - prevsxy[1]) * (sxy[1] - prevsxy[1]) +
                             (sxy[2] - prevsxy[2]) * (sxy[2] - prevsxy[2]));
                sxy[0] = s;
                interpolation.push_back(sxy);
                prevsxy = sxy;
            }
        }
    }
    int rest = (N-1) - k * (m-1);
    if(rest != 0){
        double interval = (character[m] - character[m-1])/(rest);
        for(auto j = 0; j < rest; j++){
            vector<double> sxy(3);
            sxy[1] = prevsxy[1] + interval;
            sxy[2] = f[m-1](sxy[1]);
            s = s + sqrt((sxy[1] - prevsxy[1]) * (sxy[1] - prevsxy[1]) +
                         (sxy[2] - prevsxy[2]) * (sxy[2] - prevsxy[2]));
            sxy[0] = s;
            interpolation.push_back(sxy);
            prevsxy = sxy;
        }
    }
    return interpolation;
}

void interpolateHeart(ostream& os, const vector<double>& character, int N){
    vector<Fun> f({&f1, &f2});
    vector<vector<double>> sxy = generateNodeImplicit<Fun>(f, character, N);
    vector<double> s, x, y;
    for(auto i = sxy.begin(); i != sxy.end(); i++){
        s.push_back((*i)[0]);
        x.push_back((*i)[1]);
        y.push_back((*i)[2]);
    }
    unique_ptr<DiscreteSpline> xp(new DiscreteCompletecubicSpline(x, s, 0, 0));
    unique_ptr<DiscreteSpline> yp(new DiscreteCompletecubicSpline(y, s, 1, -1));
    std::vector<std::pair<my_f_params,std::vector<double>>> anwserx = (*xp)(),
        anwsery = (*yp)();
    int k = anwserx.size();
    for(auto i = 0; i != k; i++){
        os << anwserx[i].second[0] << " " << anwserx[i].second[1] << endl;
        os << anwserx[i].first;
        os << anwsery[i].first;
    }
}


int main(int argc, char *argv[])
{
    string s("output/Heart");
    vector<double> character({0, sqrt(3), 0});
    int N[3] = {10, 40, 160};
    for(auto i = 0; i < 3; i++){
        ofstream os(s + to_string(i));
        interpolateHeart(os, character, N[i]);
    }
    return 0;
}
