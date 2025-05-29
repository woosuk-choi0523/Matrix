//
// Created by yjhs on 25. 5. 29.
//

#ifndef MEMORY_H
#define MEMORY_H

typedef  struct {
    void* Pointer;
    int Size;
    int Used;
}Memory;

typedef struct {
    Memory Memory;
    int Pointer;
    int Size;
}Point;

#endif //MEMORY_H
