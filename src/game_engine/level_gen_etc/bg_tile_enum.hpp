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

#ifndef src_game_engine_level_gen_etc_bg_tile_enum_hpp
#define src_game_engine_level_gen_etc_bg_tile_enum_hpp

// src/game_engine/level_gen_etc/bg_tile_enum.hpp

#include "../../misc_includes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
#define LIST_OF_ALT_TERRAIN_BG_TILES(X) \
	X(Water) \
	X(Lava) \
	X(Pit) \
	X(Spikes) \

#define LIST_OF_BG_TILES(X) \
	X(Blank) \
	X(Error) \
	\
	X(Wall) \
	X(Door) \
	\
	X(RoomFloor) \
	X(PathFloor) \
	/* X(Floor) */ \
	LIST_OF_ALT_TERRAIN_BG_TILES(X) \
	\
	X(UpStairs) \
	X(DownStairs) \

enum class BgTile: u8 {
	#define X(name) \
		name ,
	LIST_OF_BG_TILES(X)
	#undef X
};

using BgTileUset = std::unordered_set<BgTile>;
extern const BgTileUset
	BASIC_NO_PASS_BG_TILE_USET,
	BASIC_UNSAFE_BG_TILE_USET;
	//PLAYER_UNSAFE_BG_TILE_USET;
//inline bool bg_tile_is_player_unsafe(BgTile bg_tile) {
//	//return (bg_tile == BgTile::Pit
//	//	|| bg_tile == BgTile::Lava
//	//	|| bg_tile == BgTile::Spikes);
//	return PLAYER_UNSAFE_BG_TILE_USET.contains(bg_tile);
//}

//extern const std::unordered_map<BgTile, std::string>& bg_tile_str_map();
constexpr inline std::string bg_tile_str_map_at(BgTile bg_tile) {
	switch (bg_tile) {
		#define X(name) \
			case BgTile:: name : \
				return "game_engine::level_gen_etc::BgTile::" #name ; \
				break;
		LIST_OF_BG_TILES(X)
		#undef X

		default:
			throw std::invalid_argument(sconcat
				("game_engine::level_gen_etc::bg_tile_str_map_at(): ",
				"Internal Error: "
				"Invalid `bg_tile`: ", i32(bg_tile)));
			return "";
			break;
	}
}

using SizeAndBgTile = std::pair<size_t, BgTile>;

template<typename T>
concept IsBuildBgTileVecArg
	= (std::same_as<T, level_gen_etc::BgTile>
	|| std::same_as<T, SizeAndBgTile>);

constexpr inline void _build_bg_tile_vec_backend(
	std::vector<BgTile>& ret, BgTile first_arg
) {
	ret.push_back(first_arg);
}
constexpr inline void _build_bg_tile_vec_backend(
	std::vector<BgTile>& ret, const SizeAndBgTile& first_arg
) {
	for (size_t i=0; i<first_arg.first; ++i) {
		ret.push_back(first_arg.second);
	}
}
constexpr inline std::vector<BgTile> build_bg_tile_vec(
	const IsBuildBgTileVecArg auto&... args
) {
	std::vector<BgTile> ret;

	(_build_bg_tile_vec_backend(ret, args), ...);

	return ret;
}
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_level_gen_etc_bg_tile_enum_hpp
