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
#include "general_comp_classes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace comp
{
//--------
// This should be generated when going to a new floor, and it shouldn't be
// written into save _data (outside of debugging).
class StaticTileMap final: public ecs::Comp
{
public:		// types
	enum class Tile: u8
	{
		Wall,
		Floor,
		UpStairs,
		DownStairs,

		Door,
		Pit,
		Water,
		Spikes,
	};

	class Elem final
	{
	public:		// constants
		//--------
		static constexpr size_t
			VISITED_LO = 0x0,
			VISITED_HI = 0x0;
		//--------
	public:		// variables
		//--------
		#define MEMB_LIST_STATIC_TILE_MAP_ELEM(X) \
			X(tile, std::nullopt) \
			X(flags, std::nullopt) \

		Tile tile = Tile::Wall;
		u32 flags = 0;
		//--------
	public:		// functions
		//--------
		static Elem from_bv(const binser::Value& bv);
		operator binser::Value () const;
		//--------
		inline bool visited() const
		{
			return get_bits_with_range(flags, VISITED_HI, VISITED_LO);
		}
		inline bool set_visited(bool n_visited)
		{
			clear_and_set_bits_with_range(flags, n_visited, VISITED_HI,
				VISITED_LO);
			return visited();
		}
		//--------
	};
public:		// constants
	static const std::string
		KIND_STR,

		TILE_WALL_DRAWABLE_DATA_STR,
		TILE_FLOOR_DRAWABLE_DATA_STR,
		TILE_UP_STAIRS_DRAWABLE_DATA_STR,
		TILE_DOWN_STAIRS_DRAWABLE_DATA_STR,

		TILE_DOOR_DRAWABLE_DATA_STR,
		TILE_PIT_DRAWABLE_DATA_STR,
		TILE_WATER_DRAWABLE_DATA_STR,
		TILE_SPIKES_DRAWABLE_DATA_STR;
private:		// variables
	#define MEMB_LIST_COMP_STATIC_LAYOUT(X) \
		X(_data, std::nullopt) \

	binser::VectorEx<binser::VectorEx<Elem>> _data;
public:		// functions
	//--------
	StaticTileMap();
	StaticTileMap(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StaticTileMap);
	virtual ~StaticTileMap() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;
	//--------
private:		// functions
	//--------
	void _init_data();
	//--------
public:		// functions
	//--------
	inline Elem& at(const PosVec2& pos)
	{
		return _data.data.at(pos.y).data.at(pos.x);
	}
	inline const Elem& at(const PosVec2& pos) const
	{
		return _data.data.at(pos.y).data.at(pos.x);
	}

	template<typename VecElemT=typename SizeVec2::ElemT>
	inline Vec2<VecElemT> size_2d() const
	{
		return Vec2<VecElemT>(_data.data.front().data.size(),
			_data.data.size());
	}
	//--------
};
//--------
//class DungeonGenDb;
//--------
//--------
class DungeonGenDb final: public ecs::Comp
{
public:		// constants
	static const std::string
		KIND_STR;

	static constexpr u32
		// Chosen arbitrarily; might need to adjust later
		MIN_NUM_ROOMS = 1,
		MAX_NUM_ROOMS = 32,

		MIN_NUM_PATHS = 1,
		MAX_NUM_PATHS = 64,

		NULL_INDEX = -1;
public:		// types
	//--------
	class Room final
	{
	public:		// constants
		static constexpr SizeVec2::CtorArgs
			MIN_SIZE_2D = {.x=3, .y=3},
			MAX_SIZE_2D = {.x=10, .y=10};
	public:		// variables
		#define MEMB_TO_BV_LIST_COMP_DUNGEON_GEN_DB_ROOM(X) \
			X(pos, std::nullopt) \
			X(size_2d, std::nullopt) \

		#define MEMB_AUTOSER_LIST_COMP_DUNGEON_GEN_DB_ROOM(X) \
			/* X(pos, std::nullopt) */ \
			/* X(size_2d, std::nullopt) */ \

		PosVec2 pos = PosVec2();
		SizeVec2 size_2d = MIN_SIZE_2D;
	public:		// functions
		static Room from_bv(const binser::Value& bv);
		operator binser::Value () const;

		inline auto operator <=> (const Room& to_cmp) const = default;
	};
	//--------
	class Path final
	{
	public:		// constants
		static constexpr u32
			MIN_SIZE = 1,
			MAX_SIZE = 32;
	public:		// variables
		#define MEMB_TO_BV_LIST_COMP_DUNGEON_GEN_DB_PATH(X) \
			X(pos, std::nullopt) \
			X(size, std::nullopt) \

		#define MEMB_AUTOSER_LIST_COMP_DUNGEON_GEN_DB_PATH(X) \
			/* X(pos, std::nullopt) */ \
			/* X(size, std::nullopt) */ \
			X(horiz, std::nullopt) \

		PosVec2 pos = PosVec2();
		u32 size = MIN_SIZE;
		bool horiz = false;

	public:		// functions
		static Path from_bv(const binser::Value& bv);
		operator binser::Value () const;

		inline auto operator <=> (const Path& to_cmp) const = default;
	};
	//--------
private:		// variables
	#define MEMB_LIST_COMP_DUNGEON_GEN_DB(X) \
		X(_room_vec, std::nullopt) \
		X(_path_vec, std::nullopt) \

	binser::VectorEx<Room> _room_vec;
	binser::VectorEx<Path> _path_vec;
public:		// functions
	//--------
	DungeonGenDb();
	DungeonGenDb(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DungeonGenDb);
	virtual ~DungeonGenDb() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;
	//--------
	inline Room& room_at(size_t index)
	{
		return _room_vec.data.at(index);
	}
	inline const Room& room_at(size_t index) const
	{
		return _room_vec.data.at(index);
	}
	inline void room_push_back(Room&& to_push)
	{
		if (_room_vec.data.size() + 1 > MAX_NUM_ROOMS)
		{
			throw std::length_error(sconcat
				("game_engine::comp::DungeonGenDb::room_push_back(): ",
				"`_room_vec` cannot increase in size: ",
				_room_vec.data.size(), " ", MAX_NUM_ROOMS));
		}
		_room_vec.data.push_back(std::move(to_push));
	}
	//--------
	inline Path& path_at(size_t index)
	{
		return _path_vec.data.at(index);
	}
	inline const Path& path_at(size_t index) const
	{
		return _path_vec.data.at(index);
	}
	inline void path_push_back(Path&& to_push)
	{
		if (_path_vec.data.size() + 1 > MAX_NUM_ROOMS)
		{
			throw std::length_error(sconcat
				("game_engine::comp::DungeonGenDb::path_push_back(): ",
				"`_path_vec` cannot increase in size: ",
				_path_vec.data.size(), " ", MAX_NUM_ROOMS));
		}
		_path_vec.data.push_back(std::move(to_push));
	}
	//--------
};
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_comp_floor_layout_comp_classes_hpp
