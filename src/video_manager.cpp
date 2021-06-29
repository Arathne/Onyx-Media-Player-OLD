#include <video_manager.h>

VideoManager VideoManager::instance;

VideoManager::VideoManager (void) {}

VideoManager::~VideoManager (void) 
{
	if (video_ != nullptr)
	{
		delete video_;
	}
}

void VideoManager::open (std::string path)
{
	if (instance.video_ != nullptr)
	{
		delete instance.video_;
	}
	
	instance.video_ = new Video(path);
}

void VideoManager::play (void)
{
	if (instance.video_ != nullptr)
	{
		instance.video_->play();
	}
}

void VideoManager::pause (void)
{
	if (instance.video_ != nullptr)
	{
		instance.video_->pause();
	}
}

void VideoManager::close (void)
{
	if (instance.video_ != nullptr)
	{
		instance.video_->set_visible(false);
		instance.video_->pause();
	}
}

void VideoManager::draw (void)
{
	if (instance.video_ != nullptr)
	{
		instance.video_->draw();
	}
}
