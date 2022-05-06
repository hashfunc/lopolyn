#include "buffer.h"

EMSCRIPTEN_KEEPALIVE
uint8_t* NewBuffer(size_t size)
{
	return new uint8_t[size];
}

EMSCRIPTEN_KEEPALIVE
void DeleteBuffer(const uint8_t* buffer)
{
	delete[] buffer;
}