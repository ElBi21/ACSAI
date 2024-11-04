#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int THREAD_COUNT;

void* Hello(void* rank_par) {
    long rank = (long) rank_par;

    printf("Rank %ld says hello\n", rank);
    return NULL;
}

int main(int argc, char** argv[]) {
    pthread_t* thread_handles;

    THREAD_COUNT = strtol(argv[1], NULL, 10);
    thread_handles = malloc(THREAD_COUNT * sizeof(pthread_t));

    for (int t = 0; t < THREAD_COUNT; t++) {
        pthread_create(&thread_handles[t], NULL, Hello, (void*) t);
    }

    printf("Hello from the main thread");

    for (int t = 0; t < THREAD_COUNT; t++) {
        pthread_join(thread_handles[t], NULL);
    }

    free(thread_handles);
    return 0;
}