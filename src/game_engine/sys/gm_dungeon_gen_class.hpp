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

#ifndef src_game_engine_sys_gm_dungeon_gen_class_hpp
#define src_game_engine_sys_gm_dungeon_gen_class_hpp

// src/game_engine/sys/gm_dungeon_gen_class.hpp

#include "../../misc_includes.hpp"
#include "../comp/floor_layout_comp_classes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace sys {
//--------
// Game Mode: Dungeon Generation
class GmDungeonGen final: public ecs::Sys {
public:		// types
	//--------
	//// A `class` representing the next
	//class GenInfo final {
	//public:		// variables
	//	i32 conn_index = 0;
	//};
	//--------
	using RoomPath = comp::DungeonGen::RoomPath;
	//--------
public:		// constants
	//--------
	static constexpr i32
		MIN_NUM_ROOM_PATHS = comp::DungeonGen::MIN_NUM_ROOM_PATHS,
		MAX_NUM_ROOM_PATHS = comp::DungeonGen::MAX_NUM_ROOM_PATHS;
	//--------
	static constexpr i32
		PATH_THICKNESS = RoomPath::PATH_THICKNESS,
		PATH_MIN_LEN = RoomPath::PATH_MIN_LEN,
		PATH_MAX_LEN = RoomPath::PATH_MAX_LEN;

	static constexpr IntVec2
		ROOM_MIN_SIZE_2D = RoomPath::ROOM_MIN_SIZE_2D,
		ROOM_MAX_SIZE_2D = RoomPath::ROOM_MAX_SIZE_2D;
	//--------
	static constexpr i32
		// Generation percentages and stuff. 
		//PATH_THRESH_MIN = 0,
		//PATH_THRESH_MAX = 0,
		//ROOM_THRESH_MIN = 1,
		//ROOM_THRESH_MAX = 1,
		GEN_TYPE_PATH = 0, MIN_GEN_TYPE = GEN_TYPE_PATH,
		GEN_TYPE_ROOM = 1, MAX_GEN_TYPE = GEN_TYPE_ROOM,

		GEN_SIDE_L = 0, MIN_GEN_SIDE = GEN_SIDE_L,
		GEN_SIDE_T = 1,
		GEN_SIDE_R = 2,
		GEN_SIDE_B = 3, MAX_GEN_SIDE = GEN_SIDE_B,

		//GEN_NEXT_SAME_MIN = 0, MIN_GEN_NEXT = GEN_NEXT_SAME_MIN,
		//GEN_NEXT_SAME_MAX = 2,
		//GEN_NEXT_DIFFERENT_MIN = 3,
		//GEN_NEXT_DIFFERENT_MAX = 9, MAX_GEN_NEXT = GEN_NEXT_DIFFERENT_MAX,
		GEN_NEXT_ROOM_SAME_TYPE_MIN = 0,
			MIN_GEN_NEXT_ROOM_TYPE = GEN_NEXT_ROOM_SAME_TYPE_MIN,
		GEN_NEXT_ROOM_SAME_TYPE_MAX = 0,
		GEN_NEXT_ROOM_DIFF_TYPE_MIN = 1,
		GEN_NEXT_ROOM_DIFF_TYPE_MAX = 9,
			MAX_GEN_NEXT_ROOM_TYPE = GEN_NEXT_ROOM_DIFF_TYPE_MAX,

		GEN_NEXT_ROOM_SAME_INDEX_MIN = 0,
			MIN_GEN_NEXT_ROOM_INDEX = GEN_NEXT_ROOM_SAME_INDEX_MIN,
		GEN_NEXT_ROOM_SAME_INDEX_MAX = 3,
		GEN_NEXT_ROOM_DIFF_INDEX_MIN = 4,
		GEN_NEXT_ROOM_DIFF_INDEX_MAX = 9,
			MAX_GEN_NEXT_ROOM_INDEX = GEN_NEXT_ROOM_DIFF_INDEX_MAX,

