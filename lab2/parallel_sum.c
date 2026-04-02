#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_proc = N / size;

    if (rank == 0) {
        int arr[N];
        for (int i = 0; i < N; i++) arr[i] = i + 1;

        // Send chunks to other processes
        for (int i = 1; i < size; i++) {
            MPI_Send(&arr[i * elements_per_proc], elements_per_proc, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        // Master processes its own chunk
        long sum = 0;
        for (int i = 0; i < elements_per_proc; i++) sum += arr[i];

        // Collect partial sums
        for (int i = 1; i < size; i++) {
            long tmp_sum;
            MPI_Recv(&tmp_sum, 1, MPI_LONG, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += tmp_sum;
        }
        printf("Total Sum: %ld\n", sum);
    } else {
        int *sub_arr = malloc(sizeof(int) * elements_per_proc);
        MPI_Recv(sub_arr, elements_per_proc, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        long local_sum = 0;
        for (int i = 0; i < elements_per_proc; i++) local_sum += sub_arr[i];

        MPI_Send(&local_sum, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
        free(sub_arr);
    }

    MPI_Finalize();
    return 0;
}
