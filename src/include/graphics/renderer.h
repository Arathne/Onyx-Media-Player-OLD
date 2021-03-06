#ifndef RENDERER_H
#define RENDERER_H

#include <graphics/texture.h>
#include <graphics/color.h>
#include <texture_manager.h>

#include <vita2d.h>
#include <string>

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
		static void draw_texture (Texture & texture, float x, float y, Color color);
		static void draw_texture (Texture & texture, float x, float y, float scale_x, float scale_y);

	private:
		static Renderer instance;
		Renderer (void);
		
		vita2d_pgf* pgf_font;
};

#endif
