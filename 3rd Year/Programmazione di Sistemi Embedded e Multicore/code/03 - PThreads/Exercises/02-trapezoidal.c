#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

float TOTAL_AREA;
int A, B;
float H;
pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;

int f(float x) {
    return 4 * x * x + 2 * x - 3 ;
}

void* compute_area(void* rank_param) {
    
    int rank = (int) rank_param;
    float x = A + (rank * H);

    pthread_mutex_lock(&MUTEX);

    TOTAL_AREA += f(x);

    pthread_mutex_unlock(&MUTEX);
}

int main(int argc, char** argv) {
    long thread_count = strtol(argv[1], NULL, 10);
    A = (int*) strtol(argv[2], NULL, 10);
    B = (int*) strtol(argv[3], NULL, 10);
    H = (B - A) / thread_count;

    pthread_t* thread_handles;
    thread_handles = malloc(thread_count * sizeof(pthread_t));
    pthread_mutex_init(&MUTEX, NULL);

    for (int t = 0; t < thread_count; t++) {
        pthread_create(&thread_handles[t], NULL, compute_area, (void*) t);
    }

    for (int t = 0; t < thread_count; t++) {
        pthread_join(thread_handles[t], NULL);
    }

    printf("The area is %f", TOTAL_AREA);
    return NULL;
}