#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int rand_int() {
    return rand() / 1000000;
}

int* new_mat(int rows, int cols, bool transpose) {
    int* matrix;
    if (transpose) {
        printf("[INFO] Creating matrix of shape %d × %d\n", cols, rows);
        matrix = (int*) malloc(cols * rows * sizeof(int));
    } else {
        printf("[INFO] Creating matrix of shape %d × %d\n", rows, cols);
        matrix = (int*) malloc(rows * cols * sizeof(int));
    }
    return matrix;
}

int main(int argc, char** argv) {
    // Args: rows_1, cols_1, rows_2, cols_2
    srand(time(NULL));
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == (size - 1)) {
        int rows_1 = atoi(argv[1]);
        int cols_1 = atoi(argv[2]);
        int n_1 = rows_1 * cols_1;

        int rows_2 = atoi(argv[3]);
        int cols_2 = atoi(argv[4]);
        int n_2 = rows_2 * cols_2;

        int* mat_1 = new_mat(rows_1, cols_1, false);
        int* mat_2 = new_mat(rows_2, cols_2, true);

        for (int i = 0; i < n_1; i++) {
            mat_1[i] = rand_int();
        }

        for (int i = 0; i < n_2; i++) {
            mat_2[i] = rand_int();
        }
    }

    MPI_Finalize();
    return 0;
}