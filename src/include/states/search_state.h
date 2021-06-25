#ifndef SEARCH_STATE_H
#define SEARCH_STATE_H

#include <file.h>
#include <string>

class SearchState
{
	public:
		SearchState (void);
		SearchState (std::string path, int index);
		SearchState (const SearchState & rhs);
		~SearchState (void);
		
		std::string get_path (void);
		int get_carousel_index (void);

	private:
		std::string path_;
		int index_;
};

#endif
