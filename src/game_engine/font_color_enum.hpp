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

#ifndef src_game_engine_font_color_enum_hpp
#define src_game_engine_font_color_enum_hpp

// src/game_engine/font_color_enum.hpp

#include "../misc_includes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{

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
	LightGray,

	DarkGray,
	Black,

	// The limit, which is not a real FontColor 
	Lim,
};

inline FontColor font_color_add(FontColor font_color, u32 amount)
{
	u32 ret_u32 = static_cast<u32>(font_color);
	ret_u32 += amount;
	return static_cast<FontColor>(ret_u32);
}

extern const std::map<FontColor, std::string> FONT_COLOR_TO_STR_MAP;

class FgBgColorPair final
{
public:		// constants
	static constexpr FontColor
		DEFAULT_FG = FontColor::White,
		DEFAULT_BG = FontColor::Black;
public:		// types
	class CtorArgs final
	{
	public:		// variables
		FontColor fg, bg;
	};
public:		// variables
	FontColor fg = DEFAULT_FG, bg = DEFAULT_BG;
public:		// functions
	constexpr inline FgBgColorPair() = default;
	constexpr inline FgBgColorPair(CtorArgs s_fg_and_bg)
		: fg(s_fg_and_bg.fg), bg(s_fg_and_bg.bg)
	{
	}
	constexpr inline FgBgColorPair(FontColor s_fg,
		FontColor s_bg=DEFAULT_BG)
		: fg(s_fg), bg(s_bg)
	{
	}
	GEN_CONSTEXPR_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(FgBgColorPair);
	constexpr inline ~FgBgColorPair() = default;

	constexpr inline FgBgColorPair& operator = (FontColor n_fg)
	{
		fg = n_fg;
		bg = DEFAULT_BG;
		return *this;
	}

	constexpr inline bool operator == (const FgBgColorPair& other) const
	{
		return ((fg == other.fg) && (bg == other.bg));
	}
	constexpr inline bool operator != (const FgBgColorPair& other) const
	{
		return (!((*this) == other));
	}
};

} // namespace game_engine
} // namespace dungwich_sandeon


#endif		// src_game_engine_font_color_enum_hpp
