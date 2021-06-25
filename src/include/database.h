#ifndef DATABASE_H
#define DATABASE_H

#include <file.h>
#include <log.h>
#include <vector>
#include <fstream>

class Database
{
	public:
		~Database (void);
		
		static void add_shortcut (std::string name, std::string path);
		static void add_shortcut (const File & shortcut);
		static void remove_shortcut_at (int index);
		static File & get_shortcut_at (int index);
		static std::vector<File> get_shortcuts (void);
		static bool has_shortcuts (void);

	private:
		static Database instance;
		Database (void);

		std::vector<File> shortcuts_;
};

#endif
