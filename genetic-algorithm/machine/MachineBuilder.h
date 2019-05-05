//
// Created by guillaume on 05/05/19.
//

#ifndef GENETIC_ALGORITHM_MACHINEBUILDER_H
#define GENETIC_ALGORITHM_MACHINEBUILDER_H

#include <map>

#include "Nursery.h"
#include "Machine.h"

class MachineBuilder : public Genetic::Nursery<Machine> {

private:
    std::vector<long double> primeNumber;
    std::vector<long double> notPrimeNumber;

    mutable std::map<const Machine *, unsigned long> allFitness;

public:
    explicit MachineBuilder();

    unsigned long fitness(const Machine &individual) const override;

    void mutate(Machine &individual) const override;

    std::pair<Machine *, Machine *> crossing(const std::pair<Machine *, Machine *> &individuals) const override;

    Machine *generateIndividual() const override;
};


#endif //GENETIC_ALGORITHM_MACHINEBUILDER_H
