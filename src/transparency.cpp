#include "transparency.h"
#include <cmath>
#include <fstream>
#include <iostream> // For debugging output
using namespace std;

// Constructor
TransparencyCalculator::TransparencyCalculator(double transparencyThreshold, double redshift)
    : transparencyThreshold(transparencyThreshold), redshift(redshift) {}

// Calculate transparency for each particle using a density threshold
vector<double> TransparencyCalculator::calculateTransparency(const vector<Particle>& particles) {
    vector<double> transparencyMap;
    
    for (const auto& p : particles) {
        // For particles with density below the threshold, set transparency to 1.0 (transparent)
        // For particles with density above the threshold, set transparency to 0.0 (opaque)
        double transparency = p.getDensity() < transparencyThreshold ? 1.0 : 0.0;
        
        // Debugging: Print particle density and the calculated transparency
        cout << "Particle Density: " << p.getDensity() << ", Transparency: " << transparency << endl;

        transparencyMap.push_back(transparency);
    }
    return transparencyMap;
}

// Incorporate Madau model for transparency with redshift
vector<double> TransparencyCalculator::calculateTransparencyWithMadau(const vector<Particle>& particles) {
    vector<double> transparencyMap;
    for (const auto& p : particles) {
        // Calculate base transparency
        double baseTransparency = p.getDensity() < transparencyThreshold ? 1.0 : 0.0;
        
        // Calculate attenuation based on density and redshift
        double attenuation = exp(-redshift * p.getDensity());
        
        // Final transparency calculation
        double finalTransparency = baseTransparency * attenuation;
        
        // Debugging: Print particle ID, density, transparency values
        cout << "Particle ID: " << p.getId() 
             << ", Density: " << p.getDensity()
             << ", Base Transparency: " << baseTransparency
             << ", Attenuation: " << attenuation
             << ", Final Transparency: " << finalTransparency << endl;
        
        transparencyMap.push_back(finalTransparency);
    }
    return transparencyMap;
}

// Save transparency map to a file
void TransparencyCalculator::saveTransparencyMap(const vector<double>& transparencyMap, const string& filename) {
    ofstream file(filename);
    
    // Write transparency values to the file
    for (const auto& value : transparencyMap) {
        file << value << "\n";
    }
    file.close();
}
