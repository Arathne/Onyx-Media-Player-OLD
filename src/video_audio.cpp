#include <video_audio.h>

VideoAudio::VideoAudio (void):
	sample_rate_(48000),
	channel_count_(2)
{
	audio_port_ = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_BGM, (PCM_BUFFER/channel_count_/sizeof(int16_t)), sample_rate_, SCE_AUDIO_OUT_MODE_STEREO);
}

VideoAudio::~VideoAudio (void) 
{
	sceAudioOutReleasePort(audio_port_);
}

void VideoAudio::set_video_player (SceAvPlayerHandle & player)
{
	player_ = &player;
}

void VideoAudio::start (void) 
{
	pthread_create(&thread_, nullptr, thread_func, (void*) this);
}

void* VideoAudio::thread_func (void* args)
{
	VideoAudio* audio = (VideoAudio*) args;

	SceAvPlayerFrameInfo audio_info_;
	memset(&audio_info_, 0, sizeof(SceAvPlayerFrameInfo));

	while (sceAvPlayerIsActive(*audio->player_) && audio->player_ != nullptr && audio != nullptr)
	{
		if (sceAvPlayerGetAudioData(*audio->player_, &audio_info_))
		{
			if (audio->sample_rate_ != audio_info_.details.audio.sampleRate || audio->channel_count_ != audio_info_.details.audio.channelCount)
			{
				audio->sample_rate_ = audio_info_.details.audio.sampleRate;
				audio->channel_count_ = audio_info_.details.audio.channelCount;

				SceAudioOutMode mode = (audio->channel_count_ == 1) ? SCE_AUDIO_OUT_MODE_MONO : SCE_AUDIO_OUT_MODE_STEREO;

				sceAudioOutSetConfig(audio->audio_port_, (PCM_BUFFER/audio->channel_count_/sizeof(int16_t)), audio->sample_rate_, mode);
			}

			sceAudioOutOutput(audio->audio_port_, audio_info_.pData);
		}
	}

	pthread_exit(nullptr);
	return nullptr;
}
