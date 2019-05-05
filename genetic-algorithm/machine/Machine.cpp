//
// Created by guillaume on 05/05/19.
//

#include <iostream>
#include <wait.h>
#include <thread>
#include <zconf.h>
#include "Machine.h"

Machine::Machine() : processor(createVirtualProcessor(1, 1)) {

}

Machine::~Machine() {
    freeVirtualProcessor(processor);
}

bool Machine::isPrime(vp_data_type_t number) const {

    static const int PRIME_EXIT = 30;
    static const int NOT_PRIME_EXIT = 34;

    pid_t pid = executeVirtualProcessor(processor);

    pid_t ipid = fork();
    if (ipid < 0) {
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    if (ipid == 0) {

        writeVirtualProcessor(processor, 0, number);

        vp_data_type_t result = readVirtualProcessor(processor, 0);

        if (result == 0) {
            exit(PRIME_EXIT);
        } else {
            exit(NOT_PRIME_EXIT);
        }
    }

    std::thread threadKiller(grim_ripper, pid, ipid);

    threadKiller.join();


    int istatus = -1;
    waitpid(ipid, &istatus, 0);

    int status = -1;
    waitpid(pid, &status, 0);


    if (!WIFEXITED(status) || !WIFEXITED(istatus) || istatus == EXIT_FAILURE || status == EXIT_FAILURE) {
        throw std::runtime_error("error status");
    }

    istatus = WEXITSTATUS(istatus);
    status = WEXITSTATUS(status);

    return istatus == PRIME_EXIT;
}

void Machine::grim_ripper(pid_t pid1, pid_t pid2) {

    sleep(1);

    kill(pid1, 9);
    kill(pid2, 9);
}

void Machine::addRandomInstruction() {


    if (random() % 1999 == 0) {
        appendLineVirtualProcessor(processor, EXIT, 0, 0);
    } else if (random() % 1999) {
        appendLineVirtualProcessor(processor, INPUT, 0, random() % VP_MEMORY_SIZE_MAX_SIZE);
    } else if (random() % 1999) {
        appendLineVirtualProcessor(processor, OUTPUT, 0, random() % VP_MEMORY_SIZE_MAX_SIZE);
    } else {

        auto instruction = static_cast<vp_instruction_t>(random() % 13);

        vp_operand_t operand1 = random();
        vp_operand_t operand2 = random();

        appendLineVirtualProcessor(processor, instruction, operand1, operand2);
    }
}

void Machine::removeRandomInstruction() {

    if (processor->lines_size > 0) {

        unsigned long index = randomLine();


        for (unsigned long i = index; i < processor->lines_size - 1; i++) {
            processor->lines[i] = processor->lines[i + 1];
        }

        processor->lines_size--;
    }
}

void Machine::switchRandomInstruction() {

    if (processor->lines_size >= 2) {

        unsigned long index1 = randomLine();
        unsigned long index2 = randomLine();

        vp_line_t tmp = processor->lines[index1];

        processor->lines[index1] = processor->lines[index2];
        processor->lines[index2] = tmp;
    }
}

void Machine::printMachine() const {

    for (unsigned long i = 0; i < processor->lines_size; i++) {
        std::cout << processor->lines[i].instruction << '\t' << processor->lines[i].left << '\t'
                  << processor->lines[i].right << std::endl;
    }
}

void Machine::changeRandomInstruction() {

    if (processor->lines_size > 0) {

        unsigned long index = randomLine();

        processor->lines[index].left = random();
        processor->lines[index].right = random();
    }
}

unsigned long Machine::randomLine() const {

    long long index = random() % processor->lines_size;
    if (index < 0) {
        index += processor->lines_size;
    }

    return index;
}

virtual_processor_t *Machine::getProcessor() {
    return processor;
}
