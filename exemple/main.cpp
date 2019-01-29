//
// Created by guillaume on 28/01/19.
//


#include <iostream>
#include "CardDispatcher.h"

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "Usage : Nursery" << std::endl;
        exit(EXIT_FAILURE);
    }

    clock_t t1, t2;

    t1 = clock();

    CardDispatcher cardDispatcher;

    auto packet = cardDispatcher.process();

    if (packet != nullptr) {

        t2 = clock();

        float time = (float) (t2 - t1) / CLOCKS_PER_SEC;;

        std::cout << "Solution : " << *packet << std::endl;

        std::cout << "Time : " << time << " s" << std::endl;

        std::cout << "Iterations : " << cardDispatcher.getIteration() << std::endl;
    }

    return EXIT_SUCCESS;
}