		GEN_NEXT_PATH_SAME_TYPE_MIN = 0,
			MIN_GEN_NEXT_PATH_TYPE = GEN_NEXT_PATH_SAME_TYPE_MIN,
		GEN_NEXT_PATH_SAME_TYPE_MAX = 6,
		GEN_NEXT_PATH_DIFF_TYPE_MIN = 7,
		GEN_NEXT_PATH_DIFF_TYPE_MAX = 9,
			MAX_GEN_NEXT_PATH_TYPE = GEN_NEXT_PATH_DIFF_TYPE_MAX,

		GEN_NEXT_PATH_SAME_INDEX_MIN = 0,
			MIN_GEN_NEXT_PATH_INDEX = GEN_NEXT_PATH_SAME_INDEX_MIN ,
		GEN_NEXT_PATH_SAME_INDEX_MAX = 5,
		GEN_NEXT_PATH_DIFF_INDEX_MIN = 6,
		GEN_NEXT_PATH_DIFF_INDEX_MAX = 9,
			MAX_GEN_NEXT_PATH_INDEX = GEN_NEXT_PATH_DIFF_INDEX_MAX,

		GEN_CONNECT_YES_MIN = 0, MIN_GEN_CONNECT = GEN_CONNECT_YES_MIN,
		GEN_CONNECT_YES_MAX = 8,
		GEN_CONNECT_NO_MIN = 7,
		GEN_CONNECT_NO_MAX = 9, MAX_GEN_CONNECT = GEN_CONNECT_NO_MAX,

		// This is the number of tries to attempt room/path generation
		// after failing to generate a valid one.
		GEN_RP_LIM_TRIES
			//= 20;
			= 50;
		//--------
public:		// constants
	static const std::string
		KIND_STR;
private:		// variables
	std::optional<ecs::EntId>
		_bg_tile_map_id,
		_dungeon_gen_id;

	i32
		_attempted_num_rp = 0;
	bool
		_stop_gen_early = false,
		_done_generating = false;

public:		// functions
	GmDungeonGen() = default;
	//inline GmDungeonGen(const binser::Value& bv)
	//	: ecs::Sys(bv) {
	//}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GmDungeonGen);
	virtual ~GmDungeonGen() = default;

	virtual std::string kind_str() const;

	void clear_dungeon_gen(ecs::Engine* ecs_engine);
private:		// functions
	virtual void _init(ecs::Engine* ecs_engine);
public:		// functions
	virtual void tick(ecs::Engine* ecs_engine);
private:		// functions
	//void _connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
	//	comp::DungeonGen* dungeon_gen);
private:		// types
	class GenInnards final {
	public:		// types
		using RoomPath = GmDungeonGen::RoomPath;
	private:		// variables
		GmDungeonGen
			* _self = nullptr;
		comp::DungeonGen
			* _dungeon_gen = nullptr;
		//RoomPath
		//	* _rp = nullptr,
		//	* _item = nullptr;
		//	//* _conn_rp = nullptr;

