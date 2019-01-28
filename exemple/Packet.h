//
// Created by guillaume on 28/01/19.
//

#ifndef GENETIC_ALGORITHM_PACKET_H
#define GENETIC_ALGORITHM_PACKET_H

#include <iostream>

class Packet {

private:
    bool *table;
    unsigned int len;

public:
    Packet(unsigned int _len);

    ~Packet();

    unsigned int size() const;

    unsigned int multValue() const;

    unsigned int addValue() const;

    bool &operator[](unsigned int n) const;

    friend std::ostream &operator<<(std::ostream &, const Packet &packet);
};


#endif //GENETIC_ALGORITHM_PACKET_H
