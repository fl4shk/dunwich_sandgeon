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

#ifndef src_game_engine_pfield_layer_prio_enum_hpp
#define src_game_engine_pfield_layer_prio_enum_hpp

// src/game_engine/pfield_layer_prio_enum.hpp

#include "../misc_includes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
enum class PfieldLayerPrio: i32 {
	//BgTilesMachs,	// this is for the `game_engine::lvgen_etc::BgTile`s,
	//				// and also generated machines (switches, gates, traps,
	//				// etc.)
	Bakgnd,
	//AltTerrain,
	ItemsTraps,		// traps and items; need to prevent traps from
					// occupying the same space as items in other logic
	CharsMachs,		// The player, NPCs, and monsters; machines

	Lim, // last member
};
constexpr inline bool pflprio_is_upper_layer(PfieldLayerPrio priority) {
	return (
		//priority == PfieldLayerPrio::ItemsTraps
		//|| priority == PfieldLayerPrio::CharsMachs
		priority > PfieldLayerPrio::Bakgnd
	);
}
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_pfield_layer_prio_enum_hpp
