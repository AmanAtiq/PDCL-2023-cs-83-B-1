#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4 // Size of the NxN matrix and vector

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_proc = N / size;
    int matrix[N][N];
    int vector[N];
    int result_vector[N];
    int local_matrix[rows_per_proc][N];
    int local_result[rows_per_proc];

    if (rank == 0) {
        // Initialize Matrix A and Vector x
        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            vector[i] = i + 1; // Vector: [1, 2, 3, 4]
            for (int j = 0; j < N; j++) {
                matrix[i][j] = i + j;
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    // 1. Broadcast the full vector to everyone
    MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);

    // 2. Scatter rows of the matrix to each process
    MPI_Scatter(matrix, rows_per_proc * N, MPI_INT, local_matrix, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    // 3. Local calculation: y_local = A_local * x
    for (int i = 0; i < rows_per_proc; i++) {
        local_result[i] = 0;
        for (int j = 0; j < N; j++) {
            local_result[i] += local_matrix[i][j] * vector[j];
        }
    }

    // 4. Gather local results back into the final result vector y
    MPI_Gather(local_result, rows_per_proc, MPI_INT, result_vector, rows_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nResult Vector y:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", result_vector[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
