#include<iostream>
#include<omp.h>
#include<vector>
#include<cmath>
#include<cstdio>
using namespace std;

int main(){
    vector<double> a(11);
    double asum = 0, aprod = 1;
    double t1, t2;
#pragma omp parallel for \
    shared(a) private(t1, t2)
    for(int i = 0; i < 11; i++){
        t1 = i + 1;
        t2 = i + 1;
        a[i] = sqrt( t1 * t1 + t2 * t2);
        printf("%d %f %f %f \n", i, t1, t2, a[i]);
    }
#pragma omp parallel for reduction(+:asum) ,    \
    reduction(*:aprod)
    for(int i = 0; i < 11; i++){
        int k = omp_get_thread_num();
        printf("before %d %f %f %f \n", k, a[i], asum, aprod);
        asum = asum + a[i];
        aprod = aprod * a[i];
        printf("after  %d %f %f %f \n", k, a[i], asum, aprod);
    }
    printf("%f %f \n", asum, aprod);
}