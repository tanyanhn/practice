#include<stdio.h>
#include"mpi.h"

int main(int argc, char* argv[]){
    int rank, size,
        number = 0;
    int dest = 3,
        source = 8,
        messageid = 15,
        messagenum = 1;
    /* starts MPI*/
    MPI_Init(&argc, &argv);
    /* get current process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == source){
        printf("in source process %d, Number = %d\n", rank, number);
        number = 123;
        MPI_Send(&number, messagenum, MPI_INT, dest, messageid, MPI_COMM_WORLD);
        printf("out source process %d, Number = %d\n", rank, number);
    }
    else if(rank == dest){
        printf("Number = %d\n", number);
        MPI_Recv(&number, messagenum, MPI_INT, source, messageid, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d receved data from process %d, number = %d \n", dest, source, number);
    }
    /* get number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /* print the rank and number of processes */
    printf("Hello World from process %d of %d\n", rank, size);
    /* ends MPI */
    MPI_Finalize();
    return 0;
}