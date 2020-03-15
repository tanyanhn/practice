#include<iostream>
#include<cmath>
#include<cassert>

using namespace std;

template<int id>
double my_f(double x);
/**
 * template to represect function f
 *
 * x: x value
 * return f(x)
 *
 * create a function have to speciallize this template as follow 4
 */

template<>
double my_f<1>(double x){
    assert(x >= 0 && x <= M_PI/2 &&
           "x isn't in domain");
    double d = 0;
    d = 1/x - tan(x);
    return d;
}

template<>
double my_f<2>(double x){
    assert(x >= 0 && x <= 1 &&
           "x isn't in domain");
    double d = 0;
    d = 1/x - pow(2, x);
    return d;
}

template<>
double my_f<3>(double x){
    assert(x >= 1 && x <= 3 &&
           "x isn't in domain");
    double d = 0;
    d = pow(2, -x) + exp(x) + 2 * cos(x) - 6;
    return d;
}

template<>
double my_f<4>(double x){
    assert(x >= 0 && x <= 4 &&
           "x isn't in domain");
    double d = 0;
    d = (pow(x, 3) + 4 * pow(x, 2) + 3 * x + 5)/(2 * pow(x, 3) - 9 * pow(x, 2) + 18 * x - 2);
    return d;
}

template<class T>
double bisection(int steps, pair<double, double> it, T* F, double epsilon = 1e-10, double eta = 1e-10){
    /**
     * bisection find the root
     *
     * steps: times of bisection iterations.(steps > 0)
     * it: besection interval (interval contain a root)
     * F: Speciallize function my_f to calculate function value(f is continue)
     *
     * return x maintain after steps iterations or |F(x)| < epsilon or |it.first - it.second| < eta
     */
    cout.precision(7);
    double h = it.second - it.first,
        u = (*F)(it.first);
    for(int i = 0 ; i < steps; i++){
        h = h / 2;
        double c = it.first + h;
        double w = (*F)(c);
        if(fabs(h) < eta || fabs(w) < epsilon){
            it.second = c;
            return c;
        }
        else if(w * u > 0){
            it.first = c;
        }
        else {
            it.second = c;
        }
    }
    return (it.first + it.second)/2;
}

int main(int argc, char *argv[])
{
    int steps1 = 5, steps2 = 10;
    pair<double, double> pa1(0, M_PI/2),
        pa2(0, 1),
        pa3(1, 3),
        pa4(0, 4);
    cout << steps1 << "  steps fucntion1 iteratior to "
         << bisection(steps1, pa1, &my_f<1>) << endl;
    cout << steps2 << " steps fucntion1 iteratior to "
         << bisection(steps2, pa1, &my_f<1>) << endl;
    cout << steps1 << "  steps fucntion2 iteratior to "
         << bisection(steps1, pa2, &my_f<2>) << endl;
    cout << steps2 << " steps fucntion2 iteratior to "
         << bisection(steps2, pa2, &my_f<2>) << endl;
    cout << steps1 << "  steps fucntion3 iteratior to "
         << bisection(steps1, pa3, &my_f<3>) << endl;
    cout << steps2 << " steps fucntion3 iteratior to "
         << bisection(steps2, pa3, &my_f<3>) << endl;
    cout << steps1 << "  steps fucntion4 iteratior to "
         << bisection(steps1, pa4, &my_f<4>) << endl;
    cout << steps2 << " steps fucntion4 iteratior to "
         << bisection(steps2, pa4, &my_f<4>) << endl;
    return 0;
}


