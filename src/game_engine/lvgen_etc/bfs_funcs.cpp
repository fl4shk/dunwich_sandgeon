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

#include "bfs_funcs.hpp"
#include "path_class.hpp"
#include "dngn_floor_class.hpp"
#include "../global_shape_constants_etc.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace lvgen_etc {
//--------
void bfs_fill(
	IntVec2Uset& explored_uset, const IntVec2& start_pos,
	const BfsAtFunc& edge_exists_func, const BfsVoidAtFunc& fill_func
) {
	explored_uset.insert(start_pos);
	std::queue<IntVec2> q;
	q.push(start_pos);

	while (q.size() > 0) {
		auto v = q.front();
		q.pop();
		//if (at_func(v)) {
		//}
		auto maybe_add = [&](const IntVec2& offset) -> void {
			if (const IntVec2 w=v + offset; true) {
				if (
					edge_exists_func(w)
					&& !explored_uset.contains(w)
				) {
					explored_uset.insert(w);
					q.push(w);
					fill_func(w);
				}
			}
		};
		maybe_add(LEFT_OFFSET);
		maybe_add(TOP_OFFSET);
		maybe_add(RIGHT_OFFSET);
		maybe_add(BOTTOM_OFFSET);
	}
}
bool bfs_reachable(
	IntVec2Uset& explored_uset,
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func//, const BfsAtFunc& extra_test_func
) {
	explored_uset.insert(start_pos);
	std::queue<IntVec2> q;
	q.push(start_pos);

	while (q.size() > 0) {
		auto v = q.front();
		q.pop();
		auto maybe_add = [&](const IntVec2& offset) -> bool {
			if (const IntVec2 w=v + offset; true) {
				if (
					edge_exists_func(w)
					&& !explored_uset.contains(w)
				) {
					explored_uset.insert(w);
					q.push(w);
					//if (extra_test_func(w)) {
					//	return true;
					//}
					if (w == end_pos) {
						return true;
					}
				}
			}
			return false;
		};
		if (maybe_add(LEFT_OFFSET)) {
			return true;
		}
		if (maybe_add(TOP_OFFSET)) {
			return true;
		}
		if (maybe_add(RIGHT_OFFSET)) {
			return true;
		}
		if (maybe_add(BOTTOM_OFFSET)) {
			return true;
		}
	}
	return false;
}
//--------
//Path BfsTree::make_path_to_root() const {
//	//--------
//	Path ret;
//	//--------
//	return ret;
//	//--------
//}
//--------
std::pair<bool, Path> bfs_pathfind(
	IntVec2Uset& explored_uset,
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func
) {
	std::pair<bool, Path> ret(false, Path());

	explored_uset.insert(end_pos);
	std::queue<IntVec2> q;
	q.push(end_pos);

	//BfsTree
	//	tree{.parent=nullptr, .pos=end_pos};
	std::unordered_map<IntVec2, IntVec2>
		parent_umap;

	//temp_umap.insert({tree.pos, &tree});
	parent_umap.insert({end_pos, IntVec2{-1, -1}});

	while (q.size() > 0) {
		auto v = q.front();
		q.pop();
		//if (leaf->parent) {
		//	leaf = leaf->parent;
		//}
		//BfsTree* child = nullptr;
		IntVec2 w;
		auto maybe_add = [&](const IntVec2& offset) -> bool {
			w = v + offset;
			if (
				edge_exists_func(w)
				&& !explored_uset.contains(w)
			) {
				explored_uset.insert(w);
				q.push(w);

				//BfsTree* child = new BfsTree{.parent=leaf, pos=w};
				//leaf->child_darr.push_back
				//	(std::shared_ptr<BfsTree>(child));
				//engine->dbg_log("Inserting {", v, " ", w, "\n");
				parent_umap.insert({w, v});

				if (w == start_pos) {
					return true;
				}
			}
			return false;
		};
		auto make_path = [&]() -> void {
			ret.first = true;
			//ret.second = Path();

			// A path is guranteed to exist at this point
			IntVec2 temp;
			for (
				temp=start_pos; temp!=end_pos; //temp=parent_umap.at(temp)
			) {
				ret.second.unchecked_add(temp);
				if (temp != end_pos) {
					//engine->dbg_log("temp stuff: ",
					//	temp, " ", parent_umap.at(temp), "\n");
					temp = parent_umap.at(temp);
				}
			}
			ret.second.unchecked_add(temp);
		};
		if (maybe_add(LEFT_OFFSET)) {
			//return leaf->make_path_to_root();
			make_path();
			break; 
		}
		if (maybe_add(TOP_OFFSET)) {
			//return leaf->make_path_to_root();
			make_path();
			break; 
		}
		if (maybe_add(RIGHT_OFFSET)) {
			//return leaf->make_path_to_root();
			make_path();
			break; 
		}
		if (maybe_add(BOTTOM_OFFSET)) {
			//return leaf->make_path_to_root();
			make_path();
			break; 
		}
	}
	//return std::nullopt;
	return ret;
}
std::pair<bool, Path> bfs_pathfind(
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func
) {
	IntVec2Uset explored_uset;
	return bfs_pathfind(explored_uset, start_pos, end_pos,
		edge_exists_func);
}
std::pair<bool, Path> bfs_pathfind(
	IntVec2Uset& explored_uset,
	const IntVec2& start_pos, const IntVec2& end_pos,
	const DngnFloor& dngn_floor,
	const BgTileUset& no_pass_bg_tile_uset,
	const IntVec2Uset& forced_walkable_pos2_uset
) {
	return bfs_pathfind(explored_uset,
		start_pos, end_pos,
		[&](const IntVec2& phys_pos) -> bool {
			const auto& bg_tile = dngn_floor.phys_bg_tile_at(phys_pos);
			return (
				bg_tile && (
					forced_walkable_pos2_uset.contains(phys_pos)
					|| !no_pass_bg_tile_uset.contains(*bg_tile)
				)
			);
		});
}
std::pair<bool, Path> bfs_pathfind(
	const IntVec2& start_pos, const IntVec2& end_pos,
	const DngnFloor& dngn_floor,
	const BgTileUset& no_pass_bg_tile_uset,
	const IntVec2Uset& forced_walkable_pos2_uset
) {
	IntVec2Uset explored_uset;
	return bfs_pathfind(explored_uset,
		start_pos, end_pos,
		dngn_floor,
		no_pass_bg_tile_uset,
		forced_walkable_pos2_uset);
}
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
