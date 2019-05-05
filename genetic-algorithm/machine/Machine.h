//
// Created by guillaume on 05/05/19.
//

#ifndef GENETIC_ALGORITHM_MACHINE_H
#define GENETIC_ALGORITHM_MACHINE_H

#include "virtual-processor.h"

class Machine {

private:
    virtual_processor_t *processor;

    static void grim_ripper(pid_t pid1, pid_t pid2);

    unsigned long randomLine() const;

public:
    explicit Machine();

    bool isPrime(vp_data_type_t number) const;

    void addRandomInstruction();

    void removeRandomInstruction();

    void switchRandomInstruction();

    void changeRandomInstruction();

    void printMachine() const;

    virtual_processor_t *getProcessor();

    ~Machine();
};


#endif //GENETIC_ALGORITHM_MACHINE_H
