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

#include "dungeon_gen_class.hpp"
#include "metaball_gen_class.hpp"
#include "dijkstra_map_gen_class.hpp"
#include "bfs_funcs.hpp"
#include "../engine_class.hpp"
#include "../comp/drawable_data_umap.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
i32 DungeonGen::GenNext::gen() const {
	return engine->layout_rand<i32>(full_min(), full_max());
}
i32 DungeonGen::GenYesNo::gen() const {
	return engine->layout_rand<i32>(full_min(), full_max());
}
//--------
const std::vector<std::vector<BgTile>>
	DungeonGen::ALLOWED_ALT_TERRAIN_V2D({
		// Level 1 (index 0)
		build_bg_tile_vec
			(//SizeAndBgTile(20, ALT_TERRAIN_NONE),
			//SizeAndBgTile(5, ALT_TERRAIN_NONE),
			//SizeAndBgTile(1, ALT_TERRAIN_NONE),
			//SizeAndBgTile(2, BgTile::Water),
			SizeAndBgTile(2, BgTile::Water),
			BgTile::Spikes
			//SizeAndBgTile(3, BgTile::Lava)
			),

		// Level 2 (index 1)
		build_bg_tile_vec
			(
			//SizeAndBgTile(6, ALT_TERRAIN_NONE),
			//SizeAndBgTile(2, ALT_TERRAIN_NONE),
			SizeAndBgTile(3, BgTile::Water),
			SizeAndBgTile(2, BgTile::Spikes),
			BgTile::Pit),

		// Level 3 (index 2)
		build_bg_tile_vec
			(
			//SizeAndBgTile(5, ALT_TERRAIN_NONE),
			//SizeAndBgTile(3, ALT_TERRAIN_NONE),
			SizeAndBgTile(2, BgTile::Water),
			//BgTile::Lava,
			SizeAndBgTile(2, BgTile::Spikes),
			BgTile::Pit),

		// Level 4 (index 3)
		build_bg_tile_vec
			(
			//SizeAndBgTile(1, ALT_TERRAIN_NONE),
			BgTile::Lava,
			SizeAndBgTile(2, BgTile::Spikes),
			BgTile::Pit
			),

		// Level 5 (index 4)
		build_bg_tile_vec
			(
			//SizeAndBgTile(1, ALT_TERRAIN_NONE),
			BgTile::Lava,
			BgTile::Spikes
			),
	});
