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

#include "gm_dngn_gen_class.hpp"
#include "../engine_class.hpp"
#include "../comp/drawable_data_umap.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace sys {
//--------
const std::string
	GmDngnGen::KIND_STR("GmDngnGen");

std::string GmDngnGen::kind_str() const {
	return KIND_STR;
}

void GmDngnGen::_init(ecs::Engine* ecs_engine) {
	_init_start();

	//const std::string func_name("game_engine::sys::GmDngnGen::_init");

	//if (ecs_engine->has_ent_w_comp(
	//	make_key_set<ecs::NonSerializable, comp::StaticBgTileMap>()
	//)) {
	//}

	//if (!_bg_tile_map_id) {
	//	_bg_tile_map_id = ecs_engine->create_singleton_all(
	//		ecs::make_comp_map_ks(
	//			ecs::CompSptr(new ecs::NonSerializable()),
	//			ecs::CompSptr(new comp::StaticBgTileMap())
	//		),
	//		func_name
	//	);
	//}
	//if (!_dngn_gen_id) {
	//	_dngn_gen_id = ecs_engine->create_singleton_all(
	//		ecs::make_comp_map_ks(
	//			ecs::CompSptr(new ecs::NonSerializable()),
	//			ecs::CompSptr(new DngnFloor())
	//		),
	//		func_name
	//	);

	//	engine->dbg_log("game_engine::sys::GmDngnGen::_init(): ",
	//		*_dngn_gen_id, "\n");
	//}
	//clear(ecs_engine);
	engine->dngn_gen.clear_before_gen();
	//engine->dngn_floor().clear_before_gen();
}

void GmDngnGen::tick(ecs::Engine* ecs_engine) {
	if (
		_tick_helper(ecs_engine,
			engine->game_mode() == GameMode::DngnGen)
	) {
		//auto* bg_tile_map
		//	= ecs_engine->casted_comp_at<comp::StaticBgTileMap>(
		//		*_bg_tile_map_id
		//	);
		//auto* dngn_floor
		//	= ecs_engine->casted_comp_at<DngnFloor>
		//		(*_dngn_gen_id);

		//if (engine->key_status.key_just_went_down(KeyKind::DownR))
		{
			engine->dngn_gen.gen_curr_floor();
		}
		//if (dngn_floor->size() >= 2) {
		//	clear(ecs_engine);
		//}

		//dngn_floor->draw(bg_tile_map);
		//bg_tile_map->draw();

		//engine->draw_main();
		engine->set_game_mode(GameMode::Main);
	}
}

//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
