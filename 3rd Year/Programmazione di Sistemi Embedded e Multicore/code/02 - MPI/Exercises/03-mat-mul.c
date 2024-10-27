#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int rand_int() {
    return rand() / 1000000;
}

int* new_mat(int rows, int cols, bool transpose, int rank) {
    int* matrix;
    if (transpose == true) {
        int temp_rows = 0;
        temp_rows = rows;
        rows = cols;
        cols = temp_rows;
    }
    printf("[INFO] Rank %d is creating a matrix of shape %d × %d\n", rank, rows, cols);
    matrix = (int*) malloc(rows * cols * sizeof(int));
    return matrix;
}

int main(int argc, char** argv) {
    // Args: rows_1, cols_1, rows_2, cols_2
    srand(time(NULL));
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int scatter_root = size - 1;
    
    int rows_1 = atoi(argv[1]);
    int cols_1 = atoi(argv[2]);
    int rows_2 = atoi(argv[3]);
    int cols_2 = atoi(argv[4]);
    
    int n_1 = rows_1 * cols_1;
    int n_2 = rows_2 * cols_2;
    
    int* mat_1 = new_mat(rows_1, cols_1, false, rank);
    int* mat_2 = new_mat(rows_2, cols_2, true, rank);
    int* mat_1_partial = new_mat((rows_1 / size), cols_1, false, rank);

    // If rank is not p-1, then create a partial matrix
    /*if (rank != (size - 1)) {
        free(mat_1);
    } else {
        free(mat_1_partial);
    }*/


    if (rank == (size - 1)) {
        // Fill the matrices
        for (int i = 0; i < n_1; i++) {
            mat_1[i] = rand_int();
        }

        for (int i = 0; i < n_2; i++) {
            mat_2[i] = rand_int();
        }
    }
    
    int partial_n = (rows_1 / size) * cols_1;

    MPI_Bcast(mat_2, n_2, MPI_INT, scatter_root, MPI_COMM_WORLD);
    MPI_Scatter(mat_1, partial_n, MPI_INT,
        mat_1_partial, partial_n, MPI_INT, (size - 1), MPI_COMM_WORLD);
    
    // Make multiplication    

    MPI_Finalize();
    return 0;
}