#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <graphics/png_texture.h>

class TextureManager
{
	public:
		~TextureManager (void);
		
		static PNG_Texture & get_play (void);
		static PNG_Texture & get_pause (void);
		static PNG_Texture & get_forward (void);
		static PNG_Texture & get_backward (void);
		
		static void load_textures (void);

	private:
		static TextureManager instance;
		TextureManager (void);

		PNG_Texture play_;
		PNG_Texture pause_;
		PNG_Texture forward_;
		PNG_Texture backward_;
};

#endif
