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

#ifndef src_game_engine_comp_static_layout_comp_class_hpp
#define src_game_engine_comp_static_layout_comp_class_hpp

// src/game_engine/comp/static_layout_comp_class.hpp

#include "../../misc_includes.hpp"
#include "general_comp_classes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace comp
{

// This should be generated when going to a new floor, and it shouldn't be
// written into save data. I will store the seed that is used to generate a
// floor
class StaticLayout final: public ecs::Comp
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

	std::vector<std::vector<Tile>> _data;
public:		// functions
	inline StaticLayout() = default;
	StaticLayout(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StaticLayout);
	virtual ~StaticLayout() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value() const;

	inline Tile& at(const PosVec2& pos)
	{
		return _data.at(pos.y).at(pos.x);
	}
	inline Tile at(const PosVec2& pos) const
	{
		return _data.at(pos.y).at(pos.x);
	}

	template<typename VecElemT=size_t>
	inline Vec2<VecElemT> size_2d() const
	{
		return Vec2<VecElemT>(_data.front().size(), _data.size());
	}

	GEN_GETTER_BY_CON_REF(data);
};

} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_comp_static_layout_comp_class_hpp
