#include <states/video_state.h>
#include <graphics/png_texture.h>

VideoState::VideoState (void) {}

VideoState::VideoState (std::string path):
	path_(path),
	trick_speed_text_(""),
	texture_(nullptr)
{}

VideoState::~VideoState (void) 
{
	VideoManager::close();
}

State* VideoState::process (void) 
{
	VideoManager::open(path_);

	next_state_ = nullptr;
	run_state_ = true;
	
	while (run_state_ && VideoManager::is_finished() == false)
	{
		Input::poll();
		VideoState::check_inputs();

		Renderer::clear();
		VideoManager::draw();
		
		if (VideoManager::get_trick_direction() > 0)
		{
			texture_ = &TextureManager::get_forward();
			Renderer::draw_text(trick_speed_text_, 960-138, 40, 1.0f);
		}
		else if (VideoManager::get_trick_direction() < 0)
		{	
			texture_ = &TextureManager::get_backward();
			Renderer::draw_text(trick_speed_text_, 960-98, 40, 1.0f);
		}
		else
		{
			texture_ = nullptr;
		}
		
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
		
		
		//VideoManager::pause();
		//texture_ = &TextureManager::get_pause();
		
		//VideoManager::play();
		//texture_ = &TextureManager::get_play();
	}
	
	if (Input::began(SCE_CTRL_CIRCLE))
	{
		run_state_ = false;
	}

	if (Input::began(SCE_CTRL_RTRIGGER))
	{
		VideoManager::increase_trick_speed();
		trick_speed_text_ = VideoManager::get_trick_speed();
	}
	else if (Input::began(SCE_CTRL_LTRIGGER))
	{
		VideoManager::decrease_trick_speed();
		trick_speed_text_ = VideoManager::get_trick_speed();
	}
}

const char* VideoState::get_name () const 
{
	return "video state";
}
