#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// (-1)^n \cdot \frac{1}{2n + 1}

int thread_count;
long sum;
int* total_estimates;

void estimate(void* n, void* r) {
    long rank = (long) r;
    double factor;
    long nums = (long) n / thread_count;
    long first_ind = rank * nums / thread_count;
    long last_ind = first_ind + nums;

    if (rank % 2 == 0) {
        factor = 1;
    } else {
        factor = -1;
    }

    for (int i = first_ind; i < last_ind; i++) {
        sum += factor/(2 * i + 1);
    }
}

int main(int argc, char** argv) {
    thread_count = (int*) strtol(argv[1], NULL, 10);
    int total_estimates[thread_count];

    pthread_t* t_handle;
    int* t_handles = malloc(thread_count * sizeof(pthread_t));

    for (int t = 0; t < thread_count; t++) {
        pthread_create(&t_handles[t], NULL, estimate, (void*) t);
    }

    for (int t = 0; t < thread_count; t++) {
        pthread_join(t_handles[t], NULL);
    }

    printf("The computed estimate is %ld\n", sum);
    return 0;
}