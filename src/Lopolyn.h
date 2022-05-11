#ifndef LOPOLYN_LOPOLYN_H
#define LOPOLYN_LOPOLYN_H

#include "GLES2/gl2.h"
#include "emscripten.h"

#include "filter/gaussian.h"
#include "render.h"
#include "shader.hpp"

extern "C" {
void Preview(uint8_t* buffer, int width, int height);
}

#endif//LOPOLYN_LOPOLYN_H
