#include "Lopolyn.h"

EMSCRIPTEN_KEEPALIVE
void Preview(uint8_t* buffer, int width, int height)
{
	auto vertexShader = CreateShader(GL_VERTEX_SHADER, &VERTEX_SHADER_SOURCE);
	if (vertexShader == -1)
	{
		return;
	}

	auto gaussianFilter = GaussianFilter(5);

	auto fragmentShaderSource = gaussianFilter.GetShaderSource();
	auto fragmentShader = CreateShader(GL_FRAGMENT_SHADER, &fragmentShaderSource);
	if (fragmentShader == -1)
	{
		glDeleteShader(vertexShader);
		return;
	}

	auto program = CreateProgram(vertexShader, fragmentShader);
	if (program == -1)
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	auto coordinateLocation = glGetAttribLocation(program, "a_Coordinate");

	auto textureSizeLocation = glGetUniformLocation(program, "u_TextureSize");
	auto kernelLocation = glGetUniformLocation(program, "u_Kernel");

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

	glUniform2f(textureSizeLocation, width, height);
	glUniform1fv(kernelLocation, gaussianFilter.GetWindow(), gaussianFilter.GetKernel());

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
