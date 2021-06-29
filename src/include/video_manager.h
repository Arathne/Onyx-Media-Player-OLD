#ifndef VIDEO_MANAGER_H
#define VIDEO_MANAGER_H

#include <video.h>

class VideoManager
{
	public:
		~VideoManager (void);
		
		static void open (std::string path);
		static void close (void);

		static void play (void);
		static void pause (void);
		static void draw (void);

		static bool is_finished (void);
		
		static void jump (uint64_t time);
		static void random_jump (void);
		
		static uint64_t get_current_time (void);
		static uint64_t get_total_time (void);
		
		static void increase_trick_speed (void);
		static void decrease_trick_speed (void);
		static std::string get_trick_speed (void);
		static int get_trick_direction (void);

	private:
		static VideoManager instance;
		VideoManager (void);

		Video* video_;
};

#endif
