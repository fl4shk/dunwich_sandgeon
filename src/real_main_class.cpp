// This file is part of Dungwich Sandeon.
// 
// Dungwich Sandeon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Dungwich Sandeon is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Dungwich Sandeon.  If not, see <https://www.gnu.org/licenses/>.

#include "real_main_class.hpp"

namespace dungwich_sandeon
{

const Vec2<int> RealMain::SCREEN_SIZE_2D(Vec2<int>(640, 480)),
	RealMain::TILE_SIZE_2D(Vec2<int>(16, 16));
const std::map<RealMain::FontColor, std::string> RealMain::COLOR_TO_STR_MAP
= {
	{RealMain::FontColor::White, "White"},
	{RealMain::FontColor::Red, "Red"},
	{RealMain::FontColor::Green, "Green"},
	{RealMain::FontColor::Brown, "Brown"},
	{RealMain::FontColor::Yellow, "Yellow"},
	{RealMain::FontColor::Blue, "Blue"},
	{RealMain::FontColor::Purple, "Purple"},
	{RealMain::FontColor::Cyan, "Cyan"},
	{RealMain::FontColor::Gray, "Gray"},
	{RealMain::FontColor::Lim, "Lim"},
};
int RealMain::run()
{
	//--------
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't initialize SDL: %s", SDL_GetError());
		return 1;
	}
	sdl::QuitUponDtor quit_upon_dtor;

	sdl::prevent_dpi_scaling_issues();

	_window = SDL_CreateWindow("Dungwich Sandeon",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE_2D.x,
		SCREEN_SIZE_2D.y, SDL_WINDOW_RESIZABLE);
	if (!_window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't create window: %s", SDL_GetError());
		return 1;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't create renderer: %s", SDL_GetError());
		return 1;
	}

	_font_surface = SDL_LoadBMP("gfx/font.bmp");
	if (!_font_surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't load the bitmap font: %s", SDL_GetError());
		return 1;
	}

	// Change the magenta pixels to black
	if (auto pixels = reinterpret_cast<u8*>(_font_surface->pixels); true)
	{
		//printf("%i %i %i\n", _font_surface->h, _font_surface->w,
		//	(_font_surface->pitch / _font_surface->w));
		for (int j=0; j<_font_surface->h; ++j)
		{
			for (int i=0; i<_font_surface->w; ++i)
			{
				if ((pixels[0] != 0xff) || (pixels[1] != 0xff)
					|| (pixels[2] != 0xff))
				{
					pixels[0] = 0x00;
					pixels[1] = 0x00;
					pixels[2] = 0x00;
				}
				pixels += 3;
			}
		}
	}
	// Use black pixels for alpha blending
	if (SDL_SetColorKey(_font_surface, SDL_TRUE, 0xff00ffff) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't set the color key of the font: %s", SDL_GetError());
		return 1;
	}

	for (auto font_color=FontColor::White;
		font_color!=FontColor::Lim;
		font_color=font_color_add(font_color, 1u))
	{
		_font_texture_map[font_color]
			= sdl::Texture(SDL_CreateTextureFromSurface(_renderer,
				_font_surface));
	}
	//--------
	// Color the font textures
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Red],
		0xdd, 0x00, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font red: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Green],
		0x00, 0xdd, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font green: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Brown],
		0xc0, 0x66, 0x20) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font brown: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Yellow],
		0xdd, 0xdd, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font yellow: %s", SDL_GetError());
	}
	//--------
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Blue],
		0x64, 0x64, 0xff) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font blue: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Purple],
		0xdd, 0x00, 0xdd) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font purple: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Cyan],
		0x00, 0xdd, 0xdd) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font cyan: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Gray],
		0x90, 0x90, 0x90) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font gray: %s", SDL_GetError());
	}
	//--------
	// Draw a green background
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(_renderer, sdl::Rect(0, 0, SCREEN_SIZE_2D.x,
		SCREEN_SIZE_2D.y));
	_draw_char('@', FontColor::White, Vec2<int>(0, 0));

	_draw_char('@', FontColor::Red, Vec2<int>(1, 0));
	_draw_char('@', FontColor::Green, Vec2<int>(2, 0));
	_draw_char('@', FontColor::Brown, Vec2<int>(3, 0));
	_draw_char('@', FontColor::Yellow, Vec2<int>(4, 0));

	_draw_char('@', FontColor::Blue, Vec2<int>(5, 0));
	_draw_char('@', FontColor::Purple, Vec2<int>(6, 0));
	_draw_char('@', FontColor::Cyan, Vec2<int>(7, 0));
	_draw_char('@', FontColor::Gray, Vec2<int>(8, 0));
	SDL_RenderPresent(_renderer);
	SDL_Delay(10'000);
	//--------
	return 0;
}
void RealMain::_draw_char(int c, FontColor color,
	const Vec2<int>& draw_pos)
{
	const auto draw_char_font_surface_size_2d
		= _get_draw_char_font_surface_size_2d();
	const Vec2<int> c_tilemap_pos(c % draw_char_font_surface_size_2d.x,
		c / draw_char_font_surface_size_2d.x);
	const Vec2<int> c_real_pos(c_tilemap_pos.x * TILE_SIZE_2D.x,
		c_tilemap_pos.y * TILE_SIZE_2D.y);
	const Vec2<int> draw_real_pos(draw_pos.x * TILE_SIZE_2D.x,
		draw_pos.y * TILE_SIZE_2D.y);

	const sdl::Rect src_rect(c_real_pos.x, c_real_pos.y, TILE_SIZE_2D.x,
		TILE_SIZE_2D.y),
		dst_rect(draw_real_pos.x, draw_real_pos.y, TILE_SIZE_2D.x,
			TILE_SIZE_2D.y);
	SDL_RenderCopy(_renderer, _font_texture_map.at(color), src_rect,
		dst_rect);
}

} // namespace dungwich_sandeon
