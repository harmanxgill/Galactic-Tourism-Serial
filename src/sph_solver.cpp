// sph_solver.cpp
#include "sph_solver.h"
#include <cmath>

// Constructor
SPHSolver::SPHSolver(double smoothingLength, double mass, double gasConstant, double restDensity)
    : smoothingLength(smoothingLength), mass(mass), gasConstant(gasConstant), restDensity(restDensity) {}

// Poly6 kernel for density calculation
double SPHSolver::poly6Kernel(double r, double h) const {
    if (r < h) {
        double coeff = 315.0 / (64.0 * M_PI * pow(h, 9));
        return coeff * pow(h * h - r * r, 3);
    }
    return 0.0;
}

// Spiky kernel gradient for force calculation
double SPHSolver::spikyKernelGrad(double r, double h) const {
    if (r < h) {
        double coeff = -45.0 / (M_PI * pow(h, 6));
        return coeff * pow(h - r, 2);
    }
    return 0.0;
}

// Compute density for each particle
void SPHSolver::computeDensity(std::vector<Particle>& particles) {
    for (auto& pi : particles) {
        pi.setDensity(0.0);
        for (const auto& pj : particles) {
            double r = sqrt(pow(pi.x - pj.x, 2) + pow(pi.y - pj.y, 2) + pow(pi.z - pj.z, 2));
            pi.setDensity(pi.getDensity() + mass * poly6Kernel(r, smoothingLength));
        }
    }
}

// Compute pressure for each particle based on density
void SPHSolver::computePressure(std::vector<Particle>& particles) {
    for (auto& p : particles) {
        double pressure = gasConstant * (p.getDensity() - restDensity);
        p.setPressure(pressure > 0 ? pressure : 0.0);  // Prevent negative pressure
    }
}

// Compute forces on each particle from pressure differences
void SPHSolver::computeForces(std::vector<Particle>& particles) {
    for (auto& pi : particles) {
        double fx = 0.0, fy = 0.0, fz = 0.0;

        for (const auto& pj : particles) {
            if (&pi != &pj) {
                double r = sqrt(pow(pi.x - pj.x, 2) + pow(pi.y - pj.y, 2) + pow(pi.z - pj.z, 2));
                if (r < smoothingLength && r > 0) {
                    double force = (pi.getPressure() + pj.getPressure()) / (2.0 * pj.getDensity()) * spikyKernelGrad(r, smoothingLength);
                    fx += force * (pi.x - pj.x) / r;
                    fy += force * (pi.y - pj.y) / r;
                    fz += force * (pi.z - pj.z) / r;
                }
            }
        }

        // Update velocities based on force and particle mass
        pi.vx += fx / pi.getDensity();
        pi.vy += fy / pi.getDensity();
        pi.vz += fz / pi.getDensity();
    }
}