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

#ifndef src_game_engine_lvgen_etc_path_class_hpp
#define src_game_engine_lvgen_etc_path_class_hpp

// src/game_engine/lvgen_etc/path_class.hpp

#include "../../misc_includes.hpp"
#include "../global_shape_constants_etc.hpp"
#include "bfs_funcs.hpp"
//#include "dijkstra_map_gen_class.hpp"
//#include "bg_tile_enum.hpp"
//#include "dngn_floor_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace lvgen_etc {
//--------
class DngnFloor;
class DijkstraMap;
//--------
//using Path = std::vector<IntVec2>;
//size_t path_fill(
//	const Path& path,
//	const BgTileUset& walkable_bg_tiles, const BfsVoidAtFunc& fill_func
//);
//--------
// Different from a `RoomTunnel`.
class Path final {
	friend class DijkstraMap;
public:		// types
	// Direction matters
	using Data = std::vector<IntVec2>;

	using FillFunc = std::function<bool(const IntVec2&)>;
private:		// variables
	Data _data;
public:		// functions
	Path();
	Path(const IntVec2& start_pos);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Path);
	~Path();

	Path& add(const DngnFloor& dngn_floor, PathDir dir);
	//Path& add(const DijkstraMapGen::Dmap& dmap, PathDir dir);
	Path& unchecked_add(PathDir dir);
	Path& unchecked_add(const IntVec2& pos);
	//Path& pop_back();
	//--------
	inline const IntVec2& front() const {
		return data().front();
	}
	inline const IntVec2& back() const {
		return data().back();
	}
	inline auto begin() const {
		return _data.begin();
	}
	inline auto end() const {
		return _data.end();
	}
	inline auto cbegin() const {
		return _data.cbegin();
	}
	inline auto cend() const {
		return _data.cend();
	}
	inline const IntVec2& at(size_t i) const {
		return data().at(i);
	}
	//--------
	inline size_t size() const {
		return data().size();
	}
	//--------
	// This function returns where it stopped at
	size_t fill(
		const FillFunc& fill_func
		//const std::optional<IntVec2>& start_r2_sz2d=std::nullopt,
		//const std::optional<IntVec2>& end_r2_sz2d=std::nullopt
	) const;
	//--------
	GEN_GETTER_BY_CON_REF(data);
	//--------
};
//std::ostream& operator << (std::ostream& os, const Path& path);
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_lvgen_etc_path_class_hpp
