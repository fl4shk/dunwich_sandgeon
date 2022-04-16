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

#include "floor_layout_comp_classes.hpp"
#include "../window_size_2d_constants.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace comp
{
//--------
const std::string
	StaticTileMap::KIND_STR("StaticTileMap"),

	StaticTileMap::TILE_WALL_DRAWABLE_DATA_STR("TileWall"),
	StaticTileMap::TILE_FLOOR_DRAWABLE_DATA_STR("TileFloor"),
	StaticTileMap::TILE_UP_STAIRS_DRAWABLE_DATA_STR("TileUpStairs"),
	StaticTileMap::TILE_DOWN_STAIRS_DRAWABLE_DATA_STR("TileDownStairs"),

	StaticTileMap::TILE_DOOR_DRAWABLE_DATA_STR("TileDoor"),
	StaticTileMap::TILE_PIT_DRAWABLE_DATA_STR("TilePit"),
	StaticTileMap::TILE_WATER_DRAWABLE_DATA_STR("TileWater"),
	StaticTileMap::TILE_SPIKES_DRAWABLE_DATA_STR("TileSpikes");

StaticTileMap::StaticTileMap()
	//: _data
	//({
	//	.data=std::vector<binser::VectorEx<Tile>>
	//	(
	//		PFIELD_WINDOW_SIZE_2D.y,
	//		{
	//			.data=std::vector<Tile>(PFIELD_WINDOW_SIZE_2D.x, Tile()),
	//			.checked_size=PFIELD_WINDOW_SIZE_2D.x
	//		}
	//	),
	//	.checked_size=PFIELD_WINDOW_SIZE_2D.y
	//})
{
	_init_data();
}
StaticTileMap::StaticTileMap(const binser::Value& bv)
{
	_init_data();
	MEMB_LIST_COMP_STATIC_LAYOUT(BINSER_MEMB_DESERIALIZE);
}
std::string StaticTileMap::kind_str() const
{
	return KIND_STR;
}
StaticTileMap::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_COMP_STATIC_LAYOUT(BINSER_MEMB_SERIALIZE);

	return ret;
}

void StaticTileMap::_init_data()
{
	_data
	= {
		.data=std::vector<binser::VectorEx<Tile>>
		(
			PFIELD_WINDOW_SIZE_2D.y,
			{
				.data=std::vector<Tile>(PFIELD_WINDOW_SIZE_2D.x, Tile()),
				.checked_size=PFIELD_WINDOW_SIZE_2D.x
			}
		),
		.checked_size=PFIELD_WINDOW_SIZE_2D.y
	};
}
//--------
//--------
const std::string
	DungeonGenDb::KIND_STR("DungeonGenDb");

auto DungeonGenDb::Room::from_bv(const binser::Value& bv) -> Room
{
	DungeonGenDb::Room ret;

	#define X(...) BINSER_MEMB_FROM_BV_DESERIALIZE(__VA_ARGS__)
	MEMB_AUTOSER_LIST_COMP_DUNGEON_GEN_DB_ROOM(X);
	#undef X

	if (PosVec2Ex temp_pos={.data=PosVec2(), .max=PFIELD_WINDOW_END_POS};
		true)
	{
		binser::get_bv_memb(temp_pos, bv, "pos", std::nullopt);
		ret.pos = std::move(temp_pos.data);
	}
	if (SizeVec2Ex temp_size_2d
		= {.data=SizeVec2(), .max=MAX_SIZE_2D, .min=MIN_SIZE_2D};
		true)
	{
		binser::get_bv_memb(temp_size_2d, bv, "size_2d", std::nullopt);
		ret.size_2d = std::move(temp_size_2d.data);
	}

	return ret;
}
DungeonGenDb::Room::operator binser::Value () const
{
	binser::Value ret;

	MEMB_TO_BV_LIST_COMP_DUNGEON_GEN_DB_ROOM(BINSER_MEMB_SERIALIZE);
	MEMB_AUTOSER_LIST_COMP_DUNGEON_GEN_DB_ROOM(BINSER_MEMB_SERIALIZE);

	return ret;
}

auto DungeonGenDb::Path::from_bv(const binser::Value& bv) -> Path
{
	DungeonGenDb::Path ret;

	#define X(...) BINSER_MEMB_FROM_BV_DESERIALIZE(__VA_ARGS__)
	MEMB_AUTOSER_LIST_COMP_DUNGEON_GEN_DB_PATH(X);
	#undef X

	if (PosVec2Ex temp_pos=PFIELD_WINDOW_EX_RANGE;
		true)
	{
		binser::get_bv_memb(temp_pos, bv, "pos", std::nullopt);
		ret.pos = std::move(temp_pos.data);
	}
	if (binser::ScalarEx<decltype(size)> temp_size
		={.data=0u, .max=MAX_SIZE, .min=MIN_SIZE};
		true)
	{
		binser::get_bv_memb(temp_size, bv, "size", std::nullopt);
		ret.size = std::move(temp_size.data);
	}

	return ret;
}
DungeonGenDb::Path::operator binser::Value () const
{
	binser::Value ret;

	MEMB_TO_BV_LIST_COMP_DUNGEON_GEN_DB_PATH(BINSER_MEMB_SERIALIZE);
	MEMB_AUTOSER_LIST_COMP_DUNGEON_GEN_DB_PATH(BINSER_MEMB_SERIALIZE);

	return ret;
}

DungeonGenDb::DungeonGenDb()
{
}
DungeonGenDb::DungeonGenDb(const binser::Value& bv)
{
	_room_vec.checked_size = MAX_NUM_ROOMS;
	_room_vec.cs_is_max = true;
	_room_vec.min_size = MIN_NUM_ROOMS;

	_path_vec.checked_size = MAX_NUM_PATHS;
	_path_vec.cs_is_max = true;
	_path_vec.min_size = MIN_NUM_PATHS;

	MEMB_LIST_COMP_DUNGEON_GEN_DB(BINSER_MEMB_DESERIALIZE);
}

std::string DungeonGenDb::kind_str() const
{
	return KIND_STR;
}
DungeonGenDb::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_COMP_DUNGEON_GEN_DB(BINSER_MEMB_SERIALIZE);

	return ret;
}
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon
