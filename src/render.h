#ifndef LOPOLYN_RENDER_H
#define LOPOLYN_RENDER_H

#include <cstdio>

#include "GLES2/gl2.h"
#include "emscripten.h"

GLuint CreateShader(GLenum glType, const char* const* source);
GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader);
void SetRectangle(GLuint buffer, float x, float y, float width, float height);
void SetTexture(GLuint textures, uint8_t* buffer, int width, int height);

#endif//LOPOLYN_RENDER_H
