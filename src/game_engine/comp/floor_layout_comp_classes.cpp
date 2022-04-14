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

StaticTileMap::StaticTileMap(const binser::Value& bv)
{
	MEMB_LIST_COMP_STATIC_LAYOUT(BINSER_MEMB_DESERIALIZE);
}
std::string StaticTileMap::kind_str() const
{
	return KIND_STR;
}
StaticTileMap::operator binser::Value() const
{
	binser::Value ret;

	MEMB_LIST_COMP_STATIC_LAYOUT(BINSER_MEMB_SERIALIZE);

	return ret;
}

} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon
