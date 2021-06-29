#include <states/root_state.h>

RootState::RootState (void):
	carousel_index_(0)
{}

RootState::~RootState (void) {}

State* RootState::process (void) 
{
	std::vector<File> options;
	
	RootState::update_carousel();
	Carousel::set_index(carousel_index_);

	State* next_state = nullptr;
	bool run_state = true;
	
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
			run_state = false;
			next_state = new BrowseState();

			File entry = Carousel::get_current_file();
			Log::add("RD/ " + entry.get_absolute_path());
			FileManager::search(entry.get_absolute_path().c_str());
		}
		if (Input::began(SCE_CTRL_TRIANGLE))
		{
			Database::remove_shortcut_at(Carousel::get_index());
			int index = Carousel::get_index();
			RootState::update_carousel();
			Carousel::set_index(index);
		}
		if (Input::began(SCE_CTRL_RTRIGGER))
		{
			// stop video
		}

		Renderer::clear();
		VideoManager::draw();
		Carousel::draw();
		Log::draw();
		Renderer::swap_buffer();
	}

	carousel_index_ = Carousel::get_index();

	return new BrowseState();
}

void RootState::update_carousel (void)
{
	std::vector<File> list = Database::get_shortcuts();
	list.push_back(File("ux0:", "ux0:", true));
	list.push_back(File("uma0:", "uma0:", true));
	
	Carousel::set_list(list);
}

const char* RootState::get_name() const 
{
	return "root state";
}
