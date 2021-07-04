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
public:		// constants
	static const PosVec2 TILE_SIZE_2D;
private:		// variables
	sdl::Surface _font_surface;
	std::map<FontColor, sdl::Texture> _font_texture_map;
	sdl::Renderer* _renderer = nullptr;
	int* _zoom = nullptr;
public:		// functions
	TextHandlerSdl() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(TextHandlerSdl);
	~TextHandlerSdl() = default;

	bool init(sdl::Renderer& s_renderer, int& s_zoom);
	void draw_char(int c, FontColor color, const PosVec2& draw_pos);
private:		// functions
	PosVec2 _get_draw_char_font_surface_size_2d() const;
};

} // namespace io
} // namespace dungwich_sandeon

#endif		// src_sdl_text_handler_sdl_class_hpp