		//i32
		//	_gen_side = 0,
		//	_gen_next_type = 0,
		//	_gen_next_conn_rp_index = 0,
		//	_gen_type = 0,
		//	_conn_rp_index = 0;
		//size_t
		//	_check_i;
	public:		// functions
		inline GenInnards(
			GmDungeonGen* s_self, comp::DungeonGen* s_dungeon_gen
		)
			: _self(s_self), _dungeon_gen(s_dungeon_gen) {
		}
		bool gen_single_rp();
	private:		// functions
		//--------
		std::optional<RoomPath> _inner_gen_post_first() const;
		void _do_push_back(RoomPath&& to_push_rp) const;
		//--------
	public:		// functions
		bool any_intersect(
			const RoomPath& to_check_rp, const std::optional<size_t>& index
		) const;
		bool any_path_sides_hit_wrongly(
			const RoomPath& to_check_rp, const std::optional<size_t>& index
		) const;
		void finalize(bool do_clear) const;
		//void insert_doors(bool do_clear) const;
	private:		// static functions
		//--------
		static inline IntRect2 _ls_r2(const RoomPath& some_rp) {
			return r2_left_side_in_pfield_nb(some_rp.rect);
		}
		static inline IntRect2 _ts_r2(const RoomPath& some_rp) {
			return r2_top_side_in_pfield_nb(some_rp.rect);
		}
		static inline IntRect2 _rs_r2(const RoomPath& some_rp) {
			return r2_right_side_in_pfield_nb(some_rp.rect);
		}
		static inline IntRect2 _bs_r2(const RoomPath& some_rp) {
			return r2_bottom_side_in_pfield_nb(some_rp.rect);
		}
		//--------
		static inline bool _ls_r2_hit(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return 
				(//i32(_check_i) != _conn_rp_index
				//_gen_side == GEN_SIDE_L
				//&&
				//r2_fits_in_pfield_nb(_ls_r2(rp_0))
				r2_intersects_pfield_nb(_ls_r2(rp_0))
				&& rp_1.rect.intersect(_ls_r2(rp_0)));
		}
		static inline bool _ts_r2_hit(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return (//r2_fits_in_pfield_nb(_ts_r2(rp_0))
				r2_intersects_pfield_nb(_ts_r2(rp_0))
				&& rp_1.rect.intersect(_ts_r2(rp_0)));
		}
		static inline bool _rs_r2_hit(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return (//r2_fits_in_pfield_nb(_rs_r2(rp_0))
				r2_intersects_pfield_nb(_rs_r2(rp_0))
				&& rp_1.rect.intersect(_rs_r2(rp_0)));
		}
		static inline bool _bs_r2_hit(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return (//r2_fits_in_pfield_nb(_bs_r2(rp_0))
				r2_intersects_pfield_nb(_bs_r2(rp_0))
				&& rp_1.rect.intersect(_bs_r2(rp_0)));
		}
		//--------
		static inline bool _ls_and_rs_hit(
			const RoomPath& rp_ls, const RoomPath& rp_rs
		) {
			return _ls_r2(rp_ls).intersect(_rs_r2(rp_rs));
		}
		static inline bool _ts_and_bs_hit(
			const RoomPath& rp_ts, const RoomPath& rp_bs
		) {
			return _ts_r2(rp_ts).intersect(_bs_r2(rp_bs));
		}
		//--------
		static inline bool _path_sides_hit_wrongly(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return (
				(
					rp_0.is_horiz_path()
					&& (_ts_r2_hit(rp_0, rp_1)
						|| _bs_r2_hit(rp_0, rp_1))
				) || (
					rp_0.is_vert_path()
					&& (_ls_r2_hit(rp_0, rp_1)
						|| _rs_r2_hit(rp_0, rp_1))
				) || (
					rp_1.is_horiz_path()
					&& (_ts_r2_hit(rp_1, rp_0)
						|| _bs_r2_hit(rp_1, rp_0))
				) || (
					rp_1.is_vert_path()
					&& (_ls_r2_hit(rp_1, rp_0)
						|| _rs_r2_hit(rp_1, rp_0))
				)
			);
		}
	private:		// functions
		//--------
		//inline RoomPath* _item() {
		//	return &_dungeon_gen->at(_check_i);
		//}
		//--------
		//inline IntRect2 _rp_ls_r2(const RoomPath& rp) const {
		//	return _ls_r2(rp);
		//}
		//inline IntRect2 _rp_ts_r2(const RoomPath& rp) const {
		//	return _ts_r2(rp);
		//}
		//inline IntRect2 _rp_rs_r2(const RoomPath& rp) const {
		//	return _rs_r2(rp);
		//}
		//inline IntRect2 _rp_bs_r2(const RoomPath& rp) const {
		//	return _bs_r2(rp);
		//}
		//inline IntRect2 _item_ls_r2(const RoomPath& item) const {
		//	return _ls_r2(item);
		//}
		//inline IntRect2 _item_ts_r2(const RoomPath& item) const {
		//	return _ts_r2(item);
		//}
		//inline IntRect2 _item_rs_r2(const RoomPath& item) const {
		//	return _rs_r2(item);
		//}
		//inline IntRect2 _item_bs_r2(const RoomPath& item) const {
		//	return _bs_r2(item);
		//}

