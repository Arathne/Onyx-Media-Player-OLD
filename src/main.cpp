#include <psp2/kernel/processmgr.h>

#include <renderer.h>
#include <color.h>
#include <png_texture.h>
#include <log.h>

int main ()
{
	while (true)
	{
		Renderer::clear();
		Renderer::draw_text("HELLO WORLD", 30, 30, 1.0f, Color(0, 255, 0, 255));
		Log::draw();
		Renderer::swap_buffer();
	}

	sceKernelExitProcess(0);
}
