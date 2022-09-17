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
#include "general_comp_classes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace comp
{
//--------
#define LIST_OF_BG_TILE(X) \
	X(Wall) \
	X(Floor) \
	X(UpStairs) \
	X(DownStairs) \
	\
	X(Door) \
	X(Pit) \
	X(Water) \
	X(Spikes) \

enum class BgTile: u8
{
	//Wall,
	//Floor,
	//UpStairs,
	//DownStairs,

	//Door,
	//Pit,
	//Water,
	//Spikes,
	#define X(name) \
		name ,
	LIST_OF_BG_TILE(X)
	#undef X
};

extern const std::unordered_map<BgTile, std::string>& bg_tile_str_map();
//--------
// This should be generated when going to a new floor, and it shouldn't be
// written into save _data (outside of debugging).
class StaticBgTileMap final: public ecs::Comp
{
public:		// constants
	static const std::string
		KIND_STR;
private:		// variables
	#define MEMB_LIST_COMP_STATIC_LAYOUT(X) \
		X(_data, std::nullopt) \

	binser::VectorEx<binser::VectorEx<BgTile>> _data;
public:		// functions
	//--------
	StaticBgTileMap();
	StaticBgTileMap(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StaticBgTileMap);
	virtual ~StaticBgTileMap() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;
	//--------
private:		// functions
	//--------
	void _init_data();
	//--------
public:		// functions
	//--------
	inline BgTile& at(const DblVec2& pos)
	{
		return _data.data.at(pos.y).data.at(pos.x);
	}
	inline const BgTile& at(const DblVec2& pos) const
	{
		return _data.data.at(pos.y).data.at(pos.x);
	}

	template<typename VecElemT=typename DblVec2::ElemT>
	inline Vec2<VecElemT> size_2d() const
	{
		return Vec2<VecElemT>(_data.data.front().data.size(),
			_data.data.size());
	}
	//--------
};
//--------
class Dungeon final: public ecs::Comp
{
public:		// constants
	static const std::string
		KIND_STR;

	static constexpr i32
		// Chosen arbitrarily; might need to adjust later
		MIN_NUM_ROOMS = 3,
		MAX_NUM_ROOMS = 64;

		//MIN_NUM_PATHS = 1,
		//MAX_NUM_PATHS = 64;
public:		// types
	//--------
	class RoomPath final
	{
	public:		// constants
		static constexpr i32
			PATH_THICKNESS = 1,
			PATH_MIN_LEN = 2,
			PATH_MAX_LEN = 32;

		static constexpr IntVec2
			ROOM_MIN_SIZE_2D
				//= {3, 3},
				= {4, 4},
			ROOM_MAX_SIZE_2D
				= {10, 10};
				//= {15, 15};
	public:		// variables
		#define MEMB_AUTOSER_LIST_COMP_DUNGEON_ROOM_PATH(X) \
			/* X(rect, std::nullopt) */ \
			X(conn_set, std::nullopt) \

		IntRect2 rect
		{
			.pos=IntVec2(),
			.size_2d={PATH_THICKNESS, PATH_MIN_LEN}
		};
		std::set<i32> conn_set;
	public:		// functions
		//--------
		static RoomPath from_bv(const binser::Value& bv);
		operator binser::Value () const;
		//--------
		inline auto operator <=> (const RoomPath& to_cmp) const = default;
		//--------
		constexpr inline bool is_path() const
		{
			return ((rect.size_2d.x == PATH_THICKNESS)
				|| (rect.size_2d.y == PATH_THICKNESS));
		}
		constexpr inline bool is_horiz_path() const
		{
			return ((rect.size_2d.x >= PATH_MIN_LEN)
				&& (rect.size_2d.y == PATH_THICKNESS));
		}
		constexpr inline bool is_vert_path() const
		{
			return ((rect.size_2d.x == PATH_THICKNESS)
				&& (rect.size_2d.y >= PATH_MIN_LEN));
		}

		constexpr inline bool is_room() const
		{
			return ((rect.size_2d.x >= ROOM_MIN_SIZE_2D.x)
				&& (rect.size_2d.x <= ROOM_MAX_SIZE_2D.x)
				&& (rect.size_2d.y >= ROOM_MIN_SIZE_2D.y)
				&& (rect.size_2d.y <= ROOM_MAX_SIZE_2D.y));
		}
		//--------
	};
	//--------
private:		// variables
	#define MEMB_LIST_COMP_DUNGEON(X) \
		X(_data, std::nullopt) \
		/* X(_path_vec, std::nullopt) */ \

	binser::VectorEx<RoomPath> _data;
	//binser::VectorEx<Path> _path_vec;
public:		// functions
	//--------
	Dungeon();
	Dungeon(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Dungeon);
	virtual ~Dungeon() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;
	//--------
	inline RoomPath& at(size_t index)
	{
		return _data.data.at(index);
	}
	inline const RoomPath& at(size_t index) const
	{
		return _data.data.at(index);
	}
	inline void push_back(RoomPath&& to_push)
	{
		if (_data.data.size() + 1 > MAX_NUM_ROOMS)
		{
			throw std::length_error(sconcat
				("game_engine::comp::Dungeon::room_push_back(): ",
				"`_data` cannot increase in size: ",
				_data.data.size(), " ", MAX_NUM_ROOMS));
		}
		_data.data.push_back(std::move(to_push));
	}
	//--------
	//inline Path& path_at(size_t index)
	//{
	//	return _path_vec.data.at(index);
	//}
	//inline const Path& path_at(size_t index) const
	//{
	//	return _path_vec.data.at(index);
	//}
	//inline void path_push_back(Path&& to_push)
	//{
	//	if (_path_vec.data.size() + 1 > MAX_NUM_ROOMS)
	//	{
	//		throw std::length_error(sconcat
	//			("game_engine::comp::Dungeon::path_push_back(): ",
	//			"`_path_vec` cannot increase in size: ",
	//			_path_vec.data.size(), " ", MAX_NUM_ROOMS));
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
