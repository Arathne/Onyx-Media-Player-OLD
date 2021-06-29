#include <states/video_state.h>
#include <graphics/png_texture.h>

VideoState::VideoState (void) {}

VideoState::VideoState (std::string path):
	path_(path),
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
		
		if (texture_ != nullptr)
			Renderer::draw_texture(*texture_, 960-150, 50);
		
		//Log::add( "current: " + std::to_string(VideoManager::get_current_time()));
		//Log::add( "total: " + std::to_string(VideoManager::get_total_time()));

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
}

const char* VideoState::get_name () const 
{
	return "video state";
}
