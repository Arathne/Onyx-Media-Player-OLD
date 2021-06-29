#ifndef VIDEO_H
#define VIDEO_H

#include <graphics/renderer.h>
#include <graphics/video_texture.h>
#include <video_audio.h>
#include <psp2/sysmodule.h>
#include <psp2/avplayer.h>
#include <string>
#include <malloc.h>
#include <cstring>
#include <stdint.h>
#include <cstdlib>
#include <time.h>

#define ALIGN(x, a)	((((unsigned int)x)+((a)-1u))&(~((a)-1u)))
#define TRICK_SPEEDS_LIST_SIZE 9

class Video
{
	public:
		Video (std::string path);
		~Video (void);

		void play (void);
		void pause (void);
		void restart (void);

		uint64_t get_current_time (void);
		uint64_t get_total_time (void);
		
		void jump (uint64_t time);
		void random_jump (void);

		void set_visible (bool state);
		bool is_finished (void);
		
		void set_trick_speed (SceAvPlayerTrickSpeeds speed);
		void set_trick_normal (void);
		void increase_trick_speed (void);
		void decrease_trick_speed (void);
		std::string get_trick_speed (void);
		int get_trick_direction (void);

		void draw (void);

	private:
		Video (void);
		
		SceAvPlayerHandle player_;
		
		bool ready_;
		bool visible_;
		bool start_random_;

		uint64_t start_time_;
		uint64_t total_time_;

		VideoTexture frame_;
		SceAvPlayerFrameInfo frame_info_;
		
		int speed_;
		SceAvPlayerTrickSpeeds trick_speeds_[TRICK_SPEEDS_LIST_SIZE];

		VideoAudio audio_;

		static void* allocate_gpu (void* arg, uint32_t alignment, uint32_t size);
		static void deallocate_gpu (void* jumpback, void* ptr);
		static void* allocate (void* arg, uint32_t alignment, uint32_t size);
		static void deallocate (void* arg, void* ptr);
		
		void update (void);
};

extern "C" {
	typedef enum SceAvPlayerStreamType {
		SCE_AVPLAYER_VIDEO,
		SCE_AVPLAYER_AUDIO,
		SCE_AVPLAYER_TIMEDTEXT,
		SCE_AVPLAYER_UNKNOWN
	} SceAvPlayerStreamType;

	typedef struct SceAvPlayerStreamInfo {
		uint32_t type;
		uint8_t reserved[4];
		SceAvPlayerStreamDetails details;
		uint64_t duration;
		uint64_t startTime;
	} SceAvPlayerStreamInfo;

	int32_t sceAvPlayerStreamCount (SceAvPlayerHandle h);
	int32_t sceAvPlayerGetStreamInfo (SceAvPlayerHandle h, uint32_t argStreamID, SceAvPlayerStreamInfo* argInfo);
	int32_t sceAvPlayerEnableStream (SceAvPlayerHandle h, uint32_t argStreamID);
	int32_t sceAvPlayerDisableStream (SceAvPlayerHandle h, uint32_t argStreamID);
}

#endif
