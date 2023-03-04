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

#include "dngn_gen_class.hpp"
#include "metaball_gen_class.hpp"
#include "dijkstra_map_gen_class.hpp"
#include "path_class.hpp"
#include "bfs_funcs.hpp"
#include "../engine_class.hpp"
#include "../comp/drawable_data_umap.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace lvgen_etc {
//--------
i32 DngnGen::GenNext::gen() const {
	return engine->layout_rand<i32>(full_min(), full_max());
}
i32 DngnGen::GenYesNo::gen() const {
	return engine->layout_rand<i32>(full_min(), full_max());
}
//--------
const std::vector<std::vector<BgTile>>
	DngnGen::ALLOWED_ALT_TERRAIN_DA2D({
		// Level 1 (index 0)
		build_bg_tile_darr
			({{2, BgTile::Water},
			//SizeAndBgTile(5, BgTile::Water),
			//BgTile::Water,
			{1, BgTile::Spikes}
			//SizeAndBgTile(20, BgTile::Spikes)
			//SizeAndBgTile(3, BgTile::Lava)
			}),

		// Level 2 (index 1)
		build_bg_tile_darr
			({{1, BgTile::Water},
			{1, BgTile::Spikes},
			{1, BgTile::Pit}}),

		// Level 3 (index 2)
		build_bg_tile_darr
			({{2, BgTile::Water},
			//BgTile::Lava,
			{2, BgTile::Spikes},
			{1, BgTile::Pit}}),

		// Level 4 (index 3)
		build_bg_tile_darr
			({{1, BgTile::Lava},
			{2, BgTile::Spikes},
			{1, BgTile::Pit}, }),

		// Level 5 (index 4)
		build_bg_tile_darr
			({{1, BgTile::Lava},
			{1, BgTile::Spikes}}),
	});
