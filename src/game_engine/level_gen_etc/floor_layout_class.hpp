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

#ifndef src_game_engine_dungeon_gen_floor_layout_class_hpp
#define src_game_engine_dungeon_gen_floor_layout_class_hpp

// src/game_engine/level_gen_etc/floor_layout_class.hpp

#include "../../misc_includes.hpp"
//#include "../shape_classes.hpp"
#include "../w_bbox_base_classes.hpp"
#include "../global_shape_constants_etc.hpp"
//#include "path_class.hpp"
//#include "../comp/general_comp_classes.hpp"
#include "bg_tile_enum.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
class DungeonGen;
//--------
// The dungeon while it's either being generated has finished generating.
// As I don't think I'll be including breakable walls, in this game, this
// `ecs::Comp` can be referenced even after the dungeon has fully been
// generated for the purposes of, for example, monster AI.
class FloorLayout final {
	#include "dungeon_floor_friends.hpp"
public:		// constants
	static const std::string
		KIND_STR;

	static constexpr i32
		// Chosen arbitrarily; might need to adjust later
		MIN_NUM_ROOM_PATHS
			//= 3,
			//= 5,
			//= 8,
			//= 10,
			//= 13,
			//= 15,
			//= 20,
			= 25,
		MAX_NUM_ROOM_PATHS
			//= 3;
			//= 5;
			//= 8;
			//= 15;
			//= 42;
			= 64,
		MIN_NUM_ROOMS
			= 5;
			//= 7;

		//MIN_NUM_PATHS = 1,
		//MAX_NUM_PATHS = 64;

	static constexpr i32
		PATH_THICKNESS = 1,
		PATH_MIN_LEN
			//= 2,
			= 3,
			//= 4,
			//= 5,
		PATH_MAX_LEN
			//= 32;
			//= 20;
			//= 15;
			= 12;
			//= 10;
			//= 8;

	static constexpr IntVec2
		ROOM_MIN_SIZE_2D
			//= {3, 3},
			//= {4, 4},
			= {5, 5},
		ROOM_MAX_SIZE_2D
			//= {9, 9};
			//= {10, 10};
			= {12, 12};
			//= {15, 15};
public:		// static functions
	static constexpr inline bool r2_is_path(const IntRect2& r2) {
		return r2_is_horiz_path(r2) || r2_is_vert_path(r2);
	}
	static constexpr inline bool r2_is_horiz_path(const IntRect2& r2) {
		return (r2.size_2d.x >= PATH_MIN_LEN
			&& r2.size_2d.y == PATH_THICKNESS);
	}
	static constexpr inline bool r2_is_vert_path(const IntRect2& r2) {
		return (r2.size_2d.x == PATH_THICKNESS
			&& r2.size_2d.y >= PATH_MIN_LEN);
	}
	static constexpr inline bool r2_is_room(const IntRect2& r2) {
		return (r2.size_2d.x >= ROOM_MIN_SIZE_2D.x
			&& r2.size_2d.x <= ROOM_MAX_SIZE_2D.x
			&& r2.size_2d.y >= ROOM_MIN_SIZE_2D.y
			&& r2.size_2d.y <= ROOM_MAX_SIZE_2D.y);
	}
	static constexpr inline bool r2_is_valid(const IntRect2& r2) {
		return r2_is_path(r2) || r2_is_room(r2);
	}
public:		// types
	//--------
	class RoomPath final: public WIntBboxBase {
		#include "dungeon_floor_friends.hpp"
	public:		// variables
		#define MEMB_LIST_COMP_DUNGEON_ROOM_PATH(X) \
			/* X(rect, std::nullopt) */ \
			/* X(alt_terrain_umap, std::nullopt) */ \
			/* X(conn_index_set, std::nullopt) */ \
			/* X(door_pt_set, std::nullopt) */ \

		IntRect2 rect
			{.pos=IntVec2(),
			.size_2d{.x=PATH_THICKNESS, .y=PATH_MIN_LEN}};

		std::optional<IntVec2>
			// where the player and other entities start from when entering
			// this floor from above
			ustairs_pos = std::nullopt,
			dstairs_pos = std::nullopt;
			//ustairs_pos = std::nullopt;

		i32 id = -1;

		//class Xdata final {
		//public:		// variables
			i32 gen_side = 0;
			std::unordered_map<IntVec2, BgTile> alt_terrain_umap;

			std::unordered_set<i32> conn_index_uset;

			/// These are coordinates within pfield-space
			std::unordered_set<IntVec2> door_pt_uset;
		//} xdata;
		//bool show = false;
	public:		// functions
		//--------
		inline RoomPath() = default;
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(RoomPath);
		inline RoomPath(const IntRect2& s_rect)
			: rect(s_rect) {
		}
		virtual inline ~RoomPath() = default;
		//--------
		//static RoomPath from_bv(const binser::Value& bv);
		//operator binser::Value () const;
		//--------
		inline auto operator <=> (const RoomPath& to_cmp) const = default;
		//--------
		//virtual inline IntRect2& bbox() {
		//	return rect;
		//}
		virtual inline const IntRect2& bbox() const {
			return rect;
		}
		//--------
		//inline std::unordered_map<IntVec2, BgTile>& alt_terrain_umap() {
		//	return xdata.alt_terrain_umap;
		//}
		//inline const std::unordered_map<IntVec2, BgTile>&
		//alt_terrain_umap() const {
		//	return xdata.alt_terrain_umap;
		//}
		//inline std::unordered_set<i32>& conn_index_uset() {
		//	return xdata.conn_index_uset;
		//}
		//inline const std::unordered_set<i32>& conn_index_uset() const {
		//	return xdata.conn_index_uset;
		//}
		//inline std::unordered_set<IntVec2>& door_pt_uset() {
		//	return xdata.door_pt_uset;
		//}
		//inline const std::unordered_set<IntVec2>& door_pt_uset() const {
		//	return xdata.door_pt_uset;
		//}
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
		constexpr inline bool is_path() const {
			return r2_is_path(rect);
		}
		constexpr inline bool is_horiz_path() const {
			return r2_is_horiz_path(rect);
		}
		constexpr inline bool is_vert_path() const {
			return r2_is_vert_path(rect);
		}

