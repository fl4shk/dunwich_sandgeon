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

#ifndef src_game_engine_dungeon_gen_dungeon_gen_class_hpp
#define src_game_engine_dungeon_gen_dungeon_gen_class_hpp

// src/game_engine/level_gen_etc/dungeon_gen_class.hpp

#include "../../misc_includes.hpp"
#include "floor_layout_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
namespace sys {
class GmDungeonGen;
} // namespace sys
//--------
namespace level_gen_etc {
//--------
class DungeonGen final {
	friend class sys::GmDungeonGen;
public:		// types
	//--------
	//// A `class` representing the next
	//class GenInfo final {
	//public:		// variables
	//	i32 conn_index = 0;
	//};
	//--------
	//using BgTile = comp::BgTile;
	//using SizeAndBgTile = comp::SizeAndBgTile;
	//using FloorLayout = comp::FloorLayout;
	using RoomPath = FloorLayout::RoomPath;
	//--------
	class GenNext final {
	public:		// variables
		i32
			same_max,
			diff_max;
	public:		// functions
		constexpr inline i32 same_min() const {
			return i32(0);
		}
		constexpr inline i32 diff_min() const {
			return same_max + i32(1);
		}
		constexpr inline i32 full_min() const {
			return same_min();
		}
		constexpr inline i32 full_max() const {
			return diff_max;
		}
		i32 gen() const;
		constexpr inline bool rng_val_is_same(i32 rng_val) const {
			return (rng_val >= same_min() && rng_val <= same_max);
		}
		constexpr inline bool rng_val_is_diff(i32 rng_val) const {
			return (rng_val >= diff_min() && rng_val <= diff_max);
		}
	};
	class GenYesNo final {
	public:		// variables
		i32
			no_max,
			yes_max;
	public:		// functions
		constexpr inline i32 no_min() const {
			return i32(0);
		}
		constexpr inline i32 yes_min() const {
			return no_max + i32(1);
		}
		constexpr inline i32 full_min() const {
			return no_min();
		}
		constexpr inline i32 full_max() const {
			return yes_max;
		}
		i32 gen() const;
		constexpr inline bool rng_val_is_no(i32 rng_val) const {
			return (rng_val >= no_min() && rng_val <= no_max);
		}
		constexpr inline bool rng_val_is_yes(i32 rng_val) const {
			return (rng_val >= yes_min() && rng_val <= yes_max);
		}
	};
	//--------
public:		// constants
	static constexpr BgTile
		BIOME_TERRAIN_NONE = BgTile::Error;
	static const std::vector<std::vector<BgTile>>
		ALLOWED_BIOME_TERRAIN_V2D;
		//LEVEL_1_BIOME_TERRAIN_VEC,
		//LEVEL_2_BIOME_TERRAIN_VEC,
		//LEVEL_3_BIOME_TERRAIN_VEC,
		//LEVEL_4_BIOME_TERRAIN_VEC,
		//LEVEL_5_BIOME_TERRAIN_VEC;
	//--------
public:		// constants
	//--------
	static constexpr i32
		MIN_NUM_ROOM_PATHS = FloorLayout::MIN_NUM_ROOM_PATHS,
		MAX_NUM_ROOM_PATHS = FloorLayout::MAX_NUM_ROOM_PATHS;
	//--------
	static constexpr i32
		PATH_THICKNESS = FloorLayout::PATH_THICKNESS,
		PATH_MIN_LEN = FloorLayout::PATH_MIN_LEN,
		PATH_MAX_LEN = FloorLayout::PATH_MAX_LEN;

	static constexpr IntVec2
		ROOM_MIN_SIZE_2D = FloorLayout::ROOM_MIN_SIZE_2D,
		ROOM_MAX_SIZE_2D = FloorLayout::ROOM_MAX_SIZE_2D;
	//--------
	static constexpr i32
		// Generation percentages and stuff. 
		//PATH_THRESH_MIN = 0,
		//PATH_THRESH_MAX = 0,
		//ROOM_THRESH_MIN = 1,
		//ROOM_THRESH_MAX = 1,
		//--------
		GEN_TYPE_PATH = 0, MIN_GEN_TYPE = GEN_TYPE_PATH,
		GEN_TYPE_ROOM = 1, MAX_GEN_TYPE = GEN_TYPE_ROOM,
		//--------
		GEN_SIDE_L = 0, MIN_GEN_SIDE = GEN_SIDE_L,
		GEN_SIDE_T = 1,
		GEN_SIDE_R = 2,
		GEN_SIDE_B = 3, MAX_GEN_SIDE = GEN_SIDE_B,
		//--------
		MIN_GEN_SHRINK_NUM_ATTEMPTS_PATH
			= (PATH_MIN_LEN + PATH_MAX_LEN) / 2,
		MAX_GEN_SHRINK_NUM_ATTEMPTS_PATH = PATH_MAX_LEN,

