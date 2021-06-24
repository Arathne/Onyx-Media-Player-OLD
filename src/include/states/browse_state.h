#ifndef BROWSE_STATE_H
#define BROWSE_STATE_H

#include <states/state.h>
#include <math.h>
#include <vector>

#define PI 3.14159265

class BrowseState : public State
{
	public:
		BrowseState (void);
                ~BrowseState (void);

                State* process (void);
		const char* get_name() const;
	
	private:
		void search (const char* path);
};

#endif
