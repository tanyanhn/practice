#include<stdio.h>
#include<omp.h>

int main(int argc, char* argv[]){
    int i = 1;
#pragma omp parallel
    {
        //i++;
        //printf("global value i: %d\n", i);
        int thread_id = omp_get_thread_num();
        int thread_cout = omp_get_num_threads();
        printf("Hello from thread number: %d out of: %d, and i: %d\n", thread_id, thread_cout, i);
        //printf("global value i: %d\n", i);
        //i++;
    }
    return 0;
}