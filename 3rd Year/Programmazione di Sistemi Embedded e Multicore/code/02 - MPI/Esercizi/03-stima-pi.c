#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int n = 100000000;
    int size, rank;
    int total;
    
    MPI_Init(NULL, NULL);
    float start_time = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 1. Generare n numeri da m processi
    // 2. Ogni processo calcola la sua stima di pi
    // 3. I processi ritornano a 0 con una somma
    // 4. 0 divide per 4 la somma

    int results = 0;
    
    srand(atoi(argv[1]) * ((rank + 1) * 2));

    for (int i = 0; i < n; i++) {
        double x = ((double) rand() / RAND_MAX) * 2 - 1;
        double y = ((double) rand() / RAND_MAX) * 2 - 1;

        if ((x * x + y * y) <= 1) {
            results++;   // Circle
        }
    }

    printf("%d: %d over %d launches\n", rank, results, n);

    MPI_Reduce(&results, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double final = ((double) total * 4) / (double) (n * size);
        float final_time = MPI_Wtime();
        printf("Result: %f\n  Total time: %f seconds", final, (final_time - start_time));
    }

    MPI_Finalize();
    return 0;
}