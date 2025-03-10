#include <stdio.h>

#include "debug.h"
#include "value.h"


void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    /**
     * after disassembling the instruction at the given offset, 
     * it returns the offset of the next instruction. 
     * This is because, as we’ll see later, instructions can have different sizes.
     */
    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    // code[offset]: OP_CONSTANT    code[offset + 1]: constant index
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d ' ", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");

    // OP_CONSTANT consumes 2 Bytes
    return offset + 2;
}
int disassembleInstruction(Chunk* chunk, int offset) {
    
    printf("%04d ", offset);

    uint8_t instruction = chunk->code[offset];
    switch(instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

