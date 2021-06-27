#ifndef VIDEO_STATE_H
#define VIDEO_STATE_H

#include <states/state.h>
#include <texture_manager.h>
#include <graphics/png_texture.h>

class VideoState : public State
{
	public:
		VideoState (std::string path);
		~VideoState (void);

		State* process (void);
                const char* get_name() const;

	private:
		VideoState (void);
		
		State* next_state_;
        	bool run_state_;

		std::string path_;
		PNG_Texture* texture_;	
	
		void check_inputs (void);
};

#endif