void DngnGen::clear_before_gen(
	//ecs::Engine* ecs_engine
) {
	//auto* dngn_floor
	//	= ecs_engine->casted_comp_at<DngnFloor>(*_dngn_gen_id);
	engine->dngn_floor().clear_before_gen();
	//engine->clear_dngn_floor_arr();
	//dngn_floor->clear(engine->calc_layout_noise_add_amount());
	//_stop_gen_early = false;
	_attempted_num_rt = engine->layout_rand<i32>
		(i32(MIN_NUM_ROOM_TUNNELS), i32(MAX_NUM_ROOM_TUNNELS));
	_stop_gen_early = false;
	_done_generating = false;
}
void DngnGen::gen_curr_floor() {

	//if (dngn_floor->size() == 0) {
	//	engine->dbg_log("Debug: starting dungeon generation.\n");
	//}
	while (!_done_generating) {
		GenInnards innards(
			this
			//ecs_engine,
			//dngn_floor
		);
		innards.gen_single_rt();
		if (_done_generating) {
			innards.finalize();
			//innards._insert_alt_terrain(
			//	//true
			//);
		}
	}
	//else {
	//	engine->dbg_log("Debug: We're already done generating\n");
	//}
}
//void DngnGen::_connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
//	DngnFloor* dngn_floor) {
//}
bool DngnGen::GenInnards::gen_single_rt() {
	//--------
	auto redo = [this]() -> void {
		engine->dbg_log
			("Debug: game_engine::lvgen_etc::DngnGen::GenInnards"
			"::gen_single_rt(): ",
			"Redoing generation\n");
		_self->clear_before_gen(
			//_ecs_engine
		);
	};
	//--------
	const bool old_done_generating = _self->_done_generating;
	//--------
	if (engine->dngn_floor().size() == 0) {
		//_self->_attempted_num_rt = engine->layout_rand<i32>
		//	(i32(MIN_NUM_ROOM_TUNNELS), i32(MAX_NUM_ROOM_TUNNELS));
		//_self->_stop_gen_early = false;
		//_self->_done_generating = false;
		_self->clear_before_gen(
			//_ecs_engine
		);

		// We always generate a room in this case.
		//for (i32 tries=0; tries<GEN_RT_LIM_TRIES; ++tries)
		// Force there to be at least one room
		//for (;;) {
			RoomTunnel to_push_rt;
			//--------
			//engine->dbg_log("testificate 2\n");
			//--------
			//to_push_rt.rect.pos.x = engine->layout_rand<i32>
			//	(PFIELD_PHYS_RECT2.left_x(),
			//	PFIELD_PHYS_RECT2.right_x() - ROOM_MIN_SIZE_2D.x - 1);
			//to_push_rt.rect.pos.y = engine->layout_rand<i32>
			//	(PFIELD_PHYS_RECT2.top_y(),
			//	PFIELD_PHYS_RECT2.bottom_y() - ROOM_MIN_SIZE_2D.y - 1);

			//to_push_rt.rect.size_2d.x = engine->layout_rand<i32>
			//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
			//to_push_rt.rect.size_2d.y = engine->layout_rand<i32>
			//	(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y);
			to_push_rt.rect = engine->layout_rand_r2_in_pfnb
				(ROOM_MIN_SIZE_2D, ROOM_MAX_SIZE_2D);
			//--------
			//if (to_push_rt.fits_in_pfnb()) {
			//	_do_push_back(std::move(to_push_rt));
			//	break;
			//}
			_do_push_back(std::move(to_push_rt));
			//break;
			//--------
		//}
	}
	//else if (engine->dngn_floor().size() < MAX_NUM_ROOM_TUNNELS)
	else if (
		i32(engine->dngn_floor().size()) < _self->_attempted_num_rt
	) {
		//RoomTunnel to_push_rt;
		//if (engine->dngn_floor().size() < MIN_NUM_ROOM_TUNNELS) {
		//	for (;;) {
		//		if (auto opt_rt=_inner_gen_post_first(); opt_rt) {
		//			_do_push_back(std::move(*opt_rt));
		//			break;
		//		}
		//	}
		//} else if (!_self->_stop_gen_early) {
			i32 tries = 0;
			for (; tries<GEN_RT_LIM_TRIES; ++tries) {
				_self->_stop_gen_early = true;
				if (auto opt_rt=_inner_gen_post_first(); opt_rt) {
					_do_push_back(std::move(*opt_rt));
					_self->_stop_gen_early = false;
					break;
				}
			}
			//_self->_stop_gen_early = tries >= GEN_RT_LIM_TRIES;
			if (_self->_stop_gen_early) {
				if (engine->dngn_floor().size() < MIN_NUM_ROOM_TUNNELS) {
					redo();
				} else {
					// If we failed to find a room that fits in the
					// playfield, we stop floor generation early, and don't
					// try any more for this floor.  This is to prevent
					// infinite loops in the dungeon generation.
					engine->dbg_log
						("Debug: game_engine::sys::gen_single_rt(): ",
						"stopping room generation early: ",
						engine->dngn_floor().size(), " ",
						_self->_attempted_num_rt, "\n");
				}
			}
			//else {
			//}
		//}
	}
	_self->_done_generating
		= _self->_stop_gen_early
			|| i32(engine->dngn_floor().size())
				>= _self->_attempted_num_rt;
	if (_self->_done_generating) {
		i32 num_rooms = 0;
		for (size_t i=0; i<engine->dngn_floor().size(); ++i) {
			if (engine->dngn_floor().at(i).is_room()) {
				++num_rooms;
			}
		}
		if (num_rooms < MIN_NUM_ROOMS) {
			engine->dbg_log
				("Debug: game_engine::lvgen_etc::DngnGen",
				"::GenInnards::gen_single_rt(): ",
				"Didn't generate enough rooms. ",
				"Generated ", num_rooms, " rooms, but need at least ",
				MIN_NUM_ROOMS, ".\n");
			redo();
		}
	}
	if (!old_done_generating && _self->_done_generating) {
		engine->dbg_log
			("Just finished generating the dungeon's basic shape.\n");
	}

	return _self->_done_generating;
}
auto DngnGen::GenInnards::_inner_gen_post_first()
-> std::optional<RoomTunnel> {
	//--------
	//RoomTunnel _temp_to_push_rt;

	if (auto temp=_gen_initial_rt(); temp) {
		_temp_to_push_rt = std::move(*temp);
	} else {
		return std::nullopt;
	}
	//--------
	//const IntRect2
	//	ORIG_TO_PUSH_RECT = _temp_to_push_rt.rect;
	//const bool
	//	was_horiz_tunnel = DngnFloor::r2_is_horiz_tunnel(ORIG_TO_PUSH_RECT),
	//	was_vert_tunnel = DngnFloor::r2_is_vert_tunnel(ORIG_TO_PUSH_RECT);
	//	//was_room = DngnFloor::r2_is_room(ORIG_TO_PUSH_RECT);
	//--------
	//auto _basic_shrink_extra_test_func = [this](
	//	RoomTunnel& some_rt
	//	//, const std::optional<size_t>& index
	//) -> bool {
	//	const auto& found
	//		= _find_first_backend(
	//			some_rt, std::nullopt,
	//			[](RoomTunnel& some_rt, const RoomTunnel& some_item)
	//			-> bool {
	//				//return !(some_item.rect.intersect(some_rt.rect)
	//				//	|| _some_sides_hit(some_rt, some_item)
	//				//	|| !_tunnel_sides_hit_wrongly(some_rt, some_item));
	//				return (some_item.rect.intersect(some_rt.rect)
	//					//&& _some_sides_hit(some_rt, some_item)
	//					|| _tunnel_sides_hit_wrongly(some_rt, some_item)
	//					// Reject pairs of horizontal/vertical paths that
	//					// are too close
	//					|| _parallel_tunnels_too_close(some_rt, some_item));
	//			});
	//	//if (found) {
	//	//	//engine->dbg_log("found{", *found, "}\n");
	//	//	engine->dbg_log("found\n");
	//	//} else {
	//	//	engine->dbg_log("!found\n");
	//	//}
	//	return (some_rt.fits_in_pfnb()
	//		&& !found
	//		//&& !any_intersect_find_first(some_rt, std::nullopt)
	//		//&& any_sides_intersect_find_first(some_rt, std::nullopt)
	//		//&& !any_tunnel_sides_hit_wrongly_find_first
	//		//	(some_rt, std::nullopt)
	//		&& _rt_is_connected(some_rt)
	//		);
	//};
	// This is a simple algorithm that could be made faster and
	// more complicated, but I figure any platform running this
	// game will have fast enough hardware considering the maximum
	// numbers of rooms/paths.
	if (!_shrink
		(_temp_to_push_rt.is_horiz_tunnel(), 
		_temp_to_push_rt.is_vert_tunnel(),
		_temp_to_push_rt, // std::nullopt,
		[this](RoomTunnel& some_rt) -> bool {
			return _basic_shrink_extra_test_func(some_rt);
		})) {
		return std::nullopt;
	}


	//if (any_intersect_find_first(_temp_to_push_rt, std::nullopt)) {
	//	//engine->dbg_log("Debug: found early intersect!\n");
	//	return std::nullopt;
	//}
	//if (any_tunnel_sides_hit_wrongly_find_first(_temp_to_push_rt, std::nullopt)) {
	//	return std::nullopt;
	//}

	_connect_by_extending();
	//--------
	//_temp_to_push_rt.conn_index_uset.insert(conn_rt_index);
	//conn_rt.conn_index_uset.insert(engine->dngn_floor().size());
	//--------
	//--------
	//engine->dbg_log("`gen_type`: ", gen_type, "\n");

	return _temp_to_push_rt;
	//--------
};
void DngnGen::GenInnards::_do_push_back(RoomTunnel&& to_push_rt) const {
	//#ifdef DEBUG
	//engine->dbg_log("Debug: Generated this `RoomTunnel`: ",
	//	//to_push_rt.rect, "; ",
	//	"to_push_rt.tl:", to_push_rt.rect.tl_corner(), " ",
	//	"to_push_rt.br:", to_push_rt.rect.br_corner(), "; ",
	//	to_push_rt.is_horiz_tunnel(), " ",
	//	to_push_rt.is_vert_tunnel(), " ",
	//	to_push_rt.is_room(),
	//	"\n");
	//#endif		// DEBUG

	const auto
		to_push_rt_index = engine->dngn_floor().size();

	for (
		size_t item_index=0;
		item_index<engine->dngn_floor().size();
		++item_index
	) {
		auto& item = engine->dngn_floor()._raw_at(item_index);
		if (item.rect.intersect(to_push_rt.rect)) {
			throw std::runtime_error(sconcat
				("game_engine::lvgen_etc::DngnGen",
				"::GenInnards::_do_push_back(): ",
				"Eek! ",
				"to_push_rt{", to_push_rt.rect.tl_corner(), " ",
					to_push_rt.rect.br_corner(), "} ",
				"item{", item.rect.tl_corner(), " ",
					item.rect.br_corner(), "}\n"));
		} else if (
			_ls_r2_hit(to_push_rt, item)
			|| _ts_r2_hit(to_push_rt, item)
			|| _rs_r2_hit(to_push_rt, item)
			|| _bs_r2_hit(to_push_rt, item)
			//|| _ls_r2_hit(item, to_push_rt)
			//|| _ts_r2_hit(item, to_push_rt)
			//|| _rs_r2_hit(item, to_push_rt)
			//|| _bs_r2_hit(item, to_push_rt)
			//_ls_r2(item).intersect(to_push_rt.rect)
			//|| _ts_r2(item).intersect(to_push_rt.rect)
			//|| _rs_r2(item).intersect(to_push_rt.rect)
			//|| _bs_r2(item).intersect(to_push_rt.rect)
		) {
			to_push_rt.conn_index_uset.insert(i32(item_index));
			item.conn_index_uset.insert
				(i32(to_push_rt_index));
			//engine->dbg_log("Connected these RTs: ",
			//	"to_push_rt{", to_push_rt.rect.tl_corner(), " ",
			//		to_push_rt.rect.br_corner(), "} ",
			//		to_push_rt_index, " "
			//	"item{", item.rect.tl_corner(), " ",
			//		item.rect.br_corner(), "} ",
			//		item_index, "\n");
		}
	}

	engine->dngn_floor().push_back(std::move(to_push_rt));

	//to_push_rt = RoomTunnel();
}
auto DngnGen::GenInnards::_gen_initial_rt()
-> std::optional<RoomTunnel> {
	//--------
	RoomTunnel to_push_rt;

	const i32
		prev_rt_index = engine->dngn_floor().size() - 1;
	const RoomTunnel
		& prev_rt = engine->dngn_floor().at(prev_rt_index);
	const i32
		prev_gen_type
			= prev_rt.is_tunnel() ? GEN_TYPE_TUNNEL : GEN_TYPE_ROOM;

	to_push_rt.gen_side = 0;
	_gen_next_type = 0;
	_gen_next_conn_rt_index = 0;
	_gen_type = 0;
	_conn_rt_index = 0;

	//_gen_type = GEN_TYPE_ROOM,
	//to_push_rt.gen_side = engine->layout_rand<i32>
	//	(MIN_GEN_SIDE, MAX_GEN_SIDE),

	_gen_next_type = (prev_gen_type == GEN_TYPE_TUNNEL)
		? engine->layout_rand<i32>
			(GEN_NEXT_TUNNEL_TYPE.full_min(),
			GEN_NEXT_TUNNEL_TYPE.full_max())
		: engine->layout_rand<i32>
			(GEN_NEXT_ROOM_TYPE.full_min(),
			GEN_NEXT_ROOM_TYPE.full_max()),

	_gen_type = 0;
	if (
		(
			prev_gen_type == GEN_TYPE_TUNNEL
			&& _gen_next_type >= GEN_NEXT_TUNNEL_TYPE.same_min()
			&& _gen_next_type <= GEN_NEXT_TUNNEL_TYPE.same_max
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
		_gen_next_conn_rt_index
			= engine->layout_rand<i32>
			(some_gen_next_index.full_min(),
			some_gen_next_index.full_max());
		if (
			_gen_next_conn_rt_index >= some_gen_next_index.same_min()
			&& _gen_next_conn_rt_index <= some_gen_next_index.same_max
		) {
			_conn_rt_index = prev_rt_index;
		} else {
			if (prev_rt_index == 0) {
				_conn_rt_index = prev_rt_index;
			} else { // if (prev_rt_index > 0)
				// Force a different room from the last one to be
				// picked in this case
				_conn_rt_index
					= engine->layout_rand<i32>(0, prev_rt_index - 1);
			}
		}
	};
	if (prev_gen_type == GEN_TYPE_TUNNEL) {
		if (_gen_type == GEN_TYPE_TUNNEL) {
			index_stuff(GEN_NEXT_TUNNEL_INDEX_NOW_TUNNEL);
		} else { // if (_gen_type == GEN_TYPE_ROOM)
			index_stuff(GEN_NEXT_TUNNEL_INDEX_NOW_ROOM);
		}
		//index_stuff(GEN_NEXT_TUNNEL_INDEX);
	} else { // if (prev_gen_type == GEN_TYPE_ROOM)
		index_stuff(GEN_NEXT_ROOM_INDEX);
	}
	//--------
	//const i32 _conn_rt_index = engine->layout_rand<i32>(0, 0);
	//engine->dbg_log("test 1\n");
	const auto& conn_rt = engine->dngn_floor().at(_conn_rt_index);

	if (
		//(conn_rt.is_tunnel() && _gen_type == GEN_TYPE_TUNNEL)
		//|| (conn_rt.is_room() && _gen_type == GEN_TYPE_ROOM)

		//(conn_rt.is_tunnel() && _gen_type == GEN_TYPE_TUNNEL)
		//|| conn_rt.is_room()
		conn_rt.is_tunnel()
	) {
		if (_gen_type == GEN_TYPE_TUNNEL) {
			to_push_rt.gen_side = engine->layout_rand<i32>
				(MIN_GEN_SIDE, MAX_GEN_SIDE);
		} else { // if (_gen_type == GEN_TYPE_ROOM)
			if (conn_rt.is_horiz_tunnel()) {
				to_push_rt.gen_side
					= engine->layout_rand<i32>(0, 1)
					? GEN_SIDE_L
					: GEN_SIDE_R;
			} else { // if (conn_rt.is_vert_tunnel())
				to_push_rt.gen_side
					= engine->layout_rand<i32>(0, 1)
					? GEN_SIDE_T
					: GEN_SIDE_B;
			}
		}
	} else { // if (conn_rt.is_room())
		to_push_rt.gen_side = engine->layout_rand<i32>
			(MIN_GEN_SIDE, MAX_GEN_SIDE);
	}
	//--------
	i32
		thickness = 0,
		length = 0;
	//IntVec2
	//	temp_size_2d;

	if (_gen_type == GEN_TYPE_TUNNEL) {
		thickness
			//temp_size_2d.x
			= TUNNEL_THICKNESS,
		length
			//temp_size_2d.y
			= engine->layout_rand<i32>
				(TUNNEL_MIN_LEN, TUNNEL_MAX_LEN);
	} else { // if (_gen_type == GEN_TYPE_ROOM)
		const IntVec2 temp_vec2
		//temp_size_2d =
			//{.x=engine->layout_rand<i32>
			//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x),
			//.y=engine->layout_rand<i32>
			//	(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y)};
			= engine->layout_rand_vec2(ROOM_MIN_SIZE_2D, ROOM_MAX_SIZE_2D);
		//thickness = engine->layout_rand<i32>
		//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
		//length = engine->layout_rand<i32>
		//	(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y);

		if (to_push_rt.gen_side == GEN_SIDE_L
			|| to_push_rt.gen_side == GEN_SIDE_R) {
			thickness = temp_vec2.y;
			length = temp_vec2.x;
		} else // if (
			//to_push_rt.gen_side == GEN_SIDE_T
			//|| to_push_rt.gen_side == GEN_SIDE_B
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
		conn_rt_lx = conn_rt.rect.left_x(),
		conn_rt_ty = conn_rt.rect.top_y(),
		conn_rt_rx = conn_rt.rect.right_x(),
		conn_rt_by = conn_rt.rect.bottom_y();

	switch (to_push_rt.gen_side) {
	//--------
	case GEN_SIDE_L:
		to_push_rt.rect.pos = IntVec2
			{.x=conn_rt_lx,
			.y=engine->layout_rand<i32>(conn_rt_ty, conn_rt_by)}
				- IntVec2{length, 0};
		to_push_rt.rect.size_2d = {.x=length, .y=thickness};
		break;
	case GEN_SIDE_T:
		to_push_rt.rect.pos = IntVec2
			{.x=engine->layout_rand<i32>(conn_rt_lx, conn_rt_rx),
			.y=conn_rt_ty} - IntVec2{0, length};
		to_push_rt.rect.size_2d = {.x=thickness, .y=length};
		break;
	case GEN_SIDE_R:
		to_push_rt.rect.pos = IntVec2
			{.x=conn_rt_rx,
			.y=engine->layout_rand<i32>(conn_rt_ty, conn_rt_by)}
				+ IntVec2{1, 0};
		to_push_rt.rect.size_2d = {.x=length, .y=thickness};
		break;
	case GEN_SIDE_B:
		to_push_rt.rect.pos = IntVec2
			{.x=engine->layout_rand<i32>(conn_rt_lx, conn_rt_rx),
			.y=conn_rt_by} + IntVec2{0, 1};
		to_push_rt.rect.size_2d = {.x=thickness, .y=length};
		break;
	default:
		throw std::runtime_error(sconcat
			("game_engine::sys::DngnGen::gen_single_rt(): ",
			"(1st) `switch (to_push_rt.gen_side)`: Eek! `",
			to_push_rt.gen_side,
			"`"));
		break;
	//--------
	}
	return to_push_rt;
}
bool DngnGen::GenInnards::_shrink(
	bool was_horiz_tunnel, bool was_vert_tunnel,
	RoomTunnel& some_rt, //const std::optional<size_t>& index,
	const std::function<bool(
		RoomTunnel&//, const std::optional<size_t>&
	)>& extra_test_func
) {
	//--------
	auto shrink_left_x = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rt.rect.tl_corner() + IntVec2{1, 0},
			some_rt.rect.br_corner(),
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rt.rect = temp_rect;
	};
	auto shrink_top_y = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rt.rect.tl_corner() + IntVec2{0, 1},
			some_rt.rect.br_corner(),
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rt.rect = temp_rect;
	};
	auto shrink_right_x = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rt.rect.tl_corner(),
			some_rt.rect.br_corner() - IntVec2{1, 0},
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rt.rect = temp_rect;
	};
	auto shrink_bottom_y = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rt.rect.tl_corner(),
			some_rt.rect.br_corner() - IntVec2{0, 1},
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rt.rect = temp_rect;
	};
	//--------
	//const RoomTunnel& conn_rt = engine->dngn_floor().at(_conn_rt_index);
	//const bool
	//	was_horiz_tunnel = some_rt.is_horiz_tunnel(),
	//	was_vert_tunnel = some_rt.is_vert_tunnel();
	//	//was_room = some_rt.is_room();
	if (was_horiz_tunnel) {
		const i32
			SHRINK_NUM_ATTEMPTS = engine->layout_rand<i32>
				(MIN_GEN_SHRINK_NUM_ATTEMPTS_TUNNEL,
				MAX_GEN_SHRINK_NUM_ATTEMPTS_TUNNEL);
		for (i32 i=0; i<SHRINK_NUM_ATTEMPTS; ++i) {
			//--------
			switch (some_rt.gen_side) {
			//--------
			case GEN_SIDE_L:
				shrink_left_x();
				break;
			case GEN_SIDE_R:
				shrink_right_x();
				break;
			default:
				//if (engine->layout_rand<i32>(0, 1)) {
				//	shrink_left_x();
				//} else {
				//	shrink_right_x();
				//}
				break;
			//--------
			}
			//--------
			if (
				some_rt.is_horiz_tunnel()
				&& extra_test_func(
					some_rt//, index
				)
			) {
				return true;
			} else if (!some_rt.is_horiz_tunnel()) {
				return false;
			}
			//--------
		}
	} else if (was_vert_tunnel) {
		const i32
			SHRINK_NUM_ATTEMPTS = engine->layout_rand<i32>
				(MIN_GEN_SHRINK_NUM_ATTEMPTS_TUNNEL,
				MAX_GEN_SHRINK_NUM_ATTEMPTS_TUNNEL);
		for (i32 i=0; i<SHRINK_NUM_ATTEMPTS; ++i) {
			//--------
			switch (some_rt.gen_side) {
			//--------
			case GEN_SIDE_T:
				shrink_top_y();
				break;
			case GEN_SIDE_B:
				shrink_bottom_y();
				break;
			default:
				//if (engine->layout_rand<i32>(0, 1)) {
				//	shrink_top_y();
				//} else {
				//	shrink_bottom_y();
				//}
				break;
			//--------
			}
			//--------
			if (
				some_rt.is_vert_tunnel()
				&& extra_test_func(
					some_rt//, index
				)
			) {
				return true;
			} else if (!some_rt.is_vert_tunnel()) {
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
			const i32 gen_side = some_rt.gen_side;
			//const i32 shrink_side = gen_side;
			i32 shrink_side;

			do {
				shrink_side = engine->layout_rand<i32>
					(MIN_GEN_SIDE, MAX_GEN_SIDE);
			} while (
				(gen_side == GEN_SIDE_L && shrink_side == GEN_SIDE_R)
				|| (gen_side == GEN_SIDE_T && shrink_side == GEN_SIDE_B)
				|| (gen_side == GEN_SIDE_R && shrink_side == GEN_SIDE_L)
				|| (gen_side == GEN_SIDE_B && shrink_side == GEN_SIDE_T)
			);

			switch (shrink_side) {
			//--------
			case GEN_SIDE_L:
				shrink_left_x();
				break;
			case GEN_SIDE_T:
				shrink_top_y();
				break;
			case GEN_SIDE_R:
				shrink_right_x();
				break;
			case GEN_SIDE_B:
				shrink_bottom_y();
				break;
			default:
				throw std::runtime_error(sconcat
					("game_engine::sys::DngnGen::GenInnards",
					"::_shrink(): Eek! ",
					"shrink_side{", shrink_side, "}"));
				break;
			//--------
			}
			//--------
			if (
				some_rt.is_room()
				&& extra_test_func(
					some_rt//, index
				)
			) {
				return true;
			} else if (!some_rt.is_room()) {
				return false;
			}
			//--------
		}
	}
	return false;
	//return final_func();
};
bool DngnGen::GenInnards::_basic_shrink_extra_test_func(
	RoomTunnel& some_rt
	//, const std::optional<size_t>& index
) {
	const auto& found
		= _find_first_backend
			(some_rt, std::nullopt,
			[](RoomTunnel& some_rt, const RoomTunnel& some_item)
			-> bool {
				//return !(some_item.rect.intersect(some_rt.rect)
				//	|| _some_sides_hit(some_rt, some_item)
				//	|| !_tunnel_sides_hit_wrongly(some_rt, some_item));
				return (some_item.rect.intersect(some_rt.rect)
					//&& _some_sides_hit(some_rt, some_item)
					|| _tunnel_sides_hit_wrongly(some_rt, some_item)
					// Reject pairs of horizontal/vertical paths that
					// are too close
					|| _parallel_tunnels_too_close(some_rt, some_item));
			});
	//if (found) {
	//	//engine->dbg_log("found{", *found, "}\n");
	//	engine->dbg_log("found\n");
	//} else {
	//	engine->dbg_log("!found\n");
	//}
	return (some_rt.fits_in_pfnb()
		&& !found
		//&& !any_intersect_find_first(some_rt, std::nullopt)
		//&& any_sides_intersect_find_first(some_rt, std::nullopt)
		//&& !any_tunnel_sides_hit_wrongly_find_first
		//	(some_rt, std::nullopt)
		&& _rt_is_connected(some_rt)
		);
}
void DngnGen::GenInnards::_connect_by_extending(
	//bool was_horiz_tunnel, bool was_vert_tunnel,
	//RoomTunnel& some_rt, //const std::optional<size_t>& index,
	//const std::function<bool(
	//	RoomTunnel&//, const std::optional<size_t>&
	//)>& shrink_extra_test_func
) {
	auto should_gen_connect = []() -> bool {
		const i32
			temp = engine->layout_rand<i32>
				(GEN_YN_CONNECT.full_min(), GEN_YN_CONNECT.full_max());
		return (temp >= GEN_YN_CONNECT.yes_min()
			&& temp <= GEN_YN_CONNECT.yes_max);
	};
	const bool
		was_horiz_tunnel = _temp_to_push_rt.is_horiz_tunnel(),
		was_vert_tunnel = _temp_to_push_rt.is_vert_tunnel();
	auto attempt_extend = [&](
		const IntVec2& tl_ext, const IntVec2& br_ext
	) -> void {
		RoomTunnel temp_rt;
		temp_rt.rect = _temp_to_push_rt.rect.build_in_grid_inflated_lim
			(tl_ext, br_ext, PFIELD_PHYS_NO_BRDR_RECT2);
		if (_shrink(
			was_horiz_tunnel, was_vert_tunnel,
			temp_rt,
			[this](RoomTunnel& some_rt) -> bool {
				return _basic_shrink_extra_test_func(some_rt);
			}
		)) {
			_temp_to_push_rt.rect = temp_rt.rect;
		}
	};
	for (
		i32 basic_side=MIN_GEN_SIDE,
			temp_side=engine->layout_rand<i32>
				(MIN_GEN_SIDE, MAX_GEN_SIDE);
		basic_side<=MAX_GEN_SIDE;
		++basic_side,
			temp_side=(temp_side + 1)
				% (MAX_GEN_SIDE - MIN_GEN_SIDE + 1)
	) {
		switch (temp_side) {
		//--------
		case GEN_SIDE_L:
			if (
				should_gen_connect()
				&& !was_vert_tunnel
				&& (_temp_to_push_rt.is_horiz_tunnel()
				|| _temp_to_push_rt.is_room())
			){
				attempt_extend
					(IntVec2{GEN_EXTEND_AMOUNT_TSF, 0}, IntVec2());
			}
			break;
		case GEN_SIDE_T:
			if (
				should_gen_connect()
				&& !was_horiz_tunnel
				&& (_temp_to_push_rt.is_vert_tunnel()
				|| _temp_to_push_rt.is_room())
			) {
				attempt_extend
					(IntVec2{0, GEN_EXTEND_AMOUNT_TSF}, IntVec2());
			}
			break;
		case GEN_SIDE_R:
			if (
				should_gen_connect()
				&& !was_vert_tunnel
				&& (_temp_to_push_rt.is_horiz_tunnel()
				|| _temp_to_push_rt.is_room())
			) {
				attempt_extend
					(IntVec2(), IntVec2{GEN_EXTEND_AMOUNT_TSF, 0});
			}
			break;
		case GEN_SIDE_B:
			if (
				should_gen_connect()
				&& !was_horiz_tunnel
				&& (_temp_to_push_rt.is_vert_tunnel()
				|| _temp_to_push_rt.is_room())
			) {
				attempt_extend
					(IntVec2(), IntVec2{0, GEN_EXTEND_AMOUNT_TSF});
			}
			break;
		default:
			throw std::runtime_error(sconcat
				("game_engine::sys::DngnGen::_connect_by_extending(): ",
				"`switch (temp_side)`: Eek! `", temp_side, "`"));
			break;
		//--------
		}
	}
}

