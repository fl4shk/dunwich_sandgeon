// This file is part of Dunwich Sandgeon.
// 
// Copyright 2023 FL4SHK
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

#ifndef src_game_engine_comp_player_comp_class_hpp
#define src_game_engine_comp_player_comp_class_hpp

// src/game_engine/comp/player_comp_class.hpp

#include "../../misc_includes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace comp {
//--------
class Player final: public ecs::Comp {
public:		// constants
	static const std::string KIND_STR;
	static constexpr i32
		MAX_LEVEL = 100,
		DEFAULT_LEVEL = 1,

		MAX_EXP = 99,
		DEFAULT_EXP = 0,

		MAX_HUNGER = 100,
		DEFAULT_HUNGER = 100,

		MAX_WEIGHT = 100,
		DEFAULT_WEIGHT = 0;
public:		// variables
	#define MEMB_LIST_COMP_PLAYER(X) \
		X(level, std::nullopt) \
		X(exp, std::nullopt) \
		X(hunger, std::nullopt) \
		X(weight, std::nullopt) \

	i32
		level = DEFAULT_LEVEL,
		exp = DEFAULT_EXP,
		hunger = DEFAULT_HUNGER,
		weight = DEFAULT_WEIGHT;
public:		// functions
	inline Player() = default;
	Player(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Player);
	virtual ~Player() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;
};
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_comp_player_comp_class_hpp
