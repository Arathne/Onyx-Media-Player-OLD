#ifndef STATE_H
#define STATE_H

#include <graphics/renderer.h>
#include <input.h>
#include <log.h>

class State
{
	public: 
		virtual ~State (void) {}

		virtual State* process (void) = 0;
		virtual const char* get_name() const = 0;
};

#endif
