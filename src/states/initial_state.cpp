#include <states/initial_state.h>

InitialState::InitialState (void) {}

InitialState::~InitialState (void) {}

State* InitialState::process (void)
{
	return new BrowseState();
}

const char* InitialState::get_name() const
{
	return "initial state";
}
