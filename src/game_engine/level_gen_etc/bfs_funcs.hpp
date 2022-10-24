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

#ifndef src_game_engine_level_gen_etc_bfs_funcs_hpp
#define src_game_engine_level_gen_etc_bfs_funcs_hpp

// src/game_engine/level_gen_etc/bfs_funcs.hpp

#include "../../misc_includes.hpp"
#include "../../misc_types.hpp"
//#include "floor_layout_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
// Breadth-first search
using BfsAtFunc = std::function<bool(
	const IntVec2Uset&, const IntVec2&
)>;
using BfsVoidAtFunc = std::function<void(
	const IntVec2Uset&, const IntVec2&
)>;

// This function returns the 
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
bool bfs_reachable(
	IntVec2Uset& explored_uset,
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func, const BfsAtFunc& extra_test_func
);
inline bool bfs_reachable(
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func, const BfsAtFunc& extra_test_func
) {
	IntVec2Uset explored_uset;
	return bfs_reachable(explored_uset, start_pos, start_pos,
		edge_exists_func, extra_test_func);
}
//inline void bfs_fill(
//	const IntVec2& start_pos,
//	const BfsAtFunc& edge_exists_func, const BfsVoidAtFunc& fill_func
//);
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon


#endif		// src_game_engine_level_gen_etc_bfs_funcs_hpp
