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

#ifndef src_sdl_text_handler_sdl_class_hpp
#define src_sdl_text_handler_sdl_class_hpp

// src/sdl/text_handler_sdl_class.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"
#include "../game_engine/font_color_enum.hpp"

namespace dungwich_sandeon
{
namespace io
{

class RealMainSdl;

class TextHandlerSdl final
{
public:		// types
	using FontColor = game_engine::FontColor;
	using FgBgColorPair = game_engine::FgBgColorPair;
public:		// constants
	static const SizeVec2 TILE_SIZE_2D;

	static constexpr int
		//--------
		FONT_RED_STCM_R = 0xdd,
		FONT_RED_STCM_G = 0x0,
		FONT_RED_STCM_B = 0x0,

		FONT_GREEN_STCM_R = 0x0,
		FONT_GREEN_STCM_G = 0xdd,
		FONT_GREEN_STCM_B = 0x0,

		FONT_BROWN_STCM_R = 0xc0,
		FONT_BROWN_STCM_G = 0x66,
		FONT_BROWN_STCM_B = 0x20,

		FONT_YELLOW_STCM_R = 0xdd,
		FONT_YELLOW_STCM_G = 0xdd,
		FONT_YELLOW_STCM_B = 0x00,
		//--------
		FONT_BLUE_STCM_R = 0x64,
		FONT_BLUE_STCM_G = 0x64,
		FONT_BLUE_STCM_B = 0xff,

		FONT_PURPLE_STCM_R = 0xdd,
		FONT_PURPLE_STCM_G = 0x00,
		FONT_PURPLE_STCM_B = 0xdd,

		FONT_CYAN_STCM_R = 0x00,
		FONT_CYAN_STCM_G = 0xdd,
		FONT_CYAN_STCM_B = 0xdd,

		FONT_GRAY_STCM_R = 0x98,
		FONT_GRAY_STCM_G = 0x98,
		FONT_GRAY_STCM_B = 0x98,

		//FONT_LIGHT_GRAY_STCM_R = 0xb0,
		//FONT_LIGHT_GRAY_STCM_G = 0xb0,
		//FONT_LIGHT_GRAY_STCM_B = 0xb0,
		////FONT_LIGHT_GRAY_STCM_R = 0xa0,
		////FONT_LIGHT_GRAY_STCM_G = 0xa0,
		////FONT_LIGHT_GRAY_STCM_B = 0xa0,
		//--------
		//FONT_DARK_GRAY_STCM_R = 0x80,
		//FONT_DARK_GRAY_STCM_G = 0x80,
		//FONT_DARK_GRAY_STCM_B = 0x80,
		////FONT_DARK_GRAY_STCM_R = 0x60,
		////FONT_DARK_GRAY_STCM_G = 0x60,
		////FONT_DARK_GRAY_STCM_B = 0x60,

		FONT_BLACK_STCM_R = 0x00,
		FONT_BLACK_STCM_G = 0x00,
		FONT_BLACK_STCM_B = 0x00;
		//--------
private:		// variables
	sdl::Surface _fg_surface, _bg_surface;
	std::map<FontColor, sdl::Texture> _fg_texture_map, _bg_texture_map;
	sdl::Renderer* _renderer = nullptr;
	//int* _zoom = nullptr;
public:		// functions
	TextHandlerSdl() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(TextHandlerSdl);
	~TextHandlerSdl() = default;

	//bool init(sdl::Renderer& s_renderer, int& s_zoom);
	bool init(sdl::Renderer& s_renderer);

	void draw_char(int c, const FgBgColorPair& color_pair,
		const PosVec2& draw_pos);
	inline void draw_char(int c, FontColor fg_color,
		const PosVec2& draw_pos)
	{
		draw_char(c, FgBgColorPair(fg_color), draw_pos);
	}
private:		// functions
	PosVec2 _get_draw_char_fg_surface_size_2d() const;
};

} // namespace io
} // namespace dungwich_sandeon

#endif		// src_sdl_text_handler_sdl_class_hpp
