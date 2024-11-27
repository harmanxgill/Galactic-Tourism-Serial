// parallel_utils.cpp
#include "parallel_utils.h"
#include <algorithm> 
#include <cmath>
using namespace std;

void exchangeBoundaryParticles(vector<Particle>& particles, int rank, int size) {
    MPI_Status status;
    int particlesToSend = 10;  // Example: number of particles at boundaries to exchange
    int boundarySize = particlesToSend * sizeof(Particle);

    // Buffers for sending and receiving boundary data
    vector<Particle> sendLeft(particlesToSend);
    vector<Particle> sendRight(particlesToSend);
    vector<Particle> recvLeft(particlesToSend);
    vector<Particle> recvRight(particlesToSend);

    // Fill buffers with boundary particles
    copy(particles.begin(), particles.begin() + particlesToSend, sendLeft.begin()); // Left boundary
    copy(particles.end() - particlesToSend, particles.end(), sendRight.begin());    // Right boundary

    // Exchange particles with neighboring processes
    if (rank > 0) {
        // Send to the left neighbor and receive from the left neighbor
        MPI_Sendrecv(sendLeft.data(), boundarySize, MPI_BYTE, rank - 1, 0,
                     recvLeft.data(), boundarySize, MPI_BYTE, rank - 1, 0,
                     MPI_COMM_WORLD, &status);
    }
    if (rank < size - 1) {
        // Send to the right neighbor and receive from the right neighbor
        MPI_Sendrecv(sendRight.data(), boundarySize, MPI_BYTE, rank + 1, 0,
                     recvRight.data(), boundarySize, MPI_BYTE, rank + 1, 0,
                     MPI_COMM_WORLD, &status);
    }

    // Append received boundary particles to the local particle list
    if (rank > 0) {
        particles.insert(particles.begin(), recvLeft.begin(), recvLeft.end());
    }
    if (rank < size - 1) {
        particles.insert(particles.end(), recvRight.begin(), recvRight.end());
    }
}
