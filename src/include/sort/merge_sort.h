#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <sort/sort.h>
#include <cctype>
#include <log.h>

class MergeSort : public Sort
{
	public:
		MergeSort (void);
		~MergeSort (void);

		void alphabetical (std::vector<File> & array);

	private:
		void alphabetical_recursion (std::vector<File> & array, int start, int end);
};

#endif
