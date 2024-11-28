#include <vector>
#include "particle.h"
#include "sph_solver.h"
#include "transparency.h"
#include "visualization_utils.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void printUsage() {
    cout << "Usage: ./galactic_tourism <option>\n"
         << "Options:\n"
         << "  run                - Run the SPH simulation\n"
         << "  visualize_density  - Visualize density map\n"
         << "  visualize_transparency - Visualize transparency map\n"
         << "  animate_density    - Generate density animation\n"
         << "  animate_transparency - Generate transparency animation\n"
         << endl;
}

// Function to initialize particles with random positions (or specific initial conditions)
vector<Particle> initializeParticles(int numParticles, double mass) {
    vector<Particle> particles;
    for (int i = 0; i < numParticles; ++i) {
        double x = static_cast<double>(rand()) / RAND_MAX;
        double y = static_cast<double>(rand()) / RAND_MAX;
        double z = static_cast<double>(rand()) / RAND_MAX;
        particles.emplace_back(x, y, z, mass);
    }
    return particles;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        printUsage();
        return 1;
    }

    // Simulation parameters
    const double smoothingLength = 0.1;      // Smoothing length for kernel
    const double mass = 1.0;                 // Mass of each particle
    const double gasConstant = 1000.0;       // Constant for pressure calculation
    const double restDensity = 1.0;          // Rest density of particles
    const double transparencyThreshold = 0.5; // Threshold density for transparency
    const double redshift = 2.0;             // Redshift parameter for Madau model
    const int numSteps = 100;                // Number of simulation steps
    const double dt = 0.01;                  // Time step for simulation
    const int numParticles = 1000;           // Number of particles

    // Initialize particles
    vector<Particle> particles = initializeParticles(numParticles, mass);

    // Create SPH and Transparency solvers
    SPHSolver sphSolver(smoothingLength, mass, gasConstant, restDensity);
    TransparencyCalculator transparencyCalculator(transparencyThreshold, redshift);

    // Main simulation loop
    for (int step = 0; step < numSteps; ++step) {
        // Compute SPH properties
        sphSolver.computeDensity(particles);
        sphSolver.computePressure(particles);
        sphSolver.computeForces(particles);

        // Update particle positions based on velocity
        for (auto& p : particles) {
            p.x += p.vx * dt;
            p.y += p.vy * dt;
            p.z += p.vz * dt;
        }

        // Output intermediate results for monitoring
        if (step % 10 == 0) {
            cout << "Completed step " << step << endl;
        }
    }

    // Calculate transparency map
    vector<double> transparencyMap = transparencyCalculator.calculateTransparencyWithMadau(particles);
    transparencyCalculator.saveTransparencyMap(transparencyMap, "transparency_map_with_madau.txt");

    cout << "Simulation complete. Transparency map saved to transparency_map_with_madau.txt" << endl;

    return 0;
}
