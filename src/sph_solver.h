#ifndef SPH_SOLVER_H
#define SPH_SOLVER_H

#include <vector>
#include <cmath>
#include "particle.h"
using namespace std;

class SPHSolver {
public:
    // Constructor to initialize the SPH solver with necessary parameters
    SPHSolver(double smoothingLength, double mass, double gasConstant, double restDensity);

    // Main SPH computation functions
    void computeDensity(vector<Particle>& particles);
    void computePressure(vector<Particle>& particles);
    void computeForces(vector<Particle>& particles);

private:
    // SPH Kernel functions
    double poly6Kernel(double r, double h) const;
    double spikyKernelGrad(double r, double h) const;

    // SPH Constants
    double smoothingLength;   // Smoothing length (h)
    double mass;              // Mass of each particle
    double gasConstant;       // Gas constant for pressure calculation
    double restDensity;       // Rest density of the particles
};

#endif // SPH_SOLVER_H
