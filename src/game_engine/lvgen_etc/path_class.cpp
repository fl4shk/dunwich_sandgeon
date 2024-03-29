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

#include "path_class.hpp"
#include "bg_tile_enum.hpp"
#include "dngn_floor_class.hpp"
#include "dijkstra_map_gen_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace lvgen_etc {
//--------
Path::Path() {
}
Path::Path(const IntVec2& start_pos) {
	_data.push_back(start_pos);
}
Path::~Path() {
}

Path& Path::add(const DngnFloor& dngn_floor, PathDir dir) {
	//--------
	if (size() == 0) {
		throw std::runtime_error(sconcat
			("game_engine::lvgen_etc::Path::add(): ",
			"Internal Error: ",
			"`size() == 0`"));
	}
	//--------
	const IntVec2 pos = path_dir_to_side_pos(back(), dir);
	//--------
	if (
		const auto bg_tile = dngn_floor.phys_bg_tile_at(pos);
		!bg_tile
	) {
		throw std::invalid_argument(sconcat
			("game_engine::lvgen_etc::Path::add(): ",
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
Path& Path::unchecked_add(PathDir dir) {
	//--------
	_data.push_back(path_dir_to_side_pos(back(), dir));
	//--------
	return *this;
	//--------
}
Path& Path::unchecked_add(const IntVec2& pos) {
	//--------
	_data.push_back(pos);
	//--------
	return *this;
	//--------
}

//Path& Path::pop_back() {
//	//--------
//	_data.pop_back();
//	//--------
//	return *this;
//	//--------
//}
//--------
size_t Path::fill(
	const FillFunc& fill_func
	//const std::optional<IntVec2>& start_r2_sz2d,
	//const std::optional<IntVec2>& end_r2_sz2d
) const {
	size_t ret;
	for (ret=0; ret<data().size(); ++ret) {
		const auto& item = at(ret);
		if (!fill_func(item)) {
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
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
