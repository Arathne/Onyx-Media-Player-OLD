#include <carousel.h>

Carousel Carousel::instance;

Carousel::Carousel (void):
	index_(0),
	draw_radius_(7)
{}

Carousel::~Carousel (void) {}

void Carousel::up (void)
{
	instance.index_--;
	check(instance.index_);	
}

void Carousel::down (void)
{
	instance.index_++;
	check(instance.index_);
}

void Carousel::set_list (std::vector<File> entries)
{
	instance.entries_ = entries;
	instance.index_ = 0;
}

std::vector<File> Carousel::get_list (void)
{
	return instance.entries_;
}

File Carousel::get_current_file (void)
{
	return instance.entries_.at(instance.index_);
}

void Carousel::check (int & value)
{
	if (value < 0)
	{
		value = 0;
	}
	
	if (value > instance.entries_.size() - 1)
	{
		value = instance.entries_.size() - 1;
	}
}

void Carousel::draw (void)
{
	int lower_bound = instance.index_ - instance.draw_radius_;
	int upper_bound = instance.index_ + instance.draw_radius_;

	check(lower_bound);
	check(upper_bound);
	
	float angle_increment = 10;
	double angle = 0 + (-angle_increment * instance.index_);

	for (auto it = instance.entries_.begin(); it != instance.entries_.end(); it++)
	{
		float x = 175 * cos(angle*PI/180);
		float y = 250 * sin(angle*PI/180) + (544/2); 
		float alpha = cos(angle*PI/180) * 255;
		float scale = cos(angle*PI/180) + 0.22f;

		File current = *it;
		int i = it - instance.entries_.begin();
		
		if (i >= lower_bound && i <= upper_bound)
		{
			if (i == instance.index_)
			{
				Renderer::draw_text(current.get_name(), x, y, scale, Color(0,255,0,alpha));
			}
			else
			{
				if (current.is_directory())
				{
					Renderer::draw_text(current.get_name(), x, y, scale, Color(0,167,255,alpha));
				}
				else
				{
					Renderer::draw_text(current.get_name(), x, y, scale, Color(255,255,255,alpha));
				}
			}
		}

		angle += angle_increment;
	}
}
