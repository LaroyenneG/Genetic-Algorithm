//
// Created by guillaume on 28/01/19.
//

#include "Packet.h"

Packet::Packet(unsigned int _len) : len(_len), table(new bool[_len]) {
    for (int i = 0; i < len; i++) {
        table[i] = false;
    }
}

Packet::~Packet() {
    delete[] table;
}

bool &Packet::operator[](unsigned int n) const {

    if (n >= len) {
        throw "invalid index";
    }

    return table[n];
}

unsigned int Packet::multValue() const {

    unsigned int value = 1;

    for (int i = 0; i < len; ++i) {
        if (!table[i]) {
            value *= i + 1;
        }
    }

    return value;
}

unsigned int Packet::addValue() const {

    unsigned int value = 0;

    for (int i = 0; i < len; ++i) {
        if (table[i]) {
            value += i + 1;
        }
    }

    return value;
}

unsigned int Packet::size() const {
    return len;
}

std::ostream &operator<<(std::ostream &stream, const Packet &packet) {

    stream << '[';

    for (int i = 0; i < packet.size(); ++i) {
        stream << packet[i];
        if (i + 1 < packet.size()) {
            stream << ' ';
        }
    }

    stream << ']';

    return stream;
}
