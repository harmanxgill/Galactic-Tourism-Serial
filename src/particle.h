// particle.h
#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

class Particle {
    public:
    // Constructors
    Particle();
    Particle(double x, double y, double z, double mass);

    // Getters and Setters
    double getX() const;
    double getY() const;
    double getZ() const;
    double getDensity() const;
    double getPressure() const;
    double getMass() const;

    void setDensity(double density);
    void setPressure(double pressure);
    void setVelocity(double vx, double vy, double vz);

    // Public member variables for simplicity (or use private with getters/setters)
    double x, y, z;        // Position
    double vx, vy, vz;     // Velocity
    double density;        // Density
    double pressure;       // Pressure
    double mass;           // Mass

    private:
        // To add more internal variables or helper functions here
};

#endif // PARTICLE_H