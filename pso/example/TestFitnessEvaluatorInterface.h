//
// Created by Guillaume Laroyenne on 17/04/19.
//

#ifndef PSO_TESTFITNESSEVALUATORINTERFACE_H
#define PSO_TESTFITNESSEVALUATORINTERFACE_H


#include "../src/FitnessEvaluatorInterface.h"

class TestFitnessEvaluatorInterface : public FitnessEvaluatorInterface {

public:
    double computeFitness(double *position, unsigned int dimension) const override;

};


#endif //PSO_TESTFITNESSEVALUATORINTERFACE_H
