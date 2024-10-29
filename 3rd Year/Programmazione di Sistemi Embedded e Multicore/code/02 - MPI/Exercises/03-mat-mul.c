#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int rand_int() {
    return rand() / 20000000;
}

int* new_mat(int rows, int cols, bool transpose, int rank) {
    int* matrix;
    if (transpose == true) {
        int temp_rows = 0;
        temp_rows = rows;
        rows = cols;
        cols = temp_rows;
    }
    // printf("[INFO] Rank %d is creating a matrix of shape %d × %d\n", rank, rows, cols);
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

    if (cols_1 != rows_2) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    int n_1 = rows_1 * cols_1;
    int n_2 = rows_2 * cols_2;
    
    int* mat_1 = new_mat(rows_1, cols_1, false, rank);
    int* mat_2 = new_mat(rows_2, cols_2, false, rank);
    int* mat_1_partial = new_mat((rows_1 / size), cols_1, false, rank);
    int* res_partial = new_mat((rows_1 / size), cols_2, false, rank);

    // Fill the matrices
    if (rank == (size - 1)) {
        for (int i = 0; i < n_1; i++) {
            mat_1[i] = rand_int();
        }

        for (int i = 0; i < n_2; i++) {
            mat_2[i] = rand_int();
        }
    }
    
    int partial_n = (rows_1 / size) * cols_1;

    MPI_Bcast(mat_2, n_2, MPI_INT, scatter_root, MPI_COMM_WORLD);

    if (rank == (size - 1)) {
        MPI_Scatter(mat_1, partial_n, MPI_INT,
            MPI_IN_PLACE, partial_n, MPI_INT, (size - 1), MPI_COMM_WORLD);

        for (int r = 0; r < (rows_1 / size); r++) {     // For each row of mat_1
            for (int c = 0; c < cols_2; c++) {          // For each col of mat_2
                int val = 0;
                for (int e = 0; e < cols_1; e++) {      // For each element of the column of mat_1
                    val = val + mat_1[(r * cols_1) + e] + mat_2[(c * cols_1) + e];
                }
                res_partial[(r * cols_2) + c] = val;
            }
        }

    } else {
        MPI_Scatter(mat_1, partial_n, MPI_INT,
            mat_1_partial, partial_n, MPI_INT, (size - 1), MPI_COMM_WORLD);

        for (int r = 0; r < (rows_1 / size); r++) {     // For each row of the temp mat_1
            for (int c = 0; c < cols_2; c++) {          // For each col of mat_2
                int val = 0;
                for (int e = 0; e < cols_1; e++) {      // For each element of the column of temp mat_1
                    val = val + mat_1_partial[(r * cols_1) + e] + mat_2[(c * cols_1) + e];
                }
                res_partial[(r * cols_2) + c] = val;
            }
        }
    }

    int* res = new_mat(rows_1, cols_2, false, 0);
    MPI_Gather(res_partial, (rows_1 / size) * cols_2, MPI_INT, 
        res, (rows_1 / size) * cols_2, MPI_INT, 0, MPI_COMM_WORLD);

    // Test to see if the matrix is full or not
    if (rank == 0) {
        for (int r = 0; r < 12; r++) {
            printf("Result[%d] ", r + 1);
            for (int i = 0; i < 11; i++) {
                printf("%d ", res[(r * cols_2) + i]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}