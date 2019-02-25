//
// Created by Guillaume Laroyene on 24/02/19.
//

#include <iostream>
#include "../src/ParticleSwarmOptimization.h"

int main(int argc, char **argv) {

    srandom(static_cast<unsigned int>(time(nullptr)));

    ParticleSwarmOptimization pso(4, 40, 4, 100000, -4.0, 4.0, 0, -5.12, 5.12, 2, 2, 0.0);

    Particle *particle = pso.processing();

    if (particle != nullptr) {
        for (unsigned int d = 0; d < particle->getDimension(); ++d) {
            std::cout << particle->getBestPosition(d) << ' ';
        }
    }

    return EXIT_SUCCESS;
}
