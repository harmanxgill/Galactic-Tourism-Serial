# Galactic Tourism: Mapping Cosmic Transparency

## Overview
This project simulates the intergalactic medium (IGM) using Smoothed Particle Hydrodynamics (SPH) and computes cosmic transparency maps based on particle density and the Madau model for redshift attenuation. It leverages **MPI** and **OpenMP** for high-performance parallelization, making it suitable for large-scale simulations on modern clusters.

## Workflow Overview

### 1. Particle Initialization
- Particles are randomly distributed in a 3D unit cube.
- Each particle is assigned properties like position, velocity, mass, and density.

### 2. SPH Simulation
- Computes density, pressure, and forces for each particle using SPH kernels.
- Updates particle positions over time using calculated velocities.

### 3. Parallelization
#### MPI
- Distributes particles across processes (domain decomposition).
- Handles boundary particle exchange between neighboring processes.

#### OpenMP
- Parallelizes particle computations (density, pressure, forces) within each process.

### 4. Transparency Calculation
- Computes transparency based on particle densities and the Madau model.
- Outputs transparency maps for visualization.