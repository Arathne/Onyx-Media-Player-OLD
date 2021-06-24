#include <log.h>

Log Log::instance;

Log::Log (void):
	max_size(20)
{}

Log::~Log (void) {}

void Log::add (std::string content)
{
	instance.list.push_back(content);

	if (instance.list.size() > instance.max_size)
	{
		instance.list.erase(instance.list.begin());
	}
}

void Log::draw (void)
{
	float x = 960.0f * 0.6f;
	float y = 30.0f;
	
	for (auto it = instance.list.begin(); it != instance.list.end(); it++)
	{
		Renderer::draw_text(*it, x, y, 1.0f);
		y += 20;
	}
}
