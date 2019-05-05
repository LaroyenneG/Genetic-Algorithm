//
// Created by guillaume on 28/01/19.
//

#ifndef GENETIC_ALGORITHM_NURSERY_H
#define GENETIC_ALGORITHM_NURSERY_H

#define DEFAULT_MUTATION_PROBABILITY 0.1
#define DEFAULT_CROSSING_PROBABILITY 0.3
#define DEFAULT_MAX_ITERATION 10000000

#include <random>
#include <cassert>
#include <iostream>
#include "Population.h"

namespace Genetic {

    template<typename I>
    class Nursery {

    private:
        Population<I> population;

        const float mutationProbability;
        const float crossingProbability;
        const unsigned long maxIteration;

        unsigned long iteration;

        unsigned long bestFitness() const;

        void introduceNewGeneration(const Population<I> &nPopulation);

        void appendIndividual(I *individual);

    public:
        Nursery();

        Nursery(float _mutationProbability, float _crossingProbability,
                unsigned long _maxIteration);

        ~Nursery();

        void generatePopulation(unsigned int size);

        const I *process();

        const I *findBestIndividual();

        unsigned long getIteration() const;

        static bool probability(float p);

    protected:
        const Population<I> &getPopulation() const;

        virtual unsigned long fitness(const I &individual) const = 0;

        virtual void mutate(I &individual) const = 0;

        virtual std::pair<I *, I *> crossing(const std::pair<I *, I *> &individuals) const = 0;

        virtual I *generateIndividual() const = 0;
    };

    template<typename I>
    Nursery<I>::Nursery()
            : Nursery(DEFAULT_MUTATION_PROBABILITY, DEFAULT_CROSSING_PROBABILITY,
                      DEFAULT_MAX_ITERATION) {
    }

    template<typename I>
    Nursery<I>::Nursery(float _mutationProbability, float _crossingProbability,
                        unsigned long _maxIteration)
            : mutationProbability(_mutationProbability), crossingProbability(_crossingProbability),
              maxIteration(_maxIteration), iteration(0) {
    }

    template<typename I>
    unsigned long Nursery<I>::bestFitness() const {

        unsigned long best = 0;

        for (int i = 0; i < population.size(); ++i) {

            unsigned long value = fitness(*population[i]);

            if (best >= value || i == 0) {
                best = value;
            }
        }

        return best;
    }

    template<typename I>
    void Nursery<I>::introduceNewGeneration(const Population<I> &nPopulation) {

        auto popSize = population.size();

        Population allIndividual = population + nPopulation;

        population.clear();

        while (population.size() < popSize && !allIndividual.empty()) {

            I *individual = nullptr;
            unsigned long bestValue = 0;

            for (int i = 0; i < allIndividual.size(); i++) {

                auto value = fitness(*allIndividual[i]);

                if (i == 0 || value <= bestValue) {
                    bestValue = value;
                    individual = allIndividual[i];
                }

                if (probability(0.3)) {
                    break;
                }
            }

            population += individual;
            allIndividual -= individual;
        }

        allIndividual.deleteContents();
    }

    template<typename I>
    const I *Nursery<I>::process() {

        iteration = 0;

        while (bestFitness() > 0 && iteration < maxIteration) {

            std::cout << "Iteration : " << iteration << std::endl;

            Population<I> newPopulation;

            for (int i = 0; i < population.size() / 2; ++i) {

                std::pair<I *, I *> individualPair = population.select();

                if (probability(crossingProbability)) {
                    individualPair = crossing(individualPair);
                }

                if (probability(mutationProbability)) {
                    mutate(*individualPair.first);
                }

                if (probability(mutationProbability)) {
                    mutate(*individualPair.second);
                }

                newPopulation += individualPair;
            }

            introduceNewGeneration(newPopulation);

            iteration++;
        }

        return findBestIndividual();
    }

    template<typename I>
    const I *Nursery<I>::findBestIndividual() {

        I *best = nullptr;

        for (int i = 0; i < population.size(); ++i) {

            if (i == 0) {
                best = population[i];
            } else if (fitness(*best) > fitness(*population[i])) {
                best = population[i];
            }
        }

        return best;
    }

    template<typename I>
    bool Nursery<I>::probability(float p) {

        double randNumber = 0;

        for (int i = 1; i < 6; ++i) {
            randNumber += ((unsigned long) random() % 10) / pow(10, i);
        }

        return randNumber <= p;
    }

    template<typename I>
    void Nursery<I>::appendIndividual(I *individual) {
        population.addIndividual(individual);
    }

    template<typename I>
    Nursery<I>::~Nursery() {
        population.deleteContents();
    }

    template<typename I>
    unsigned long Nursery<I>::getIteration() const {
        return iteration;
    }

    template<typename I>
    void Nursery<I>::generatePopulation(unsigned int size) {
        for (int i = 0; i < size; ++i) {
            appendIndividual(generateIndividual());
        }
    }

    template<typename I>
    const Population<I> &Nursery<I>::getPopulation() const {
        return population;
    }
}


#endif //GENETIC_ALGORITHM_NURSERY_H
