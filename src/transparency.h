#ifndef TRANSPARENCY_H
#define TRANSPARENCY_H

#include <vector>
#include <string> 
#include "particle.h"

class TransparencyCalculator {
private:
    double transparencyThreshold;
    double redshift;

public:
    TransparencyCalculator(double transparencyThreshold, double redshift);
    std::vector<double> calculateTransparency(const std::vector<Particle>& particles);
    std::vector<double> calculateTransparencyWithMadau(const std::vector<Particle>& particles);
    void saveTransparencyMap(const std::vector<double>& transparencyMap, const std::string& filename);
}
#endif