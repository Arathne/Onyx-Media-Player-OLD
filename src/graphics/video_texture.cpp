#include <graphics/video_texture.h>

VideoTexture::VideoTexture (void):
	draw_(false)
{
	texture_ = (vita2d_texture*)malloc(sizeof(vita2d_texture));
	texture_ -> palette_UID = 0;
}

VideoTexture::~VideoTexture (void)
{
	if (texture_ != nullptr)
		vita2d_free_texture(texture_);
}

void VideoTexture::update (const void* pData, unsigned int width, unsigned int height)
{
	sceGxmTextureInitLinear(
		&texture_->gxm_tex,
		pData,
		SCE_GXM_TEXTURE_FORMAT_YVU420P2_CSC1,
		width,
		height,
		0
	);

	draw_ = true;
}

const vita2d_texture* VideoTexture::get_vita2d_ptr (void) const
{
	if (draw_)
		return texture_;
	else
		return nullptr;
}
