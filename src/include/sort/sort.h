#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <string>
#include <vector>
#include <file.h>

class Sort
{
	public:
		virtual ~Sort (void) {}

		virtual void alphabetical (std::vector<File> & array) = 0;
};

#endif
