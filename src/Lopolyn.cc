#include "Lopolyn.h"

EMSCRIPTEN_KEEPALIVE
void Preview(uint8_t* buffer, int width, int height)
{
	auto vertexShader = Shader(GL_VERTEX_SHADER, &VERTEX_SHADER_SOURCE);
	if (!vertexShader.GetStatus())
	{
		printf("%s", vertexShader.GetError());
		return;
	}

	auto fragmentShader = Shader(GL_FRAGMENT_SHADER, &FRAGMENT_SHADER_SOURCE);
	if (!fragmentShader.GetStatus())
	{
		printf("%s", fragmentShader.GetError());
		return;
	}

	auto program = CreateProgram(vertexShader.Get(), fragmentShader.Get());
	if (program == -1)
	{
		return;
	}

	auto coordinateLocation = glGetAttribLocation(program, "a_Coordinate");

	GLuint coordinateBuffer[1];
	glGenBuffers(1, coordinateBuffer);
	SetRectangle(coordinateBuffer[0], 0, 0, 1, 1);

	GLuint textures[1];
	glGenTextures(1, textures);

	SetTexture(textures[0], buffer, width, height);

	glViewport(0, 0, width, height);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	glEnableVertexAttribArray(coordinateLocation);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer[0]);
	glVertexAttribPointer(coordinateLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
