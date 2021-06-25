#include <file_manager.h>

FileManager FileManager::instance;

FileManager::FileManager (void):
	path_("")
{}

FileManager::~FileManager (void) {}

void FileManager::search (File file, int carousel_index)
{
	std::string path = file.get_absolute_path();

	SearchState state(path, carousel_index);
	instance.history_.push(state);

	FileManager::search(path.c_str());
}

void FileManager::search (const char* path)
{
	instance.path_ = path;
	SceUID search_uid = sceIoDopen(path);
	instance.entries_.clear();
	SceIoDirent current;
	
	int directories = 0;
	int files = 0;
	
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

	instance.sort_.alphabetical(instance.entries_);

	Log::add("SD/ :: " + std::to_string(directories) + "d " + std::to_string(files) + "f");

	sceIoDclose(search_uid);
}

std::string FileManager::get_parent_directory (void)
{
	return FileManager::get_parent_directory(instance.path_);
}

std::string FileManager::get_parent_directory (std::string path)
{
	std::size_t found = path.find_last_of("/");
	
	if (found == std::string::npos)
	{
		return path;
	}
	
	return path.substr(0, found);
}

std::string FileManager::get_current_directory (void)
{
	return instance.path_;
}

int FileManager::go_back (void)
{
	if (instance.history_.empty())
		return -1;

	SearchState state = instance.history_.top();
	std::string parent_path = FileManager::get_parent_directory(instance.path_);

	FileManager::search(parent_path.c_str());
	
	instance.history_.pop();
	Log::add("path: " + state.get_path());

	return state.get_carousel_index();
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

const std::vector<File> FileManager::get_all (void)
{
	return instance.entries_;
}
