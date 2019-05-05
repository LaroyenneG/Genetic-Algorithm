//
// Created by guillaume on 05/05/19.
//

#include <iostream>
#include "MachineBuilder.h"

int main(int argc, char **argv) {

    srandom(static_cast<unsigned int>(time(nullptr)));

    MachineBuilder machineBuilder;

    const Machine *solution = machineBuilder.process();

    solution->printMachine();

    return EXIT_SUCCESS;
}