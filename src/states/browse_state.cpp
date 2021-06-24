#include <states/browse_state.h>
#include <psp2/io/dirent.h>

BrowseState::BrowseState (void) {}

BrowseState::~BrowseState (void) {}

State* BrowseState::process (void) 
{
	BrowseState::search("ux0:vpk");

	while (true)
	{
		Renderer::clear();
		Input::poll();

		Log::draw();
		Renderer::swap_buffer();
	}

	return this;
}

const char* BrowseState::get_name() const
{
	return "browse state";
}

void BrowseState::search (const char* path)
{
	SceUID directory = sceIoDopen(path);
	
	SceIoDirent current;

	while (sceIoDread(directory, &current) > 0)
	{
		std::string x;

		if ((current.d_stat.st_mode & SCE_S_IFDIR) == SCE_S_IFDIR)
		{
			x = "directory";
		}
		else
		{
			x = "file";
		}
		
		x = std::string(current.d_name) + std::string(" : ") + x;
		Log::add(x);
	}

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
