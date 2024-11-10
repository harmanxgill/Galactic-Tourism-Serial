// transparency.cpp
#include "transparency.h"
#include <cmath>
#include <fstream>

// Constructor
TransparencyCalculator::TransparencyCalculator(double threshold, double redshift)
    : threshold(threshold), redshift(redshift) {}

// Calculate optical depth using Madau model
double TransparencyCalculator::computeOpticalDepth(double density) const {
    // Simplified formula for optical depth based on density and redshift
    double tau = 0.0025 * density * (1 + redshift) * (1 + redshift);
    return tau;
}

// Calculate transparency using Madau model
std::vector<double> TransparencyCalculator::calculateTransparencyWithMadau(const std::vector<Particle>& particles) {
    std::vector<double> transparencyMap;
    for (const auto& p : particles) {
        double tau = computeOpticalDepth(p.getDensity());
        double transmission = std::exp(-tau); // Transparency score
        transparencyMap.push_back(transmission);
    }
    return transparencyMap;
}

// Save the transparency map to a file
void TransparencyCalculator::saveTransparencyMap(const std::vector<double>& transparencyMap, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& transparency : transparencyMap) {
            file << transparency << "\n";
        }
        file.close();
    }
}