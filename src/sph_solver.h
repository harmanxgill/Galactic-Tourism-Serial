#ifndef SPH_SOLVER_H
#define SPH_SOLVER_H

#include <vector>
#include <cmath>
#include "particle.h"
using namespace std;

class SPHSolver {
    public:
    // Constructor
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
    double smoothingLength;
    double mass;
    double gasConstant;
    double restDensity;
};

#endif // SPH_SOLVER_H
