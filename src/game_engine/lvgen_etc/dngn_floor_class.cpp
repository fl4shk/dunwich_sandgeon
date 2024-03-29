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

#include "../comp/drawable_data_umap.hpp"
#include "../comp/item_comp_classes.hpp"
#include "dngn_floor_class.hpp"
#include "path_class.hpp"
#include "dijkstra_map_gen_class.hpp"
#include "bfs_funcs.hpp"
#include "../engine_class.hpp"
#include "../global_shape_constants_etc.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace lvgen_etc {
//--------
AltTerrainInfo AltTerrainInfo::from_bv(const binser::Value& bv) {
	AltTerrainInfo ret;

	MEMB_LIST_LVGEN_ETC_ALT_TERRAIN_STATE(BINSER_MEMB_FROM_BV_DESERIALIZE);

	return ret;
}
AltTerrainInfo::operator binser::Value () const {
	binser::Value ret;

	MEMB_LIST_LVGEN_ETC_ALT_TERRAIN_STATE(BINSER_MEMB_SERIALIZE);

	return ret;
}
//--------
i32 DngnFloor::level_index() {
	return engine->level_index();
}
//--------
DngnFloor::DngnFloor() {}
DngnFloor::DngnFloor(const binser::Value& bv) {
	//_rt_data.checked_size
	//	= RoomTunnel::MAX_NUM_ROOM_TUNNELS_DARR.at(level_index());
	//_rt_data.cs_is_max = true;
	////_rt_data.min_size = 0;
	//_rt_data.min_size
	//	= RoomTunnel::MIN_NUM_ROOM_TUNNELS_DARR.at(level_index());

	MEMB_SER_LIST_LVGEN_ETC_FLOOR_LAYOUT(BINSER_MEMB_DESERIALIZE);
}

