# Lab 1: Distributed Memory Programming with MPI

## Overview
This lab covers the transition from shared-memory (Pthreads) to distributed-memory systems using the **Message Passing Interface (MPI)**. It demonstrates the **SPMD** (Single Program, Multiple Data) model and explores both point-to-point and collective communication.

## Files
* **hello_mpi.c**: Demonstrates basic rank and size identification.
* **even_odd.c**: Implements conditional logic based on process rank.
* **pingpong.c**: Measures communication latency using `MPI_Send` and `MPI_Recv`.
* **count_mpi.c**: Implements parallel counting using `MPI_Reduce` for global summation.

## Compilation and Execution
To compile the MPI programs:
```bash
mpicc -O2 <filename>.c -o <output_name>
```

To run with 2 processes:
```bash
mpirun -np 2 ./<output_name>
```

## Key Observations
* **Point-to-Point**: Used in ping-pong to pass data between specific ranks.
* **Collective**: `MPI_Reduce` was used to efficiently gather local counts into a global sum on Rank 0, avoiding the manual lock contention issues seen in Pthreads.
