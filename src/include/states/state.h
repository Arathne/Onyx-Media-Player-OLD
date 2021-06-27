#ifndef STATE_H
#define STATE_H

#include <graphics/renderer.h>
#include <input.h>
#include <log.h>
#include <file.h>
#include <file_manager.h>
#include <video.h>

class State
{
	public: 
		virtual ~State (void) {}

		virtual State* process (void) = 0;
		virtual const char* get_name() const = 0;
};

#endif