DngnFloor::operator binser::Value () const {
	binser::Value ret;

	MEMB_SER_LIST_LVGEN_ETC_FLOOR_LAYOUT(BINSER_MEMB_SERIALIZE);

	return ret;
}
//--------
std::optional<BgTile> DngnFloor::bg_tile_at(
	const IntVec2& pos, size_t i
) const {
	//BgTile bg_tile = BgTile::Blank;
	//std::optional<BgTile> ret = std::nullopt;

	const RoomTunnel& rt = at(i);
	const bool in_border = rt.pos_in_border(pos);

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
		//		const auto j = _rt_to_id_umap
		//			.at(static_cast<RoomTunnel*>(item));
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
		//if (!rt.door_pt_uset.contains(pos)) {
		//	if (rt.alt_terrain_umap.contains(pos)) {
		//		bg_tile = rt.alt_terrain_umap.at(pos);
		//	} else {
		//		bg_tile
		//			= rt.is_tunnel(level_index())
		//			? BgTile::TunnelFloor
		//			: BgTile::RoomFloor;
		//	}
		//} else {
		//	bg_tile = BgTile::Door;
		//}
		return phys_bg_tile_at(pos
			//+
			//+ IntVec2{1, 1}
			//- IntVec2{1, 1}
			);
		//do_draw();
	}
	//return bg_tile;
}
std::optional<BgTile> DngnFloor::phys_bg_tile_at(
	const IntVec2& phys_pos, RoomTunnel** ret_rt
) const {
	//if (!PFIELD_PHYS_RECT2.arg_inside(phys_pos)) {
	//	return std::nullopt;
	//}
	if (!PFIELD_PHYS_NO_BRDR_RECT2.intersect(phys_pos)) {
		return std::nullopt;
	}
	const auto& neighbors = cg_neighbors(phys_pos);

	for (auto& neighbor: neighbors) {
		if (neighbor->bbox().intersect(phys_pos)) {
			RoomTunnel& rt = *static_cast<RoomTunnel*>(neighbor);
			if (ret_rt) {
				*ret_rt = &rt;
			}
			//if (
			//	//!_dbg_did_show
			//	//&&
			//	phys_pos
			//		== IntVec2{9, 16}
			//		//== IntVec2{10, 16}
			//) {
			//	//_dbg_did_show = true;
			//	engine->dbg_log
			//		("DngnFloor::phys_bg_tile_at(): ",
			//		"`AltTerrainState::Normal`: ",
			//		//char(comp::drawable_data_umap().at
			//		//	(bg_tile_str_map_at(*bg_tile)).c),
			//		//char(comp::drawable_data_umap().at
			//		//	(bg_tile_str_map_at
			//		//		(rt.alt_terrain_umap.at(phys_pos))).c),
			//		(rt.alt_terrain_umap.contains(phys_pos)
			//			? sconcat(char(comp::drawable_data_umap().at
			//				(bg_tile_str_map_at
			//					(rt.alt_terrain_umap.at(phys_pos))).c))
			//			: "!contains"), 
			//		"\n");
			//}

			if (ustairs_pos && *ustairs_pos == phys_pos) {
				return BgTile::UpStairs;
			} else if (dstairs_pos && *dstairs_pos == phys_pos) {
				return BgTile::DownStairs;
			} 
			//else if (
			//	rt.door_umap.contains(phys_pos)
			//	&& rt.door_umap.at(phys_pos)
			//) {
			//	//return BgTile::Door;
			//	//return rt.door_umap.at(phys_pos)
			//	//	? BgTile::LockedDoor : BgTile::Door;
			//	return *rt.door_umap.at(phys_pos).bg_tile;
			//}
			else if (
				rt.alt_terrain_umap.contains(phys_pos)
				//&& rt.alt_terrain_umap.at(phys_pos)
				//&& !engine->pfield_ent_id_umap_contains
				//	({phys_pos.x, phys_pos.y, pos3_z()})
				&& !(
					alt_terrain_info_umap.contains(phys_pos)
					&& alt_terrain_info_umap.at(phys_pos).state
						== AltTerrainState::Destroyed
				)
			) {
				if (
					//alt_terrain_info_umap.contains(phys_pos)
					//&& alt_terrain_info_umap.at(phys_pos).alt_bg_tile
					alt_terrain_info_umap.contains(phys_pos)
					&& alt_terrain_info_umap.at(phys_pos).state
						== AltTerrainState::ShowAlt
				) {
					return alt_terrain_info_umap.at(phys_pos).alt_bg_tile;
				}
				else
				//if (
				//	!alt_terrain_info_umap.contains(phys_pos)
				//	|| alt_terrain_info_umap.at(phys_pos).state
				//		== AltTerrainState::Normal
				//)
				{
					//if (
					//	//!_dbg_did_show
					//	//&&
					//	phys_pos == IntVec2{9, 16}
					//) {
					//	//_dbg_did_show = true;
					//	engine->dbg_log
					//		("DngnFloor::phys_bg_tile_at(): ",
					//		"`AltTerrainState::Normal`: ",
					//		//char(comp::drawable_data_umap().at
					//		//	(bg_tile_str_map_at(*bg_tile)).c),
					//		char(comp::drawable_data_umap().at
					//			(bg_tile_str_map_at
					//				(rt.alt_terrain_umap.at(phys_pos))).c),
					//		"\n");
					//}
					return
						//*rt.alt_terrain_umap.at(phys_pos);
						rt.alt_terrain_umap.at(phys_pos);
					//return BgTile::Error;
				}
			}
			//else if (
			//	//gnd_item_umap.contains(phys_pos)
			//	engine->pfield_ent_id_umap_contains
			//		({phys_pos.x, phys_pos.y, pos3_z()})
			//) {
			//	return engine->ecs_engine
			//}
			else {
				return
					rt.is_tunnel(level_index())
					? BgTile::TunnelFloor
					: BgTile::RoomFloor;
			}
		}
	}
	return std::nullopt;
}
//--------
void DngnFloor::_position_ctor_callback(comp::Position* obj) {
	if (
		obj->floor() == _pos3_z
		&& pflprio_is_upper_layer(obj->priority)
	) {
		// Prevent walking through walls here
		if (
			const auto& rt_index = phys_pos_to_rt_index(obj->pos2());
			!rt_index
		) {
			throw std::invalid_argument(sconcat
				("game_engine::lvgen_etc::DngnFloor",
				"::_position_ctor_callback(): Internal error: ",
				"(developer note: `!rt_index)): ",
				*obj, "\n"));
		}

		auto& umap = upper_layer_umap(obj->priority);

		if (umap.contains(obj->pos2())) {
			throw std::invalid_argument(sconcat
				("game_engine::lvgen_etc::DngnFloor",
				"::_position_ctor_callback(): Internal error: ",
				"(developer note: `umap.contains(obj->pos2())`): ",
				*obj, "\n"));
		}
		umap.insert({obj->pos2(), obj->ent_id()});
	} else if (obj->floor() != _pos3_z) {
		throw std::invalid_argument(sconcat
			("game_engine::lvgen_etc::DngnFloor",
			"::_position_ctor_callback(): Internal error: ",
			"(developer note: `obj->floor() != _pos3_z`): ",
			*obj, " ", _pos3_z, "\n"));
	} else { // if (!pflprio_is_upper_layer(obj->priority))
		throw std::invalid_argument(sconcat
			("game_engine::lvgen_etc::DngnFloor",
			"::_position_ctor_callback(): Internal error: ",
			"(developer note: `!pflprio_is_upper_layer(obj->priority)`): ",
			*obj, "\n"));
	}
}
void DngnFloor::_position_dtor_callback(comp::Position* obj) {
	if (
		obj->floor() == _pos3_z
		&& pflprio_is_upper_layer(obj->priority)
	) {
		// Prevent walking through walls here
		//if (rt_index) {
		//	RoomTunnel& rt = _raw_at(*rt_index);
		//} else {
		//	//throw std::invalid_argument
		//	//engine->err
		//}
		if (
			const auto& rt_index = phys_pos_to_rt_index(obj->pos2());
			!rt_index
		) {
			throw std::invalid_argument(sconcat
				("game_engine::lvgen_etc::DngnFloor",
				"::_position_dtor_callback(): Internal error: ",
				"(developer note: `!rt_index)): ",
				*obj, "\n"));
		}

		auto& umap = upper_layer_umap(obj->priority);

		if (!umap.contains(obj->pos2())) {
			throw std::invalid_argument(sconcat
				("game_engine::lvgen_etc::DngnFloor",
				"::_position_dtor_callback(): Internal error: ",
				"(developer note: `!umap.contains(obj->pos2())`): ",
				*obj, "\n"));
		}

		umap.erase(obj->pos2());
	} else if (obj->floor() != _pos3_z) {
		throw std::invalid_argument(sconcat
			("game_engine::lvgen_etc::DngnFloor",
			"::_position_dtor_callback(): Internal error: ",
			"(developer note: `obj->floor() != _pos3_z`): ",
			*obj, " ", _pos3_z, "\n"));
	} else { // if (!pflprio_is_upper_layer(obj->priority))
		throw std::invalid_argument(sconcat
			("game_engine::lvgen_etc::DngnFloor",
			"::_position_dtor_callback(): Internal error: ",
			"(developer note: `!pflprio_is_upper_layer(obj->priority)`): ",
			*obj, "\n"));
	}
}
//void DngnFloor::_position_set_pos3_callback(
//	comp::Position* obj, const IntVec3& n_pos3
//) {
//	if (
//		obj->priority == PfieldLayerPrio::ItemsTraps
//		|| obj->priority == PfieldLayerPrio::CharsMachs
//	) {
//		const auto& rt_index = phys_pos_to_rt_index(obj->pos2());
//		if (rt_index) {
//			RoomTunnel& rt = _raw_at(rt_index);
//		}
//	}
//}
//--------
std::optional<size_t> DngnFloor::phys_pos_to_rt_index(
	const IntVec2& phys_pos
) const {
	//if (!PFIELD_PHYS_NO_BRDR_RECT2.intersect(phys_pos)) {
	//	return std::nullopt;
	//}
	const auto& neighbors = cg_neighbors(phys_pos);

	for (auto& neighbor: neighbors) {
		if (neighbor->bbox().intersect(phys_pos)) {
			return rt_to_id_umap().at(static_cast<RoomTunnel*>(neighbor));
		}
	}
	return std::nullopt;
}
void DngnFloor::push_back(RoomTunnel&& to_push) {
	if (
		size() + 1u
		> RoomTunnel::MAX_NUM_ROOM_TUNNELS_DARR.at(level_index())
	) {
		throw std::length_error(sconcat
			("game_engine::lvgen_etc::DngnFloor::push_back(): ",
			"`_rt_data.data` cannot increase in size: ",
			//_rt_data.data.size(),
			_rt_data.size(),
			" ", level_index(),
			" ", RoomTunnel::MAX_NUM_ROOM_TUNNELS_DARR
				.at(level_index())));
	}
	//to_push.id = i32(size());
	//_rt_data.data.push_back(std::move(to_push));
	_rt_data.push_back(RoomTunnelSptr(new RoomTunnel(std::move(to_push))));
	_rt_to_id_umap.insert(std::pair
		(_rt_data.back().get(), _rt_data.size() - 1u));
	_coll_grid.insert(_rt_data.back().get());
}
void DngnFloor::clear_before_gen(
	//double n_layout_noise_pos_scale,
	//double n_layout_noise_pos_offset
) {
	//_rt_data.data.resize(0);
	//_rt_data.data.clear();
	_rt_data.clear();
	_rt_to_id_umap.clear();
	_coll_grid.clear();
	ustairs_pos
		//= {-1, -1};
		= std::nullopt;
	dstairs_pos = std::nullopt;
	alt_terrain_info_umap.clear();
	//destroyed_alt_terrain_uset.clear();
	//_layout_noise_pos_scale = n_layout_noise_pos_scale;
	//_layout_noise_pos_offset = n_layout_noise_pos_offset;
}
std::pair<bool, Path> DngnFloor::erase_non_walkable_in_path(
	const IntVec2& start_phys_pos, const IntVec2& end_phys_pos,
	const std::optional<IntVec2>& start_r2_sz2d,
	const std::optional<IntVec2>& end_r2_sz2d,
	const BgTileUset& alt_terrain_to_erase_uset,
	// These two `std::optional`s allow the caller of this function to
	// pick between the following options:
	// `std::nullopt`: don't check this layer at all
	// `size() == 0`: any object in this layer blocks passage
	// `size() > 0`: only components listed in the `StrKeyUset` block
	//				passage
	const std::optional<StrKeyUset>& items_traps_to_erase_uset,
	const std::optional<StrKeyUset>& chars_machs_to_erase_uset,
	const BgTileUset& no_pass_bg_tile_uset
) {
	//DijkstraMapGen dmap_gen;
	//dmap_gen.add(start_phys_pos);
	//const auto& dmap = dmap_gen.gen_basic(*this, no_pass_bg_tile_uset);
	//auto path = dmap.make_path(end_phys_pos);
	auto path = bfs_pathfind(start_phys_pos, end_phys_pos,
		*this,
		no_pass_bg_tile_uset);
	//engine->dbg_log
	//	("DngnFloor::erase_alt_terrain_in_path():\n",
	//	"start_phys_pos: ", start_phys_pos, "\n",
	//	"end_phys_pos: ", end_phys_pos, "\n",
	//	"dmap.BOUNDS_R2: ", dmap.BOUNDS_R2, "\n",
	//	"bool(path): ", static_cast<bool>(path), "\n",
	//	"path->size(): ",
	//		(path ? sconcat(path->size()) : "invalid"), "\n");
	//if (path.first) {
		//for (const auto& item: path.second) {
		//	//engine->dbg_log(item, " ");
		//	const auto& bg_tile = phys_bg_tile_at(item);
		//	engine->dbg_log
		//		(item, ": ",
		//		(bg_tile
		//			? sconcat(char(comp::drawable_data_umap().at
		//				(bg_tile_str_map_at(*bg_tile)).c))
		//			: "(invalid)"),
		//		"\n");
		//}
		//engine->dbg_log("\n");
		auto fill_func = [&](const IntVec2& phys_pos) -> bool {
			//const IntVec2
			//	pos = phys_pos - dmap.BOUNDS_R2.tl_corner();
			//engine->dbg_log
			//	("DngnFloor::erase_alt_terrain_in_path(): ",
			//	phys_pos, "\n");
			RoomTunnel* rt;
			const auto& bg_tile = phys_bg_tile_at(phys_pos, &rt);
			if (bg_tile) {
				//--------
				auto upper_layer_func = [this, &phys_pos](
					const std::optional<StrKeyUset>& str_key_uset,
					PfieldLayerPrio prio
				) -> void {
					// `str_key_uset` allows the caller of this function to
					// pick between the following options:
					// `std::nullopt`: don't check this layer at all
					// `size() == 0`: any object in this layer blocks
					//				passage
					// `size() > 0`: only the  `kind_str()`s of each
					//				`ecs::comp`` listed in the `StrKeyUset`
					//				block passage
					if (!str_key_uset) {
						return;
					} else if (str_key_uset->size() == 0) {
						const auto& ul_umap = upper_layer_umap(prio);
						if (ul_umap.contains(phys_pos)) {
							engine->ecs_engine.sched_destroy
								(ul_umap.at(phys_pos));
						}
					} else {
						const auto& ul_umap = upper_layer_umap(prio);
						if (ul_umap.contains(phys_pos)) {
							const ecs::EntId id = ul_umap.at(phys_pos);
							for (const auto& key: *str_key_uset) {
								if (
									engine->ecs_engine.has_ent_w_comp
										(id, key)
								) {
									engine->ecs_engine.sched_destroy(id);
								}
							}
						}
					}
				};
				//--------
				if (
					alt_terrain_to_erase_uset.contains(*bg_tile)
					&& rt->alt_terrain_umap.contains(phys_pos)
				) {
					//engine->dbg_log("testificate\n");
					rt->alt_terrain_umap.erase(phys_pos);
					//rt->alt_terrain_umap[phys_pos] = BgTile::Lava;
				}
				//--------
				upper_layer_func
					(items_traps_to_erase_uset,
					PfieldLayerPrio::ItemsTraps);
				upper_layer_func
					(chars_machs_to_erase_uset,
					PfieldLayerPrio::CharsMachs);
				//--------
				//return true;
				//--------
			}
			//return false;
			return true;
		};
		path.second.fill(fill_func);

		auto erase_endpt_func = [this, &fill_func](
			const IntVec2& endpt_phys_pos,
			const std::optional<IntVec2>& endpt_r2_sz2d
		) -> bool {
			if (
				endpt_r2_sz2d
				&& endpt_r2_sz2d->x != 0 && endpt_r2_sz2d->y != 0
			) {
				//engine->dbg_log
				//	("`endpt_r2_sz2d` non-null and non-zero: ",
				//	*endpt_r2_sz2d, " ", endpt_phys_pos, "\n");
				IntVec2 phys_pos;
				const IntVec2
					phys_pos_tl
						(i32(float(endpt_phys_pos.x)
							+ std::ceil((-(float(endpt_r2_sz2d->x) - 1.0f))
								/ 2.0f)),
						i32(float(endpt_phys_pos.y)
							+ std::ceil((-(float(endpt_r2_sz2d->y) - 1.0f)) 
								/ 2.0f))),
					phys_pos_br
						(i32(float(endpt_phys_pos.x)
							+ std::ceil((float(endpt_r2_sz2d->x) - 1.0f)
								/ 2.0f)),
						i32(float(endpt_phys_pos.y)
							+ std::ceil((float(endpt_r2_sz2d->y) - 1.0f)
								/ 2.0f)));
				//engine->dbg_log
				//	("tl", phys_pos_tl, " ", "br", phys_pos_br, "\n");

				for (
					phys_pos.y=phys_pos_tl.y;
					phys_pos.y<=phys_pos_br.y;
					++phys_pos.y
				) {
					for (
						phys_pos.x=phys_pos_tl.x;
						phys_pos.x<=phys_pos_br.x;
						++phys_pos.x
					) {
						//engine->dbg_log(phys_pos, "\n");
						fill_func(phys_pos);
						//RoomTunnel* rt;
						//const auto& bg_tile
						//	= phys_bg_tile_at(phys_pos, &rt);
						//if (bg_tile) {
						//	if (
						//		//alt_terrain_to_erase_uset.contains
						//		//	(*bg_tile)
						//		//&&
						//		rt->alt_terrain_umap.contains(phys_pos)
						//	) {
						//		rt->alt_terrain_umap.erase(phys_pos);
						//	}
						//}
						//else { // if (!bg_tile)
						//	engine->dbg_log
						//		("didn't have a `bg_tile`: ",
						//		phys_pos, "\n");
						//}
					}
				}
				return true;
			} else {
				return false;
			}
		};
		erase_endpt_func(start_phys_pos, start_r2_sz2d);
		erase_endpt_func(end_phys_pos, end_r2_sz2d);
	//}
	return path;
}
bool DngnFloor::erase_tunnel_during_gen(size_t index) {
	if (
		size() > RoomTunnel::MIN_NUM_ROOM_TUNNELS_DARR.at(level_index())
		&& _rt_data.at(index)->is_tunnel(level_index())
	) {
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
		if (
			auto& rt=*_rt_data.at(index);
			//destroyed_alt_terrain_uset.size() > 0
			//alt_terrain_info_umap
			true
		) {
			const auto& neighbors = cg_neighbors(rt);
			for (auto& neighbor: neighbors) {
				//RoomTunnel* other_rt = static_cast<RoomTunnel*>(neighbor);
				//const size_t other_index = _rt_to_id_umap().at(other_rt);
				if (neighbor->bbox().intersect(rt.rect)) {
					// Rooms and paths are generated as not intersecting
					IntVec2 pos;
					for (
						pos.y=rt.rect.top_y();
						pos.y<=rt.rect.bottom_y();
						++pos.y
					) {
						for (
							pos.x=rt.rect.left_x();
							pos.x<=rt.rect.right_x();
							++pos.x
						) {
							if (alt_terrain_info_umap.contains(pos)) {
								//alt_terrain_info_umap.at(pos).destroyed
								//	= true;
								alt_terrain_info_umap.erase(pos);
								//alt_terrain_info_umap.at(pos).state
								//	= AltTerrainState::Destroyed;
							}
						}
					}
				}
			}
		}

		// We have to erase from `_rt_to_id_umap` and `_coll_grid`
		// before we erase from `_rt_data` due to `_rt_data` being a
		// depedency of `_rt_to_id_umap` and `_coll_grid`.
		_rt_to_id_umap.erase(_rt_data.at(index).get());
		_coll_grid.erase(_rt_data.at(index).get(), std::nullopt);
		_rt_data.erase(_rt_data.begin() + index);
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
			//item.id = i32(i);
		}
		return true;
	}
	return false;
}
CollGridT::DataElPtrUsetT DngnFloor::cg_neighbors(RoomTunnel& rt) const {
	return _coll_grid.neighbors(&rt);
}
CollGridT::DataElPtrUsetT DngnFloor::cg_neighbors(size_t index) const {
	return _coll_grid.neighbors(_rt_data.at(index).get());
}
CollGridT::DataElPtrUsetT DngnFloor::cg_neighbors(const IntVec2& pos)
const {
	RoomTunnel temp_rt; //= {.rect{pos=pos, .size_2d={1, 1}}};
	temp_rt.rect.pos = pos;
	temp_rt.rect.size_2d = {1, 1};
	return _coll_grid.neighbors(&temp_rt);
}
void DngnFloor::draw() const {
	//bg_tile_map->at({0, 0}) = BgTile::Floor;

	// Draw the background
	for (size_t i=0; i<size(); ++i) 
	//for (size_t i=1; i<size(); ++i)
	{
		const RoomTunnel& rt = at(i);
		IntVec2
			pos;
		// Note that rooms are already generated with their borders inside
		// of `engine.pfield_window`
		for (
			pos.y=rt.rect.top_y() - i32(1);
			pos.y<=rt.rect.bottom_y() + i32(1);
			++pos.y
		) {
			for (
				pos.x=rt.rect.left_x() - i32(1);
				pos.x<=rt.rect.right_x() + i32(1);
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
					printerr("game_engine::lvgen_etc::DngnFloor::draw(): ",
						"rt: ",
						"Exception thrown: ", e.what(), "\n");
					throw std::out_of_range(sconcat
						("rt.rect", rt.rect, ", pos", pos, ", ",
						"rs{", rt.rect.right_x(), "}, ",
						"bs{", rt.rect.bottom_y(), "}, ",
						"fp{", rt.fits_in_pfnb(), "}"));
				}
			}
		}
	}
	// Other logic must ensure that both sets of stairs cannot be
	// overwritten.
	for (i32 i=0; i<i32(upper_layer_umap_arr.size()); ++i) {
		const auto& prio = PfieldLayerPrio(i);
		if (pflprio_is_upper_layer(prio)) {
			const auto& umap = upper_layer_umap(prio);
			for (const auto& item: umap) {
				try {
					if (
						engine->ecs_engine.has_ent_w_comp
							(item.second, comp::Drawable::KIND_STR)
					) {
						engine->pfield_window.drawable_data_at(item.first)
							= engine->ecs_engine.casted_comp_at
							<comp::Drawable>(item.second)->data();
					} 
				} catch (const std::exception& e) {
					printerr("game_engine::lvgen_etc::DngnFloor::draw(): ",
						"ul: ",
						"Exception thrown: ", e.what(), "\n");
					throw std::out_of_range(sconcat
						("pos", item.first, ", ent_id", item.second));
				}
			}
		}
	}
}
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
