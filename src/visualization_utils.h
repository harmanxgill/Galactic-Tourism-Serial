#ifndef VISUALIZATION_UTILS_H
#define VISUALIZATION_UTILS_H

#include <vector>
#include <string>
#include "particle.h"

class VisualizationUtils {
public:
    static void saveDensityMap(const std::vector<Particle>& particles, const std::string& filename);
    static void visualizeMap(const std::vector<double>& map, int width, int height);
};

#endif
