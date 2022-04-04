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

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace sys
{

// Game Mode: Dungeon Generation
class GmDungeonGen final: public ecs::Sys
{
public:		// constants
	static const std::string KIND_STR;
public:		// functions
	GmDungeonGen() = default;
	//inline GmDungeonGen(const binser::Value& bv)
	//	: ecs::Sys(bv)
	//{
	//}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GmDungeonGen);
	virtual ~GmDungeonGen() = default;

	virtual std::string kind_str() const;
	virtual void init(ecs::Engine* ecs_engine);
	virtual void tick(ecs::Engine* ecs_engine);
private:		// functions
};

} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_sys_gm_dungeon_gen_class_hpp
