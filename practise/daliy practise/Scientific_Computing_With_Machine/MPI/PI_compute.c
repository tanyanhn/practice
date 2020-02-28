#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include"mpi.h"

int main(int argc, char* argv[]){
    int true = 1;                    // to force the loop
    int n,                           // number of intervals
        rank,                        // rank of the MPI process
        size,                        // number of processes
        i,                           // variable for the loop
        len;                         // name of the process
    double PI_VALUE = M_PI;          // reference value of pi
    double mypi,                     // value for each process
        pi,                          // value of pi calculated
        h,
        sum,                         // sum of the area
        x;

    double start_time,               // starting time
        end_time,                    // ending time
        computation_time;            // time for computing value of pi

    char name[80];                   // char array for storing the name of the node where is
                                     // located the process

    /* Initialization */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* We ask for the name of the node */
    MPI_Get_processor_name(name, &len);

    while(true){
        if(rank == 0){
            printf("Enter the number of intervals: (0 quits)");
            scanf("%d", &n);
            start_time = MPI_Wtime();
        }
        /* We are broadcasting to everybody the number of interval */
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if(n == 0) break;

        h = 1.0 / (double) n;
        sum = 0.0;
        for(i = rank + 1; i <= n; i += size){
            x = h * ((double)i - 0.5);
            sum += 4.0 / (1.0 + x * x);
        }
        mypi = h * sum;
        printf("This is my sum: %.16f from rank: %d in: %s\n", mypi, rank, name);

        MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if(rank == 0){
            printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI_VALUE));
            end_time = MPI_Wtime();
            computation_time = end_time - start_time;
            printf("Time of calculating pi is: %f\n", computation_time);
        }
    }
    MPI_Finalize();
    return 0;
}