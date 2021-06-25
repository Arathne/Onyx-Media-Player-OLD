#include <states/search_state.h>

SearchState::SearchState (void):
	path_(""),
	index_(0)
{}

SearchState::SearchState (std::string path, int index):
	path_(path),
	index_(index)
{}

SearchState::SearchState (const SearchState & rhs):
	path_(rhs.path_),
	index_(rhs.index_)
{}

SearchState::~SearchState (void) {}

std::string SearchState::get_path (void)
{
	return path_;
}

int SearchState::get_carousel_index (void)
{
	return index_;
}