		MIN_GEN_SHRINK_NUM_ATTEMPTS_ROOM
			= (math::max_va(ROOM_MIN_SIZE_2D.x, ROOM_MIN_SIZE_2D.y)
				+ math::max_va(ROOM_MAX_SIZE_2D.x, ROOM_MAX_SIZE_2D.y))
				/ 2,
		MAX_GEN_SHRINK_NUM_ATTEMPTS_ROOM
			= math::max_va(ROOM_MAX_SIZE_2D.x, ROOM_MAX_SIZE_2D.y) * 2,
		//--------
		// "TSF" is short for "to shrink from"
		GEN_EXTEND_AMOUNT_TSF
			//= 5,
			//= 7,
			//= 8,
			//= 10,
			= 15,
		GEN_PARALLEL_PATH_MIN_DIST
			//= 3;
			= 4;
			//= 5;
		//--------
	//--------
	static constexpr float
		//MIN_GEN_BIOME_THRESH_0
		//	= 0.0f,
		//	//= 0.005f,
		//MAX_GEN_BIOME_THRESH_0
		//	= 0.0075f,
		//MIN_GEN_BIOME_THRESH_1
		//	//= 0.05f,
		//	= 0.075f,
		//	//= 0.3f,
		//MAX_GEN_BIOME_THRESH_1
		//	//= 0.5f,
		//	//= 0.25f,
		//	= 0.15f,
		MIN_GEN_BIOME_THRESH_0
			//= 0.3f,
			//= 0.5f,
			//= 0.75f,
			//= 1.0f,
			= 2.0f,
			//= 4.0f,
		MAX_GEN_BIOME_THRESH_0
			//= 4.0f,
			= 6.0f,
			//= 8.0f,
		GEN_BIOME_THRESH_MM_SCALE = 1000.0f;
	//static constexpr i32
	//	GEN_BIOME_MBINS_TYPE_PATH = 0,
	//		MIN_GEN_BIOME_MBINS_TYPE = GEN_BIOME_MBINS_TYPE_PATH,
	//	GEN_BIOME_MBINS_TYPE_ROOM = 1,
	//	GEN_BIOME_MBINS_TYPE_BOTH = 2,
	//		MAX_GEN_BIOME_MBINS_TYPE = GEN_BIOME_MBINS_TYPE_BOTH;
	static constexpr i32
		GEN_BIOME_MBALL_MIN_AMOUNT
			//= 2,
			//= 3,
			= 4,
		GEN_BIOME_MBALL_MAX_AMOUNT
			//= 4;
			//= 5;
			//= 7;
			//= 8;
			//= 10;
			= 12;
			//= 13;
			//= 20;
	static constexpr IntVec2
		GEN_BIOME_MBALL_MIN_SIZE_2D
			= {1, 1},
			//= {3, 3},
			//= {5, 5},
			//= {6, 6},
			//= {7, 7},
		GEN_BIOME_MBALL_MAX_SIZE_2D
			//= {3, 3},
			//= {5, 5},
			//= {6, 6},
			= {7, 7},
			//= {8, 8},
			//= {10, 10},
			//= {15, 15},
		GEN_BIOME_MBALL_GEN_MIN_SIZE_2D
			//= {15, 15},
			//= {25, 25},
			//= {30, 30},
			//= {35, 35},
			= PFIELD_PHYS_NO_BRDR_RECT2.size_2d,
			/// 7,
		GEN_BIOME_MBALL_GEN_MAX_SIZE_2D
			= PFIELD_PHYS_NO_BRDR_RECT2.size_2d;
			//- IntVec2{5, 5};
			//- (PFIELD_PHYS_NO_BRDR_RECT2.size_2d / 7);
			//- GEN_BIOME_MBALL_GEN_MIN_SIZE_2D;
			//- GEN_BIOME_MBALL_MIN_SIZE_2D;
	//--------
	static constexpr GenNext
		//GEN_NEXT_SAME_MIN = 0, MIN_GEN_NEXT = GEN_NEXT_SAME_MIN,
		//GEN_NEXT_SAME_MAX = 2,
		//GEN_NEXT_DIFFERENT_MIN = 3,
		//GEN_NEXT_DIFFERENT_MAX = 9, MAX_GEN_NEXT = GEN_NEXT_DIFFERENT_MAX,
		GEN_NEXT_ROOM_TYPE
			{
			//.same_max=0,
			//.diff_max=9
			.same_max=25,
			//.same_max=45,
			.diff_max=99
			},
		GEN_NEXT_ROOM_INDEX
			{
			.same_max=3,
			.diff_max=9
			},

