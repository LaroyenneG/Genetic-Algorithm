//
// Created by Guillaume Laroyenne on 17/04/19.
//

#define _USE_MATH_DEFINES

#include <math.h>
#include "TestFitnessEvaluatorInterface.h"

double TestFitnessEvaluatorInterface::computeFitness(double *position, unsigned int dimension) const {

    double result = 10.0 * dimension;

    for (unsigned int d = 0; d < dimension; ++d) {

        double xi = position[d];

        result += xi * xi - 10.0 * cos(2.0 * M_PI * xi);
    }

    return result;
}
