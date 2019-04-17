//
// Created by Guillaume Laroyenne on 24/02/19.
//

#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

#include "FitnessEvaluatorInterface.h"

class Particle {

private:
    unsigned int dimension;
    double *position;
    double *bestPosition;
    double *speed;
    const FitnessEvaluatorInterface *fitnessEvaluatorInterface;

    void checkArrayIndex(unsigned int dim) const;

public:
    explicit Particle(unsigned int _dimension, const FitnessEvaluatorInterface *_fitnessEvaluatorInterface);

    double getPosition(unsigned int dim) const;

    void setPosition(unsigned int dim, double value);

    double getBestPosition(unsigned int dim) const;

    void setBestPosition(unsigned int dim, double value);

    double getSpeed(unsigned int dim) const;

    void setSpeed(unsigned int dim, double value);

    double bestFitness() const;

    double fitness() const;

    ~Particle();

    double getDimension() const;
};

#endif //PSO_PARTICLE_H
