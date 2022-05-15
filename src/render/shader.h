#ifndef LOPOLYN_SHADER_H
#define LOPOLYN_SHADER_H

#include <memory>

#include "GLES2/gl2.h"

class Shader
{
private:
	int status{};
	GLuint shader{};
	std::unique_ptr<char[]> error;

public:
	Shader(GLenum type, const char* const* source);
	~Shader();

	GLuint Get() const;
	int GetStatus() const;
	const char* GetError();
};

#endif//LOPOLYN_SHADER_H
