#ifndef src_real_main_class_hpp
#define src_real_main_class_hpp

// src/real_main_class.hpp

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

#include "misc_includes.hpp"

namespace dungwich_sandeon
{

class RealMain final
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
	static const Vec2<int> SCREEN_SIZE_2D, TILE_SIZE_2D;
	static const std::map<FontColor, std::string> COLOR_TO_STR_MAP;
private:		// variables
	sdl::Window _window;
	sdl::Renderer _renderer;
	sdl::Surface _font_surface;
	std::map<FontColor, sdl::Texture> _font_texture_map;
public:		// functions
	RealMain() = default;
	~RealMain() = default;

	int run();

private:		// functions
	inline Vec2<int> _get_draw_char_font_surface_size_2d()
	{
		return Vec2<int>(_font_surface->w / TILE_SIZE_2D.x,
			_font_surface->h / TILE_SIZE_2D.y);
	}
	void _draw_char(int c, FontColor color, const Vec2<int>& draw_pos);
};

} // namespace dungwich_sandeon

#endif		// src_real_main_class_hpp
