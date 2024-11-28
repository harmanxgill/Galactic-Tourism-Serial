// particle.h
#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
public:
    // Constructors
    Particle();
    Particle(double x, double y, double z, double mass, int id);

    // Getters and Setters
    double getX() const;
    double getY() const;
    double getZ() const;
    double getDensity() const;
    double getPressure() const;
    double getVx() const;
    double getVy() const;
    double getVz() const;
    double getMass() const;
    int getId() const; // Getter for particle ID
    void setDensity(double density);
    void setPressure(double pressure);
    void setVx(double vx);
    void setVy(double vy);
    void setVz(double vz);

    // Public variables for position and velocity
    double x, y, z; // Position
    double vx, vy, vz; // Velocity
    double density; // Density
    double pressure; // Pressure
    double mass; // Mass
    int id; // Unique particle ID
};

#endif // PARTICLE_H
