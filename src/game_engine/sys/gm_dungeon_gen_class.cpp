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

void GmDungeonGen::clear_dungeon_gen(ecs::Engine* ecs_engine) {
	auto* dungeon_gen
		= ecs_engine->casted_comp_at<comp::DungeonGen>(*_dungeon_gen_id);
	dungeon_gen->clear();
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
				ecs::CompSptr(new comp::DungeonGen())
			),
			func_name
		);

		printout("game_engine::sys::GmDungeonGen::_init(): ",
			*_dungeon_gen_id, "\n");
	}
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
			= ecs_engine->casted_comp_at<comp::DungeonGen>(
				*_dungeon_gen_id
			);

		if (engine->key_status.key_just_went_down(KeyKind::DownR)) {
			//if (dungeon_gen->size() == 0) {
			//	printout("Debug: starting dungeon generation.\n");
			//}
			GenInnards innards(this, dungeon_gen);
			innards.gen_single_rp();
			innards.finalize(true);
			//else {
			//	printout("Debug: We're already done generating\n");
			//}
		}

		//dungeon_gen->draw(bg_tile_map);
		//bg_tile_map->draw();
		dungeon_gen->draw();
		engine->screen_window.clear();

		engine->screen_window.draw(engine->pfield_window);
		engine->screen_window.draw(engine->log_window);
		engine->screen_window.draw(engine->hud_window);
	}
}

