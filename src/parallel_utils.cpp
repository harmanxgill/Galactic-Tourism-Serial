#include "parallel_utils.h"
#include <algorithm>
#include <cmath>
using namespace std;

void exchangeBoundaryParticles(vector<Particle>& particles) {
    // Example: Just keep the first 10 and last 10 particles as boundary particles for this simulation.
    int particlesToSend = 10;  // Number of boundary particles to process
    int boundarySize = particlesToSend;  // No need for MPI_BYTE size

    // Buffers for sending and receiving boundary data
    vector<Particle> sendLeft(particlesToSend);
    vector<Particle> sendRight(particlesToSend);
    vector<Particle> recvLeft(particlesToSend);
    vector<Particle> recvRight(particlesToSend);

    // Fill buffers with boundary particles
    copy(particles.begin(), particles.begin() + particlesToSend, sendLeft.begin()); // Left boundary
    copy(particles.end() - particlesToSend, particles.end(), sendRight.begin());    // Right boundary

    // In a serial implementation, there's no need to communicate with other processes.
    // Instead, we'll just assume that boundary particles are handled within the single process.
    // If you were simulating boundary effects, you could modify or compute the particles here.

    // In this case, we just keep these boundary particles in the list for later usage.
    // Insert the boundary particles into the main list if needed (e.g., if you want to extend the list).

    // Example: Append left and right boundary particles to the list (this is just illustrative).
    particles.insert(particles.begin(), recvLeft.begin(), recvLeft.end());
    particles.insert(particles.end(), recvRight.begin(), recvRight.end());

    // In a real scenario, you would perform additional computations on the boundary particles if needed.
}
