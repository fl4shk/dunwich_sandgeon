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
#include "../comp/floor_layout_comp_classes.hpp"

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

void GmDungeonGen::_init(ecs::Engine* ecs_engine)
{
	_init_start();

	// In this case, there shouldn't be any
	_bg_tile_map_id = ecs_engine->create_singleton_all
		(ecs::make_comp_map_ks
			(ecs::CompSptr(new ecs::NonSerializable()),
			ecs::CompSptr(new comp::StaticBgTileMap())),
		sconcat("game_engine::sys::", KIND_STR));
}

void GmDungeonGen::tick(ecs::Engine* ecs_engine)
{
	if (_tick_helper(ecs_engine,
		engine->game_mode() == GameMode::DungeonGen))
	{
		// TODO: add procedural dungeon generation
		auto* bg_tile_map
			= ecs_engine->casted_comp_at<comp::StaticBgTileMap>
				(_bg_tile_map_id);

		bg_tile_map->draw();
		engine->screen_window.clear();

		engine->screen_window.draw(engine->pfield_window);
		engine->screen_window.draw(engine->log_window);
		engine->screen_window.draw(engine->hud_window);
	}
}

} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
