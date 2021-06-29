#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <math.h>
#include <log.h>
#include <file.h>

#define PI 3.14159265

class Carousel
{
	public:
		~Carousel (void);
		
		static void up (void);
		static void down (void);

		static void set_list (std::vector<File> entries);
		static void set_list (std::vector<File> entries, int index);
		static bool is_list_empty (void);
		static void set_index (int value);

		static std::vector<File> get_list (void);
		static File get_current_file (void);
		static int get_index (void);

		static void draw (void);

	private:
		static Carousel instance;
		Carousel (void);

		std::vector<File> entries_;
		int index_;
		int draw_radius_;

		static void check (int & value);
};

#endif
