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

#include "static_layout_comp_class.hpp"
#include "../window_size_2d_constants.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace comp
{

const std::string
	StaticLayout::KIND_STR("StaticLayout"),

	StaticLayout::TILE_WALL_DRAW_DATA_STR("TileWall"),
	StaticLayout::TILE_FLOOR_DRAW_DATA_STR("TileFloor"),
	StaticLayout::TILE_UP_STAIRS_DRAW_DATA_STR("TileUpStairs"),
	StaticLayout::TILE_DOWN_STAIRS_DRAW_DATA_STR("TileDownStairs"),

	StaticLayout::TILE_DOOR_DRAW_DATA_STR("TileDoor"),
	StaticLayout::TILE_PIT_DRAW_DATA_STR("TilePit"),
	StaticLayout::TILE_WATER_DRAW_DATA_STR("TileWater"),
	StaticLayout::TILE_SPIKES_DRAW_DATA_STR("TileSpikes");

StaticLayout::StaticLayout(const binser::Value& bv)
{
	MEMB_LIST_COMP_STATIC_LAYOUT(BINSER_MEMB_DESERIALIZE);
}
std::string StaticLayout::kind_str() const
{
	return KIND_STR;
}
StaticLayout::operator binser::Value() const
{
	binser::Value ret;

	MEMB_LIST_COMP_STATIC_LAYOUT(BINSER_MEMB_SERIALIZE);

	return ret;
}

} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon
