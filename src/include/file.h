#ifndef FILE_H
#define FILE_H

#include <psp2/io/stat.h>
#include <string>

class File
{
	public:
		File (void);
		File (std::string name, std::string absolute_path, bool folder);
		File (std::string name, std::string absolute_path, SceIoStat & stat);
		File (const File & rhs);
		
		void set_name (std::string name);
		void set_size (SceOff size);
		void set_creation_time (SceDateTime time);
		void set_last_access_time (SceDateTime time);
		void set_directory (bool state);

		std::string get_name (void) const;
		std::string get_absolute_path (void) const;
		SceOff get_size (void) const;
		SceDateTime get_creation_time (void) const;
		SceDateTime get_last_access_time (void) const;
		bool is_directory (void) const;

		const File & operator = (const File & rhs);

	private:
		std::string name_;
		std::string path_;
		bool directory_;

		SceOff size_;
		SceDateTime creation_time_;
		SceDateTime last_access_time_;
};

#endif
