#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

long thread_count;
long total_launches;
//int num_estimates;
int sum;
pthread_mutex_t sum_lock = PTHREAD_MUTEX_INITIALIZER;

double rand_double() {
    // Generates a random double
    return 2 * (rand() / (double) RAND_MAX) - 1;
}

void* estimate(void* rank) {
    // Estimates pi for one thread
    int in_circle = 0;
    srand(time(NULL));
    printf("Ciao sono thread %d e stimerò con %d lanci\n", (int*) rank, (int*) (total_launches / thread_count));

    for (int i = 0; i < (total_launches / thread_count); i++) {
        double x = rand_double();
        double y = rand_double();
        if ((x * x + y * y) <= 1) {
            in_circle++;
        }
    }

    pthread_mutex_lock(&sum_lock);
    sum += in_circle;
    pthread_mutex_unlock(&sum_lock);

    return NULL;
}

int main(int argv, char** argc) {
    fprintf(stderr, "\n\n\n");
    if ((strtol(argc[1], NULL, 10) == 0) && (strtol(argc[2], NULL, 10) == 0)) {
        return 1;
    }

    thread_count = strtol(argc[1], NULL, 10);
    total_launches = strtol(argc[2], NULL, 10);

    pthread_t* t_handles;
    t_handles = malloc(thread_count * sizeof(pthread_t));

    pthread_mutex_init(&sum_lock, NULL);
    
    for (int t = 0; t < thread_count; t++) {
        pthread_create(&t_handles[t], NULL, estimate, (void*) t);
    }

    for (int t = 0; t < thread_count; t++) {
        pthread_join(t_handles[t], NULL);
    }

    free(t_handles);

    double final = ((double) sum * 4) / (double) (total_launches);
    printf("The estimated value with %ld threads is %f", thread_count, final);

    return 0;
}