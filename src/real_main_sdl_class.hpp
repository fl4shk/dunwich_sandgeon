#ifndef src_real_main_sdl_class_hpp
#define src_real_main_sdl_class_hpp

// src/real_main_sdl_class.hpp

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

class RealMainSdl final
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
	// These constants have values in amount of tilemap entries
	static const Vec2<int> SCREEN_TM_SIZE_2D, PLAYFIELD_TM_POS,
		PLAYFIELD_TM_SIZE_2D;
	// Default values for some member variables
	static const Vec2<int> DEF_SCREEN_SIZE_2D;
	static constexpr int DEF_ZOOM = 2;
	static const std::map<FontColor, std::string> COLOR_TO_STR_MAP;
public:		// types
	enum class InputKind
	{
		MoveLeft,
		MoveUp,
		MoveRight,
		MoveDown,

		TargetEnemy,
		TargetItem,

		ExitMenu,
		OpenInvMenu,
		OpenSaveMenu,

		ZoomIn,
		ZoomOut,
	};

private:		// variables
	Vec2<int> _screen_size_2d;
	int _zoom = DEF_ZOOM;
	sdl::Window _window;
	sdl::Renderer _renderer;
	sdl::Surface _font_surface;
	std::map<FontColor, sdl::Texture> _font_texture_map;
	sdl::KeyStatusMap _key_status_map;
	InputKind _input_kind;
public:		// functions
	RealMainSdl() = default;
	~RealMainSdl() = default;

	int run();

private:		// functions
	inline KeyStatus& _key_stat(const KeycModPair& kmp)
	{
		return _key_status_map.at(kmp);
	}
	inline Vec2<int> _get_draw_char_font_surface_size_2d()
	{
		return Vec2<int>(_font_surface->w / TILE_SIZE_2D.x,
			_font_surface->h / TILE_SIZE_2D.y);
	}
	void _draw_char(int c, FontColor color, const Vec2<int>& draw_pos);
};

} // namespace dungwich_sandeon

#endif		// src_real_main_sdl_class_hpp
