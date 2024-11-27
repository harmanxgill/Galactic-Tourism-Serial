#include "visualization_utils.h"
#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;

// Save density data to a file
void VisualizationUtils::saveDensityMap(const vector<Particle>& particles, const string& filename) {
    ofstream file(filename);
    for (const auto& p : particles) {
        file << p.getX() << " " << p.getY() << " " << p.getZ() << " " << p.getDensity() << "\n";
    }
    file.close();
}

// Generate a simple ASCII-based visualization
void VisualizationUtils::visualizeMap(const vector<double>& map, int width, int height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double value = map[i * width + j];
            cout << (value > 0.5 ? '#' : '.') << " ";
        }
        cout << "\n";
    }
}
