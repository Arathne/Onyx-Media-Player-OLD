#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <stack>
#include <states/state.h>
#include <states/initial_state.h>

class StateManager
{
	public:
		~StateManager (void);
		static void process (void);

	private:
		static StateManager instance;
		StateManager (void);
		
		std::stack<State*> stack_;
};

#endif
