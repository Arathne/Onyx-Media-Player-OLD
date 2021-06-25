#include <database.h>

#define SHORTCUT_PATH "ux0:/data/onyx/shortcuts.data"
#define DELIMITER std::string("||")

Database Database::instance;

Database::Database (void) 
{
	std::ifstream input(SHORTCUT_PATH);
	std::string str;
	
	while (std::getline(input, str))
	{
		std::string name = str.substr(0, str.find(DELIMITER));
		std::string path = str.substr(str.find(DELIMITER) + DELIMITER.size());
		instance.shortcuts_.push_back(File(name, path, true));
	}

	input.close();
}

Database::~Database (void) {}

void Database::add_shortcut (std::string name, std::string path)
{
	if (name != ". . .")
	{
		instance.shortcuts_.push_back(File(name, path, true));
		Log::add("ADD/ :: " + name + " " + path);

		std::ofstream file(SHORTCUT_PATH, std::ofstream::app);
		file << name << DELIMITER << path << std::endl;
		file.close();
	}
}

void Database::add_shortcut (const File & shortcut)
{
	instance.shortcuts_.push_back(shortcut);
}

void Database::remove_shortcut_at (int index)
{
	if (index >= 0 && index < instance.shortcuts_.size())
	{
		instance.shortcuts_.erase(instance.shortcuts_.begin() + index);
	
		std::ofstream file(SHORTCUT_PATH);
		std::string data;

		for (auto it = instance.shortcuts_.begin(); it != instance.shortcuts_.end(); it++)
		{
			data += it->get_name() + DELIMITER + it->get_absolute_path() + "\n";
		}
		
		file << data;
		file.close();
	}
}

File & Database::get_shortcut_at (int index)
{
	return instance.shortcuts_.at(index);
}

std::vector<File> Database::get_shortcuts (void)
{
	return instance.shortcuts_;
}

bool Database::has_shortcuts (void)
{
	return instance.shortcuts_.empty();
}
