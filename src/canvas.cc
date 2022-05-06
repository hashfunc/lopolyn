#include "canvas.h"

EMSCRIPTEN_KEEPALIVE
void BindCanvas(const char* selector)
{
	EmscriptenWebGLContextAttributes contextAttributes;
	emscripten_webgl_init_context_attributes(&contextAttributes);
	auto ctx = emscripten_webgl_create_context(selector, &contextAttributes);
	emscripten_webgl_make_context_current(ctx);
}
