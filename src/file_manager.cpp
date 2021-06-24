#include <file_manager.h>

FileManager FileManager::instance;

FileManager::FileManager (void):
	path_("")
{}

FileManager::~FileManager (void) {}

void FileManager::search (const char* path)
{
	instance.path_ = path;
	SceUID search_uid = sceIoDopen(path);
	instance.entries_.clear();
	SceIoDirent current;
	
	int directories = 0;
	int files = 0;
	
	std::string current_directory = FileManager::get_current_directory();
	if (current_directory != "ux0:" && current_directory != "uma0:")
		instance.entries_.push_back(File(". . .", FileManager::get_parent_directory(), true));

	while (sceIoDread(search_uid, &current) > 0)
	{
		File entry(std::string(current.d_name), std::string(path) + "/" + std::string(current.d_name), current.d_stat);
		
		if (entry.is_directory())
		{
			instance.entries_.push_back(entry);
			directories++;
		}
		else
		{
			if (entry.get_name().find(".mp4") != std::string::npos)
			{
				instance.entries_.push_back(entry);
				files++;
			}
		}
	}

	Log::add("SD :: " + std::to_string(directories) + "d " + std::to_string(files) + "f");

	sceIoDclose(search_uid);
}

std::string FileManager::get_parent_directory (void)
{
	std::size_t found = instance.path_.find_last_of("/");
	
	if (found == std::string::npos)
	{
		return instance.path_;
	}
	
	return instance.path_.substr(0, found);
}

std::string FileManager::get_current_directory (void)
{
	return instance.path_;
}

const std::vector<File> FileManager::get_directories (void)
{
	std::vector<File> directories;

	for (auto it = instance.entries_.begin(); it != instance.entries_.end(); it++)
	{
		if (it->is_directory())
		{
			directories.push_back(*it);
		}
	}

	return directories;
}

const std::vector<File> FileManager::get_video_files (void)
{
	std::vector<File> files;
	
	for (auto it = instance.entries_.begin(); it != instance.entries_.end(); it++)
	{
		if (it->is_directory() == false)
		{
			files.push_back(*it);
		}
	}
	
	return files;
}

const std::vector<File> & FileManager::get_all (void)
{
	return instance.entries_;
}
