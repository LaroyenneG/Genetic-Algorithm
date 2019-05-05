//
// Created by guillaume on 05/05/19.
//

#include <thread>
#include <mutex>
#include "MachineBuilder.h"

#include "Population.h"

unsigned long MachineBuilder::fitness(const Machine &individual) const {

    std::mutex mutex;

    unsigned long value = 0;

    if (allFitness.find(&individual) == allFitness.end()) {

        allFitness.clear();

        const Genetic::Population<Machine> &pop = getPopulation();

        auto **threads = new std::thread *[pop.size()];

        for (unsigned int i = 0; i < pop.size(); i++) {

            threads[i] = new std::thread([&]() {

                double fvalue = 0;

                try {

                    for (auto n : notPrimeNumber) {
                        if (individual.isPrime(n)) {
                            fvalue++;
                        }
                    }

                    for (auto n : primeNumber) {
                        if (!individual.isPrime(n)) {
                            fvalue++;
                        }
                    }


                } catch (std::runtime_error &e) {
                    fvalue = 1844674407370955161l;
                }

                mutex.lock();

                auto it = allFitness.begin();

                allFitness.insert(it, std::pair<const Machine *, unsigned long>(&individual, fvalue));

                mutex.unlock();
            });

        }


        for (unsigned int i = 0; i < pop.size(); i++) {
            threads[i]->join();
            delete threads[i];
        }

        delete[] threads;
    }


    value = allFitness.find(&individual)->second;

    return value;
}

void MachineBuilder::mutate(Machine &individual) const {

    int type = random() % 4;

    switch (type) {

        case 0:
            individual.addRandomInstruction();
            break;

        case 1:
            individual.removeRandomInstruction();
            break;

        case 2:
            individual.switchRandomInstruction();
            break;

        case 3:
            individual.changeRandomInstruction();
            break;

        default:
            std::cerr << "invalid type " << type << std::endl;
            exit(EXIT_FAILURE);
    }
}

std::pair<Machine *, Machine *> MachineBuilder::crossing(const std::pair<Machine *, Machine *> &individuals) const {

    std::pair<Machine *, Machine *> result;

    auto *m1 = individuals.first;
    auto *m2 = individuals.second;

    auto *im1 = new Machine();
    auto *im2 = new Machine();

    for (unsigned int i = 0; i < m1->getProcessor()->lines_size && i < m2->getProcessor()->lines_size; i++) {

        appendLineVirtualProcessor(im1->getProcessor(), m1->getProcessor()->lines[i].instruction,
                                   m1->getProcessor()->lines[i].left, m1->getProcessor()->lines[i].right);
        appendLineVirtualProcessor(im1->getProcessor(), m2->getProcessor()->lines[i].instruction,
                                   m2->getProcessor()->lines[i].left, m2->getProcessor()->lines[i].right);
    }


    for (unsigned int i = 0; i < m1->getProcessor()->lines_size && i < m2->getProcessor()->lines_size; i++) {

        appendLineVirtualProcessor(im2->getProcessor(), m2->getProcessor()->lines[i].instruction,
                                   m2->getProcessor()->lines[i].left, m2->getProcessor()->lines[i].right);
        appendLineVirtualProcessor(im2->getProcessor(), m1->getProcessor()->lines[i].instruction,
                                   m1->getProcessor()->lines[i].left, m1->getProcessor()->lines[i].right);
    }

    result.first = im1;
    result.second = im2;

    return result;
}

Machine *MachineBuilder::generateIndividual() const {

    static const unsigned int MAX_LINE = 100;

    auto *machine = new Machine();

    for (unsigned int i = 0; i < MAX_LINE; i++) {

        if (random() % 2 == 0) {
            machine->addRandomInstruction();
        }
    }

    return machine;
}

MachineBuilder::MachineBuilder() {

    generatePopulation(100);

    for (unsigned int n = 0; n < 800000; n++) {

        bool prime = true;

        for (unsigned int d = 2; d <= sqrt(n); d++) {

            if (n % d == 0) {
                prime = false;
                break;
            }
        }

        if (prime) {
            primeNumber.push_back(n);
        } else {
            notPrimeNumber.push_back(n);
        }
    }
}
