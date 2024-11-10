#include <iostream>
#include <cassert>
#include <vector>
#include "../src/particle.h"
#include "../src/sph_solver.h"
#include "../src/transparency.h"

// Test Particle Initialization
void testParticleInitialization() {
    Particle p(1.0, 2.0, 3.0, 1.0); // Initialize with position and mass
    assert(p.getX() == 1.0);
    assert(p.getY() == 2.0);
    assert(p.getZ() == 3.0);
    assert(p.getMass() == 1.0);
    assert(p.getDensity() == 0.0); // Check default values
    assert(p.getPressure() == 0.0);

    std::cout << "Particle initialization test passed.\n";
}

// Test Density Calculation in SPHSolver
void testDensityCalculation() {
    // Set up particles in a known configuration
    std::vector<Particle> particles;
    particles.emplace_back(0.0, 0.0, 0.0, 1.0);
    particles.emplace_back(0.1, 0.0, 0.0, 1.0); // Close to first particle

    // Set SPH solver with parameters
    double smoothingLength = 0.15;
    double mass = 1.0;
    double gasConstant = 1.0; // Irrelevant for density test
    double restDensity = 0.0; // Irrelevant for density test
    SPHSolver solver(smoothingLength, mass, gasConstant, restDensity);

    // Compute densities
    solver.computeDensity(particles);

    // Check densities (you may need to adjust expected values based on kernel choice)
    assert(particles[0].getDensity() > 0.0); // Density should be positive
    assert(particles[1].getDensity() > 0.0);
    std::cout << "Density calculation test passed.\n";
}

// Test Transparency Calculation with Madau Model
void testTransparencyCalculation() {
    // Initialize particles with known densities
    std::vector<Particle> particles;
    particles.emplace_back(0.0, 0.0, 0.0, 1.0);
    particles[0].setDensity(0.5); // Manually set density for test

    double threshold = 1.0;
    double redshift = 2.0;
    TransparencyCalculator calculator(threshold, redshift);

    // Calculate transparency
    std::vector<double> transparencyMap = calculator.calculateTransparencyWithMadau(particles);

    // Expected transparency should be less than 1 due to non-zero density
    assert(transparencyMap[0] < 1.0);
    std::cout << "Transparency calculation test passed.\n";
}

// Main function to run all tests
int main() {
    std::cout << "Running tests...\n";

    testParticleInitialization();
    testDensityCalculation();
    testTransparencyCalculation();

    std::cout << "All tests passed successfully.\n";
    return 0;
}