		constexpr inline bool is_room() const {
			return r2_is_room(rect);
		}

		constexpr inline bool is_valid() const {
			return r2_is_valid(rect);
		}
		//--------
	};
	//--------
	using RoomPathSptr = std::shared_ptr<RoomPath>;
	//--------
private:		// variables
	#define MEMB_LIST_COMP_DUNGEON(X) \
		/* X(_rp_data, std::nullopt) */ \
		/* X(_layout_noise_pos_scale, std::nullopt) */ \
		/* X(_layout_noise_pos_offset, std::nullopt) */ \

	std::vector<RoomPathSptr> _rp_data;
	std::unordered_map<RoomPath*, size_t> _rp_to_index_umap;
	CollGridT _coll_grid;
	//binser::VectorEx<RoomPath> _rp_data;
	//double
	//	_layout_noise_pos_scale = 0.0d,
	//	_layout_noise_pos_offset = 0.0d;
public:		// functions
	//--------
	FloorLayout();
	//FloorLayout(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(FloorLayout);
	~FloorLayout() = default;

	//virtual std::string kind_str() const;
	//virtual operator binser::Value () const;
	//--------
	std::optional<BgTile> bg_tile_at(const IntVec2& pos, size_t i) const;
	std::optional<BgTile> phys_bg_tile_at(const IntVec2& pos) const;
	//inline std::optional<BgTile> left_phys_bg_tile_at(const IntVec2& pos)
	//const {
	//	return phys_bg_tile_at(pos + LEFT_OFFSET);
	//}
	//inline std::optional<BgTile> top_phys_bg_tile_at(const IntVec2& pos)
	//const {
	//	return phys_bg_tile_at(pos + TOP_OFFSET);
	//}
	//inline std::optional<BgTile> right_phys_bg_tile_at(const IntVec2& pos)
	//const {
	//	return phys_bg_tile_at(pos + RIGHT_OFFSET);
	//}
	//inline std::optional<BgTile> bottom_phys_bg_tile_at(const IntVec2& pos)
	//const {
	//	return phys_bg_tile_at(pos + BOTTOM_OFFSET);
	//}
	//--------
	inline auto begin() {
		//return _rp_data.data.begin();
		return _rp_data.begin();
	}
	inline auto end() {
		//return _rp_data.data.end();
		return _rp_data.end();
	}
	inline auto cbegin() const {
		//return _rp_data.data.cbegin();
		return _rp_data.cbegin();
	}
	inline auto cend() const {
		//return _rp_data.data.cend();
		return _rp_data.cend();
	}
private:		// functions
	inline RoomPath& _raw_at(size_t index) {
		//return _rp_data.data.at(index);
		return *_rp_data.at(index);
	}
	//RoomPath& _raw_phys_at(const IntVec2& phys_pos);
public:		// functions
	//inline RoomPath& at(size_t index) {
	//	//return _rp_data.data.at(index);
	//	return *_rp_data.at(index);
	//}
	inline const RoomPath& at(size_t index) const {
		//return _rp_data.data.at(index);
		return *_rp_data.at(index);
	}
	std::optional<size_t> phys_pos_to_rp_index(const IntVec2& phys_pos)
	const;
	//inline RoomPath::Xdata& xdata_at(size_t index) {
	//	return _rp_data.at(index)->xdata;
	//}
	//inline const RoomPath::Xdata& xdata_at(size_t index) const {
	//	return _rp_data.at(index)->xdata;
	//}
	void push_back(RoomPath&& to_push);
	//void pop_back() {
	//	_rp_to_index_umap.erase(_rp_data.back().get());
	//	_coll_grid.erase(_rp_data.back().get());
	//	_rp_data.pop_back();
	//}
	inline size_t size() const {
		//return _rp_data.data.size();
		return _rp_data.size();
	}
	inline void clear(
		//double n_layout_noise_pos_scale,
		//double n_layout_noise_pos_offset
	) {
		//_rp_data.data.resize(0);
		//_rp_data.data.clear();
		_rp_data.clear();
		_rp_to_index_umap.clear();
		_coll_grid.clear();
		//_layout_noise_pos_scale = n_layout_noise_pos_scale;
		//_layout_noise_pos_offset = n_layout_noise_pos_offset;
	}
	bool erase_maybe(size_t index);
	CollGridT::DataElPtrUsetT cg_neighbors(RoomPath& rp) const;
	CollGridT::DataElPtrUsetT cg_neighbors(size_t index) const;
	CollGridT::DataElPtrUsetT cg_neighbors(const IntVec2& pos) const;

	void draw() const;
	//--------
	GEN_GETTER_BY_CON_REF(rp_data);
	GEN_GETTER_BY_CON_REF(rp_to_index_umap);
	GEN_GETTER_BY_CON_REF(coll_grid);
	//GEN_GETTER_BY_CON_REF(path_vec);
	//GEN_GETTER_BY_CON_REF(layout_noise_pos_scale);
	//GEN_GETTER_BY_CON_REF(layout_noise_pos_offset);
	//--------
};
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_dungeon_gen_floor_layout_class_hpp
