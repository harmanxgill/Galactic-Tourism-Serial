# Why Parallelization?

The Smoothed Particle Hydrodynamics (SPH) simulation involves computationally expensive operations:

1. Density, pressure, and force calculations: Each particle interacts with nearby particles, leading to `O(n^2)` complexity in a naive implementation for `n` particles.

2. Large Data: Simulations often involve thousands or millions of particles, exceeding the capacity of a single processor or memory.

**Solution:**

1. MPI: Distributes the workload across multiple processes, allowing each process to handle a subset of particles.
2. OpenMP: Further divides the workload among multiple threads within each process to utilize multi-core CPUs.

# MPI

MPI handles domain decomposition and communication between processes:

## Domain Decomposition

- The particles are divided into subsets, and each subset is assigned to an MPI process.
    - For `p` processes, each process handles approximately `n/p` particles.
- This reduces the workload per process, allowing the simulation to scale across multiple processors.

## Communication
Particles near the boundaries of a process's subdomain require information about particles in neighboring processes for SPH calculations.

- Each process sends its boundary particle data to its neighboring processes and receives data from them.
- Boundary Particle Exchange: Uses `MPI_Sendrecv` to ensure both sending and receiving happen simultaneously, avoiding deadlocks.

# OpenMP
OpenMP parallelizes loops within each MPI process to utilize multiple CPU cores. Each thread processes a subset of the particles assigned to the process.

