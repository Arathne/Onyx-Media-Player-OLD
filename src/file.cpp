#include <file.h>

File::File (void):
	name_("null"),
	directory_(false)
{}

File::File (std::string name, SceIoStat & stat):
	name_(name),
	size_(stat.st_size),
	creation_time_(stat.st_ctime),
	last_access_time_(stat.st_atime),
	directory_((stat.st_mode & SCE_S_IFDIR) == SCE_S_IFDIR ? true : false)
{}

File::File (const File & rhs):
	name_(rhs.name_),
	size_(rhs.size_),
	creation_time_(rhs.creation_time_),
	last_access_time_(rhs.last_access_time_),
	directory_(rhs.directory_)
{}

void File::set_name (std::string name)
{
	name_ = name;
}

void File::set_size (SceOff size)
{
	size_ = size;
}

void File::set_creation_time (SceDateTime time)
{
	creation_time_ = time;	
}

void File::set_last_access_time (SceDateTime time)
{
	last_access_time_ = time;
}

void File::set_directory (bool state)
{
	directory_ = state;
}

std::string File::get_name (void) const
{
	return name_;
}

SceOff File::get_size (void) const
{
	return size_;
}

SceDateTime File::get_creation_time (void) const
{
	return creation_time_;
}

SceDateTime File::get_last_access_time (void) const
{
	return last_access_time_;
}

bool File::is_directory (void) const
{
	return directory_;
}

const File & File::operator = (const File & rhs)
{
	if (&rhs != &(*this))
	{
		name_ = rhs.name_;
		size_ = rhs.size_;
		creation_time_ = rhs.creation_time_;
		last_access_time_ = rhs.last_access_time_;
		directory_ = rhs.directory_;
	}

	return *this;
}
