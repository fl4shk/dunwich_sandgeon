// This file is part of Dungwich Sandeon.
// 
// Copyright 2022 FL4SHK
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

#ifndef src_game_engine_playfield_layer_prio_enum_hpp
#define src_game_engine_playfield_layer_prio_enum_hpp

// src/game_engine/playfield_layer_prio_enum.hpp

#include "../misc_includes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{

enum class PlayfieldLayerPrio: uint
{
	Block,
	Item,
	Char,
};

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_playfield_layer_prio_enum_hpp
