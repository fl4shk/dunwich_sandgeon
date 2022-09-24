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

#ifndef src_game_engine_font_color_enum_hpp
#define src_game_engine_font_color_enum_hpp

// src/game_engine/font_color_enum.hpp

#include "../misc_includes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{

enum class FontColor: i32
{
	White,

	Red,
	Green,
	Brown,
	Yellow,

	Blue,
	Purple,
	Cyan,
	//LightGray,
	Gray,

	//DarkGray,
	Black,

	// The limit, which is not a real FontColor 
	Lim,
};

inline FontColor font_color_add(FontColor font_color, i32 amount)
{
	i32 ret_u32 = i32(font_color);
	ret_u32 += amount;
	return FontColor(ret_u32);
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
	#define MEMB_LIST_FG_BG_COLOR_PAIR(X) \
		X(fg, std::nullopt) \
		X(bg, std::nullopt) \

	FontColor
		fg = DEFAULT_FG,
		bg = DEFAULT_BG;
public:		// functions
	constexpr inline FgBgColorPair() = default;
	constexpr inline FgBgColorPair(CtorArgs ctor_args)
		: fg(ctor_args.fg), bg(ctor_args.bg)
	{
	}
	constexpr inline FgBgColorPair(FontColor s_fg,
		FontColor s_bg=DEFAULT_BG)
		: fg(s_fg), bg(s_bg)
	{
	}
	//constexpr 
	inline FgBgColorPair(const binser::Value& bv)
	{
		fg = FontColor(bv.at("fg").get<i32>());
		bg = FontColor(bv.at("bg").get<i32>());
	}
	GEN_CX_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(FgBgColorPair);
	constexpr inline ~FgBgColorPair() = default;

	constexpr inline FgBgColorPair& operator = (FontColor n_fg)
	{
		fg = n_fg;
		bg = DEFAULT_BG;
		return *this;
	}
	inline operator binser::Value () const
	{
		binser::Value ret;

		ret.insert("fg", i32(fg));
		ret.insert("bg", i32(bg));

		return ret;
	}

	constexpr inline bool operator == (const FgBgColorPair& other) const
	{
		return fg == other.fg && bg == other.bg;
	}
	constexpr inline bool operator != (const FgBgColorPair& other) const
	{
		return !(*this == other);
	}
};

} // namespace game_engine
} // namespace dunwich_sandgeon


#endif		// src_game_engine_font_color_enum_hpp
