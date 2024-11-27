#ifndef VISUALIZATION_UTILS_H
#define VISUALIZATION_UTILS_H

#include <vector>
#include <string>
#include <cmath>
#include "particle.h"
using namespace std;

class VisualizationUtils {
public:
    static void saveDensityMap(const vector<Particle>& particles, const string& filename);
    static void visualizeMap(const vector<double>& map, int width, int height);
};

#endif