//void GmDungeonGen::_connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
//	comp::DungeonGen* dungeon_gen) {
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
			//printout("testificate 2\n");
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

		//auto dbg_sconcat
		//	= [](const std::string& name, i32 some_min, i32 some_max)
		//-> std::string {
		//	return sconcat("`", name, "`: ",
		//		strjoin2(" ",
		//			some_min, some_max, some_max - some_min + i32(1)
		//		),
		//		"\n"
		//	);
		//};
		//printout("GmDungeonGen::_gen_single_rp(): Debug: \n",
		//	dbg_sconcat("GEN_TYPE", MIN_GEN_TYPE, MAX_GEN_TYPE), "\n",
		//	dbg_sconcat("GEN_SIDE", MIN_GEN_SIDE, MAX_GEN_SIDE), "\n",
		//	dbg_sconcat("GEN_NEXT", MIN_GEN_NEXT, MAX_GEN_NEXT), "\n"
		//);
	}
	//else if (_dungeon_gen->size() < MAX_NUM_ROOM_PATHS)
	else if (i32(_dungeon_gen->size()) < _self->_attempted_num_rp) {
		RoomPath to_push_rp;
		if (_dungeon_gen->size() < MIN_NUM_ROOM_PATHS) {
			for (;;) {
				if (auto opt_rp=_inner_gen_post_first(); opt_rp) {
					//printout("`gen_single_rp()` initial gen: ",
					//	any_intersect(*opt_rp, std::nullopt), ": ",
					//	"{", opt_rp->rect.tl_corner(), " ",
					//	opt_rp->rect.br_corner(), "}",
					//	"\n");
					_do_push_back(std::move(*opt_rp));
					break;
				}
			}
		} else if (!_self->_stop_gen_early) {
			i32 tries = 0;
			for (; tries<GEN_RP_LIM_TRIES; ++tries) {
				if (auto opt_rp=_inner_gen_post_first(); opt_rp) {
					//printout("`gen_single_rp()` !_self->_stop_gen_early: ",
					//	tries, ": ",
					//	any_intersect(*opt_rp, std::nullopt), ": ",
					//	"{", opt_rp->rect.tl_corner(), " ",
					//	opt_rp->rect.br_corner(), "}",
					//	"\n");
					_do_push_back(std::move(*opt_rp));
					break;
				}
			}
			// If we failed to find a room that fits in the playfield, we
			// stop floor generation early, and don't try any more for this
			// floor.  This is to prevent infinite loops in the dungeon
			// generation.
			_self->_stop_gen_early = tries >= GEN_RP_LIM_TRIES;
			if (_self->_stop_gen_early) {
				printout("stopping room generation early: ",
					_dungeon_gen->size(), " ", _self->_attempted_num_rp,
					"\n");
			}
			//else {
			//}
		}
	}
	_self->_done_generating
		= _self->_stop_gen_early
			|| i32(_dungeon_gen->size()) >= _self->_attempted_num_rp;

	return _self->_done_generating;
}
auto GmDungeonGen::GenInnards::_inner_gen_post_first() const
-> std::optional<RoomPath> {
	//--------
	RoomPath to_push_rp;
	//--------
	const i32
		prev_rp_index = _dungeon_gen->size() - 1;
	const RoomPath
		& prev_rp = _dungeon_gen->at(prev_rp_index);
	const i32 
		prev_gen_type
			= prev_rp.is_path() ? GEN_TYPE_PATH : GEN_TYPE_ROOM;
	i32
		gen_side = 0,
		gen_next_type = 0,
		gen_next_conn_rp_index = 0,
		gen_type = 0,
		conn_rp_index = 0;

	//gen_type = GEN_TYPE_ROOM,
	//gen_side = engine->layout_rand<i32>
	//	(MIN_GEN_SIDE, MAX_GEN_SIDE),

	gen_next_type = (prev_gen_type == GEN_TYPE_PATH)
		? engine->layout_rand<i32>
			(MIN_GEN_NEXT_PATH_TYPE, MAX_GEN_NEXT_PATH_TYPE)
		: engine->layout_rand<i32>
			(MIN_GEN_NEXT_ROOM_TYPE, MAX_GEN_NEXT_ROOM_TYPE),
	gen_next_conn_rp_index = (prev_gen_type == GEN_TYPE_PATH)
		? engine->layout_rand<i32>
			(MIN_GEN_NEXT_PATH_INDEX, MAX_GEN_NEXT_PATH_INDEX)
		: engine->layout_rand<i32>
			(MIN_GEN_NEXT_ROOM_INDEX, MAX_GEN_NEXT_ROOM_INDEX);

	gen_type = 0;
	if (
		(
			prev_gen_type == GEN_TYPE_PATH
			&& gen_next_type >= GEN_NEXT_PATH_SAME_TYPE_MIN
			&& gen_next_type <= GEN_NEXT_PATH_SAME_TYPE_MAX
		) || (
			prev_gen_type == GEN_TYPE_ROOM
			&& gen_next_type >= GEN_NEXT_ROOM_SAME_TYPE_MIN
			&& gen_next_type <= GEN_NEXT_ROOM_SAME_TYPE_MAX
		)
	) {
		gen_type = prev_gen_type;
		//printout(
		//	"game_engine::sys::GmDungeonGen
		//	"::_gen_single_rp(): ",
		//	"using `prev_gen_type`: ",
		//	gen_type, "\n"
		//);
	} else { // if (switching types) 
		do {
			gen_type = engine->layout_rand<i32>
				(MIN_GEN_TYPE, MAX_GEN_TYPE);
		} while (gen_type == prev_gen_type);

		//printout(
		//	"game_engine::sys::GmDungeonGen::_gen_single_rp(): ",
		//	"randomizing `gen_type`, ",
		//	"but picking something different: ",
		//	"`gen_type`: ", gen_type, "; ",
		//	"`prev_gen_type`: ", prev_gen_type, "\n"
		//);
	}
	//--------
	// Which `RoomPath` are we connecting to?
	//printout("test 0\n");
	//i32 conn_rp_index;
	if (
		//gen_next_conn_rp_index >= GEN_NEXT_SAME_MIN
		//&& gen_next_conn_rp_index <= GEN_NEXT_SAME_MAX
		(
			prev_gen_type == GEN_TYPE_PATH
			&& gen_next_conn_rp_index
				>= GEN_NEXT_PATH_SAME_INDEX_MIN
			&& gen_next_conn_rp_index
				<= GEN_NEXT_PATH_SAME_INDEX_MAX
		) || (
			prev_gen_type == GEN_TYPE_ROOM
			&& gen_next_conn_rp_index
				>= GEN_NEXT_ROOM_SAME_INDEX_MIN
			&& gen_next_conn_rp_index
				<= GEN_NEXT_ROOM_SAME_INDEX_MAX
		)
	) {
		conn_rp_index = prev_rp_index;
	} else //if (
		//gen_next_conn_rp_index >= GEN_NEXT_DIFFERENT_MIN
		//&& gen_next_conn_rp_index <= GEN_NEXT_DIFFERENT_MAX
	//)
	{
		if (prev_rp_index == 0) {
			conn_rp_index = prev_rp_index;
		} else { // if (prev_rp_index > 0)
			// Force a different room from the last one to be
			// picked in this case
			conn_rp_index
				= engine->layout_rand<i32>
					(0, prev_rp_index - 1);
		}
	}

	//const i32 conn_rp_index = engine->layout_rand<i32>(0, 0);
	//printout("test 1\n");
	const auto& conn_rp = _dungeon_gen->at(conn_rp_index);

	if (
		//(conn_rp.is_path() && gen_type == GEN_TYPE_PATH)
		//|| (conn_rp.is_room() && gen_type == GEN_TYPE_ROOM)
		(conn_rp.is_path() && gen_type == GEN_TYPE_PATH)
		|| conn_rp.is_room()
	) {
		gen_side = engine->layout_rand<i32>
			(MIN_GEN_SIDE, MAX_GEN_SIDE);
	} else {
		if (conn_rp.is_horiz_path()) {
			gen_side
				= engine->layout_rand<i32>(0, 1)
				? GEN_SIDE_L
				: GEN_SIDE_R;
		} else { // if (conn_rp.is_vert_path())
			gen_side
				= engine->layout_rand<i32>(0, 1)
				? GEN_SIDE_T
				: GEN_SIDE_B;
		}
		//else if (conn_rp.is_room()) {
		//	gen_side = engine->layout_rand<i32>
		//		(MIN_GEN_SIDE, MAX_GEN_SIDE);
		//}
	}
	//if (inner_gen_tries > GEN_RP_LIM_TRIES) {
	//	printout("debug: failed dungeon generation ",
	//		"(inner_gen_tries too large): ",
	//		"\n");
	//	return std::nullopt;
	//}
	//--------
	i32
		thickness = 0,
		length = 0;
	//IntVec2
	//	temp_size_2d;

	if (gen_type == GEN_TYPE_PATH) {
		thickness
			//temp_size_2d.x
			= PATH_THICKNESS,
		length
			//temp_size_2d.y
			= engine->layout_rand<i32>
				(PATH_MIN_LEN, PATH_MAX_LEN);
	} else { // if (gen_type == GEN_TYPE_ROOM)
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

		if (
			gen_side == GEN_SIDE_L
			|| gen_side == GEN_SIDE_R
		) {
			thickness = temp_vec2.y;
			length = temp_vec2.x;
		} else // if (
			//gen_side == GEN_SIDE_T || gen_side == GEN_SIDE_B
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

	switch (gen_side) {
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
			("game_engine::sys::GmDungeonGen::_gen_single_rp(): ",
			"(1st) `switch (gen_side)`: Eek! `", gen_side,
			"`"));
		break;
	//--------
	}
	//--------
	// This is a simple algorithm that could be made faster and
	// more complicated, but I figure any platform running this
	// game will have fast enough hardware considering the maximum
	// numbers of rooms/paths.
	if (!to_push_rp.fits_in_pfield_nb()) {
		return std::nullopt;
	}
	//printout("to_push_rp.fits_in_pfield_nb(): ", to_push_rp.rect, "\n");


	//const IntVec2
	//	tl_amount
	//		{.x=gen_side == GEN_SIDE_L ? 0 : 1,
	//		.y=gen_side == GEN_SIDE_T ? 0 : 1},
	//	br_amount
	//		{.x=gen_side == GEN_SIDE_R ? 0 : 1,
	//		.y=gen_side == GEN_SIDE_B ? 0 : 1};
	//const IntRect2 inflated_rect
	//	= to_push_rp.rect.build_in_grid_inflated_lim
	//		(tl_amount, br_amount, PFIELD_PHYS_RECT2);


	//bool found_intersect = false;
	//auto any_intersect = [this](
	//	const RoomPath& to_check_rp,
	//	const std::optional<size_t>& index
	//) -> bool {
	//	for (size_t k=0; k<_dungeon_gen->size(); ++k) {
	//		const auto& some_item = _dungeon_gen->at(k);
	//		if (index && (*index == k)) {
	//			continue;
	//		} else if (some_item.rect.intersect
	//			(to_check_rp.rect)
	//		) {
	//			return true;
	//		}
	//	}
	//	return false;
	//};
	//any_intersect();

	if (any_intersect(to_push_rp, std::nullopt)) {
		//printout("Debug: found early intersect!\n");
		return std::nullopt;
	}

	if (any_path_sides_hit_wrongly(to_push_rp, std::nullopt)) {
		return std::nullopt;
	}
	for (
		size_t item_index=0;
		item_index<_dungeon_gen->size();
		++item_index
	) {
	//for (const auto& item: *_dungeon_gen)
		auto& item = _dungeon_gen->at(item_index);
		//if (
		//	//(
		//	//	to_push_rp.is_horiz_path()
		//	//	&& (_ts_r2_hit(to_push_rp, item)
		//	//		|| _bs_r2_hit(to_push_rp, item))
		//	//) || (
		//	//	to_push_rp.is_vert_path()
		//	//	&& (_ls_r2_hit(to_push_rp, item)
		//	//		|| _rs_r2_hit(to_push_rp, item))
		//	//) || (
		//	//	item.is_horiz_path()
		//	//	&& (_ts_r2_hit(item, to_push_rp)
		//	//		|| _bs_r2_hit(item, to_push_rp))
		//	//) || (
		//	//	item.is_vert_path()
		//	//	&& (_ls_r2_hit(item, to_push_rp)
		//	//		|| _rs_r2_hit(item, to_push_rp))
		//	//)
		//	////|| (i32(i) != conn_rp_index
		//	////	&&
		//	////	item.rect.intersect(to_push_rp.rect))
		//	_path_sides_hit_wrongly(to_push_rp, item)
		//) {
		//	//printout("debug: failed generation\n");
		//	return std::nullopt;
		//}

		auto should_gen_connect = []() -> bool {
			const i32
				temp = engine->layout_rand<i32>
					(MIN_GEN_CONNECT, MAX_GEN_CONNECT);
			return (temp >= GEN_CONNECT_YES_MIN
				&& temp <= GEN_CONNECT_YES_MAX);
		};
		auto dbg_print_before = [this, &to_push_rp, &item]() -> void {
			printout("before:\n",
				"to_push_rp.tl:", to_push_rp.rect.tl_corner(), " ",
				"to_push_rp.br:", to_push_rp.rect.br_corner(), "\n",
				"item.tl:", item.rect.tl_corner(), " "
				"item.br:", item.rect.br_corner(), "\n");
		};
		auto dbg_print_after = [this, &to_push_rp, &item]() -> void {
			printout("after:\n",
				"to_push_rp.tl:", to_push_rp.rect.tl_corner(), " ",
				"to_push_rp.br:", to_push_rp.rect.br_corner(), "\n",
				"item.tl:", item.rect.tl_corner(), " "
				"item.br:", item.rect.br_corner(), "\n");
		};

		using TempRpPair
			= std::pair<std::optional<RoomPath>,
				std::optional<RoomPath>>;

		std::vector<TempRpPair> temp_rp_pair_vec
			(MAX_GEN_SIDE - MIN_GEN_SIDE + 1,
			TempRpPair(std::nullopt, std::nullopt));
		auto gen_temp_rp_pair_vec_elem = [&](
			bool sides_did_hit, i32 some_side,
			const std::pair<IntVec2, IntVec2>& rp_offset_pair,
			const std::pair<IntVec2, IntVec2>& item_offset_pair,
			const std::string& dbg_str, bool do_dbg_print
		) -> void {
			//auto possible_to_extend_that_way = []
			if (
				//_ls_and_rs_hit(to_push_rp, item)
				sides_did_hit
				&& should_gen_connect()
			) {
				RoomPath temp_rp;
				if (!engine->layout_rand<i32>(0, 1)) {
					if (do_dbg_print) {
						printout(dbg_str, " 0\n");
						dbg_print_before();
					}
					temp_rp.rect
						= to_push_rp.rect.build_in_grid_inflated_lim
						(rp_offset_pair.first,
						rp_offset_pair.second,
						PFIELD_PHYS_NO_BORDER_RECT2);
					temp_rp_pair_vec.at(some_side).first
						= std::move(temp_rp);
					if (do_dbg_print) {
						dbg_print_after();
					}
				} else {
					if (do_dbg_print) {
						printout(dbg_str, " 1\n");
						dbg_print_before();
					}
					temp_rp.rect
						= item.rect.build_in_grid_inflated_lim
						(item_offset_pair.first,
						item_offset_pair.second,
						PFIELD_PHYS_NO_BORDER_RECT2);
					temp_rp_pair_vec.at(some_side).second
						= std::move(temp_rp);
					if (do_dbg_print) {
						dbg_print_after();
					}
				}
			}
		};
		gen_temp_rp_pair_vec_elem
			(_ls_and_rs_hit(to_push_rp, item), GEN_SIDE_L,
			std::pair(IntVec2{1, 0}, IntVec2()),
			std::pair(IntVec2(), IntVec2{1, 0}),
			"ls", false);
		gen_temp_rp_pair_vec_elem
			(_ts_and_bs_hit(to_push_rp, item), GEN_SIDE_T,
			std::pair(IntVec2{0, 1}, IntVec2()),
			std::pair(IntVec2(), IntVec2{0, 1}),
			"ts", false);
		gen_temp_rp_pair_vec_elem
			(_ls_and_rs_hit(item, to_push_rp), GEN_SIDE_R,
			std::pair(IntVec2(), IntVec2{1, 0}),
			std::pair(IntVec2{1, 0}, IntVec2()),
			"rs", false);
		//if (_ts_and_bs_hit(item, to_push_rp)) {
		//	printout("to_push_rp.bs intersects item.ts:\n",
		//		"\t_rp{", to_push_rp.rect.tl_corner(), " ",
		//			to_push_rp.rect.br_corner(), "} ",
		//		"item{", item.rect.tl_corner(), " ",
		//			item.rect.br_corner(), "}\n",
		//		"\t_rp_bs{", _rp_bs_r2().tl_corner(), " ",
		//			_rp_bs_r2().br_corner(), "} ",
		//		"item_ts{", _ts_r2(item).tl_corner(), " ",
		//			_ts_r2(item).br_corner(), "}",
		//		"\n");
		//}
		gen_temp_rp_pair_vec_elem
			(_ts_and_bs_hit(item, to_push_rp), GEN_SIDE_B,
			std::pair(IntVec2(), IntVec2{0, 1}),
			std::pair(IntVec2{0, 1}, IntVec2()),
			"bs", false);
		if (
			const i32 check_first_extend_side=engine->layout_rand<i32>
				(MIN_GEN_SIDE, MAX_GEN_SIDE);
			true
		) {
			i32
				i
					//= MIN_GEN_SIDE;
					= std::abs(MAX_GEN_SIDE - MIN_GEN_SIDE),
				extend_side = check_first_extend_side;

			auto end_loop = [&i, &extend_side]() -> void {
				//++i;
				--i;
				++extend_side;
				if (extend_side > MAX_GEN_SIDE) {
					extend_side = MIN_GEN_SIDE;
				}
			};
			//while (i <= MAX_GEN_SIDE)
			while (i >= 0) {
				auto& temp_rp_pair
					= temp_rp_pair_vec.at(extend_side);
				RoomPath
					* temp_rp = nullptr, * to_edit_rp = nullptr;
				std::string dbg_str = "";

				if (temp_rp_pair.first) {
					temp_rp = &(*temp_rp_pair.first);

					if (any_intersect(*temp_rp, std::nullopt)) {
						printout("first testificate 0 \n");
						//return std::nullopt;
						//end_loop();
						//continue;
					} else {
						printout("first testificate 1\n");
						dbg_str = "to_push_rp";
						to_edit_rp = &to_push_rp;
					}
				} else if (temp_rp_pair.second) {
					temp_rp = &(*temp_rp_pair.second);

					if (any_intersect(*temp_rp, item_index)) {
						printout("second testificate 0\n");
						//return std::nullopt;
						//end_loop();
						//continue;
					} else {
						printout("second testificate 1\n");
						dbg_str = "item";
						to_edit_rp = &item;
					}
				}
				//else {
				//	printout("testificate\n");
				//}
				if (temp_rp && to_edit_rp
					&& !(
						(to_edit_rp->is_horiz_path()
						&& !temp_rp->is_horiz_path())
						|| (to_edit_rp->is_vert_path()
							&& !temp_rp->is_vert_path())
					) //&& !_path_sides_hit_wrongly(*temp_rp, *to_edit_rp)
					&& !any_path_sides_hit_wrongly(*temp_rp,
						((dbg_str == "item")
							? std::optional<size_t>(item_index)
							: std::nullopt))
				) {
					printout("Debug: doing extension: ",
						dbg_str,
						"{", to_edit_rp->rect.tl_corner(), " ",
							to_edit_rp->rect.br_corner(), "} ",
						"temp_rp",
						"{", temp_rp->rect.tl_corner(), " ",
							temp_rp->rect.br_corner(), "}",
						"\n");
					to_edit_rp->rect = temp_rp->rect;
				}
				end_loop();
			}
			//if (i > MAX_GEN_SIDE) {
			//	printout("testificate\n");
			//	return std::nullopt;
			//}
		}

		//maybe_extend_l();
		//maybe_extend_t();
		//maybe_extend_r();
		//maybe_extend_b();
	}
	//--------
	//to_push_rp.conn_index_set.insert(conn_rp_index);
	//conn_rp.conn_index_set.insert(_dungeon_gen->size());
	//--------
	//--------
	//printout("`gen_type`: ", gen_type, "\n");

	return to_push_rp;
	//--------
};
void GmDungeonGen::GenInnards::_do_push_back(RoomPath&& to_push_rp) const {
	#ifdef DEBUG
	printout("Generated this `RoomPath`: ",
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
bool GmDungeonGen::GenInnards::any_intersect(
	const RoomPath& to_check_rp, const std::optional<size_t>& index
) const {
	for (size_t k=0; k<_dungeon_gen->size(); ++k) {
		const auto& some_item = _dungeon_gen->at(k);
		if (index && (*index == k)) {
			continue;
		} else if (some_item.rect.intersect(to_check_rp.rect)) {
			return true;
		}
	}
	return false;
}
bool GmDungeonGen::GenInnards::any_path_sides_hit_wrongly(
	const RoomPath& to_check_rp, const std::optional<size_t>& index
) const {
	for (size_t k=0; k<_dungeon_gen->size(); ++k) {
		const auto& some_item = _dungeon_gen->at(k);
		if (index && (*index == k)) {
		} else if (_path_sides_hit_wrongly(to_check_rp, some_item)) {
			return true;
		}
	}
	return false;
}
void GmDungeonGen::GenInnards::finalize(bool do_clear) const {
	if (do_clear) {
		//for (i=0; i<_dungeon_gen->size(); ++i)
		for (auto& some_rp: *_dungeon_gen) {
			//_dungeon_gen->at(i).door_pt_set.clear();
			some_rp.conn_index_set.clear();
			some_rp.door_pt_set.clear();
		}
	}
	for (
		size_t item_index=0;
		item_index<_dungeon_gen->size();
		++item_index
	) {
		for (
			size_t rp_index=0;
			rp_index<_dungeon_gen->size();
			++rp_index
		) {
			if (item_index == rp_index) {
				continue;
			}
			auto
				& rp = _dungeon_gen->at(rp_index),
				& item = _dungeon_gen->at(item_index);
			//--------
			if (!item.rect.intersect(rp.rect)) {
				//--------
				// set `conn_index_set`
				// We only need to check intersection with one of the two
				// `RoomPath`'s sides
				if (_ls_r2_hit(rp, item)
					|| _ts_r2_hit(rp, item)
					|| _rs_r2_hit(rp, item)
					|| _bs_r2_hit(rp, item)) {
					rp.conn_index_set.insert(item_index);
					item.conn_index_set.insert(rp_index);
				}
				//--------
				// insert doors
				if (rp.is_room() && item.is_path()) {
					if (item.is_horiz_path()) {
						if (_ls_r2_hit(item, rp)) {
							item.door_pt_set.insert
								(_ls_r2(rp).tl_corner()
									+ IntVec2{1, 0});
						}
						if (_rs_r2_hit(item, rp)) {
							item.door_pt_set.insert
								(_rs_r2(rp).tr_corner()
									- IntVec2{1, 0});
						}
					} else { // if (item.is_vert_path())
						if (_ts_r2_hit(item, rp)) {
							item.door_pt_set.insert
								(_ts_r2(rp).tl_corner()
									+ IntVec2{0, 1});
						}
						if (_bs_r2_hit(item, rp)) {
							item.door_pt_set.insert
								(_bs_r2(rp).bl_corner()
									- IntVec2{0, 1});
						}
					}
				} else if (rp.is_path() && item.is_room()) {
					if (rp.is_horiz_path()) {
						if (_ls_r2_hit(rp, item)) {
							rp.door_pt_set.insert
								(_ls_r2(item).tl_corner()
									+ IntVec2{1, 0});
						}
						if (_rs_r2_hit(rp, item)) {
							rp.door_pt_set.insert
								(_rs_r2(item).tr_corner()
									- IntVec2{1, 0});
						}
					} else { // if (rp.is_vert_path())
						if (_ts_r2_hit(rp, item)) {
							rp.door_pt_set.insert
								(_ts_r2(item).tl_corner()
									+ IntVec2{0, 1});
						}
						if (_bs_r2_hit(rp, item)) {
							rp.door_pt_set.insert
								(_bs_r2(item).bl_corner()
									- IntVec2{0, 1});
						}
					}
				}
			}
		}
	}
}
//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
