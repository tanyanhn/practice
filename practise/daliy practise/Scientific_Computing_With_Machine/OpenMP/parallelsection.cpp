#include<iostream>
#include<unistd.h>
#include<omp.h>
using namespace std;

template<int i>
void func(){
    sleep(i + 1);
    int k = omp_get_thread_num();
    cout << "func: " << i << " from thread :" << k << endl;
}

int main(){
    int m = 0;
#pragma omp parallel sections
    {
#pragma omp section
        {
            func<1>();
        }
#pragma omp section
        {
            func<2>();
        }
#pragma omp section
        {
            func<3>();
        }
#pragma omp section
        {
            func<4>();
        }
#pragma omp section
        {
            func<5>();
        }
    }
#pragma omp parallel num_threads(4)
    {
        cout << "func<0> now thread : " << omp_get_thread_num() << endl;
#pragma omp atomic
        m++;
        cout << m << endl;
        func<0>();
#pragma omp single
        {
            cout << "func<8> now thread : " << omp_get_thread_num() << endl;
            func<8>();
#pragma omp task
            {
                cout << "func<5> now thread : " << omp_get_thread_num() << endl;
                func<5>();
            }
            cout << "func<9> now thread : " << omp_get_thread_num() << endl;
            func<9>();
#pragma omp task
            {
                cout << "func<6> now thread : " << omp_get_thread_num() << endl;
                func<6>();
            }
            cout << "func<7> now thread : " << omp_get_thread_num() << endl;
            func<7>();
        }
#pragma omp critial
        cout << "func<0> now thread : " << omp_get_thread_num() << endl;
        func<0>();
    }
    return 0;
}

