//
// Created by guillaume on 28/01/19.
//

#include "CardDispatcher.h"

CardDispatcher::CardDispatcher() {
    generatePopulation(70);
}

unsigned long CardDispatcher::fitness(const Packet &individual) const {
    return static_cast<unsigned long>(abs(36 - individual.addValue()) + abs(360 - individual.multValue()));
}

void CardDispatcher::mutate(Packet &individual) const {

    if (individual.size() > 0) {

        unsigned int index = ((unsigned int) random()) % individual.size();

        individual[index] = !individual[index];
    }
}

std::pair<Packet *, Packet *> CardDispatcher::crossing(const std::pair<Packet *, Packet *> &individuals) const {

    if (individuals.first->size() != individuals.second->size()) {
        throw "invalid packet size";
    }

    unsigned int size = individuals.first->size();

    std::pair<Packet *, Packet *> newPair(new Packet(size), new Packet(size));

    Packet &p1 = *individuals.first;
    Packet &p2 = *individuals.second;

    Packet &np1 = *newPair.first;
    Packet &np2 = *newPair.second;

    unsigned int cursor = ((unsigned int) random()) % size;

    for (int i = 0; i < cursor; ++i) {
        np1[i] = p1[i];
    }

    for (int j = cursor; j < size; ++j) {
        np1[j] = p2[j];
    }

    for (int i = 0; i < cursor; ++i) {
        np2[i] = p2[i];
    }

    for (int j = cursor; j < size; ++j) {
        np2[j] = p1[j];
    }

    return newPair;
}

Packet *CardDispatcher::generateIndividual() const {

    auto *packet = new Packet(10);

    for (int j = 0; j < packet->size(); ++j) {
        mutate(*packet);
    }

    return packet;
}


