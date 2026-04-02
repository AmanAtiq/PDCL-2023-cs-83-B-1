#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int limit = 10;
    int count = 0;
    int partner_rank = (rank + 1) % 2;

    while (count < limit) {
        if (rank == count % 2) {
            count++;
            MPI_Send(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("Rank %d sent and incremented count %d to rank %d\n", rank, count, partner_rank);
        } else {
            MPI_Recv(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Rank %d received count %d from rank %d\n", rank, count, partner_rank);
        }
    }
    MPI_Finalize();
    return 0;
}
