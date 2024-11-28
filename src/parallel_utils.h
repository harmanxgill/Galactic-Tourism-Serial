#ifndef PARALLEL_UTILS_H
#define PARALLEL_UTILS_H

#include <vector>
#include "particle.h"
#include <cmath>
using namespace std;

// Function to handle boundary particles in the serial version
void exchangeBoundaryParticles(vector<Particle>& particles);

#endif
