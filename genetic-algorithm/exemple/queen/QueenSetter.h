//
// Created by guillaume on 01/02/19.
//

#ifndef GENETIC_ALGORITHM_QUEENSETTER_H
#define GENETIC_ALGORITHM_QUEENSETTER_H

#include "Nursery.h"
#include "Board.h"

using namespace Genetic;

class QueenSetter : public Nursery<Board> {

public:
    QueenSetter();

    unsigned long fitness(const Board &individual) const override;

    void mutate(Board &individual) const override;

    std::pair<Board *, Board *> crossing(const std::pair<Board *, Board *> &individuals) const override;

    Board *generateIndividual() const override;

private:
    static short get_next(const Board &source, const Board &target, int index);
};


#endif //GENETIC_ALGORITHM_QUEENSETTER_H
