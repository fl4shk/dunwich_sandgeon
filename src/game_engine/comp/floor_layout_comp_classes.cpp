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

#include "drawable_data_map.hpp"
#include "floor_layout_comp_classes.hpp"
#include "../engine_class.hpp"
#include "../global_shape_constants.hpp"

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
//const std::string
//	StaticBgTileMap::KIND_STR("StaticBgTileMap");
//
//StaticBgTileMap::StaticBgTileMap() {
//	_init_data();
//}
//StaticBgTileMap::StaticBgTileMap(const binser::Value& bv) {
//	_init_data();
//	MEMB_LIST_COMP_STATIC_LAYOUT(BINSER_MEMB_DESERIALIZE);
//}
//std::string StaticBgTileMap::kind_str() const {
//	return KIND_STR;
//}
//StaticBgTileMap::operator binser::Value () const {
//	binser::Value ret;
//
//	MEMB_LIST_COMP_STATIC_LAYOUT(BINSER_MEMB_SERIALIZE);
//
//	return ret;
//}
//
//void StaticBgTileMap::init_data() {
//	_data = {
//		.data=std::vector<binser::VectorEx<BgTile>>(
//			PFIELD_PHYS_SIZE_2D.y,
//			{
//				.data=std::vector<BgTile>(PFIELD_PHYS_SIZE_2D.x, 
//					BgTile::Blank),
//				.checked_size=size_t(PFIELD_PHYS_SIZE_2D.x)
//			}
//		),
//		.checked_size=size_t(PFIELD_PHYS_SIZE_2D.y)
//	};
//}
//void StaticBgTileMap::draw() const {
//	const auto& temp_size_2d = size_2d();
//
//	IntVec2 pos;
//	for (pos.y=0; pos.y<temp_size_2d.y; ++pos.y) {
//		for (pos.x=0; pos.x<temp_size_2d.x; ++pos.x) {
//			engine->pfield_window.drawable_data_at(pos)
//				= drawable_data_map().at(bg_tile_str_map_at(at(pos)));
//		}
//	}
//}
//--------
//--------
const std::string
	DungeonGen::KIND_STR("DungeonGen");

auto DungeonGen::RoomPath::from_bv(const binser::Value& bv) -> RoomPath {
	RoomPath ret;

	MEMB_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_FROM_BV_DESERIALIZE);

	//if (!ret.is_valid())
	if (!ret.fits_in_pfield()) {
		//throw std::invalid_argument(sconcat(
		//		(func_name ? sconcat(*func_name, "(): ") : std::string()),
		//		(msg ? sconcat(*msg, ": ") : std::string()),
		//		data_str, " < ", min_str,
		//			" || ", data_str, " || ", max_str,
		//			": ",
		//		data, " ", min, " ", max
		//));
		throw std::invalid_argument(sconcat(
			"game_engine::comp::DungeonGen::RoomPath::from_bv(): ",
			"`ret.rect` does not fit in the playfield: ", ret.rect
		));
	}
	if (!ret.is_path() && !ret.is_room()) {
		throw std::invalid_argument(sconcat(
			"game_engine::comp::DungeonGen::RoomPath::from_bv(): ",
			"`ret.rect` is the wrong shape to be a path or a room: ",
			ret.rect
		));
	}

	return ret;
}
DungeonGen::RoomPath::operator binser::Value () const {
	binser::Value ret;

	//MEMB_EX_MM_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_SERIALIZE);
	//MEMB_EX_CS_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_SERIALIZE);
	//MEMB_AUTOSER_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_SERIALIZE);
	//BINSER_MEMB_SERIALIZE(rect);
	MEMB_LIST_COMP_DUNGEON_ROOM_PATH(BINSER_MEMB_SERIALIZE);

	return ret;
}

