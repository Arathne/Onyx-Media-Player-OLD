#include <psp2/kernel/processmgr.h>

#include <renderer.h>
#include <color.h>
#include <png_texture.h>
#include <log.h>
#include <input.h>

#define PI 3.14159265
#include <math.h>
#include <string>
#include <video.h>

int main ()
{
	while (true)
	{
		Renderer::clear();
		Input::poll();
		
		if (Input::began(SCE_CTRL_CROSS))
		{
			Video::open("app0:gameplay.mp4");
		}
		else if (Input::began(SCE_CTRL_CIRCLE))
		{
			Video::open("app0:gameplay2.mp4");
		}
		
		Video::draw();
		//Log::add(std::to_string(gameplay1.getTime()));

		Log::draw();
		Renderer::swap_buffer();
	}

	sceKernelExitProcess(0);
}

/*float radius = 175;
double angle = 0;
int size = 15;
for (int i = 0; i < size; i++)
{
	float x = radius * cos(angle*PI/180);
	float y = radius * sin(angle*PI/180) + (544/2);	

	Renderer::draw_text("X", x, y, 1.0f, Color(0, 255, 0, 255));

	angle += 360/size;
}*/
