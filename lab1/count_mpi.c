#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000
#define TARGET 42

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_proc = N / size;
    int *sub_arr = malloc(sizeof(int) * elements_per_proc);
    
    srand(time(NULL) + rank); 
    for (int i = 0; i < elements_per_proc; i++) sub_arr[i] = rand() % 100;

    double start_time = MPI_Wtime();

    long local_count = 0;
    for (int i = 0; i < elements_per_proc; i++) {
        if (sub_arr[i] == TARGET) local_count++;
    }

    long global_count = 0;
    MPI_Reduce(&local_count, &global_count, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Total Count: %ld\n", global_count);
        printf("MPI Parallel Time: %f seconds\n", end_time - start_time);
    }

    free(sub_arr);
    MPI_Finalize();
    return 0;
}
