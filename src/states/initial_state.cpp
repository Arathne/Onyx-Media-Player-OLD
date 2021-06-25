#include <states/initial_state.h>

InitialState::InitialState (void) {}

InitialState::~InitialState (void) {}

State* InitialState::process (void)
{
	sceIoMkdir("ux0:/data/onyx", 0777);
	
	return new RootState();
}

const char* InitialState::get_name() const
{
	return "initial state";
}
