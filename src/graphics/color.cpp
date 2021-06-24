#include <graphics/color.h>

Color::Color (void):
	red_(0),
	green_(0),
	blue_(0),
	alpha_(255)
{}

Color::Color (int r, int g, int b):
	alpha_(255)
{
	Color::setRed(r);
	Color::setGreen(g);
	Color::setBlue(b);
}

Color::Color (int r, int g, int b, int a)
{
	Color::setRed(r);
	Color::setGreen(g);
	Color::setBlue(b);
	Color::setAlpha(a);
}

Color::Color (const Color & rhs):
	red_(rhs.red_),
	green_(rhs.green_),
	blue_(rhs.blue_),
	alpha_(rhs.alpha_)
{}

Color::~Color (void) {}

void Color::setRed (int value)
{
	check(value);
	red_ = (unsigned char) value;
}

void Color::setGreen (int value)
{
	check(value);
	green_ = (unsigned char) value;
}

void Color::setBlue (int value)
{
	check(value);
	blue_ = (unsigned char) value;
}

void Color::setAlpha (int value)
{
	check(value);
	alpha_ = (unsigned char) value;
}

int Color::getRed (void) const
{
	return (int) red_;
}

int Color::getGreen (void) const
{
	return (int) green_;
}

int Color::getBlue (void) const
{
	return (int) blue_;
}

int Color::getAlpha (void) const
{
	return (int) alpha_;
}

unsigned int Color::convert_to_vita2d (void) const
{
	return RGBA8(red_, green_, blue_, alpha_);
}

void Color::check (int & value)
{
	if (value > 255)
		value = 255;

	if (value < 0)
		value = 0;
}

const Color & Color::operator = (const Color & rhs)
{
	if (&rhs != &(*this))
	{
		red_ = rhs.red_;
		green_ = rhs.green_;
		blue_ = rhs.blue_;
		alpha_ = rhs.alpha_;
	}

	return *this;
}
