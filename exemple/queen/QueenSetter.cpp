//
// Created by guillaume on 01/02/19.
//

#include <list>

#include "QueenSetter.h"

QueenSetter::QueenSetter() {
    generatePopulation(4);
}


unsigned long QueenSetter::fitness(const Board &individual) const {

    unsigned long n = 0;

    for (int i = 0; i < individual.size() - 1; ++i) {
        if (abs(individual[i] - individual[i + 1]) == 1) {
            n++;
        }
    }

    return n;
}

void QueenSetter::mutate(Board &individual) const {

    unsigned int index1;
    unsigned int index2;

    do {
        index1 = ((unsigned int) random()) % individual.size();
        index2 = ((unsigned int) random()) % individual.size();
    } while (index1 == index2);

    auto tmp = individual[index1];

    individual[index2] = individual[index1];

    individual[index1] = tmp;
}

std::pair<Board *, Board *> QueenSetter::crossing(const std::pair<Board *, Board *> &individuals) const {


    if (individuals.second->size() != individuals.first->size()) {
        throw std::string("invalid size");
    }

    unsigned int size = individuals.first->size();

    std::pair<Board *, Board *> pair(new Board(size), new Board(size));

    unsigned int index = ((unsigned int) random() % size);


    Board &b1 = *individuals.first;
    Board &b2 = *individuals.second;

    Board &nb1 = *pair.first;
    Board &nb2 = *pair.second;


    for (unsigned int i = 0; i < index; ++i) {
        nb1[i] = b1[i];
    }
    for (unsigned int i = 0; i < index; ++i) {
        nb2[i] = b2[i];
    }

    for (unsigned int j = index; j < size; ++j) {
        nb1[j] = get_next(b2, nb1, index);
    }

    for (unsigned int j = index; j < size; ++j) {
        nb2[j] = get_next(b1, nb2, index);
    }


    return pair;
}

Board *QueenSetter::generateIndividual() const {

    auto *board = new Board(4);

    std::vector<unsigned short> values;

    for (unsigned short i = 0; i < board->size(); ++i) {
        values.push_back(i);
    }

    for (unsigned int i = 0; i < board->size(); ++i) {

        auto index = static_cast<unsigned int>(((unsigned int) random()) % values.size());

        board->operator[](i) = values[index];

        values.erase(values.begin() + index);
    }

    return board;
}

short QueenSetter::get_next(const Board &source, const Board &target, int index) {

    short value = -1;

    for (int i = 0; i < target.size(); ++i) {

        short n = source[(index + i) % source.size()];

        bool find = false;

        for (int j = 0; j < target.size(); ++j) {
            if (target[j] == n) {
                find = true;
                break;
            }
        }

        if (!find) {
            value = n;
            break;
        }
    }

    return value;
}


