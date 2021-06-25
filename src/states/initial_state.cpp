#include <states/initial_state.h>

InitialState::InitialState (void) {}

InitialState::~InitialState (void) {}

State* InitialState::process (void)
{
	return new RootState();
}

const char* InitialState::get_name() const
{
	return "initial state";
}
