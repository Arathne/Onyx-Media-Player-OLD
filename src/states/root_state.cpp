#include <states/root_state.h>

RootState::RootState (void) {}

RootState::~RootState (void) {}

State* RootState::process (void) 
{
	std::vector<File> options;
	
	File developer("developer", "ux0:/vpk/developer", true);
	File ux0("ux0:", "ux0:", true);
	
	options.push_back(developer);
	options.push_back(ux0);

	Carousel::set_list(options);
	

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

		Renderer::clear();
		Carousel::draw();
		Log::draw();
		Renderer::swap_buffer();
	}

	return new BrowseState();
}

const char* RootState::get_name() const 
{
	return "root state";
}
