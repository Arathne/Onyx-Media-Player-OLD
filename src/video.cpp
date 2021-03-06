/* here are some references, the first one is as simple as it gets.
 *    
 *    https://github.com/Arathne/vita-graphic-samples/tree/master/vita2d/video
 *    https://github.com/Rinnegatamante/lpp-vita
 *    https://github.com/SonicMastr/Vita-Media-Player
 *
 * trick speed is unstable when using sceAvPlayerSetTrickSpeed(), will need a rework
*/

#include <video.h>
#include <log.h>

Video::Video (void) {}

Video::Video (std::string path):
	player_(-1),
	ready_(false),
	visible_(true),
	start_random_(false),
	start_time_(0),
	total_time_(UINT64_MAX),
	frame_(VideoTexture()),
	audio_(VideoAudio()),
	speed_(3),
	trick_speeds_{
		SCE_AVPLAYER_TRICK_SPEED_REWIND_32X,
		SCE_AVPLAYER_TRICK_SPEED_REWIND_16X,
		SCE_AVPLAYER_TRICK_SPEED_REWIND_8X,
		SCE_AVPLAYER_TRICK_SPEED_NORMAL,
		SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_2X,
		SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_4X,
		SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_8X,
		SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_16X,
		SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_32X
	}
{
	sceSysmoduleLoadModule(SCE_SYSMODULE_AVPLAYER);
	srand(time(nullptr));

	SceAvPlayerInitData init_data;

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

	player_ = sceAvPlayerInit(&init_data);
	sceAvPlayerSetLooping(player_, false);

	sceAvPlayerAddSource(player_, path.c_str());

	audio_.set_video_player(player_);
	audio_.start();
}

Video::~Video (void) 
{
	sceAvPlayerClose(player_);
}

void Video::play (void)
{
	sceAvPlayerResume(player_);
}

void Video::pause (void)
{
	sceAvPlayerPause(player_);
}

void Video::restart (void)
{
	sceAvPlayerJumpToTime(player_, 0);
	sceAvPlayerResume(player_);
}

void Video::jump (uint64_t time)
{
	sceAvPlayerJumpToTime(player_, time);
}

void Video::random_jump (void)
{
	if (ready_)
	{
		uint32_t max = total_time_ * 0.65;
		uint32_t min = total_time_ * 0.2;
		int rand_time = rand() % (max-min + 1) + min;
		Video::jump(rand_time);
	}
	else
	{
		start_random_ = true;
	}
}

uint64_t Video::get_current_time (void)
{
	return sceAvPlayerCurrentTime(player_);
}

uint64_t Video::get_total_time (void)
{
	return total_time_;
}

bool Video::is_finished (void)
{
	if (Video::get_current_time() >= total_time_)
	{
		return true;
	}

	if (sceAvPlayerIsActive(player_) == false)
	{
		return true;
	}

	return false;
}

void Video::set_visible (bool state)
{
	visible_ = state;
}

void Video::update (void)
{
	if (sceAvPlayerGetVideoData(player_, &frame_info_))
	{
		if (ready_ == false)
		{
			SceAvPlayerStreamInfo video_stream;
			memset(&video_stream, 0, sizeof(SceAvPlayerStreamInfo));
			sceAvPlayerGetStreamInfo(player_, SCE_AVPLAYER_VIDEO, &video_stream);
		
			total_time_ = video_stream.duration;
			ready_ = true;
			
			if (start_random_)
			{	
				Video::random_jump();
			}
			else
			{
				Video::jump(start_time_);
			}
		}
		else
		{
			frame_.update(
				frame_info_.pData,
				frame_info_.details.video.width,
				frame_info_.details.video.height
                        );
		}
	}
}

void Video::draw (void)
{
	Video::update();
	
	if (sceAvPlayerIsActive(player_) && Video::is_finished() == false && visible_ && ready_)
	{
		float scale_x = 960.0f / (float) frame_info_.details.video.width;
		float scale_y = 544.0f / (float) frame_info_.details.video.height;
		Renderer::draw_texture(frame_, 0, 0, scale_x, scale_y);
	}
}

void Video::set_trick_speed (SceAvPlayerTrickSpeeds speed)
{
	sceAvPlayerSetTrickSpeed(player_, speed);
}

void Video::set_trick_normal (void)
{
	speed_ = 3;
	Video::set_trick_speed(SCE_AVPLAYER_TRICK_SPEED_NORMAL);
}

void Video::increase_trick_speed (void)
{
	if (ready_)
	{
		speed_++;

		if (speed_ >= TRICK_SPEEDS_LIST_SIZE)
		{
			speed_ = TRICK_SPEEDS_LIST_SIZE - 1;
		}
	
		Video::set_trick_speed(trick_speeds_[speed_]);
	}
}

void Video::decrease_trick_speed (void)
{
	if (ready_)
	{
		speed_--;
	
		if (speed_ < 0)
		{
			speed_ = 0;
		}
	
		if (speed_ == 3)
		{
			uint64_t time = Video::get_current_time();
			Video::set_trick_speed(trick_speeds_[speed_]);
			Video::jump(time);
		}
		else
		{
			Video::set_trick_speed(trick_speeds_[speed_]);
		}
	}
}

int Video::get_trick_direction (void)
{
	int trick = trick_speeds_[speed_];
	
	if (trick > 100)
		return 1;
	
	if (trick < 100)
		return -1;

	return 0;
}

std::string Video::get_trick_speed (void)
{
	std::string out;

	switch(trick_speeds_[speed_])
	{
		case SCE_AVPLAYER_TRICK_SPEED_REWIND_32X:
			out = "x32";
			break;
		case SCE_AVPLAYER_TRICK_SPEED_REWIND_16X:
			out = "x16";
			break;
		case SCE_AVPLAYER_TRICK_SPEED_REWIND_8X:
			out = "x8";
			break;
		case SCE_AVPLAYER_TRICK_SPEED_NORMAL:
			out = "";
			break;
		case SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_2X:
			out = "x2";
			break;
		case SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_4X:
			out = "x4";
			break;
		case SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_8X:
			out = "x8";
			break;
		case SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_16X:
			out = "x16";
			break;
		case SCE_AVPLAYER_TRICK_SPEED_FAST_FORWARD_32X:
			out = "x32";
			break;
		default:
			out = "";
			break;
	}

	return out;
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
