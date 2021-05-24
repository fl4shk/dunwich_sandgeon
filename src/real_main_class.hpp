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
	enum class Color: u32
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

		Lim,
	};
public:		// functions
	static inline Color color_add(Color color, u32 amount)
	{
		u32 ret_u32 = static_cast<u32>(color);
		ret_u32 += amount;
		return static_cast<Color>(ret_u32);
	}
public:		// constants
	static constexpr int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;
	static const std::map<Color, std::string> COLOR_TO_STR_MAP;
private:		// variables
	sdl::Window _window;
	sdl::Renderer _renderer;
	std::map<Color, sdl::Texture> _font_texture_map;
public:		// functions
	RealMain() = default;
	~RealMain() = default;

	int run();

private:		// functions
};

} // namespace dungwich_sandeon

#endif		// src_real_main_class_hpp
