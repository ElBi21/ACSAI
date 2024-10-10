#include <mpi.h>
#include <stdio.h>
//mpicc to compile, mpirun to run -n x where x is the number of processes we want to start --oversubscribe allows to run more then the number of core
//-g for debug info

int main(void){
    int mpi = MPI_Init(NULL, NULL); 
    int size, rank;

    if(mpi != MPI_SUCCESS){
        printf("Error starting mpi. Terminating\n");
        MPI_Abort(MPI_COMM_WORLD, mpi);
    }

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
        printf("hello world!,\n process %d of %d\n", rank, size);
        for (int i = 1; i < size; i++){
             char str[256]; 
             MPI_Recv(str, 256, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             printf("%s", str);
        }
    }

    else{
        char to_send[256];
        sprintf(to_send, "hello world!,\n process %d of %d\n", rank, size);
        MPI_Send(to_send, 256, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}