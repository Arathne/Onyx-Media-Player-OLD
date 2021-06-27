#ifndef PNG_TEXTURE_H
#define PNG_TEXTURE_H

#include <graphics/texture.h>

class PNG_Texture : public Texture
{
	public:
		PNG_Texture (void);
		PNG_Texture (const char* path);
		~PNG_Texture (void);
		
		void load (const char* path);
		const vita2d_texture* get_vita2d_ptr (void) const; 
		

	private:
		vita2d_texture* texture_;
};


#endif
