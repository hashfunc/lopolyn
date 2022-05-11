#ifndef LOPOLYN_GAUSSIAN_H
#define LOPOLYN_GAUSSIAN_H

#include <cmath>
#include <memory>
#include <sstream>
#include <string>

class GaussianFilter
{
	int window;
	std::unique_ptr<float[]> kernel;
	std::string source;

public:
	explicit GaussianFilter(float sigma);

	int GetWindow() const;
	const float* GetKernel();
	const char* GetShaderSource();

private:
	float gauss(float sigma, double x);
	std::string CreateShaderSource();
};

#endif//LOPOLYN_GAUSSIAN_H