//auto DungeonGen::Path::from_bv(const binser::Value& bv) -> Path {
//	Path ret;
//
//	#define X(...) BINSER_MEMB_FROM_BV_DESERIALIZE_EX_MM(__VA_ARGS__)
//	MEMB_EX_MM_LIST_COMP_DUNGEON_PATH(X);
//	#undef X
//
//	//#define X(...) BINSER_MEMB_FROM_BV_DESERIALIZE_EX_CS(__VA_ARGS__)
//	//MEMB_EX_CS_LIST_COMP_DUNGEON_PATH(X);
//	//#undef X
//
//	#define X(...) BINSER_MEMB_FROM_BV_DESERIALIZE(__VA_ARGS__)
//	MEMB_AUTOSER_LIST_COMP_DUNGEON_PATH(X);
//	#undef X
//
//	//if (DblVec2Ex temp_pos=PFIELD_WINDOW_EX_RANGE; true) {
//	//	binser::get_bv_memb(temp_pos, bv, "pos", std::nullopt);
//	//	ret.pos = std::move(temp_pos.data);
//	//}
//	//if (binser::ScalarEx<decltype(size)> temp_size={
//	//		.data=0u, .max=MAX_SIZE, .min=MIN_SIZE
//	//	};
//	//	true) {
//	//	binser::get_bv_memb(temp_size, bv, "size", std::nullopt);
//	//	ret.size = std::move(temp_size.data);
//	//}
//
//	return ret;
//}
//DungeonGen::Path::operator binser::Value () const {
//	binser::Value ret;
//
//	MEMB_EX_MM_LIST_COMP_DUNGEON_PATH(BINSER_MEMB_SERIALIZE);
//	MEMB_AUTOSER_LIST_COMP_DUNGEON_PATH(BINSER_MEMB_SERIALIZE);
//
//	return ret;
//}
//bool DungeonGen::Path::overlaps(const Path& path) const {
//}

DungeonGen::DungeonGen() {}
DungeonGen::DungeonGen(const binser::Value& bv) {
	_data.checked_size = MAX_NUM_ROOM_PATHS;
	_data.cs_is_max = true;
	//_data.min_size = 0;
	_data.min_size = MIN_NUM_ROOM_PATHS;

	//_path_vec.checked_size = MAX_NUM_PATHS;
	//_path_vec.cs_is_max = true;
	//_path_vec.min_size = MIN_NUM_PATHS;

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

//void DungeonGen::draw(StaticBgTileMap* bg_tile_map)
void DungeonGen::draw() {
	//bg_tile_map->at({0, 0}) = BgTile::Floor;
	for (size_t i=0; i<size(); ++i) {
		const RoomPath& rp = at(i);
		IntVec2
			pos, local_pos;
		for (
			pos.y=math::max_va(
				rp.rect.top_y() - i32(1),
				PFIELD_PHYS_RECT2.top_y()
			),
				local_pos.y=0;
			pos.y<=math::min_va(
				rp.rect.bottom_y() + i32(1),
				PFIELD_PHYS_RECT2.bottom_y()
			);
			++pos.y, ++local_pos.y
		) {
			for (
				pos.x=math::max_va(
					rp.rect.left_x() - i32(1),
					PFIELD_PHYS_RECT2.left_x()
				),
					local_pos.x=0;
				pos.x<=math::min_va(
					rp.rect.right_x() + i32(1),
					PFIELD_PHYS_RECT2.right_x()
				);
				++pos.x, ++local_pos.x
			) {
				try {
					BgTile bg_tile = BgTile::Error;

					auto do_draw = [&pos, &bg_tile]() -> void {
						engine->pfield_window.drawable_data_at(pos)
							= drawable_data_map().at(
								bg_tile_str_map_at(bg_tile)
							);
					};
					const bool in_border = (!(
						(local_pos.x > 0)
						&& (local_pos.x < rp.rect.size_2d.x + 1)
						&& (local_pos.y > 0)
						&& (local_pos.y < rp.rect.size_2d.y + 1)
					));

					if (rp.is_path()) {
						bg_tile = BgTile::PathFloor;
						if (!in_border) {
							do_draw();
						}
					} else if (rp.is_room()) {
						if (in_border) {
							// I'm doing this the slow/easy way for now.
							bool did_intersect = false;
							for (size_t j=0; j<i; ++j) {
								if (at(j).rect.intersect(pos)) {
									did_intersect = true;
								}
							}
							if (!did_intersect) {
								bg_tile = BgTile::Wall;
								do_draw();
							}
						} else { // if (!in_border)
							//if (!rp.door_pt_set.contains(pos)) {
								bg_tile = BgTile::RoomFloor;
							//} else {
							//	bg_tile = BgTile::Door;
							//}
							do_draw();
						}
					}
				} catch (const std::exception& e) {
					printerr("game_engine::comp::DungeonGen::draw(): "
						"Exception thrown: ", e.what(), "\n");
					throw std::out_of_range(sconcat(
						"rp.rect",rp.rect, ", pos", pos, ", ",
						"rs{", rp.rect.right_x(), "}, ",
						"bs{", rp.rect.bottom_y(), "}, ",
						"fp{", rp.fits_in_pfield(), "}"
						
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
