#include "gaussian.h"

float GaussianFilter::gauss(float sigma, double x)
{
	double exponent = -0.5 * std::pow(x / sigma, 2);
	double value = (1 / (std::sqrt(2.0 * M_PI) * sigma)) * std::exp(exponent);
	return static_cast<float>(value);
}

GaussianFilter::GaussianFilter(const float sigma)
{
	window = int(sigma * 8.0) + 1;
	kernel = std::make_unique<float[]>(window);

	const int radius = (window / 2);
	for (int index = 0; index < window; index++)
	{
		kernel[index] = gauss(sigma, -radius + index);
	}
}

int GaussianFilter::GetWindow() const
{
	return window;
}

const float* GaussianFilter::GetKernel()
{
	return kernel.get();
}

std::string GaussianFilter::CreateShaderSource()
{
	std::ostringstream stream;
	stream << "precision highp float;"
		   << "\n"
		   << "uniform sampler2D u_Texture;"
		   << "\n"
		   << "uniform vec2 u_TextureSize;"
		   << "\n"
		   << "varying vec2 v_TextureCoordinate;"
		   << "\n"
		   << "uniform float u_Kernel[" << window << "];"
		   << "\n"
		   << "void main() {"
		   << "\n"
		   << "  vec2 pixel = vec2(1.0, 1.0) / u_TextureSize;"
		   << "\n"
		   << "  float weight = 1.0;"
		   << "\n"
		   << "  vec4 color = texture2D(u_Texture, v_TextureCoordinate);"
		   << "\n";

	const int radius = window / 2;
	for (int index = 0; index < window; index++)
	{
		stream << "  color += texture2D(u_Texture, v_TextureCoordinate + vec2(" << -radius + index << ".0 * pixel.x, 0.0)) * u_Kernel[" << index << "];"
			   << "\n";
		stream << "  weight += u_Kernel[" << index << "];"
			   << "\n";
	}

	stream << "  gl_FragColor = color / weight;"
		   << "\n";
	stream << "}";

	return stream.str();
}

const char* GaussianFilter::GetShaderSource()
{
	if (source.empty())
	{
		source = CreateShaderSource();
	}
	return source.c_str();
}
