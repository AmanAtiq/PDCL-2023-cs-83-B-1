#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, data;
    if (rank == 0) data = 100; // Root sets the value

    // All processes call Bcast, rank 0 is the root
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Rank %d received data: %d\n", rank, data);

    MPI_Finalize();
    return 0;
}
