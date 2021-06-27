#include <settings.h>

Settings Settings::instance;

Settings::Settings (void):
	auto_play_(false)
{}

Settings::~Settings (void) {}

void Settings::set_auto_play (bool state)
{
	instance.auto_play_ = state;
}

bool Settings::get_auto_play (void)
{
	return instance.auto_play_;
}

