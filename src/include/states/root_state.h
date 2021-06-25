#ifndef ROOT_STATE
#define ROOT_STATE

#include <states/state.h>
#include <states/browse_state.h>
#include <carousel.h>
#include <vector>

class RootState : public State
{
	public:
		RootState (void);
		~RootState (void);

		State* process (void);
		const char* get_name() const;

};

#endif
