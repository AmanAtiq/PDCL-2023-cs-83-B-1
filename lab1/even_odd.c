#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank % 2 == 0) printf("Rank %d: I am even\n", rank);
    else printf("Rank %d: I am odd\n", rank);

    MPI_Finalize();
    return 0;
}
