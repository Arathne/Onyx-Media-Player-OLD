#include <states/browse_state.h>

BrowseState::BrowseState (void) {}

BrowseState::~BrowseState (void) {}

State* BrowseState::process (void) 
{
	State* next_state = nullptr;
	bool run_state = true;

	Carousel::set_list(FileManager::get_all());

	while (run_state)
	{
		Input::poll();
		
		if (Input::began(SCE_CTRL_UP))
		{
			Carousel::up();
		}
		else if (Input::began(SCE_CTRL_DOWN))
		{
			Carousel::down();
		}
		
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
							run_state = false;
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
					Video::open(entry.get_absolute_path().c_str());
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
				run_state = false;
			}
		}
		else if (Input::began(SCE_CTRL_TRIANGLE))
		{
			File entry = Carousel::get_current_file();
                        if (entry.is_directory())
			{
				Database::add_shortcut(entry.get_name(), entry.get_absolute_path());
			}
		}
		
		Renderer::clear();
		Video::draw();
		Carousel::draw();
		Log::draw();
		Renderer::swap_buffer();
	}

	return next_state;
}

const char* BrowseState::get_name() const
{
	return "browse state";
}
