#include <states/video_state.h>
#include <graphics/png_texture.h>

VideoState::VideoState (void) {}

VideoState::VideoState (std::string path):
	path_(path),
	texture_(nullptr)
{}

VideoState::~VideoState (void) {}

State* VideoState::process (void) 
{
	Video video(path_);

	next_state_ = nullptr;
	run_state_ = true;
	
	while (run_state_)
	{
		Input::poll();
		VideoState::check_inputs();

		Renderer::clear();
		video.draw();
		
		if (texture_ != nullptr)
			Renderer::draw_texture(*texture_, 960-150, 50);
		
		Log::draw();
		Renderer::swap_buffer();
	}

	return next_state_;
}


void VideoState::check_inputs (void)
{
	if (Input::began(SCE_CTRL_CROSS))
	{
		/*if (Video::is_playing())
		{
			//Video::pause();
			texture_ = &TextureManager::get_pause();
		}
		else
		{
			//Video::play();
			texture_ = &TextureManager::get_play();
		}*/
	}
	
	if (Input::began(SCE_CTRL_CIRCLE))
	{
		run_state_ = false;
	}
}

const char* VideoState::get_name () const 
{
	return "video state";
}
