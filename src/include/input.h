#ifndef INPUT_H
#define INPUT_H

#include <psp2/ctrl.h>

class Input
{
	public:
		~Input (void);

		static void poll (void);
		static bool began (SceCtrlButtons button);
		static bool ended (SceCtrlButtons button);
		static bool isActive (SceCtrlButtons button);

	private:
		Input (void);

		static Input instance;

		SceCtrlData previous_;
		SceCtrlData current_;
};

#endif
