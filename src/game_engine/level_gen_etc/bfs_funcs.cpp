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

#include "bfs_funcs.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
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
					edge_exists_func(explored_uset, w)
					&& !explored_uset.contains(w)
				) {
					explored_uset.insert(w);
					q.push(w);
					fill_func(explored_uset, w);
				}
			}
		};
		maybe_add({-1, 0}); // left
		maybe_add({0, -1}); // top
		maybe_add({1, 0}); // right
		maybe_add({0, 1}); // bottom
	}
}
bool bfs_reachable(
	IntVec2Uset& explored_uset,
	const IntVec2& start_pos, const IntVec2& end_pos,
	const BfsAtFunc& edge_exists_func, const BfsAtFunc& extra_test_func
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
					edge_exists_func(explored_uset, w)
					&& !explored_uset.contains(w)
				) {
					explored_uset.insert(w);
					q.push(w);
					if (extra_test_func(explored_uset, w)) {
						return true;
					}
				}
			}
			return false;
		};
		if (maybe_add({-1, 0})) { // left
			return true;
		}
		if (maybe_add({0, -1})) { // top
			return true;
		}
		if (maybe_add({1, 0})) { // right
			return true;
		}
		if (maybe_add({0, 1})) {// bottom
			return true;
		}
	}
	return false;
}
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon