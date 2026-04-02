cat <<EOF > allreduce.c
#include <mpi.h>
#include <stdio.h>

/*
   Allreduce: Every process contributes a local value,
   and every process receives the global sum.
*/
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int local_val = rank + 1;
    int global_sum;

    MPI_Allreduce(&local_val, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Rank %d: Local %d, Global Sum %d\n", rank, local_val, global_sum);

    MPI_Finalize();
    return 0;
}
EOF
