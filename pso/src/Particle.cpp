//
// Created by Guillaume Laroyenne on 24/02/19.
//

#include <string>
#include <math.h>
#include "Particle.h"

Particle::Particle(unsigned int _dimension)
        : dimension(_dimension), position(new double[_dimension]),
          bestPosition(new double[_dimension]), speed(new double[_dimension]) {

    for (int i = 0; i < dimension; ++i) {
        position[i] = 0;
        bestPosition[i] = 0;
        speed[i] = 0;
    }
}

Particle::~Particle() {
    delete[] position;
    delete[] bestPosition;
    delete[] speed;
}

double Particle::getPosition(unsigned int dim) const {

    checkArrayIndex(dim);

    return position[dim];
}

double Particle::getBestPosition(unsigned int dim) const {

    checkArrayIndex(dim);

    return bestPosition[dim];
}

double Particle::getSpeed(unsigned int dim) const {

    checkArrayIndex(dim);

    return speed[dim];
}


void Particle::checkArrayIndex(unsigned int dim) const {
    if (dim >= dimension) {
        throw std::string(" index out of bounds");
    }
}

void Particle::setPosition(unsigned int dim, double value) {

    checkArrayIndex(dim);

    position[dim] = value;
}

void Particle::setBestPosition(unsigned int dim, double value) {

    checkArrayIndex(dim);

    bestPosition[dim] = value;
}

void Particle::setSpeed(unsigned int dim, double value) {

    checkArrayIndex(dim);

    speed[dim] = value;
}

double Particle::getDimension() const {
    return dimension;
}

double Particle::bestFitness() const {
    return 0;
}

double Particle::fitness() const {
    return 0;
}

double Particle::computeFitness(double *table, unsigned int size) {

    double result = 10.0 * size;

    for (unsigned int d = 0; d < size; ++d) {

        double xi = table[d];

        result += xi * xi - 10.0 * cos(2.0 * M_PI * xi);
    }

    return result;
}
