#include "Memory.h"

#include <stdlib.h>

void InitMemory(Memory *memory, const int size) {
    memory->Pointer = malloc(size);
    memory->Size = size;
    memory->used = 0;
}

void DestroyMemory(Memory *memory) {
    free(memory->Pointer);

}