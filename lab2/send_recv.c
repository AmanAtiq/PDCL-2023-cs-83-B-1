#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        int send_val = 100;
        MPI_Send(&send_val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent value %d to process 1\n", send_val);
    } else if (rank == 1) {
        int recv_val;
        MPI_Recv(&recv_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received value %d from process 0\n", recv_val);
    }

    MPI_Finalize();
    return 0;
}
