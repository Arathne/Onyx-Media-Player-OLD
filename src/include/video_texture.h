#ifndef VIDEO_TEXTURE_H
#define VIDEO_TEXTURE_H

#include <psp2/gxm.h>
#include <vita2d.h>
#include <texture.h>
#include <cstdlib>

class VideoTexture : public Texture 
{
	public:
		VideoTexture (void);
		~VideoTexture (void);
		
		void update (const void* pData, unsigned int width, unsigned int height);

		const vita2d_texture* get_vita2d_ptr (void) const;

	private:
		vita2d_texture* texture_;
		bool draw_;
};

#endif
