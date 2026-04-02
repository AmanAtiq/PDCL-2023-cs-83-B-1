#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Each rank starts with its (rank + 1) as the value
    int local_val = rank + 1;
    int scan_result;

    // MPI_Scan computes the inclusive prefix sum
    MPI_Scan(&local_val, &scan_result, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Rank %d: Local Value = %d, Prefix Sum = %d\n", rank, local_val, scan_result);

    MPI_Finalize();
    return 0;
}
