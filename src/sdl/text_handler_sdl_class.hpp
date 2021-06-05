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

namespace dungwich_sandeon
{

namespace io
{

class RealMainSdl;

class TextHandlerSdl final
{
public:		// types
	enum class FontColor: u32
	{
		White,

		Red,
		Green,
		Brown,
		Yellow,

		Blue,
		Purple,
		Cyan,
		Gray,

		// The limit, which is not a real font_color 
		Lim,
	};
public:		// functions
	static inline FontColor font_color_add(FontColor font_color,
		u32 amount)
	{
		u32 ret_u32 = static_cast<u32>(font_color);
		ret_u32 += amount;
		return static_cast<FontColor>(ret_u32);
	}
public:		// constants
	static const Vec2<int> TILE_SIZE_2D;
	static const std::map<FontColor, std::string> COLOR_TO_STR_MAP;
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
	void draw_char(int c, FontColor color, const Vec2<int>& draw_pos);
private:		// functions
	Vec2<int> _get_draw_char_font_surface_size_2d() const;
};

} // namespace io

} // namespace dungwich_sandeon

#endif		// src_sdl_text_handler_sdl_class_hpp
