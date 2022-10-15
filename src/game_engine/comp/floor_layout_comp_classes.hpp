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

#ifndef src_game_engine_comp_floor_layout_comp_classes_hpp
#define src_game_engine_comp_floor_layout_comp_classes_hpp

// src/game_engine/comp/floor_layout_comp_classes.hpp

#include "../../misc_includes.hpp"
//#include "../shape_classes.hpp"
#include "../global_shape_constants.hpp"
#include "general_comp_classes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace comp {
//--------
#define LIST_OF_BG_TILE(X) \
	X(Blank) \
	X(Error) \
	\
	X(Wall) \
	X(Door) \
	\
	X(RoomFloor) \
	X(PathFloor) \
	/* X(Floor) */ \
	X(Pit) \
	X(Water) \
	X(Spikes) \
	\
	X(UpStairs) \
	X(DownStairs) \

enum class BgTile: u8 {
	#define X(name) \
		name ,
	LIST_OF_BG_TILE(X)
	#undef X
};

//extern const std::unordered_map<BgTile, std::string>& bg_tile_str_map();
static constexpr inline std::string bg_tile_str_map_at(BgTile bg_tile) {
	switch (bg_tile) {
		#define X(name) \
			case BgTile:: name : \
				return "game_engine::comp::BgTile::" #name ; \
				break;
		LIST_OF_BG_TILE(X)
		#undef X

		default:
			throw std::invalid_argument(sconcat(
				"game_engine::comp::bg_tile_str_map_at(): Error: "
				"Invalid `bg_tile`: ", i32(bg_tile)
			));
			return "";
			break;
	}
}
//--------
//// This should be generated when going to a new floor, and it shouldn't be
//// written into save _data (outside of debugging).
//class StaticBgTileMap final: public ecs::Comp {
//public:		// constants
//	static const std::string
//		KIND_STR;
//private:		// variables
//	#define MEMB_LIST_COMP_STATIC_LAYOUT(X)
//		X(_data, std::nullopt)
//
//	binser::VectorEx<binser::VectorEx<BgTile>> _data;
//public:		// functions
//	//--------
//	StaticBgTileMap();
//	StaticBgTileMap(const binser::Value& bv);
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StaticBgTileMap);
//	virtual ~StaticBgTileMap() = default;
//
//	virtual std::string kind_str() const;
//	virtual operator binser::Value () const;
//	//--------
//	// This also clear
//	void init_data();
//	//--------
//	inline BgTile& at(const IntVec2& pos) {
//		//try {
//			return _data.data.at(pos.y).data.at(pos.x);
//		//} catch (const std::exception& e) {
//		//	printerr(e.what(), "\n");
//		//	throw std::out_of_range(sconcat("`pos`: ", pos));
//		//}
//	}
//	inline const BgTile& at(const IntVec2& pos) const {
//		return _data.data.at(pos.y).data.at(pos.x);
//	}
//
//	template<typename VecElemT=typename IntVec2::ElemT>
//	inline Vec2<VecElemT> size_2d() const {
//		return Vec2<VecElemT>(_data.data.front().data.size(),
//			_data.data.size());
//	}
//
//	void draw() const; 
//	//--------
//};
//--------
// The dungeon while it's either being generated has finished generating.
// As I don't think I'll be including breakable walls, in this game, this
// `ecs::Comp` can be referenced even after the dungeon has fully been
// generated for the purposes of, for example, monster AI.
class DungeonGen final: public ecs::Comp {
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
			= 20,
		MAX_NUM_ROOM_PATHS
			//= 15;
			= 30;

		//MIN_NUM_PATHS = 1,
		//MAX_NUM_PATHS = 64;

	static constexpr i32
		PATH_THICKNESS = 1,
		PATH_MIN_LEN
			//= 2,
			= 3,
			//= 5,
		PATH_MAX_LEN
			//= 32;
			//= 20;
			//= 15;
			= 12;
			//= 10;
			//= 8;

	static constexpr IntVec2
		ROOM_MIN_SIZE_2D{
			//3, 3
			4, 4,
		},
		ROOM_MAX_SIZE_2D{
			//9, 9,
			10, 10,
			//15, 15,
		};
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
	class RoomPath final {
	public:		// variables
		#define MEMB_LIST_COMP_DUNGEON_ROOM_PATH(X) \
			X(rect, std::nullopt) \
			/* X(gen_side, std::nullopt) */ \
			X(conn_index_set, std::nullopt) \
			X(door_pt_set, std::nullopt) \

		IntRect2 rect{
			.pos=IntVec2(),
			.size_2d{.x=PATH_THICKNESS, .y=PATH_MIN_LEN}
		};
		//i32 gen_side = 0;

