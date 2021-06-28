#ifndef VIDEO_AUDIO_H
#define VIDEO_AUDIO_H

#include <psp2/avplayer.h>
#include <psp2/audioout.h>
#include <pthread.h>
#include <cstring>

#define PCM_BUFFER 4096

class VideoAudio
{
	public:
		VideoAudio (void);
		~VideoAudio (void);
		
		void set_video_player (SceAvPlayerHandle & player);
		void start (void);

	public:
		pthread_t thread_;

		SceAvPlayerHandle* player_;
		SceUID audio_port_;
		
		uint32_t sample_rate_;
		uint16_t channel_count_;
		
		static void* thread_func (void* args);
};

#endif
