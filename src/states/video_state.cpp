#include <states/video_state.h>
#include <graphics/png_texture.h>

VideoState::VideoState (void) {}

VideoState::VideoState (std::string path):
	path_(path),
	trick_speed_text_(""),
	playing_(true)
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
			Renderer::draw_texture(TextureManager::get_forward(), 960-150, 50);
			Renderer::draw_text(trick_speed_text_, 960-138, 40, 1.0f);
		}
		else if (VideoManager::get_trick_direction() < 0)
		{	
			Renderer::draw_texture(TextureManager::get_backward(), 960-150, 50);
			Renderer::draw_text(trick_speed_text_, 960-98, 40, 1.0f);
		}
		
		if (playing_ == false)
		{
			Renderer::draw_texture(TextureManager::get_pause(), 960-150, 50);
		}

		Log::draw();
		Renderer::swap_buffer();
	}

	return next_state_;
}


void VideoState::check_inputs (void)
{
	if (Input::began(SCE_CTRL_CROSS))
	{
		playing_ = !playing_;
		
		if (playing_)
		{
			VideoManager::set_trick_normal();
			VideoManager::play();
		}
		else
		{
			VideoManager::set_trick_normal();
			VideoManager::pause();
		}
	}
	
	if (Input::began(SCE_CTRL_CIRCLE))
	{
		run_state_ = false;
	}

	if (Input::began(SCE_CTRL_RTRIGGER))
	{
		playing_ = true;
		VideoManager::play();
		VideoManager::increase_trick_speed();
		trick_speed_text_ = VideoManager::get_trick_speed();
	}
	else if (Input::began(SCE_CTRL_LTRIGGER))
	{
		playing_ = true;
		VideoManager::play();
		VideoManager::decrease_trick_speed();
		trick_speed_text_ = VideoManager::get_trick_speed();
	}
}

const char* VideoState::get_name () const 
{
	return "video state";
}
