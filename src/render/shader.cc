#include "shader.h"


Shader::Shader(GLenum type, const char* const* source)
{
	shader = glCreateShader(type);

	glShaderSource(shader, 1, source, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		error = std::make_unique<char[]>(length);
		glGetShaderInfoLog(shader, length, nullptr, error.get());
	}
}

Shader::~Shader()
{
	glDeleteShader(shader);
}

GLuint Shader::Get() const
{
	return shader;
}

int Shader::GetStatus() const
{
	return status;
}

const char* Shader::GetError()
{
	if (status)
	{
		return nullptr;
	}
	return error.get();
}