		GEN_NEXT_PATH_TYPE
			{
			//.same_max=0,
			//.same_max=2,
			//.diff_max=9
			.same_max=25,
			//.same_max=5,
			.diff_max=99,
			//.same_max=32,
			//.same_max=85,
			//.diff_max=99
			},
		//GEN_NEXT_PATH_INDEX
		//	{.same_max=85,
		//	.diff_max=99};
		// generating a room, and previously generated a path
		GEN_NEXT_PATH_INDEX_NOW_ROOM
			{
			//.same_max=87,
			//.same_max=93,
			//.same_max=95,
			.same_max=96,
			.diff_max=99
			//.same_max=3,
			//.same_max=100,
			//.diff_max=200
			//.same_max=1999,
			//.diff_max=2000
			//.same_max=1999,
			//.diff_max=2000
			},
		// generating a path, and previously generated a path
		GEN_NEXT_PATH_INDEX_NOW_PATH
			{
			.same_max=5,
			.diff_max=9
			//.same_max=45,
			//.same_max=75,
			//.same_max=1999,
			//.diff_max=2000
			};
	//--------
	static constexpr GenYesNo
		GEN_YN_CONNECT
			{
			//.no_max=65,
			//.no_max=34,
			//.no_max=0,
			.no_max=35,
			.yes_max=99
			//.yes_max=999
			},

		GEN_YN_RM_DE_PATHS_DO_RM
			{
			//.no_max=29,
			//.no_max=19,
			.no_max=0,
			.yes_max=99,
			},
		GEN_YN_RM_DE_PATHS_FINISH_IF
			{
			//.no_max=29,
			//.no_max=19,
			.no_max=98,
			.yes_max=99
			};
	//--------
	static constexpr i32
		// This is the number of tries to attempt room/path generation
		// after failing to generate a valid one.
		GEN_RP_LIM_TRIES
			//= 20;
			//= 50;
			= 100;
	//--------
private:		// variables
	i32
		_attempted_num_rp = 0;
	bool
		_stop_gen_early = false,
		_done_generating = false;
	FloorLayout _floor_layout;
public:		// functions
	DungeonGen() = default;
	//inline DungeonGen(const binser::Value& bv)
	//	: ecs::Sys(bv) {
	//}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DungeonGen);
	inline ~DungeonGen() = default;

	void clear(
		//ecs::Engine* ecs_engine
	);
	void gen_curr_floor();
	GEN_GETTER_BY_CON_REF(floor_layout);
private:		// functions
	//void _connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
	//	FloorLayout* floor_layout);
private:		// types
	class GenInnards final {
	public:		// types
		using RoomPath = DungeonGen::RoomPath;
	private:		// variables
		DungeonGen
			* _self = nullptr;
		//ecs::Engine
		//	* _ecs_engine = nullptr;
		//FloorLayout
		//	* _floor_layout = nullptr;
		RoomPath _temp_to_push_rp;
		//RoomPath
		//	* _rp = nullptr,
		//	* _item = nullptr;
		//	//* _conn_rp = nullptr;

