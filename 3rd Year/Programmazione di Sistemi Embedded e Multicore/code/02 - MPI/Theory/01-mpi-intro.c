#include <stdio.h>
#include <mpi.h>

int main(void) {
    // Per usare MPI, serve usare una funzione chiamata MPI_INIT;
    int res = MPI_Init(NULL, NULL);

    if(res != MPI_SUCCESS) {
        printf("C'è stato un errore con il programma");
        MPI_Abort(MPI_COMM_WORLD, res);
    }

    printf("Hello world");

    // Per terminare l'esecuzione di tutti i threads si usa MPI_Finalize
    MPI_Finalize();
    return 0;
}
