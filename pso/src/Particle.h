//
// Created by Guillaume Laroyenne on 24/02/19.
//

#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

class Particle {

private:
    unsigned int dimension;
    double *position;
    double *bestPosition;
    double *speed;
    double fitness;

    void checkArrayIndex(unsigned int dim) const;

public:
    explicit Particle(unsigned int _dimension);

    double getPosition(unsigned int dim) const;

    void setPosition(unsigned int dim, double value);

    double getBestPosition(unsigned int dim) const;

    void setBestPosition(unsigned int dim, double value);

    double getSpeed(unsigned int dim) const;

    void setSpeed(unsigned int dim, double value);

    double getFitness() const;

    void setFitness(double _fitness);

    ~Particle();

    double getDimension() const;
};

#endif //PSO_PARTICLE_H
