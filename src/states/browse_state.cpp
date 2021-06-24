#include <states/browse_state.h>

BrowseState::BrowseState (void) {}

BrowseState::~BrowseState (void) {}

State* BrowseState::process (void) 
{
	FileManager::search("ux0:vpk");
	Carousel::set_list(FileManager::get_all());
	
	while (true)
	{
		Renderer::clear();
		Input::poll();
		
		if (Input::began(SCE_CTRL_UP))
		{
			Carousel::up();
		}
		else if (Input::began(SCE_CTRL_DOWN))
		{
			Carousel::down();
		}
		else if (Input::began(SCE_CTRL_CROSS))
		{
			
		}

		Carousel::draw();

		Log::draw();
		Renderer::swap_buffer();
	}

	return this;
}

const char* BrowseState::get_name() const
{
	return "browse state";
}

















/*float radius = 175;
double angle = 0;
int size = 15;
for (int i = 0; i < size; i++)
{
	float x = radius * cos(angle*PI/180);
	float y = radius * sin(angle*PI/180) + (544/2);	

	Renderer::draw_text("X", x, y, 1.0f, Color(0, 255, 0, 255));

	angle += 360/size;
}*/
