#include <stdio.h>
#include <mpi.h>

float func(int x) {
    return (-x * (x - 20)) / 4;
}

int main() {
    int a = 0;
    int b = 40;
    int n = 10;

    int base = (b - a) / n;

    float area[n], total;
    total = 0;
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < (n / size); i++) {
        int index = i + (rank * (n / size));
        area[index] = (base / 2) * (func(base * index) + func(base * (index + 1)));
    }

    printf("Rank %d putting in Area[%d] the value %f\n", rank, rank, area[rank]);

    MPI_Reduce(&area[rank * (n / size)], &total, (n / size), MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Area totale = %f", total);
    }

    MPI_Finalize();

    return 0;
}