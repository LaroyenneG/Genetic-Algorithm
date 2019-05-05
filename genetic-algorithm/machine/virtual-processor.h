/*
Created by Guillaume Laroyenne on 03/05/19.
*/

#ifndef VIRTUALPROCESSOR_VIRTUAL_PROCESSOR_H
#define VIRTUALPROCESSOR_VIRTUAL_PROCESSOR_H

#include <stdbool.h>

#define VP_INPUT_OUTPUT_MAX_SIZE 10
#define VP_MEMORY_BLOCK_SIZE 10
#define VP_MEMORY_SIZE_MAX_SIZE 100000

#ifdef __cplusplus
extern "C" {
#endif


typedef long double vp_data_type_t;
typedef long long vp_operand_t;

typedef enum {
    ADD = 0,
    MULT = 1,
    DIV,
    COPY,
    SUB,
    MOD,
    LET,
    JMP,
    EXIT,
    GREATER,
    LOWER,
    EQUAL,
    INPUT,
    OUTPUT
} vp_instruction_t;

typedef struct {
    vp_instruction_t instruction;
    vp_operand_t right;
    vp_operand_t left;
} vp_line_t;

typedef struct {
    int input[VP_INPUT_OUTPUT_MAX_SIZE];
    int output[VP_INPUT_OUTPUT_MAX_SIZE];
    vp_data_type_t *memory;
    vp_line_t *lines;
    size_t input_size;
    size_t output_size;
    size_t memory_size;
    size_t cursor;
    size_t lines_size;
} virtual_processor_t;


virtual_processor_t *createVirtualProcessor(size_t input_size, size_t output_size);

void freeVirtualProcessor(virtual_processor_t *virtualProcessor);

pid_t executeVirtualProcessor(virtual_processor_t *virtualProcessor);

void writeVirtualProcessor(virtual_processor_t *virtualProcessor, size_t index, vp_data_type_t value);

vp_data_type_t readVirtualProcessor(virtual_processor_t *virtualProcessor, size_t index);

void
appendLineVirtualProcessor(virtual_processor_t *virtualProcessor, vp_instruction_t instruction, vp_operand_t left,
                           vp_operand_t right);

#ifdef __cplusplus
};
#endif

#endif //VIRTUALPROCESSOR_VIRTUAL_PROCESSOR_H