		//inline IntRect2 _item_ls_r2() const {
		//	return IntRect2::build_in_grid_lim
		//		(item().rect.tl_corner() - IntVec2{1, 0},
		//		item().rect.bl_corner() - IntVec2{1, 0},
		//		PFIELD_PHYS_NO_BORDER_RECT2);
		//}
		//inline IntRect2 _item_ts_r2() const {
		//	return IntRect2::build_in_grid_lim
		//		(item().rect.tl_corner() - IntVec2{0, 1},
		//		item().rect.tr_corner() - IntVec2{0, 1},
		//		PFIELD_PHYS_NO_BORDER_RECT2);
		//}
		//inline IntRect2 _item_rs_r2() const {
		//	return IntRect2::build_in_grid_lim
		//		(item().rect.tr_corner() + IntVec2{1, 0},
		//		item().rect.br_corner() + IntVec2{1, 0},
		//		PFIELD_PHYS_NO_BORDER_RECT2);
		//}
		//inline IntRect2 _item_bs_r2() const {
		//	return IntRect2::build_in_grid_lim
		//		(item().rect.bl_corner() + IntVec2{0, 1},
		//		item().rect.br_corner() + IntVec2{0, 1},
		//				PFIELD_PHYS_NO_BORDER_RECT2);
		//}
		//--------
		//inline bool _item_ls_r2_hit() const {
		//	return (r2_fits_in_pfield_nb(_item_ls_r2())
		//		&& rp.rect.intersect(_item_ls_r2()));
		//}
		//inline bool _item_ts_r2_hit() const {
		//	return (r2_fits_in_pfield_nb(_item_ts_r2())
		//		&& rp.rect.intersect(_item_ts_r2()));
		//}
		//inline bool _item_rs_r2_hit() const {
		//	return (r2_fits_in_pfield_nb(_item_rs_r2())
		//		&& rp.rect.intersect(_item_rs_r2()));
		//}
		//inline bool _item_bs_r2_hit() const {
		//	return (r2_fits_in_pfield_nb(_item_bs_r2())
		//		&& rp.rect.intersect(_item_bs_r2()));
		//}
		//inline bool _rp_ls_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _ls_r2_hit(rp, item);
		//}
		//inline bool _rp_ts_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _ts_r2_hit(rp, item);
		//}
		//inline bool _rp_rs_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _rs_r2_hit(rp, item);
		//}
		//inline bool _rp_bs_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _bs_r2_hit(rp, item);
		//}

		//inline bool _item_ls_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _ls_r2_hit(item, rp);
		//}
		//inline bool _item_ts_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _ts_r2_hit(item, rp);
		//}
		//inline bool _item_rs_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _rs_r2_hit(item, rp);
		//}
		//inline bool _item_bs_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _bs_r2_hit(item, rp);
		//}
		//--------
		//inline bool _rp_ls_r2_and_item_rs_r2_hit() const {
		//	return _rp_ls_r2().intersect(_item_rs_r2());
		//}
		//inline bool _rp_ts_r2_and_item_bs_r2_hit() const {
		//	return _rp_ts_r2().intersect(_item_bs_r2());
		//}
		//inline bool _rp_rs_r2_and_item_ls_r2_hit() const {
		//	return _rp_rs_r2().intersect(_item_ls_r2());
		//}
		//inline bool _rp_bs_r2_and_item_ts_r2_hit() const {
		//	return _rp_bs_r2().intersect(_item_ts_r2());
		//}
		//inline bool _rp_ls_r2_and_item_rs_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _ls_and_rs_hit(rp, item);
		//}
		//inline bool _rp_ts_r2_and_item_bs_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _ts_and_bs_hit(rp, item);
		//}
		//inline bool _rp_rs_r2_and_item_ls_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _ls_and_rs_hit(item, rp);
		//}
		//inline bool _rp_bs_r2_and_item_ts_r2_hit(
		//	const RoomPath& rp, const RoomPath& item
		//) const {
		//	return _ts_and_bs_hit(item, rp);
		//}
		//--------
	};
	friend class GenInnards;
};
//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_sys_gm_dungeon_gen_class_hpp
