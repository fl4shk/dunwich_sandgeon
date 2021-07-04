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

#ifndef src_game_engine_player_comp_class_hpp
#define src_game_engine_player_comp_class_hpp

// src/game_engine/player_comp_class.hpp

#include "../misc_includes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

class Player final: public ecs::Comp
{
public:		// functions
	inline Player() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Player);
	virtual ~Player() = default;

	virtual std::string kind_str() const;
};

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_player_comp_class_hpp
