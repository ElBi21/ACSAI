#include <stdio.h>
#include <mpi.h>

int main(void) {
    int res = MPI_Init(NULL, NULL);
    int comm_sz, my_rank;

    // Determiniamo la dimensione del comunicatore
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    // Determiniamo il rank del processo che esegue
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(res != MPI_SUCCESS) {
        printf("C'è stato un errore con il programma");
        MPI_Abort(MPI_COMM_WORLD, res);
    }

    printf("'Hello world' dal core %d di %d\n", my_rank, comm_sz);

    MPI_Finalize();
    return 0;
}
