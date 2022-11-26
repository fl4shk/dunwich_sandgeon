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

#ifndef src_game_engine_dngn_gen_dngn_gen_class_hpp
#define src_game_engine_dngn_gen_dngn_gen_class_hpp

// src/game_engine/lvgen_etc/dngn_gen_class.hpp

#include "../../misc_includes.hpp"
#include "room_tunnel_class.hpp"
#include "dngn_floor_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
namespace sys {
class GmDngnGen;
} // namespace sys
//--------
namespace lvgen_etc {
//--------
class DngnGen final {
	friend class sys::GmDngnGen;
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
	//using DngnFloor = comp::DngnFloor;
	//using RoomTunnel = RoomTunnel;
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
		ALT_TERRAIN_NONE = BgTile::Error;
	static const std::vector<std::vector<BgTile>>
		ALLOWED_ALT_TERRAIN_DA2D;
		//LEVEL_1_ALT_TERRAIN_VEC,
		//LEVEL_2_ALT_TERRAIN_VEC,
		//LEVEL_3_ALT_TERRAIN_VEC,
		//LEVEL_4_ALT_TERRAIN_VEC,
		//LEVEL_5_ALT_TERRAIN_VEC;
	//--------
public:		// constants
	//--------
	static constexpr i32
		MIN_NUM_ROOM_TUNNELS = RoomTunnel::MIN_NUM_ROOM_TUNNELS,
		MAX_NUM_ROOM_TUNNELS = RoomTunnel::MAX_NUM_ROOM_TUNNELS,
		MIN_NUM_ROOMS = RoomTunnel::MIN_NUM_ROOMS;
	//--------
	static constexpr i32
		TUNNEL_THICKNESS = RoomTunnel::TUNNEL_THICKNESS,
		TUNNEL_MIN_LEN = RoomTunnel::TUNNEL_MIN_LEN,
		TUNNEL_MAX_LEN = RoomTunnel::TUNNEL_MAX_LEN;

	static constexpr IntVec2
		ROOM_MIN_SIZE_2D = RoomTunnel::ROOM_MIN_SIZE_2D,
		ROOM_MAX_SIZE_2D = RoomTunnel::ROOM_MAX_SIZE_2D;
	//--------
	static constexpr i32
		//--------
		// Generation percentages and stuff. 
		//--------
		GEN_TYPE_TUNNEL = 0, MIN_GEN_TYPE = GEN_TYPE_TUNNEL,
		GEN_TYPE_ROOM = 1, MAX_GEN_TYPE = GEN_TYPE_ROOM,
		//--------
		GEN_SIDE_L = 0, MIN_GEN_SIDE = GEN_SIDE_L,
		GEN_SIDE_T = 1,
		GEN_SIDE_R = 2,
		GEN_SIDE_B = 3, MAX_GEN_SIDE = GEN_SIDE_B,
		//--------
		MIN_GEN_SHRINK_NUM_ATTEMPTS_TUNNEL
			= (TUNNEL_MIN_LEN + TUNNEL_MAX_LEN) / 2,
		MAX_GEN_SHRINK_NUM_ATTEMPTS_TUNNEL = TUNNEL_MAX_LEN,

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
		GEN_PARALLEL_TUNNEL_MIN_DIST
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
			//= 1.0f,
			//= 2.0f,
			= 4.0f,
			//= 6.0f,
			//= 8.0f,
		GEN_BIOME_THRESH_MM_SCALE = 1000.0f;
	//static constexpr i32
	//	GEN_BIOME_MBINS_TYPE_TUNNEL = 0,
	//		MIN_GEN_BIOME_MBINS_TYPE = GEN_BIOME_MBINS_TYPE_TUNNEL,
	//	GEN_BIOME_MBINS_TYPE_ROOM = 1,
	//	GEN_BIOME_MBINS_TYPE_BOTH = 2,
	//		MAX_GEN_BIOME_MBINS_TYPE = GEN_BIOME_MBINS_TYPE_BOTH;
	static constexpr i32
		GEN_BIOME_MBALL_MIN_AMOUNT
			//= 2,
			//= 3,
			//= 4,
			//= 7,
			= 10,
			//= 15,
			//= 35,
		GEN_BIOME_MBALL_MAX_AMOUNT
			//= 4;
			//= 5;
			//= 7;
			//= 8;
			//= 10;
			//= 12;
			//= 13;
			//= 15;
			= 17;
			//= 20;
			//= 25;
			//= 28;
			//= 35;
	static constexpr IntVec2
		GEN_BIOME_MBALL_MIN_SIZE_2D
			//= {1, 1},
			//= {2, 2},
			= {3, 3},
			//= {4, 4},
			//= {5, 5},
			//= {6, 6},
			//= {7, 7},
		GEN_BIOME_MBALL_MAX_SIZE_2D
			//= {3, 3},
			//= {4, 4},
			//= {5, 5},
			= {6, 6},
			//= {7, 7},
			//= {8, 8},
			//= {9, 9},
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
			//.same_max=25,
			.same_max=34,
			//.same_max=45,
			.diff_max=99
			},
		GEN_NEXT_ROOM_INDEX
			{
			.same_max=3,
			.diff_max=9
			},

