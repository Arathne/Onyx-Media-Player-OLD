/* NOTES: this class cannot take advantage of c++ classes because the audio thread method is required to be static which wouldn't be a problem if I could pass
 *        parameters to it. Ideally, I wanted it to be able to open multiple videos at once. Also, the code would have been much easier to read.
 *
 *	  another thing to keep in mind is that the player needs to be completely closed and reinitialized before playing another video. Meaning, all threads
 *	  that the avplayer made will be closed. Not ideal performance wise. Fortunately, playing a video is near instant and shouldn't be an issue.
 *
 *        here are some references, the first one is as simple as it gets.
 *	    https://github.com/Arathne/vita-graphic-samples/tree/master/vita2d/video
 *	    https://github.com/Rinnegatamante/lpp-vita/tree/3dff18e5083b5f2288e7bcac51e0dce69ed3e70c
 *	    https://github.com/SonicMastr/Vita-Media-Player
 *
 * IMPORTANT: sometimes AvPlayer fails to initalize and the only way to fix it is to restart the vita. I think this is an issue with vitasdk rather than my code being buggy.
*/

#include <video.h>

Video Video::instance;

int* a = new int;

Video::Video (void)
{
	sceSysmoduleLoadModule(SCE_SYSMODULE_AVPLAYER);
	
	memset(&frame_info_, 0, sizeof(SceAvPlayerFrameInfo));
	memset(&init_data, 0, sizeof(SceAvPlayerInitData));

	init_data.memoryReplacement.allocate = Video::allocate;
	init_data.memoryReplacement.deallocate = Video::deallocate;
	init_data.memoryReplacement.allocateTexture = Video::allocate_gpu;
	init_data.memoryReplacement.deallocateTexture = Video::deallocate_gpu;

	init_data.basePriority = 0xA0;
	init_data.numOutputVideoFrameBuffers = 1;
	init_data.autoStart = true;
	init_data.debugLevel = 3;
	
	audio_thread_uid_ = sceKernelCreateThread("VideoAudioOutput", audio_thread, 0x10000100, 0x4000, 0, 0, nullptr);
}

Video::~Video (void)
{
	sceKernelDeleteThread(Video::audio_thread_uid_);
	sceAvPlayerClose(player_);
	
	if (frame_ != nullptr)
		delete frame_;
}

void Video::reset (void)
{
	if (frame_ != nullptr)
		delete frame_;
	
	frame_ = new VideoTexture();

	sceAvPlayerClose(player_);
	player_ = sceAvPlayerInit(&init_data);
	sceAvPlayerSetLooping(player_, false);
	
	sceKernelStartThread(audio_thread_uid_, 0, nullptr);
}

void Video::open (const char* path)
{
	instance.reset();
	sceAvPlayerAddSource(instance.player_, path);
}

void Video::pause (void)
{
	sceAvPlayerPause(instance.player_);
}

void Video::play (void)
{
	sceAvPlayerResume(instance.player_);
}

bool Video::isActive (void)
{
	if (sceAvPlayerIsActive(instance.player_) == SCE_TRUE)
		return true;
	else
		return false;
}

uint64_t Video::getTime (void)
{
	return sceAvPlayerCurrentTime(instance.player_);
}

void Video::draw (void)
{
	if (Video::isActive())
	{
		instance.frame_update();
		Renderer::draw_texture(*instance.frame_, 0, 0);
	}
}

void Video::frame_update (void)
{
	if (sceAvPlayerGetVideoData(player_, &instance.frame_info_))
	{
		instance.frame_->update(
			instance.frame_info_.pData,
			instance.frame_info_.details.video.width,
			instance.frame_info_.details.video.height
		);
	}
}

SceInt32 Video::audio_thread (SceSize args, void* argp)
{
	memset(&instance.audio_info_, 0, sizeof(SceAvPlayerFrameInfo));

	uint32_t audioSampleRate = 48000;
	uint16_t channelCount = 2;
	
	SceUID audioPort = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_BGM, (PCM_BUFFER/channelCount/sizeof(int16_t)), audioSampleRate, SCE_AUDIO_OUT_MODE_STEREO);
	
	while (sceAvPlayerIsActive(instance.player_))
	{
		if (sceAvPlayerGetAudioData(instance.player_, &instance.audio_info_))
		{
			if (audioSampleRate != instance.audio_info_.details.audio.sampleRate || channelCount != instance.audio_info_.details.audio.channelCount)
			{
				audioSampleRate = instance.audio_info_.details.audio.sampleRate;
				channelCount = instance.audio_info_.details.audio.channelCount;
				
				SceAudioOutMode mode = (channelCount == 1) ? SCE_AUDIO_OUT_MODE_MONO : SCE_AUDIO_OUT_MODE_STEREO;

				sceAudioOutSetConfig(audioPort, (PCM_BUFFER/channelCount/sizeof(int16_t)), audioSampleRate, mode);
			}

			sceAudioOutOutput(audioPort, instance.audio_info_.pData);
		}
	}
	
	sceAudioOutReleasePort(audioPort);
	
	return sceKernelExitThread(0);
}

void* Video::allocate (void* arg, uint32_t alignment, uint32_t size)
{
	return memalign(alignment, size);
}

void Video::deallocate (void* arg, void* ptr)
{
	free(ptr);
}

void* Video::allocate_gpu (void* arg, uint32_t alignment, uint32_t size)
{
	void* ptr = nullptr;

	if (alignment < 0x40000)
	{
		alignment = 0x40000;
	}

	size = ALIGN(size, alignment);

	SceKernelAllocMemBlockOpt opt;
	memset(&opt, 0, sizeof(opt));
	opt.size = sizeof(SceKernelAllocMemBlockOpt);
	opt.attr = SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_ALIGNMENT;
	opt.alignment = alignment;

	SceUID uid = sceKernelAllocMemBlock("Video Memblock", SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW, size, &opt);

	sceKernelGetMemBlockBase(uid, &ptr);
	sceGxmMapMemory(ptr, size, (SceGxmMemoryAttribFlags)(SCE_GXM_MEMORY_ATTRIB_READ | SCE_GXM_MEMORY_ATTRIB_WRITE));

	return ptr;
}

void Video::deallocate_gpu (void* jumpback, void* ptr)
{
	SceUID uid = sceKernelFindMemBlockByAddr(ptr, 0);
	sceGxmUnmapMemory(ptr);
	sceKernelFreeMemBlock(uid);
}
