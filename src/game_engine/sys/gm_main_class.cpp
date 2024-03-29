// This file is part of Dunwich Sandgeon.
// 
// Copyright 2023 FL4SHK
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

	if (
		auto ent_id_darr=ecs_engine->ent_id_darr_from_keys_all_v
			(comp::Player::KIND_STR, comp::Drawable::KIND_STR);
		true
	) {
		if (ent_id_darr.size() == 0) {
			_player_id = ecs_engine->create_singleton_all
				(ecs::make_comp_umap_ks
					(ecs::CompSptr(new comp::Player()),
					//ecs::CompSptr(new comp::Drawable
					//	(comp::drawable_data_umap().at
					//		(comp::Player::KIND_STR))),
					comp::make_drawable<comp::Player>()),
				func_name);
			//printout(ecs_engine->comp_at<comp::Player>(_player_id)->kind_str(),
			//	" ",
			//	ecs_engine->comp_at<comp::Drawable>(_player_id)->kind_str(),
			//	"\n");
			// See `game_engine::Engine::NonEcsSerData`'s `player_pos3` and
			// `prev_floor` for the player's position information
		} else if (ent_id_darr.size() != 1) {
			engine->corrupted_save_file_err();
		} else { // if (ent_id_darr.size() == 1)
			_player_id = ent_id_darr.front();
		}
	}
	//--------
	// temporary debugging code
	//--------
}
void GmMain::tick(ecs::Engine* ecs_engine) {
	if (
		_tick_helper(ecs_engine,
			engine->game_mode() == GameMode::Main)
	) {
		//--------
		PlayerAction action;
		if (
			(
				engine->key_status.key_just_went_down(KeyKind::Start)
				&& engine->key_status.key_down_now(KeyKind::Select)
			) || (
				engine->key_status.key_just_went_down(KeyKind::Select)
				&& engine->key_status.key_down_now(KeyKind::Start)
			)
		) {
			//engine->dbg_log("Returning to Title Screen\n");
			//engine->set_game_mode(GameMode::TitleScreen);
			engine->save_and_return_to_title();
			//engine->save_and_quit();
		} else if (
			engine->key_status.key_down_now(KeyKind::LeftD)
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::RightD, KeyKind::UpD, KeyKind::DownD})
		) {
			//action.move_dir = PathDir::Left;
			action.kind = InputKind::Left;
		} else if (
			engine->key_status.key_just_went_down(KeyKind::UpD)
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::DownD, KeyKind::LeftD, KeyKind::RightD})
		) {
			//action.move_dir = PathDir::Top;
			action.kind = InputKind::Up;
		} else if (
			engine->key_status.key_just_went_down(KeyKind::RightD)
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::LeftD, KeyKind::UpD, KeyKind::DownD})
		) {
			//action.kind = PathDir::Right;
			action.kind = InputKind::Right;
		} else if (
			engine->key_status.key_just_went_down(KeyKind::DownD)
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::UpD, KeyKind::LeftD, KeyKind::RightD})
		) {
			//action.move_dir = PathDir::Bottom;
			action.kind = InputKind::Down;
		} else if (
			(
				(
					engine->key_status.key_just_went_down(KeyKind::LeftD)
					&& engine->key_status.key_down_now(KeyKind::UpD)
				) || (
					engine->key_status.key_just_went_down(KeyKind::UpD)
					&& engine->key_status.key_down_now(KeyKind::LeftD)
				)
			) 
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::RightD, KeyKind::DownD})
		) {
			action.kind = InputKind::UpLeft;
		} else if (
			(
				(
					engine->key_status.key_just_went_down(KeyKind::RightD)
					&& engine->key_status.key_down_now(KeyKind::UpD)
				) || (
					engine->key_status.key_just_went_down(KeyKind::UpD)
					&& engine->key_status.key_down_now(KeyKind::RightD)
				)
			) 
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::LeftD, KeyKind::DownD})
		) {
			action.kind = InputKind::UpRight;
		} else if (
			(
				(
					engine->key_status.key_just_went_down(KeyKind::RightD)
					&& engine->key_status.key_down_now(KeyKind::DownD)
				) || (
					engine->key_status.key_just_went_down(KeyKind::DownD)
					&& engine->key_status.key_down_now(KeyKind::RightD)
				)
			) 
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::LeftD, KeyKind::UpD})
		) {
			action.kind = InputKind::DownRight;
		} else if (
			(
				(
					engine->key_status.key_just_went_down(KeyKind::LeftD)
					&& engine->key_status.key_down_now(KeyKind::DownD)
				) || (
					engine->key_status.key_just_went_down(KeyKind::DownD)
					&& engine->key_status.key_down_now(KeyKind::LeftD)
				)
			) 
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::RightD, KeyKind::UpD})
		) {
			action.kind = InputKind::DownLeft;
		} else if (
			engine->key_status.key_just_went_down(KeyKind::LeftF)
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::UpF, KeyKind::RightF, KeyKind::DownF})
		) {
		} else if (
			engine->key_status.key_just_went_down(KeyKind::UpF)
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::LeftF, KeyKind::RightF, KeyKind::DownF})
		) {
		} else if (
			engine->key_status.key_just_went_down(KeyKind::RightF)
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::LeftF, KeyKind::UpF, KeyKind::DownF})
		) {
		} else if (
			engine->key_status.key_just_went_down(KeyKind::DownF)
			&& engine->key_status.key_uset_up_now(std::unordered_set
				{KeyKind::LeftF, KeyKind::UpF, KeyKind::RightF})
		) {
		}
		//--------
		//if (action.move_dir) {
		//	
		//}
		//--------
		engine->draw_to_main_windows();
		//engine->pfield_window.clear();
		//engine->dngn_gen.dngn_floor().draw();
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
