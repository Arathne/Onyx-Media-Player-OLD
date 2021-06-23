#ifndef LOG_H
#define LOG_H

#include <string>
#include <vector>
#include <renderer.h>

class Log
{
	public:
		~Log (void);
		
		static void add (std::string content);
		static void draw (void);

	private:
		static Log instance;
		Log (void);

		std::vector<std::string> list;
		int max_size;
};

#endif
