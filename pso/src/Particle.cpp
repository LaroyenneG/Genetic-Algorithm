//
// Created by Guillaume Laroyenne on 24/02/19.
//



#include <string>
#include <stdexcept>
#include "Particle.h"

Particle::Particle(unsigned int _dimension, const FitnessEvaluatorInterface *_fitnessEvaluatorInterface)
        : dimension(_dimension), position(new double[_dimension]), bestPosition(new double[_dimension]),
          speed(new double[_dimension]), fitnessEvaluatorInterface(_fitnessEvaluatorInterface) {

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
        throw std::out_of_range("index out of bounds");
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
    return fitnessEvaluatorInterface->computeFitness(bestPosition, dimension);
}

double Particle::fitness() const {
    return fitnessEvaluatorInterface->computeFitness(position, dimension);
}

