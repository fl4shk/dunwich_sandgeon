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

#include "../comp/drawable_data_umap.hpp"
#include "floor_layout_class.hpp"
#include "../engine_class.hpp"
#include "../global_shape_constants_etc.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
const std::string
	FloorLayout::KIND_STR("FloorLayout");

//auto FloorLayout::RoomPath::from_bv(const binser::Value& bv) -> RoomPath {
//	RoomPath ret;
//
//	MEMB_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_FROM_BV_DESERIALIZE);
//
//	//if (!ret.is_valid())
//	if (!ret.fits_in_pfield_nb()) {
//		//throw std::invalid_argument(sconcat(
//		//		(func_name ? sconcat(*func_name, "(): ") : std::string()),
//		//		(msg ? sconcat(*msg, ": ") : std::string()),
//		//		data_str, " < ", min_str,
//		//			" || ", data_str, " || ", max_str,
//		//			": ",
//		//		data, " ", min, " ", max
//		//));
//		throw std::invalid_argument(sconcat(
//			"game_engine::level_gen_etc::FloorLayout::RoomPath::from_bv(): ",
//			"`ret.rect` does not fit in the playfield: ", ret.rect
//		));
//	}
//	if (!ret.is_path() && !ret.is_room()) {
//		throw std::invalid_argument(sconcat(
//			"game_engine::level_gen_etc::FloorLayout::RoomPath::from_bv(): ",
//			"`ret.rect` is the wrong shape to be a path or a room: ",
//			ret.rect
//		));
//	}
//
//	return ret;
//}
//FloorLayout::RoomPath::operator binser::Value () const {
//	binser::Value ret;
//
//	//MEMB_EX_MM_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_SERIALIZE);
//	//MEMB_EX_CS_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_SERIALIZE);
//	//MEMB_AUTOSER_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_SERIALIZE);
//	//BINSER_MEMB_SERIALIZE(rect);
//	MEMB_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_SERIALIZE);
//
//	return ret;
//}
FloorLayout::FloorLayout() {}
//FloorLayout::FloorLayout(const binser::Value& bv) {
//	//_rp_data.checked_size = MAX_NUM_ROOM_PATHS;
//	//_rp_data.cs_is_max = true;
//	////_rp_data.min_size = 0;
//	//_rp_data.min_size = MIN_NUM_ROOM_PATHS;
//
//	MEMB_LIST_COMP_DUNGEON(BINSER_MEMB_DESERIALIZE);
//}

//std::string FloorLayout::kind_str() const {
//	return KIND_STR;
//}
//FloorLayout::operator binser::Value () const {
//	binser::Value ret;
//
//	MEMB_LIST_COMP_DUNGEON(BINSER_MEMB_SERIALIZE);
//
//	return ret;
//}
//--------
std::optional<BgTile> FloorLayout::bg_tile_at(
	const IntVec2& pos, size_t i
) const {
	//BgTile bg_tile = BgTile::Blank;
	//std::optional<BgTile> ret = std::nullopt;

	const RoomPath& rp = at(i);
	const bool in_border = rp.pos_in_border(pos);

	if (in_border) {
		// I'm doing this the slow/easy way for now.
		bool did_intersect = false;
		for (size_t j=0; j<i; ++j)
		//for (size_t j=0; j<size(); ++j)
		{
			if (j != i) {
				if (at(j).rect.intersect(pos)) {
					did_intersect = true;
					break;
				}
			}
		}
		//if (const auto& item_uset=cg_neighbors(i); true) {
		//	for (const auto& item: item_uset) {
		//		const auto j = _rp_to_index_umap
		//			.at(static_cast<RoomPath*>(item));
		//		if (item->bbox().intersect(pos) && j < i) {
		//			did_intersect = true;
		//			break;
		//		}
		//	}
		//}

		if (!did_intersect) {
			return BgTile::Wall;
			//do_draw();
		} else {
			return std::nullopt;
		}
	} else { // if (!in_border)
		//if (!rp.door_pt_uset.contains(pos)) {
		//	if (rp.alt_terrain_umap.contains(pos)) {
		//		bg_tile = rp.alt_terrain_umap.at(pos);
		//	} else {
		//		bg_tile
		//			= rp.is_path()
		//			? BgTile::PathFloor
		//			: BgTile::RoomFloor;
		//	}
		//} else {
		//	bg_tile = BgTile::Door;
		//}
		return phys_bg_tile_at(pos);
		//do_draw();
	}
	//return bg_tile;
}
std::optional<BgTile> FloorLayout::phys_bg_tile_at(const IntVec2& pos)
const {
	//if (!PFIELD_PHYS_RECT2.arg_inside(pos)) {
	//	return std::nullopt;
	//}
	if (!PFIELD_PHYS_NO_BRDR_RECT2.intersect(pos)) {
		return std::nullopt;
	}
	const auto& neighbors = cg_neighbors(pos);

	for (auto& neighbor: neighbors) {
		if (neighbor->bbox().intersect(pos)) {
			RoomPath& rp = *static_cast<RoomPath*>(neighbor);

			if (ustairs_pos == pos) {
				return BgTile::UpStairs;
			} else if (dstairs_pos && *dstairs_pos == pos) {
				return BgTile::DownStairs;
			} else if (rp.door_pt_uset.contains(pos)) {
				return BgTile::Door;
			} else if (rp.alt_terrain_umap.contains(pos)) {
				return rp.alt_terrain_umap.at(pos);
			}  else {
				return
					rp.is_path()
					? BgTile::PathFloor
					: BgTile::RoomFloor;
			}
		}
	}
	return std::nullopt;
}
//--------
std::optional<size_t> FloorLayout::phys_pos_to_rp_index(
	const IntVec2& phys_pos
) const {
	//if (!PFIELD_PHYS_NO_BRDR_RECT2.intersect(phys_pos)) {
	//	return std::nullopt;
	//}
	const auto& neighbors = cg_neighbors(phys_pos);

	for (auto& neighbor: neighbors) {
		if (neighbor->bbox().intersect(phys_pos)) {
			return rp_to_index_umap().at(static_cast<RoomPath*>(neighbor));
		}
	}
	return std::nullopt;
}
void FloorLayout::push_back(RoomPath&& to_push) {
	if (size() + size_t(1) > MAX_NUM_ROOM_PATHS) {
		throw std::length_error(sconcat
			("game_engine::level_gen_etc::FloorLayout::push_back(): ",
			"`_rp_data.data` cannot increase in size: ",
			//_rp_data.data.size(),
			_rp_data.size(),
			" ", MAX_NUM_ROOM_PATHS));
	}
	to_push.id = i32(size());
	//_rp_data.data.push_back(std::move(to_push));
	_rp_data.push_back(RoomPathSptr(new RoomPath(std::move(to_push))));
	_rp_to_index_umap.insert(std::pair
		(_rp_data.back().get(), _rp_data.size() - size_t(1)));
	_coll_grid.insert(_rp_data.back().get());
}
bool FloorLayout::erase_maybe(size_t index) {
	if (size() > MIN_NUM_ROOM_PATHS) {
		//for (size_t i=0; i<size(); ++i) {
		//	if (i == index) {
		//		continue;
		//	}
		//	auto& item = _raw_at(i);
		//	if (item.conn_index_uset.contains(i32(index))) {
		//		item.conn_index_uset.erase(i32(index));
		//	}
		//	//if (i > index) {
		//	//	item.id = i32(i);
		//	//}
		//	item.id = i32(i - 1);
		//}
		// We have to erase from `_rp_to_index_umap` and `_coll_grid`
		// before we erase from `_rp_data`.
		_rp_to_index_umap.erase(_rp_data.at(index).get());
		_coll_grid.erase(_rp_data.at(index).get(), std::nullopt);
		_rp_data.erase(_rp_data.begin() + index);
		for (size_t i=0; i<size(); ++i) {
			auto& item = _raw_at(i);
			std::unordered_set<i32> temp_conn_index_uset;
			for (const auto& conn_index: item.conn_index_uset) {
				if (conn_index > i32(index)) {
					temp_conn_index_uset.insert(conn_index - 1);
				} else if (conn_index < i32(index)) {
					temp_conn_index_uset.insert(conn_index);
				}
			}
			//if (item.conn_index_uset.contains(i32(index))) {
			//	item.conn_index_uset.erase(i32(index));
			//}
			item.conn_index_uset = std::move(temp_conn_index_uset);
			item.id = i32(i);
		}
		return true;
	}
	return false;
}
CollGridT::DataElPtrUsetT FloorLayout::cg_neighbors(RoomPath& rp) const {
	return _coll_grid.neighbors(&rp);
}
CollGridT::DataElPtrUsetT FloorLayout::cg_neighbors(size_t index) const {
	return _coll_grid.neighbors(_rp_data.at(index).get());
}
CollGridT::DataElPtrUsetT FloorLayout::cg_neighbors(const IntVec2& pos)
const {
	RoomPath temp_rp; //= {.rect{pos=pos, .size_2d={1, 1}}};
	temp_rp.rect.pos = pos;
	temp_rp.rect.size_2d = {1, 1};
	return _coll_grid.neighbors(&temp_rp);
}
void FloorLayout::draw() const {
	//bg_tile_map->at({0, 0}) = BgTile::Floor;
	for (size_t i=0; i<size(); ++i) 
	//for (size_t i=1; i<size(); ++i)
	{
		const RoomPath& rp = at(i);
		IntVec2
			pos;
		// Note that rooms are already generated with their borders inside
		// of `engine.pfield_window`
		for (
			pos.y=rp.rect.top_y() - i32(1);
			pos.y<=rp.rect.bottom_y() + i32(1);
			++pos.y
		) {
			for (
				pos.x=rp.rect.left_x() - i32(1);
				pos.x<=rp.rect.right_x() + i32(1);
				++pos.x
			) {
				try {
					const auto& bg_tile = bg_tile_at(pos, i);
					//if (bg_tile != BgTile::Blank)
					if (bg_tile) {
						engine->pfield_window.drawable_data_at(pos)
							= comp::drawable_data_umap().at
								(bg_tile_str_map_at(*bg_tile));
					}
				} catch (const std::exception& e) {
					printerr("game_engine::level_gen_etc::FloorLayout",
						"::draw(): "
						"Exception thrown: ", e.what(), "\n");
					throw std::out_of_range(sconcat(
						"rp.rect",rp.rect, ", pos", pos, ", ",
						"rs{", rp.rect.right_x(), "}, ",
						"bs{", rp.rect.bottom_y(), "}, ",
						"fp{", rp.fits_in_pfnb(), "}"
						
					));
				}
			}
		}
	}
}
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
