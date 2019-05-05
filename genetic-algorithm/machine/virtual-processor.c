/*
Created by Guillaume Laroyenne on 03/05/19.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#include "virtual-processor.h"

#define PROCESSOR_ARITHMETIC_OPERATION(left, operator, right) writeMemoryVirtualProcessor(virtualProcessor, right, \
        readMemoryVirtualProcessor(virtualProcessor, left) \
        operator readMemoryVirtualProcessor(virtualProcessor, right))


static void executeLineVirtualProcessor(virtual_processor_t *virtualProcessor, vp_line_t *line, bool *alive);

static void instructionError(vp_instruction_t instruction);

static void writeMemoryVirtualProcessor(virtual_processor_t *virtualProcessor, size_t address, vp_data_type_t value);

static vp_data_type_t readMemoryVirtualProcessor(virtual_processor_t *virtualProcessor, size_t address);

static vp_data_type_t inputVirtualProcessor(virtual_processor_t *virtualProcessor, size_t index);

static void outputVirtualProcessor(virtual_processor_t *virtualProcessor, size_t index, vp_data_type_t value);

virtual_processor_t *createVirtualProcessor(size_t input_size, size_t output_size) {

    virtual_processor_t *virtualProcessor = malloc(sizeof(virtual_processor_t));
    if (virtualProcessor == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    virtualProcessor->memory = malloc(sizeof(vp_data_type_t) * VP_MEMORY_BLOCK_SIZE);
    if (virtualProcessor->memory == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    virtualProcessor->memory_size = VP_MEMORY_BLOCK_SIZE;

    for (unsigned int i = 0; i < virtualProcessor->memory_size; i++) {
        virtualProcessor->memory[i] = INFINITY;
    }

    memset(virtualProcessor->input, 0, sizeof(int) * VP_INPUT_OUTPUT_MAX_SIZE);
    memset(virtualProcessor->output, 0, sizeof(int) * VP_INPUT_OUTPUT_MAX_SIZE);

    for (unsigned int i = 0; i < VP_INPUT_OUTPUT_MAX_SIZE; i++) {

        virtualProcessor->input[i] = -1;
        virtualProcessor->output[i] = -1;
    }

    virtualProcessor->input_size = input_size;
    virtualProcessor->output_size = output_size;


    virtualProcessor->cursor = 0;

    virtualProcessor->lines = malloc(1);
    if (virtualProcessor->lines == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    virtualProcessor->lines_size = 0;

    return virtualProcessor;
}


void freeVirtualProcessor(virtual_processor_t *virtualProcessor) {

    if (virtualProcessor != NULL) {

        for (unsigned int i = 0; i < VP_INPUT_OUTPUT_MAX_SIZE; ++i) {

            if (virtualProcessor->output[i] >= 0) {
                close(virtualProcessor->output[i]);
            }
            if (virtualProcessor->input[i] >= 0) {
                close(virtualProcessor->input[i]);
            }
        }

        free(virtualProcessor->lines);
        virtualProcessor->lines = NULL;

        free(virtualProcessor->memory);
        virtualProcessor->memory = NULL;

        free(virtualProcessor);
    }
}


pid_t executeVirtualProcessor(virtual_processor_t *virtualProcessor) {

    static const unsigned int PIPE_DUP = 2;

    int outputPipe[VP_INPUT_OUTPUT_MAX_SIZE][PIPE_DUP];
    int inputPipe[VP_INPUT_OUTPUT_MAX_SIZE][PIPE_DUP];

    for (unsigned int i = 0; i < VP_INPUT_OUTPUT_MAX_SIZE; ++i) {
        for (unsigned int j = 0; j < PIPE_DUP; ++j) {
            outputPipe[j][i] = -1;
            inputPipe[j][i] = -1;
        }
    }

    for (unsigned int i = 0; i < virtualProcessor->input_size; ++i) {
        if (pipe(inputPipe[i]) < 0) {
            perror("pipe()");
            exit(EXIT_FAILURE);
        }
    }

    for (unsigned int i = 0; i < virtualProcessor->output_size; ++i) {
        if (pipe(outputPipe[i]) < 0) {
            perror("pipe()");
            exit(EXIT_FAILURE);
        }
    }


    pid_t pid = fork();
    if (pid < 0) {
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {

        for (unsigned int i = 0; i < virtualProcessor->output_size; ++i) {
            virtualProcessor->output[i] = outputPipe[i][1];
            close(outputPipe[i][0]);
        }

        for (unsigned int i = 0; i < virtualProcessor->input_size; ++i) {
            virtualProcessor->input[i] = inputPipe[i][0];
            close(inputPipe[i][1]);
        }


        virtualProcessor->cursor = 0;

        bool alive = virtualProcessor->lines > 0;

        while (alive) {

            vp_line_t *line = &virtualProcessor->lines[virtualProcessor->cursor];

            executeLineVirtualProcessor(virtualProcessor, line, &alive);

            virtualProcessor->cursor = (virtualProcessor->cursor + 1) % virtualProcessor->lines_size;
            if (virtualProcessor->cursor < 0) {
                virtualProcessor->cursor += virtualProcessor->lines_size;
            }
        }

        freeVirtualProcessor(virtualProcessor);

        exit(EXIT_SUCCESS);

    } else {

        for (unsigned int i = 0; i < virtualProcessor->output_size; ++i) {
            virtualProcessor->output[i] = outputPipe[i][0];
            close(outputPipe[i][1]);
        }

        for (unsigned int i = 0; i < virtualProcessor->input_size; ++i) {
            virtualProcessor->input[i] = inputPipe[i][1];
            close(inputPipe[i][0]);
        }
    }

    return pid;
}

void executeLineVirtualProcessor(virtual_processor_t *virtualProcessor, vp_line_t *line, bool *alive) {

    size_t cursor = virtualProcessor->lines_size;

    vp_instruction_t instruction = line->instruction;

    vp_operand_t left = line->left;
    vp_operand_t right = line->right;

    switch (instruction) {

        case EXIT:
            if (left != 0 || right != 0) {
                instructionError(instruction);
            }
            *alive = false;
            break;

        case JMP:
            if (right + cursor < 0 || right + cursor >= virtualProcessor->lines_size) {
                instructionError(instruction);
            }
            if (readMemoryVirtualProcessor(virtualProcessor, left)) {
                virtualProcessor->cursor = cursor + right - 1;
            }
            break;

        case MULT:
            PROCESSOR_ARITHMETIC_OPERATION(left, *, right);
            break;

        case ADD:
            PROCESSOR_ARITHMETIC_OPERATION(left, +, right);
            break;

        case DIV:
            if (left == 0) {
                instructionError(instruction);
            }
            PROCESSOR_ARITHMETIC_OPERATION(left, /, right);
            break;

        case SUB:
            PROCESSOR_ARITHMETIC_OPERATION(left, -, right);
            break;

        case MOD:
            writeMemoryVirtualProcessor(virtualProcessor, right,
                                        (long long) readMemoryVirtualProcessor(virtualProcessor, right) %
                                        (unsigned long long) readMemoryVirtualProcessor(virtualProcessor, left));
            break;

        case COPY:
            writeMemoryVirtualProcessor(virtualProcessor, right, readMemoryVirtualProcessor(virtualProcessor, left));
            break;

        case LOWER:
            PROCESSOR_ARITHMETIC_OPERATION(left, <, right);
            break;


        case GREATER:
            PROCESSOR_ARITHMETIC_OPERATION(left, >, right);
            break;

        case EQUAL:
            PROCESSOR_ARITHMETIC_OPERATION(left, ==, right);
            break;

        case LET:
            if (right >= VP_MEMORY_SIZE_MAX_SIZE) {
                instructionError(instruction);
            }

            writeMemoryVirtualProcessor(virtualProcessor, right, left);
            break;

        case INPUT:
            if (left < 0 || left >= VP_INPUT_OUTPUT_MAX_SIZE || right >= VP_MEMORY_SIZE_MAX_SIZE ||
                virtualProcessor->input[left] < 0) {
                instructionError(instruction);
            }

            writeMemoryVirtualProcessor(virtualProcessor, right, inputVirtualProcessor(virtualProcessor, left));
            break;

        case OUTPUT:
            if (left < 0 || left >= VP_INPUT_OUTPUT_MAX_SIZE || virtualProcessor->output[left] < 0) {
                instructionError(instruction);
            }

            outputVirtualProcessor(virtualProcessor, left, readMemoryVirtualProcessor(virtualProcessor, right));
            break;

        default:
            instructionError(instruction);
    }
}

void instructionError(vp_instruction_t instruction) {

    switch (instruction) {

        case LET:
            fprintf(stderr, "let instruction memory over size\n");
            break;

        case JMP:
            fprintf(stderr, "jmp instruction error\n");
            break;

        default:
            fprintf(stderr, "invalid instruction : %d\n", instruction);
    }

    exit(EXIT_FAILURE);
}


void writeMemoryVirtualProcessor(virtual_processor_t *virtualProcessor, size_t address, vp_data_type_t value) {


    while (address >= virtualProcessor->memory_size) {

        size_t size = virtualProcessor->memory_size + VP_MEMORY_BLOCK_SIZE;

        virtualProcessor->memory = realloc(virtualProcessor->memory, sizeof(vp_data_type_t) * size);
        if (virtualProcessor->memory == NULL) {
            perror("realloc()");
            exit(EXIT_FAILURE);
        }

        for (size_t i = virtualProcessor->memory_size; i < size; i++) {
            virtualProcessor->memory[i] = INFINITY;
        }

        virtualProcessor->memory_size = size;
    }

    virtualProcessor->memory[address] = value;
}


vp_data_type_t readMemoryVirtualProcessor(virtual_processor_t *virtualProcessor, size_t address) {

    if (address >= virtualProcessor->memory_size) {
        fprintf(stderr, "segmentation fault\n");
        exit(EXIT_FAILURE);
    }

    vp_data_type_t value = 0;

    value = virtualProcessor->memory[address];

    if (value == INFINITY) {
        fprintf(stderr, "memory no init\n");
        exit(EXIT_FAILURE);
    }

    return value;
}


void writeVirtualProcessor(virtual_processor_t *virtualProcessor, size_t index, vp_data_type_t value) {

    if (index >= VP_INPUT_OUTPUT_MAX_SIZE || virtualProcessor->input[index] < 0) {
        fprintf(stderr, "invalid in out index\n");
        exit(EXIT_FAILURE);
    }

    ssize_t ssize = write(virtualProcessor->input[index], &value, sizeof(vp_data_type_t));
    if (ssize != sizeof(vp_data_type_t)) {
        perror("write()");
        exit(EXIT_FAILURE);
    }
}

vp_data_type_t readVirtualProcessor(virtual_processor_t *virtualProcessor, size_t index) {

    if (index >= VP_INPUT_OUTPUT_MAX_SIZE || virtualProcessor->output[index] < 0) {
        fprintf(stderr, "invalid in out index\n");
        exit(EXIT_FAILURE);
    }

    vp_data_type_t value = INFINITY;

    ssize_t ssize = read(virtualProcessor->output[index], &value, sizeof(vp_data_type_t));
    if (ssize != sizeof(vp_data_type_t)) {
        perror("read()");
        exit(EXIT_FAILURE);
    }

    return value;
}


void appendLineVirtualProcessor(virtual_processor_t *virtualProcessor, vp_instruction_t instruction, vp_operand_t left,
                                vp_operand_t right) {

    virtualProcessor->lines = realloc(virtualProcessor->lines, sizeof(vp_line_t) * (virtualProcessor->lines_size + 1));
    if (virtualProcessor->lines == NULL) {
        perror("realloc()");
        exit(EXIT_FAILURE);
    }

    vp_line_t line;
    line.instruction = instruction;
    line.right = right;
    line.left = left;

    virtualProcessor->lines[virtualProcessor->lines_size] = line;

    virtualProcessor->lines_size++;
}


vp_data_type_t inputVirtualProcessor(virtual_processor_t *virtualProcessor, size_t index) {

    vp_data_type_t value = INFINITY;

    ssize_t ssize = read(virtualProcessor->input[index], &value, sizeof(vp_data_type_t));
    if (ssize != sizeof(vp_data_type_t)) {
        perror("read()");
        exit(EXIT_FAILURE);
    }

    return value;
}

void outputVirtualProcessor(virtual_processor_t *virtualProcessor, size_t index, vp_data_type_t value) {

    ssize_t ssize = write(virtualProcessor->output[index], &value, sizeof(vp_data_type_t));
    if (ssize != sizeof(vp_data_type_t)) {
        perror("write()");
        exit(EXIT_FAILURE);
    }
}