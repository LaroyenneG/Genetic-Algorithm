//
// Created by guillaume on 05/05/19.
//

#include <iostream>
#include "MachineBuilder.h"

int main(int argc, char **argv) {


    MachineBuilder machineBuilder;

    const Machine *solution = machineBuilder.process();

    solution->printMachine();

    return EXIT_SUCCESS;
}