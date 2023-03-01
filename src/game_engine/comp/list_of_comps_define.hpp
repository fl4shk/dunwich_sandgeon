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

#ifndef src_game_engine_comp_list_of_comps_define_hpp
#define src_game_engine_comp_list_of_comps_define_hpp

// src/game_engine/comp/list_of_comps_define.hpp

#include "../../misc_includes.hpp"

#define LIST_OF_COMPS \
	comp::Drawable, \
	comp::Position, \
	comp::BaseStats, \
	\
	comp::Player, \
	\
	/* comp::Wall, */ \
	/* comp::Floor, */ \
	/* comp::DownStairs, */ \
	/* comp::UpStairs, */ \
	/* comp::StaticBgTileMap, */\
	/* comp::DngnFloor, */ \
	\
	comp::StatusOnFire, \
	comp::StatusPoisoned, \
	comp::StatusAsleep, \
	comp::StatusTravelSpeed, \
	comp::StatusActionSpeed

#endif		// src_game_engine_comp_list_of_comps_define_hpp
