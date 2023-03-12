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

#include "dijkstra_map_gen_class.hpp"
#include "path_class.hpp"
#include "dngn_floor_class.hpp"
#include "../engine_class.hpp"
#include "../pfield_layer_prio_enum.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace lvgen_etc {
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
std::pair<bool, Path> DijkstraMap::make_path(
	//const DijkstraMap& dmap, //const DngnFloor& dngn_floor,
	const IntVec2& start_phys_pos, float stop_when_le_val
) const {
	std::pair<bool, Path> ret(true, Path());
	//temp.push_back(start_pos);
	IntVec2 phys_pos = start_phys_pos;

	if (!BOUNDS_R2.intersect(start_phys_pos)) {
		throw std::out_of_range(sconcat
			("game_engine::lvgen_etc::DijkstraMapGen::make_path(): ",
			"Internal Error: ",
			"`start_phys_pos` (", start_phys_pos, ") is outside the ",
			"bounds of `dmap`: ",
			"({", BOUNDS_R2.tl_corner(), " ",
				BOUNDS_R2.br_corner(), "})"));
	}
	ret.second._data.push_back(phys_pos);
	//while (pos != goal.pos)
	//for (;;)
	while (phys_at(phys_pos) > stop_when_le_val) {
		auto inner_func = [&](PathDir dir) -> bool {
			const auto side_phys_pos=path_dir_to_side_pos(phys_pos, dir);
			//engine->dbg_log
			//	("side_phys_pos stuff: ",
			//	side_phys_pos, " ",
			//	side_phys_pos - BOUNDS_R2.tl_corner(), "\n");
			if (
				BOUNDS_R2.intersect(side_phys_pos)
			) {
				//ret.second._data.push_back(side_pos);
				if (phys_at(side_phys_pos) < phys_at(phys_pos)) {
					// Always go "downhill".
					phys_pos = side_phys_pos;
					ret.second._data.push_back(phys_pos);
					return true;
				} else {
					//engine->dbg_log
					//	("testificate 0: ",
					//	"{", BOUNDS_R2.tl_corner(), " ",
					//		BOUNDS_R2.br_corner(), "} ",
					//	side_phys_pos, " ",
					//	phys_pos, "\n");
					return false;
				}
			} else {
				//return InnerFuncRet::OutOfBounds;
				//engine->dbg_log("testificate 1\n");
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
			//engine->dbg_log
			//	("DijkstraMap::make_path(): Failed to find a `Path`\n");
			//for (const IntVec2& item: ret.second) {
			//	engine->dbg_log(item, " ");
			//}
			//engine->dbg_log("\n");
			// This happens when we fail to find a `Path`. I'm about 90%
			// certain there's *not* an off-by-one error here.
			//return std::nullopt;
			//return ret;
			ret.first = false;
			break;
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
				osprintout(os, std::hex, "-0", std::abs(item), std::dec);
			} else if (item == 0) {
				osprintout(os, std::hex, " 0", item, std::dec);
			} else if (item >= 1 && item <= 15) {
				osprintout(os, std::hex, "+0", item, std::dec);
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
		for (size_t i=0; i<_goal_darr.size(); ++i) {
			if (const auto& goal=_goal_darr.at(i); goal.pos == pos) {
				throw std::invalid_argument(sconcat
					("game_engine::lvgen_etc::DijkstraMapGen::add(): ",
					"Internal Error: ",
					"already have a `Goal` with that `pos`: ",
					i, ": ", goal.pos, " ", goal.val));
			}
		}
	}
	//if (!PFIELD_PHYS_NO_BRDR_RECT2.intersect(pos)) {
	//	throw std::invalid_argument(sconcat
	//		("game_engine::lvgen_etc::DijkstraMapGen::add(): ",
	//		"Internal Error: ",
	//		"`pos` is not inclusively inside of ",
	//		"`PFIELD_PHYS_NO_BRDR_RECT2`: ",
	//		pos, " ",
	//		"{", "tl", PFIELD_PHYS_NO_BRDR_RECT2.tl_corner(), " ",
	//			"br", PFIELD_PHYS_NO_BRDR_RECT2.br_corner(), "}"));
	//}
	_goal_pos_to_index_umap.insert(std::pair(pos, _goal_darr.size()));
	_goal_darr.push_back({.pos=pos, .val=val});
	//_goal_umap.insert(std::pair(pos, Goal{.pos=pos, .val=val}));
	return *this;
}
//--------
DijkstraMap DijkstraMapGen::gen_basic(
	const DngnFloor& dngn_floor,
	const BgTileUset& no_pass_bg_tile_uset
	//,
	//const std::optional<StrKeyUset>& no_pass_items_traps_uset,
	//const std::optional<StrKeyUset>& no_pass_chars_machs_uset
) const {
	//DijkstraMap ret(PFIELD_PHYS_NO_BRDR_RECT2.size_2d.y,
	//	std::vector<float>
	//		(PFIELD_PHYS_NO_BRDR_RECT2.size_2d.x, VERY_HIGH_NUM));
	DijkstraMap ret;

	if (dngn_floor.size() == 0) {
		throw std::invalid_argument(sconcat
			("game_engine::lvgen_etc::DijkstraMapGen::gen_basic(): ",
			"Internal Error: ",
			"`dngn_floor.size() == 0`, should be `> 0`"));
	}
	class Sortable final {
	public:		// variables
		DijkstraMap* dmap = nullptr;
		IntVec2 phys_pos;
	public:		// functions
		constexpr inline auto operator <=> (const Sortable& to_cmp) const {
			return dmap->phys_at(phys_pos)
				<=> to_cmp.dmap->phys_at(to_cmp.phys_pos);
		}
	};

	std::deque<Sortable>
		to_sort_deque, to_move_deque;

	// Insert goals
	for (const auto& goal: goal_darr()) {
		//ret.at(goal.pos.y).at(goal.pos.x) = goal.val;
		ret._raw_phys_at(goal.pos) = goal.val;
		to_sort_deque.push_back({&ret, goal.pos});
	}

	auto edge_exists_func = [&](const IntVec2& phys_pos) -> bool {
		//auto upper_layer_func = [&dngn_floor, &phys_pos](
		//	const std::optional<StrKeyUset>& str_key_uset,
		//	PfieldLayerPrio prio
		//) -> bool {
		//	// `str_key_uset` allows the caller of this function to
		//	// pick between the following options:
		//	// `std::nullopt`: don't check this layer at all
		//	// `size() == 0`: any object in this layer blocks passage
		//	// `size() > 0`: only the  `kind_str()`s of each `ecs::comp``
		//	//				listed in the `StrKeyUset` block passage
		//	if (!str_key_uset) {
		//		return true;
		//	} else if (str_key_uset->size() == 0) {
		//		const auto& ul_umap = dngn_floor.upper_layer_umap(prio);
		//		return !ul_umap.contains(phys_pos);
		//	} else {
		//		const auto& ul_umap = dngn_floor.upper_layer_umap(prio);
		//		if (ul_umap.contains(phys_pos)) {
		//			for (const auto& key: *str_key_uset) {
		//				if (engine->
		//			}
		//		}
		//		return true;
		//	}
		//};

		const auto& bg_tile = dngn_floor.phys_bg_tile_at(phys_pos);
		return (
			bg_tile && !no_pass_bg_tile_uset.contains(*bg_tile)
			//&& upper_layer_func
			//	(no_pass_items_traps_uset, PfieldLayerPrio::ItemsTraps)
			//&& upper_layer_func
			//	(no_pass_chars_machs_uset, PfieldLayerPrio::CharsMachs)
		);
		//return static_cast<bool>(bg_tile);
	};
	//{
	//	//--------
	//	const IntVec2 start_pos = dngn_floor.at(0).rect.tl_corner();
	//	//--------
	//	auto fill_func = [&](const IntVec2& phys_pos) -> void {
	//		if (ret.phys_at(phys_pos) != ret.VERY_HIGH_NUM) {
	//			to_sort_deque.push_back({&ret, phys_pos});
	//		}
	//	};
	//	//--------
	//	// The initial `bfs_fill()` call that traverses the *entire* floor
	//	bfs_fill(start_pos, edge_exists_func, fill_func);
	//	//--------
	//}
	bool did_change;
	do {
		did_change = false;
		std::sort(to_sort_deque.begin(), to_sort_deque.end());

		auto fill_func = [&](const IntVec2& phys_pos) -> void {
			// At this point, `pos` is guaranteed to be at the location of
			// a valid physical BG tile
			const auto& ret_item = ret.phys_at(phys_pos);
			auto inner_func = [&](const IntVec2& offset) -> void {
				const IntVec2 side_phys_pos = phys_pos + offset;
				if (ret.BOUNDS_R2.intersect(side_phys_pos)) {
					if (
						//const auto bg_tile
						//	= dngn_floor.phys_bg_tile_at(side_phys_pos);
						//bg_tile && !no_pass_bg_tile_uset.contains(*bg_tile)
						edge_exists_func(side_phys_pos)
					) {
						auto& ret_side_item
							= ret._raw_phys_at(side_phys_pos);
						if (
							ret_side_item > ret_item
							&& ret_side_item != ret_item + 1
						) {
							did_change = true;
							ret_side_item = ret_item + 1;
							to_move_deque.push_back({&ret, side_phys_pos});
							//ret_side_item = ret_item;
						}
						//return true;
					}
				}
				//return false;
			};
			//return (
				inner_func(LEFT_OFFSET);
				//||
				inner_func(TOP_OFFSET);
				//||
				inner_func(RIGHT_OFFSET);
				//||
				inner_func(BOTTOM_OFFSET);
			//);
		};
		//const float lowest_val = to_sort_deque.front();
		while (to_sort_deque.size() > 0) {
			const Sortable item = to_sort_deque.front();
			fill_func(item.phys_pos);
			//if (!fill_func(item.phys_pos)) {
			//	return std::nullopt;
			//}
			to_sort_deque.pop_front();
		}
		to_sort_deque = std::move(to_move_deque);
		to_move_deque.clear();
	} while (did_change);

	//do {
	//	//--------
	//	did_change = false;
	//	//--------
	//	if (IntVec2 pos; true) {
	//		for (pos.y=0; pos.y<ret.size_2d().y; ++pos.y) {
	//			for (pos.x=0; pos.x<ret.size_2d().x; ++pos.x) {
	//				if (
	//					
	//				) {
	//				}
	//			}
	//		}
	//	}
	//	//--------
	//} while (did_change);
	//do {
	//	const IntVec2 start_pos = dngn_floor.at(0).rect.tl_corner();
	//	//--------
	//	auto edge_exists_func = [&](
	//		const IntVec2Uset& explored_uset, const IntVec2& phys_pos
	//	) -> bool {
	//		const auto& bg_tile = dngn_floor.phys_bg_tile_at(phys_pos);
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
	//	engine->dbg_log(sstm.str());
	//}
	//engine->dbg_log(ret);

	return ret;
}
DijkstraMap DijkstraMapGen::gen_flipped(
	const DngnFloor& dngn_floor,
	const BgTileUset& no_pass_bg_tile_uset,
	//const std::optional<StrKeyUset>& no_pass_items_traps_uset,
	//const std::optional<StrKeyUset>& no_pass_chars_machs_uset,
	float bonus
) const {
	auto ret = gen_basic
		(dngn_floor,
		no_pass_bg_tile_uset
		//,
		//no_pass_items_traps_uset,
		//no_pass_chars_machs_uset
		);
	//if (ret) {
		//flip(ret, bonus);
		//return ret;
		ret.flip(bonus);
		return ret;
	//}
	//return std::nullopt;
}
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
