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
#include "path_class.hpp"
#include "floor_layout_class.hpp"
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
DijkstraMap::DijkstraMap() 
	: _data(SIZE_2D.y, std::vector<float>(SIZE_2D.x, VERY_HIGH_NUM)) {}
DijkstraMap::~DijkstraMap() {}

DijkstraMap& DijkstraMap::flip(float bonus) {
	for (auto& row: _data) {
		for (auto& item: row) {
			item *= -1.0f - std::abs(bonus);
		}
	}

	return *this;
}
std::optional<Path> DijkstraMap::make_path(
	//const DijkstraMap& dmap, //const FloorLayout& floor_layout,
	const IntVec2& start_phys_pos, float stop_when_le_val
) const {
	Path ret;
	//temp.push_back(start_pos);
	IntVec2 phys_pos = start_phys_pos;

	if (!BOUNDS_R2.intersect(start_phys_pos)) {
		throw std::out_of_range(sconcat
			("game_engine::level_gen_etc::DijkstraMapGen::make_path(): ",
			"Internal Error: ",
			"`start_phys_pos` (", start_phys_pos, ") is outside the ",
			"bounds of `dmap`: ",
			"({", BOUNDS_R2.tl_corner(), " ",
				BOUNDS_R2.br_corner(), "})"));
	}
	ret._data.push_back(phys_pos);
	//while (pos != goal.pos)
	//for (;;)
	while (phys_at(phys_pos) > stop_when_le_val) {
		auto inner_func = [&](PathDir dir) -> bool {
			if (
				const auto side_phys_pos=path_dir_to_side_pos
					(phys_pos, dir);
				BOUNDS_R2.intersect(side_phys_pos)
			) {
				//ret._data.push_back(side_pos);
				if (phys_at(side_phys_pos) < phys_at(phys_pos)) {
					// Always go "downhill".
					phys_pos = side_phys_pos;
					ret._data.push_back(phys_pos);
					return true;
				} else {
					return false;
				}
			} else {
				//return InnerFuncRet::OutOfBounds;
				return false;
			}
		};
		if (
			!(
				inner_func(PathDir::Left)
				|| inner_func(PathDir::Top)
				|| inner_func(PathDir::Right)
				|| inner_func(PathDir::Bottom)
			)
		) {
			// This happens when we fail to find a `Path`. I'm about 90%
			// certain there's *not* an off-by-one error here.
			return std::nullopt;
		}
	}
	//ret.insert(std::pair(goal.pos, std::move(temp)));
	return ret;
}
std::ostream& operator << (
	std::ostream& os, const DijkstraMap& self
) {
	// debug printing
	IntVec2 pos;
	for (pos.y=0; pos.y<self.size_2d().y; ++pos.y) {
		for (pos.x=0; pos.x<self.size_2d().x; ++pos.x) {
			const i32 item = i32(self.at(pos));
			if (item >= -255 && item <= -16) {
				osprintout(os, std::hex, "-", std::abs(item), std::dec);
			} else if (item >= -15 && item <= -1) {
				osprintout(os, std::hex, "- ", std::abs(item), std::dec);
			} else if (item == 0) {
				osprintout(os, std::hex, "  ", item, std::dec);
			} else if (item >= 1 && item <= 15) {
				osprintout(os, std::hex, "+ ", item, std::dec);
			} else if (item >= 16 && item <= 255) {
				osprintout(os, std::hex, "+", item, std::dec);
			} else {
				osprintout(os, "   ");
			}
			if (pos.x + 1 < self.size_2d().x) {
				osprintout(os, " ");
			}
		}
		osprintout(os, "\n");
	}
	return os;
}
//--------
DijkstraMapGen::DijkstraMapGen() {}
DijkstraMapGen::~DijkstraMapGen() {}
//--------
DijkstraMapGen& DijkstraMapGen::add(const IntVec2& pos, float val) {
	//if (goal_umap().contains(pos))
	if (goal_pos_to_index_umap().contains(pos)) {
		for (size_t i=0; i<_goal_vec.size(); ++i) {
			if (const auto& goal=_goal_vec.at(i); goal.pos == pos) {
				throw std::invalid_argument(sconcat
					("game_engine::level_gen_etc::DijkstraMapGen::add(): ",
					"Internal Error: ",
					"already have a `Goal` with that `pos`: ",
					i, ": ", goal.pos, " ", goal.val));
			}
		}
	}
	_goal_pos_to_index_umap.insert(std::pair(pos, _goal_vec.size()));
	_goal_vec.push_back({.pos=pos, .val=val});
	//_goal_umap.insert(std::pair(pos, Goal{.pos=pos, .val=val}));
	return *this;
}
//--------
DijkstraMap DijkstraMapGen::gen_basic(
	const FloorLayout& floor_layout, const BgTileUset& no_pass_uset
) const {
	//DijkstraMap ret(PFIELD_PHYS_NO_BRDR_RECT2.size_2d.y,
	//	std::vector<float>
	//		(PFIELD_PHYS_NO_BRDR_RECT2.size_2d.x, VERY_HIGH_NUM));
	DijkstraMap ret;

	if (floor_layout.size() == 0) {
		throw std::invalid_argument(sconcat
			("game_engine::level_gen_etc::DijkstraMapGen::gen_basic(): ",
			"Internal Error: ",
			"`floor_layout.size() == 0`, should be `> 0`"));
	}

	// Insert goals
	for (const auto& goal: goal_vec()) {
		//ret.at(goal.pos.y).at(goal.pos.x) = goal.val;
		ret._raw_phys_at(goal.pos) = goal.val;
	}

	bool did_change;
	do {
		//--------
		did_change = false;
		//--------
		const IntVec2 start_pos = floor_layout.at(0).rect.tl_corner();
		//--------
		auto edge_exists_func = [&](
			const IntVec2Uset& explored_uset, const IntVec2& phys_pos
		) -> bool {
			const auto& bg_tile = floor_layout.phys_bg_tile_at(phys_pos);
			return (bg_tile && !no_pass_uset.contains(*bg_tile));
			//return static_cast<bool>(bg_tile);
		};
		//--------
		auto fill_func = [&](
			const IntVec2Uset& explored_uset, const IntVec2& phys_pos
		) -> void {
			// At this point, `pos` is guaranteed to be at the location of
			// a valid physical BG tile
			//const IntVec2
			//	ret_pos = pos - PFIELD_PHYS_NO_BRDR_RECT2.tl_corner();
			const auto
				//& ret_item = ret.at(ret_pos.y).at(ret_pos.x);
				& ret_item = ret.phys_at(phys_pos);
			auto inner_func = [&](const IntVec2& offset) -> void {
				const IntVec2
					side_phys_pos = phys_pos + offset;
					//ret_side_pos = side_pos
					//	- PFIELD_PHYS_NO_BRDR_RECT2.tl_corner();
				if (ret.BOUNDS_R2.intersect(side_phys_pos)) {
					if (
						const auto bg_tile
							= floor_layout.phys_bg_tile_at(side_phys_pos);
						bg_tile && !no_pass_uset.contains(*bg_tile)
					) {
						auto
							//& ret_side_item = ret
							//	.at(ret_side_pos.y).at(ret_side_pos.x);
							& ret_side_item
								= ret._raw_phys_at(side_phys_pos);
						if (
							ret_side_item > ret_item
							&& ret_side_item != ret_item + 1
						) {
							ret_side_item = ret_item + 1;
							//ret_side_item = ret_item;
							did_change = true;
						}
					}
				}
			};
			inner_func(LEFT_OFFSET);
			inner_func(TOP_OFFSET);
			inner_func(RIGHT_OFFSET);
			inner_func(BOTTOM_OFFSET);
		};
		//--------
		bfs_fill(start_pos, edge_exists_func, fill_func);
		//--------
	} while (did_change);
	//bool did_change;
	//do {
	//	//--------
	//	did_change = false;
	//	//--------
	//	IntVec2 pos;
	//	for (pos.y=0; pos.y<ret.size_2d().y; ++pos.y) {
	//		for (pos.x=0; pos.x<ret.size_2d().x; ++pos.x) {
	//			if (
	//				
	//			) {
	//			}
	//		}
	//	}
	//	//--------
	//} while (did_change);
	//do {
	//	const IntVec2 start_pos = floor_layout.at(0).rect.tl_corner();
	//	//--------
	//	auto edge_exists_func = [&](
	//		const IntVec2Uset& explored_uset, const IntVec2& phys_pos
	//	) -> bool {
	//		const auto& bg_tile = floor_layout.phys_bg_tile_at(phys_pos);
	//		return (bg_tile && !no_pass_uset.contains(*bg_tile));
	//	}
	//	//--------
	//	auto fill_func = [&](
	//		const IntVec2Uset& explored_uset, const IntVec2& phys_pos
	//	) -> void {
	//		const auto& ret_iem = ret.phys_at(phys_pos);
	//		auto inner_func
	//	};
	//	//--------
	//} while (did_change);

	//if (std::stringstream sstm; true) {
	//	osprint_dmap(sstm, ret);
	//	engine->log(sstm.str());
	//}
	engine->log(ret);

	return ret;
}
DijkstraMap DijkstraMapGen::gen_flipped(
	const FloorLayout& floor_layout, const BgTileUset& no_pass_uset,
	float bonus
) const {
	DijkstraMap ret = gen_basic(floor_layout, no_pass_uset);
	//flip(ret, bonus);
	//return ret;
	ret.flip(bonus);
	return ret;
}
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