		std::set<i32> conn_index_set;

		/// These are coordinates within pfield-space
		std::set<IntVec2> door_pt_set;
		//bool show = false;
	public:		// functions
		//--------
		static RoomPath from_bv(const binser::Value& bv);
		operator binser::Value () const;
		//--------
		inline auto operator <=> (const RoomPath& to_cmp) const = default;
		//--------
		constexpr inline bool fits_in_pfield_nb() const {
			//return (rect.pos.x >= 0
			//	&& rect.pos.x <= PFIELD_SIZE_2D.x);
			//return PFIELD_PHYS_RECT2.arg_inside(rect, false,
			//	IntVec2());
			//return PFIELD_PHYS_RECT2.arg_inside(rect, CDIFF_V2);
			//return PFIELD_PHYS_RECT2.arg_inside(rect);
			//return PFIELD_PHYS_RECT2.arg_inside<true>(rect);
			return r2_fits_in_pfield_nb(rect);
		}
		constexpr inline bool is_path() const {
			//return ((rect.size_2d.x == PATH_THICKNESS)
			//	|| (rect.size_2d.y == PATH_THICKNESS));
			//return is_horiz_path() || is_vert_path();
			return r2_is_path(rect);
		}
		constexpr inline bool is_horiz_path() const {
			//return (rect.size_2d.x >= PATH_MIN_LEN
			//	&& rect.size_2d.y == PATH_THICKNESS);
			return r2_is_horiz_path(rect);
		}
		constexpr inline bool is_vert_path() const {
			//return (rect.size_2d.x == PATH_THICKNESS
			//	&& rect.size_2d.y >= PATH_MIN_LEN);
			return r2_is_vert_path(rect);
		}

		constexpr inline bool is_room() const {
			//return (rect.size_2d.x >= ROOM_MIN_SIZE_2D.x
			//	&& rect.size_2d.x <= ROOM_MAX_SIZE_2D.x
			//	&& rect.size_2d.y >= ROOM_MIN_SIZE_2D.y
			//	&& rect.size_2d.y <= ROOM_MAX_SIZE_2D.y);
			return r2_is_room(rect);
		}

		constexpr inline bool is_valid() const {
			//return is_path() || is_room();
			return r2_is_valid(rect);
		}
		//--------
	};
	//--------
private:		// variables
	#define MEMB_LIST_COMP_DUNGEON(X) \
		X(_data, std::nullopt) \
		/* X(_path_vec, std::nullopt) */ \

	//std::vector<RoomPath> _data;
	binser::VectorEx<RoomPath> _data;
	//binser::VectorEx<Path> _path_vec;
public:		// functions
	//--------
	DungeonGen();
	DungeonGen(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DungeonGen);
	virtual ~DungeonGen() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;
	//--------
	inline auto begin() {
		return _data.data.begin();
	}
	inline auto end() {
		return _data.data.end();
	}
	inline auto cbegin() const {
		return _data.data.cbegin();
	}
	inline auto cend() const {
		return _data.data.cend();
	}
	inline RoomPath& at(size_t index) {
		return _data.data.at(index);
	}
	inline const RoomPath& at(size_t index) const {
		return _data.data.at(index);
	}
	inline void push_back(RoomPath&& to_push) {
		if (size() + 1 > MAX_NUM_ROOM_PATHS) {
			throw std::length_error(sconcat(
				"game_engine::comp::DungeonGen::room_push_back(): ",
				"`_data.data` cannot increase in size: ",
				_data.data.size(), " ", MAX_NUM_ROOM_PATHS
			));
		}
		_data.data.push_back(std::move(to_push));
	}
	inline size_t size() const {
		return _data.data.size();
	}
	inline void clear() {
		//_data.data.resize(0);
		_data.data.clear();
	}

	//void draw(StaticBgTileMap* bg_tile_map);
	void draw();
	//--------
	//inline Path& path_at(size_t index) {
	//	return _path_vec.data.at(index);
	//}
	//inline const Path& path_at(size_t index) const {
	//	return _path_vec.data.at(index);
	//}
	//inline void path_push_back(Path&& to_push) {
	//	if (_path_vec.data.size() + 1 > MAX_NUM_PATHS) {
	//		throw std::length_error(sconcat(
	//			"game_engine::comp::DungeonGen::path_push_back(): ",
	//			"`_path_vec` cannot increase in size: ",
	//			_path_vec.data.size(), " ", MAX_NUM_PATHS
	//		));
	//	}
	//	_path_vec.data.push_back(std::move(to_push));
	//}
	//--------
	GEN_GETTER_BY_CON_REF(data);
	//GEN_GETTER_BY_CON_REF(path_vec);
	//--------
};
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_comp_floor_layout_comp_classes_hpp
