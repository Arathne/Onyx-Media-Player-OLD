#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <states/state.h>
#include <states/initial_state.h>
#include <stack>

class StateManager
{
	public:
		~StateManager (void);
		static int process (void);

	private:
		static StateManager instance;
		StateManager (void);
		
		std::stack<State*> stack_;
};

#endif