bool DngnGen::GenInnards::_rt_is_connected(
	const RoomTunnel& some_rt
) const {
	const RoomTunnel& conn_rt
		= engine->dngn_floor().at(_conn_rt_index);
	return (
		(some_rt.gen_side == GEN_SIDE_L
			&& _ls_r2_hit(conn_rt, some_rt))
		|| (some_rt.gen_side == GEN_SIDE_T
			&& _ts_r2_hit(conn_rt, some_rt))
		|| (some_rt.gen_side == GEN_SIDE_R
			&& _rs_r2_hit(conn_rt, some_rt))
		|| (some_rt.gen_side == GEN_SIDE_B
			&& _bs_r2_hit(conn_rt, some_rt))
	);
};
//--------
auto DngnGen::GenInnards::any_intersect_find_all(
	RoomTunnel& to_check_rt, const std::optional<size_t>& index
) -> std::vector<size_t> {
	return _find_all_backend(to_check_rt, index,
		[](const RoomTunnel& to_check_rt, const RoomTunnel& some_item)
		-> bool {
			return some_item.rect.intersect(to_check_rt.rect);
		});
}
auto DngnGen::GenInnards::any_intersect_find_first(
	RoomTunnel& to_check_rt, const std::optional<size_t>& index
) -> std::optional<size_t> {
	//for (size_t k=0; k<engine->dngn_floor().size(); ++k) {
	//	auto& some_item = engine->dngn_floor().at(k);
	//	if (index && (*index == k)) {
	//		continue;
	//	} else if (some_item.rect.intersect(to_check_rt.rect)) {
	//		return &some_item;
	//	}
	//}
	//return nullptr;

	return _find_first_backend(to_check_rt, index,
		[](const RoomTunnel& to_check_rt, const RoomTunnel& some_item)
		-> bool {
			return some_item.rect.intersect(to_check_rt.rect);
		});
}
//--------
auto DngnGen::GenInnards::any_sides_intersect_find_all(
	RoomTunnel& to_check_rt, const std::optional<size_t>& index
) -> std::vector<size_t> {
	return _find_all_backend(to_check_rt, index,
		[](const RoomTunnel& to_check_rt, const RoomTunnel& some_item)
		-> bool {
			return _some_sides_hit(to_check_rt, some_item);
		});
}
auto DngnGen::GenInnards::any_sides_intersect_find_first(
	RoomTunnel& to_check_rt, const std::optional<size_t>& index
) -> std::optional<size_t> {
	//for (size_t k=0; k<engine->dngn_floor().size(); ++k) {
	//	auto& some_item = engine->dngn_floor().at(k);
	//	if (index && (*index == k)) {
	//		continue;
	//	} else if (_some_sides_hit(to_check_rt, some_item)) {
	//		return &some_item;
	//	}
	//}
	//return nullptr;
	return _find_first_backend(to_check_rt, index,
		[](const RoomTunnel& to_check_rt, const RoomTunnel& some_item)
		-> bool {
			return _some_sides_hit(to_check_rt, some_item);
		});
}
//--------
auto DngnGen::GenInnards::any_tunnel_sides_hit_wrongly_find_all(
	RoomTunnel& to_check_rt, const std::optional<size_t>& index
) -> std::vector<size_t> {
	return _find_all_backend(to_check_rt, index,
		[](const RoomTunnel& to_check_rt, const RoomTunnel& some_item)
		-> bool {
			return _tunnel_sides_hit_wrongly(to_check_rt, some_item);
		});
}
auto DngnGen::GenInnards::any_tunnel_sides_hit_wrongly_find_first(
	RoomTunnel& to_check_rt, const std::optional<size_t>& index
) -> std::optional<size_t> {
	//for (size_t k=0; k<engine->dngn_floor().size(); ++k) {
	//	auto& some_item = engine->dngn_floor()._raw_at(k);
	//	if (index && (*index == k)) {
	//		continue;
	//	} else if (_tunnel_sides_hit_wrongly(to_check_rt, some_item)) {
	//		//engine->dbg_log("any_tunnel_sides_hit_wrongly_find_first(): ",
	//		//	"wrong hit found: ",
	//		//	"to_check_rt{", to_check_rt.rect.tl_corner(), " ",
	//		//		to_check_rt.rect.br_corner(), "} ",
	//		//	"engine->dngn_floor()._raw_at(", k, ")",
	//		//		"{", some_item.rect.tl_corner(), " ",
	//		//			some_item.rect.br_corner(), "}",
	//		//		"\n");
	//		//return true;
	//		return &some_item;
	//	}
	//}
	//return nullptr;
	return _find_first_backend(to_check_rt, index,
		[](const RoomTunnel& to_check_rt, const RoomTunnel& some_item)
		-> bool {
			return _tunnel_sides_hit_wrongly(to_check_rt, some_item);
		});
}
//--------
auto DngnGen::GenInnards::_find_all_backend(
	RoomTunnel& to_check_rt,
	const std::optional<size_t>& index,
	const std::function<bool(
		RoomTunnel&, const RoomTunnel&
	)>& test_func
) -> std::vector<size_t> {
	std::vector<size_t> ret;

	//const auto& raw_some_item_set
	//	= engine->dngn_floor().cg_find_others(to_check_rt);
	for (size_t k=0; k<engine->dngn_floor().size(); ++k)
	//for (auto* raw_some_item: raw_some_item_set)
	{
		//const auto& some_item = engine->dngn_floor().at(k);
		//RoomTunnel* some_item = static_cast<RoomTunnel*>(raw_some_item);
		//const size_t k = engine->dngn_floor().rt_to_index_map()
		//	.at(some_item);
		RoomTunnel* some_item = &engine->dngn_floor()._raw_at(k);
		if (index && (*index == k)) {
			continue;
		} else if (test_func(to_check_rt, *some_item)) {
			ret.push_back(k);
		}
	}
	return ret;
}
auto DngnGen::GenInnards::_find_first_backend(
	RoomTunnel& to_check_rt,
	const std::optional<size_t>& index,
	const std::function<bool(
		RoomTunnel&, const RoomTunnel&
	)>& test_func
) -> std::optional<size_t> {
	//--------
	//engine->dngn_floor()._coll_grid.clear();
	//for (size_t k=0; k<engine->dngn_floor().size(); ++k) {
	//	engine->dngn_floor()._coll_grid.insert(&engine->dngn_floor()
	//		._raw_at(k));
	//}
	//--------
	//const auto& raw_some_item_uset
	//	= engine->dngn_floor()._cg_find_others(to_check_rt);
	//const auto& raw_some_item_uset
	//	= engine->dngn_floor()._coll_grid.find_others(&to_check_rt);
	for (size_t k=0; k<engine->dngn_floor().size(); ++k)
	//for (auto* raw_some_item: raw_some_item_uset)
	{
		//const auto& some_item = engine->dngn_floor().at(k);
		const RoomTunnel& some_item = engine->dngn_floor().at(k);
		//RoomTunnel* some_item = static_cast<RoomTunnel*>(raw_some_item);
		//const size_t k = engine->dngn_floor().rt_to_index_umap()
		//	.at(some_item);
		if (index && (*index == k)) {
			continue;
		} else if (test_func(to_check_rt, some_item)) {
			return k;
		}
	}
	return std::nullopt;
	//--------
}
void DngnGen::GenInnards::finalize() const {
	//if (do_clear) {
	//	//for (i=0; i<engine->dngn_floor().size(); ++i)
	//	for (auto& some_rt: engine->dngn_floor()) {
	//		//auto& some_rt = engine->dngn_floor().at(i);
	//		//engine->dngn_floor().at(i).door_pt_uset.clear();
	//		some_rt.conn_index_uset.clear();
	//		some_rt.door_pt_uset.clear();
	//	}
	//}
	for (
		size_t rt_index=0;
		rt_index<engine->dngn_floor().size();
		++rt_index
	) {
		//if (item_index == rt_index) {
		//	continue;
		//}
		auto
			& rt = engine->dngn_floor()._raw_at(rt_index);
			//& item = engine->dngn_floor()._raw_at(item_index);
		//auto& rt_xdata = engine->dngn_floor().xdata_at(rt_index);
		//--------
		//const auto& raw_item_uset = engine->dngn_floor().cg_neighbors
		//	(rt_index);
		//for (auto* raw_item: raw_item_uset)
		for (
			size_t item_index=0;
			item_index<engine->dngn_floor().size();
			++item_index
		) {
			if (item_index == rt_index) {
				continue;
			}
			//RoomTunnel* item = static_cast<RoomTunnel*>(raw_item);
			RoomTunnel* item = &engine->dngn_floor()._raw_at(item_index);
			//auto& item_xdata = item->xdata;
			//const size_t item_index
			//	= engine->dngn_floor().rt_to_index_umap().at(item);
			//--------
			// Old code to set `conn_index_uset`. See `_do_push_back` for
			// the new code to do this.
			//// We only need to check intersection with one of the two
			//// `RoomTunnel`'s sides
			//if (
			//	_ls_r2_hit(rt, *item) || _ts_r2_hit(rt, *item)
			//	|| _rs_r2_hit(rt, *item) || _bs_r2_hit(rt, *item)
			//	//|| _ls_r2_hit(*item, rt) || _ts_r2_hit(*item, rt)
			//	//|| _rs_r2_hit(*item, rt) || _bs_r2_hit(*item, rt)
			//) {
			//	rt.conn_index_uset.insert(item_index);
			//	item->conn_index_uset.insert(rt_index);
			//}
			//auto add_to_conn_index_uset = [](
			//	RoomTunnel& rt_0, size_t rt_0_index,
			//	RoomTunnel& rt_1, size_t rt_1_index
			//) -> void {
			//	if (rt_0.is_horiz_tunnel()) {
			//	} else if (rt_0.is_vert_tunnel()) {
			//	} else { // if (rt_0.is_room())
			//	}
			//};
			//--------
			// insert doors
			auto maybe_insert_door = [](
				RoomTunnel& some_rt, const IntVec2& some_corner
			) -> void {
				if (!some_rt.alt_terrain_umap.contains(some_corner)) {
					//some_rt.door_pt_uset.insert(some_corner);
					//some_rt.door_umap.insert({some_corner, std::nullopt});
					some_rt.alt_terrain_umap.insert
						({some_corner, BgTile::Door});
				}
			};
			if (rt.is_room() && item->is_tunnel()) {
				if (item->is_horiz_tunnel()) {
					if (_ls_r2_hit(*item, rt)) {
						maybe_insert_door(*item, item->rect.tl_corner());
					}
					if (_rs_r2_hit(*item, rt)) {
						maybe_insert_door(*item, item->rect.tr_corner());
					}
				} else { // if (item->is_vert_tunnel())
					if (_ts_r2_hit(*item, rt)) {
						maybe_insert_door(*item, item->rect.tl_corner());
					}
					if (_bs_r2_hit(*item, rt)) {
						maybe_insert_door(*item, item->rect.bl_corner());
					}
				}
			} else if (rt.is_tunnel() && item->is_room()) {
				if (rt.is_horiz_tunnel()) {
					if (_ls_r2_hit(rt, *item)) {
						maybe_insert_door(rt, rt.rect.tl_corner());
					}
					if (_rs_r2_hit(rt, *item)) {
						maybe_insert_door(rt, rt.rect.tr_corner());
					}
				} else { // if (rt.is_vert_tunnel())
					if (_ts_r2_hit(rt, *item)) {
						maybe_insert_door(rt, rt.rect.tl_corner());
					}
					if (_bs_r2_hit(rt, *item)) {
						maybe_insert_door(rt, rt.rect.bl_corner());
					}
				}
			}
		}
	}
	//for (size_t i=0; i<engine->dngn_floor().size(); ++i) {
	//	const auto& some_rt = engine->dngn_floor().at(i);
	//	if (some_rt.door_pt_uset.size() > 0) {
	//		engine->dbg_log("door pts ", i, " [");
	//		for (const auto& door_pt: some_rt.door_pt_uset) {
	//			engine->dbg_log(door_pt, " ");
	//		}
	//		engine->dbg_log("]\n");
	//	}
	//}
	_remove_dead_end_tunnels();
	_insert_exits();
	_insert_alt_terrain();
	_insert_items_and_locked_doors();
}
void DngnGen::GenInnards::_remove_dead_end_tunnels() const {
	for (;;) {
		bool
			did_rm = false,
			erase_ret_inv = true;
		for (
			size_t item_index=0;
			item_index<engine->dngn_floor().size();
			++item_index
		) {
			did_rm = false;
			erase_ret_inv = true;
			auto& item = engine->dngn_floor()._raw_at(item_index);
			if (item.is_tunnel() && item.conn_index_uset.size() <= 1) {
				if (
					GEN_YN_RM_DE_TUNNELS_DO_RM.rng_val_is_yes
						(GEN_YN_RM_DE_TUNNELS_DO_RM.gen())
				) {
					//engine->dbg_log("_remove_dead_end_tunnels(): ",
					//	"going to remove: ",
					//	"item{", item.rect.tl_corner(), " ",
					//		item.rect.br_corner(), "} ",
					//	i32(item_index), "\n");
					if (item.conn_index_uset.size() == 0) {
						throw std::runtime_error(sconcat
							("game_engine::lvgen_etc::DngnGen",
							"::GenInnards::_remove_dead_end_tunnels(): ",
							"Eek! ", item_index, "; ",
							item.rect.tl_corner(), " ",
							item.rect.br_corner()));
					} else {
						did_rm = true;
						erase_ret_inv
							= !engine->dngn_floor().erase_tunnel_during_gen
								(item_index);
						break;
					}
				}
			}
		}
		if (
			erase_ret_inv || !did_rm
			//|| GEN_YN_RM_DE_TUNNELS_FINISH_IF.rng_val_is_yes
			//	(GEN_YN_RM_DE_TUNNELS_FINISH_IF.gen())
		) {
			break;
		}
	}
}
void DngnGen::GenInnards::_insert_exits() const {
	auto inner_insert = [this](bool up) -> void {
		//for (i32 tries=0; tries<GEN_EXITS_LIM_TRIES; ++tries)
		for (;;) {
			RoomTunnel& rt = engine->dngn_floor()._raw_at
				(engine->layout_rand_lt_bound<i32>
					(engine->dngn_floor().size()));

			if (rt.is_room()) {
				const IntVec2 stairs_pos
					= engine->layout_rand_vec2(rt.rect);

				bool did_intersect = false;

				for (const auto& conn_index: rt.conn_index_uset) {
					const RoomTunnel& conn_rt
						= engine->dngn_floor().at(conn_index);
					const IntRect2& rect = conn_rt.rect;
					if (
						(
							conn_rt.is_horiz_tunnel()
							&& (
								(rect.tl_corner() + LEFT_OFFSET
									== stairs_pos)
								|| (rect.tr_corner() + RIGHT_OFFSET
									== stairs_pos)
							)
						) || (
							conn_rt.is_vert_tunnel()
							&& (
								(rect.tl_corner() + TOP_OFFSET
									== stairs_pos)
								|| (rect.bl_corner() + BOTTOM_OFFSET
									== stairs_pos)
							)
						)
					) {
						did_intersect = true;
						break;
					}
				}
				if (did_intersect) {
					continue;
				}

				auto& ustairs_pos = engine->dngn_floor().ustairs_pos;
				auto& dstairs_pos = engine->dngn_floor().dstairs_pos;
				if (up) {
					if (dstairs_pos && *dstairs_pos == stairs_pos) {
						continue;
					} else {
						ustairs_pos = stairs_pos;
					}
				} else { // if (!up)
					if (ustairs_pos && *ustairs_pos == stairs_pos) {
						continue;
					} else {
						dstairs_pos = stairs_pos;
					}
				}
				return;
			}
		}
	};
	inner_insert(true);

	if (engine->floor() != engine->LAST_FLOOR) {
		//bool did_insert
		//do {
		//	did_insert = false;
		//} while (!did_insert);
		inner_insert(false);
	}
}
void DngnGen::GenInnards::_insert_alt_terrain() const {
	const auto
		& allowed_alt_terrain_darr = ALLOWED_ALT_TERRAIN_DA2D
			.at(engine->level_index());

	const IntRect2
		//floor_r2
		//	= PFIELD_PHYS_RECT2,
		//	//= r2_build_in_pfield({1, 1}, {9, 4}),
		biome_mballs_bounds_r2
			//= PFIELD_PHYS_NO_BRDR_RECT2;
			= engine->layout_rand_r2_in_pfnb
				(GEN_BIOME_MBALL_GEN_MIN_SIZE_2D,
				GEN_BIOME_MBALL_GEN_MAX_SIZE_2D);
	//engine->dbg_log
	//	("DngnGen::GenInnards::_insert_alt_terrain():\n",
	//	"PFIELD_PHYS_RECT2: ",
	//		PFIELD_PHYS_RECT2, " ",
	//		"{", "tl", PFIELD_PHYS_RECT2.tl_corner(), " ",
	//		"br", PFIELD_PHYS_RECT2.br_corner(), "}", "\n",
	//	"PFIELD_PHYS_NO_BRDR_RECT2: ",
	//		PFIELD_PHYS_NO_BRDR_RECT2, " ",
	//		"{", "tl", PFIELD_PHYS_NO_BRDR_RECT2.tl_corner(), " ",
	//		"br", PFIELD_PHYS_NO_BRDR_RECT2.br_corner(), "}", "\n",
	//	"biome_mballs_bounds_r2: ",
	//		biome_mballs_bounds_r2, " ",
	//		"{", "tl", biome_mballs_bounds_r2.tl_corner(), " ",
	//		"br", biome_mballs_bounds_r2.br_corner(), "}", "\n");
	//engine->dbg_log(biome_mballs_bounds_r2, "\n");

	MetaballGen
		//biome_mballs(floor_r2.size_2d);
		biome_mballs(biome_mballs_bounds_r2.size_2d);

	// old code, do not uncomment
	//for (
	//	size_t item_index=0;
	//	item_index<engine->dngn_floor().size();
	//	++item_index
	//) {
	//	const auto& item = engine->dngn_floor()._raw_at(item_index);
	//	//if (
	//	//	(item.is_tunnel()
	//	//		&& (gen_biome_mbins_type == GEN_BIOME_MBINS_TYPE_TUNNEL
	//	//			|| gen_biome_mbins_type == GEN_BIOME_MBINS_TYPE_BOTH))
	//	//	|| (item.is_room()
	//	//		&& (gen_biome_mbins_type == GEN_BIOME_MBINS_TYPE_ROOM
	//	//			|| gen_biome_mbins_type == GEN_BIOME_MBINS_TYPE_BOTH))
	//	//) {
	//	//if (item.is_room()) {
	//		biome_mballs.add(item.rect.cntr_pos(),
	//			FltVec2(item.rect.size_2d));
	//	//}
	//	//}
	//}

	if (std::vector<IntRect2> biome_r2_darr; true) {
		const i32
			num_biome_r2s = engine->layout_rand<i32>
				(GEN_BIOME_MBALL_MIN_AMOUNT, GEN_BIOME_MBALL_MAX_AMOUNT);
		while (i32(biome_r2_darr.size()) < num_biome_r2s) {
			const IntRect2
				//to_push = engine->layout_rand_r2_in_pfnb
				//	(GEN_BIOME_MBALL_MIN_SIZE_2D,
				//	GEN_BIOME_MBALL_MAX_SIZE_2D);
				to_push = engine->layout_rand_r2
					(biome_mballs_bounds_r2,
					GEN_BIOME_MBALL_MIN_SIZE_2D,
					GEN_BIOME_MBALL_MAX_SIZE_2D);
			//if (r2_fits_in_pfnb(IntRect2(to_push)))
			{
				biome_r2_darr.push_back(to_push);
			}
		}
		for (const auto& biome_r2: biome_r2_darr) {
			const FltRect2 temp_biome_r2
				{.pos=FltVec2(biome_r2.pos),
				.size_2d=FltVec2(biome_r2.size_2d)};
			biome_mballs.add
				(temp_biome_r2.cntr_pos(), temp_biome_r2.size_2d);
			//biome_mballs.add
			//	(temp_biome_r2.cntr_pos(), temp_biome_r2.half_size());
		}
	}

	// old code, do not uncomment
	//const float
	//	//BIOME_THRESH_0 = engine->layout_rand<i32>
	//	//	(MIN_GEN_BIOME_THRESH_0 * GEN_BIOME_THRESH_MM_SCALE,
	//	//	MAX_GEN_BIOME_THRESH_0 * GEN_BIOME_THRESH_MM_SCALE)
	//	//	/ GEN_BIOME_THRESH_MM_SCALE,
	//	//BIOME_THRESH_1 = engine->layout_rand<i32>
	//	//	(MIN_GEN_BIOME_THRESH_1 * GEN_BIOME_THRESH_MM_SCALE,
	//	//	MAX_GEN_BIOME_THRESH_1 * GEN_BIOME_THRESH_MM_SCALE)
	//	//	/ GEN_BIOME_THRESH_MM_SCALE;
	//	//BIOME_THRESH_0
	//	//	//= 0.050f,
	//	//	= 0.0f,
	//	//BIOME_THRESH_1
	//	BIOME_THRESH
	//		//= 0.15f;
	//		= 0.1f;
	//		//= 10;
	//		//= 5;
	const float
		biome_thresh
			= float(engine->layout_rand<i32>
			(MIN_GEN_BIOME_THRESH_0 * GEN_BIOME_THRESH_MM_SCALE,
			MAX_GEN_BIOME_THRESH_0 * GEN_BIOME_THRESH_MM_SCALE))
			/ GEN_BIOME_THRESH_MM_SCALE;
			//= 10.0f;
			//= 5.0f;
	//engine->dbg_log("biome_thresh: ", biome_thresh, "\n");

	const auto& biome_gen
		//= biome_mballs.gen(0.10f, 0.3f);
		//= biome_mballs.gen(0.01f, 0.3f);
		//= biome_mballs.gen(0.00f, 0.5f);
		//= biome_mballs.gen(BIOME_THRESH_0, BIOME_THRESH_1);
		//= biome_mballs.gen(BIOME_THRESH);
		//= biome_mballs.gen();
		= biome_mballs.gen(biome_thresh);
	// old code, do not uncomment
	//engine->dbg_log("Debug: Generated metaballs\n");
	//for (size_t j=0; j<biome_gen.size(); ++j) {
	//	const auto& row = biome_gen.at(j);
	//	engine->dbg_log(j, ": ");
	//	for (size_t i=0; i<row.size(); ++i) {
	//		//engine->dbg_log(i, "{", row.at(i), "}");
	//		engine->dbg_log(row.at(i));
	//		if (i + 1u < row.size()) {
	//			engine->dbg_log(" ");
	//		}
	//	}
	//	engine->dbg_log("\n");
	//}

	std::vector<std::vector<std::pair<bool, BgTile>>> biome_bg_tiles
		= std::vector<std::vector<std::pair<bool, BgTile>>>
		(biome_gen.size(),
			std::vector<std::pair<bool, BgTile>>
				(biome_gen.front().size(),
					{false, ALT_TERRAIN_NONE}));
	for (i32 j=0; j<i32(biome_gen.size()); ++j) {
		const auto& row = biome_gen.at(j);
		for (i32 i=0; i<i32(row.size()); ++i) {
			const auto& item = row.at(i);
			biome_bg_tiles.at(j).at(i).first
				= !item;
				//= item;
			//if (!item) {
			//	const auto& neighbors
			//		= engine->dngn_floor().cg_neighbors(IntVec2{i, j});
			//	for (auto& neighbor: neighbors) {
			//		if (neighbor->bbox().intersect(IntVec2{i, j})) {
			//			RoomTunnel& rt = *static_cast<RoomTunnel*>(neighbor);
			//			rt.alt_terrain_umap.insert
			//				({IntVec2{i, j}, std::nullopt});
			//		}
			//	}
			//}
		}
	}
	// old code, do not uncomment
	//for (size_t j=0; j<biome_bg_tiles.size(); ++j) {
	//	const auto& row = biome_bg_tiles.at(j);
	//	for (size_t i=0; i<row.size(); ++i) {
	//		const auto& item = row.at(i);
	//		printout(item.first ? "~" : ".");
	//	}
	//	printout("\n");
	//}

	// move/change this code
	// Breadth-first search
	{
		IntVec2Uset explored_uset;
		IntVec2 pos;
		for (pos.y=0; pos.y<i32(biome_bg_tiles.size()); ++pos.y) {
			auto& row = biome_bg_tiles.at(pos.y);
			for (pos.x=0; pos.x<i32(row.size()); ++pos.x) {
				const BgTile rng_bg_tile=allowed_alt_terrain_darr
					.at(engine->layout_rand<i32>
						(0, allowed_alt_terrain_darr.size() - 1));
				// `explored_uset` contains all positions that have been
				// visited by the calls to `bfs_fill`
				if (!explored_uset.contains(pos)) {
					bfs_fill
						(explored_uset, pos,
						[&](const IntVec2& some_pos) -> bool {
							const IntVec2
								temp_pos = some_pos
									- biome_mballs_bounds_r2.tl_corner();
							return PFIELD_PHYS_NO_BRDR_RECT2
								.intersect(some_pos)
								&& biome_bg_tiles
									.at(temp_pos.y).at(temp_pos.x).first;
						},
						[&](const IntVec2& some_pos) -> void {
							const IntVec2
								temp_pos = some_pos
									- biome_mballs_bounds_r2.tl_corner();
							auto& bg_tile
								= biome_bg_tiles
									.at(temp_pos.y).at(temp_pos.x);
							if (bg_tile.first) {
								bg_tile.second = rng_bg_tile;
							}
						});
				}
			}
		}
	}
	// move/change this code
	{
		const auto& ustairs_pos = engine->dngn_floor().ustairs_pos;
		const auto& dstairs_pos = engine->dngn_floor().dstairs_pos;
		if (ustairs_pos && dstairs_pos) {
			DijkstraMapGen dmap_gen;
			dmap_gen.add(*dstairs_pos);

			// This is just for checking that the dmap generates properly
			// no matter the values of the goals
			//dmap_gen.add(ustairs_pos, -4.5f);

			const auto& dmap = dmap_gen.gen_basic
				(engine->dngn_floor(), BASIC_NO_PASS_BG_TILE_USET);
			const auto& path = dmap.make_path(*ustairs_pos);
			//engine->dbg_log("Filling `path`\n");
			path->fill
				([&](const IntVec2& phys_pos) -> bool {
					//auto& fl = engine->dngn_floor();
					// This assumes that the `std::optional`s returned by
					// these functions definitely contain values.
					//const auto& bg_tile = *fl.phys_bg_tile_at(pos);
					const IntVec2
						pos = phys_pos - dmap.BOUNDS_R2.tl_corner();
					auto& bg_tile = biome_bg_tiles.at(pos.y).at(pos.x);
					//const size_t rt_index = *fl.phys_pos_to_rt_index(pos);
					//engine->dbg_log(pos, ": ", bg_tile_str_map_at(bg_tile),
					//	"\n");

					if (
						bg_tile.first
						&& BASIC_NO_PASS_BG_TILE_USET.contains
							(bg_tile.second)
					) {
						//auto& rt = fl._raw_at(rt_index);
						//rt.alt_terrain_umap.erase(pos);
						bg_tile.first = false;
					}
					return true;
				});
		}
	}

	// move/change this code
	// This displays the biome `BgTile`s via `engine->dbg_log()`
	//engine->dbg_log("Debug: generated biome `BgTile`s\n");
	//for (size_t j=0; j<biome_bg_tiles.size(); ++j) {
	//	auto& row = biome_bg_tiles.at(j);
	//	if (j < 10u) {
	//		engine->dbg_log(0);
	//	}
	//	engine->dbg_log(j, ": ");
	//	for (size_t i=0; i<row.size(); ++i) {
	//		const auto& bg_tile = row.at(i);
	//		//if (bg_tile == ALT_TERRAIN_NONE)
	//		if (!bg_tile.first) {
	//			engine->dbg_log(char(comp::drawable_data_umap().at
	//				(bg_tile_str_map_at(BgTile::RoomFloor)).c));
	//		} else { // if (bg_tile.first)
	//			const auto& draw_data
	//				= comp::drawable_data_umap().at
	//					(bg_tile_str_map_at(bg_tile.second));
	//			engine->dbg_log(char(draw_data.c));
	//		}
	//	}
	//	//if (j + 1u < biome_bg_tiles.size()) {
	//		engine->dbg_log("\n");
	//	//}
	//}

	// move/change this code
	//for (auto& item: engine->dngn_floor())
	for (
		size_t item_index=0;
		item_index<engine->dngn_floor().size();
		++item_index
	) {
		auto& item = engine->dngn_floor()._raw_at(item_index);
		//if (do_clear) {
		//	item.alt_terrain_umap.clear();
		//}

		//if (item.is_tunnel()) {
		//	continue;
		//}

		// Note that `RoomTunnel`s are already generated with their borders
		IntVec2
			pos;
		for (
			pos.y=item.rect.top_y()
				//+ TOP_OFFSET.y
				;
			pos.y<=item.rect.bottom_y()
				//+ BOTTOM_OFFSET.y
				;
			++pos.y
		) {
			for (
				pos.x=item.rect.left_x()
					//+ LEFT_OFFSET.x
					;
				pos.x<=item.rect.right_x()
					//+ RIGHT_OFFSET.x
					;
				++pos.x
			) {
				//if (!biome_mballs_bounds_r2.intersect(pos)) {
				//	engine->dbg_log
				//		("DngnGen debug: _insert_alt_terrain(): ",
				//		"biome_mballs_bounds_r2",
				//			"{", biome_mballs_bounds_r2.tl_corner(), " ",
				//			biome_mballs_bounds_r2.br_corner(), "}\n",
				//		"pos", pos, "\n");
				//	continue;
				//}

				const IntVec2
					temp_pos = pos - biome_mballs_bounds_r2.pos;

				const auto
					& bg_tile = biome_bg_tiles.at(temp_pos.y)
						.at(temp_pos.x);

				if (!bg_tile.first) {
					continue;
				}

				// TODO: incorporate `DijkstraMapGen` and connections
				// between stairs
				// NOTE: now the above ^ is done
				//if (item.is_tunnel()) {
				//	if (!BASIC_UNSAFE_BG_TILE_USET.contains
				//		(bg_tile.second)) {
				//		item.alt_terrain_umap[pos] = bg_tile.second;
				//	}
				//} else { // if (item.is_room())
				//	if (
				//		!BASIC_UNSAFE_BG_TILE_USET.contains
				//			(bg_tile.second)
				//		|| (!item.pos_in_border(pos)
				//			&& !item.pos_in_internal_border(pos))
				//	) {
				//		item.alt_terrain_umap[pos] = bg_tile.second;
				//	}
				//}
				if (
					item.is_room()
					|| !BASIC_NO_PASS_BG_TILE_USET.contains(bg_tile.second)
				) {
					item.alt_terrain_umap.insert
					({
						//--------
						pos
							// (old code) convert coordinate systems
							//+ TL_CORNER_OFFSET
							// oops, `biome_mballs_bounds_r2` was actually
							// supposed to be inside of the
							// no-internal-border area of the playfield.
							,
						//--------
						bg_tile.second
						//--------
					});
				}
			}
		}
	}
}
void DngnGen::GenInnards::_insert_items_and_locked_doors() const {
}
//void DngnGen::GenInnards::_fill_in_alt_terrain() const {
//}
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
