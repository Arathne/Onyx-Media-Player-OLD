#ifndef PNG_TEXTURE_H
#define PNG_TEXTURE_H

#include <texture.h>

class PNG_Texture : public Texture
{
	public:
		PNG_Texture (const char* path);
		~PNG_Texture (void);
		
		const vita2d_texture* get_vita2d_ptr (void) const; 
		

	private:
		PNG_Texture (void);
		
		vita2d_texture* texture_;
};


#endif
