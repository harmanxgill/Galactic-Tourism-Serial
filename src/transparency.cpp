#include "transparency.h"
#include <cmath>
#include <fstream>
using namespace std;

// Constructor
TransparencyCalculator::TransparencyCalculator(double transparencyThreshold, double redshift)
    : transparencyThreshold(transparencyThreshold), redshift(redshift) {}

// Calculate transparency for each particle using a density threshold
vector<double> TransparencyCalculator::calculateTransparency(const vector<Particle>& particles) {
    vector<double> transparencyMap;
    for (const auto& p : particles) {
        double transparency = p.getDensity() < transparencyThreshold ? 1.0 : 0.0;
        transparencyMap.push_back(transparency);
    }
    return transparencyMap;
}

// Incorporate Madau model for transparency with redshift
vector<double> TransparencyCalculator::calculateTransparencyWithMadau(const vector<Particle>& particles) {
    vector<double> transparencyMap;
    for (const auto& p : particles) {
        double baseTransparency = p.getDensity() < transparencyThreshold ? 1.0 : 0.0;
        double attenuation = exp(-redshift * p.getDensity());
        transparencyMap.push_back(baseTransparency * attenuation);
    }
    return transparencyMap;
}

// Save transparency map to a file
void TransparencyCalculator::saveTransparencyMap(const vector<double>& transparencyMap, const string& filename) {
    ofstream file(filename);
    for (const auto& value : transparencyMap) {
        file << value << "\n";
    }
    file.close();
}
