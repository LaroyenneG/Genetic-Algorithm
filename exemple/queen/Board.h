//
// Created by guillaume on 01/02/19.
//

#ifndef GENETIC_ALGORITHM_BOARD_H
#define GENETIC_ALGORITHM_BOARD_H


#include <ostream>

class Board {

private:
    short *table;
    unsigned int len;

public:
    explicit Board(unsigned int _size);

    ~Board();

    unsigned int size() const;

    short &operator[](unsigned int n) const;

    friend std::ostream &operator<<(std::ostream &os, const Board &board);
};


#endif //GENETIC_ALGORITHM_BOARD_H
