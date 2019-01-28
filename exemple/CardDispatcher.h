//
// Created by guillaume on 28/01/19.
//

#ifndef GENETIC_ALGORITHM_CARDDISPATCHER_H
#define GENETIC_ALGORITHM_CARDDISPATCHER_H


#include "../src/Nursery.h"
#include "Packet.h"

using namespace Genetic;

class CardDispatcher : public Nursery<Packet> {

public:
    CardDispatcher(unsigned int popSize);

protected:
    unsigned long fitness(const Packet &individual) const override;

    void mutate(const Packet &individual) const override;

    std::pair<Packet *, Packet *> crossing(const std::pair<Packet *, Packet *> &individuals) const override;

};


#endif //GENETIC_ALGORITHM_CARDDISPATCHER_H
