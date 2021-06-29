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

bool VideoManager::is_finished (void)
{
	if (instance.video_ != nullptr)
	{
		return instance.video_->is_finished();
	}

	return false;
}

uint64_t VideoManager::get_current_time (void)
{
	if (instance.video_ != nullptr)
	{
		return instance.video_->get_current_time();
	}

	return 0;
}

uint64_t VideoManager::get_total_time (void)
{
	if (instance.video_ != nullptr)
	{
		return instance.video_->get_total_time();
	}

	return 0;
}

void VideoManager::jump (uint64_t time)
{
	if (instance.video_ != nullptr)
	{
		instance.video_->jump(time);
	}
}

void VideoManager::random_jump (void)
{
	if (instance.video_ != nullptr)
	{
		instance.video_->random_jump();
	}
}
