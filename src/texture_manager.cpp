#include <texture_manager.h>

TextureManager TextureManager::instance;

TextureManager::TextureManager (void) {}

TextureManager::~TextureManager (void) {}

PNG_Texture & TextureManager::get_play (void)
{
	return instance.play_;
}

PNG_Texture & TextureManager::get_pause (void)
{
	return instance.pause_;
}

PNG_Texture & TextureManager::get_forward (void)
{
	return instance.forward_;
}

PNG_Texture & TextureManager::get_backward (void)
{
	return instance.backward_;
}

void TextureManager::load_textures (void)
{
	instance.play_.load("app0:play.png");
	instance.pause_.load("app0:pause.png");
	instance.forward_.load("app0:forward.png");
	instance.backward_.load("app0:backward.png");
}
