#include <input.h>
#include <log.h>

Input Input::instance;

Input::Input (void)
{
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_DIGITAL);
}

Input::~Input (void) {}

void Input::poll (void)
{
	instance.previous_ = instance.current_;
	sceCtrlPeekBufferPositive(0, &instance.current_, 1);

	if (Input::began(SCE_CTRL_SELECT))
	{
		Log::enable(!Log::is_enabled());
	}
}

bool Input::began (SceCtrlButtons button)
{
	if ((button & instance.current_.buttons) == button)
	{
		if ((button & instance.previous_.buttons) != button)
		{
			return true;
		}
	}

	return false;
}

bool Input::ended (SceCtrlButtons button)
{
	if ((button & instance.previous_.buttons) == button)
	{
		if ((button & instance.current_.buttons) != button)
		{
			return true;
		}
	}

	return false;
}

bool Input::isActive (SceCtrlButtons button)
{
	if ((button & instance.current_.buttons) == button)
	{
		return true;
	}
	
	return false;
}
