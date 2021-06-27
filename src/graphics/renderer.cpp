#include <graphics/renderer.h>

Renderer Renderer::instance;

Renderer::Renderer (void)
{
	vita2d_init();
	Renderer::set_clear_color(0, 0, 0, 255);
	vita2d_set_vblank_wait(true);
	pgf_font = vita2d_load_default_pgf();
	TextureManager::load_textures();
}

Renderer::~Renderer (void)
{
	vita2d_fini();
	vita2d_free_pgf(pgf_font);
}

void Renderer::set_clear_color (int r, int g, int b, int a)
{
	vita2d_set_clear_color(RGBA8(r, g, b, a));
}

void Renderer::clear (void)
{
	vita2d_start_drawing();
	vita2d_clear_screen();
}

void Renderer::swap_buffer (void)
{
	vita2d_end_drawing();
	vita2d_swap_buffers();
}

void Renderer::draw_text (std::string content, float x, float y, float scale)
{
	Color white (255, 255, 255, 255);
	draw_text(content, x, y, scale, white);
}

void Renderer::draw_text (std::string content, float x, float y, float scale, Color color)
{
	vita2d_pgf_draw_text(instance.pgf_font, x, y, color.convert_to_vita2d(), scale, content.c_str());
}

void Renderer::draw_texture (Texture & texture, float x, float y)
{
	if (texture.get_vita2d_ptr() != nullptr)
	{
		vita2d_draw_texture(texture.get_vita2d_ptr(), x, y);
	}
}

void Renderer::draw_texture (Texture & texture, float x, float y, Color color)
{
	if (texture.get_vita2d_ptr() != nullptr)
	{
		vita2d_draw_texture_tint(texture.get_vita2d_ptr(), x, y, color.convert_to_vita2d());
	}
}

void Renderer::draw_texture (Texture & texture, float x, float y, float scale_x, float scale_y)
{
	if (texture.get_vita2d_ptr() != nullptr)
	{
		vita2d_draw_texture_scale(texture.get_vita2d_ptr(), x, y, scale_x, scale_y);
	}
}
