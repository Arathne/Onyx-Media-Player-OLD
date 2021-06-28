#ifndef VIDEO_H
#define VIDEO_H

#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h> 
#include <psp2/sysmodule.h>
#include <psp2/avplayer.h>
#include <psp2/audioout.h> 
#include <graphics/renderer.h>
#include <graphics/video_texture.h>

#include <stdlib.h>
#include <malloc.h>
#include <cstdint>
#include <cstring>

#define ALIGN(x, a)	((((unsigned int)x)+((a)-1u))&(~((a)-1u)))
#define PCM_BUFFER 4096

class Video
{
	public:
		~Video (void);

		static void open (const char* path);
		static void close (void);
		static void play (void);
		static void pause (void);
		
		static bool is_closed (void);
		static bool is_playing (void);
		static bool isActive (void);
		static uint64_t getTime (void);
		
		static void random_jump (void);

		static void draw (void);
		
	private:
		static Video instance;
		Video (void);
		
		SceAvPlayerInitData init_data;
		SceAvPlayerHandle player_;
		VideoTexture* frame_;
		
		uint64_t duration_;

		SceAvPlayerFrameInfo audio_info_;
		SceAvPlayerFrameInfo frame_info_;
		
		bool playing_;
		bool closed_;

		static void* allocate_gpu (void* arg, uint32_t alignment, uint32_t size);
		static void deallocate_gpu (void* jumpback, void* ptr);
		static void* allocate (void* arg, uint32_t alignment, uint32_t size);
		static void deallocate (void* arg, void* ptr);

		SceUID audio_thread_uid_;
		static SceInt32 audio_thread (SceSize args, void* argp);

		void frame_update (void);
		void reset (void);
};

// currently missing in vitasdk header by mistake
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
