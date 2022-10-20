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

#include "drawable_data_umap.hpp"
#include "floor_layout_comp_classes.hpp"
#include "../engine_class.hpp"
#include "../global_shape_constants_etc.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace comp {
//--------
//const std::unordered_map<BgTile, std::string>& bg_tile_str_map() {
//	//--------
//	static const std::unordered_map<BgTile, std::string>
//		BG_TILE_STR_MAP = {
//		//{Tile::Wall, "TileWall"},
//		//{Tile::Floor, "TileFloor"},
//		//{Tile::UpStairs, "TileUpStairs"},
//		//{Tile::DownStairs, "TileDownStairs"},
//
//		//{Tile::Door, "TileDoor"},
//		//{Tile::Pit, "TilePit"},
//		//{Tile::Water, "TileWater"},
//		//{Tile::Spikes, "TileSpikes"},
//		#define X(name) { BgTile:: name, "BgTile" #name },
//		LIST_OF_BG_TILE(X)
//		#undef X
//	};
//	//--------
//	return BG_TILE_STR_MAP;
//	//--------
//}
//--------
//--------
//--------
const std::string
	DungeonGen::KIND_STR("DungeonGen");

//auto DungeonGen::RoomPath::from_bv(const binser::Value& bv) -> RoomPath {
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
//			"game_engine::comp::DungeonGen::RoomPath::from_bv(): ",
//			"`ret.rect` does not fit in the playfield: ", ret.rect
//		));
//	}
//	if (!ret.is_path() && !ret.is_room()) {
//		throw std::invalid_argument(sconcat(
//			"game_engine::comp::DungeonGen::RoomPath::from_bv(): ",
//			"`ret.rect` is the wrong shape to be a path or a room: ",
//			ret.rect
//		));
//	}
//
//	return ret;
//}
//DungeonGen::RoomPath::operator binser::Value () const {
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

DungeonGen::DungeonGen() {}
DungeonGen::DungeonGen(const binser::Value& bv) {
	//_rp_data.checked_size = MAX_NUM_ROOM_PATHS;
	//_rp_data.cs_is_max = true;
	////_rp_data.min_size = 0;
	//_rp_data.min_size = MIN_NUM_ROOM_PATHS;

	MEMB_LIST_COMP_DUNGEON(BINSER_MEMB_DESERIALIZE);
}

std::string DungeonGen::kind_str() const {
	return KIND_STR;
}
DungeonGen::operator binser::Value () const {
	binser::Value ret;

	MEMB_LIST_COMP_DUNGEON(BINSER_MEMB_SERIALIZE);

	return ret;
}

void DungeonGen::push_back(RoomPath&& to_push) {
	if (size() + size_t(1) > MAX_NUM_ROOM_PATHS) {
		throw std::length_error(sconcat
			("game_engine::comp::DungeonGen::push_back(): ",
			"`_rp_data.data` cannot increase in size: ",
			//_rp_data.data.size(),
			_rp_data.size(),
			" ", MAX_NUM_ROOM_PATHS));
	}
	//_rp_data.data.push_back(std::move(to_push));
	_rp_data.push_back(RoomPathSptr(new RoomPath(std::move(to_push))));
	//_rp_to_index_umap.insert(std::pair
	//	(_rp_data.back().get(), _rp_data.size() - size_t(1)));
	//_coll_grid.insert(_rp_data.back().get());
}
//CollGridT::DataElPtrUsetT DungeonGen::cg_neighbors(RoomPath& rp) const {
//	return _coll_grid.neighbors(&rp);
//}
//CollGridT::DataElPtrUsetT DungeonGen::cg_neighbors(size_t index) const {
//	return _coll_grid.neighbors(_rp_data.at(index).get());
//}
void DungeonGen::draw() {
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
					BgTile bg_tile = BgTile::Error;

					auto do_draw = [&pos, &bg_tile]() -> void {
						engine->pfield_window.drawable_data_at(pos)
							= drawable_data_umap().at
								(bg_tile_str_map_at(bg_tile));
					};
					const bool in_border
						= rp.pos_in_border(pos);

					if (in_border) {
						// I'm doing this the slow/easy way for now.
						bool did_intersect = false;
						for (size_t j=0; j<i; ++j) {
							if (at(j).rect.intersect(pos)) {
								did_intersect = true;
								//break;
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
							bg_tile = BgTile::Wall;
							do_draw();
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
							if (rp.alt_terrain_umap.contains(pos)) {
								bg_tile = rp.alt_terrain_umap.at(pos);
							} else {
								if (!rp.door_pt_uset.contains(pos)) {
									bg_tile
										= rp.is_path()
										? BgTile::PathFloor
										: BgTile::RoomFloor;
								} else {
									bg_tile = BgTile::Door;
								}
							}
						do_draw();
					}
				} catch (const std::exception& e) {
					printerr("game_engine::comp::DungeonGen::draw(): "
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
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon
