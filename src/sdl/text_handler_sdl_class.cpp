// This file is part of Dunwich Sandgeon.
// 
// Copyright 2022 FL4SHK
//
// Dunwich Sandgeon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Dunwich Sandgeon is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Dunwich Sandgeon.  If not, see <https://www.gnu.org/licenses/>.

#include "text_handler_sdl_class.hpp"

namespace dunwich_sandgeon
{
namespace io
{

const PosVec2 TextHandlerSdl::TILE_SIZE_2D(8, 8);

//bool TextHandlerSdl::init(sdl::Renderer& s_renderer, int& s_zoom)
bool TextHandlerSdl::init(sdl::Renderer& s_renderer)
{
	//--------
	_renderer = &s_renderer;
	//_zoom = &s_zoom;

	_fg_surface = SDL_LoadBMP("gfx/font.bmp");

	if (!_fg_surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't load the bitmap font: %s", SDL_GetError());
		return false;
	}

	_bg_surface = SDL_LoadBMP("gfx/bg.bmp");

	if (!_bg_surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't load the bitmap font: %s", SDL_GetError());
		return false;
	}
	//--------
	//// Use black pixels for alpha blending
	//if (SDL_SetColorKey(_fg_surface, SDL_TRUE, 0x000000ff) < 0)
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
		_fg_texture_map[font_color]
			= sdl::Texture(SDL_CreateTextureFromSurface(*_renderer,
				_fg_surface));
		_bg_texture_map[font_color]
			= sdl::Texture(SDL_CreateTextureFromSurface(*_renderer,
				_bg_surface));
	}
	//--------
	// Color the font and bg textures
	if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::Red],
		FONT_RED_STCM_R, FONT_RED_STCM_G, FONT_RED_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the fg red: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::Red],
		FONT_RED_STCM_R, FONT_RED_STCM_G, FONT_RED_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the bg red: %s", SDL_GetError());
		return false;
	}

	if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::Green],
		FONT_GREEN_STCM_R, FONT_GREEN_STCM_G, FONT_GREEN_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the fg green: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::Green],
		FONT_GREEN_STCM_R, FONT_GREEN_STCM_G, FONT_GREEN_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the bg green: %s", SDL_GetError());
		return false;
	}

	if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::Brown],
		FONT_BROWN_STCM_R, FONT_BROWN_STCM_G, FONT_BROWN_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the fg brown: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::Brown],
		FONT_BROWN_STCM_R, FONT_BROWN_STCM_G, FONT_BROWN_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the bg brown: %s", SDL_GetError());
		return false;
	}

	if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::Yellow],
		FONT_YELLOW_STCM_R, FONT_YELLOW_STCM_G, FONT_YELLOW_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the fg yellow: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::Yellow],
		FONT_YELLOW_STCM_R, FONT_YELLOW_STCM_G, FONT_YELLOW_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the bg yellow: %s", SDL_GetError());
		return false;
	}
	//--------
	if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::Blue],
		FONT_BLUE_STCM_R, FONT_BLUE_STCM_G, FONT_BLUE_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the fg blue: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::Blue],
		FONT_BLUE_STCM_R, FONT_BLUE_STCM_G, FONT_BLUE_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the bg blue: %s", SDL_GetError());
		return false;
	}

	if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::Purple],
		FONT_PURPLE_STCM_R, FONT_PURPLE_STCM_G, FONT_PURPLE_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the fg purple: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::Purple],
		FONT_PURPLE_STCM_R, FONT_PURPLE_STCM_G, FONT_PURPLE_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the bg purple: %s", SDL_GetError());
		return false;
	}

	if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::Cyan],
		FONT_CYAN_STCM_R, FONT_CYAN_STCM_G, FONT_CYAN_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the fg cyan: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::Cyan],
		FONT_CYAN_STCM_R, FONT_CYAN_STCM_G, FONT_CYAN_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the bg cyan: %s", SDL_GetError());
		return false;
	}

	if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::Gray],
		FONT_GRAY_STCM_R, FONT_GRAY_STCM_G,
			FONT_GRAY_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the fg light gray: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::Gray],
		FONT_GRAY_STCM_R, FONT_GRAY_STCM_G,
			FONT_GRAY_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the bg light gray: %s", SDL_GetError());
		return false;
	}

	//if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::LightGray],
	//	FONT_LIGHT_GRAY_STCM_R, FONT_LIGHT_GRAY_STCM_G,
	//		FONT_LIGHT_GRAY_STCM_B) < 0)
	//{
	//	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
	//		"Couldn't color the fg light gray: %s", SDL_GetError());
	//	return false;
	//}
	//if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::LightGray],
	//	FONT_LIGHT_GRAY_STCM_R, FONT_LIGHT_GRAY_STCM_G,
	//		FONT_LIGHT_GRAY_STCM_B) < 0)
	//{
	//	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
	//		"Couldn't color the bg light gray: %s", SDL_GetError());
	//	return false;
	//}
	//--------
	//if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::DarkGray],
	//	FONT_DARK_GRAY_STCM_R, FONT_DARK_GRAY_STCM_G,
	//		FONT_DARK_GRAY_STCM_B) < 0)
	//{
	//	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
	//		"Couldn't color the fg dark gray: %s", SDL_GetError());
	//	return false;
	//}
	//if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::DarkGray],
	//	FONT_DARK_GRAY_STCM_R, FONT_DARK_GRAY_STCM_G,
	//		FONT_DARK_GRAY_STCM_B) < 0)
	//{
	//	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
	//		"Couldn't color the bg dark gray: %s", SDL_GetError());
	//	return false;
	//}

	if (SDL_SetTextureColorMod(_fg_texture_map[FontColor::Black],
		FONT_BLACK_STCM_R, FONT_BLACK_STCM_G, FONT_BLACK_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the fg black: %s", SDL_GetError());
		return false;
	}
	if (SDL_SetTextureColorMod(_bg_texture_map[FontColor::Black],
		FONT_BLACK_STCM_R, FONT_BLACK_STCM_G, FONT_BLACK_STCM_B) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the bg black: %s", SDL_GetError());
		return false;
	}
	//--------
	return true;
	//--------
}

