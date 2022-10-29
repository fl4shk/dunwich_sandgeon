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

#include "gm_main_class.hpp"
#include "../engine_class.hpp"
#include "../comp/player_comp_class.hpp" 
#include "../comp/drawable_data_umap.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace sys {
//--------
const std::string
	GmMain::KIND_STR("GmMain");
std::string GmMain::kind_str() const {
	return KIND_STR;
}
//--------
void GmMain::_init(ecs::Engine* ecs_engine) {
	//--------
	_init_start();
	//--------
	const std::string func_name("game_engine::sys::GmMain::_init");

	if (!_player_id) {
		_player_id = ecs_engine->create_singleton_all
			(ecs::make_comp_umap_ks
				(ecs::CompSptr(new comp::Player()),
				//ecs::CompSptr(new comp::Drawable
				//	(comp::drawable_data_umap().at
				//		(comp::Player::KIND_STR))),
				comp::make_drawable<comp::Player>()),
			func_name);
		// See `game_engine::Engine::NonEcsSerData::player_pos` for the
		// player's position
	}
	//--------
}
void GmMain::tick(ecs::Engine* ecs_engine) {
	if (
		_tick_helper(ecs_engine,
			engine->game_mode() == GameMode::Main)
	) {
		//--------
		if (
			engine->key_status.key_just_went_down(KeyKind::LeftL)
			&& engine->key_status.key_up_now(KeyKind::RightL)
		) {
		} else if (
			engine->key_status.key_just_went_down(KeyKind::UpL)
			&& engine->key_status.key_up_now(KeyKind::DownL)
		) {
		} else if (
			engine->key_status.key_just_went_down(KeyKind::RightL)
			&& engine->key_status.key_up_now(KeyKind::LeftL)
		) {
		} else if (
			engine->key_status.key_just_went_down(KeyKind::DownL)
			&& engine->key_status.key_up_now(KeyKind::UpL)
		) {
		}
		//--------
		//else if (
		//) {
		//} else if (
		//) {
		//}
		//--------
		engine->draw_to_main_windows();
		//engine->pfield_window.clear();
		//engine->dungeon_gen.floor_layout().draw();
		//engine->screen_window.clear();

		//engine->screen_window.draw(engine->pfield_window);
		//engine->screen_window.draw(engine->log_window);
		//engine->screen_window.draw(engine->hud_window);
	}

}
//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
