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

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
DijkstraMapGen::DijkstraMapGen() {}
DijkstraMapGen::~DijkstraMapGen() {}
//--------
DijkstraMapGen& DijkstraMapGen::add(const IntVec2& pos, float val) {
	//_goal_vec.push_back({.pos=pos, .val=val});
	_goal_umap.insert(std::pair(pos, val));
	return *this;
}
//--------
auto DijkstraMapGen::gen_basic(const FloorLayout& floor_layout) const
-> Dmap {
	Dmap ret;

	for (const auto& pair: _goal_umap) {
		const auto& bg_tile = floor_layout.phys_bg_tile_at(pair.first);
	}

	return ret;
}
auto DijkstraMapGen::gen_flipped(const FloorLayout& floor_layout) const
-> Dmap {
	Dmap ret = gen_basic(floor_layout);

	for (auto& pair: ret) {
		pair.second *= FLIP_SCALE;
	}

	return ret;
}
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
