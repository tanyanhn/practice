#include"function.h"
#include<cmath>

using namespace std;

void function::newtoninterpolation(const int n){
    vector<pair<double,double>> interpolatepoint;
    for(auto i = 0; i < n + 1; i++){
        double point = a + i*(b - a)/n;
        double value = f(point);
        interpolatepoint.push_back(make_pair(point,value));
    }
    for(auto i = interpolatepoint.begin(); i < interpolatepoint.end(); i++){
        cal(*i);
    }
}

void function::chebyshevinterpolation(const int n){
    vector<pair<double,double>> interpolatepoint;
    for(auto i = 0; i < n + 1; i++){
        double point = cos(i * M_PI / n);
        double value = f(point);
        interpolatepoint.push_back(make_pair(point,value));
    }
    for(auto i = interpolatepoint.begin(); i < interpolatepoint.end(); i++){
        cal(*i);
    }
}

int function::cal(pair<double, double> newnum){
    vector<double> newrow;
    newrow.push_back(newnum.first);
    newrow.push_back(newnum.second);
    int k = difference.size() - 1;
    newrow.resize(k + 3);
    difference.push_back(newrow);
    for(int i = 1; i < k + 2; i++){
        double f1 = difference[k+1][i],
            f2 = difference[k][i],
            x1 = difference[k + 1][0],
            x2 = difference[k + 1 - i][0];
        double f = (f1 - f2) / (x1 - x2);
        difference[k + 1][i + 1] = f;
    }
    return 1;
}

