#ifndef TEXTURE_H
#define TEXTURE_H

#include <vita2d.h>

class Texture
{
	public:
		virtual ~Texture (void) {};
		
		virtual const vita2d_texture* get_vita2d_ptr (void) const = 0;
};

#endif
