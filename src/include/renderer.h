#ifndef RENDERER_H
#define RENDERER_H

#include <vita2d.h>
#include <string>
#include <color.h>
#include <texture.h>

class Renderer
{
	public:
		~Renderer (void);
		
		static void clear (void);
		static void set_clear_color (int r, int g, int b, int a);
		static void swap_buffer (void);
		
		static void draw_text (std::string content, float x, float y, float scale);
		static void draw_text (std::string content, float x, float y, float scale, Color color);
		
		static void draw_texture (Texture & texture, float x, float y);

	private:
		static Renderer instance;
		Renderer (void);
		
		vita2d_pgf* pgf_font;
};

#endif
