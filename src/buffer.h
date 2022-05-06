#ifndef LOPOLYN_BUFFER_H
#define LOPOLYN_BUFFER_H

#include <cstdint>
#include <cstdlib>

#include "emscripten.h"

extern "C" {
uint8_t* NewBuffer(size_t size);
void DeleteBuffer(const uint8_t*);
}

#endif//LOPOLYN_BUFFER_H
