cat <<EOF > manual_bcast.c
#include <mpi.h>
#include <stdio.h>

/* Manual Broadcast Implementation:
   The root sends to every process individually.
   This is O(N) complexity.
*/
void manual_bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    if (rank == root) {
        for (int i = 0; i < size; i++) {
            if (i != root) {
                MPI_Send(data, count, datatype, i, 0, comm);
            }
        }
    } else {
        MPI_Recv(data, count, datatype, root, 0, comm, MPI_STATUS_IGNORE);
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, data = 0;
    if (rank == 0) data = 777;

    double start = MPI_Wtime();
    manual_bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    double end = MPI_Wtime();

    if (rank == 0) printf("Manual Bcast Result: %d, Time: %f\n", data, end - start);
    MPI_Finalize();
    return 0;
}
EOF
