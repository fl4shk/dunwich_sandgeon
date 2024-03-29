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

#include "bg_tile_enum.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace lvgen_etc {
//--------
//const std::unordered_map<BgTile, std::string>& bg_tile_str_map() {
//	//--------
//	static const std::unordered_map<BgTile, std::string>
//		BG_TILE_STR_MAP = {
//		//{Tile::Wall, "TileWall"},
//		//{Tile::Floor, "TileFloor"},
//		//{Tile::UpStairs, "TileUpStairs"},
//		//{Tile::DownStairs, "TileDownStairs"},
//
//		//{Tile::Door, "TileDoor"},
//		//{Tile::Pit, "TilePit"},
//		//{Tile::Water, "TileWater"},
//		//{Tile::Spikes, "TileSpikes"},
//		#define X(name) { BgTile:: name, "BgTile" #name },
//		LIST_OF_BG_TILE(X)
//		#undef X
//	};
//	//--------
//	return BG_TILE_STR_MAP;
//	//--------
//}
//--------
const BgTileUset
	// Stay in a `RoomTunnel`
	RT_BRDR_BG_TILE_USET = {
		BgTile::Blank,
		BgTile::Error,
		BgTile::Wall,
	},
	BASIC_NO_PASS_BG_TILE_USET = {
		BgTile::Blank,
		BgTile::Error,
		BgTile::Wall,
		BgTile::Spikes,
		BgTile::Pit,
		BgTile::Lava,
	},
	BASIC_UNSAFE_BG_TILE_USET = {
		BgTile::Spikes,
		BgTile::Pit,
		BgTile::Lava,
	},
	WALKABLE_NO_ITEMS_TRAPS_BG_TILE_USET = {
		#define X(arg) \
			BgTile::arg,
		LIST_OF_WALKABLE_NO_ITEMS_TRAPS_BG_TILES(X)
		#undef X
	},
	ALT_TERRAIN_BG_TILE_USET = {
		#define X(arg) \
			BgTile::arg,
		LIST_OF_ALT_TERRAIN_BG_TILES(X)
		#undef X
	},
	ANY_DOOR_BG_TILE_USET = {
		BgTile::Door,
		BgTile::LockedDoor,
		//BgTile::BossDoor,
	},
	LOCK_BG_TILE_USET = {
		BgTile::LockedDoor,
	};
	//ANY_LOCKED_BG_TILE_USET = {
	//	BgTile::LockedDoor,
	//	BgTile::BossDoor,
	//},
	//BOSS_LOCKED_BG_TILE_USET = {
	//	BgTile::BossDoor,
	//};
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
