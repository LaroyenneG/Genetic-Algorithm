//
// Created by guillaume on 28/01/19.
//


#include <iostream>
#include "card/CardDispatcher.h"
#include "queen/QueenSetter.h"

template<typename I>
void launch(Nursery<I> &nursery) {

    clock_t t1, t2;

    t1 = clock();

    const I *solution = nursery.process();


    if (solution != nullptr) {

        t2 = clock();

        float time = (float) (t2 - t1) / CLOCKS_PER_SEC;;

        std::cout << "Solution : " << *solution << std::endl;

        std::cout << "Time : " << time << " s" << std::endl;

        std::cout << "Iterations : " << nursery.getIteration() << std::endl;
    }
}

void cardDemo() {

    CardDispatcher cardDispatcher;

    launch(cardDispatcher);
}

void queenDemo() {
    QueenSetter queenSetter;

    launch(queenSetter);
}


int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "Usage : Nursery" << std::endl;
        exit(EXIT_FAILURE);
    }

    srandom(static_cast<unsigned int>(time(nullptr)));

    cardDemo();
    queenDemo();


    return EXIT_SUCCESS;
}