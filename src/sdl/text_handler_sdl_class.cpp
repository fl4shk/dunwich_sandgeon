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

#include "text_handler_sdl_class.hpp"

namespace dungwich_sandeon
{

namespace io
{

const PosVec2 TextHandlerSdl::TILE_SIZE_2D(8, 8);

bool TextHandlerSdl::init(sdl::Renderer& s_renderer, int& s_zoom)
{
	//--------
	_renderer = &s_renderer;
	_zoom = &s_zoom;
	_font_surface = SDL_LoadBMP("gfx/font.bmp");
	if (!_font_surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't load the bitmap font: %s", SDL_GetError());
		return false;
	}
	//--------
	//// Use black pixels for alpha blending
	//if (SDL_SetColorKey(_font_surface, SDL_TRUE, 0x000000ff) < 0)
	//{
	//	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
	//		"Couldn't set the color key of the font: %s", SDL_GetError());
	//	return false;
	//}
	//--------
	for (auto font_color=FontColor::White;
		font_color!=FontColor::Lim;
		font_color=font_color_add(font_color, 1u))
	{
		_font_texture_map[font_color]
			= sdl::Texture(SDL_CreateTextureFromSurface(*_renderer,
				_font_surface));
	}
	//--------
	// Color the font textures
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Red],
		0xdd, 0x00, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font red: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Green],
		0x00, 0xdd, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font green: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Brown],
		0xc0, 0x66, 0x20) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font brown: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Yellow],
		0xdd, 0xdd, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font yellow: %s", SDL_GetError());
		return false;
	}
	//--------
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Blue],
		0x64, 0x64, 0xff) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font blue: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Purple],
		0xdd, 0x00, 0xdd) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font purple: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Cyan],
		0x00, 0xdd, 0xdd) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font cyan: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_font_texture_map[FontColor::Gray],
		0x90, 0x90, 0x90) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font gray: %s", SDL_GetError());
		return false;
	}
	//--------
	return true;
	//--------
}

void TextHandlerSdl::draw_char(int c, FontColor color,
	const PosVec2& draw_pos)
{
	const auto draw_char_font_surface_size_2d
		= _get_draw_char_font_surface_size_2d();
	const PosVec2 c_tilemap_pos(c % draw_char_font_surface_size_2d.x,
		c / draw_char_font_surface_size_2d.x);
	const PosVec2 c_real_pos(c_tilemap_pos.x * TILE_SIZE_2D.x,
		c_tilemap_pos.y * TILE_SIZE_2D.y);
	const PosVec2 draw_real_pos(draw_pos.x * TILE_SIZE_2D.x,
		draw_pos.y * TILE_SIZE_2D.y);

	const sdl::Rect src_rect(c_real_pos.x, c_real_pos.y,
		TILE_SIZE_2D.x, TILE_SIZE_2D.y),
		dst_rect(draw_real_pos.x * (*_zoom), draw_real_pos.y * (*_zoom),
			TILE_SIZE_2D.x * (*_zoom), TILE_SIZE_2D.y * (*_zoom));
	SDL_RenderCopy(*_renderer, _font_texture_map.at(color), src_rect,
		dst_rect);
}
PosVec2 TextHandlerSdl::_get_draw_char_font_surface_size_2d() const
{
	return PosVec2(_font_surface->w / TILE_SIZE_2D.x,
		_font_surface->h / TILE_SIZE_2D.y);
}

} // namespace io

} // namespace dungwich_sandeon
