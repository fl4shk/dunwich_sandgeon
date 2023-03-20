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

#ifndef src_game_engine_lvgen_etc_room_tunnel_class_hpp
#define src_game_engine_lvgen_etc_room_tunnel_class_hpp

// src/game_engine/lvgen_etc/room_tunnel_class.hpp

#include "../../misc_includes.hpp"
//#include "../shape_classes.hpp"
#include "../w_bbox_base_classes.hpp"
#include "../global_shape_constants_etc.hpp"
//#include "path_class.hpp"
//#include "../comp/general_comp_classes.hpp"
#include "bg_tile_enum.hpp"
#include "list_of_dngn_floor_friends_define.hpp"
namespace dunwich_sandgeon {
namespace game_engine {
//--------
class Engine;
//--------
namespace lvgen_etc {
//--------
class DngnGen;
//--------
// A Room or a Tunnel within the dungeon
class RoomTunnel final: public WIntBboxBase {
	#define X(arg) \
		friend class arg ;
	LIST_OF_DNGN_FLOOR_FRIENDS(X)
	#undef X
public:		// constants
	static const std::vector<i32>
		// Chosen arbitrarily; might need to adjust later
		MIN_NUM_ROOM_TUNNELS_DARR,
		MAX_NUM_ROOM_TUNNELS_DARR,
		MIN_NUM_ROOMS_DARR,

		MIN_NUM_LOCKS_DARR,
		MAX_NUM_LOCKS_DARR;

		//MIN_NUM_TUNNELS = 1,
		//MAX_NUM_TUNNELS = 64;

	static constexpr i32
		TUNNEL_THICKNESS = 1;

	static const std::vector<i32>
		TUNNEL_MIN_LEN_DARR,
		TUNNEL_MAX_LEN_DARR;

	static const std::vector<IntVec2>
		ROOM_MIN_SIZE_2D_DARR,
		ROOM_MAX_SIZE_2D_DARR;
public:		// serialized variables
	#define MEMB_SER_LIST_LVGEN_ETC_FLOOR_LAYOUT_ROOM_TUNNEL(X) \
		/* X(rect, std::nullopt) */ \
		/* X(alt_terrain_umap, std::nullopt) */ \
		/* X(conn_index_uset, std::nullopt) */ \
		/* X(door_pt_uset, std::nullopt) */ \
		/* X(destroyed_alt_terrain_uset, std::nullopt) */

	//std::unordered_set<IntVec2> destroyed_alt_terrain_uset;

	IntRect2 rect
		{.pos=IntVec2(),
		.size_2d{.x=TUNNEL_THICKNESS, .y=TUNNEL_MIN_LEN_DARR.at(0)}};

	//std::optional<IntVec2>
	//	// where the player and other entities start from when entering
	//	// this floor from above
	//	ustairs_pos = std::nullopt,
	//	dstairs_pos = std::nullopt;
	//	//ustairs_pos = std::nullopt;

	//i32 id = -1;

	i32 gen_side = 0;
	// These are coordinates within phys pfield-space
	//std::unordered_map<IntVec2, std::optional<BgTile>>
	std::unordered_map<IntVec2, BgTile>
		alt_terrain_umap;
	std::unordered_set<IntVec2>
		door_pt_uset;
	//std::unordered_set<ecs::EntId>
	//	items_traps_uset;

	std::unordered_set<i32> conn_index_uset;

	//std::unordered_map<IntVec2, std::optional<BgTile>>
	//std::unordered_map<IntVec2, std::optional<BgTile>>
	//	door_umap;
	//bool show = false;
public:		// static functions
	//--------
	static inline bool r2_is_tunnel(
		const IntRect2& r2, i32 level_index
	) {
		return r2_is_horiz_tunnel(r2, level_index)
			|| r2_is_vert_tunnel(r2, level_index);
	}
	static inline bool r2_is_horiz_tunnel(
		const IntRect2& r2, i32 level_index
	) {
		return (r2.size_2d.x >= TUNNEL_MIN_LEN_DARR.at(level_index)
			&& r2.size_2d.y == TUNNEL_THICKNESS);
	}
	static inline bool r2_is_vert_tunnel(
		const IntRect2& r2, i32 level_index
	) {
		return (r2.size_2d.x == TUNNEL_THICKNESS
			&& r2.size_2d.y >= TUNNEL_MIN_LEN_DARR.at(level_index));
	}
	static inline bool r2_is_room(
		const IntRect2& r2, i32 level_index
	) {
		return (r2.size_2d.x >= ROOM_MIN_SIZE_2D_DARR.at(level_index).x
			&& r2.size_2d.x <= ROOM_MAX_SIZE_2D_DARR.at(level_index).x
			&& r2.size_2d.y >= ROOM_MIN_SIZE_2D_DARR.at(level_index).y
			&& r2.size_2d.y <= ROOM_MAX_SIZE_2D_DARR.at(level_index).y);
	}
	static inline bool r2_is_valid(
		const IntRect2& r2, i32 level_index
	) {
		return (r2_is_tunnel(r2, level_index)
			|| r2_is_room(r2, level_index));
	}
	//--------
public:		// functions
	//--------
	RoomTunnel();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(RoomTunnel);
	RoomTunnel(const IntRect2& s_rect);
	virtual ~RoomTunnel();
	//--------
	//static RoomTunnel from_bv(const binser::Value& bv);
	//operator binser::Value () const;
	//--------
	inline auto operator <=> (const RoomTunnel& to_cmp) const = default;
	//--------
	//virtual inline IntRect2& bbox() {
	//	return rect;
	//}
	virtual inline const IntRect2& bbox() const {
		return rect;
	}
	//--------
	constexpr inline bool pos_in_border(
		const IntVec2& pos
	) const {
		return r2_pos_in_border(rect, pos);
	}
	constexpr inline bool pos_in_internal_border(
		const IntVec2& pos
	) const {
		return r2_pos_in_internal_border(rect, pos);
	}
	constexpr inline bool fits_in_pfnb() const {
		//return (rect.pos.x >= 0
		//	&& rect.pos.x <= PFIELD_SIZE_2D.x);
		//return PFIELD_PHYS_RECT2.arg_inside(rect, false,
		//	IntVec2());
		//return PFIELD_PHYS_RECT2.arg_inside(rect, CDIFF_V2);
		//return PFIELD_PHYS_RECT2.arg_inside(rect);
		//return PFIELD_PHYS_RECT2.arg_inside<true>(rect);
		return r2_fits_in_pfnb(rect);
	}
	inline bool is_tunnel(i32 level_index) const {
		return r2_is_tunnel(rect, level_index);
	}
	inline bool is_horiz_tunnel(i32 level_index) const {
		return r2_is_horiz_tunnel(rect, level_index);
	}
	inline bool is_vert_tunnel(i32 level_index) const {
		return r2_is_vert_tunnel(rect, level_index);
	}

	inline bool is_room(i32 level_index) const {
		return r2_is_room(rect, level_index);
	}

	inline bool is_valid(i32 level_index) const {
		return r2_is_valid(rect, level_index);
	}
	//--------
};

using RoomTunnelSptr = std::shared_ptr<RoomTunnel>;
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_lvgen_etc_room_tunnel_class_hpp
