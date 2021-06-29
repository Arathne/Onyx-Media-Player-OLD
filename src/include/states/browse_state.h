#ifndef BROWSE_STATE_H
#define BROWSE_STATE_H

#include <states/state.h>
#include <states/video_state.h>
#include <carousel.h>
#include <database.h>

class BrowseState : public State
{
	public:
		BrowseState (void);
                ~BrowseState (void);

                State* process (void);
		const char* get_name() const;
	
	private:
		bool run_state_;
		State* next_state_;
		
		int index_;

		void check_inputs (void);
		void check_preview (void);
		void check_vertical_movement (void);
		void check_change_directories (void);
		void check_add_shortcut (void);
};

#endif