		i32
			//_gen_side = 0,
			_gen_next_type = 0,
			_gen_next_conn_rp_index = 0,
			_gen_type = 0,
			_conn_rp_index = 0;
		//size_t
		//	_check_i;
	public:		// functions
		inline GenInnards(
			DungeonGen* s_self
			//ecs::Engine* s_ecs_engine,
			//FloorLayout* s_dungeon_floor
		)
			: _self(s_self)
			//_ecs_engine(s_ecs_engine),
			//_floor_layout(s_dungeon_floor)
			//_floor_layout(&_self->floor_layout)
		{
		}
		bool gen_single_rp();
	public:		// functions
		std::optional<RoomPath> _inner_gen_post_first();
	private:		// functions
		//--------
		void _do_push_back(RoomPath&& to_push_rp) const;
		//--------
		std::optional<RoomPath> _gen_initial_rp();
		//--------
		//i32 _choose_shrink_or_extend_side(
		//	bool was_horiz_path, bool was_vert_path,
		//	//const RoomPath& some_rp
		//	//const std::optional<size_t>& index
		//);
		bool _shrink(
			bool was_horiz_path, bool was_vert_path,
			RoomPath& some_rp, //const std::optional<size_t>& index,
			const std::function<bool(
				RoomPath&//, const std::optional<size_t>&
			)>& extra_test_func
		);
		bool _basic_shrink_extra_test_func(
			RoomPath& some_rp
			//, const std::optional<size_t>& index
		);
		void _connect(
			//bool was_horiz_path, bool was_vert_path,
			//RoomPath& some_rp, //const std::optional<size_t>& index,
			//const std::function<bool(
			//	RoomPath&//, const std::optional<size_t>&
			//)>& shrink_extra_test_func
		);
		//--------
		inline bool _rp_is_connected(const RoomPath& some_rp) const {
			const RoomPath& conn_rp
				= _self->_floor_layout.at(_conn_rp_index);
			return (
				(some_rp.gen_side == GEN_SIDE_L
					&& _ls_r2_hit(conn_rp, some_rp))
				|| (some_rp.gen_side == GEN_SIDE_T
					&& _ts_r2_hit(conn_rp, some_rp))
				|| (some_rp.gen_side == GEN_SIDE_R
					&& _rs_r2_hit(conn_rp, some_rp))
				|| (some_rp.gen_side == GEN_SIDE_B
					&& _bs_r2_hit(conn_rp, some_rp))
			);
		};
		//--------
	public:		// functions
		//--------
		std::vector<size_t> any_intersect_find_all(
			RoomPath& to_check_rp, const std::optional<size_t>& index
		);
		std::optional<size_t> any_intersect_find_first(
			RoomPath& to_check_rp, const std::optional<size_t>& index
		);
		//--------
		std::vector<size_t> any_sides_intersect_find_all(
			RoomPath& to_check_rp, const std::optional<size_t>& index
		);
		std::optional<size_t> any_sides_intersect_find_first(
			RoomPath& to_check_rp, const std::optional<size_t>& index
		);
		//--------
		std::vector<size_t> any_path_sides_hit_wrongly_find_all(
			RoomPath& to_check_rp, const std::optional<size_t>& index
		);
		std::optional<size_t> any_path_sides_hit_wrongly_find_first(
			RoomPath& to_check_rp, const std::optional<size_t>& index
		);
		//--------
	private:		// functions
		//--------
		std::vector<size_t> _find_all_backend(
			RoomPath& to_check_rp,
			const std::optional<size_t>& index,
			const std::function<bool(
				RoomPath&, const RoomPath&
			)>& test_func
		);
		std::optional<size_t> _find_first_backend(
			RoomPath& to_check_rp,
			const std::optional<size_t>& index,
			const std::function<bool(
				RoomPath&, const RoomPath&
			)>& test_func
		);
		//--------
	public:		// functions
		//--------
		void finalize(
			//bool do_clear
		) const;
		//void insert_doors(bool do_clear) const;
	private:		// functions
		//--------
		void _remove_dead_end_paths() const;
		void _insert_biome_terrain(
			//bool do_clear
		) const;
		//--------
	private:		// static functions
		//--------
		static constexpr inline IntRect2 _ls_r2(const RoomPath& some_rp) {
			return r2_left_side_1ge_past_in_pfnb(some_rp.rect);
		}
		static constexpr inline IntRect2 _ts_r2(const RoomPath& some_rp) {
			return r2_top_side_1ge_past_in_pfnb(some_rp.rect);
		}
		static constexpr inline IntRect2 _rs_r2(const RoomPath& some_rp) {
			return r2_right_side_1ge_past_in_pfnb(some_rp.rect);
		}
		static constexpr inline IntRect2 _bs_r2(const RoomPath& some_rp) {
			return r2_bottom_side_1ge_past_in_pfnb(some_rp.rect);
		}
		//--------
		static constexpr inline bool _ls_r2_hit(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return 
				(//i32(_check_i) != _conn_rp_index
				//rp_0.gen_side == GEN_SIDE_L
				//&&
				r2_fits_in_pfnb(_ls_r2(rp_0))
				//r2_intersects_pfield_nb(_ls_r2(rp_0))
				&& rp_1.rect.intersect(_ls_r2(rp_0)));
		}
		static constexpr inline bool _ts_r2_hit(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return (r2_fits_in_pfnb(_ts_r2(rp_0))
				//r2_intersects_pfield_nb(_ts_r2(rp_0))
				&& rp_1.rect.intersect(_ts_r2(rp_0)));
		}
		static constexpr inline bool _rs_r2_hit(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return (r2_fits_in_pfnb(_rs_r2(rp_0))
				//r2_intersects_pfield_nb(_rs_r2(rp_0))
				&& rp_1.rect.intersect(_rs_r2(rp_0)));
		}
		static constexpr inline bool _bs_r2_hit(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return (r2_fits_in_pfnb(_bs_r2(rp_0))
				//r2_intersects_pfield_nb(_bs_r2(rp_0))
				&& rp_1.rect.intersect(_bs_r2(rp_0)));
		}
		//--------
		static constexpr inline bool _ls_and_rs_hit(
			const RoomPath& rp_ls, const RoomPath& rp_rs
		) {
			return _ls_r2(rp_ls).intersect(_rs_r2(rp_rs));
		}
		static constexpr inline bool _ts_and_bs_hit(
			const RoomPath& rp_ts, const RoomPath& rp_bs
		) {
			return _ts_r2(rp_ts).intersect(_bs_r2(rp_bs));
		}
		//--------
		static constexpr inline bool _some_sides_hit(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return (_ls_r2_hit(rp_0, rp_1)
				|| _ts_r2_hit(rp_0, rp_1)
				|| _rs_r2_hit(rp_0, rp_1)
				|| _bs_r2_hit(rp_0, rp_1));
		}
		static constexpr inline bool _path_sides_hit_wrongly(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			return (
				(
					rp_0.is_horiz_path()
					&& (rp_1.is_horiz_path() || rp_1.is_room())
					&& (_ts_r2_hit(rp_0, rp_1)
						|| _bs_r2_hit(rp_0, rp_1))
				) || (
					rp_0.is_vert_path()
					&& (rp_1.is_vert_path() || rp_1.is_room())
					&& (_ls_r2_hit(rp_0, rp_1)
						|| _rs_r2_hit(rp_0, rp_1))
				) || (
					rp_1.is_horiz_path()
					&& (rp_0.is_horiz_path() || rp_0.is_room())
					&& (_ts_r2_hit(rp_1, rp_0)
						|| _bs_r2_hit(rp_1, rp_0))
				) || (
					rp_1.is_vert_path()
					&& (rp_0.is_vert_path() || rp_0.is_room())
					&& (_ls_r2_hit(rp_1, rp_0)
						|| _rs_r2_hit(rp_1, rp_0))
				)
			);
		}
		static constexpr inline bool _parallel_paths_too_close(
			const RoomPath& rp_0, const RoomPath& rp_1
		) {
			if (rp_0.is_horiz_path() && rp_1.is_horiz_path()) {
				return (
					rp_0.rect.build_in_grid_inflated_lim
						(IntVec2{0, GEN_PARALLEL_PATH_MIN_DIST}, IntVec2(),
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rp_1.rect)
					|| rp_1.rect.build_in_grid_inflated_lim
						(IntVec2{0, GEN_PARALLEL_PATH_MIN_DIST}, IntVec2(),
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rp_0.rect)
					|| rp_0.rect.build_in_grid_inflated_lim
						(IntVec2(), IntVec2{0, GEN_PARALLEL_PATH_MIN_DIST},
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rp_1.rect)
					|| rp_1.rect.build_in_grid_inflated_lim
						(IntVec2(), IntVec2{0, GEN_PARALLEL_PATH_MIN_DIST},
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rp_0.rect)
				);
			} else if (rp_0.is_vert_path() && rp_1.is_vert_path()) {
				return (
					rp_0.rect.build_in_grid_inflated_lim
						(IntVec2{GEN_PARALLEL_PATH_MIN_DIST, 0}, IntVec2(),
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rp_1.rect)
					|| rp_1.rect.build_in_grid_inflated_lim
						(IntVec2{GEN_PARALLEL_PATH_MIN_DIST, 0}, IntVec2(),
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rp_0.rect)
					|| rp_0.rect.build_in_grid_inflated_lim
						(IntVec2(), IntVec2{GEN_PARALLEL_PATH_MIN_DIST, 0},
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rp_1.rect)
					|| rp_1.rect.build_in_grid_inflated_lim
						(IntVec2(), IntVec2{GEN_PARALLEL_PATH_MIN_DIST, 0},
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rp_0.rect)
				);
			} else {
				return false;
			}
		}
		//--------
	};
	friend class GenInnards;
};
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon


#endif		// src_game_engine_dungeon_gen_dungeon_gen_class_hpp
