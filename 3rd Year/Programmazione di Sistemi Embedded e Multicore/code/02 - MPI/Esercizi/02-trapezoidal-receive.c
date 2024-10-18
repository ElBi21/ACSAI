#include <stdio.h>
#include <mpi.h>

float func(int x) {
    return (-x * (x - 20)) / 4;
}

int main() {
    int a = 0;
    int b = 20;
    int n = 4;

    int base = (b - a) / n;

    float area[4], total;
    total = 0;
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    area[rank] = (base / 2) * (func(base * rank) + func(base * (rank + 1)));
    printf("Rank %d putting in Area[%d] the value %f\n", rank, rank, area[rank]);

    MPI_Reduce(&area[rank], &total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Area totale = %f", total);
    }

    MPI_Finalize();

    return 0;
}