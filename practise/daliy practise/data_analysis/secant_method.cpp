#include<iostream>
#include<cmath>
#include<cassert>

using namespace std;

template<int id>
class my_f{
public:
    double operator()(double x);
};
/**
 * template to represect function f
 *
 * x: x value
 * return f(x)
 *
 * create a function have to speciallize this template as follow 4
 */

template<>
double my_f<1>::operator()(double x){
    double d = sin(x/2) - 1;
    return d;
}

template<>
double my_f<2>::operator()(double x){
    double d = exp(x) - tan(x);
    return d;
}

template<>
double my_f<3>::operator()(double x){
    double d = pow(x, 3) + (-12) * pow(x, 2) + 3 * x + 1;
    return d;
}

template<class T>
double secant_method(int steps, pair<double, double> it, T F, double epsilon = 1e-10, double eta = 1e-10){
    /**
     * secant_method find the root
     *
     * steps: times of secant_method iterations.(steps > 0)
     * it: start point pair (two position is close to a root)
     * F: Speciallize function my_f to calculate function value(F(x1) != F(x2) x1,x2 is start points)
     *
     *  return x maintain after steps iterations or |F(x)| < epsilon or |it.first - it.second| < eta
     */
    cout.precision(7);
    double u = F(it.second),
        v = F(it.first);
    for(auto i = 0; i < steps; i++){
        if(fabs(u) > fabs(v)){
            swap(it.first, it.second);
            swap(u, v);
        }
        double s = (it.second - it.first)/(u -v);
        it.first = it.second;
        v = u;
        it.second = it.second - u * s;
        u = F(it.second);
        if(fabs(it.second - it.first) < eta || fabs(u) < epsilon){
            return it.second;
        }
    }
}

int main(int argc, char *argv[])
{
    int steps1 = 5, steps2 = 10, steps3 = 50;
    pair<double, double> pa1(0.5, M_PI/2),
        pa2(1, 1.4),
        pa3(0, -0.5);
    my_f<1> function1;
    my_f<2> function2;
    my_f<3> function3;
    cout << steps1 << "  steps fucntion1 iteratior to "
         << secant_method(steps1, pa1, function1) << endl;
    cout << steps2 << " steps fucntion1 iteratior to "
         << secant_method(steps2, pa1, function1) << endl;
    cout << steps3 << " steps fucntion1 iteratior to "
         << secant_method(steps3, pa1, function1) << endl;
    cout << steps1 << "  steps fucntion2 iteratior to "
         << secant_method(steps1, pa2, function2) << endl;
    cout << steps2 << " steps fucntion2 iteratior to "
         << secant_method(steps2, pa2, function2) << endl;
    cout << steps3 << " steps fucntion2 iteratior to "
         << secant_method(steps3, pa2, function2) << endl;
    cout << steps1 << "  steps fucntion3 iteratior to "
         << secant_method(steps1, pa3, function3) << endl;
    cout << steps2 << " steps fucntion3 iteratior to "
         << secant_method(steps2, pa3, function3) << endl;
    cout << steps3 << " steps fucntion3 iteratior to "
         << secant_method(steps3, pa3, function3) << endl;
    return 0;
}

