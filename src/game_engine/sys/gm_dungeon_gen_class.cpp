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
			_gen_single_rp(dungeon_gen);
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

void GmDungeonGen::_gen_single_rp(comp::DungeonGen* dungeon_gen) {
	//GenInfo gen_info;
	comp::DungeonGen::RoomPath rp;

	auto do_push_back = [&]() -> void {
		#ifdef DEBUG
		printout("Generated this `RoomPath`: ",
			rp.rect, "; ",
			rp.is_horiz_path(), " ", rp.is_vert_path(), " ", rp.is_room(),
			"\n");
		#endif		// DEBUG

		dungeon_gen->push_back(std::move(rp));
	};

	if (dungeon_gen->size() == 0) {
		_attempted_num_rp = engine->layout_rand<i32>
			(i32(MIN_NUM_ROOM_PATHS), i32(MAX_NUM_ROOM_PATHS));
		//_prev_gen_side = 0;
		_stop_gen_early = false;

		// We always generate a room in this case.
		//for (i32 tries=0; tries<GEN_RP_MAX_TRIES; ++tries)
		// Force there to be at least one room
		for (;;) {
			//--------
			//printout("testificate 2\n");
			//--------
			rp.rect.pos.x = engine->layout_rand<i32>
				(PFIELD_PHYS_RECT2.left_x(),
				PFIELD_PHYS_RECT2.right_x() - ROOM_MIN_SIZE_2D.x - 1);
			rp.rect.pos.y = engine->layout_rand<i32>
				(PFIELD_PHYS_RECT2.top_y(),
				PFIELD_PHYS_RECT2.bottom_y() - ROOM_MIN_SIZE_2D.y - 1);

			rp.rect.size_2d.x = engine->layout_rand<i32>
				(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
			rp.rect.size_2d.y = engine->layout_rand<i32>
				(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y);
			//--------
			if (rp.fits_in_pfield()) {
				break;
			}
			//--------
		}
		do_push_back();

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
	//else if (dungeon_gen->size() < MAX_NUM_ROOM_PATHS)
	else if (
		!_stop_gen_early
		&& i32(dungeon_gen->size()) < _attempted_num_rp
	) {
		auto inner_gen = [&]() -> bool {
			//--------
			const i32
				prev_rp_index = dungeon_gen->size() - 1;
			const comp::DungeonGen::RoomPath
				& prev_rp = dungeon_gen->at(prev_rp_index);
			const i32 
				prev_gen_type
					= prev_rp.is_path() ? GEN_TYPE_PATH : GEN_TYPE_ROOM;

			i32
				//gen_side,
				gen_next_type,
				gen_next_conn_rp_index,
				gen_type;

			//gen_type = GEN_TYPE_ROOM,
			//rp.gen_side = engine->layout_rand<i32>
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
					&& gen_next_type <= GEN_NEXT_PATH_SAME_TYPE_MIN
				) || (
					prev_gen_type == GEN_TYPE_ROOM
					&& gen_next_type >= GEN_NEXT_ROOM_SAME_TYPE_MIN
					&& gen_next_type <= GEN_NEXT_ROOM_SAME_TYPE_MIN
				)
			) {
				gen_type = prev_gen_type;
				//printout(
				//	"game_engine::sys::GmDungeonGen::_gen_single_rp(): ",
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
			i32 conn_rp_index;
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
			} else // if (gen_next_conn_rp_index >= GEN_NEXT_DIFFERENT_MIN
				//&& gen_next_conn_rp_index <= GEN_NEXT_DIFFERENT_MAX)
			{
				if (prev_rp_index == 0) {
					conn_rp_index = prev_rp_index;
				} else { // if (prev_rp_index > 0)
					// Force a different room from the last one to be
					// picked in this case
					conn_rp_index
						= engine->layout_rand<i32>(0, prev_rp_index - 1);
				}
			}

			//const i32 conn_rp_index = engine->layout_rand<i32>(0, 0);
			//printout("test 1\n");
			auto& conn_rp = dungeon_gen->at(conn_rp_index);

			if (
				(conn_rp.is_path() && gen_type == GEN_TYPE_PATH)
				|| (conn_rp.is_room() && gen_type == GEN_TYPE_ROOM)
			) {
				do {
					rp.gen_side = engine->layout_rand<i32>
						(MIN_GEN_SIDE, MAX_GEN_SIDE);
				} while (rp.gen_side == conn_rp.gen_side);
			} else { 
				if (
					conn_rp.gen_side == GEN_SIDE_L
					|| conn_rp.gen_side == GEN_SIDE_R
				) {
					rp.gen_side
						= engine->layout_rand<i32>(0, 1)
						? GEN_SIDE_L
						: GEN_SIDE_R;
				} else {
					rp.gen_side
						= engine->layout_rand<i32>(0, 1)
						? GEN_SIDE_T
						: GEN_SIDE_B;
				}
			}
			//--------
			i32
				thickness = 0,
				length = 0;

			if (gen_type == GEN_TYPE_PATH) {
				thickness = PATH_THICKNESS;
				length = engine->layout_rand<i32>
					(PATH_MIN_LEN, PATH_MAX_LEN);
			} else { // if (gen_type == GEN_TYPE_ROOM)
				const IntVec2 temp_vec2{
					.x=engine->layout_rand<i32>
						(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x),
					.y=engine->layout_rand<i32>
						(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y)
				};
				//thickness = engine->layout_rand<i32>
				//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
				//length = engine->layout_rand<i32>
				//	(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y);

				if (
					rp.gen_side == GEN_SIDE_L
					|| rp.gen_side == GEN_SIDE_R
				) {
					thickness = temp_vec2.y;
					length = temp_vec2.x;
				} else // if (
					//rp.gen_side == GEN_SIDE_T || rp.gen_side == GEN_SIDE_B
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

			switch (rp.gen_side) {
			//--------
			case GEN_SIDE_L:
				rp.rect.pos = IntVec2
					{.x=conn_rp_lx,
					.y=engine->layout_rand<i32>(conn_rp_ty, conn_rp_by)}
						- IntVec2{length, 0};
				rp.rect.size_2d = {.x=length, .y=thickness};
				break;
			case GEN_SIDE_T:
				rp.rect.pos = IntVec2
					{.x=engine->layout_rand<i32>(conn_rp_lx, conn_rp_rx),
					.y=conn_rp_ty} - IntVec2{0, length};
				rp.rect.size_2d = {.x=thickness, .y=length};
				break;
			case GEN_SIDE_R:
				rp.rect.pos = IntVec2
					{.x=conn_rp_rx,
					.y=engine->layout_rand<i32>(conn_rp_ty, conn_rp_by)}
						+ IntVec2{1, 0};
				rp.rect.size_2d = {.x=length, .y=thickness};
				break;
			case GEN_SIDE_B:
				rp.rect.pos = IntVec2
					{.x=engine->layout_rand<i32>(conn_rp_lx, conn_rp_rx),
					.y=conn_rp_by} + IntVec2{0, 1};
				rp.rect.size_2d = {.x=thickness, .y=length};
				break;
			default:
				throw std::runtime_error(sconcat
					("game_engine::sys::GmDungeonGen::_gen_single_rp(): ",
					"(1st) `switch (rp.gen_side)`: Eek! `", rp.gen_side,
					"`"));
				break;
			//--------
			}
			//--------
			// This is a simple algorithm that could be made faster and
			// more complicated, but I figure any platform running this
			// game will have fast enough hardware considering the maximum
			// numbers of rooms/paths.
			if (!rp.fits_in_pfield()) {
				return false;
			}
			//printout("rp.fits_in_pfield(): ", rp.rect, "\n");

		
			//const IntVec2
			//	tl_amount
			//		{.x=rp.gen_side == GEN_SIDE_L ? 0 : 1,
			//		.y=rp.gen_side == GEN_SIDE_T ? 0 : 1},
			//	br_amount
			//		{.x=rp.gen_side == GEN_SIDE_R ? 0 : 1,
			//		.y=rp.gen_side == GEN_SIDE_B ? 0 : 1};
			//const IntRect2 inflated_rect
			//	= rp.rect.build_in_grid_inflated_lim
			//		(tl_amount, br_amount, PFIELD_PHYS_RECT2);

			for (size_t i=0; i<dungeon_gen->size(); ++i) {
				const IntRect2
					//left_side_r2 = IntRect2::build_in_grid
					//	(rp.rect.tl_corner() - IntVec2{1, 0},
					//	rp.rect.bl_corner() - IntVec2{1, 0}),
					//top_side_r2 = IntRect2::build_in_grid
					//	(rp.rect.tl_corner() - IntVec2{0, 1},
					//	rp.rect.tr_corner() - IntVec2{0, 1}),
					//right_side_r2 = IntRect2::build_in_grid
					//	(rp.rect.tr_corner() + IntVec2{1, 0},
					//	rp.rect.br_corner() + IntVec2{1, 0}),
					//bottom_side_r2 = IntRect2::build_in_grid
					//	(rp.rect.bl_corner() + IntVec2{0, 1},
					//	rp.rect.br_corner() + IntVec2{0, 1});
					left_side_r2 = {
						.pos=rp.rect.pos - IntVec2{1, 0},
						.size_2d{1, rp.rect.size_2d.y},
					},
					top_side_r2 = {
						.pos=rp.rect.pos - IntVec2{0, 1},
						.size_2d{rp.rect.size_2d.x, 1},
					},
					right_side_r2 = {
						.pos=rp.rect.pos + IntVec2{rp.rect.size_2d.x, 0},
						.size_2d{1, rp.rect.size_2d.y},
					},
					bottom_side_r2 = {
						.pos=rp.rect.pos + IntVec2{0, rp.rect.size_2d.y},
						.size_2d={rp.rect.size_2d.x, 1},
					};
				const auto& item = dungeon_gen->at(i);

				if (
					item.rect.intersect(rp.rect)
					|| (
						rp.gen_side == GEN_SIDE_L
						&& PFIELD_PHYS_RECT2.intersect(left_side_r2)
						&& item.rect.intersect(left_side_r2)
					) || (
						rp.gen_side == GEN_SIDE_T
						&& PFIELD_PHYS_RECT2.intersect(top_side_r2)
						&& item.rect.intersect(top_side_r2)
					) || (
						rp.gen_side == GEN_SIDE_R
						&& PFIELD_PHYS_RECT2.intersect(right_side_r2)
						&& item.rect.intersect(right_side_r2)
					) || (
						rp.gen_side == GEN_SIDE_B
						&& PFIELD_PHYS_RECT2.intersect(bottom_side_r2)
						&& item.rect.intersect(bottom_side_r2)
					)
				) {
					printout("debug: failed dungeon generation: ",
						rp.rect, " ", item.rect, "; ",
						"left: ", left_side_r2, " ",
						"top: ", top_side_r2, " ",
						"right: ", right_side_r2, " ", 
						"bottom: ", bottom_side_r2,
						"\n");
					return false;
				}
			}
			//--------
			rp.conn_index_set.insert(conn_rp_index);
			conn_rp.conn_index_set.insert(dungeon_gen->size());
			//--------
			//comp::DungeonGen::RoomPath
			//	* room_ptr = nullptr,
			//	* path_ptr = nullptr;
			//if (rp.is_path() && conn_rp.is_room()) {
			//	room_ptr = 
			//}
			//if (rp.is_path() && conn_rp.is_room()) {
			//	switch (rp.gen_side) {
			//	//--------
			//	case GEN_SIDE_L:
			//		conn_rp.door_pt_set.insert({
			//		});
			//		break;
			//	case GEN_SIDE_T:
			//		conn_rp.door_pt_set.insert({
			//		});
			//		break;
			//	case GEN_SIDE_R:
			//		conn_rp.door_pt_set.insert({
			//		});
			//		break;
			//	case GEN_SIDE_B:
			//		conn_rp.door_pt_set.insert({
			//		});
			//		break;
			//	default:
			//		throw std::runtime_error(sconcat
			//			("game_engine::sys::GmDungeonGen",
			//			"::_gen_single_rp(): ",
			//			"(2nd) `switch (rp.gen_side)`: Eek! `",
			//			rp.gen_side, "`"));
			//		break;
			//	//--------
			//	}
			//} else if (rp.is_room() && conn_rp.is_path()) {
			//	switch (gen_side) {
			//	//--------
			//	case GEN_SIDE_L:
			//		rp.door_pt_set.insert({
			//		});
			//		break;
			//	case GEN_SIDE_T:
			//		rp.door_pt_set.insert({
			//		});
			//		break;
			//	case GEN_SIDE_R:
			//		rp.door_pt_set.insert({
			//		});
			//		break;
			//	case GEN_SIDE_B:
			//		rp.door_pt_set.insert({
			//		});
			//		break;
			//	default:
			//		throw std::runtime_error(sconcat
			//			("game_engine::sys::GmDungeonGen",
			//			"::_gen_single_rp(): ",
			//			"(3rd) `switch (rp.gen_side)`: Eek! `",
			//			rp.gen_side, "`"));
			//		break;
			//	//--------
			//	}
			//}
			//--------
			//printout("`gen_type`: ", gen_type, "\n");

			return true;
			//--------
		};

		if (dungeon_gen->size() < MIN_NUM_ROOM_PATHS) {
			for (;;) {
				if (inner_gen()) {
					break;
				}
			}
		} else {
			i32 tries = 0;
			for (; tries<GEN_RP_MAX_TRIES; ++tries) {
				if (inner_gen()) {
					break;
				}
			}
			// If we failed to find a room that fits in the playfield, we
			// stop floor generation early, and don't try any more for this
			// floor.  This is to prevent infinite loops in the dungeon
			// generation.
			_stop_gen_early = tries >= GEN_RP_MAX_TRIES;
			if (_stop_gen_early) {
				printout("stopping room generation early: ",
					dungeon_gen->size(), " ", _attempted_num_rp,
					"\n");
			}
		}

		do_push_back();
	}
}
//void GmDungeonGen::_connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
//	comp::DungeonGen* dungeon_gen) {
//}
//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
