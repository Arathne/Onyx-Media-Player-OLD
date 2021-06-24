#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <graphics/renderer.h>
#include <psp2/io/dirent.h>
#include <file.h>
#include <vector>
#include <log.h>

class FileManager
{
	public:
		~FileManager (void);
		
		static void search (const char* path);
		static std::string get_last_search (void);

		static const std::vector<File> get_directories (void);
		static const std::vector<File> get_video_files (void);
		static const std::vector<File> & get_all (void);

	private:
		static FileManager instance;
		FileManager (void);
		
		std::string path_;
		std::vector<File> entries_;
};

#endif
