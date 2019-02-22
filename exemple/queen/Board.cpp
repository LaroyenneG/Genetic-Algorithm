//
// Created by guillaume on 01/02/19.
//

#include "Board.h"

Board::Board(unsigned int _size) : len(_size), table(new short[_size]) {

    for (int i = 0; i < len; ++i) {
        table[i] = -1;
    }
}

Board::~Board() {
    delete[] table;
}

short &Board::operator[](unsigned int n) const {
    return table[n];
}

unsigned int Board::size() const {
    return len;
}

std::ostream &operator<<(std::ostream &stream, const Board &board) {

    stream << '[';

    for (int i = 0; i < board.size(); ++i) {
        stream << board[i];
        if (i + 1 < board.size()) {
            stream << ' ';
        }
    }

    stream << ']';

    return stream;
}
