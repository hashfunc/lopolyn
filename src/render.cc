#include "render.h"

GLuint CreateShader(GLenum glType, const char* const* source)
{
	auto shader = glCreateShader(glType);

	glShaderSource(shader, 1, source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLsizei logLength;
		GLchar log[1024];
		glGetShaderInfoLog(shader, sizeof(log), &logLength, log);
		printf("shader compile error: %s", log);

		glDeleteShader(shader);
		return -1U;
	}

	return shader;
}

GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
	auto program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		GLsizei logLength;
		GLchar log[1024];
		glGetProgramInfoLog(program, sizeof(log), &logLength, log);
		printf("shader compile error: %s", log);

		glDeleteProgram(program);
		return -1U;
	}

	return program;
}

void SetRectangle(GLuint buffer, float x, float y, float width, float height)
{

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	float x1 = x;
	float x2 = x + width;
	float y1 = y;
	float y2 = y + height;
	float data[12] = {x1, y1, x2, y1, x1, y2, x1, y2, x2, y1, x2, y2};
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void SetTexture(GLuint textures, uint8_t* buffer, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, textures);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
}