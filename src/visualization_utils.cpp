#include "visualization_utils.h"
#include <fstream>
#include <iostream>

// Save density data to a file
void VisualizationUtils::saveDensityMap(const std::vector<Particle>& particles, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& p : particles) {
        file << p.getX() << " " << p.getY() << " " << p.getZ() << " " << p.getDensity() << "\n";
    }
    file.close();
}

// Generate a simple ASCII-based visualization
void VisualizationUtils::visualizeMap(const std::vector<double>& map, int width, int height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double value = map[i * width + j];
            std::cout << (value > 0.5 ? '#' : '.') << " ";
        }
        std::cout << "\n";
    }
}
