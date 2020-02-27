#include <cstdio>
#include <gsl/gsl_sf_bessel.h>

int main(void){
    double x = 5.0,
        y = gsl_sf_bessel_J0 (x);
    printf("Jo(%g) = %.18e\n", x, y);
    return 0;
}