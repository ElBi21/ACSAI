#include <stdio.h>
#include <mpi.h>

int main(void) {
    int STRING_SIZE = 64;

    int res = MPI_Init(NULL, NULL);
    int comm_sz, my_rank;

    if(res != MPI_SUCCESS) {
        printf("C'è stato un errore con il programma");
        MPI_Abort(MPI_COMM_WORLD, res);
    }
    
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank == 0) {
        printf("'Hello world' dal core %d di %d\n", my_rank, comm_sz);
        for (int i = 1; i < comm_sz; i++) {
            // Creiamo il buffer per ricevere le stringhe
            char str_buff[STRING_SIZE];

            // Per ricevere un messaggio, usiamo la funzione MPI_Recv. La receive è bloccante: una volta conclusa,
            // si avrà la sicurezza che ciò che è stato inviato sia stato ricevuto correttamente
            MPI_Recv(str_buff, STRING_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", str_buff);
        }
    } else {
        char str_buff[STRING_SIZE];
        // Per creare una stringa, possiamo usare la funzione sprintf
        sprintf(str_buff, "'Hello world' dal core %d di %d\n", my_rank, comm_sz);

        // Per mandare un messaggio, usiamo la funzione MPI_Send
        MPI_Send(str_buff, STRING_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
