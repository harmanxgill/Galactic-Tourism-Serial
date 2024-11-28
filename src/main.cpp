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
// Function to initialize particles with random positions (and assign unique IDs)
vector<Particle> initializeParticles(int numParticles, double mass) {
    vector<Particle> particles;
    const double boxSize = 0.0928; // Box size
    double maxVelocity = 0.5; 

    for (int i = 0; i < numParticles; ++i) {
        double x = static_cast<double>(rand()) / RAND_MAX * boxSize; 
        double y = static_cast<double>(rand()) / RAND_MAX * boxSize; 
        double z = static_cast<double>(rand()) / RAND_MAX * boxSize; 

        double vx = (static_cast<double>(rand()) / RAND_MAX) * maxVelocity;
        double vy = (static_cast<double>(rand()) / RAND_MAX) * maxVelocity;
        double vz = (static_cast<double>(rand()) / RAND_MAX) * maxVelocity;
        
       Particle p(x, y, z, mass, i);
        p.setVx(vx);  // Set velocity
        p.setVy(vy);
        p.setVz(vz);
        p.setDensity(0);             // Set density
        p.setPressure(0);            // Set pressure
        particles.push_back(p);

       cout << "Particle " << i << " -> x: " << x << ", y: " << y << ", z: " << z
     << ", vx: " << p.getVx() << ", vy: " << p.getVy() << ", vz: " << p.getVz()
     << ", density: " << p.getDensity() << ", pressure: " << p.getPressure() << endl;
    }

    return particles;
}

// Function to print particle specs
void printParticleSpecs(const vector<Particle>& particles, int step) {
    cout << "Step " << step << ":\n";
    for (size_t i = 0; i < particles.size(); ++i) {
        const Particle& p = particles[i];
        cout << "Particle " << i << " -> x: " << p.getX() 
             << ", y: " << p.getY()
             << ", z: " << p.getZ()
             << ", vx: " << p.getVx() 
             << ", vy: " << p.getVy()
             << ", vz: " << p.getVz()
             << ", density: " << p.getDensity() 
             << ", pressure: " << p.getPressure() << endl;
    }
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
    const double transparencyThreshold = 0.3; // Threshold density for transparency
    const double redshift = 1.0;             // Redshift parameter for Madau model
    const int numSteps = 1000;                // Number of simulation steps
    const double dt = 100;                  // Time step for simulation
    const int numParticles = 10;           // Number of particles

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

        // Print particle specs for this timestep
        if (step % 100 == 0) {
            printParticleSpecs(particles, step);
        }
        
    }

    // Calculate transparency map
    vector<double> transparencyMap = transparencyCalculator.calculateTransparencyWithMadau(particles);
    transparencyCalculator.saveTransparencyMap(transparencyMap, "transparency_map_with_madau.txt");

    cout << "Simulation complete. Transparency map saved to transparency_map_with_madau.txt" << endl;

    return 0;
}
