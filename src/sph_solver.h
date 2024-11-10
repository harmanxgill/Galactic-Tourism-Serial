// sph_solver.h
#ifndef SPH_SOLVER_H
#define SPH_SOLVER_H

#include <vector>
#include "particle.h"

class SPHSolver{
    public:
    // Constructor
    SPHSolver(double smoothingLength, double mass, double gasConstant, double restDensity);

    // Main SPH computation functions
    void computeDensity(std::vector<Particle>& particles);
    void computePressure(std::vector<Particle>& particles);
    void computeForces(std::vector<Particle>& particles);

    private:
    // SPH Kernel functions
    double poly6Kernel(double r, double h) const;
    double spikyKernelGrad(double r, double h) const;

    // SPH Constants
    double smoothingLength;
    double mass;
    double gasConstant;
    double restDensity;
};

#endif // SPH_SOLVER_H