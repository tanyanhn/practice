#include<stdio.h>
#include<omp.h>
#include<unistd.h>

void work(int id, int i){
    printf("worker %d doing, i: %d\n", id, i);
    return;
}

int main(int argc, char* argv[]){
    //int i = 0, n = 10;
    int N = 14;
#pragma omp parallel if(N > 13)
    {
        int thread_id = omp_get_thread_num();
        work(thread_id, -1);
        int i = 0, n = 10;
#pragma omp for schedule(dynamic, 2)
        for(i = 0; i < n; i++){
            sleep(i + 1);
            int thread_id = omp_get_thread_num();
            work(thread_id, i);
            //sleep(i);
        }
        thread_id = omp_get_thread_num();
        work(thread_id, -1);
    }
    return 0;
}