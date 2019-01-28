//
// Created by guillaume on 28/01/19.
//

#ifndef GENETIC_ALGORITHM_NURSERY_H
#define GENETIC_ALGORITHM_NURSERY_H

#define DEFAULT_MUTATION_PROBABILITY 0.1f
#define DEFAULT_CROSSING_PROBABILITY 0.3f
#define DEFAULT_MAX_ITERATION 10000000

#include <random>
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

        static bool probability(float p);

    public:
        Nursery();

        Nursery(float _mutationProbability, float _crossingProbability, unsigned long _maxIteration);

        ~Nursery();

        const I *process();

        const I *findBestIndividual();

        void appendIndividual(I *individual);

        unsigned long getIteration() const;

    protected:
        virtual unsigned long fitness(const I &individual) const = 0;

        virtual void mutate(const I &individual) const = 0;

        virtual std::pair<I *, I *> crossing(const std::pair<I *, I *> &individuals) const = 0;
    };

    template<typename I>
    Nursery<I>::Nursery()
            : Nursery(DEFAULT_MUTATION_PROBABILITY, DEFAULT_CROSSING_PROBABILITY, DEFAULT_MAX_ITERATION) {
    }

    template<typename I>
    Nursery<I>::Nursery(float _mutationProbability, float _crossingProbability, unsigned long _maxIteration)
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
        population += nPopulation; // temperately
    }

    template<typename I>
    const I *Nursery<I>::process() {

        iteration = 0;

        while (bestFitness() > 0 && iteration < maxIteration) {

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

        for (int i = 0; i < 5; ++i) {
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
}


#endif //GENETIC_ALGORITHM_NURSERY_H
