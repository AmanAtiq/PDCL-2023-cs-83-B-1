# Assignment 1 Part B: Parallel Merge Sort

## Description
This project implements a parallel version of the **Merge Sort** algorithm using MPI. It was selected as a "past problem" from a Data Structures and Algorithms course to demonstrate distributed memory parallelization.

## Parallel Strategy
- **Decomposition:** The master process (Rank 0) uses `MPI_Scatter` to distribute segments of a large random array to all available processes.
- **Local Sort:** Each process sorts its segment using the standard C `qsort` library.
- **Collection:** The sorted segments are gathered back to the master process using `MPI_Gather` for final synchronization.

## How to Run
1. Compile: `mpicc main_problem.c -o main_problem`
2. Run: `mpirun -np 4 ./main_problem`

## Performance Note
The current implementation uses a small dataset (N=1000) to demonstrate correctness. For small N, communication overhead may exceed computation savings.
