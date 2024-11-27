// particle.cpp
#include "particle.h"
#include <cmath>
using namespace std;

// Default constructor
Particle::Particle() 
    : x(0.0), y(0.0), z(0.0), vx(0.0), vy(0.0), vz(0.0), density(0.0), pressure(0.0), mass(1.0) {}

// Parameterized constructor
Particle::Particle(double x, double y, double z, double mass) 
    : x(x), y(y), z(z), vx(0.0), vy(0.0), vz(0.0), density(0.0), pressure(0.0), mass(mass) {}

// Getters
double Particle::getX() const { return x; }
double Particle::getY() const { return y; }
double Particle::getZ() const { return z; }
double Particle::getDensity() const { return density; }
double Particle::getPressure() const { return pressure; }
double Particle::getMass() const { return mass; }

// Setters
void Particle::setDensity(double density) { this->density = density; }
void Particle::setPressure(double pressure) { this->pressure = pressure; }
void Particle::setVelocity(double vx, double vy, double vz) {
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
}
