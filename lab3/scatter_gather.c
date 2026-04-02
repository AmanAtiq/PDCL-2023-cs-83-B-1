#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data[4] = {10, 20, 30, 40}; // Assume size is 4
    int recv_item;

    // Scatter 1 item to each process
    MPI_Scatter(send_data, 1, MPI_INT, &recv_item, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Rank %d received %d via Scatter\n", rank, recv_item);

    // Modify data
    recv_item += 5;

    // Gather back to root
    int gather_data[4];
    MPI_Gather(&recv_item, 1, MPI_INT, gather_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered results at root: %d, %d, %d, %d\n", 
                gather_data[0], gather_data[1], gather_data[2], gather_data[3]);
    }

    MPI_Finalize();
    return 0;
}
