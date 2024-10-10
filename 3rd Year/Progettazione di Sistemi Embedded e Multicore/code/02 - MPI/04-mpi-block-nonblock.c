#include <stdio.h>
#include <mpi.h>

int main() {
    int rank, size;
    int send_right = 19;
    int send_left = 23;
    int recv_left, recv_right;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Possiamo farlo o con richieste singole o con un array di richieste
    MPI_Request request_send_right, request_send_left;
    MPI_Request request_recv_right, request_recv_left;

    // Usiamo una request non bloccante per mandare al core di destra
    MPI_Isend(&send_right, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD, &request_send_right);

    // Mandiamo al core di sinistra
    MPI_Isend(&send_left, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, &request_send_left);

    // Riceviamo da destra
    MPI_Irecv(&recv_right, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD, &request_recv_right);

    // Riceviamo da sinistra
    MPI_Irecv(&recv_left, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, &request_recv_left);

    // Qui ora potremmo fare qualche altro calcolo, e poi controllare se è stato ricevuto
    // tutto con successo
    MPI_Wait(&request_send_right, MPI_STATUSES_IGNORE);
    MPI_Wait(&request_send_left, MPI_STATUSES_IGNORE);
    MPI_Wait(&request_recv_right, MPI_STATUSES_IGNORE);
    MPI_Wait(&request_recv_left, MPI_STATUSES_IGNORE);

    // rank + 1 determina il core che sta al rank successivo rispetto al core che esegue.
    // Se il core che esegue è l'ultimo fra tutti i core, e volessimo fare una struttura
    // circolare, allora possiamo usare il modulo, cosicché se sforassimo con rank + 1 il
    // limite di cores, allora verremmo riportati al primo


    MPI_Finalize();
    return 0;
}
