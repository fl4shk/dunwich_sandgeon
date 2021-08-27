// This file is part of Dungwich Sandeon.
// 
// Dungwich Sandeon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Dungwich Sandeon is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Dungwich Sandeon.  If not, see <https://www.gnu.org/licenses/>.

#ifndef src_game_engine_block_comp_classes_hpp
#define src_game_engine_block_comp_classes_hpp

// src/game_engine/block_comp_classes.hpp

#include "../../misc_includes.hpp"
#include "general_comp_classes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

//class InBetweenWalls final: public ecs::Comp
//{
//public:		// constants
//	static constexpr Drawable::Data
//		DRAWABLE_DATA{.c=' ', .color=FontColor::Black};
//public:		// functions
//	InBetweenWalls() = default;
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(InBetweenWalls);
//	virtual ~InBetweenWalls() = default;
//
//	virtual std::string kind_str() const;
//};

class Wall final: public ecs::Comp
{
public:		// constants
	static constexpr Drawable::Data
		DRAWABLE_DATA{.c='#', .color=FontColor::Gray};
public:		// functions
	Wall() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Wall);
	virtual ~Wall() = default;

	virtual std::string kind_str() const;
};

class Floor final: public ecs::Comp
{
public:		// constants
	static constexpr Drawable::Data
		DRAWABLE_DATA{.c='.', .color=FontColor::Gray};
public:		// functions
	Floor() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Floor);
	virtual ~Floor() = default;

	virtual std::string kind_str() const;
};

class DownStairs final: public ecs::Comp
{
public:		// constants
	static constexpr Drawable::Data
		DRAWABLE_DATA{.c='s', .color=FontColor::White};
public:		// functions
	DownStairs() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DownStairs);
	virtual ~DownStairs() = default;

	virtual std::string kind_str() const;
};

class UpStairs final: public ecs::Comp
{
public:		// constants
	static constexpr Drawable::Data
		DRAWABLE_DATA{.c='S', .color=FontColor::White};
public:		// functions
	UpStairs() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(UpStairs);
	virtual ~UpStairs() = default;

	virtual std::string kind_str() const;
};

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_block_comp_classes_hpp
