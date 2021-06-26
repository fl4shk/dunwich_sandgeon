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

class Engine;

namespace comp
{

class Drawable final: public ecs::Comp
{
public:		// variables
	int c = ' ';
	FontColor color = FontColor::White;
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

class Position final: public ecs::Comp
{
public:		// variables
	PosVec2 pos;
public:		// functions
	Position() = default;
	inline Position(const PosVec2& s_pos)
		: pos(s_pos)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Position);
	virtual ~Position() = default;

	virtual std::string kind_str() const;
};

class Weight final: public ecs::Comp
{
public:		// variables
	uint val = 0;
public:		// functions
	Weight() = default;
	inline Weight(uint s_val)
		: val(s_val)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Weight);
	virtual ~Weight() = default;

	virtual std::string kind_str() const;
};

class BaseStats final: public ecs::Comp
{
public:		// constants
	static constexpr uint MAX_VAL = 999,
		DEFAULT_HP = 50,
		DEFAULT_ATK = 20,
		DEFAULT_DEF = 20,
		DEFAULT_MAG_ATK = 20,
		DEFAULT_MAG_DEF = 20;
public:		// variables
	uint hp = DEFAULT_HP,
		atk = DEFAULT_ATK,
		def = DEFAULT_DEF,
		mag_atk = DEFAULT_MAG_ATK,
		mag_def = DEFAULT_MAG_DEF;
public:		// functions
	BaseStats() = default;
	inline BaseStats(uint s_hp, uint s_atk, uint s_def, uint s_mag_atk,
		uint s_mag_def)
		: hp(s_hp), atk(s_atk), def(s_def), mag_atk(s_mag_atk),
		mag_def(s_mag_def)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(BaseStats);
	virtual ~BaseStats() = default;

	virtual std::string kind_str() const;
};


} // namespace comp

} // namespace game_engine

} // namespace dungwich_sandeon

#endif		// src_game_engine_general_comp_classes_hpp
