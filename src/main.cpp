#include <psp2/kernel/processmgr.h>
#include <states/state_manager.h>

int main ()
{
	bool run_program = true;

	while (run_program)
	{
		if (StateManager::process() != 0)
		{
			run_program = false;
		}
	}

	sceKernelExitProcess(0);
}




/*#define PI 3.14159265
#include <math.h>
#include <string>
#include <video.h>*/

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
