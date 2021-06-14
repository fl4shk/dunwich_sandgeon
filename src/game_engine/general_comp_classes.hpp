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

#ifndef src_game_engine_general_comp_classes_hpp
#define src_game_engine_general_comp_classes_hpp

// src/game_engine/general_comp_classes.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"
#include "font_color_enum.hpp"

namespace dungwich_sandeon
{

namespace game_engine
{

class Position: public ecs::Comp
{
public:		// variables
	PosVec2 pos;
public:		// functions
	Position() = default;
	inline Position(const PosVec2& s_pos)
		: pos(s_pos)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Position)
	virtual ~Position() = default;

	virtual std::string kind_str() const;
};

class Drawable: public ecs::Comp
{
public:		// variables
	int c;
	FontColor color;
public:		// functions
	Drawable() = default;
	inline Drawable(int s_c, FontColor s_color)
		: c(s_c), color(s_color)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Drawable);
	virtual ~Drawable() = default;

	virtual std::string kind_str() const;
};

} // namespace game_engine

} // namespace dungwich_sandeon

#endif		// src_game_engine_general_comp_classes_hpp
