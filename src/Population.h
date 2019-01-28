//
// Created by guillaume on 28/01/19.
//

#ifndef GENETIC_ALGORITHM_POPULATION_H
#define GENETIC_ALGORITHM_POPULATION_H

#include <vector>
#include <random>

namespace Genetic {

    template<typename I>
    class Population {

    private:
        std::vector<I *> individuals;

        I *selectRandomIndividual() const;

    public:
        Population();

        Population(const Population &population);

        Population(const std::pair<I *, I *> &pair);

        ~Population();

        void removeIndividual(const I *individual);

        void addIndividual(I *nIndividual);

        void addPopulation(const Population<I> &population);

        void removePopulation(const Population<I> &population);

        unsigned long size() const;

        std::pair<I *, I *> select() const;

        void clear();

        void deleteContents();

        Population<I> operator+(const Population<I> &population);

        Population<I> &operator+=(const Population<I> &population);

        Population<I> operator-(const Population<I> &population);

        Population<I> &operator-=(const Population<I> &population);

        Population<I> &operator=(const Population<I> &population);

        auto &operator[](unsigned long id) const;
    };


    template<typename I>
    Population<I>::Population() = default;

    template<typename I>
    Population<I>::Population(const std::pair<I *, I *> &pair) {
        addIndividual(pair.first);
        addIndividual(pair.second);
    }

    template<typename I>
    Population<I>::Population(const Population &population) {

        for (auto item : population.individuals) {
            individuals.push_back(item);
        }
    }

    template<typename I>
    void Population<I>::addIndividual(I *nIndividual) {

        bool contain = false;

        for (auto individual : individuals) {
            if (nIndividual == individual) {
                contain = true;
                break;
            }
        }

        if (!contain) {
            individuals.push_back(nIndividual);
        }
    }

    template<typename I>
    void Population<I>::addPopulation(const Population<I> &population) {

        for (auto individual : population.individuals) {
            addIndividual(individual);
        }
    }

    template<typename I>
    void Population<I>::removeIndividual(const I *individual) {

        for (auto it = individuals.begin(); it != individuals.end(); it++) {
            if (*it == individual) {
                individuals.erase(it);
                break;
            }
        }
    }

    template<typename I>
    void Population<I>::removePopulation(const Population<I> &population) {

        for (auto individual : population.individuals) {
            removeIndividual(individual);
        }
    }

    template<typename I>
    unsigned long Population<I>::size() const {
        return individuals.size();
    }


    template<typename I>
    I *Population<I>::selectRandomIndividual() const {

        I *individual = nullptr;

        if (individuals.size() > 0) {

            auto randIndex = ((unsigned long) random()) % individuals.size();

            individual = individuals[randIndex];
        }

        return individual;
    }

    template<typename I>
    std::pair<I *, I *> Population<I>::select() const {

        return std::pair<I *, I *>(selectRandomIndividual(), selectRandomIndividual());
    }

    template<typename I>
    void Population<I>::clear() {
        individuals.clear();
    }

    template<typename I>
    void Population<I>::deleteContents() {

        for (auto item : individuals) {
            delete item;
        }

        clear();
    }

    template<typename I>
    Population<I>::~Population() = default;

    template<typename I>
    Population<I> Population<I>::operator+(const Population<I> &population) {

        Population result(*this);

        result.addPopulation(population);

        return *result;
    }

    template<typename I>
    Population<I> Population<I>::operator-(const Population<I> &population) {

        Population result(*this);

        result.removePopulation(population);

        return result;
    }

    template<typename I>
    Population<I> &Population<I>::operator=(const Population<I> &population) {

        if (&population != this) {

            individuals.clear();

            for (auto &item : population.individuals) {
                individuals.push_back(item);
            }
        }

        return *this;
    }

    template<typename I>
    auto &Population<I>::operator[](unsigned long id) const {
        return individuals[id];
    }

    template<typename I>
    Population<I> &Population<I>::operator+=(const Population<I> &population) {

        addPopulation(population);

        return *this;
    }

    template<typename I>
    Population<I> &Population<I>::operator-=(const Population<I> &population) {

        removePopulation(population);

        return *this;
    }
}


#endif //GENETIC_ALGORITHM_POPULATION_H
