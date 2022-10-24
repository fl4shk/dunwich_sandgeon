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

#include "dijkstra_map_gen_class.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
//const BgTileUset
//	DijkstraMapGen::DEFAULT_NO_PASS_USET = {
//		BgTile::Wall,
//		BgTile::Pit,
//		BgTile::Lava,
//	};
//--------
DijkstraMapGen::DijkstraMapGen() {}
DijkstraMapGen::~DijkstraMapGen() {}
//--------
DijkstraMapGen& DijkstraMapGen::add(const IntVec2& pos, float val) {
	_goal_vec.push_back({.pos=pos, .val=val});
	//_goal_umap.insert(std::pair(pos, val));
	return *this;
}
//--------
auto DijkstraMapGen::gen_basic(
	const FloorLayout& floor_layout, const BgTileUset& no_pass_uset
) const
-> Dmap {
	Dmap ret(PFIELD_PHYS_SIZE_2D.y,
		std::vector<float>(PFIELD_PHYS_SIZE_2D.x, VERY_HIGH_NUM));

	//for (const auto& pair: _goal_umap) {
	//	const auto& bg_tile = floor_layout.phys_bg_tile_at(pair.first);
	//	if (bg_tile) {
	//		ret.insert(std::pair(pair.first, *bg_tile));
	//	}
	//}
	//for (const auto& goal: _goal_vec)

	// Insert goals
	for (size_t i=0; i<_goal_vec.size(); ++i) {
		const auto& goal = _goal_vec.at(i);
		if (ret.at(goal.pos.y).at(goal.pos.x) == goal.val) {
			throw std::runtime_error(sconcat
				("game_engine::level_gen_etc::DijkstraMapGen: Eek! ",
				i, ": ", goal.pos, " ", goal.val));
		}
	}

	return ret;
}
auto DijkstraMapGen::gen_flipped(
	const FloorLayout& floor_layout, const BgTileUset& no_pass_uset,
	float bonus
) const -> Dmap {
	Dmap ret = gen_basic(floor_layout, no_pass_uset);
	flip(ret, bonus);
	return ret;
}
auto DijkstraMapGen::flip(Dmap& dmap, float bonus) const -> Dmap& {
	for (auto& row: dmap) {
		for (auto& item: row) {
			item *= -1.0f - std::abs(bonus);
		}
	}

	return dmap;
}
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
