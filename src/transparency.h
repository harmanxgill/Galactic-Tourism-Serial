// transparency.h
#ifndef TRANSPARENCY_H
#define TRANSPARENCY_H

#include <vector>
#include "particle.h"

class TransparencyCalculator {
public:
    TransparencyCalculator(double threshold, double redshift);
    std::vector<double> calculateTransparencyWithMadau(const std::vector<Particle>& particles);
    void saveTransparencyMap(const std::vector<double>& transparencyMap, const std::string& filename);

private:
    double threshold; // Density threshold for transparency
    double redshift; // Redshift parameter for Madau model
    double computeOpticalDepth(double density) const; // Madau optical depth calculation
};

#endif // TRANSPARENCY_H