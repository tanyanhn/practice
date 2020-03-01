#include<iostream>
#include<omp.h>


int main(){
    int a=10, b=11, c=12, d=13;
    std::cout << "abcd's values: " << a << " " << b << " " << c << " " << d << std::endl;
    double t = omp_get_wtime();
    omp_set_num_threads(7);
#pragma omp parallel for  firstprivate(a)       \
    lastprivate(b), firstprivate(c)             \
    lastprivate(c), shared(d), ordered
    for(int i=0; i<8; ++i){
#pragma omp ordered
#pragma omp critical //ordered
//#pragma omp ordered
        std::cout << "thread " << omp_get_thread_num() << " acd's values: "
                  << a << " " << c << " " << d << " " << i << std::endl;
        a = b = c = d = omp_get_thread_num();
#pragma omp critical
        std::cout << omp_get_thread_num() << omp_get_wtime() - t << std::endl;
    }
    std::cout << "abcd's values: " << a << " " << b << " " << c << " " << d << std::endl;

#pragma omp parallel num_threads(5)
    {
#pragma omp critical
        std::cout << omp_get_thread_num() << "\n";
#pragma omp barrier
#pragma omp critical
        std::cout << omp_get_thread_num()+20 << "\n";
    }
    std::cout << omp_get_num_procs();
}