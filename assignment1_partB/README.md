
# Parallel Assignment: Merge Sort

- **Name:** Amna Atiq

- **Roll Number:** 2023-cs-83



## Problem Description

This project parallelizes the Merge Sort algorithm ((N \log N)$) using MPI. It was originally studied in the Data Structures course.



## Results Summary

- **Best Time:** 0.000163s

- **Observation:** At N=1000, communication overhead exceeds computation.



## How to Run

### Sequential:

`gcc sequential/sequential_merge.c -o seq_sort && ./seq_sort`

### Parallel:

`mpicc parallel/main_problem.c -o par_sort && mpirun -np 4 ./par_sort`

