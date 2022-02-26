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

#include "gm_dungeon_gen_class.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace sys
{

const std::string
	GmDungeonGen::KIND_STR("GmDungeonGen");

std::string GmDungeonGen::kind_str() const
{
	return KIND_STR;
}

void GmDungeonGen::init(ecs::Engine* ecs_engine)
{
	_init_start();
}

void GmDungeonGen::tick(ecs::Engine* ecs_engine)
{
	auto engine = game_engine::engine;

	if (_tick_helper(ecs_engine,
		engine->game_mode() == GameMode::DungeonGen))
	{
		// TODO: add procedural dungeon generation
	}
}

} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
