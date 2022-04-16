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

DungeonGenDb::Room DungeonGenDb::Room::from_bv(const binser::Value& bv)
{
	DungeonGenDb::Room ret;

	MEMB_LIST_COMP_DUNGEON_GEN_DB_ROOM(BINSER_MEMB_FROM_BV_DESERIALIZE);

	return ret;
}
DungeonGenDb::Room::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_COMP_DUNGEON_GEN_DB_ROOM(BINSER_MEMB_SERIALIZE);

	return ret;
}

DungeonGenDb::Path DungeonGenDb::Path::from_bv(const binser::Value& bv)
{
	DungeonGenDb::Path ret;

	MEMB_LIST_COMP_DUNGEON_GEN_DB_PATH(BINSER_MEMB_FROM_BV_DESERIALIZE);

	return ret;
}
DungeonGenDb::Path::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_COMP_DUNGEON_GEN_DB_PATH(BINSER_MEMB_SERIALIZE);

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
