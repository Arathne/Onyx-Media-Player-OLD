#ifndef INITIAL_STATE_H
#define INITIAL_STATE_H

#include <states/state.h>
#include <states/browse_state.h>

class InitialState : public State
{
	public:
		InitialState (void);
		~InitialState (void);

		State* process (void);
		const char* get_name() const;
};

#endif
