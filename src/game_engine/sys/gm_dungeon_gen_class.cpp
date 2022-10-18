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

#include "gm_dungeon_gen_class.hpp"
#include "../metaball_gen_class.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace sys {
//--------
const std::string
	GmDungeonGen::KIND_STR("GmDungeonGen");

std::string GmDungeonGen::kind_str() const {
	return KIND_STR;
}
const std::vector<std::vector<GmDungeonGen::BgTile>>
	GmDungeonGen::LEVEL_ALLOWED_ALT_TERRAIN_V2D({
		// Level 1 (index 0)
		build_alt_terrain_vec
			(//AtvPair(20, ALT_TERRAIN_NONE),
			AtvPair(5, ALT_TERRAIN_NONE),
			AtvPair(1, BgTile::Water),
			AtvPair(1, BgTile::Spikes)
			//AtvPair(3, BgTile::Lava)
			),

		// Level 2 (index 1)
		build_alt_terrain_vec
			(AtvPair(6, ALT_TERRAIN_NONE),
			BgTile::Water,
			BgTile::Spikes,
			BgTile::Pit),

		// Level 3 (index 2)
		build_alt_terrain_vec
			(AtvPair(5, ALT_TERRAIN_NONE),
			BgTile::Water,
			BgTile::Lava,
			BgTile::Spikes,
			BgTile::Pit),

		// Level 4 (index 3)
		build_alt_terrain_vec
			(AtvPair(5, ALT_TERRAIN_NONE),
			BgTile::Lava,
			BgTile::Spikes),

		// Level 5 (index 4)
		build_alt_terrain_vec
			(AtvPair(5, ALT_TERRAIN_NONE),
			BgTile::Lava,
			BgTile::Spikes),
	});

void GmDungeonGen::clear_dungeon_gen(ecs::Engine* ecs_engine) {
	auto* dungeon_gen
		= ecs_engine->casted_comp_at<DungeonGen>(*_dungeon_gen_id);
	dungeon_gen->clear();
	//dungeon_gen->clear(engine->calc_layout_noise_add_amount());
}
void GmDungeonGen::_init(ecs::Engine* ecs_engine) {
	_init_start();

	const std::string func_name("game_engine::sys::GmDungeonGen::_init");

	//if (ecs_engine->has_ent_w_comp(
	//	make_key_set<ecs::NonSerializable, comp::StaticBgTileMap>()
	//)) {
	//}

	//if (!_bg_tile_map_id) {
	//	_bg_tile_map_id = ecs_engine->create_singleton_all(
	//		ecs::make_comp_map_ks(
	//			ecs::CompSptr(new ecs::NonSerializable()),
	//			ecs::CompSptr(new comp::StaticBgTileMap())
	//		),
	//		func_name
	//	);
	//}
	if (!_dungeon_gen_id) {
		_dungeon_gen_id = ecs_engine->create_singleton_all(
			ecs::make_comp_map_ks(
				ecs::CompSptr(new ecs::NonSerializable()),
				ecs::CompSptr(new DungeonGen())
			),
			func_name
		);

		engine->log("game_engine::sys::GmDungeonGen::_init(): ",
			*_dungeon_gen_id, "\n");
	}
	clear_dungeon_gen(ecs_engine);
}

void GmDungeonGen::tick(ecs::Engine* ecs_engine) {
	if (
		_tick_helper(ecs_engine,
			engine->game_mode() == GameMode::DungeonGen)
	) {
		//auto* bg_tile_map
		//	= ecs_engine->casted_comp_at<comp::StaticBgTileMap>(
		//		*_bg_tile_map_id
		//	);
		auto* dungeon_gen
			= ecs_engine->casted_comp_at<DungeonGen>
				(*_dungeon_gen_id);

		//if (engine->key_status.key_just_went_down(KeyKind::DownR))
		{
			//if (dungeon_gen->size() == 0) {
			//	engine->log("Debug: starting dungeon generation.\n");
			//}
			while (!_done_generating) {
				GenInnards innards(this, ecs_engine, dungeon_gen);
				innards.gen_single_rp();
				if (_done_generating) {
					innards.finalize_basic(
						//true
					);
					innards.insert_alt_terrain(
						true
					);
				}
			}
			//else {
			//	engine->log("Debug: We're already done generating\n");
			//}
		}
		//if (dungeon_gen->size() >= 2) {
		//	clear_dungeon_gen(ecs_engine);
		//}

		//dungeon_gen->draw(bg_tile_map);
		//bg_tile_map->draw();
		engine->pfield_window.clear();
		dungeon_gen->draw();
		engine->screen_window.clear();

		engine->screen_window.draw(engine->pfield_window);
		engine->screen_window.draw(engine->log_window);
		engine->screen_window.draw(engine->hud_window);
	}
}

