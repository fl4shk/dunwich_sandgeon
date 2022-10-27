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

#include "path_class.hpp"
#include "bg_tile_enum.hpp"
#include "floor_layout_class.hpp"
#include "dijkstra_map_gen_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
Path::Path() {
}
Path::Path(const IntVec2& start_pos) {
	_data.push_back(start_pos);
}
Path::~Path() {
}

Path& Path::add(const FloorLayout& floor_layout, PathDir dir) {
	//--------
	if (size() == 0) {
		throw std::runtime_error(sconcat
			("game_engine::level_gen_etc::Path::add(): ",
			"Internal Error: ",
			"`size() == 0`"));
	}
	//--------
	const IntVec2 pos = path_dir_to_side_pos(back(), dir);
	//--------
	if (
		const auto bg_tile = floor_layout.phys_bg_tile_at(pos);
		!bg_tile
	) {
		throw std::invalid_argument(sconcat
			("game_engine::level_gen_etc::Path::add(): ",
			"Internal Error: ",
			"Invalid `dir` (", to_string(dir), ") for ",
			"`back()` (", back(), ")"));
	}
	//--------
	_data.push_back(pos);
	//--------
	return *this;
	//--------
}
//--------
size_t Path::fill(const FillFunc& fill_func) const {
	size_t ret;
	for (ret=0; ret<data().size(); ++ret) {
		const auto& item = at(ret);
		if (fill_func(item)) {
			break;
		}
	}
	return ret;
}
//size_t path_fill(
//	const Path& path,
//	const BgTileUset& walkable_bg_tiles, const BfsVoidAtFunc& fill_func
//) {
//	size_t ret = 0;
//	for (; ret<path.size(); ++ret) {
//		const auto& item = path.at(ret);
//	}
//	return ret;
//}
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
