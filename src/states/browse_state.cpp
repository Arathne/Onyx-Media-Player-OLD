#include <states/browse_state.h>

BrowseState::BrowseState (void):
	run_state_(true),
	next_state_(nullptr),
	index_(1)
{}

BrowseState::~BrowseState (void) {}

State* BrowseState::process (void) 
{
	next_state_ = nullptr;
	run_state_ = true;

	Carousel::set_list(FileManager::get_all(), index_);

	while (run_state_)
	{
		Input::poll();
		BrowseState::check_inputs();

		Renderer::clear();
		VideoManager::draw();
		Carousel::draw();
		Log::draw();
		Renderer::swap_buffer();
	}

	return next_state_;
}

void BrowseState::check_inputs (void)
{
	BrowseState::check_vertical_movement(); // UP - DOWN
	BrowseState::check_change_directories(); // CROSS - CIRCLE
	BrowseState::check_add_shortcut(); // TRIANGLE
	BrowseState::check_preview(); // RTRIGGER
}

void BrowseState::check_preview (void)
{
	if (Input::began(SCE_CTRL_RTRIGGER))
	{
		File entry = Carousel::get_current_file();
		if (entry.is_directory() == false)
		{
			VideoManager::open(entry.get_absolute_path().c_str());
			VideoManager::random_jump();
		}
		else
		{
			VideoManager::close();
		}
	}
}

void BrowseState::check_vertical_movement (void)
{
	if (Input::began(SCE_CTRL_UP))
	{
		Carousel::up();
	}
	else if (Input::began(SCE_CTRL_DOWN))
	{
		Carousel::down();
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
			else
			{
				Log::add("VID/ " + entry.get_absolute_path());
				next_state_ = new VideoState(entry.get_absolute_path());	
				index_ = Carousel::get_index();
				run_state_ = false;
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