void TextHandlerSdl::draw_char(int c, const FgBgColorPair& color_pair,
	const PosVec2& draw_pos)
{
	const auto draw_char_fg_surface_size_2d
		= _get_draw_char_fg_surface_size_2d();
	const PosVec2
		c_tilemap_pos(c % draw_char_fg_surface_size_2d.x,
			c / draw_char_fg_surface_size_2d.x),

		c_real_pos(c_tilemap_pos.x * TILE_SIZE_2D.x,
			c_tilemap_pos.y * TILE_SIZE_2D.y),

		draw_real_pos(draw_pos.x * TILE_SIZE_2D.x,
			draw_pos.y * TILE_SIZE_2D.y);

	const sdl::Rect
		fg_src_rect(c_real_pos.x, c_real_pos.y, TILE_SIZE_2D.x,
			TILE_SIZE_2D.y),

		bg_src_rect(0, 0, TILE_SIZE_2D.x, TILE_SIZE_2D.y),

		//dst_rect(draw_real_pos.x * (*_zoom), draw_real_pos.y * (*_zoom),
		//	TILE_SIZE_2D.x * (*_zoom), TILE_SIZE_2D.y * (*_zoom));
		dst_rect(draw_real_pos.x, draw_real_pos.y,
			TILE_SIZE_2D.x, TILE_SIZE_2D.y);

	SDL_RenderCopy(*_renderer, _bg_texture_map.at(color_pair.bg),
		bg_src_rect, dst_rect);
	SDL_RenderCopy(*_renderer, _fg_texture_map.at(color_pair.fg),
		fg_src_rect, dst_rect);
}
PosVec2 TextHandlerSdl::_get_draw_char_fg_surface_size_2d() const
{
	return PosVec2(_fg_surface->w / TILE_SIZE_2D.x,
		_fg_surface->h / TILE_SIZE_2D.y);
}

} // namespace io
} // namespace dunwich_sandgeon
