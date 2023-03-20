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

#ifndef src_game_engine_lvgen_etc_bfs_funcs_hpp
#define src_game_engine_lvgen_etc_bfs_funcs_hpp

// src/game_engine/lvgen_etc/bfs_funcs.hpp

#include "../../misc_includes.hpp"
#include "../../misc_types.hpp"
//#include "dngn_floor_class.hpp"
#include "bg_tile_enum.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace lvgen_etc {
//--------
class Path;
class DngnFloor;
//--------
// Breadth-first search
using BfsAtFunc = std::function<bool(
	//const IntVec2Uset&, // explored_uset
	const IntVec2& // pos
)>;
using BfsVoidAtFunc = std::function<void(
	//const IntVec2Uset&, // explored_uset
	const IntVec2& // pos
)>;

void bfs_fill(
	IntVec2Uset& explored_uset, const IntVec2& start_pos,
	const BfsAtFunc& edge_exists_func, const BfsVoidAtFunc& fill_func
);
inline void bfs_fill(
	const IntVec2& start_pos,
	const BfsAtFunc& edge_exists_func, const BfsVoidAtFunc& fill_func
) {
	IntVec2Uset explored_uset;
	bfs_fill(explored_uset, start_pos, edge_exists_func, fill_func);
}
// Whether or not two positions are reachable
bool bfs_reachable(
	IntVec2Uset& explored_uset,
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func//, const BfsAtFunc& extra_test_func
);
inline bool bfs_reachable(
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func//, const BfsAtFunc& extra_test_func
) {
	IntVec2Uset explored_uset;
	return bfs_reachable(explored_uset, start_pos, end_pos,
		edge_exists_func//, extra_test_func
		);
}

//class BfsTree {
//public:		// variables
//	BfsTree* parent = nullptr;
//	IntVec2 pos;
//	//PathDir dir;
//	std::vector<std::shared_ptr<BfsTree>> child_darr;
//public:		// functions
//	Path make_path_to_root() const;
//};
std::pair<bool, Path> bfs_pathfind(
	IntVec2Uset& explored_uset,
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func
);
std::pair<bool, Path> bfs_pathfind(
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func
);

std::pair<bool, Path> bfs_pathfind(
	IntVec2Uset& explored_uset,
	const IntVec2& start_pos, const IntVec2& end_pos,
	const DngnFloor& dngn_floor,
	const BgTileUset& no_pass_bg_tile_uset,
	const IntVec2Uset& forced_walkable_pos2_uset=IntVec2Uset()
);
std::pair<bool, Path> bfs_pathfind(
	const IntVec2& start_pos, const IntVec2& end_pos,
	const DngnFloor& dngn_floor,
	const BgTileUset& no_pass_bg_tile_uset,
	const IntVec2Uset& forced_walkable_pos2_uset=IntVec2Uset()
);
//inline void bfs_fill(
//	const IntVec2& start_pos,
//	const BfsAtFunc& edge_exists_func, const BfsVoidAtFunc& fill_func
//);
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon


#endif		// src_game_engine_lvgen_etc_bfs_funcs_hpp