		GEN_NEXT_TUNNEL_TYPE
			{
			//.same_max=0,
			//.same_max=2,
			//.diff_max=9
			.same_max=19,
			//.same_max=25,
			//.same_max=5,
			.diff_max=99,
			//.same_max=32,
			//.same_max=85,
			//.diff_max=99
			},
		//GEN_NEXT_TUNNEL_INDEX
		//	{.same_max=85,
		//	.diff_max=99};
		// generating a room, and previously generated a path
		GEN_NEXT_TUNNEL_INDEX_NOW_ROOM
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
		GEN_NEXT_TUNNEL_INDEX_NOW_TUNNEL
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
			//.no_max=4,
			.no_max=7,
			//.no_max=14,
			//.no_max=35,
			.yes_max=99
			//.yes_max=999
			},

		GEN_YN_RM_DE_TUNNELS_DO_RM
			{
			//.no_max=29,
			//.no_max=19,
			.no_max=4,
			.yes_max=99,
			};
		//GEN_YN_RM_DE_TUNNELS_FINISH_IF
		//	{
		//	//.no_max=29,
		//	//.no_max=19,
		//	.no_max=94,
		//	.yes_max=99
		//	};
	//--------
	static constexpr i32
		// This is the number of tries to attempt room/path generation
		// after failing to generate a valid one.
		GEN_RP_LIM_TRIES
			//= 20;
			//= 50;
			= 100;
		//GEN_EXITS_LIM_TRIES
		//	= 350;
	//--------
private:		// variables
	i32
		_attempted_num_rt = 0;
	bool
		_stop_gen_early = false,
		_done_generating = false;
	//DngnFloor _dngn_floor;
public:		// functions
	DngnGen() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DngnGen);
	inline ~DngnGen() = default;

	void clear_before_gen(
		//ecs::Engine* ecs_engine
	);
	void gen_curr_floor();
	//GEN_GETTER_BY_CON_REF(dngn_floor);
private:		// functions
	//void _connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
	//	DngnFloor* dngn_floor);
