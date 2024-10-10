#include <stdio.h>
#include <mpi.h>

float my_func(int x) {
    return (-x * (x - 20)) / 4;
}

int main() {
    int rank, size;
    int a, b, n;

    a = 0;
    b = 20;
    n = 4;

    int base = (b - a) / n;

    // Initiate the threads
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    float core_a = b / n * rank;
    float core_b = b / n * (rank + 1);

    float area = (base / 2) * (my_func(core_a) + my_func(core_b));

    printf("Sub-area calcolata: %f\n  Dal thread %d\n", area, rank);

    if (rank == 0) {
        // Receive and do sum
        float total_area, buff;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&buff, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_area += buff;
        }
        printf("  → Area totale: %f\n", total_area);
    } else {
        // Send the sum to 0
        MPI_Send(&area, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

