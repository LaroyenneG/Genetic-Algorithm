//
// Created by Guillaume Laroyenne on 17/04/19.
//

#ifndef PSO_FITNESSEVALUATORINTERFACE_H
#define PSO_FITNESSEVALUATORINTERFACE_H

class Particle;

class FitnessEvaluatorInterface {

public:
    virtual double computeFitness(double *position, unsigned int dimension) const = 0;

};


#endif //PSO_FITNESSEVALUATORINTERFACE_H
