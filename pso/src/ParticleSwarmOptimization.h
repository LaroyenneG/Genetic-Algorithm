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

    double deltaSpeed[2];

    double fitnessValue;

    unsigned int dimensionSpace;

    double bounds[2];

    double coefficients[2];

    Particle **swarm;

    double computeFitness(const Particle *particle) const;

    void initializeSwarm();

    Particle *getBestNeighbor(unsigned int index) const;

    double boundedSpeed(double value) const;

    double boundedPosition(double value) const;

public:
    ParticleSwarmOptimization(unsigned int _dimensionSpace, unsigned int _nbParticle, unsigned int _nbNeighbors,
                              unsigned int _nbIteration, double _deltaSpeedMin, double _deltaSpeedMax,
                              double _fitnessValue, double _minBound, double _maxBound, double _indCoefficients,
                              double _colCoefficients);

    ~ParticleSwarmOptimization();

    Particle *processing();

    static double randDoubleBetween(double min, double max);
};


#endif //PSO_PARTICLESWARMOPTIMIZATION_H
