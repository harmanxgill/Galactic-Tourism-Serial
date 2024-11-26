#ifndef PARALLEL_UTILS_H
#define PARALLEL_UTILS_H

#include <vector>
#include "particle.h"
#include <mpi.h>

// Function to exchange boundary particles between neighboring MPI processes
void exchangeBoundaryParticles(std::vector<Particle>& particles, int rank, int size);

#endif
