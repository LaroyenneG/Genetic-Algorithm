//
// Created by Guillaume Laroyenne on 24/02/19.
//

#ifndef PSO_PARTICLESWARMOPTIMIZATION_H
#define PSO_PARTICLESWARMOPTIMIZATION_H

#include "Particle.h"

class ParticleSwarmOptimization {

private:
    unsigned int swarmSize;
    unsigned int nbNeighbors;
    unsigned int nbIteration;

    double deltaSpeed[2]{};

    double fitnessDesired;

    unsigned int dimensionSpace;

    double bounds[2]{};

    double coefficients[3]{};

    Particle **swarm;

    void initializeSwarm();

    Particle *getBestNeighbor(unsigned int index) const;

    Particle *getBestParticle() const;

    double boundedSpeed(double value) const;

    double boundedPosition(double value) const;

public:
    ParticleSwarmOptimization(unsigned int _dimensionSpace, unsigned int _nbParticle, unsigned int _nbNeighbors,
                              unsigned int _nbIteration, double _deltaSpeedMin, double _deltaSpeedMax,
                              double _fitnessValue, double _minBound, double _maxBound, double _indCoefficient,
                              double _colCoefficient, double _inertiaCoefficient);

    ~ParticleSwarmOptimization();

    Particle *processing();

    static double randDoubleBetween(double min, double max);
};


#endif //PSO_PARTICLESWARMOPTIMIZATION_H
