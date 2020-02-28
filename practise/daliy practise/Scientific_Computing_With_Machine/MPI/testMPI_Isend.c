#include<stdio.h>
#include<mpi.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    int rank, number[2], source, destination, messagestag = 7, messagesnum = 2;
    number[0] = 0;
    number[1] = 1;
    source = 6;
    destination = 0;
    int waittime = 1;
    MPI_Status status;
    MPI_Request request;
    /*static MPI */
    MPI_Init(&argc, &argv);
    /* get current process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    request = MPI_REQUEST_NULL;
    if(rank == source){
        sleep(5);
        number[0] = 123;
        number[1] = 10;
        MPI_Isend(&number, messagesnum, MPI_INT, destination, messagestag, MPI_COMM_WORLD, &request);
        //waittime = number[1];
    }
    else if(rank == destination){
        //sleep(5);
        MPI_Irecv(&number, messagesnum, MPI_INT, source, messagestag, MPI_COMM_WORLD, &request);
        waittime = number[1];
    }
    printf("processor %d wait hear\n", rank);
    if(rank <=6 )
        MPI_Wait(&request, &status);
    //waittime = number[1];
    sleep(waittime);
    if(rank == source){
        printf("processor %d sent %d, %d, and waittime :%d\n", rank, number[0], number[1], waittime);
    }
    if(rank == destination){
        printf("processor %d got %d, %d, and waittime :%d\n", rank, number[0], number[1], waittime);
    }
    printf("processor %d finish wait\n", rank);
    MPI_Finalize();
    return 0;
}