void DungeonGen::clear(
	//ecs::Engine* ecs_engine
) {
	//auto* floor_layout
	//	= ecs_engine->casted_comp_at<FloorLayout>(*_dungeon_gen_id);
	_floor_layout.clear();
	//floor_layout->clear(engine->calc_layout_noise_add_amount());
	//_stop_gen_early = false;
	_attempted_num_rp = engine->layout_rand<i32>
		(i32(MIN_NUM_ROOM_PATHS), i32(MAX_NUM_ROOM_PATHS));
	_stop_gen_early = false;
	_done_generating = false;
}
void DungeonGen::gen_curr_floor() {

	//if (floor_layout->size() == 0) {
	//	engine->log("Debug: starting dungeon generation.\n");
	//}
	while (!_done_generating) {
		GenInnards innards(
			this
			//ecs_engine,
			//floor_layout
		);
		innards.gen_single_rp();
		if (_done_generating) {
			innards.finalize(
				//true
			);
			//innards._insert_alt_terrain(
			//	//true
			//);
		}
	}
	//else {
	//	engine->log("Debug: We're already done generating\n");
	//}
}
//void DungeonGen::_connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
//	FloorLayout* floor_layout) {
//}
bool DungeonGen::GenInnards::gen_single_rp() {
	//--------
	const bool old_done_generating = _self->_done_generating;
	//--------
	if (_self->floor_layout().size() == 0) {
		//_self->_attempted_num_rp = engine->layout_rand<i32>
		//	(i32(MIN_NUM_ROOM_PATHS), i32(MAX_NUM_ROOM_PATHS));
		//_self->_stop_gen_early = false;
		//_self->_done_generating = false;
		_self->clear(
			//_ecs_engine
		);

		// We always generate a room in this case.
		//for (i32 tries=0; tries<GEN_RP_LIM_TRIES; ++tries)
		// Force there to be at least one room
		//for (;;) {
			RoomPath to_push_rp;
			//--------
			//engine->log("testificate 2\n");
			//--------
			//to_push_rp.rect.pos.x = engine->layout_rand<i32>
			//	(PFIELD_PHYS_RECT2.left_x(),
			//	PFIELD_PHYS_RECT2.right_x() - ROOM_MIN_SIZE_2D.x - 1);
			//to_push_rp.rect.pos.y = engine->layout_rand<i32>
			//	(PFIELD_PHYS_RECT2.top_y(),
			//	PFIELD_PHYS_RECT2.bottom_y() - ROOM_MIN_SIZE_2D.y - 1);

			//to_push_rp.rect.size_2d.x = engine->layout_rand<i32>
			//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
			//to_push_rp.rect.size_2d.y = engine->layout_rand<i32>
			//	(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y);
			to_push_rp.rect = engine->layout_rand_r2_in_pfnb
				(ROOM_MIN_SIZE_2D, ROOM_MAX_SIZE_2D);
			//--------
			//if (to_push_rp.fits_in_pfnb()) {
			//	_do_push_back(std::move(to_push_rp));
			//	break;
			//}
			_do_push_back(std::move(to_push_rp));
			//break;
			//--------
		//}
	}
	//else if (_self->floor_layout().size() < MAX_NUM_ROOM_PATHS)
	else if (
		i32(_self->floor_layout().size()) < _self->_attempted_num_rp
	) {
		//RoomPath to_push_rp;
		//if (_self->floor_layout().size() < MIN_NUM_ROOM_PATHS) {
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
				if (_self->floor_layout().size() < MIN_NUM_ROOM_PATHS) {
					engine->log
						("Debug: game_engine::sys::gen_single_rp(): ",
						"Redoing generation\n");
					_self->clear(
						//_ecs_engine
					);
				} else {
					// If we failed to find a room that fits in the
					// playfield, we stop floor generation early, and don't
					// try any more for this floor.  This is to prevent
					// infinite loops in the dungeon generation.
					engine->log
						("Debug: game_engine::sys::gen_single_rp(): ",
						"stopping room generation early: ",
						_self->floor_layout().size(), " ",
						_self->_attempted_num_rp, "\n");
				}
			}
			//else {
			//}
		//}
	}
	_self->_done_generating
		= _self->_stop_gen_early
			|| i32(_self->floor_layout().size())
				>= _self->_attempted_num_rp;
	if (!old_done_generating && _self->_done_generating) {
		engine->log
			("Just finished generating the dungeon's basic shape.\n");
	}

	return _self->_done_generating;
}
auto DungeonGen::GenInnards::_inner_gen_post_first()
-> std::optional<RoomPath> {
	//--------
	//RoomPath _temp_to_push_rp;

	if (auto temp=_gen_initial_rp(); temp) {
		_temp_to_push_rp = std::move(*temp);
	} else {
		return std::nullopt;
	}
	//--------
	//const IntRect2
	//	ORIG_TO_PUSH_RECT = _temp_to_push_rp.rect;
	//const bool
	//	was_horiz_path = FloorLayout::r2_is_horiz_path(ORIG_TO_PUSH_RECT),
	//	was_vert_path = FloorLayout::r2_is_vert_path(ORIG_TO_PUSH_RECT);
	//	//was_room = FloorLayout::r2_is_room(ORIG_TO_PUSH_RECT);
	//--------
	//auto _basic_shrink_extra_test_func = [this](
	//	RoomPath& some_rp
	//	//, const std::optional<size_t>& index
	//) -> bool {
	//	const auto& found
	//		= _find_first_backend(
	//			some_rp, std::nullopt,
	//			[](RoomPath& some_rp, const RoomPath& some_item)
	//			-> bool {
	//				//return !(some_item.rect.intersect(some_rp.rect)
	//				//	|| _some_sides_hit(some_rp, some_item)
	//				//	|| !_path_sides_hit_wrongly(some_rp, some_item));
	//				return (some_item.rect.intersect(some_rp.rect)
	//					//&& _some_sides_hit(some_rp, some_item)
	//					|| _path_sides_hit_wrongly(some_rp, some_item)
	//					// Reject pairs of horizontal/vertical paths that
	//					// are too close
	//					|| _parallel_paths_too_close(some_rp, some_item));
	//			});
	//	//if (found) {
	//	//	//engine->log("found{", *found, "}\n");
	//	//	engine->log("found\n");
	//	//} else {
	//	//	engine->log("!found\n");
	//	//}
	//	return (some_rp.fits_in_pfnb()
	//		&& !found
	//		//&& !any_intersect_find_first(some_rp, std::nullopt)
	//		//&& any_sides_intersect_find_first(some_rp, std::nullopt)
	//		//&& !any_path_sides_hit_wrongly_find_first
	//		//	(some_rp, std::nullopt)
	//		&& _rp_is_connected(some_rp)
	//		);
	//};
	// This is a simple algorithm that could be made faster and
	// more complicated, but I figure any platform running this
	// game will have fast enough hardware considering the maximum
	// numbers of rooms/paths.
	if (!_shrink
		(_temp_to_push_rp.is_horiz_path(), _temp_to_push_rp.is_vert_path(),
		_temp_to_push_rp, // std::nullopt,
		[this](RoomPath& some_rp) -> bool {
			return _basic_shrink_extra_test_func(some_rp);
		})) {
		return std::nullopt;
	}


	//if (any_intersect_find_first(_temp_to_push_rp, std::nullopt)) {
	//	//engine->log("Debug: found early intersect!\n");
	//	return std::nullopt;
	//}
	//if (any_path_sides_hit_wrongly_find_first(_temp_to_push_rp, std::nullopt)) {
	//	return std::nullopt;
	//}

	_connect();
	//--------
	//_temp_to_push_rp.conn_index_uset.insert(conn_rp_index);
	//conn_rp.conn_index_uset.insert(_self->floor_layout().size());
	//--------
	//--------
	//engine->log("`gen_type`: ", gen_type, "\n");

	return _temp_to_push_rp;
	//--------
};
void DungeonGen::GenInnards::_do_push_back(RoomPath&& to_push_rp) const {
	//#ifdef DEBUG
	//engine->log("Debug: Generated this `RoomPath`: ",
	//	//to_push_rp.rect, "; ",
	//	"to_push_rp.tl:", to_push_rp.rect.tl_corner(), " ",
	//	"to_push_rp.br:", to_push_rp.rect.br_corner(), "; ",
	//	to_push_rp.is_horiz_path(), " ",
	//	to_push_rp.is_vert_path(), " ",
	//	to_push_rp.is_room(),
	//	"\n");
	//#endif		// DEBUG

	const auto
		to_push_rp_index = _self->floor_layout().size();

	for (
		size_t item_index=0;
		item_index<_self->floor_layout().size();
		++item_index
	) {
		auto& item = _self->_floor_layout._raw_at(item_index);
		if (item.rect.intersect(to_push_rp.rect)) {
			throw std::runtime_error(sconcat
				("game_engine::level_gen_etc::DungeonGen",
				"::GenInnards::_do_push_back(): ",
				"Eek! ",
				"to_push_rp{", to_push_rp.rect.tl_corner(), " ",
					to_push_rp.rect.br_corner(), "} ",
				"item{", item.rect.tl_corner(), " ",
					item.rect.br_corner(), "}\n"));
		} else if (
			_ls_r2_hit(to_push_rp, item)
			|| _ts_r2_hit(to_push_rp, item)
			|| _rs_r2_hit(to_push_rp, item)
			|| _bs_r2_hit(to_push_rp, item)
			//|| _ls_r2_hit(item, to_push_rp)
			//|| _ts_r2_hit(item, to_push_rp)
			//|| _rs_r2_hit(item, to_push_rp)
			//|| _bs_r2_hit(item, to_push_rp)
			//_ls_r2(item).intersect(to_push_rp.rect)
			//|| _ts_r2(item).intersect(to_push_rp.rect)
			//|| _rs_r2(item).intersect(to_push_rp.rect)
			//|| _bs_r2(item).intersect(to_push_rp.rect)
		) {
			to_push_rp.conn_index_uset.insert(i32(item_index));
			item.conn_index_uset.insert
				(i32(to_push_rp_index));
			//engine->log("Connected these RPs: ",
			//	"to_push_rp{", to_push_rp.rect.tl_corner(), " ",
			//		to_push_rp.rect.br_corner(), "} ",
			//		to_push_rp_index, " "
			//	"item{", item.rect.tl_corner(), " ",
			//		item.rect.br_corner(), "} ",
			//		item_index, "\n");
		}
	}

	_self->_floor_layout.push_back(std::move(to_push_rp));

	//to_push_rp = RoomPath();
}
auto DungeonGen::GenInnards::_gen_initial_rp()
-> std::optional<RoomPath> {
	//--------
	RoomPath to_push_rp;

	const i32
		prev_rp_index = _self->floor_layout().size() - 1;
	const RoomPath
		& prev_rp = _self->floor_layout().at(prev_rp_index);
	const i32
		prev_gen_type
			= prev_rp.is_path() ? GEN_TYPE_PATH : GEN_TYPE_ROOM;

	to_push_rp.gen_side = 0;
	_gen_next_type = 0;
	_gen_next_conn_rp_index = 0;
	_gen_type = 0;
	_conn_rp_index = 0;

	//_gen_type = GEN_TYPE_ROOM,
	//to_push_rp.gen_side = engine->layout_rand<i32>
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
	const auto& conn_rp = _self->floor_layout().at(_conn_rp_index);

	if (
		//(conn_rp.is_path() && _gen_type == GEN_TYPE_PATH)
		//|| (conn_rp.is_room() && _gen_type == GEN_TYPE_ROOM)

		//(conn_rp.is_path() && _gen_type == GEN_TYPE_PATH)
		//|| conn_rp.is_room()
		conn_rp.is_path()
	) {
		if (_gen_type == GEN_TYPE_PATH) {
			to_push_rp.gen_side = engine->layout_rand<i32>
				(MIN_GEN_SIDE, MAX_GEN_SIDE);
		} else { // if (_gen_type == GEN_TYPE_ROOM)
			if (conn_rp.is_horiz_path()) {
				to_push_rp.gen_side
					= engine->layout_rand<i32>(0, 1)
					? GEN_SIDE_L
					: GEN_SIDE_R;
			} else { // if (conn_rp.is_vert_path())
				to_push_rp.gen_side
					= engine->layout_rand<i32>(0, 1)
					? GEN_SIDE_T
					: GEN_SIDE_B;
			}
		}
	} else { // if (conn_rp.is_room())
		to_push_rp.gen_side = engine->layout_rand<i32>
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
			//{.x=engine->layout_rand<i32>
			//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x),
			//.y=engine->layout_rand<i32>
			//	(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y)};
			= engine->layout_rand_vec2(ROOM_MIN_SIZE_2D, ROOM_MAX_SIZE_2D);
		//thickness = engine->layout_rand<i32>
		//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
		//length = engine->layout_rand<i32>
		//	(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y);

		if (to_push_rp.gen_side == GEN_SIDE_L
			|| to_push_rp.gen_side == GEN_SIDE_R) {
			thickness = temp_vec2.y;
			length = temp_vec2.x;
		} else // if (
			//to_push_rp.gen_side == GEN_SIDE_T
			//|| to_push_rp.gen_side == GEN_SIDE_B
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

	switch (to_push_rp.gen_side) {
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
			("game_engine::sys::DungeonGen::gen_single_rp(): ",
			"(1st) `switch (to_push_rp.gen_side)`: Eek! `",
			to_push_rp.gen_side,
			"`"));
		break;
	//--------
	}
	return to_push_rp;
}
bool DungeonGen::GenInnards::_shrink(
	bool was_horiz_path, bool was_vert_path,
	RoomPath& some_rp, //const std::optional<size_t>& index,
	const std::function<bool(
		RoomPath&//, const std::optional<size_t>&
	)>& extra_test_func
) {
	//--------
	auto shrink_left_x = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rp.rect.tl_corner() + IntVec2{1, 0},
			some_rp.rect.br_corner(),
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rp.rect = temp_rect;
	};
	auto shrink_top_y = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rp.rect.tl_corner() + IntVec2{0, 1},
			some_rp.rect.br_corner(),
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rp.rect = temp_rect;
	};
	auto shrink_right_x = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rp.rect.tl_corner(),
			some_rp.rect.br_corner() - IntVec2{1, 0},
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rp.rect = temp_rect;
	};
	auto shrink_bottom_y = [&]() -> void {
		const auto temp_rect = IntRect2::build_in_grid_lim
			(some_rp.rect.tl_corner(),
			some_rp.rect.br_corner() - IntVec2{0, 1},
			PFIELD_PHYS_NO_BRDR_RECT2);
		some_rp.rect = temp_rect;
	};
	//--------
	//const RoomPath& conn_rp = _self->_floor_layout.at(_conn_rp_index);
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
			switch (some_rp.gen_side) {
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
			switch (some_rp.gen_side) {
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
			const i32 gen_side = some_rp.gen_side;
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
					("game_engine::sys::DungeonGen::GenInnards",
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
bool DungeonGen::GenInnards::_basic_shrink_extra_test_func(
	RoomPath& some_rp
	//, const std::optional<size_t>& index
) {
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
	//	//engine->log("found{", *found, "}\n");
	//	engine->log("found\n");
	//} else {
	//	engine->log("!found\n");
	//}
	return (some_rp.fits_in_pfnb()
		&& !found
		//&& !any_intersect_find_first(some_rp, std::nullopt)
		//&& any_sides_intersect_find_first(some_rp, std::nullopt)
		//&& !any_path_sides_hit_wrongly_find_first
		//	(some_rp, std::nullopt)
		&& _rp_is_connected(some_rp)
		);
}
void DungeonGen::GenInnards::_connect(
	//bool was_horiz_path, bool was_vert_path,
	//RoomPath& some_rp, //const std::optional<size_t>& index,
	//const std::function<bool(
	//	RoomPath&//, const std::optional<size_t>&
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
		was_horiz_path = _temp_to_push_rp.is_horiz_path(),
		was_vert_path = _temp_to_push_rp.is_vert_path();
	auto attempt_extend = [&](
		const IntVec2& tl_ext, const IntVec2& br_ext
	) -> void {
		RoomPath temp_rp;
		temp_rp.rect = _temp_to_push_rp.rect.build_in_grid_inflated_lim
			(tl_ext, br_ext, PFIELD_PHYS_NO_BRDR_RECT2);
		if (_shrink(
			was_horiz_path, was_vert_path,
			temp_rp,
			[this](RoomPath& some_rp) -> bool {
				return _basic_shrink_extra_test_func(some_rp);
			}
		)) {
			_temp_to_push_rp.rect = temp_rp.rect;
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
				&& !was_vert_path
				&& (_temp_to_push_rp.is_horiz_path()
				|| _temp_to_push_rp.is_room())
			){
				attempt_extend
					(IntVec2{GEN_EXTEND_AMOUNT_TSF, 0}, IntVec2());
			}
			break;
		case GEN_SIDE_T:
			if (
				should_gen_connect()
				&& !was_horiz_path
				&& (_temp_to_push_rp.is_vert_path()
				|| _temp_to_push_rp.is_room())
			) {
				attempt_extend
					(IntVec2{0, GEN_EXTEND_AMOUNT_TSF}, IntVec2());
			}
			break;
		case GEN_SIDE_R:
			if (
				should_gen_connect()
				&& !was_vert_path
				&& (_temp_to_push_rp.is_horiz_path()
				|| _temp_to_push_rp.is_room())
			) {
				attempt_extend
					(IntVec2(), IntVec2{GEN_EXTEND_AMOUNT_TSF, 0});
			}
			break;
		case GEN_SIDE_B:
			if (
				should_gen_connect()
				&& !was_horiz_path
				&& (_temp_to_push_rp.is_vert_path()
				|| _temp_to_push_rp.is_room())
			) {
				attempt_extend
					(IntVec2(), IntVec2{0, GEN_EXTEND_AMOUNT_TSF});
			}
			break;
		default:
			throw std::runtime_error(sconcat
				("game_engine::sys::DungeonGen::_connect(): ",
				"`switch (temp_side)`: Eek! `", temp_side, "`"));
			break;
		//--------
		}
	}
}
//--------
auto DungeonGen::GenInnards::any_intersect_find_all(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::vector<size_t> {
	return _find_all_backend(to_check_rp, index,
		[](const RoomPath& to_check_rp, const RoomPath& some_item)
		-> bool {
			return some_item.rect.intersect(to_check_rp.rect);
		});
}
auto DungeonGen::GenInnards::any_intersect_find_first(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::optional<size_t> {
	//for (size_t k=0; k<_self->floor_layout().size(); ++k) {
	//	auto& some_item = _self->_floor_layout.at(k);
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
auto DungeonGen::GenInnards::any_sides_intersect_find_all(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::vector<size_t> {
	return _find_all_backend(to_check_rp, index,
		[](const RoomPath& to_check_rp, const RoomPath& some_item)
		-> bool {
			return _some_sides_hit(to_check_rp, some_item);
		});
}
auto DungeonGen::GenInnards::any_sides_intersect_find_first(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::optional<size_t> {
	//for (size_t k=0; k<_self->floor_layout().size(); ++k) {
	//	auto& some_item = _self->_floor_layout.at(k);
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
auto DungeonGen::GenInnards::any_path_sides_hit_wrongly_find_all(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::vector<size_t> {
	return _find_all_backend(to_check_rp, index,
		[](const RoomPath& to_check_rp, const RoomPath& some_item)
		-> bool {
			return _path_sides_hit_wrongly(to_check_rp, some_item);
		});
}
auto DungeonGen::GenInnards::any_path_sides_hit_wrongly_find_first(
	RoomPath& to_check_rp, const std::optional<size_t>& index
) -> std::optional<size_t> {
	//for (size_t k=0; k<_self->floor_layout().size(); ++k) {
	//	auto& some_item = _self->_floor_layout._raw_at(k);
	//	if (index && (*index == k)) {
	//		continue;
	//	} else if (_path_sides_hit_wrongly(to_check_rp, some_item)) {
	//		//engine->log("any_path_sides_hit_wrongly_find_first(): ",
	//		//	"wrong hit found: ",
	//		//	"to_check_rp{", to_check_rp.rect.tl_corner(), " ",
	//		//		to_check_rp.rect.br_corner(), "} ",
	//		//	"_self->_floor_layout._raw_at(", k, ")",
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
auto DungeonGen::GenInnards::_find_all_backend(
	RoomPath& to_check_rp,
	const std::optional<size_t>& index,
	const std::function<bool(
		RoomPath&, const RoomPath&
	)>& test_func
) -> std::vector<size_t> {
	std::vector<size_t> ret;

	//const auto& raw_some_item_set
	//	= _self->floor_layout().cg_find_others(to_check_rp);
	for (size_t k=0; k<_self->floor_layout().size(); ++k)
	//for (auto* raw_some_item: raw_some_item_set)
	{
		//const auto& some_item = _self->floor_layout().at(k);
		//RoomPath* some_item = static_cast<RoomPath*>(raw_some_item);
		//const size_t k = _self->floor_layout().rp_to_index_map()
		//	.at(some_item);
		RoomPath* some_item = &_self->_floor_layout._raw_at(k);
		if (index && (*index == k)) {
			continue;
		} else if (test_func(to_check_rp, *some_item)) {
			ret.push_back(k);
		}
	}
	return ret;
}
auto DungeonGen::GenInnards::_find_first_backend(
	RoomPath& to_check_rp,
	const std::optional<size_t>& index,
	const std::function<bool(
		RoomPath&, const RoomPath&
	)>& test_func
) -> std::optional<size_t> {
	//--------
	//_self->_floor_layout._coll_grid.clear();
	//for (size_t k=0; k<_self->floor_layout().size(); ++k) {
	//	_self->_floor_layout._coll_grid.insert(&_self->_floor_layout
	//		._raw_at(k));
	//}
	//--------
	//const auto& raw_some_item_uset
	//	= _self->_floor_layout._cg_find_others(to_check_rp);
	//const auto& raw_some_item_uset
	//	= _self->_floor_layout._coll_grid.find_others(&to_check_rp);
	for (size_t k=0; k<_self->floor_layout().size(); ++k) 
	//for (auto* raw_some_item: raw_some_item_uset)
	{
		//const auto& some_item = _self->floor_layout().at(k);
		const RoomPath& some_item = _self->floor_layout().at(k);
		//RoomPath* some_item = static_cast<RoomPath*>(raw_some_item);
		//const size_t k = _self->floor_layout().rp_to_index_umap()
		//	.at(some_item);
		if (index && (*index == k)) {
			continue;
		} else if (test_func(to_check_rp, some_item)) {
			return k;
		}
	}
	return std::nullopt;
	//--------
}
void DungeonGen::GenInnards::finalize(
	//bool do_clear
) const {
	//if (do_clear) {
	//	//for (i=0; i<_self->floor_layout().size(); ++i)
	//	for (auto& some_rp: *_self->_floor_layout) {
	//		//auto& some_rp = _self->_floor_layout.at(i);
	//		//_self->_floor_layout.at(i).door_pt_uset.clear();
	//		some_rp.conn_index_uset.clear();
	//		some_rp.door_pt_uset.clear();
	//	}
	//}
	for (
		size_t rp_index=0;
		rp_index<_self->floor_layout().size();
		++rp_index
	) {
		//if (item_index == rp_index) {
		//	continue;
		//}
		auto
			& rp = _self->_floor_layout._raw_at(rp_index);
			//& item = _self->_floor_layout._raw_at(item_index);
		//auto& rp_xdata = _self->_floor_layout.xdata_at(rp_index);
		//--------
		//const auto& raw_item_uset = _self->_floor_layout.cg_neighbors
		//	(rp_index);
		//for (auto* raw_item: raw_item_uset)
		for (
			size_t item_index=0;
			item_index<_self->floor_layout().size();
			++item_index
		) {
			if (item_index == rp_index) {
				continue;
			}
			//RoomPath* item = static_cast<RoomPath*>(raw_item);
			RoomPath* item = &_self->_floor_layout._raw_at(item_index);
			//auto& item_xdata = item->xdata;
			//const size_t item_index
			//	= _self->_floor_layout.rp_to_index_umap().at(item);
			//--------
			// set `conn_index_uset`
			//// We only need to check intersection with one of the two
			//// `RoomPath`'s sides
			//if (
			//	_ls_r2_hit(rp, *item) || _ts_r2_hit(rp, *item)
			//	|| _rs_r2_hit(rp, *item) || _bs_r2_hit(rp, *item)
			//	//|| _ls_r2_hit(*item, rp) || _ts_r2_hit(*item, rp)
			//	//|| _rs_r2_hit(*item, rp) || _bs_r2_hit(*item, rp)
			//) {
			//	rp.conn_index_uset.insert(item_index);
			//	item->conn_index_uset.insert(rp_index);
			//}
			//auto add_to_conn_index_uset = [](
			//	RoomPath& rp_0, size_t rp_0_index,
			//	RoomPath& rp_1, size_t rp_1_index
			//) -> void {
			//	if (rp_0.is_horiz_path()) {
			//	} else if (rp_0.is_vert_path()) {
			//	} else { // if (rp_0.is_room())
			//	}
			//};
			//--------
			// insert doors
			auto maybe_insert_door = [](
				RoomPath& some_rp, const IntVec2& some_corner
			) -> void {
				if (!some_rp.alt_terrain_umap.contains(some_corner)) {
					some_rp.door_pt_uset.insert(some_corner);
				}
			};
			if (rp.is_room() && item->is_path()) {
				if (item->is_horiz_path()) {
					if (_ls_r2_hit(*item, rp)) {
						maybe_insert_door(*item, item->rect.tl_corner());
					}
					if (_rs_r2_hit(*item, rp)) {
						maybe_insert_door(*item, item->rect.tr_corner());
					}
				} else { // if (item->is_vert_path())
					if (_ts_r2_hit(*item, rp)) {
						maybe_insert_door(*item, item->rect.tl_corner());
					}
					if (_bs_r2_hit(*item, rp)) {
						maybe_insert_door(*item, item->rect.bl_corner());
					}
				}
			} else if (rp.is_path() && item->is_room()) {
				if (rp.is_horiz_path()) {
					if (_ls_r2_hit(rp, *item)) {
						maybe_insert_door(rp, rp.rect.tl_corner());
					}
					if (_rs_r2_hit(rp, *item)) {
						maybe_insert_door(rp, rp.rect.tr_corner());
					}
				} else { // if (rp.is_vert_path())
					if (_ts_r2_hit(rp, *item)) {
						maybe_insert_door(rp, rp.rect.tl_corner());
					}
					if (_bs_r2_hit(rp, *item)) {
						maybe_insert_door(rp, rp.rect.bl_corner());
					}
				}
			}
		}
	}
	//for (size_t i=0; i<_self->floor_layout().size(); ++i) {
	//	const auto& some_rp = _self->_floor_layout.at(i);
	//	if (some_rp.door_pt_uset.size() > 0) {
	//		engine->log("door pts ", i, " [");
	//		for (const auto& door_pt: some_rp.door_pt_uset) {
	//			engine->log(door_pt, " ");
	//		}
	//		engine->log("]\n");
	//	}
	//}
	_remove_dead_end_paths();
	_insert_alt_terrain();
}
void DungeonGen::GenInnards::_remove_dead_end_paths() const {
	for (;;) {
		bool
			did_rm = false,
			erase_maybe_ret = true;
		for (
			size_t item_index=0;
			item_index<_self->floor_layout().size();
			++item_index
		) {
			did_rm = false;
			erase_maybe_ret = true;
			auto& item = _self->_floor_layout._raw_at(item_index);
			if (item.is_path() && item.conn_index_uset.size() <= 1) {
				if (
					GEN_YN_RM_DE_PATHS_DO_RM.rng_val_is_yes
						(GEN_YN_RM_DE_PATHS_DO_RM.gen())
				) {
					//engine->log("_remove_dead_end_paths(): ",
					//	"going to remove: ",
					//	"item{", item.rect.tl_corner(), " ",
					//		item.rect.br_corner(), "} ",
					//	i32(item_index), "\n");
					if (item.conn_index_uset.size() == 0) {
						throw std::runtime_error(sconcat
							("game_engine::level_gen_etc::DungeonGen",
							"::GenInnards::_remove_dead_end_paths(): ",
							"Eek! ", item_index, "; ",
							item.rect.tl_corner(), " ",
							item.rect.br_corner()));
					} else {
						did_rm = true;
						erase_maybe_ret
							= !_self->_floor_layout.erase_maybe
								(item_index);
						break;
					}
				}
			}
		}
		if (
			erase_maybe_ret || !did_rm
			//|| GEN_YN_RM_DE_PATHS_FINISH_IF.rng_val_is_yes
			//	(GEN_YN_RM_DE_PATHS_FINISH_IF.gen())
		) {
			break;
		}
	}
}
void DungeonGen::GenInnards::_insert_alt_terrain(
	//bool do_clear
) const {
	const auto
		& allowed_alt_terrain_vec = ALLOWED_ALT_TERRAIN_V2D
			.at(engine->level_minus_1());

	const IntRect2
		floor_r2
			= PFIELD_PHYS_RECT2,
			//= r2_build_in_pfield({1, 1}, {9, 4}),
		biome_mballs_bounds_r2
			//= PFIELD_PHYS_NO_BRDR_RECT2;
			= engine->layout_rand_r2_in_pfnb
				(GEN_BIOME_MBALL_GEN_MIN_SIZE_2D,
				GEN_BIOME_MBALL_GEN_MAX_SIZE_2D);
	//engine->log(biome_mballs_bounds_r2, "\n");

	MetaballGen
		//biome_mballs(floor_r2.size_2d);
		biome_mballs(biome_mballs_bounds_r2.size_2d);

	//for (
	//	size_t item_index=0;
	//	item_index<_self->floor_layout().size();
	//	++item_index
	//) {
	//	const auto& item = _self->_floor_layout._raw_at(item_index);
	//	//if (
	//	//	(item.is_path()
	//	//		&& (gen_biome_mbins_type == GEN_BIOME_MBINS_TYPE_PATH
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
	if (std::vector<IntRect2> biome_r2_vec; true) {
		const i32
			num_biome_r2s = engine->layout_rand<i32>
				(GEN_BIOME_MBALL_MIN_AMOUNT, GEN_BIOME_MBALL_MAX_AMOUNT);
		while (i32(biome_r2_vec.size()) < num_biome_r2s) {
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
				biome_r2_vec.push_back(to_push);
			}
		}
		for (const auto& biome_r2: biome_r2_vec) {
			const FltRect2 temp_biome_r2
				{.pos=FltVec2(biome_r2.pos),
				.size_2d=FltVec2(biome_r2.size_2d)};
			biome_mballs.add
				(temp_biome_r2.cntr_pos(), temp_biome_r2.size_2d);
			//biome_mballs.add
			//	(temp_biome_r2.cntr_pos(), temp_biome_r2.half_size());
		}
	}

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
		biome_thresh = float(engine->layout_rand<i32>
			(MIN_GEN_BIOME_THRESH_0 * GEN_BIOME_THRESH_MM_SCALE,
			MAX_GEN_BIOME_THRESH_0 * GEN_BIOME_THRESH_MM_SCALE))
			/ GEN_BIOME_THRESH_MM_SCALE;

	const auto& biome_gen
		//= biome_mballs.gen(0.10f, 0.3f);
		//= biome_mballs.gen(0.01f, 0.3f);
		//= biome_mballs.gen(0.00f, 0.5f);
		//= biome_mballs.gen(BIOME_THRESH_0, BIOME_THRESH_1);
		//= biome_mballs.gen(BIOME_THRESH);
		//= biome_mballs.gen();
		= biome_mballs.gen(biome_thresh);
	//engine->log("Debug: Generated metaballs\n");
	//for (size_t j=0; j<biome_gen.size(); ++j) {
	//	const auto& row = biome_gen.at(j);
	//	engine->log(j, ": ");
	//	for (size_t i=0; i<row.size(); ++i) {
	//		//engine->log(i, "{", row.at(i), "}");
	//		engine->log(row.at(i));
	//		if (i + size_t(1) < row.size()) {
	//			engine->log(" ");
	//		}
	//	}
	//	engine->log("\n");
	//}
	std::vector<std::vector<std::pair<bool, BgTile>>> biome_bg_tiles
		(biome_gen.size(),
			std::vector<std::pair<bool, BgTile>>
				(biome_gen.front().size(),
					std::pair(false, ALT_TERRAIN_NONE)));
	for (size_t j=0; j<biome_gen.size(); ++j) {
		const auto& row = biome_gen.at(j);
		for (size_t i=0; i<row.size(); ++i) {
			const auto& item = row.at(i);
			biome_bg_tiles.at(j).at(i).first
				= !item;
				//= item;
			//else if (
			//	item < 0.075f
			//	//item < 0.065f
			//) {
			//	bg_tile = BgTile::Water;
			//}
		}
	}

	// Breadth-first search
	{
		IntVec2Uset explored_uset;
		IntVec2 pos;
		for (pos.y=0; pos.y<i32(biome_bg_tiles.size()); ++pos.y) {
			auto& row = biome_bg_tiles.at(pos.y);
			for (pos.x=0; pos.x<i32(row.size()); ++pos.x) {
				const BgTile rng_bg_tile=allowed_alt_terrain_vec
					.at(engine->layout_rand<i32>
						(0, allowed_alt_terrain_vec.size() - 1));
				if (!explored_uset.contains(pos)) {
					bfs_fill
						(explored_uset, pos,
						[&](
							const IntVec2Uset& some_explored_uset,
							const IntVec2& some_pos
						) -> bool {
							const IntVec2
								temp_pos = some_pos
									- biome_mballs_bounds_r2.tl_corner();
							return PFIELD_PHYS_NO_BRDR_RECT2
								.intersect(some_pos)
								&& biome_bg_tiles
									.at(temp_pos.y).at(temp_pos.x).first;
						},
						[&](
							const IntVec2Uset& some_explored_uset,
							const IntVec2& some_pos
						) -> void {
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


	engine->log("Debug: generated biome `BgTile`s\n");
	for (size_t j=0; j<biome_bg_tiles.size(); ++j) {
		auto& row = biome_bg_tiles.at(j);
		engine->log(j, ": ");
		for (size_t i=0; i<row.size(); ++i) {
			const auto& bg_tile = row.at(i);
			//if (bg_tile == ALT_TERRAIN_NONE)
			if (!bg_tile.first) {
				engine->log(char(comp::drawable_data_umap().at
					(bg_tile_str_map_at(BgTile::RoomFloor)).c));
			} else { // if (bg_tile.first)
				const auto& draw_data
					= comp::drawable_data_umap().at
						(bg_tile_str_map_at(bg_tile.second));
				engine->log(char(draw_data.c));
			}
		}
		//if (j + size_t(1) < biome_bg_tiles.size()) {
			engine->log("\n");
		//}
	}

	////for (auto& item: *_self->floor_layout)
	for (
		size_t item_index=0;
		item_index<_self->floor_layout().size();
		++item_index
	) {
		auto& item = _self->_floor_layout._raw_at(item_index);
		//if (do_clear) {
		//	item.alt_terrain_umap.clear();
		//}

		//if (item.is_path()) {
		//	continue;
		//}

		// Note that `RoomPath`s are already generated with their borders
		IntVec2
			pos;
		for (
			pos.y=item.rect.top_y() - i32(1);
			pos.y<=item.rect.bottom_y() + i32(1);
			++pos.y
		) {
			for (
				pos.x=item.rect.left_x() - i32(1);
				pos.x<=item.rect.right_x() + i32(1);
				++pos.x
			) {
				//const auto
				//	//bg_tile_index = engine->layout_noise<i32>
				//	//	(0, allowed_alt_terrain_vec.size() - 1, pos,
				//	//	_self->_floor_layout.layout_noise_add_amount());
				//	bg_tile_index = engine->mball_out
				//		(0, allowed_alt_terrain_vec.size() - 1,
				//		mball_dyna2d, pos);

				//const auto
				//	bg_tile_index =
				//const BgTile
				//	bg_tile
				//		//= allowed_alt_terrain_vec.at(bg_tile_index);
				//		//= BgTile::Water;
				//		= biome_gen.at(pos.y).at(pos.x) 
				//		//? BgTile::Spikes
				//		? BgTile::Water
				//		: ALT_TERRAIN_NONE;
				//const auto& lake = biome_gen.at(pos.y).at(pos.x);
				//BgTile bg_tile;
				//if (lake <= 0.1f) {
				//	bg_tile = BgTile::Spikes;
				//} else if (lake <= 0.11f) {
				//	bg_tile = BgTile::Water;
				//} else {
				//	bg_tile = ALT_TERRAIN_NONE;
				//}
				if (!biome_mballs_bounds_r2.intersect(pos)) {
					continue;
				}

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
				if (item.is_path()) {
					if (!BASIC_UNSAFE_BG_TILE_USET.contains
						(bg_tile.second)) {
						item.alt_terrain_umap[pos] = bg_tile.second;
					}
				} else { // if (item.is_room())
					if (
						!BASIC_UNSAFE_BG_TILE_USET.contains
							(bg_tile.second)
						|| (!item.pos_in_border(pos)
							&& !item.pos_in_internal_border(pos))
					) {
						item.alt_terrain_umap[pos] = bg_tile.second;
					}
				}
			}
		}
	}
}
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
