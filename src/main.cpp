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
