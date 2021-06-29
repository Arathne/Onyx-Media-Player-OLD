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

	private:
		static VideoManager instance;
		VideoManager (void);

		Video* video_;
};

#endif