private:		// types
	class GenInnards final {
	public:		// types
		//using RoomTunnel = DngnGen::RoomTunnel;
	private:		// variables
		DngnGen
			* _self = nullptr;
		//ecs::Engine
		//	* _ecs_engine = nullptr;
		//DngnFloor
		//	* _dngn_floor = nullptr;
		RoomTunnel _temp_to_push_rt;
		//RoomTunnel
		//	* _rt = nullptr,
		//	* _item = nullptr;
		//	//* _conn_rt = nullptr;

		i32
			//_gen_side = 0,
			_gen_next_type = 0,
			_gen_next_conn_rt_index = 0,
			_gen_type = 0,
			_conn_rt_index = 0;
		//size_t
		//	_check_i;
		//std::vector<std::vector<std::pair<bool, BgTile>>> _biome_bg_tiles;
	public:		// functions
		inline GenInnards(
			DngnGen* s_self
			//ecs::Engine* s_ecs_engine,
			//DngnFloor* s_dngn_floor
		)
			: _self(s_self)
			//_ecs_engine(s_ecs_engine),
			//_dngn_floor(s_dngn_floor)
			//_dngn_floor(&_self->dngn_floor)
		{
		}
		bool gen_single_rt();
	public:		// functions
		std::optional<RoomTunnel> _inner_gen_post_first();
	private:		// functions
		//--------
		void _do_push_back(RoomTunnel&& to_push_rt) const;
		//--------
		std::optional<RoomTunnel> _gen_initial_rt();
		//--------
		//i32 _choose_shrink_or_extend_side(
		//	bool was_horiz_tunnel, bool was_vert_tunnel,
		//	//const RoomTunnel& some_rt
		//	//const std::optional<size_t>& index
		//);
		bool _shrink(
			bool was_horiz_tunnel, bool was_vert_tunnel,
			RoomTunnel& some_rt, //const std::optional<size_t>& index,
			const std::function<bool(
				RoomTunnel&//, const std::optional<size_t>&
			)>& extra_test_func
		);
		bool _basic_shrink_extra_test_func(
			RoomTunnel& some_rt
			//, const std::optional<size_t>& index
		);
		void _connect_by_extending(
			//bool was_horiz_tunnel, bool was_vert_tunnel,
			//RoomTunnel& some_rt, //const std::optional<size_t>& index,
			//const std::function<bool(
			//	RoomTunnel&//, const std::optional<size_t>&
			//)>& shrink_extra_test_func
		);
		//--------
		bool _rt_is_connected(const RoomTunnel& some_rt) const;
		//--------
	public:		// functions
		//--------
		std::vector<size_t> any_intersect_find_all(
			RoomTunnel& to_check_rt, const std::optional<size_t>& index
		);
		std::optional<size_t> any_intersect_find_first(
			RoomTunnel& to_check_rt, const std::optional<size_t>& index
		);
		//--------
		std::vector<size_t> any_sides_intersect_find_all(
			RoomTunnel& to_check_rt, const std::optional<size_t>& index
		);
		std::optional<size_t> any_sides_intersect_find_first(
			RoomTunnel& to_check_rt, const std::optional<size_t>& index
		);
		//--------
		std::vector<size_t> any_tunnel_sides_hit_wrongly_find_all(
			RoomTunnel& to_check_rt, const std::optional<size_t>& index
		);
		std::optional<size_t> any_tunnel_sides_hit_wrongly_find_first(
			RoomTunnel& to_check_rt, const std::optional<size_t>& index
		);
		//--------
	private:		// functions
		//--------
		std::vector<size_t> _find_all_backend(
			RoomTunnel& to_check_rt,
			const std::optional<size_t>& index,
			const std::function<bool(
				RoomTunnel&, const RoomTunnel&
			)>& test_func
		);
		std::optional<size_t> _find_first_backend(
			RoomTunnel& to_check_rt,
			const std::optional<size_t>& index,
			const std::function<bool(
				RoomTunnel&, const RoomTunnel&
			)>& test_func
		);
		//--------
	public:		// functions
		//--------
		void finalize() const;
		//void insert_doors(bool do_clear) const;
	private:		// functions
		//--------
		void _remove_dead_end_tunnels() const;
		void _insert_exits() const;
		void _insert_items_and_doors() const;
		void _insert_alt_terrain() const;
		void _fill_in_alt_terrain() const;
		//--------
	private:		// static functions
		//--------
		static constexpr inline IntRect2 _ls_r2(const RoomTunnel& some_rt) {
			return r2_left_side_1ge_past_in_pfnb(some_rt.rect);
		}
		static constexpr inline IntRect2 _ts_r2(const RoomTunnel& some_rt) {
			return r2_top_side_1ge_past_in_pfnb(some_rt.rect);
		}
		static constexpr inline IntRect2 _rs_r2(const RoomTunnel& some_rt) {
			return r2_right_side_1ge_past_in_pfnb(some_rt.rect);
		}
		static constexpr inline IntRect2 _bs_r2(const RoomTunnel& some_rt) {
			return r2_bottom_side_1ge_past_in_pfnb(some_rt.rect);
		}
		//--------
		static constexpr inline bool _ls_r2_hit(
			const RoomTunnel& rt_0, const RoomTunnel& rt_1
		) {
			return 
				(//i32(_check_i) != _conn_rt_index
				//rt_0.gen_side == GEN_SIDE_L
				//&&
				r2_fits_in_pfnb(_ls_r2(rt_0))
				//r2_intersects_pfield_nb(_ls_r2(rt_0))
				&& rt_1.rect.intersect(_ls_r2(rt_0)));
		}
		static constexpr inline bool _ts_r2_hit(
			const RoomTunnel& rt_0, const RoomTunnel& rt_1
		) {
			return (r2_fits_in_pfnb(_ts_r2(rt_0))
				//r2_intersects_pfield_nb(_ts_r2(rt_0))
				&& rt_1.rect.intersect(_ts_r2(rt_0)));
		}
		static constexpr inline bool _rs_r2_hit(
			const RoomTunnel& rt_0, const RoomTunnel& rt_1
		) {
			return (r2_fits_in_pfnb(_rs_r2(rt_0))
				//r2_intersects_pfield_nb(_rs_r2(rt_0))
				&& rt_1.rect.intersect(_rs_r2(rt_0)));
		}
		static constexpr inline bool _bs_r2_hit(
			const RoomTunnel& rt_0, const RoomTunnel& rt_1
		) {
			return (r2_fits_in_pfnb(_bs_r2(rt_0))
				//r2_intersects_pfield_nb(_bs_r2(rt_0))
				&& rt_1.rect.intersect(_bs_r2(rt_0)));
		}
		//--------
		static constexpr inline bool _ls_and_rs_hit(
			const RoomTunnel& rt_ls, const RoomTunnel& rt_rs
		) {
			return _ls_r2(rt_ls).intersect(_rs_r2(rt_rs));
		}
		static constexpr inline bool _ts_and_bs_hit(
			const RoomTunnel& rt_ts, const RoomTunnel& rt_bs
		) {
			return _ts_r2(rt_ts).intersect(_bs_r2(rt_bs));
		}
		//--------
		static constexpr inline bool _some_sides_hit(
			const RoomTunnel& rt_0, const RoomTunnel& rt_1
		) {
			return (_ls_r2_hit(rt_0, rt_1)
				|| _ts_r2_hit(rt_0, rt_1)
				|| _rs_r2_hit(rt_0, rt_1)
				|| _bs_r2_hit(rt_0, rt_1));
		}
		static constexpr inline bool _tunnel_sides_hit_wrongly(
			const RoomTunnel& rt_0, const RoomTunnel& rt_1
		) {
			return (
				(
					rt_0.is_horiz_tunnel()
					&& (rt_1.is_horiz_tunnel() || rt_1.is_room())
					&& (_ts_r2_hit(rt_0, rt_1)
						|| _bs_r2_hit(rt_0, rt_1))
				) || (
					rt_0.is_vert_tunnel()
					&& (rt_1.is_vert_tunnel() || rt_1.is_room())
					&& (_ls_r2_hit(rt_0, rt_1)
						|| _rs_r2_hit(rt_0, rt_1))
				) || (
					rt_1.is_horiz_tunnel()
					&& (rt_0.is_horiz_tunnel() || rt_0.is_room())
					&& (_ts_r2_hit(rt_1, rt_0)
						|| _bs_r2_hit(rt_1, rt_0))
				) || (
					rt_1.is_vert_tunnel()
					&& (rt_0.is_vert_tunnel() || rt_0.is_room())
					&& (_ls_r2_hit(rt_1, rt_0)
						|| _rs_r2_hit(rt_1, rt_0))
				)
			);
		}
		static constexpr inline bool _parallel_tunnels_too_close(
			const RoomTunnel& rt_0, const RoomTunnel& rt_1
		) {
			if (rt_0.is_horiz_tunnel() && rt_1.is_horiz_tunnel()) {
				return (
					rt_0.rect.build_in_grid_inflated_lim
						(IntVec2{0, GEN_PARALLEL_TUNNEL_MIN_DIST},
						IntVec2(),
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rt_1.rect)
					|| rt_1.rect.build_in_grid_inflated_lim
						(IntVec2{0, GEN_PARALLEL_TUNNEL_MIN_DIST},
						IntVec2(),
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rt_0.rect)
					|| rt_0.rect.build_in_grid_inflated_lim
						(IntVec2(),
						IntVec2{0, GEN_PARALLEL_TUNNEL_MIN_DIST},
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rt_1.rect)
					|| rt_1.rect.build_in_grid_inflated_lim
						(IntVec2(),
						IntVec2{0, GEN_PARALLEL_TUNNEL_MIN_DIST},
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rt_0.rect)
				);
			} else if (rt_0.is_vert_tunnel() && rt_1.is_vert_tunnel()) {
				return (
					rt_0.rect.build_in_grid_inflated_lim
						(IntVec2{GEN_PARALLEL_TUNNEL_MIN_DIST, 0},
						IntVec2(),
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rt_1.rect)
					|| rt_1.rect.build_in_grid_inflated_lim
						(IntVec2{GEN_PARALLEL_TUNNEL_MIN_DIST, 0},
						IntVec2(),
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rt_0.rect)
					|| rt_0.rect.build_in_grid_inflated_lim
						(IntVec2(),
						IntVec2{GEN_PARALLEL_TUNNEL_MIN_DIST, 0},
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rt_1.rect)
					|| rt_1.rect.build_in_grid_inflated_lim
						(IntVec2(),
						IntVec2{GEN_PARALLEL_TUNNEL_MIN_DIST, 0},
						PFIELD_PHYS_NO_BRDR_RECT2).intersect(rt_0.rect)
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
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon


#endif		// src_game_engine_dngn_gen_dngn_gen_class_hpp
