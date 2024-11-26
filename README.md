# Galactic Tourism: Mapping Cosmic Transparency

## Overview
This project simulates the intergalactic medium (IGM) using Smoothed Particle Hydrodynamics (SPH) and computes cosmic transparency maps based on particle density and the Madau model for redshift attenuation. It leverages **MPI** and **OpenMP** for high-performance parallelization, making it suitable for large-scale simulations on modern clusters.

## Features
- **SPH Simulation:** Models particle density, pressure, and forces in the IGM.
- **Transparency Mapping:** Calculates transparency scores with support for the Madau model.
- **Parallelization:**
    - **MPI:** Distributes particles among processes for domain decomposition.
    - **OpenMP:** Parallelizes computations within each process.
- **Visualization:** Generates density and transparency maps, with options for animations.