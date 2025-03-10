#include <stdlib.h>

#include "chunk.h"
#include "memory.h"


void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initValueArray(&chunk->constants);
}

/**
 * The first thing we need to do is see if the current array already has capacity for the new byte.
 * If it doesn’t, then we first need to grow the array to make room. 
 * (We also hit this case on the very first write when the array is NULL and  capacity is 0.)
 */

void writeChunk(Chunk* chunk, uint8_t byte) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}

// We deallocate all of the memory 
// and then call initChunk() to zero out the fields leaving the chunk in a well-defined empty state.
void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    initChunk(chunk);
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    // return the index of added value
    return chunk->constants.count - 1;
}
