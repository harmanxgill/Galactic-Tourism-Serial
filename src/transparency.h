#ifndef TRANSPARENCY_H
#define TRANSPARENCY_H

#include <vector>
#include <string> 
#include <cmath>
#include "particle.h"
using namespace std;

class TransparencyCalculator {
private:
    double transparencyThreshold;
    double redshift;

public:
    TransparencyCalculator(double transparencyThreshold, double redshift);
    vector<double> calculateTransparency(const vector<Particle>& particles);
    vector<double> calculateTransparencyWithMadau(const vector<Particle>& particles);
    void saveTransparencyMap(const vector<double>& transparencyMap, const string& filename);
};

#endif
