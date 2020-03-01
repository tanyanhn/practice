
#include<iostream>
#include<omp.h>
int main(int arc, char* arg[])
{
    const int size = 1000, times = 10000;
    long long int data[size], dataValue=0;
    for(int j=1; j<=times; ++j)
        dataValue += j;
#pragma omp parallel num_threads(16)
    for(int i=0; i<1000000; ++i) ;
    bool wrong; double t, tsigle;
    for(int m=1; m<=16; ++m){
        wrong = false;
        t = omp_get_wtime();
        for(int n=0; n<100; ++n){
#pragma omp parallel for num_threads(m)
            for(int i=0; i<size; ++i){
                data[i] = 0;
                for(int j=1; j<=times; ++j)
                    data[i] += j;
                if(data[i] != dataValue)
                    wrong = true;
            }
        }
        t = omp_get_wtime()-t;
        if(m==1) tsigle=t;
        std::cout << "num_threads(" << m << ") rumtime: " << t << " s.\n";
        std::cout << "wrong=" << wrong << "\tspeedup: " << tsigle/t << "\tefficiency: " << tsigle/t/m << "\n\n";
    }
    std::cin.get();
    return 0;
  }