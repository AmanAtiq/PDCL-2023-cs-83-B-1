# Lab 1: Getting Started with MPI
This lab introduces the fundamental environment setup for Distributed Memory programming using the Message Passing Interface (MPI).

## Key Exercises
1. **Hello World:** Initializing and shutting down the MPI environment using `MPI_Init` and `MPI_Finalize`.
2. **Rank and Size:** Using `MPI_Comm_rank` and `MPI_Comm_size` to manage process identification.
3. **Ping-Pong:** Implementing basic point-to-point communication where two processes exchange data sequentially.

## How to Compile and Run

### Hello World / Rank and Size:
1. **Compile:**
   ```bash
   mpicc hello_mpi.c -o hello_mpi
   ```
2. **Run (with 4 processes):**
   ```bash
   mpirun -np 4 ./hello_mpi
   ```

### Ping-Pong:
1. **Compile:**
   ```bash
   mpicc pingpong.c -o pingpong
   ```
2. **Run (with 2 processes):**
   ```bash
   mpirun -np 2 ./pingpong
   ```
