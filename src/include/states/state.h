#ifndef STATE_H
#define STATE_H

#include <log.h>
#include <renderer.h>
#include <input.h>

class State
{
	public: 
		virtual ~State (void) {}

		virtual State* process (void) = 0;
		virtual const char* get_name() const = 0;
};

#endif
