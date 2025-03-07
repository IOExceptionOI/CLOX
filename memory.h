#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

// This macro calculates a new capacity based on a given current capacity.
// chunk->capacity = GROW_CAPACITY(oldCapacity);
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

// chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);



#endif