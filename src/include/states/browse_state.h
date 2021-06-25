#ifndef BROWSE_STATE_H
#define BROWSE_STATE_H

#include <states/state.h>
#include <carousel.h>

class BrowseState : public State
{
	public:
		BrowseState (void);
                ~BrowseState (void);

                State* process (void);
		const char* get_name() const;
};

#endif