//void GmDungeonGen::_connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
//	DungeonGen* dungeon_gen) {
//}
bool GmDungeonGen::GenInnards::gen_single_rp() {
	//--------
	if (_dungeon_gen->size() == 0) {
		_self->_attempted_num_rp = engine->layout_rand<i32>
			(i32(MIN_NUM_ROOM_PATHS), i32(MAX_NUM_ROOM_PATHS));
		_self->_stop_gen_early = false;
		_self->_done_generating = false;

		// We always generate a room in this case.
		//for (i32 tries=0; tries<GEN_RP_LIM_TRIES; ++tries)
		// Force there to be at least one room
		for (;;) {
			RoomPath to_push_rp;
			//--------
			//engine->log("testificate 2\n");
			//--------
			to_push_rp.rect.pos.x = engine->layout_rand<i32>
				(PFIELD_PHYS_RECT2.left_x(),
				PFIELD_PHYS_RECT2.right_x() - ROOM_MIN_SIZE_2D.x - 1);
			to_push_rp.rect.pos.y = engine->layout_rand<i32>
				(PFIELD_PHYS_RECT2.top_y(),
				PFIELD_PHYS_RECT2.bottom_y() - ROOM_MIN_SIZE_2D.y - 1);

			to_push_rp.rect.size_2d.x = engine->layout_rand<i32>
				(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
			to_push_rp.rect.size_2d.y = engine->layout_rand<i32>
				(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y);
			//--------
			if (to_push_rp.fits_in_pfield_nb()) {
				_do_push_back(std::move(to_push_rp));
				break;
			}
			//--------
		}
	}
	//else if (_dungeon_gen->size() < MAX_NUM_ROOM_PATHS)
	else if (i32(_dungeon_gen->size()) < _self->_attempted_num_rp) {
		//RoomPath to_push_rp;
		//if (_dungeon_gen->size() < MIN_NUM_ROOM_PATHS) {
		//	for (;;) {
		//		if (auto opt_rp=_inner_gen_post_first(); opt_rp) {
		//			_do_push_back(std::move(*opt_rp));
		//			break;
		//		}
		//	}
		//} else if (!_self->_stop_gen_early) {
			i32 tries = 0;
			for (; tries<GEN_RP_LIM_TRIES; ++tries) {
				_self->_stop_gen_early = true;
				if (auto opt_rp=_inner_gen_post_first(); opt_rp) {
					_do_push_back(std::move(*opt_rp));
					_self->_stop_gen_early = false;
					break;
				}
			}
			//_self->_stop_gen_early = tries >= GEN_RP_LIM_TRIES;
			if (_self->_stop_gen_early) {
				if (_dungeon_gen->size() < MIN_NUM_ROOM_PATHS) {
					engine->log
						("Debug: game_engine::sys::gen_single_rp(): ",
						"Redoing generation\n");
					_self->clear_dungeon_gen(_ecs_engine);
				} else {
					// If we failed to find a room that fits in the
					// playfield, we stop floor generation early, and don't
					// try any more for this floor.  This is to prevent
					// infinite loops in the dungeon generation.
					engine->log
						("Debug: game_engine::sys::gen_single_rp(): ",
						"stopping room generation early: ",
						_dungeon_gen->size(), " ",
						_self->_attempted_num_rp, "\n");
				}
			}
			//else {
			//}
		//}
	}
	const bool old_done_generating = _self->_done_generating;
	_self->_done_generating
		= _self->_stop_gen_early
			|| i32(_dungeon_gen->size()) >= _self->_attempted_num_rp;
	if (!old_done_generating && _self->_done_generating) {
		engine->log("Just finished generating the dungeon.\n");
	}

	return _self->_done_generating;
}
auto GmDungeonGen::GenInnards::_inner_gen_post_first()
-> std::optional<RoomPath> {
	//--------
	//RoomPath _to_push_rp;

	if (auto temp=_gen_initial_rp(); temp) {
		_to_push_rp = std::move(*temp);
	} else {
		return std::nullopt;
	}
	//--------
	//const IntRect2
	//	ORIG_TO_PUSH_RECT = _to_push_rp.rect;
	//const bool
	//	was_horiz_path = DungeonGen::r2_is_horiz_path(ORIG_TO_PUSH_RECT),
	//	was_vert_path = DungeonGen::r2_is_vert_path(ORIG_TO_PUSH_RECT);
	//	//was_room = DungeonGen::r2_is_room(ORIG_TO_PUSH_RECT);
	//--------
	//--------
	auto basic_shrink_extra_test_func = [this](
		RoomPath& some_rp
		//, const std::optional<size_t>& index
	) -> bool {
		const auto& found
			= _find_first_backend(
				some_rp, std::nullopt,
				[](RoomPath& some_rp, const RoomPath& some_item)
				-> bool {
					//return !(some_item.rect.intersect(some_rp.rect)
					//	|| _some_sides_hit(some_rp, some_item)
					//	|| !_path_sides_hit_wrongly(some_rp, some_item));
					return (some_item.rect.intersect(some_rp.rect)
						//&& _some_sides_hit(some_rp, some_item)
						|| _path_sides_hit_wrongly(some_rp, some_item)
						// Reject pairs of horizontal/vertical paths that
						// are too close
						|| _parallel_paths_too_close(some_rp, some_item));
				});
		//if (found) {
		//	//printout("found{", *found, "}\n");
		//	printout("found\n");
		//} else {
		//	printout("!found\n");
		//}
		return (some_rp.fits_in_pfield_nb()
			&& !found
			//&& !any_intersect_find_first(some_rp, std::nullopt)
			//&& any_sides_intersect_find_first(some_rp, std::nullopt)
			//&& !any_path_sides_hit_wrongly_find_first
			//	(some_rp, std::nullopt)
			&& _rp_is_connected(some_rp));
	};
	// This is a simple algorithm that could be made faster and
	// more complicated, but I figure any platform running this
	// game will have fast enough hardware considering the maximum
	// numbers of rooms/paths.
	if (!_shrink(
		_to_push_rp.is_horiz_path(), _to_push_rp.is_vert_path(),
		_to_push_rp, // std::nullopt,
		basic_shrink_extra_test_func
	)) {
		return std::nullopt;
	}


	//if (any_intersect_find_first(_to_push_rp, std::nullopt)) {
	//	//engine->log("Debug: found early intersect!\n");
	//	return std::nullopt;
	//}
	//if (any_path_sides_hit_wrongly_find_first(_to_push_rp, std::nullopt)) {
	//	return std::nullopt;
	//}

	//const i32
	//	START_ITEM_INDEX = engine->layout_rand<i32>
	//		(0, _dungeon_gen->size() - 1);
	//for (
	//	size_t basic_index=0, item_index=START_ITEM_INDEX;
	//	basic_index<_dungeon_gen->size();
	//	++basic_index,
	//		item_index = (item_index + 1) % _dungeon_gen->size()
	//	//size_t item_index=START_ITEM_INDEX;
	//	//item_index 
	//	//	!= (
	//	//		START_ITEM_INDEX == 0
	//	//		? _dungeon_gen->size()
	//	//		: START_ITEM_INDEX - 1
	//	//	);
	//	//item_index = (item_index + 1) % _dungeon_gen->size()
	//) {
	//for (const auto& item: *_dungeon_gen)
		//auto& item = _dungeon_gen->at(item_index);


		//std::vector<RoomPath> temp_rect_vec;
		//auto gen_temp_rect_vec_elem = [&](
		//	//bool hit_happened,
		//	i32 some_side,
		//	const std::pair<IntVec2, IntVec2>& rp_offset_pair
		//	//const std::pair<IntVec2, IntVec2>& item_offset_pair
		//	//const std::string& dbg_str, bool do_dbg_print
		//) -> void {
		//	//if (
		//	//	hit_happened
		//	//	//&& should_gen_connect()
		//	//) {
		//		//RoomPath temp_rp;
		//		RoomPath temp_rp;
		//		//std::optional<size_t> opt_index(std::nullopt);

		//		//if (!engine->layout_rand<i32>(0, 1)) {
		//			//auto& temp_rp_pair = temp_rp_pair_vec.at(some_side);
		//			//temp_rp_pair.first = RoomPath();
		//			//temp_rp = &(*temp_rp_pair.first);
		//			temp_rp.rect
		//				= _to_push_rp.rect.build_in_grid_inflated_lim
		//					(rp_offset_pair.first,
		//					rp_offset_pair.second,
		//					PFIELD_PHYS_NO_BRDR_RECT2);
		//		//} else {
		//		//	//auto& temp_rp_pair = temp_rp_pair_vec.at(some_side);
		//		//	//temp_rp_pair.second = RoomPath();
		//		//	//temp_rp = &(*temp_rp_pair.second);
		//		//	temp_rp.rect
		//		//		= item.rect.build_in_grid_inflated_lim
		//		//		(item_offset_pair.first,
		//		//		item_offset_pair.second,
		//		//		PFIELD_PHYS_NO_BRDR_RECT2);
		//		//}
		//		//_shrink(*temp_rp);
		//	}
		//};
		//gen_temp_rect_vec_elem
		//	(//_ls_and_rs_hit(_to_push_rp, item),
		//	GEN_SIDE_L,
		//	std::pair(IntVec2{GEN_EXTEND_AMOUNT_TSF, 0}, IntVec2())
		//	//std::pair(IntVec2(), IntVec2{GEN_EXTEND_AMOUNT_TSF, 0})
		//	);
		//gen_temp_rect_vec_elem
		//	(//_ts_and_bs_hit(_to_push_rp, item),
		//	GEN_SIDE_T,
		//	std::pair(IntVec2{0, GEN_EXTEND_AMOUNT_TSF}, IntVec2())
		//	//std::pair(IntVec2(), IntVec2{0, GEN_EXTEND_AMOUNT_TSF})
		//	);
		//gen_temp_rect_vec_elem
		//	(//_ls_and_rs_hit(item, _to_push_rp),
		//	GEN_SIDE_R,
		//	std::pair(IntVec2(), IntVec2{GEN_EXTEND_AMOUNT_TSF, 0})
		//	//std::pair(IntVec2{GEN_EXTEND_AMOUNT_TSF, 0}, IntVec2())
		//	);
		//gen_temp_rect_vec_elem
		//	(//_ts_and_bs_hit(item, _to_push_rp),
		//	GEN_SIDE_B,
		//	std::pair(IntVec2(), IntVec2{0, GEN_EXTEND_AMOUNT_TSF})
		//	//std::pair(IntVec2{0, GEN_EXTEND_AMOUNT_TSF}, IntVec2())
		//	);
		//if (
		//	const i32 check_first_extend_side=engine->layout_rand<i32>
		//		(MIN_GEN_SIDE, MAX_GEN_SIDE);
		//	true
		//) {
		//	i32
		//		i
		//			//= MIN_GEN_SIDE;
		//			= std::abs(MAX_GEN_SIDE - MIN_GEN_SIDE),
		//		extend_side = check_first_extend_side;

		//	auto end_loop = [&i, &extend_side]() -> void {
		//		--i;
		//		++extend_side;
		//		if (extend_side > MAX_GEN_SIDE) {
		//			extend_side = MIN_GEN_SIDE;
		//		}
		//	};
		//	//while (i <= MAX_GEN_SIDE)
		//	while (i >= 0) {
		//		auto& temp_rect_pair
		//			= temp_rp_pair_vec.at(extend_side);
		//		RoomPath
		//			* temp_rp = nullptr,
		//			* to_edit_rp = nullptr,
		//			* to_keep_rp = nullptr;
		//		std::string dbg_str = "";

		//		auto show_debug_maybe = [&]() -> void {
		//			engine->log("Debug: **MAYBE** doing extension: ",
		//				dbg_str,
		//				"{", to_edit_rp->rect.tl_corner(), " ",
		//					to_edit_rp->rect.br_corner(), "} ",
		//				"temp_rp",
		//				"{", temp_rp->rect.tl_corner(), " ",
		//					temp_rp->rect.br_corner(), "}",
		//				"\n");
		//		};

		//		if (temp_rect_pair.first) {
		//			temp_rp = &(*temp_rect_pair.first);

		//			if (any_intersect_find_first(*temp_rp, std::nullopt)) {
		//				engine->log("first testificate 0 \n");
		//				//return std::nullopt;
		//				//end_loop();
		//				//continue;
		//			} else {
		//				engine->log("first testificate 1\n");
		//				dbg_str = "_to_push_rp";
		//				to_edit_rp = &_to_push_rp;
		//				to_keep_rp = &item;
		//				show_debug_maybe();
		//			}
		//		} else if (temp_rect_pair.second) {
		//			temp_rp = &(*temp_rect_pair.second);

		//			if (any_intersect_find_first(*temp_rp, item_index)) {
		//				engine->log("second testificate 0\n");
		//				//return std::nullopt;
		//				//end_loop();
		//				//continue;
		//			} else {
		//				engine->log("second testificate 1\n");
		//				dbg_str = "item";
		//				to_edit_rp = &item;
		//				to_keep_rp = &_to_push_rp;
		//				show_debug_maybe();
		//			}
		//		}
		//		//else {
		//		//	engine->log("testificate\n");
		//		//}
		//		if (temp_rp && to_edit_rp && to_keep_rp
		//			&& !(
		//				(to_edit_rp->is_horiz_path()
		//					&& !temp_rp->is_horiz_path())
		//				|| (to_edit_rp->is_vert_path()
		//					&& !temp_rp->is_vert_path())
		//			) //&& !_path_sides_hit_wrongly(*temp_rp, *to_edit_rp)
		//			&& temp_rp->is_valid()
		//			&& !any_path_sides_hit_wrongly_find_first(*temp_rp,
		//				((dbg_str == "item")
		//					? std::optional<size_t>(item_index)
		//					: std::nullopt))
		//			&& !_path_sides_hit_wrongly(*temp_rp, *to_keep_rp)
		//			//&& !any_path_sides_hit_wrongly_find_first(*to_edit_rp,
		//			//	((dbg_str == "item")
		//			//		? std::optional<size_t>(item_index)
		//			//		: std::nullopt))
		//		) {
		//			engine->log("Debug: doing extension: ",
		//				"dbg_str{\"", dbg_str, "\"} ",
		//				"_to_push_rp{", _to_push_rp.rect.tl_corner(), " ",
		//					_to_push_rp.rect.br_corner(), "} ",
		//				"item{", item.rect.tl_corner(), " ",
		//					item.rect.br_corner(), "} ",
		//				"temp_rp",
		//				"{", temp_rp->rect.tl_corner(), " ",
		//					temp_rp->rect.br_corner(), "}",
		//				"\n");
		//			to_edit_rp->rect = temp_rp->rect;
		//		}
		//		end_loop();
		//	}
		//	//if (i > MAX_GEN_SIDE) {
		//	//	engine->log("testificate\n");
		//	//	return std::nullopt;
		//	//}
		//}

		//maybe_extend_l();
		//maybe_extend_t();
		//maybe_extend_r();
		//maybe_extend_b();
		//std::vector<RoomPath> temp_rect_vec;
	//}
	auto should_gen_connect = []() -> bool {
		const i32
			temp = engine->layout_rand<i32>
				(GEN_YN_CONNECT.full_min(), GEN_YN_CONNECT.full_max());
		return (temp >= GEN_YN_CONNECT.yes_min()
			&& temp <= GEN_YN_CONNECT.yes_max);
	};
	const bool
		was_horiz_path = _to_push_rp.is_horiz_path(),
		was_vert_path = _to_push_rp.is_vert_path();
	for (
		i32 basic_side=MIN_GEN_SIDE,
			temp_side=engine->layout_rand<i32>
				(MIN_GEN_SIDE, MAX_GEN_SIDE);
		basic_side<=MAX_GEN_SIDE;
		++basic_side,
			temp_side=(temp_side + 1)
				% (MAX_GEN_SIDE - MIN_GEN_SIDE + 1)
	) {
		auto attempt_extend = [&](
			const IntVec2& tl_ext, const IntVec2& br_ext
		) -> void {
			RoomPath temp_rp;
			temp_rp.rect = _to_push_rp.rect.build_in_grid_inflated_lim
				(tl_ext, br_ext, PFIELD_PHYS_NO_BRDR_RECT2);
			if (_shrink(
				was_horiz_path, was_vert_path,
				temp_rp, basic_shrink_extra_test_func
			)) {
				_to_push_rp.rect = temp_rp.rect;
			}
		};
		switch (temp_side) {
		//--------
		case GEN_SIDE_L:
			if (
				should_gen_connect()
				&& (_to_push_rp.is_horiz_path() || _to_push_rp.is_room())
			){
				attempt_extend
					(IntVec2{GEN_EXTEND_AMOUNT_TSF, 0}, IntVec2());
			}
			break;
		case GEN_SIDE_T:
			if (
				should_gen_connect()
				&& (_to_push_rp.is_vert_path() || _to_push_rp.is_room())
			) {
				attempt_extend
					(IntVec2{0, GEN_EXTEND_AMOUNT_TSF}, IntVec2());
			}
			break;
		case GEN_SIDE_R:
			if (
				should_gen_connect()
				&& (_to_push_rp.is_horiz_path() || _to_push_rp.is_room())
			) {
				attempt_extend
					(IntVec2(), IntVec2{GEN_EXTEND_AMOUNT_TSF, 0});
			}
			break;
		case GEN_SIDE_B:
			if (
				should_gen_connect()
				&& (_to_push_rp.is_vert_path() || _to_push_rp.is_room())
			) {
				attempt_extend
					(IntVec2(), IntVec2{0, GEN_EXTEND_AMOUNT_TSF});
			}
			break;
		default:
			throw std::runtime_error(sconcat
				("game_engine::sys::GmDungeonGen",
				"::_inner_gen_post_first(): ",
				"`switch (temp_side)`: Eek! `", temp_side, "`"));
			break;
		//--------
		}
	}
	//--------
	//_to_push_rp.conn_index_uset.insert(conn_rp_index);
	//conn_rp.conn_index_uset.insert(_dungeon_gen->size());
	//--------
	//--------
	//engine->log("`gen_type`: ", gen_type, "\n");

	return _to_push_rp;
	//--------
};
auto GmDungeonGen::GenInnards::_gen_initial_rp()
-> std::optional<RoomPath> {
	//--------
	RoomPath to_push_rp;

	const i32
		prev_rp_index = _dungeon_gen->size() - 1;
	const RoomPath
		& prev_rp = _dungeon_gen->at(prev_rp_index);
	const i32
		prev_gen_type
			= prev_rp.is_path() ? GEN_TYPE_PATH : GEN_TYPE_ROOM;

	_gen_side = 0;
	_gen_next_type = 0;
	_gen_next_conn_rp_index = 0;
	_gen_type = 0;
	_conn_rp_index = 0;

	//_gen_type = GEN_TYPE_ROOM,
	//_gen_side = engine->layout_rand<i32>
	//	(MIN_GEN_SIDE, MAX_GEN_SIDE),

	_gen_next_type = (prev_gen_type == GEN_TYPE_PATH)
		? engine->layout_rand<i32>
			(GEN_NEXT_PATH_TYPE.full_min(),
			GEN_NEXT_PATH_TYPE.full_max())
		: engine->layout_rand<i32>
			(GEN_NEXT_ROOM_TYPE.full_min(),
			GEN_NEXT_ROOM_TYPE.full_max()),

	_gen_type = 0;
	if (
		(
			prev_gen_type == GEN_TYPE_PATH
			&& _gen_next_type >= GEN_NEXT_PATH_TYPE.same_min()
			&& _gen_next_type <= GEN_NEXT_PATH_TYPE.same_max
		) || (
			prev_gen_type == GEN_TYPE_ROOM
			&& _gen_next_type >= GEN_NEXT_ROOM_TYPE.same_min()
			&& _gen_next_type <= GEN_NEXT_ROOM_TYPE.same_max
		)
	) {
		_gen_type = prev_gen_type;
	} else { // if (switching types
		do {
			_gen_type = engine->layout_rand<i32>
				(MIN_GEN_TYPE, MAX_GEN_TYPE);
		} while (_gen_type == prev_gen_type);
	}
	//--------
	auto index_stuff = [&](const GenNext& some_gen_next_index) -> void {
		_gen_next_conn_rp_index
			= engine->layout_rand<i32>
			(some_gen_next_index.full_min(),
			some_gen_next_index.full_max());
		if (
			_gen_next_conn_rp_index >= some_gen_next_index.same_min()
			&& _gen_next_conn_rp_index <= some_gen_next_index.same_max
		) {
			_conn_rp_index = prev_rp_index;
		} else {
			if (prev_rp_index == 0) {
				_conn_rp_index = prev_rp_index;
			} else { // if (prev_rp_index > 0)
				// Force a different room from the last one to be
				// picked in this case
				_conn_rp_index
					= engine->layout_rand<i32>(0, prev_rp_index - 1);
			}
		}
	};
	if (prev_gen_type == GEN_TYPE_PATH) {
		if (_gen_type == GEN_TYPE_PATH) {
			index_stuff(GEN_NEXT_PATH_INDEX_NOW_PATH);
		} else { // if (_gen_type == GEN_TYPE_ROOM)
			index_stuff(GEN_NEXT_PATH_INDEX_NOW_ROOM);
		}
		//index_stuff(GEN_NEXT_PATH_INDEX);
	} else { // if (prev_gen_type == GEN_TYPE_ROOM)
		index_stuff(GEN_NEXT_ROOM_INDEX);
	}
	//--------
	//const i32 _conn_rp_index = engine->layout_rand<i32>(0, 0);
	//engine->log("test 1\n");
	const auto& conn_rp = _dungeon_gen->at(_conn_rp_index);

	if (
		//(conn_rp.is_path() && _gen_type == GEN_TYPE_PATH)
		//|| (conn_rp.is_room() && _gen_type == GEN_TYPE_ROOM)

		//(conn_rp.is_path() && _gen_type == GEN_TYPE_PATH)
		//|| conn_rp.is_room()
		conn_rp.is_path()
	) {
		if (_gen_type == GEN_TYPE_PATH) {
			_gen_side = engine->layout_rand<i32>
				(MIN_GEN_SIDE, MAX_GEN_SIDE);
		} else { // if (_gen_type == GEN_TYPE_ROOM)
			if (conn_rp.is_horiz_path()) {
				_gen_side
					= engine->layout_rand<i32>(0, 1)
					? GEN_SIDE_L
					: GEN_SIDE_R;
			} else { // if (conn_rp.is_vert_path())
				_gen_side
					= engine->layout_rand<i32>(0, 1)
					? GEN_SIDE_T
					: GEN_SIDE_B;
			}
		}
	} else { // if (conn_rp.is_room())
		_gen_side = engine->layout_rand<i32>
			(MIN_GEN_SIDE, MAX_GEN_SIDE);
	}
	//--------
	i32
		thickness = 0,
		length = 0;
	//IntVec2
	//	temp_size_2d;

	if (_gen_type == GEN_TYPE_PATH) {
		thickness
			//temp_size_2d.x
			= PATH_THICKNESS,
		length
			//temp_size_2d.y
			= engine->layout_rand<i32>
				(PATH_MIN_LEN, PATH_MAX_LEN);
	} else { // if (_gen_type == GEN_TYPE_ROOM)
		const IntVec2 temp_vec2
		//temp_size_2d =
			{.x=engine->layout_rand<i32>
				(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x),
			.y=engine->layout_rand<i32>
				(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y)};
		//thickness = engine->layout_rand<i32>
		//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
		//length = engine->layout_rand<i32>
		//	(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y);

		if (_gen_side == GEN_SIDE_L || _gen_side == GEN_SIDE_R) {
			thickness = temp_vec2.y;
			length = temp_vec2.x;
		} else // if (
			//_gen_side == GEN_SIDE_T || _gen_side == GEN_SIDE_B
		//)
		{
			//thickness = engine->layout_rand<i32>
			//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
			thickness = temp_vec2.x;
			length = temp_vec2.y;
		}
	}
	//--------
	const i32
		conn_rp_lx = conn_rp.rect.left_x(),
		conn_rp_ty = conn_rp.rect.top_y(),
		conn_rp_rx = conn_rp.rect.right_x(),
		conn_rp_by = conn_rp.rect.bottom_y();

	switch (_gen_side) {
	//--------
	case GEN_SIDE_L:
		to_push_rp.rect.pos = IntVec2
			{.x=conn_rp_lx,
			.y=engine->layout_rand<i32>(conn_rp_ty, conn_rp_by)}
				- IntVec2{length, 0};
		to_push_rp.rect.size_2d = {.x=length, .y=thickness};
		break;
	case GEN_SIDE_T:
		to_push_rp.rect.pos = IntVec2
			{.x=engine->layout_rand<i32>(conn_rp_lx, conn_rp_rx),
			.y=conn_rp_ty} - IntVec2{0, length};
		to_push_rp.rect.size_2d = {.x=thickness, .y=length};
		break;
	case GEN_SIDE_R:
		to_push_rp.rect.pos = IntVec2
			{.x=conn_rp_rx,
			.y=engine->layout_rand<i32>(conn_rp_ty, conn_rp_by)}
				+ IntVec2{1, 0};
		to_push_rp.rect.size_2d = {.x=length, .y=thickness};
		break;
	case GEN_SIDE_B:
		to_push_rp.rect.pos = IntVec2
			{.x=engine->layout_rand<i32>(conn_rp_lx, conn_rp_rx),
			.y=conn_rp_by} + IntVec2{0, 1};
		to_push_rp.rect.size_2d = {.x=thickness, .y=length};
		break;
	default:
		throw std::runtime_error(sconcat
			("game_engine::sys::GmDungeonGen::gen_single_rp(): ",
			"(1st) `switch (_gen_side)`: Eek! `", _gen_side,
			"`"));
		break;
	//--------
	}
	return to_push_rp;
}
void GmDungeonGen::GenInnards::_do_push_back(RoomPath&& to_push_rp) const {
	#ifdef DEBUG
	engine->log("Debug: Generated this `RoomPath`: ",
		//to_push_rp.rect, "; ",
		"to_push_rp.tl:", to_push_rp.rect.tl_corner(), " ",
		"to_push_rp.br:", to_push_rp.rect.br_corner(), "; ",
		to_push_rp.is_horiz_path(), " ",
		to_push_rp.is_vert_path(), " ",
		to_push_rp.is_room(),
		"\n");
	#endif		// DEBUG

	_dungeon_gen->push_back(std::move(to_push_rp));
	//to_push_rp = RoomPath();
}
//--------
auto GmDungeonGen::GenInnards::any_intersect_find_all(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::vector<size_t> {
	return _find_all_backend(to_check_rp, index,
		[](const RoomPath& to_check_rp, const RoomPath& some_item)
		-> bool {
			return some_item.rect.intersect(to_check_rp.rect);
		});
}
auto GmDungeonGen::GenInnards::any_intersect_find_first(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::optional<size_t> {
	//for (size_t k=0; k<_dungeon_gen->size(); ++k) {
	//	auto& some_item = _dungeon_gen->at(k);
	//	if (index && (*index == k)) {
	//		continue;
	//	} else if (some_item.rect.intersect(to_check_rp.rect)) {
	//		return &some_item;
	//	}
	//}
	//return nullptr;

	return _find_first_backend(to_check_rp, index,
		[](const RoomPath& to_check_rp, const RoomPath& some_item)
		-> bool {
			return some_item.rect.intersect(to_check_rp.rect);
		});
}
//--------
auto GmDungeonGen::GenInnards::any_sides_intersect_find_all(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::vector<size_t> {
	return _find_all_backend(to_check_rp, index,
		[](const RoomPath& to_check_rp, const RoomPath& some_item)
		-> bool {
			return _some_sides_hit(to_check_rp, some_item);
		});
}
auto GmDungeonGen::GenInnards::any_sides_intersect_find_first(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::optional<size_t> {
	//for (size_t k=0; k<_dungeon_gen->size(); ++k) {
	//	auto& some_item = _dungeon_gen->at(k);
	//	if (index && (*index == k)) {
	//		continue;
	//	} else if (_some_sides_hit(to_check_rp, some_item)) {
	//		return &some_item;
	//	}
	//}
	//return nullptr;
	return _find_first_backend(to_check_rp, index,
		[](const RoomPath& to_check_rp, const RoomPath& some_item)
		-> bool {
			return _some_sides_hit(to_check_rp, some_item);
		});
}
//--------
auto GmDungeonGen::GenInnards::any_path_sides_hit_wrongly_find_all(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::vector<size_t> {
	return _find_all_backend(to_check_rp, index,
		[](const RoomPath& to_check_rp, const RoomPath& some_item)
		-> bool {
			return _path_sides_hit_wrongly(to_check_rp, some_item);
		});
}
auto GmDungeonGen::GenInnards::any_path_sides_hit_wrongly_find_first(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::optional<size_t> {
	//for (size_t k=0; k<_dungeon_gen->size(); ++k) {
	//	auto& some_item = _dungeon_gen->at(k);
	//	if (index && (*index == k)) {
	//		continue;
	//	} else if (_path_sides_hit_wrongly(to_check_rp, some_item)) {
	//		//engine->log("any_path_sides_hit_wrongly_find_first(): ",
	//		//	"wrong hit found: ",
	//		//	"to_check_rp{", to_check_rp.rect.tl_corner(), " ",
	//		//		to_check_rp.rect.br_corner(), "} ",
	//		//	"_dungeon_gen->at(", k, ")",
	//		//		"{", some_item.rect.tl_corner(), " ",
	//		//			some_item.rect.br_corner(), "}",
	//		//		"\n");
	//		//return true;
	//		return &some_item;
	//	}
	//}
	//return nullptr;
	return _find_first_backend(to_check_rp, index,
		[](const RoomPath& to_check_rp, const RoomPath& some_item)
		-> bool {
			return _path_sides_hit_wrongly(to_check_rp, some_item);
		});
}
//--------
auto GmDungeonGen::GenInnards::_find_all_backend(
	RoomPath& to_check_rp,
	const std::optional<size_t>& index,
	const std::function<bool(
		RoomPath&, const RoomPath&
	)>& test_func
) -> std::vector<size_t> {
	std::vector<size_t> ret;

	//const auto& raw_some_item_set
	//	= _dungeon_gen->cg_find_others(to_check_rp);
	for (size_t k=0; k<_dungeon_gen->size(); ++k)
	//for (auto* raw_some_item: raw_some_item_set)
	{
		//const auto& some_item = _dungeon_gen->at(k);
		//RoomPath* some_item = static_cast<RoomPath*>(raw_some_item);
		//const size_t k = _dungeon_gen->rp_to_index_map().at(some_item);
		RoomPath* some_item = &_dungeon_gen->_raw_at(k);
		if (index && (*index == k)) {
			continue;
		} else if (test_func(to_check_rp, *some_item)) {
			ret.push_back(k);
		}
	}
	return ret;
}
auto GmDungeonGen::GenInnards::_find_first_backend(
	RoomPath& to_check_rp,
	const std::optional<size_t>& index,
	const std::function<bool(
		RoomPath&, const RoomPath&
	)>& test_func
) -> std::optional<size_t> {
	//--------
	//_dungeon_gen->_coll_grid.clear();
	//for (size_t k=0; k<_dungeon_gen->size(); ++k) {
	//	_dungeon_gen->_coll_grid.insert(&_dungeon_gen->_raw_at(k));
	//}
	//--------
	//const auto& raw_some_item_uset
	//	= _dungeon_gen->cg_find_others(to_check_rp);
	//const auto& raw_some_item_uset
	//	= _dungeon_gen->_coll_grid.find_others(&to_check_rp);
	for (size_t k=0; k<_dungeon_gen->size(); ++k) 
	//for (auto* raw_some_item: raw_some_item_uset)
	{
		//const auto& some_item = _dungeon_gen->at(k);
		RoomPath* some_item = &_dungeon_gen->_raw_at(k);
		//RoomPath* some_item = static_cast<RoomPath*>(raw_some_item);
		//const size_t k = _dungeon_gen->rp_to_index_umap().at(some_item);
		if (index && (*index == k)) {
			continue;
		} else if (test_func(to_check_rp, *some_item)) {
			return k;
		}
	}
	return std::nullopt;
	//--------
}
void GmDungeonGen::GenInnards::finalize_basic(
	//bool do_clear
) const {
	//if (do_clear) {
	//	//for (i=0; i<_dungeon_gen->size(); ++i)
	//	for (auto& some_rp: *_dungeon_gen) {
	//		//auto& some_rp = _dungeon_gen->at(i);
	//		//_dungeon_gen->at(i).door_pt_uset.clear();
	//		some_rp.conn_index_uset.clear();
	//		some_rp.door_pt_uset.clear();
	//	}
	//}
	for (
		size_t rp_index=0;
		rp_index<_dungeon_gen->size();
		++rp_index
	) {
		//if (item_index == rp_index) {
		//	continue;
		//}
		auto
			& rp = _dungeon_gen->_raw_at(rp_index);
			//& item = _dungeon_gen->_raw_at(item_index);
		//auto& rp_xdata = _dungeon_gen->xdata_at(rp_index);
		//--------
		const auto& raw_item_uset = _dungeon_gen->cg_neighbors(rp_index);
		for (auto* raw_item: raw_item_uset) {
			RoomPath* item = static_cast<RoomPath*>(raw_item);
			//auto& item_xdata = item->xdata;
			const size_t item_index
				= _dungeon_gen->rp_to_index_umap().at(item);
			//--------
			// set `conn_index_uset`
			// We only need to check intersection with one of the two
			// `RoomPath`'s sides
			if (_ls_r2_hit(rp, *item) || _ts_r2_hit(rp, *item)
				|| _rs_r2_hit(rp, *item) || _bs_r2_hit(rp, *item)) {
				rp.conn_index_uset.insert(item_index);
				item->conn_index_uset.insert(rp_index);
			}
			//--------
			// insert doors
			if (rp.is_room() && item->is_path()) {
				if (item->is_horiz_path()) {
					if (_ls_r2_hit(*item, rp)) {
						item->door_pt_uset.insert(item->rect.tl_corner());
					}
					if (_rs_r2_hit(*item, rp)) {
						item->door_pt_uset.insert(item->rect.tr_corner());
					}
				} else { // if (item->is_vert_path())
					if (_ts_r2_hit(*item, rp)) {
						item->door_pt_uset.insert(item->rect.tl_corner());
					}
					if (_bs_r2_hit(*item, rp)) {
						item->door_pt_uset.insert(item->rect.bl_corner());
					}
				}
			} else if (rp.is_path() && item->is_room()) {
				if (rp.is_horiz_path()) {
					if (_ls_r2_hit(rp, *item)) {
						rp.door_pt_uset.insert(rp.rect.tl_corner());
					}
					if (_rs_r2_hit(rp, *item)) {
						rp.door_pt_uset.insert(rp.rect.tr_corner());
					}
				} else { // if (rp.is_vert_path())
					if (_ts_r2_hit(rp, *item)) {
						rp.door_pt_uset.insert(rp.rect.tl_corner());
					}
					if (_bs_r2_hit(rp, *item)) {
						rp.door_pt_uset.insert(rp.rect.bl_corner());
					}
				}
			}
		}
	}
	//for (size_t i=0; i<_dungeon_gen->size(); ++i) {
	//	const auto& some_rp = _dungeon_gen->at(i);
	//	if (some_rp.door_pt_uset.size() > 0) {
	//		engine->log("door pts ", i, " [");
	//		for (const auto& door_pt: some_rp.door_pt_uset) {
	//			engine->log(door_pt, " ");
	//		}
	//		engine->log("]\n");
	//	}
	//}
}
bool GmDungeonGen::GenInnards::_shrink(
	bool was_horiz_path, bool was_vert_path,
	RoomPath& some_rp, //const std::optional<size_t>& index,
	const std::function<bool(
		RoomPath&//, const std::optional<size_t>&
	)>& extra_test_func
) {
	//--------
	auto move_left_x = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rp.rect.tl_corner() + IntVec2{1, 0},
			some_rp.rect.br_corner(),
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rp.rect = temp_rect;
	};
	auto move_top_y = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rp.rect.tl_corner() + IntVec2{0, 1},
			some_rp.rect.br_corner(),
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rp.rect = temp_rect;
	};
	auto move_right_x = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rp.rect.tl_corner(),
			some_rp.rect.br_corner() - IntVec2{1, 0},
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rp.rect = temp_rect;
	};
	auto move_bottom_y = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rp.rect.tl_corner(),
			some_rp.rect.br_corner() - IntVec2{0, 1},
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rp.rect = temp_rect;
	};
	//--------
	//const bool
	//	was_horiz_path = some_rp.is_horiz_path(),
	//	was_vert_path = some_rp.is_vert_path();
	//	//was_room = some_rp.is_room();
	if (was_horiz_path) {
		const i32
			SHRINK_NUM_ATTEMPTS = engine->layout_rand<i32>
				(MIN_GEN_SHRINK_NUM_ATTEMPTS_PATH,
				MAX_GEN_SHRINK_NUM_ATTEMPTS_PATH);
		for (i32 i=0; i<SHRINK_NUM_ATTEMPTS; ++i) {
			//--------
			if (engine->layout_rand<i32>(0, 1)) {
				move_left_x();
			} else {
				move_right_x();
			}
			//--------
			if (
				some_rp.is_horiz_path()
				&& extra_test_func(
					some_rp//, index
				)
			) {
				return true;
			} else if (!some_rp.is_horiz_path()) {
				return false;
			}
			//--------
		}
	} else if (was_vert_path) {
		const i32
			SHRINK_NUM_ATTEMPTS = engine->layout_rand<i32>
				(MIN_GEN_SHRINK_NUM_ATTEMPTS_PATH,
				MAX_GEN_SHRINK_NUM_ATTEMPTS_PATH);
		for (i32 i=0; i<SHRINK_NUM_ATTEMPTS; ++i) {
			//--------
			if (engine->layout_rand<i32>(0, 1)) {
				move_top_y();
			} else {
				move_bottom_y();
			}
			//--------
			if (
				some_rp.is_vert_path()
				&& extra_test_func(
					some_rp//, index
				)
			) {
				return true;
			} else if (!some_rp.is_vert_path()) {
				return false;
			}
			//--------
		}
	} else { // if (was_room)
		const i32
			SHRINK_NUM_ATTEMPTS = engine->layout_rand<i32>
				(MIN_GEN_SHRINK_NUM_ATTEMPTS_ROOM,
				MAX_GEN_SHRINK_NUM_ATTEMPTS_ROOM);
		for (i32 i=0; i<SHRINK_NUM_ATTEMPTS; ++i) {
			//--------
			const i32
				shrink_side = engine->layout_rand<i32>
					(MIN_GEN_SIDE, MAX_GEN_SIDE);
			switch (shrink_side) {
			//--------
			case GEN_SIDE_L:
				move_left_x();
				break;
			case GEN_SIDE_T:
				move_top_y();
				break;
			case GEN_SIDE_R:
				move_right_x();
				break;
			case GEN_SIDE_B:
				move_bottom_y();
				break;
			default:
				throw std::runtime_error(sconcat
					("game_engine::sys::GmDungeonGen::GenInnards",
					"::_shrink(): Eek! ",
					"shrink_side{", shrink_side, "}"));
				break;
			//--------
			}
			//--------
			if (
				some_rp.is_room()
				&& extra_test_func(
					some_rp//, index
				)
			) {
				return true;
			} else if (!some_rp.is_room()) {
				return false;
			}
			//--------
		}
	}
	return false;
	//return final_func();
};
//--------
void GmDungeonGen::GenInnards::insert_alt_terrain(
	bool do_clear
) const {
	const auto
		& allowed_alt_terrain_vec = LEVEL_ALLOWED_ALT_TERRAIN_V2D
			.at(engine->level_minus_1());

	//for (auto& item: *_dungeon_gen)
	//for (
	//	size_t item_index=0;
	//	item_index<_dungeon_gen->size();
	//	++item_index
	//) {
	//	auto& item = _dungeon_gen->at(item_index);
	//	if (do_clear) {
	//		item.alt_terrain_umap.clear();
	//	}

	//	//if (item.is_path()) {
	//	//	continue;
	//	//}

	//	// Note that `RoomPath`s are already generated with their borders
	//	IntVec2
	//		pos;
	//	for (
	//		pos.y=item.rect.top_y() - i32(1);
	//		pos.y<=item.rect.bottom_y() + i32(1);
	//		++pos.y
	//	) {
	//		for (
	//			pos.x=item.rect.left_x() - i32(1);
	//			pos.x<=item.rect.right_x() + i32(1);
	//			++pos.x
	//		) {
	//			//const auto
	//			//	bg_tile_index = engine->layout_noise<i32>
	//			//		(0, allowed_alt_terrain_vec.size() - 1, pos,
	//			//		_dungeon_gen->layout_noise_add_amount());

	//			const auto
	//				bg_tile_index =
	//			const BgTile
	//				bg_tile = allowed_alt_terrain_vec.at(bg_tile_index);
	//			if (bg_tile == ALT_TERRAIN_NONE) {
	//				continue;
	//			}

	//			if (item.is_path()) {
	//				if (!bg_tile_is_unsafe(bg_tile)) {
	//					item.alt_terrain_umap[pos] = bg_tile;
	//				}
	//			} else { // if (item.is_room())
	//				//RoomPath* some_path_rp = nullptr;
	//				//for (const auto& conn_index: item.conn_index_uset) {
	//				//	// It's guaranteed at this point that there's
	//				//	// either one or zero paths at `pos`, so we can
	//				//	// stop the search at the first check
	//				//	RoomPath& conn_rp = _dungeon_gen->at(conn_index);
	//				//	if (conn_rp.is_path()) {
	//				//		some_path_rp = &conn_rp;
	//				//		break;
	//				//	}
	//				//}
	//				if (
	//					! bg_tile_is_unsafe(bg_tile)
	//					|| (!item.pos_in_border(pos)
	//						&& !item.pos_in_internal_border(pos))
	//				) {
	//					item.alt_terrain_umap[pos] = bg_tile;
	//				}
	//			}

	//		}
	//	}
	//}
}
//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
