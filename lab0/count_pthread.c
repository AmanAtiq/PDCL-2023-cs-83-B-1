#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 300000000
#define TARGET 42

int *arr;
long global_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    long start;
    long end;
} ThreadArgs;

void* count_chunk(void* arg) {
    ThreadArgs *args = (ThreadArgs*) arg;
    long local_count = 0;

    for (long i = args->start; i < args->end; i++) {
        if (arr[i] == TARGET)
            local_count++;
    }

    pthread_mutex_lock(&mutex);
    global_count += local_count;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {

    int NUM_THREADS = 4;   // default

    if (argc > 1)
        NUM_THREADS = atoi(argv[1]);

    arr = malloc(N * sizeof(int));
    if (!arr) { perror("malloc"); return 1; }

    srand(time(NULL));
    for (long i = 0; i < N; i++)
        arr[i] = rand() % 100;

    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];

    long chunk_size = N / NUM_THREADS;

    clock_t start = clock();

    for (int t = 0; t < NUM_THREADS; t++) {
        args[t].start = t * chunk_size;
        args[t].end = (t == NUM_THREADS - 1) ? N : (t + 1) * chunk_size;
        pthread_create(&threads[t], NULL, count_chunk, &args[t]);
    }

    for (int t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t], NULL);

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Count = %ld\n", global_count);
    printf("Time with %d threads = %.4f seconds\n", NUM_THREADS, elapsed);

    free(arr);
    pthread_mutex_destroy(&mutex);
    return 0;
}
