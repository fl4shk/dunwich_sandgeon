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

#ifndef src_game_engine_sys_gm_dungeon_gen_class_hpp
#define src_game_engine_sys_gm_dungeon_gen_class_hpp

// src/game_engine/sys/gm_dungeon_gen_class.hpp

#include "../../misc_includes.hpp"
#include "../comp/floor_layout_comp_classes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace sys {
//--------
// Game Mode: Dungeon Generation
class GmDungeonGen final: public ecs::Sys {
public:		// types
	//// A `class` representing the next
	//class GenInfo final {
	//public:		// variables
	//	i32 conn_index = 0;
	//};
	//--------
	static constexpr i32
		MIN_NUM_ROOM_PATHS = comp::DungeonGen::MIN_NUM_ROOM_PATHS,
		MAX_NUM_ROOM_PATHS = comp::DungeonGen::MAX_NUM_ROOM_PATHS;
	//--------
	static constexpr i32
		PATH_THICKNESS = comp::DungeonGen::RoomPath::PATH_THICKNESS,
		PATH_MIN_LEN = comp::DungeonGen::RoomPath::PATH_MIN_LEN,
		PATH_MAX_LEN = comp::DungeonGen::RoomPath::PATH_MAX_LEN;

	static constexpr IntVec2
		ROOM_MIN_SIZE_2D = comp::DungeonGen::RoomPath::ROOM_MIN_SIZE_2D,
		ROOM_MAX_SIZE_2D = comp::DungeonGen::RoomPath::ROOM_MAX_SIZE_2D;
	//--------
	static constexpr i32
		// Generation percentages and stuff. 
		//PATH_THRESH_MIN = 0,
		//PATH_THRESH_MAX = 0,
		//ROOM_THRESH_MIN = 1,
		//ROOM_THRESH_MAX = 1,
		GEN_TYPE_PATH = 0, MIN_GEN_TYPE = GEN_TYPE_PATH,
		GEN_TYPE_ROOM = 1, MAX_GEN_TYPE = GEN_TYPE_ROOM,

		GEN_SIDE_L = 0, MIN_GEN_SIDE = GEN_SIDE_L,
		GEN_SIDE_T = 1,
		GEN_SIDE_R = 2,
		GEN_SIDE_B = 3, MAX_GEN_SIDE = GEN_SIDE_B,

		GEN_NEXT_SAME_MIN = 0, MIN_GEN_NEXT = GEN_NEXT_SAME_MIN,
		GEN_NEXT_SAME_MAX = 2,
		GEN_NEXT_DIFFERENT_MIN = 3,
		GEN_NEXT_DIFFERENT_MAX = 9, MAX_GEN_NEXT = GEN_NEXT_DIFFERENT_MAX,

		// This is the number of tries to attempt room/path generation
		// after failing to generate a valid one.
		GEN_RP_MAX_TRIES = 20;
		//--------
public:		// constants
	static const std::string
		KIND_STR;
private:		// variables
	std::optional<ecs::EntId>
		_bg_tile_map_id,
		_dungeon_gen_id;

	i32
		_attempted_num_rp = 0;
public:		// functions
	GmDungeonGen() = default;
	//inline GmDungeonGen(const binser::Value& bv)
	//	: ecs::Sys(bv) {
	//}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GmDungeonGen);
	virtual ~GmDungeonGen() = default;

	virtual std::string kind_str() const;

	void clear_dungeon_gen(ecs::Engine* ecs_engine);
private:		// functions
	virtual void _init(ecs::Engine* ecs_engine);
public:		// functions
	virtual void tick(ecs::Engine* ecs_engine);
private:		// functions
	void _gen_single_rp(comp::DungeonGen* dungeon_gen);
	//void _connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
	//	comp::DungeonGen* dungeon_gen);
};
//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_sys_gm_dungeon_gen_class_hpp
