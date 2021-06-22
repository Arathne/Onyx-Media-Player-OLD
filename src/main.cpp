#include <psp2/kernel/processmgr.h>

#include "graphics/renderer.h"
#include <color.h>

int main ()
{
	while (true)
	{
		Renderer::clear();
		Renderer::draw_text("HELLO WORLD", 30, 30, 1.0f, Color(0, 255, 0, 255));
		Renderer::swap_buffer();
	}

	sceKernelExitProcess(0);
}
