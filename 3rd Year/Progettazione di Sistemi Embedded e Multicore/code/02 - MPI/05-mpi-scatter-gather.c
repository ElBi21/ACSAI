#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main() {
    int debug = 0;
    int n = 40;
    int size, rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int total_elements = n * size;
    int a[total_elements], b[total_elements];
    int recv_buff_a[total_elements / size], recv_buff_b[total_elements / size];
    int total_sum[total_elements];

    if (rank == 0) {
        for (int i = 0; i < total_elements; i++) {
            a[i] = rand()%100;
            b[i] = rand()%100;
        }
    }
    
    MPI_Scatter(&a, n, MPI_INT, &recv_buff_a, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&b, n, MPI_INT, &recv_buff_b, n, MPI_INT, 0, MPI_COMM_WORLD);

    int local_sum[n];
    for (int i = 0; i < n; i++) {
        local_sum[i] = recv_buff_a[i] + recv_buff_b[i];
    }

    MPI_Gather(&local_sum, n, MPI_INT, &total_sum, n, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0 && debug == 1) {
        printf("Printing the sums:");
        for (int i = 0; i < total_elements; i++) {
            printf("A[%d] + B[%d]: %d + %d = %d\n", i, i, a[i], b[i], total_sum[i]);
        }
    }

    MPI_Finalize();
    return 0;
}