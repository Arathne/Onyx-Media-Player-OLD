#include <graphics/png_texture.h>

PNG_Texture::PNG_Texture (void) {}

PNG_Texture::PNG_Texture (const char* path)
{
	texture_ = vita2d_load_PNG_file(path);
}

PNG_Texture::~PNG_Texture (void)
{
	if (texture_ != nullptr)
		vita2d_free_texture(texture_);
}

void PNG_Texture::load (const char* path)
{
	if (texture_ != nullptr)
		vita2d_free_texture(texture_);
	
	texture_ = vita2d_load_PNG_file(path);
}

const vita2d_texture* PNG_Texture::get_vita2d_ptr (void) const
{
	return texture_;
}
