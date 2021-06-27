#include <states/browse_state.h>

BrowseState::BrowseState (void):
	run_state_(true),
	next_state_(nullptr),
	video_path_("")
{}

BrowseState::~BrowseState (void) {}

State* BrowseState::process (void) 
{
	next_state_ = nullptr;

	Carousel::set_list(FileManager::get_all());
	run_state_ = true;

	while (run_state_)
	{
		Input::poll();
		BrowseState::check_inputs();

		Renderer::clear();
		Video::draw();
		Carousel::draw();
		Log::draw();
		Renderer::swap_buffer();
	}

	return next_state_;
}

void BrowseState::play_video (void)
{
	File entry = Carousel::get_current_file();
	if (entry.is_directory() == false)
	{
		Video::open(entry.get_absolute_path().c_str());
	}
}

void BrowseState::check_inputs (void)
{
	BrowseState::check_vertical_movement(); // UP - DOWN
	BrowseState::check_change_directories(); // CROSS - CIRCLE
	BrowseState::check_add_shortcut(); // TRIANGLE
	BrowseState::check_preview(); // L-R TRIGGERS
}

void BrowseState::check_preview (void)
{
	if (Input::began(SCE_CTRL_RTRIGGER))
	{
		Settings::set_auto_play(false);
		BrowseState::play_video();
		
		File entry = Carousel::get_current_file();
		if (entry.is_directory() == false)
		{
			std::string entry_path = entry.get_absolute_path();
			if (video_path_ != entry_path)
			{
				Video::open(entry_path.c_str());
				Video::random_jump();
				video_path_ = entry_path;
			}
			else
			{
				Video::close();
				video_path_ = "";
			}
		}
		else
		{
			Video::close();
			video_path_ = "";
		}
	}

	if (Input::began(SCE_CTRL_LTRIGGER))
	{
		Settings::set_auto_play(!Settings::get_auto_play());
	}
}

void BrowseState::check_vertical_movement (void)
{
	if (Input::began(SCE_CTRL_UP))
	{
		Carousel::up();

		if (Settings::get_auto_play())
		{
			BrowseState::play_video();
		}
	}
	else if (Input::began(SCE_CTRL_DOWN))
	{
		Carousel::down();

		if (Settings::get_auto_play())
		{
			BrowseState::play_video();
		}
	}
}

void BrowseState::check_add_shortcut (void)
{
	if (Input::began(SCE_CTRL_TRIANGLE))
	{
		File entry = Carousel::get_current_file();
		if (entry.is_directory())
		{
			Database::add_shortcut(entry.get_name(), entry.get_absolute_path());
		}
	}
}

void BrowseState::check_change_directories (void)
{
	if (Input::began(SCE_CTRL_CROSS))
	{
		if (Carousel::is_list_empty() == false)
		{
			File entry = Carousel::get_current_file();
			if (entry.is_directory())
			{
				Log::add("RD/ " + entry.get_absolute_path());

				if (entry.get_name() == ". . .")
				{
					int previous_carousel_index = FileManager::go_back();

					if (previous_carousel_index >= 0)
					{
						Carousel::set_list(FileManager::get_all());
						Carousel::set_index(previous_carousel_index);
					}

					if (entry.get_name() == Carousel::get_current_file().get_name())
					{
						run_state_ = false;
					}
				}
				else
				{
					FileManager::search(entry, Carousel::get_index());
					Carousel::set_list(FileManager::get_all());
				}
			}
		}
	}
	else if (Input::began(SCE_CTRL_CIRCLE))
	{
		int previous_carousel_index = FileManager::go_back();

		if (previous_carousel_index >= 0)
		{
			Carousel::set_list(FileManager::get_all());
			Carousel::set_index(previous_carousel_index);
		}
		else
		{
			run_state_ = false;
		}
	}
}

const char* BrowseState::get_name() const
{
	return "browse state";
}
